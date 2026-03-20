#include "all.h"

//**************************************************************************** S
//	  関数名		:	敵キャラクターの表示、行動処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	Hero.cの敵バージョン
//	 最終更新日		:	2003/01/09 (火)
//**************************************************************************** E

// 敵に関するデファイン
#define	SLIME_SPEED			0x0000C000	// スライムの移動速度
#define	SLIME_SEARCH		32			//           索敵範囲

#define	US_SPEED			0x0000C000	// トカゲの移動速度
#define	US_SEARCH			32			//         索敵範囲
#define US_INTERVAL			60			//         攻撃間隔

#define	NU_SPEED			0x0000C000	// スシの移動速度
#define	NU_SEARCH			32			//       索敵範囲
#define NU_INTERVAL			60			//       攻撃間隔

#define	PZ_SPEED			0x00014000	// プラズマの移動速度
#define	PZ_SEARCH			32			//           索敵範囲
#define PZ_INTERVAL			60			//           攻撃間隔

#define	TR_SPEED			0x0000C000	// トリの移動速度
#define	TR_SEARCH			32			//       索敵範囲
#define TR_INTERVAL			60			//       攻撃間隔

#define	MAGIC_SPEED			2			// 魔法の移動スピード

// 魔法発射時のオフセット
#define MG_RIGHT_OFFSET_X 	32
#define MG_RIGHT_OFFSET_Y 	16

#define MG_LEFT_OFFSET_X 	16
#define MG_LEFT_OFFSET_Y 	16

#define MG_UP_OFFSET_X 		8
#define MG_UP_OFFSET_Y 		16

#define MG_DOWN_OFFSET_X 	8
#define MG_DOWN_OFFSET_Y 	32

void EnemyMagicAttack (void);

s32 enemymg_offset_x;
s32 enemymg_offset_y;

