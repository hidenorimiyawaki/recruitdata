/************************************************************
*						ITEM.H								*
*															*
*	このファイルでは、アイテムクラスの定義をします。		*
*															*
*				作成日：2003/11/27							*
*			最終更新日：2003/11/27							*
*															*
************************************************************/
#define SEGMENT_FILENAME_2	IDR_MIDI1			// 再生するMIDI名


class BGM{
	public:
		//----------オーディオ変数

		// DirectMusicの変数
		IDirectMusicPerformance8* g_pPerformance;	// パフォーマンス
		IDirectMusicLoader8* g_pLoader;				// ローダー
		IDirectMusicAudioPath8* g_pDefAudioPath;		// デフォルト・オーディオパス

		// DirectMusicのセグメント
		IDirectMusicSegment8* g_pSegment2;			// セグメント
		IDirectMusicSegmentState8* g_pSegmentState2;	// セグメントの状態
		MUSIC_TIME g_SegLength2;						// セグメントの長さ

	public:
		BGM();
		~BGM();
		Initialize(HWND);
		Play();
		Stop();
		ReleaseDMSegment();
};

BGM::BGM(){
	g_pPerformance = NULL;
	g_pLoader = NULL;
	g_pDefAudioPath = NULL;

	g_pSegment2 = NULL;
	g_pSegmentState2 = NULL;

	g_SegLength2 = 0;						// セグメントの長さ

}

BGM::Initialize(HWND hWnd){
	HRESULT hr;

	hr = CoInitialize(NULL);

	// *****************************************
	// パフォーマンスの作成
	hr = CoCreateInstance(CLSID_DirectMusicPerformance, NULL,
						  CLSCTX_INPROC, IID_IDirectMusicPerformance8,
						  (void**)&g_pPerformance );
	if (FAILED(hr))
	{
		return false;
	}

	// パフォーマンスの初期化
	hr = g_pPerformance->InitAudio( 
		NULL,				  // IDirectMusicインターフェイスは不要
		NULL,				  // IDirectSoundインターフェイスは不要
		hWnd,			   // ウィンドウのハンドル
		DMUS_APATH_SHARED_STEREOPLUSREVERB,  // デフォルトのオーディオパス・タイプ
		64,					// パフォーマンス・チャンネルの数
		DMUS_AUDIOF_ALL,	   // シンセサイザの機能
		NULL);				 // オーディオ・パラメータにはデフォルトを使用
	if (FAILED(hr))
	{
		return false;
	}

	// デフォルト・オーディオパスの取得
	hr = g_pPerformance->GetDefaultAudioPath(&g_pDefAudioPath);
	if (FAILED(hr))
	{
		return false;
	}

	// パフォーマンスで自動ダウンロードを有効にする
//	BOOL fAuto = TRUE;
//	hr = g_pPerformance->SetGlobalParam(GUID_PerfAutoDownload, &fAuto, sizeof(BOOL));
//	if (FAILED(hr))
//	{
//		DXTRACE_ERR("パフォーマンスで自動ダウンロード設定に失敗", hr);
//		return false;
//	}

	// *****************************************
	// ローダーの作成
	hr = CoCreateInstance(CLSID_DirectMusicLoader, NULL, 
						  CLSCTX_INPROC, IID_IDirectMusicLoader8,
						  (void**)&g_pLoader);
	if (FAILED(hr))
	{
		return false;
	}

	// ローダーの初期化（検索パスをカレント・ディレクトリに設定）
	CHAR strPath[MAX_PATH];
	DWORD i = GetCurrentDirectory(MAX_PATH, strPath);
	if (i==0 || MAX_PATH<i)
	{
		return false;
	}

	// マルチ・バイト文字をUNICODEに変換
	WCHAR wstrSearchPath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, strPath, -1, wstrSearchPath, MAX_PATH);

	// ローダーに検索パスを設定
	hr = g_pLoader->SetSearchDirectory(GUID_DirectMusicAllTypes,wstrSearchPath, FALSE);

	// *****************************************
	// セグメント２作成（リソースからMIDIデータをロード）
	// リソースを検索＆ロード
//	HRSRC hFound = FindResource(NULL, MAKEINTRESOURCE(IDC_MIDI1), RESOURCETYPE_MIDI);
	HRSRC hFound = FindResource(NULL, MAKEINTRESOURCE(SEGMENT_FILENAME_2), RESOURCETYPE_MIDI);
	HGLOBAL hRes = LoadResource(NULL, hFound);

	// DMUS_OBJECTDESC構造体を定義
	DMUS_OBJECTDESC ObjDesc;
	ZeroMemory(&ObjDesc, sizeof(DMUS_OBJECTDESC));
	ObjDesc.dwSize	  = sizeof(DMUS_OBJECTDESC);
	ObjDesc.guidClass   = CLSID_DirectMusicSegment;
	ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_MEMORY;
	ObjDesc.pbMemData   = (BYTE*)LockResource(hRes);
	ObjDesc.llMemLength = SizeofResource(NULL, hFound);

	// メモリ（リソース）からセグメントをロード
	hr = g_pLoader->GetObject(&ObjDesc, IID_IDirectMusicSegment8,
							  (void**)&g_pSegment2);

	// スタンダードMIDIファイルの場合は、パラメータを設定する
	hr = g_pSegment2->SetParam(GUID_StandardMIDIFile,
								  0xFFFFFFFF, 0, 0, NULL);
	// セグメント２の長さを取得
	hr = g_pSegment2->GetLength(&g_SegLength2);

	// *****************************************
	// バンドのダウンロード（自動）
//	g_pSegment1->SetParam(GUID_Enable_Auto_Download, 0xFFFFFFFF, 0, 0, NULL);
//	if (FAILED(hr))
//	{
//		DXTRACE_ERR("セグメント１の自動ダウンロードの設定に失敗", hr);
//		return false;
//	}
//	g_pSegment2->SetParam(GUID_Enable_Auto_Download, 0xFFFFFFFF, 0, 0, NULL);
//	if (FAILED(hr))
//	{
//		DXTRACE_ERR("セグメント２の自動ダウンロードの設定に失敗", hr);
//		return false;
//	}

	// *****************************************
	// バンドのダウンロード（手動）
	hr = g_pSegment2->Download( g_pPerformance );

	return true;

}
BGM::ReleaseDMSegment(){

	g_pPerformance->Stop(NULL, NULL, 0, 0);		// サウンドの再生を停止
	g_pPerformance->CloseDown();				// パフォーマンスの終了

	SAFE_RELEASE(g_pSegment2);					// セグメントの解放
	SAFE_RELEASE(g_pLoader);					// ローダーの解放
	SAFE_RELEASE(g_pPerformance);				// パフォーマンスの解放
	CoUninitialize();

}
BGM::Play(){
	g_pSegment2->SetParam(GUID_StandardMIDIFile, 0xffffffff, 0, 0, NULL);
	g_pPerformance->PlaySegmentEx(g_pSegment2, NULL, NULL, 0, 0, NULL, NULL, NULL);
}
BGM::Stop(){
	g_pPerformance->StopEx(g_pSegment2, 0, 0);
	g_pPerformance->Stop(NULL, NULL, 0, 0);
}
BGM::~BGM(){
}