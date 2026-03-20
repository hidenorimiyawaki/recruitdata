/****************************************************************
*						music.h									*
*																*
*	このファイルでは、ゲーム中に使用する効果音・BGMに使用する	*
*	クラスの定義をします。										*
*																*
****************************************************************/

class MUSIC
{
	//----- 変数
	public:
		// DirectMusicの変数
		IDirectMusicPerformance8*		pPerformance;		// パフォーマンス
		IDirectMusicLoader8*			pLoader;			// ローダー
		IDirectMusicAudioPath8*			pDefAudioPath;		// デフォルト・オーディオパス

		// DirectMusicのセグメント
		IDirectMusicSegment8*			pSegment;			// セグメント
		IDirectMusicSegmentState8*		pSegmentState;		// セグメントの状態
		MUSIC_TIME						SegLength;			// セグメントの長さ
		int								loop_flg;			// ループの有無

	//----- 関数
	public:
		MUSIC();											// コンストラクタ
		Initialize(WCHAR*);									// 初期化関数(音楽ファイルのアドレスを引数とする)
		Play();												// 演奏
		Stop();												// 演奏停止
		ReleaseDMSegment();									// このクラスの音楽変数のリリース
};