void Enemy (void)
{
	s32 local_x,local_y;
	s32	work_x,work_y;
	
	// ワールド座標からローカル座標への変換
	local_x = EnemyNowstatus[EnemyNo].x - PlayerNowstatus[PlayerNo].x;
	local_y = EnemyNowstatus[EnemyNo].y - PlayerNowstatus[PlayerNo].y;
	
	work_x = PlayerNowstatus[PlayerNo].x + ( HERO_CENTER_X << 16 );
	work_y = PlayerNowstatus[PlayerNo].y + ( HERO_CENTER_Y << 16 );

	OamBuf[EnemyNo+1].Bit32 = OAM_OBJ_ON;
	OamBuf[EnemyNo+1].Oam.Pltt = EnemyNowstatus[EnemyNo].coloer;
	OamBuf[EnemyNo+1].Oam.CharNo = 128 + 32*(EnemyNo+1);

	// ******************** 選択キャラによる処理の分岐 ******************** S
	
	switch ( EnemyNowstatus[EnemyNo].name ){
	
		// ***********************   スライム   ************************** S
		case SLIME :
			switch ( EnemyNowstatus[EnemyNo].type ){
				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + SLIME_SEARCH)<<16 && local_x <= (240 - SLIME_SEARCH)<<16 && local_y >= (-32 + SLIME_SEARCH)<<16 && local_y <= (160 - SLIME_SEARCH)<<16){
						if ( ( work_x >> 16 ) < ( EnemyNowstatus[EnemyNo].x >> 16 ) ){
							EnemyNowstatus[EnemyNo].x -= SLIME_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( ( work_x >> 16 ) > ( EnemyNowstatus[EnemyNo].x >> 16 ) ){
							EnemyNowstatus[EnemyNo].x += SLIME_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}
						if ( ( work_y >> 16 ) < ( EnemyNowstatus[EnemyNo].y >> 16 ) ){
							EnemyNowstatus[EnemyNo].y -= SLIME_SPEED;		// 上へ移動
						}
						else if ( ( work_y >> 16 ) > ( EnemyNowstatus[EnemyNo].y >> 16 ) ){
							EnemyNowstatus[EnemyNo].y += SLIME_SPEED;		// 下へ移動
						}
						else {
						}
					}

					// *********************** スライムの表示 ************************** S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_SL_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
						NowAnime2 = (ANIME*)ENEMY_SL_F;			// 攻撃力を格納する
					}
					else OamBuf[EnemyNo+1].Bit32 = OAM_OBJ_OFF;
					// *********************** スライムの表示 ************************** E
					break;
				case ATK :		// スライムは攻撃アニメーション無し
					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_SL_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
							NowAnime2 = (ANIME*)ENEMY_SL_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}
			// ***********************   スライム   ************************** E
 			break;
		case RAFRY :
			// ***********************    ラフリ    ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){
			
				case STAND :
					if( !EnemyMagic[EnemyNo].status ){
						if ( local_x >= (-32 + SLIME_SEARCH)<<16 && local_x <= (240 - SLIME_SEARCH)<<16 && local_y >= (-32 + SLIME_SEARCH)<<16 && local_y <= (160 - SLIME_SEARCH)<<16){
							if ( work_x >> 16 < ( EnemyNowstatus[EnemyNo].x >> 16 ) - 10 ){
								enemymg_offset_x = -1;
							}
							else if ( work_x >> 16 > ( EnemyNowstatus[EnemyNo].x >> 16 ) + 10 ){
								enemymg_offset_x = 1;
							}
							else{
								enemymg_offset_x = 0;
							}
							if ( work_y >> 16 < ( EnemyNowstatus[EnemyNo].y >> 16 ) - 10){
								enemymg_offset_y = -1;
							}
							else if ( work_y >> 16 > ( EnemyNowstatus[EnemyNo].y  >> 16 ) + 10 ){
								enemymg_offset_y = 1;
							}
							else{
								enemymg_offset_y = 0;
							}
							EnemyMagic[EnemyNo].status = 1;
						}
					}
					if( EnemyMagic[EnemyNo].status ){
						EnemyMagicAttack();
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_RF_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
//						NowAnime2 = (ANIME*)ENEMY_RF_F;			// 攻撃力を格納する
					}
					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_RF_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_RF_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}		

			// ***********************    ラフリ    ************************** E
			break;
		case USA :
			// ***********************    トカゲ    ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + US_SEARCH)<<16 && local_x <= (240 - US_SEARCH)<<16 && local_y >= (-32 + US_SEARCH)<<16 && local_y <= (160 - US_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= US_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += US_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= US_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += US_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
						EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************   トカゲの表示   **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_US_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_US_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_US_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_US_F;			// 攻撃力を格納する
						}
					}
					// ***********************   トカゲの表示   **************************E
					break;
				case ATK :
					// ***********************   トカゲの攻撃   **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								OamBuf[EnemyNo+1].Oam.HFlip = 1;
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_US_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_US_ATK_F;		// 攻撃力を格納する
								break;
							case TURN_D :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_US_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_US_ATK_F;			// 攻撃力を格納する
						}
					}
					// ***********************   トカゲの攻撃   **************************E
					break;
				case INTERVAL :
					// ******************  トカゲの攻撃インターバル  *********************S
					EnemyNowstatus[EnemyNo].count++;				// カウンタの加算
					if ( EnemyNowstatus[EnemyNo].count > US_INTERVAL ){
						EnemyNowstatus[EnemyNo].type = STAND;
						EnemyNowstatus[EnemyNo].count = 0;			// カウンタリセット
					}
					if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x -= US_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 1;
					}
					else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x += US_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 0;
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_US_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_US_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_US_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_US_F;			// 攻撃力を格納する
						}
					}
					// ******************  トカゲの攻撃インターバル  *********************E

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_US_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_US_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}		
			// ***********************    トカゲ    ************************** E
			break;
		case SUSI :
			// ***********************     スシ     ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + NU_SEARCH)<<16 && local_x <= (240 - NU_SEARCH)<<16 && local_y >= (-32 + NU_SEARCH)<<16 && local_y <= (160 - NU_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= NU_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += NU_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= NU_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += NU_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
						EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************    スシの表示    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_NU_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_NU_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_NU_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_NU_F;			// 攻撃力を格納する
						}
					}
					// ***********************    スシの表示    **************************E
					break;
				case ATK :
					// ***********************    スシの攻撃    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_NU_ATK_R , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_NU_ATK_R;		// 攻撃力を格納する
								break;
							case TURN_D :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_NU_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_NU_ATK_F;			// 攻撃力を格納する
						}
					}
					// ***********************    スシの攻撃    **************************E
					break;
				case INTERVAL :
					// ******************   スシの攻撃インターバル   *********************S
					EnemyNowstatus[EnemyNo].count++;				// カウンタの加算
					if ( EnemyNowstatus[EnemyNo].count > NU_INTERVAL ){
						EnemyNowstatus[EnemyNo].type = STAND;
						EnemyNowstatus[EnemyNo].count = 0;			// カウンタリセット
					}
					if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x -= NU_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 1;
					}
					else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x += NU_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 0;
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_NU_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_NU_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_NU_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_NU_F;			// 攻撃力を格納する
						}
					}
					// ******************   スシの攻撃インターバル   *********************E

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_NU_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_NU_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}		
			// ***********************     スシ     ************************** E
			break;
		case PLAZUMA :
			// ***********************   プラズマ   ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + PZ_SEARCH)<<16 && local_x <= (240 - PZ_SEARCH)<<16 && local_y >= (-32 + PZ_SEARCH)<<16 && local_y <= (160 - PZ_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= PZ_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += PZ_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= PZ_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += PZ_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
						EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************  プラズマの表示  **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_PZ_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_PZ_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_PZ_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_PZ_F;			// 攻撃力を格納する
						}
					}
					// ***********************  プラズマの表示  **************************E
					break;
				case ATK :
					// ***********************  プラズマの攻撃  **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_PZ_ATK_R , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_PZ_ATK_R;		// 攻撃力を格納する
								break;
							case TURN_D :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_PZ_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_PZ_ATK_F;			// 攻撃力を格納する
						}
					}
					// ***********************  プラズマの攻撃  **************************E
					break;
				case INTERVAL :
					// ****************** プラズマの攻撃インターバル *********************S
					EnemyNowstatus[EnemyNo].count++;				// カウンタの加算
					if ( EnemyNowstatus[EnemyNo].count > PZ_INTERVAL ){
						EnemyNowstatus[EnemyNo].type = STAND;
						EnemyNowstatus[EnemyNo].count = 0;			// カウンタリセット
					}
					if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x -= PZ_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 1;
					}
					else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x += PZ_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 0;
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_PZ_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_PZ_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_PZ_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_PZ_F;			// 攻撃力を格納する
						}
					}
					// ****************** プラズマの攻撃インターバル *********************E

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_PZ_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_PZ_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}		
			// ***********************   プラズマ   ************************** E
			break;

		case UNI :
			// ***********************     ウニ     ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + TR_SEARCH)<<16 && local_x <= (240 - TR_SEARCH)<<16 && local_y >= (-32 + TR_SEARCH)<<16 && local_y <= (160 - TR_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= TR_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += TR_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
					//	EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************    ウニの表示    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_UI_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_TR_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_UI_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_TR_F;			// 攻撃力を格納する
						}
					}
					// ***********************    ウニの表示    **************************E
					break;
				case ATK :
					break;
				case INTERVAL :

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_UI_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_UI_ATK_F;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}		
			// ***********************     ウニ     ************************** E
			break;

		case TORI :
			// ***********************     トリ     ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + TR_SEARCH)<<16 && local_x <= (240 - TR_SEARCH)<<16 && local_y >= (-32 + TR_SEARCH)<<16 && local_y <= (160 - TR_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= TR_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += TR_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
						EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************    トリの表示    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_TR_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_TR_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_TR_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_TR_F;			// 攻撃力を格納する
						}
					}
					// ***********************    トリの表示    **************************E
					break;
				case ATK :
					// ***********************    トリの攻撃    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_TR_ATK_R , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_TR_ATK_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_TR_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_TR_ATK_F;			// 攻撃力を格納する
						}
					}
					// ***********************    トリの攻撃    **************************E
					break;
				case INTERVAL :
					// ******************   トリの攻撃インターバル   *********************S
					EnemyNowstatus[EnemyNo].count++;				// カウンタの加算
					if ( EnemyNowstatus[EnemyNo].count > TR_INTERVAL ){
						EnemyNowstatus[EnemyNo].type = STAND;
						EnemyNowstatus[EnemyNo].count = 0;			// カウンタリセット
					}
					if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 1;
					}
					else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 0;
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_TR_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_TR_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_TR_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_TR_F;			// 攻撃力を格納する
						}
					}
					// ******************   トリの攻撃インターバル   *********************E

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_TR_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_TR_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}
			break;
			// ***********************     トリ     ************************** E

		case BAT :
			// ***********************     蝙蝠     ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + TR_SEARCH)<<16 && local_x <= (240 - TR_SEARCH)<<16 && local_y >= (-32 + TR_SEARCH)<<16 && local_y <= (160 - TR_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= TR_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += TR_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
						EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************    蝙蝠の表示    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_KO_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_KO_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_KO_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_KO_F;			// 攻撃力を格納する
						}
					}
					// ***********************    蝙蝠の表示    **************************E
					break;
				case ATK :
					// ***********************    蝙蝠の攻撃    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_KO_ATK_R , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_KO_ATK_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_KO_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_KO_ATK_F;			// 攻撃力を格納する
						}
					}
					// ***********************    蝙蝠の攻撃    **************************E
					break;
				case INTERVAL :
					// ******************   蝙蝠の攻撃インターバル   *********************S
					EnemyNowstatus[EnemyNo].count++;				// カウンタの加算
					if ( EnemyNowstatus[EnemyNo].count > TR_INTERVAL ){
						EnemyNowstatus[EnemyNo].type = STAND;
						EnemyNowstatus[EnemyNo].count = 0;			// カウンタリセット
					}
					if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 1;
					}
					else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 0;
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_KO_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_KO_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_KO_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_KO_F;			// 攻撃力を格納する
						}
					}
					// ******************   蝙蝠の攻撃インターバル   *********************E

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_KO_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_KO_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}		
			break;
			// ***********************     蝙蝠     ************************** E

		case GHOST :
			// ***********************     ゴースト     ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + TR_SEARCH)<<16 && local_x <= (240 - TR_SEARCH)<<16 && local_y >= (-32 + TR_SEARCH)<<16 && local_y <= (160 - TR_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= TR_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += TR_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
						EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************    ゴーストの表示    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_GO_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_GO_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_GO_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_GO_F;			// 攻撃力を格納する
						}
					}
					// ***********************    ゴーストの表示    **************************E
					break;
				case ATK :
					// ***********************    ゴーストの攻撃    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_GO_ATK_R , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_GO_ATK_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_GO_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_GO_ATK_F;			// 攻撃力を格納する
						}
					}
					// ***********************    ゴーストの攻撃    **************************E
					break;
				case INTERVAL :
					// ******************   ゴーストの攻撃インターバル   *********************S
					EnemyNowstatus[EnemyNo].count++;				// カウンタの加算
					if ( EnemyNowstatus[EnemyNo].count > TR_INTERVAL ){
						EnemyNowstatus[EnemyNo].type = STAND;
						EnemyNowstatus[EnemyNo].count = 0;			// カウンタリセット
					}
					if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 1;
					}
					else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 0;
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_GO_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_GO_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_GO_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_GO_F;			// 攻撃力を格納する
						}
					}
					// ******************   ゴーストの攻撃インターバル   *********************E

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_GO_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_GO_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}		
			break;
			// ***********************     ゴースト     ************************** E

		case DOM :
			// ***********************     ドム     ************************** S
			switch ( EnemyNowstatus[EnemyNo].type ){

				case STAND :

					// 視界範囲に入ると追跡を開始
					if ( local_x >= (-32 + TR_SEARCH)<<16 && local_x <= (240 - TR_SEARCH)<<16 && local_y >= (-32 + TR_SEARCH)<<16 && local_y <= (160 - TR_SEARCH)<<16){
						if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 1;
						}
						else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
							EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 右へ移動
							OamBuf[EnemyNo+1].Oam.HFlip = 0;
						}
						else {
						}

						if ( work_y >> 16 < EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y -= TR_SPEED;		// 上へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_U;
						}
						else if ( work_y >> 16 > EnemyNowstatus[EnemyNo].y >> 16 ){
							EnemyNowstatus[EnemyNo].y += TR_SPEED;		// 下へ移動
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
						else{
							EnemyNowstatus[EnemyNo].turn = TURN_D;
						}
					}

					if ( local_x >= (104-32)<<16 && local_x <= (104+32)<<16 && local_y >= (54-32)<<16 && local_y <= (54+32)<<16){
						EnemyNowstatus[EnemyNo].type = ATK;

					}
					// ***********************    ドムの表示    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){

						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_DO_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_DO_F;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_DO_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_DO_F;			// 攻撃力を格納する
						}
					}
					// ***********************    ドムの表示    **************************E
					break;
				case ATK :
					// ***********************    ドムの攻撃    **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_DO_ATK_R , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_DO_ATK_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_DO_ATK_F , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
									EnemyNowstatus[EnemyNo].type = INTERVAL;
								}
								NowAnime2 = (ANIME*)ENEMY_DO_ATK_F;			// 攻撃力を格納する
						}
					}
					// ***********************    ドムの攻撃    **************************E
					break;
				case INTERVAL :
					// ******************   ドムの攻撃インターバル   *********************S
					EnemyNowstatus[EnemyNo].count++;				// カウンタの加算
					if ( EnemyNowstatus[EnemyNo].count > TR_INTERVAL ){
						EnemyNowstatus[EnemyNo].type = STAND;
						EnemyNowstatus[EnemyNo].count = 0;			// カウンタリセット
					}
					if ( work_x >> 16 < EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x -= TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 1;
					}
					else if ( work_x >> 16 > EnemyNowstatus[EnemyNo].x >> 16 ){
						EnemyNowstatus[EnemyNo].x += TR_SPEED;		// 左へ移動
						OamBuf[EnemyNo+1].Oam.HFlip = 0;
					}
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						switch ( EnemyNowstatus[EnemyNo].turn ){
							case TURN_U :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_DO_R   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_DO_R;			// 攻撃力を格納する
								break;
							case TURN_D :
								Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_DO_F   , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime);
								NowAnime2 = (ANIME*)ENEMY_DO_F;			// 攻撃力を格納する
						}
					}
					// ******************   ドムの攻撃インターバル   *********************E

					break;
				case DAMAGE :
					// *********************** ダメージ状態 **************************S
					if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
						if ( Action( EnemyNo+1, OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1), ENEMY_DO_DAM , local_x>>16, local_y>>16, &EnemyNowstatus[EnemyNo].cnt, &EnemyNowstatus[EnemyNo].anime)){
							EnemyNowstatus[EnemyNo].type = STAND;
						}
						NowAnime2 = (ANIME*)ENEMY_DO_DAM;			// 攻撃力を格納する
					}
					// *********************** ダメージ状態 **************************E
					break;
			}
			break;
		
			// ***********************     ドム     ************************** E
		default:

			break;
	}
