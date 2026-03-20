#include	"all.h"

void Bbriefing(void);

// 基本フレーム 3つとも共通のパレット
extern const u16	char_select_frame_Palette[16];
extern const u8		char_select_frame_Character[8*8/2*112];
extern const u16	char_select_frame_Map[32*32];
extern const u8		stage_select_frame_Character[8*8/2*104];
extern const u16	stage_select_frame_Map[32*32];
extern const u8		winner_frame_Character[8*8/2*96];
extern const u16	winner_frame_Map[32*32];

// ステージセレクトに使用するアイコン 3つとも共通のパレット
extern const u16	woods_icon_Palette[16];
extern const u8		woods_icon_Character[8*8/2*135];
extern const u16	woods_icon_Map[32*32];
extern const u8		ruins_icon_Character[8*8/2*113];
extern const u16	ruins_icon_Map[32*32];
extern const u8		snow_icon_Character[8*8/2*118];
extern const u16	snow_icon_Map[32*32];

// キャラクターセレクトに使用するアイコン パレットはゲーム中と同じ
//extern const u8		select_speed_Char[];
extern const u8		select_magic_Char[];
extern const u8		select_petit_Char[];
extern const u8		select_beast_Char[];
extern const u8		select_power_Char[];
extern const u8		select_beast_Char[];

// 結果発表画面で勝利プレイヤーを宣言するときに使用 パレットは共通
extern const u8		player1_logo_Char[];
extern const u8		player2_logo_Char[];
extern const u8		player3_logo_Char[];
extern const u8		player4_logo_Char[];

EX s8 select;
