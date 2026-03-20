#include "main.h"
MUSIC::MUSIC(){
	pPerformance = NULL;
	pLoader = NULL;
	pDefAudioPath = NULL;

	pSegment = NULL;
	pSegmentState = NULL;

	SegLength = 0;						// セグメントの長さ

	loop_flg = 0;
}

MUSIC::Initialize(WCHAR* SoundFileName){
	CHAR		strPath[MAX_PATH];
	WCHAR		wstrSearchPath[MAX_PATH];

	CoInitialize(NULL);				// ＣＯＭの初期化

	// パフォーマンスの作成と初期化
	CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC, IID_IDirectMusicPerformance8, (void**)&pPerformance );
	// ローダーの作成と初期化
	CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, IID_IDirectMusicLoader8, (void**)&pLoader);
	// シンセサイザの初期化
	pPerformance->InitAudio( 
		NULL,									// IDirectMusic インターフェイスは不要
		NULL,									// IDirectSound インターフェイスは不要
		NULL,									// ウィンドウハンドル
		DMUS_APATH_DYNAMIC_STEREO,				// オーディオパスタイプ
		64,										// パフォーマンスチャンネル数
		DMUS_AUDIOF_ALL,						// シンセサイザの機能
		NULL);									// オーディオパラメータにはデフォルトを使用

	// ファイルのロード
	// カレントディレクトリを取得
	GetCurrentDirectory(MAX_PATH, strPath);
	MultiByteToWideChar( CP_ACP, 0, strPath, -1, wstrSearchPath, MAX_PATH );		// Unicode に変換
	// 検索ディレクトリを設定
	pLoader->SetSearchDirectory(
		GUID_DirectMusicAllTypes,			// 検索ファイルの種類
		wstrSearchPath,						// 検索場所
		FALSE);								// オブジェクトデータを消去しない
	// ファイルからセグメントをロード
		if(FAILED(pLoader->LoadObjectFromFile(
			CLSID_DirectMusicSegment,		// クラス識別子
			IID_IDirectMusicSegment8,		// 目的のインターフェイスＩＤ
			&SoundFileName[0],			// ファイル名
			(LPVOID *)&pSegment))) {	// インターフェイスを受け取るポインタ
			MessageBox(NULL, "ファイルの読み込みに失敗しました", "Error", MB_OK | MB_ICONSTOP);
			return false;
		}
		pSegment->Download(pPerformance);		// バンドのダウンロード
		if(loop_flg == 1){
			// ループの設定
			pSegment->SetLoopPoints(0, 0);
			pSegment->SetRepeats(DMUS_SEG_REPEAT_INFINITE);
		}
	return true;
}
MUSIC::ReleaseDMSegment(){

	pPerformance->Stop(NULL, NULL, 0, 0);		// サウンドの再生を停止
	pPerformance->CloseDown();				// パフォーマンスの終了

	SAFE_RELEASE(pSegment);					// セグメントの解放
	SAFE_RELEASE(pLoader);					// ローダーの解放
	SAFE_RELEASE(pPerformance);				// パフォーマンスの解放
	CoUninitialize();

}
MUSIC::Play(){
	pPerformance->PlaySegmentEx(pSegment, NULL, NULL, 0, 0, NULL, NULL, NULL);
}
MUSIC::Stop(){
	pPerformance->StopEx(pSegment, 0, 0);
	pPerformance->Stop(NULL, NULL, 0, 0);
}