//	EX enum { SLIME, RAFRY, USA, SUSI, PLAZUMA, UNI, TORI, KAERU, KINOKO, BAT, SASORI, HAE } EnemyName;

	// ******************** 選択キャラによる処理の分岐 ******************** E
	if ( (EnemyNowstatus[EnemyNo].x >> 16) >= ( 512 - 48 ) )	EnemyNowstatus[EnemyNo].x = ( 512 - 48 ) << 16;
	if ( (EnemyNowstatus[EnemyNo].y >> 16) >= ( 512 - 48 ) )	EnemyNowstatus[EnemyNo].y = ( 512 - 48 ) << 16;

	if ( (EnemyNowstatus[EnemyNo].x >> 16) <= ( 0 + 48 ) )		EnemyNowstatus[EnemyNo].x = ( 0 + 48 ) << 16;
	if ( (EnemyNowstatus[EnemyNo].y >> 16) <= ( 0 + 48 ) )		EnemyNowstatus[EnemyNo].y = ( 0 + 48 ) << 16;

	return;
}

//**************************************************************************** S
//	  関数名		:	敵の魔法処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	Magic.cの敵バージョン
//	 最終更新日		:	2003/01/09 (火)
//**************************************************************************** E

void EnemyMagicAttack (void)
{
	s32 enemymg_local_x;
	s32 enemymg_local_y;
	
		// ************** 魔法が発動中の時のみ処理 ************** S
		if( EnemyMagic[EnemyNo].status ){
			
			OamBuf[22].Bit32 = OAM_OBJ_ON;		// スプライト表示の準備
			OamBuf[22].Oam.Pltt = 10;
			OamBuf[22].Oam.CharNo = 128;

			// ************** 魔法状態が一段階目時のみ処理 ************** S
			if( EnemyMagic[EnemyNo].status == 1){

				// ************** 魔法フラグがOFF時のみ処理を通る ************** S
				if( !EnemyMagic[EnemyNo].flg ){
					// プレイヤーの向きから魔法の初期位置を設定
					if ( enemymg_offset_x > 0 ){		// 方向
						EnemyMagic[EnemyNo].x = EnemyNowstatus[EnemyNo].x + ( MG_RIGHT_OFFSET_X << 16 );
					}
					else if( enemymg_offset_x < 0 ){
						EnemyMagic[EnemyNo].x = EnemyNowstatus[EnemyNo].x - ( MG_LEFT_OFFSET_X << 16 );
					}
					else{
						EnemyMagic[EnemyNo].x = EnemyNowstatus[EnemyNo].x;
					}
					
					if ( enemymg_offset_y < 0 ){		// 方向
						EnemyMagic[EnemyNo].y = EnemyNowstatus[EnemyNo].y - ( MG_UP_OFFSET_Y << 16 );
					}
					else if ( enemymg_offset_y > 0 ){
						EnemyMagic[EnemyNo].y = EnemyNowstatus[EnemyNo].y + ( MG_DOWN_OFFSET_Y << 16 );
					}
					else{
						EnemyMagic[EnemyNo].y = EnemyNowstatus[EnemyNo].y;
					}
					
					EnemyMagic[EnemyNo].flg = ON;								// 魔法フラグON
					EnemyMagic[EnemyNo].turn = PlayerNowstatus[PlayerNo].turn;		// プレイヤーの向きを格納
				}				//PlayerNowStartus
				// ************** 魔法フラグがOFF時のみ処理を通る ************** E

				// 魔法の移動

				EnemyMagic[EnemyNo].x += (enemymg_offset_x << 16);
				EnemyMagic[EnemyNo].y += (enemymg_offset_y << 16);
				
				enemymg_local_x = EnemyMagic[EnemyNo].x - Hoffset;
				enemymg_local_y = EnemyMagic[EnemyNo].y - Voffset;
				

				// スプライトの表示 正常終了後次の段階へ
				if( Action( 22, OBJ_MODE0_VRAM+1024*4, MG_SHOT_S, (enemymg_local_x >> 16), (enemymg_local_y >> 16), &EnemyMagic[EnemyNo].cnt, &EnemyMagic[EnemyNo].anime) ){
					EnemyMagic[EnemyNo].status = 2;
				}
//				NowAnime2 = (ANIME*)MG_SHOT_S;			// 攻撃力を格納する
			}
			// ************** 魔法状態が一段階目時のみ処理 ************** E

			else {
				enemymg_local_x = EnemyMagic[EnemyNo].x - Hoffset;
				enemymg_local_y = EnemyMagic[EnemyNo].y - Voffset;

				if( Action( 22, OBJ_MODE0_VRAM+1024*4, MG_SHOT_B, (enemymg_local_x >> 16), (enemymg_local_y >> 16), &EnemyMagic[EnemyNo].cnt, &EnemyMagic[EnemyNo].anime) ){
					EnemyMagic[EnemyNo].status = EnemyMagic[EnemyNo].flg = OFF;		// 魔法状態を初期化
					EnemyMagic[EnemyNo].x = EnemyMagic[EnemyNo].y = 255;			// 画面外へスプライト表示を退避
					enemymg_local_x = enemymg_local_y = 0;
				}
//				NowAnime2 = (ANIME*)MG_SHOT_B;			// 攻撃力を格納する

			}
			
	}
	// ************** 魔法が発動中の時のみ処理 ************** E
	return;
	
}
