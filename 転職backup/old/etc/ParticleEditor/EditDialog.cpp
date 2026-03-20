// EditDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "test.h"
#include "EditDialog.h"
#include ".\editdialog.h"


// CEditDialog ダイアログ

IMPLEMENT_DYNAMIC(CEditDialog, CDialog)
CEditDialog::CEditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDialog::IDD, pParent)
	, m_Edit_Num(0)
	, m_Edit_Scale(0)
	, m_Edit_Time(0)
	, m_Edit_Pos_X(0)
	, m_Edit_Pos_Y(0)
	, m_Edit_Pos_Z(0)
	, m_Edit_Dir_X(0)
	, m_Edit_Dir_Y(0)
	, m_Edit_Dir_Z(0)
	, m_Edit_Gravity(0)
	, m_Edit_Range_X(0)
	, m_Edit_Range_Y(0)
	, m_Edit_Range_Z(0)
	, m_Edit_Speed(0)
{
}

CEditDialog::~CEditDialog()
{
}

void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_NUM, m_Edit_Slider_Num);
	DDX_Control(pDX, IDC_SLIDER_SIZE, m_Edit_Slider_Size);
	DDX_Control(pDX, IDC_SLIDER_TIME, m_Edit_Slider_Time);
	DDX_Control(pDX, IDC_SLIDER_POS_X, m_Edit_Slider_Pos_X);
	DDX_Control(pDX, IDC_SLIDER_POS_Y, m_Edit_Slider_Pos_Y);
	DDX_Control(pDX, IDC_SLIDER_POS_Z, m_Edit_Slider_Pos_Z);
	DDX_Control(pDX, IDC_SLIDER_DIR_X, m_Edit_Slider_Dir_X);
	DDX_Control(pDX, IDC_SLIDER_DIR_Y, m_Edit_Slider_Dir_Y);
	DDX_Control(pDX, IDC_SLIDER_DIR_Z, m_Edit_Slider_Dir_Z);
	DDX_Control(pDX, IDC_SLIDER_GRAVITY, m_Edit_Slider_Gravity);
	DDX_Control(pDX, IDC_SLIDER_RANGE_X, m_Edit_Slider_Range_X);
	DDX_Control(pDX, IDC_SLIDER_RANGE_Y, m_Edit_Slider_Range_Y);
	DDX_Control(pDX, IDC_SLIDER_RANGE_Z, m_Edit_Slider_Range_Z);
	DDX_Control(pDX, IDC_CHECK_SIDE_X, m_Check_Side_X);
	DDX_Control(pDX, IDC_CHECK_SIDE_Y, m_Check_Side_Y);
	DDX_Control(pDX, IDC_CHECK_SIDE_Z, m_Check_Side_Z);
	DDX_Control(pDX, IDC_CHECK_ADD_ALPHA, m_Check_Add_Alpha);
	DDX_Control(pDX, IDC_CHECK_ALPHA, m_Check_Alpha);
	DDX_Control(pDX, IDC_CHECK_SIZE, m_Check_Size);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_Edit_Slider_Speed);
	DDX_Text(pDX, IDC_EDIT_NUM, m_Edit_Num);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_Edit_Scale);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Edit_Time);
	DDX_Text(pDX, IDC_EDIT_POS_X, m_Edit_Pos_X);
	DDX_Text(pDX, IDC_EDIT_POS_Y, m_Edit_Pos_Y);
	DDX_Text(pDX, IDC_EDIT_POS_Z, m_Edit_Pos_Z);
	DDX_Text(pDX, IDC_EDIT_DIR_X, m_Edit_Dir_X);
	DDX_Text(pDX, IDC_EDIT_DIR_Y, m_Edit_Dir_Y);
	DDX_Text(pDX, IDC_EDIT_DIR_Z, m_Edit_Dir_Z);
	DDX_Text(pDX, IDC_EDIT_GRAVITY, m_Edit_Gravity);
	DDX_Text(pDX, IDC_EDIT_RANGE_X, m_Edit_Range_X);
	DDX_Text(pDX, IDC_EDIT_RANGE_Y, m_Edit_Range_Y);
	DDX_Text(pDX, IDC_EDIT_RANGE_Z, m_Edit_Range_Z);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_Edit_Speed);
	DDX_Control(pDX, IDC_CHECK_TIME, m_Check_Time);
	DDX_Control(pDX, IDC_STATIC_DIR_X, m_Static_Dir_X);
	DDX_Control(pDX, IDC_STATIC_DIR_Y, m_Static_Dir_Y);
	DDX_Control(pDX, IDC_STATIC_DIR_Z, m_Static_Dir_Z);
	DDX_Control(pDX, IDC_STATIC_SPEED, m_Static_Speed);
	DDX_Control(pDX, IDC_STATIC_GRAVITY, m_Static_Gravity);
	DDX_Control(pDX, IDC_CHECK_ALPHA_TIME, m_Check_Time_Alpha);
}


BEGIN_MESSAGE_MAP(CEditDialog, CDialog)
	ON_WM_HSCROLL()
	ON_WM_KILLFOCUS()
	ON_BN_CLICKED(IDC_RADIO_POS, OnBnClickedRadioPos)
	ON_BN_CLICKED(IDC_RADIO_ROT, OnBnClickedRadioRot)
	ON_BN_CLICKED(IDC_RADIO_SCALE, OnBnClickedRadioScale)
	ON_BN_CLICKED(IDC_CHECK_SIDE_X, OnBnClickedCheckSideX)
	ON_BN_CLICKED(IDC_CHECK_SIDE_Y, OnBnClickedCheckSideY)
	ON_BN_CLICKED(IDC_CHECK_SIDE_Z, OnBnClickedCheckSideZ)
	ON_BN_CLICKED(IDC_CHECK_TIME, OnBnClickedCheckTime)
	ON_BN_CLICKED(IDC_CHECK_SIZE, OnBnClickedCheckSize)
END_MESSAGE_MAP()


// CEditDialog メッセージ ハンドラ

//-------------------------------------------------------------------
// func   : void OnInitDialog()
// param  : 無し
// print  : ダイアログ生成時に自動で呼ばれる
//-------------------------------------------------------------------
BOOL CEditDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// アプリケーションオブジェクトのポインタを取得
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// 各種初期化

	//---------------- パーティクルカテゴリ初期化 ----------------------------------------
		// パーティクル数設定スライダー初期化
		m_Edit_Slider_Num.SetRange(1, PARTICLE_MAX, true);
		m_Edit_Slider_Num.SetPageSize(1);	m_Edit_Slider_Num.SetLineSize(1);	m_Edit_Slider_Num.SetPos(0);
		m_Edit_Slider_Num.SetPos(100);
		// パーティクル数設定エディットボックス初期化
		m_Edit_Num = m_Edit_Slider_Num.GetPos();


		// 継続時間設定スライダー初期化
		m_Edit_Slider_Time.SetRange(1, 1200, true);
		m_Edit_Slider_Time.SetPageSize(1);	m_Edit_Slider_Time.SetLineSize(1);	m_Edit_Slider_Time.SetPos(0);
		m_Edit_Slider_Time.SetPos(60);
		// 継続時間設定エディットボックス初期化
		m_Edit_Time = m_Edit_Slider_Time.GetPos();



	//---------------- 座標カテゴリ初期化 ----------------------------------------
		// X座標設定スライダー初期化
		m_Edit_Slider_Pos_X.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Pos_X.SetPageSize(1);	m_Edit_Slider_Pos_X.SetLineSize(1);	m_Edit_Slider_Pos_X.SetPos(0);
		m_Edit_Slider_Pos_X.SetPos(0);
		// X座標設定エディットボックス初期化
		m_Edit_Pos_X = m_Edit_Slider_Pos_X.GetPos()*0.01f;


		// Y座標設定スライダー初期化
		m_Edit_Slider_Pos_Y.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Pos_Y.SetPageSize(1);	m_Edit_Slider_Pos_Y.SetLineSize(1);	m_Edit_Slider_Pos_Y.SetPos(0);
		m_Edit_Slider_Pos_Y.SetPos(0);
		// Y座標設定エディットボックス初期化
		m_Edit_Pos_Y = m_Edit_Slider_Pos_Y.GetPos()*0.01f;


		// Z座標設定スライダー初期化
		m_Edit_Slider_Pos_Z.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Pos_Z.SetPageSize(1);	m_Edit_Slider_Pos_Z.SetLineSize(1);	m_Edit_Slider_Pos_Z.SetPos(0);
		m_Edit_Slider_Pos_Z.SetPos(0);
		// Z座標設定エディットボックス初期化
		m_Edit_Pos_Z = m_Edit_Slider_Pos_Z.GetPos()*0.01f;


		// パーティクルX軸発生範囲パラメータ設定スライダー初期化
		m_Edit_Slider_Range_X.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Range_X.SetPageSize(1);	m_Edit_Slider_Range_X.SetLineSize(1);	m_Edit_Slider_Range_X.SetPos(0);
		m_Edit_Slider_Range_X.SetPos(0);
		// パーティクルX軸発生範囲設定エディットボックス初期化
		m_Edit_Range_X = m_Edit_Slider_Range_X.GetPos()*0.01f;


		// パーティクルY軸発生範囲パラメータ設定スライダー初期化
		m_Edit_Slider_Range_Y.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Range_Y.SetPageSize(1);	m_Edit_Slider_Range_Y.SetLineSize(1);	m_Edit_Slider_Range_Y.SetPos(0);
		m_Edit_Slider_Range_Y.SetPos(0);
		// パーティクルY軸発生範囲設定エディットボックス初期化
		m_Edit_Range_Y = m_Edit_Slider_Range_Y.GetPos()*0.01f;


		// パーティクルZ軸発生範囲パラメータ設定スライダー初期化
		m_Edit_Slider_Range_Z.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Range_Z.SetPageSize(1);	m_Edit_Slider_Range_Z.SetLineSize(1);	m_Edit_Slider_Range_Z.SetPos(0);
		m_Edit_Slider_Range_Z.SetPos(0);
		// パーティクルZ軸発生範囲設定エディットボックス初期化
		m_Edit_Range_Z = m_Edit_Slider_Range_Z.GetPos()*0.01f;



	//---------------- パラメータカテゴリ初期化 ----------------------------------------
		// 汎用Xパラメータ設定スライダー初期化
		m_Edit_Slider_Dir_X.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Dir_X.SetPageSize(1);	m_Edit_Slider_Dir_X.SetLineSize(1);	m_Edit_Slider_Dir_X.SetPos(0);
		m_Edit_Slider_Dir_X.SetPos(0);
		// 汎用Xパラメータ設定エディットボックス初期化
		m_Edit_Dir_X = m_Edit_Slider_Dir_X.GetPos()*0.01f;
		// 汎用Xパラメータ用フラグ初期化
		m_Check_Side_X.SetCheck((int)pApp->posflg.x);

		// 汎用Yパラメータ設定スライダー初期化
		m_Edit_Slider_Dir_Y.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Dir_Y.SetPageSize(1);	m_Edit_Slider_Dir_Y.SetLineSize(1);	m_Edit_Slider_Dir_Y.SetPos(0);
		m_Edit_Slider_Dir_Y.SetPos(0);
		// 汎用Yパラメータ設定エディットボックス初期化
		m_Edit_Dir_Y = m_Edit_Slider_Dir_Y.GetPos()*0.01f;
		// 汎用Yパラメータ用フラグ初期化
		m_Check_Side_Y.SetCheck((int)pApp->posflg.y);


		// 汎用Zパラメータ設定スライダー初期化
		m_Edit_Slider_Dir_Z.SetRange(SCROLL_MIN, SCROLL_MAX, true);
		m_Edit_Slider_Dir_Z.SetPageSize(1);	m_Edit_Slider_Dir_Z.SetLineSize(1);	m_Edit_Slider_Dir_Z.SetPos(0);
		m_Edit_Slider_Dir_Z.SetPos(0);
		// 汎用Zパラメータ設定エディットボックス初期化
		m_Edit_Dir_Z = m_Edit_Slider_Dir_Z.GetPos()*0.01f;
		// 汎用Zパラメータ用フラグ初期化
		m_Check_Side_Z.SetCheck((int)pApp->posflg.z);


		// 汎用スピードパラメータ設定スライダー初期化
		m_Edit_Slider_Speed.SetRange(1, 5000, true);
		m_Edit_Slider_Speed.SetPageSize(1);	m_Edit_Slider_Speed.SetLineSize(1);	m_Edit_Slider_Speed.SetPos(0);
		m_Edit_Slider_Speed.SetPos(100);
		// 汎用スピード設定パラメータ設定エディットボックス初期化
		m_Edit_Speed = m_Edit_Slider_Speed.GetPos()*0.01f;


		// 重力パラメータ設定スライダー初期化
		m_Edit_Slider_Gravity.SetRange(-10000, 10000, true);
		m_Edit_Slider_Gravity.SetPageSize(1);	m_Edit_Slider_Gravity.SetLineSize(1);	m_Edit_Slider_Gravity.SetPos(0);
		m_Edit_Slider_Gravity.SetPos(0);
		// 重力パラメータ設定エディットボックス初期化
		m_Edit_Gravity = m_Edit_Slider_Gravity.GetPos()*0.01f;



	//---------------- テクスチャカテゴリ初期化 ----------------------------------------
		// テクスチャサイズ設定スライダー初期化
		m_Edit_Slider_Size.SetRange(1, (PARTICLE_MAX_SCALE)*100, true);
		m_Edit_Slider_Size.SetPageSize(1);	m_Edit_Slider_Size.SetLineSize(1);	m_Edit_Slider_Size.SetPos(0);
		m_Edit_Slider_Size.SetPos(100);
		// テクスチャサイズ表示エディットボックス初期化
		m_Edit_Scale = m_Edit_Slider_Size.GetPos()*0.01f;



	//---------------- その他設定 ----------------------------------------------------
		// アルファブレンディング設定初期化
		m_Check_Alpha.SetCheck(true);

		// 加算半透明設定初期化
		m_Check_Add_Alpha.SetCheck(true);

		// ラジオボタンを初期化
		CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
		pBtn->SetCheck(true);



	UpdateData(false);		// 反映	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CEditDialog::PreTranslateMessage(MSG* pMsg)
{
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	CButton* pBtn;
	POSITION3 pos;

	// キーボードメッセージを処理
	switch(pMsg->message) {
	case WM_KEYDOWN:
		switch(pMsg->wParam) {
		case VK_RETURN:	
			// 各エディットボックスへのパラメータ入力を反映させる

			UpdateData(true);		// 現在の情報をコントロールに反映

			//---------------- パーティクルカテゴリ --------------------------
				// パーティクル数の入力内容を反映
				if(m_Edit_Num < 1) m_Edit_Num = 1;
				else if(m_Edit_Num > PARTICLE_MAX) m_Edit_Num = PARTICLE_MAX;
				m_Edit_Slider_Num.SetPos(m_Edit_Num);
		
				// 継続時間の入力内容を反映
				if(m_Edit_Time < 1) m_Edit_Time = 1;
				else if(m_Edit_Time > 1200) m_Edit_Time = 1200;
				m_Edit_Slider_Time.SetPos(m_Edit_Time);


			//---------------- 座標カテゴリ --------------------------
				// X座標の入力内容を反映
				if(m_Edit_Pos_X < SCROLL_MIN*0.01f) m_Edit_Pos_X = SCROLL_MIN*0.01f;
				else if(m_Edit_Pos_X > SCROLL_MAX*0.01f) m_Edit_Pos_X = SCROLL_MAX*0.01f;
				m_Edit_Slider_Pos_X.SetPos((int)(m_Edit_Pos_X * 100.0f));

				// Y座標の入力内容を反映
				if(m_Edit_Pos_Y < SCROLL_MIN*0.01f) m_Edit_Pos_Y = SCROLL_MIN*0.01f;
				else if(m_Edit_Pos_Y > SCROLL_MAX*0.01f) m_Edit_Pos_Y = SCROLL_MAX*0.01f;
				m_Edit_Slider_Pos_Y.SetPos((int)(m_Edit_Pos_Y * 100.0f));

				// Z座標の入力内容を反映
				if(m_Edit_Pos_Z < SCROLL_MIN*0.01f) m_Edit_Pos_Z = SCROLL_MIN*0.01f;
				else if(m_Edit_Pos_Z > SCROLL_MAX*0.01f) m_Edit_Pos_Z = SCROLL_MAX*0.01f;
				m_Edit_Slider_Pos_Z.SetPos((int)(m_Edit_Pos_Z * 100.0f));

				// X座標の発生範囲の入力内容を反映
				if(m_Edit_Range_X < SCROLL_MIN*0.01f) m_Edit_Range_X = SCROLL_MIN*0.01f;
				else if(m_Edit_Range_X > SCROLL_MAX*0.01f) m_Edit_Range_X = SCROLL_MAX*0.01f;
				m_Edit_Slider_Range_X.SetPos((int)(m_Edit_Range_X * 100.0f));

				// Y座標の発生範囲の入力内容を反映
				if(m_Edit_Range_Y < SCROLL_MIN*0.01f) m_Edit_Range_Y = SCROLL_MIN*0.01f;
				else if(m_Edit_Range_Y > SCROLL_MAX*0.01f) m_Edit_Range_Y = SCROLL_MAX*0.01f;
				m_Edit_Slider_Range_Y.SetPos((int)(m_Edit_Range_Y * 100.0f));

				// Z座標の発生範囲の入力内容を反映
				if(m_Edit_Range_Z < SCROLL_MIN*0.01f) m_Edit_Range_Z = SCROLL_MIN*0.01f;
				else if(m_Edit_Range_Z > SCROLL_MAX*0.01f) m_Edit_Range_Z = SCROLL_MAX*0.01f;
				m_Edit_Slider_Range_Z.SetPos((int)(m_Edit_Range_Z * 100.0f));



			//---------------- パラメータカテゴリ --------------------------
				// ラジオボタンの設定が”移動値”の状態のとき
				pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
				if(pBtn->GetCheck()){
					// X座標パラメータの入力内容を反映
					if(m_Edit_Dir_X < SCROLL_MIN*0.01f) {
						m_Edit_Dir_X = SCROLL_MIN*0.01f;
						pApp->pos.x = SCROLL_MIN;
					}
					else if(m_Edit_Dir_X > SCROLL_MAX*0.01f){
						m_Edit_Dir_X = SCROLL_MAX*0.01f;
						pApp->pos.x = SCROLL_MAX;
					}
					else {
						pApp->pos.x = m_Edit_Dir_X*100;
					}
					m_Edit_Slider_Dir_X.SetPos((int)(m_Edit_Dir_X * 100.0f));

					// Y座標パラメータの入力内容を反映
					if(m_Edit_Dir_Y < SCROLL_MIN*0.01f) {
						m_Edit_Dir_Y = SCROLL_MIN*0.01f;
						pApp->pos.y = SCROLL_MIN;
					}
					else if(m_Edit_Dir_Y > SCROLL_MAX*0.01f){
						m_Edit_Dir_Y = SCROLL_MAX*0.01f;
						pApp->pos.y = SCROLL_MAX;
					}
					else {
						pApp->pos.y = m_Edit_Dir_Y*100;
					}
					m_Edit_Slider_Dir_Y.SetPos((int)(m_Edit_Dir_Y * 100.0f));

					// Z座標パラメータの入力内容を反映
					if(m_Edit_Dir_Z < SCROLL_MIN*0.01f) {
						m_Edit_Dir_Z = SCROLL_MIN*0.01f;
						pApp->pos.z = SCROLL_MIN;
					}
					else if(m_Edit_Dir_Z > SCROLL_MAX*0.01f) {
						m_Edit_Dir_Z = SCROLL_MAX*0.01f;
						pApp->pos.z = SCROLL_MAX;
					}
					else {
						pApp->pos.z = m_Edit_Dir_Z*100;
					}
					m_Edit_Slider_Dir_Z.SetPos((int)(m_Edit_Dir_Z * 100.0f));

					// スピードパラメータの入力内容を反映
					if(m_Edit_Speed < 1*0.01f) {
						m_Edit_Speed = 1*0.01f;
						pApp->pos.w = 1;
					}
					else if(m_Edit_Speed > 5000*0.01f) {
						m_Edit_Speed = 5000*0.01f;
						pApp->pos.w = 5000;
					}
					else {
						pApp->pos.w = m_Edit_Speed*100;
					}
					m_Edit_Slider_Speed.SetPos((int)(m_Edit_Speed * 100.0f));

					// 重力の入力内容を反映
					if(m_Edit_Gravity < -10000*0.01f) m_Edit_Gravity = -10000*0.01f;
					else if(m_Edit_Gravity > 10000*0.01f) m_Edit_Gravity = 10000*0.01f;
					pApp->gravity = m_Edit_Gravity;
					m_Edit_Slider_Gravity.SetPos((int)(m_Edit_Gravity * 100.0f));


				}

				// ラジオボタンの設定が”回転値”の状態のとき
				pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
				if(pBtn->GetCheck()){
					// X座標パラメータの入力内容を反映
					if(m_Edit_Dir_X <= 0) {
						m_Edit_Dir_X = 0;
						pApp->rot.x = 0;
					}
					else if(m_Edit_Dir_X >= 360){
						m_Edit_Dir_X = 360;
						pApp->rot.x = 360;
					}
					else {
						pApp->rot.x = m_Edit_Dir_X;
					}
					m_Edit_Slider_Dir_X.SetPos((int)m_Edit_Dir_X);

					// Y座標パラメータの入力内容を反映
					if(m_Edit_Dir_Y <= 0) {
						m_Edit_Dir_Y = 0;
						pApp->rot.y = 0;
					}
					else if(m_Edit_Dir_Y >= 360) {
						m_Edit_Dir_Y = 360;
						pApp->rot.y = 360;
					}
					else {
						pApp->rot.y = m_Edit_Dir_Y;
					}
					m_Edit_Slider_Dir_Y.SetPos((int)m_Edit_Dir_Y);

					// Z座標パラメータの入力内容を反映
					if(m_Edit_Dir_Z <= 0) {
						m_Edit_Dir_Z = 0;
						pApp->rot.z = 0;
					}
					else if(m_Edit_Dir_Z >= 360) {
						m_Edit_Dir_Z = 360;
						pApp->rot.z = 360;
					}
					else {
						pApp->rot.z = m_Edit_Dir_Z;
					}
					m_Edit_Slider_Dir_Z.SetPos((int)m_Edit_Dir_Z);

					// スピードパラメータの入力内容を反映
					if(m_Edit_Speed < 1) {
						m_Edit_Speed = 1;
						pApp->rot.w = 1;
					}
					else if(m_Edit_Speed > 10000) {
						m_Edit_Speed = 10000;
						pApp->rot.w = 10000;
					}
					else {
						pApp->rot.w = m_Edit_Speed;
					}
					m_Edit_Slider_Speed.SetPos((int)(m_Edit_Speed));

					// 極座標角の入力内容を反映
					if(m_Edit_Gravity < 0) m_Edit_Gravity = 0;
					else if(m_Edit_Gravity > 360) m_Edit_Gravity = 360;
					pApp->dir = m_Edit_Gravity;
					m_Edit_Slider_Gravity.SetPos((int)(m_Edit_Gravity));
				}


				// ラジオボタンの設定が”スケール値”の状態のとき
				pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
				if(pBtn->GetCheck()){
					// X座標パラメータの入力内容を反映
					if(m_Edit_Dir_X < SCROLL_MIN*0.01f) {
						m_Edit_Dir_X = SCROLL_MIN*0.01f;
						pApp->scale.x = SCROLL_MIN;
					}
					else if(m_Edit_Dir_X > SCROLL_MAX*0.01f) {
						m_Edit_Dir_X = SCROLL_MAX*0.01f;
						pApp->scale.x = SCROLL_MAX;
					}
					else{
						pApp->scale.x = m_Edit_Dir_X;
					}
					m_Edit_Slider_Dir_X.SetPos((int)(m_Edit_Dir_X * 100.0f));

					// Y座標パラメータの入力内容を反映
					if(m_Edit_Dir_Y < SCROLL_MIN*0.01f) {
						m_Edit_Dir_Y = SCROLL_MIN*0.01f;
						pApp->scale.y = SCROLL_MIN;
					}
					else if(m_Edit_Dir_Y > SCROLL_MAX*0.01f) {
						m_Edit_Dir_Y = SCROLL_MAX*0.01f;
						pApp->scale.y = SCROLL_MAX;
					}
					else {
						pApp->scale.y = m_Edit_Dir_Y;
					}
					m_Edit_Slider_Dir_Y.SetPos((int)(m_Edit_Dir_Y * 100.0f));

					// Z座標パラメータの入力内容を反映
					if(m_Edit_Dir_Z < SCROLL_MIN*0.01f) {
						m_Edit_Dir_Z = SCROLL_MIN*0.01f;
						pApp->scale.z = SCROLL_MIN;
					}
					else if(m_Edit_Dir_Z > SCROLL_MAX*0.01f) {
						m_Edit_Dir_Z = SCROLL_MAX*0.01f;
						pApp->scale.z = SCROLL_MAX;
					}
					else {
						pApp->scale.z = m_Edit_Dir_Z;
					}
					m_Edit_Slider_Dir_Z.SetPos((int)(m_Edit_Dir_Z * 100.0f));

					// スピードパラメータの入力内容を反映
					if(m_Edit_Speed < 1*0.01f) {
						m_Edit_Speed = 1*0.01f;
						pApp->scale.w = 1;
					}
					else if(m_Edit_Speed > 5000*0.01f) {
						m_Edit_Speed = 5000*0.01f;
						pApp->scale.w = 5000;
					}
					else {
						pApp->scale.w = m_Edit_Speed;
					}
					m_Edit_Slider_Speed.SetPos((int)(m_Edit_Speed * 100.0f));
				}




			//---------------- テクスチャカテゴリ --------------------------
				// テクスチャスケールの入力内容を反映
				if(m_Edit_Scale < 0.01f) m_Edit_Scale = 0.01f;
				else if(m_Edit_Scale > 50.0f) m_Edit_Scale = 50.0f;
				m_Edit_Slider_Size.SetPos((int)(m_Edit_Scale * 100.0f));


			UpdateData(false);		// 各コントロールに反映	

			ReStart();
			return true;


			case VK_ESCAPE:		return true;	// 「押されてなかった事にする」
		}
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CEditDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	float work;
	POSITION3 pos;
	CButton* pBtn;

	// アプリケーションオブジェクトのポインタを取得
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	//---------------- パーティクルカテゴリ --------------------------
		// パーティクル数設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Num) {
			m_Edit_Num = m_Edit_Slider_Num.GetPos();
		}

		// 継続時間設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Time){
			m_Edit_Time = m_Edit_Slider_Time.GetPos();
		}

	//---------------- 座標カテゴリ --------------------------
		// X座標設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Pos_X){
			UpdateData(true);
			work = m_Edit_Pos_X;
			m_Edit_Pos_X = m_Edit_Slider_Pos_X.GetPos()*0.01f;
			pApp->direct_x.mainbord->SetMove((m_Edit_Pos_X-work)*-1,0,0);
		}

		// Y座標設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Pos_Y){
			UpdateData(true);
			work = m_Edit_Pos_Y;
			m_Edit_Pos_Y = m_Edit_Slider_Pos_Y.GetPos()*0.01f;
			pApp->direct_x.mainbord->SetMove(0,(m_Edit_Pos_Y-work)*-1,0);
		}

		// Z座標設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Pos_Z){
			UpdateData(true);
			work = m_Edit_Pos_Z;
			m_Edit_Pos_Z = m_Edit_Slider_Pos_Z.GetPos()*0.01f;
			pApp->direct_x.mainbord->SetMove(0,0,(m_Edit_Pos_Z-work)*-1);
		}

		// X軸発生範囲設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Range_X){
			m_Edit_Range_X = m_Edit_Slider_Range_X.GetPos()*0.01f;
			for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
				pApp->particle[i].rangex = m_Edit_Range_X;
				pApp->particle[i].rangey = m_Edit_Range_Y;
				pApp->particle[i].rangez = m_Edit_Range_Z;
			}
		}

		// Y軸発生範囲設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Range_Y){
			m_Edit_Range_Y = m_Edit_Slider_Range_Y.GetPos()*0.01f;
			for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
				pApp->particle[i].rangex = m_Edit_Range_X;
				pApp->particle[i].rangey = m_Edit_Range_Y;
				pApp->particle[i].rangez = m_Edit_Range_Z;
			}
		}

		// Z軸発生範囲設定のスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Range_Z){
			m_Edit_Range_Z = m_Edit_Slider_Range_Z.GetPos()*0.01f;
			for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
				pApp->particle[i].rangex = m_Edit_Range_X;
				pApp->particle[i].rangey = m_Edit_Range_Y;
				pApp->particle[i].rangez = m_Edit_Range_Z;
			}
		}


	//---------------- パラメータカテゴリ --------------------------
		// ラジオボタンが”移動値”に設定されていた場合
		pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
		if(pBtn->GetCheck()){
			// X軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_X){
				UpdateData(true);
				work = m_Edit_Dir_X;
				m_Edit_Dir_X = m_Edit_Slider_Dir_X.GetPos()*0.01f;
				pApp->direct_x.mainbord->SetMove((m_Edit_Dir_X-work)*-1,0,0);
				pApp->pos.x = (float)m_Edit_Slider_Dir_X.GetPos();
			}
			// Y軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Y){
				UpdateData(true);
				work = m_Edit_Dir_Y;
				m_Edit_Dir_Y = m_Edit_Slider_Dir_Y.GetPos()*0.01f;
				pApp->direct_x.mainbord->SetMove(0,(m_Edit_Dir_Y-work)*-1,0);
				pApp->pos.y = (float)m_Edit_Slider_Dir_Y.GetPos();
			}
			// Z軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Z){
				UpdateData(true);
				work = m_Edit_Dir_Z;
				m_Edit_Dir_Z = m_Edit_Slider_Dir_Z.GetPos()*0.01f;
				pApp->direct_x.mainbord->SetMove(0,0,(m_Edit_Dir_Z-work)*-1);
				pApp->pos.z = (float)m_Edit_Slider_Dir_Z.GetPos();
			}
			// 加速度の設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Speed) {
				m_Edit_Speed = m_Edit_Slider_Speed.GetPos()*0.01f;
				for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
					pApp->particle[i].speed = m_Edit_Speed;
				}
				pApp->pos.w = m_Edit_Speed * 100;
			}
			// 重力の設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Gravity) {
				m_Edit_Gravity = m_Edit_Slider_Gravity.GetPos()*0.01f;
				pApp->gravity = m_Edit_Gravity;
			}

		}


		// ラジオボタンが”回転値”に設定されていた場合
		pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
		if(pBtn->GetCheck()){
			// X軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_X){
				UpdateData(true);
				work = m_Edit_Dir_X;
				m_Edit_Dir_X = (float)m_Edit_Slider_Dir_X.GetPos();
				pApp->direct_x.mainbord->SetMove((m_Edit_Dir_X-work)*-1,0,0);
				pApp->rot.x = (float)m_Edit_Slider_Dir_X.GetPos();
			}
			// Y軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Y){
				UpdateData(true);
				work = m_Edit_Dir_Y;
				m_Edit_Dir_Y = (float)m_Edit_Slider_Dir_Y.GetPos();
				pApp->direct_x.mainbord->SetMove(0,(m_Edit_Dir_Y-work)*-1,0);
				pApp->rot.y = (float)m_Edit_Slider_Dir_Y.GetPos();
			}
			// Z軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Z){
				UpdateData(true);
				work = m_Edit_Dir_Z;
				m_Edit_Dir_Z = (float)m_Edit_Slider_Dir_Z.GetPos();
				pApp->direct_x.mainbord->SetMove(0,0,(m_Edit_Dir_Z-work)*-1);
				pApp->rot.z = (float)m_Edit_Slider_Dir_Z.GetPos();
			}
			// 加速度の設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Speed) {
				m_Edit_Speed = m_Edit_Slider_Speed.GetPos();
				pApp->rot.w = m_Edit_Speed;
			}

			// 極座標角の設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Gravity) {
				m_Edit_Gravity = m_Edit_Slider_Gravity.GetPos();
				pApp->dir = m_Edit_Gravity;
			}
		}


		// ラジオボタンが”スケール値”に設定されていた場合
		pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
		if(pBtn->GetCheck()){
			// X軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_X){
				UpdateData(true);
				work = m_Edit_Dir_X;
				m_Edit_Dir_X = m_Edit_Slider_Dir_X.GetPos()*0.01f;
				pApp->direct_x.mainbord->SetMove((m_Edit_Dir_X-work)*-1,0,0);
				pApp->scale.x = (float)m_Edit_Dir_X;
			}
			// Y軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Y){
				UpdateData(true);
				work = m_Edit_Dir_Y;
				m_Edit_Dir_Y = m_Edit_Slider_Dir_Y.GetPos()*0.01f;
				pApp->direct_x.mainbord->SetMove(0,(m_Edit_Dir_Y-work)*-1,0);
				pApp->scale.y = (float)m_Edit_Dir_Y;
			}
			// Z軸に対する設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Z){
				UpdateData(true);
				work = m_Edit_Dir_Z;
				m_Edit_Dir_Z = m_Edit_Slider_Dir_Z.GetPos()*0.01f;
				pApp->direct_x.mainbord->SetMove(0,0,(m_Edit_Dir_Z-work)*-1);
				pApp->scale.z = (float)m_Edit_Dir_Z;
			}
			// 加速度の設定を反映
			if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Speed) {
				m_Edit_Speed = m_Edit_Slider_Speed.GetPos()*0.01f;
				for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
					pApp->particle[i].speed = m_Edit_Speed;
				}
				pApp->scale.w = m_Edit_Speed * 100;
			}
		}





	//---------------- テクスチャカテゴリ --------------------------
		// テクスチャサイズのスライダーがスクロールされた場合
		if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Size){
			m_Edit_Scale = m_Edit_Slider_Size.GetPos()*0.01f;
		}


	UpdateData(false);		// コントロールに反映

	ReStart();


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEditDialog::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	POSITION3 pos;
	CButton* pBtn;


	UpdateData(true);		// 現在の情報をコントロールに反映

	//---------------- パーティクルカテゴリ --------------------------
		// パーティクル数の入力内容を反映
		if(m_Edit_Num < 1) m_Edit_Num = 1;
		else if(m_Edit_Num > PARTICLE_MAX) m_Edit_Num = PARTICLE_MAX;
		m_Edit_Slider_Num.SetPos(m_Edit_Num);

		// 継続時間の入力内容を反映
		if(m_Edit_Time < 1) m_Edit_Time = 1;
		else if(m_Edit_Time > 1200) m_Edit_Time = 1200;
		m_Edit_Slider_Time.SetPos(m_Edit_Time);


	//---------------- 座標カテゴリ --------------------------
		// X座標の入力内容を反映
		if(m_Edit_Pos_X < SCROLL_MIN*0.01f) m_Edit_Pos_X = SCROLL_MIN*0.01f;
		else if(m_Edit_Pos_X > SCROLL_MAX*0.01f) m_Edit_Pos_X = SCROLL_MAX*0.01f;
		m_Edit_Slider_Pos_X.SetPos((int)(m_Edit_Pos_X * 100.0f));

		// Y座標の入力内容を反映
		if(m_Edit_Pos_Y < SCROLL_MIN*0.01f) m_Edit_Pos_Y = SCROLL_MIN*0.01f;
		else if(m_Edit_Pos_Y > SCROLL_MAX*0.01f) m_Edit_Pos_Y = SCROLL_MAX*0.01f;
		m_Edit_Slider_Pos_Y.SetPos((int)(m_Edit_Pos_Y * 100.0f));

		// Z座標の入力内容を反映
		if(m_Edit_Pos_Z < SCROLL_MIN*0.01f) m_Edit_Pos_Z = SCROLL_MIN*0.01f;
		else if(m_Edit_Pos_Z > SCROLL_MAX*0.01f) m_Edit_Pos_Z = SCROLL_MAX*0.01f;
		m_Edit_Slider_Pos_Z.SetPos((int)(m_Edit_Pos_Z * 100.0f));

		// X座標の発生範囲の入力内容を反映
		if(m_Edit_Range_X < SCROLL_MIN*0.01f) m_Edit_Range_X = SCROLL_MIN*0.01f;
		else if(m_Edit_Range_X > SCROLL_MAX*0.01f) m_Edit_Range_X = SCROLL_MAX*0.01f;
		m_Edit_Slider_Range_X.SetPos((int)(m_Edit_Range_X * 100.0f));

		// Y座標の発生範囲の入力内容を反映
		if(m_Edit_Range_Y < SCROLL_MIN*0.01f) m_Edit_Range_Y = SCROLL_MIN*0.01f;
		else if(m_Edit_Range_Y > SCROLL_MAX*0.01f) m_Edit_Range_Y = SCROLL_MAX*0.01f;
		m_Edit_Slider_Range_Y.SetPos((int)(m_Edit_Range_Y * 100.0f));

		// Z座標の発生範囲の入力内容を反映
		if(m_Edit_Range_Z < SCROLL_MIN*0.01f) m_Edit_Range_Z = SCROLL_MIN*0.01f;
		else if(m_Edit_Range_Z > SCROLL_MAX*0.01f) m_Edit_Range_Z = SCROLL_MAX*0.01f;
		m_Edit_Slider_Range_Z.SetPos((int)(m_Edit_Range_Z * 100.0f));



	//---------------- パラメータカテゴリ --------------------------
		// ラジオボタンの設定が”移動値”の状態のとき
		pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
		if(pBtn->GetCheck()){
			// X座標パラメータの入力内容を反映
			if(m_Edit_Dir_X < SCROLL_MIN*0.01f) {
				m_Edit_Dir_X = SCROLL_MIN*0.01f;
				pApp->pos.x = SCROLL_MIN;
			}
			else if(m_Edit_Dir_X > SCROLL_MAX*0.01f){
				m_Edit_Dir_X = SCROLL_MAX*0.01f;
				pApp->pos.x = SCROLL_MAX;
			}
			else {
				pApp->pos.x = m_Edit_Dir_X*100;
			}
			m_Edit_Slider_Dir_X.SetPos((int)(m_Edit_Dir_X * 100.0f));

			// Y座標パラメータの入力内容を反映
			if(m_Edit_Dir_Y < SCROLL_MIN*0.01f) {
				m_Edit_Dir_Y = SCROLL_MIN*0.01f;
				pApp->pos.y = SCROLL_MIN;
			}
			else if(m_Edit_Dir_Y > SCROLL_MAX*0.01f){
				m_Edit_Dir_Y = SCROLL_MAX*0.01f;
				pApp->pos.y = SCROLL_MAX;
			}
			else {
				pApp->pos.y = m_Edit_Dir_Y*100;
			}
			m_Edit_Slider_Dir_Y.SetPos((int)(m_Edit_Dir_Y * 100.0f));

			// Z座標パラメータの入力内容を反映
			if(m_Edit_Dir_Z < SCROLL_MIN*0.01f) {
				m_Edit_Dir_Z = SCROLL_MIN*0.01f;
				pApp->pos.z = SCROLL_MIN;
			}
			else if(m_Edit_Dir_Z > SCROLL_MAX*0.01f) {
				m_Edit_Dir_Z = SCROLL_MAX*0.01f;
				pApp->pos.z = SCROLL_MAX;
			}
			else {
				pApp->pos.z = m_Edit_Dir_Z*100;
			}
			m_Edit_Slider_Dir_Z.SetPos((int)(m_Edit_Dir_Z * 100.0f));

			// スピードパラメータの入力内容を反映
			if(m_Edit_Speed < 1*0.01f) {
				m_Edit_Speed = 1*0.01f;
				pApp->pos.w = 1;
			}
			else if(m_Edit_Speed > 5000*0.01f) {
				m_Edit_Speed = 5000*0.01f;
				pApp->pos.w = 5000;
			}
			else {
				pApp->pos.w = m_Edit_Speed*100;
			}
			m_Edit_Slider_Speed.SetPos((int)(m_Edit_Speed * 100.0f));

			// 重力の入力内容を反映
			if(m_Edit_Gravity < -10000*0.01f) m_Edit_Gravity = -10000*0.01f;
			else if(m_Edit_Gravity > 10000*0.01f) m_Edit_Gravity = 10000*0.01f;
			pApp->gravity = m_Edit_Gravity;
			m_Edit_Slider_Gravity.SetPos((int)(m_Edit_Gravity * 100.0f));

		}

		// ラジオボタンの設定が”回転値”の状態のとき
		pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
		if(pBtn->GetCheck()){
			// X座標パラメータの入力内容を反映
			if(m_Edit_Dir_X <= 0) {
				m_Edit_Dir_X = 0;
				pApp->rot.x = 0;
			}
			else if(m_Edit_Dir_X >= 360){
				m_Edit_Dir_X = 360;
				pApp->rot.x = 360;
			}
			else {
				pApp->rot.x = m_Edit_Dir_X;
			}
			m_Edit_Slider_Dir_X.SetPos((int)m_Edit_Dir_X);

			// Y座標パラメータの入力内容を反映
			if(m_Edit_Dir_Y <= 0) {
				m_Edit_Dir_Y = 0;
				pApp->rot.y = 0;
			}
			else if(m_Edit_Dir_Y >= 360) {
				m_Edit_Dir_Y = 360;
				pApp->rot.y = 360;
			}
			else {
				pApp->rot.y = m_Edit_Dir_Y;
			}
			m_Edit_Slider_Dir_Y.SetPos((int)m_Edit_Dir_Y);

			// Z座標パラメータの入力内容を反映
			if(m_Edit_Dir_Z <= 0) {
				m_Edit_Dir_Z = 0;
				pApp->rot.z = 0;
			}
			else if(m_Edit_Dir_Z >= 360) {
				m_Edit_Dir_Z = 360;
				pApp->rot.z = 360;
			}
			else {
				pApp->rot.z = m_Edit_Dir_Z;
			}
			m_Edit_Slider_Dir_Z.SetPos((int)m_Edit_Dir_Z);

			// スピードパラメータの入力内容を反映
			if(m_Edit_Speed < 1) {
				m_Edit_Speed = 1;
				pApp->rot.w = 1;
			}
			else if(m_Edit_Speed > 10000) {
				m_Edit_Speed = 10000;
				pApp->rot.w = 10000;
			}
			else {
				pApp->rot.w = m_Edit_Speed;
			}
			m_Edit_Slider_Speed.SetPos((int)(m_Edit_Speed));

			// 極座標角を反映
			if(m_Edit_Gravity < 0) m_Edit_Gravity = 0;
			else if(m_Edit_Gravity > 360) m_Edit_Gravity = 360;
			pApp->dir = m_Edit_Gravity;
			m_Edit_Slider_Gravity.SetPos((int)(m_Edit_Gravity));

		}


		// ラジオボタンの設定が”スケール値”の状態のとき
		pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
		if(pBtn->GetCheck()){
			// X座標パラメータの入力内容を反映
			if(m_Edit_Dir_X < SCROLL_MIN*0.01f) {
				m_Edit_Dir_X = SCROLL_MIN*0.01f;
				pApp->scale.x = SCROLL_MIN;
			}
			else if(m_Edit_Dir_X > SCROLL_MAX*0.01f) {
				m_Edit_Dir_X = SCROLL_MAX*0.01f;
				pApp->scale.x = SCROLL_MAX;
			}
			else{
				pApp->scale.x = m_Edit_Dir_X;
			}
			m_Edit_Slider_Dir_X.SetPos((int)(m_Edit_Dir_X * 100.0f));

			// Y座標パラメータの入力内容を反映
			if(m_Edit_Dir_Y < SCROLL_MIN*0.01f) {
				m_Edit_Dir_Y = SCROLL_MIN*0.01f;
				pApp->scale.y = SCROLL_MIN;
			}
			else if(m_Edit_Dir_Y > SCROLL_MAX*0.01f) {
				m_Edit_Dir_Y = SCROLL_MAX*0.01f;
				pApp->scale.y = SCROLL_MAX;
			}
			else {
				pApp->scale.y = m_Edit_Dir_Y;
			}
			m_Edit_Slider_Dir_Y.SetPos((int)(m_Edit_Dir_Y * 100.0f));

			// Z座標パラメータの入力内容を反映
			if(m_Edit_Dir_Z < SCROLL_MIN*0.01f) {
				m_Edit_Dir_Z = SCROLL_MIN*0.01f;
				pApp->scale.z = SCROLL_MIN;
			}
			else if(m_Edit_Dir_Z > SCROLL_MAX*0.01f) {
				m_Edit_Dir_Z = SCROLL_MAX*0.01f;
				pApp->scale.z = SCROLL_MAX;
			}
			else {
				pApp->scale.z = m_Edit_Dir_Z;
			}
			m_Edit_Slider_Dir_Z.SetPos((int)(m_Edit_Dir_Z * 100.0f));

			// スピードパラメータの入力内容を反映
			if(m_Edit_Speed < 1*0.01f) {
				m_Edit_Speed = 1*0.01f;
				pApp->scale.w = 1;
			}
			else if(m_Edit_Speed > 5000*0.01f) {
				m_Edit_Speed = 5000*0.01f;
				pApp->scale.w = 5000;
			}
			else {
				pApp->scale.w = m_Edit_Speed;
			}
			m_Edit_Slider_Speed.SetPos((int)(m_Edit_Speed * 100.0f));
		}





	//---------------- テクスチャカテゴリ --------------------------
		// テクスチャスケールの入力内容を反映
		if(m_Edit_Scale < 0.01f) m_Edit_Scale = 0.01f;
		else if(m_Edit_Scale > 50.0f) m_Edit_Scale = 50.0f;
		m_Edit_Slider_Size.SetPos((int)(m_Edit_Scale * 100.0f));



	UpdateData(false);		// 各コントロールに反映	

	// 入力パラメータをプレビューに反映
	ReStart();

}

void CEditDialog::OnBnClickedRadioPos()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

#if 0
	// 全てのラジオボタンを再設定
	CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
	pBtn->SetCheck(true);
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
	pBtn->SetCheck(false);
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
	pBtn->SetCheck(false);
#endif

	// 汎用X軸用スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Dir_X.SetRange(SCROLL_MIN, SCROLL_MAX, true);
	m_Edit_Slider_Dir_X.SetPageSize(1);	m_Edit_Slider_Dir_X.SetLineSize(1);	m_Edit_Slider_Dir_X.SetPos(0);
	m_Edit_Slider_Dir_X.SetPos((int)pApp->pos.x);

	// 汎用Y軸用スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Dir_Y.SetRange(SCROLL_MIN, SCROLL_MAX, true);
	m_Edit_Slider_Dir_Y.SetPageSize(1);	m_Edit_Slider_Dir_Y.SetLineSize(1);	m_Edit_Slider_Dir_Y.SetPos(0);
	m_Edit_Slider_Dir_Y.SetPos((int)pApp->pos.y);

	// 汎用Z軸用スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Dir_Z.SetRange(SCROLL_MIN, SCROLL_MAX, true);
	m_Edit_Slider_Dir_Z.SetPageSize(1);	m_Edit_Slider_Dir_Z.SetLineSize(1);	m_Edit_Slider_Dir_Z.SetPos(0);
	m_Edit_Slider_Dir_Z.SetPos((int)pApp->pos.z);

	// 汎用スピードパラメータ設定スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Speed.SetRange(1, 5000, true);
	m_Edit_Slider_Speed.SetPageSize(1);	m_Edit_Slider_Speed.SetLineSize(1);	m_Edit_Slider_Speed.SetPos(0);
	m_Edit_Slider_Speed.SetPos((int)pApp->pos.w);

	// 重力パラメータ設定スライダー初期化
	m_Edit_Slider_Gravity.SetRange(-10000, 10000, true);
	m_Edit_Slider_Gravity.SetPageSize(1);	m_Edit_Slider_Gravity.SetLineSize(1);	m_Edit_Slider_Gravity.SetPos(0);
	m_Edit_Slider_Gravity.SetPos((int)pApp->gravity*100);

	// X軸に対する設定を反映
	m_Edit_Dir_X = pApp->pos.x*0.01f;
	// Y軸に対する設定を反映
	m_Edit_Dir_Y = pApp->pos.y*0.01f;
	// Z軸に対する設定を反映
	m_Edit_Dir_Z = pApp->pos.z*0.01f;
	// 加速度の設定を反映
	m_Edit_Speed = pApp->pos.w*0.01f;
	// 重力の設定を反映
	m_Edit_Gravity = pApp->gravity;

	// 汎用Xパラメータ用フラグ反映
	m_Check_Side_X.SetCheck((int)pApp->posflg.x);
	// 汎用Yパラメータ用フラグ反映
	m_Check_Side_Y.SetCheck((int)pApp->posflg.y);
	// 汎用Zパラメータ用フラグ反映
	m_Check_Side_Z.SetCheck((int)pApp->posflg.z);


	// 各種パラメータ用のテキストを変更
	m_Check_Side_X.SetWindowText("両サイドに散らす");
	m_Check_Side_Y.SetWindowText("両サイドに散らす");
	m_Check_Side_Z.SetWindowText("両サイドに散らす");
	m_Static_Dir_X.SetWindowText("向き:X");
	m_Static_Dir_Y.SetWindowText("向き:Y");
	m_Static_Dir_Z.SetWindowText("向き:Z");
	m_Static_Speed.SetWindowText("加速度");
	m_Static_Gravity.SetWindowText("重力");

	UpdateData(false);		// 各コントロールに反映	
}

void CEditDialog::OnBnClickedRadioRot()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

#if 0
	// 全てのラジオボタンを再設定
	CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
	pBtn->SetCheck(true);
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
	pBtn->SetCheck(false);
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
	pBtn->SetCheck(false);
#endif

	// 汎用X軸用スライダーを回転値設定用にあわせて再設定
	m_Edit_Slider_Dir_X.SetRange(0, 360, true);
	m_Edit_Slider_Dir_X.SetPageSize(1);	m_Edit_Slider_Dir_X.SetLineSize(1);	m_Edit_Slider_Dir_X.SetPos(0);
	m_Edit_Slider_Dir_X.SetPos((int)pApp->rot.x);

	// 汎用Y軸用スライダーを回転値設定用にあわせて再設定
	m_Edit_Slider_Dir_Y.SetRange(0, 360, true);
	m_Edit_Slider_Dir_Y.SetPageSize(1);	m_Edit_Slider_Dir_Y.SetLineSize(1);	m_Edit_Slider_Dir_Y.SetPos(0);
	m_Edit_Slider_Dir_Y.SetPos((int)pApp->rot.y);

	// 汎用Z軸用スライダーを回転値設定用にあわせて再設定
	m_Edit_Slider_Dir_Z.SetRange(0, 360, true);
	m_Edit_Slider_Dir_Z.SetPageSize(1);	m_Edit_Slider_Dir_Z.SetLineSize(1);	m_Edit_Slider_Dir_Z.SetPos(0);
	m_Edit_Slider_Dir_Z.SetPos((int)pApp->rot.z);

	// 汎用スピードパラメータ設定スライダーを回転値設定用にあわせて再設定
	m_Edit_Slider_Speed.SetRange(1, 10000, true);
	m_Edit_Slider_Speed.SetPageSize(1);	m_Edit_Slider_Speed.SetLineSize(1);	m_Edit_Slider_Speed.SetPos(0);
	m_Edit_Slider_Speed.SetPos((int)pApp->rot.w);

	// 重力パラメータ設定スライダー初期化
	m_Edit_Slider_Gravity.SetRange(0, 360, true);
	m_Edit_Slider_Gravity.SetPageSize(1);	m_Edit_Slider_Gravity.SetLineSize(1);	m_Edit_Slider_Gravity.SetPos(0);
	m_Edit_Slider_Gravity.SetPos(pApp->dir);


	// X軸に対する設定を反映
	m_Edit_Dir_X = pApp->rot.x;
	// Y軸に対する設定を反映
	m_Edit_Dir_Y = pApp->rot.y;
	// Z軸に対する設定を反映
	m_Edit_Dir_Z = pApp->rot.z;
	// 加速度の設定を反映
	m_Edit_Speed = pApp->rot.w;
	// 極座標角の設定を反映
	m_Edit_Gravity = pApp->dir;


	// 汎用Xパラメータ用フラグ反映
	m_Check_Side_X.SetCheck((int)pApp->rotflg.x);
	// 汎用Yパラメータ用フラグ反映
	m_Check_Side_Y.SetCheck((int)pApp->rotflg.y);
	// 汎用Zパラメータ用フラグ反映
	m_Check_Side_Z.SetCheck((int)pApp->rotflg.z);

	// 各種パラメータ用のテキストを変更
	m_Check_Side_X.SetWindowText("円筒座標系で動かす");
	m_Check_Side_Y.SetWindowText("極座標系で動かす");
	m_Check_Side_Z.SetWindowText("発生座標を軸として計算する");
	m_Static_Dir_X.SetWindowText("角度:X");
	m_Static_Dir_Y.SetWindowText("角度:Y");
	m_Static_Dir_Z.SetWindowText("角度:Z");
	m_Static_Speed.SetWindowText("半径");
	m_Static_Gravity.SetWindowText("極座標角");

	UpdateData(false);		// 各コントロールに反映	
}

void CEditDialog::OnBnClickedRadioScale()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

#if 0
	// 全てのラジオボタンを再設定
	CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
	pBtn->SetCheck(true);
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
	pBtn->SetCheck(false);
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
	pBtn->SetCheck(false);
#endif

	// 汎用X軸用スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Dir_X.SetRange(SCROLL_MIN/10, SCROLL_MAX/10, true);
	m_Edit_Slider_Dir_X.SetPageSize(1);	m_Edit_Slider_Dir_X.SetLineSize(1);	m_Edit_Slider_Dir_X.SetPos(0);
	m_Edit_Slider_Dir_X.SetPos((int)pApp->scale.x);

	// 汎用Y軸用スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Dir_Y.SetRange(SCROLL_MIN/10, SCROLL_MAX/10, true);
	m_Edit_Slider_Dir_Y.SetPageSize(1);	m_Edit_Slider_Dir_Y.SetLineSize(1);	m_Edit_Slider_Dir_Y.SetPos(0);
	m_Edit_Slider_Dir_Y.SetPos((int)pApp->scale.y);

	// 汎用Z軸用スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Dir_Z.SetRange(SCROLL_MIN/10, SCROLL_MAX/10, true);
	m_Edit_Slider_Dir_Z.SetPageSize(1);	m_Edit_Slider_Dir_Z.SetLineSize(1);	m_Edit_Slider_Dir_Z.SetPos(0);
	m_Edit_Slider_Dir_Z.SetPos((int)pApp->scale.z);

	// 汎用スピードパラメータ設定スライダーを移動値設定用にあわせて再設定
	m_Edit_Slider_Speed.SetRange(1, 5000, true);
	m_Edit_Slider_Speed.SetPageSize(1);	m_Edit_Slider_Speed.SetLineSize(1);	m_Edit_Slider_Speed.SetPos(0);
	m_Edit_Slider_Speed.SetPos((int)pApp->scale.z);

	// X軸に対する設定を反映
	m_Edit_Dir_X = pApp->scale.x;
	// Y軸に対する設定を反映
	m_Edit_Dir_Y = pApp->scale.y;
	// Z軸に対する設定を反映
	m_Edit_Dir_Z = pApp->scale.z;
	// 加速度の設定を反映
	m_Edit_Speed = pApp->scale.w*0.01f;

	// 汎用Xパラメータ用フラグ反映
	m_Check_Side_X.SetCheck((int)pApp->scaleflg.x);
	// 汎用Yパラメータ用フラグ反映
	m_Check_Side_Y.SetCheck((int)pApp->scaleflg.y);
	// 汎用Zパラメータ用フラグ反映
	m_Check_Side_Z.SetCheck((int)pApp->scaleflg.z);

	// 各種パラメータ用のテキストを変更
	m_Check_Side_X.SetWindowText("時間経過でこの値にする");
	m_Check_Side_Y.SetWindowText("時間経過でこの値にする");
	m_Check_Side_Z.SetWindowText("時間経過でこの値にする");
	m_Static_Dir_X.SetWindowText("拡大率:X");
	m_Static_Dir_Y.SetWindowText("拡大率:Y");
	m_Static_Dir_Z.SetWindowText("拡大率:Z");
	m_Static_Speed.SetWindowText("");
	m_Static_Gravity.SetWindowText("");

	UpdateData(false);		// 各コントロールに反映
}

void CEditDialog::OnBnClickedCheckSideX()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	CButton* pBtn;

	// ラジオボタンのチェックが”移動値”ならば
	// 現在のX軸用チェックボタンの内容を移動値用Xフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
	if(pBtn->GetCheck()) pApp->posflg.x = (bool)m_Check_Side_X.GetCheck();

	// ラジオボタンのチェックが”回転値”ならば
	// 現在のX軸用チェックボタンの内容を回転値用Xフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
	if(pBtn->GetCheck()) pApp->rotflg.x = (bool)m_Check_Side_X.GetCheck();

	// ラジオボタンのチェックが”スケール値”ならば
	// 現在のX軸用チェックボタンの内容をスケール値用Xフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
	if(pBtn->GetCheck()) pApp->scaleflg.x = (bool)m_Check_Side_X.GetCheck();

}

void CEditDialog::OnBnClickedCheckSideY()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	CButton* pBtn;

	// ラジオボタンのチェックが”移動値”ならば
	// 現在のY軸用チェックボタンの内容を移動値用Yフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
	if(pBtn->GetCheck()) pApp->posflg.y = (bool)m_Check_Side_Y.GetCheck();

	// ラジオボタンのチェックが”回転値”ならば
	// 現在のY軸用チェックボタンの内容を回転値用Yフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
	if(pBtn->GetCheck()) pApp->rotflg.y = (bool)m_Check_Side_Y.GetCheck();

	// ラジオボタンのチェックが”スケール値”ならば
	// 現在のY軸用チェックボタンの内容をスケール値用Yフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
	if(pBtn->GetCheck()) pApp->scaleflg.y = (bool)m_Check_Side_Y.GetCheck();

}

void CEditDialog::OnBnClickedCheckSideZ()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	CButton* pBtn;

	// ラジオボタンのチェックが”移動値”ならば
	// 現在のZ軸用チェックボタンの内容を移動値用Zフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_POS);
	if(pBtn->GetCheck()) pApp->posflg.z = (bool)m_Check_Side_Z.GetCheck();
	
	// ラジオボタンのチェックが”回転値”ならば
	// 現在のZ軸用チェックボタンの内容を回転値用Zフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_ROT);
	if(pBtn->GetCheck()) pApp->rotflg.z = (bool)m_Check_Side_Z.GetCheck();

	// ラジオボタンのチェックが”スケール値”ならば
	// 現在のZ軸用チェックボタンの内容をスケール値用Zフラグ保存変数に格納
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_SCALE);
	if(pBtn->GetCheck()) pApp->scaleflg.z = (bool)m_Check_Side_Z.GetCheck();

}

void CEditDialog::OnBnClickedCheckTime()
{
	// エフェクトを再起動する
	ReStart();

}

void CEditDialog::OnBnClickedCheckSize()
{
	// エフェクトを再起動する
	ReStart();
}

void CEditDialog::ReStart(void)
{
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	POSITION3 pos;

	pos.x = pApp->pos.x;
	pos.y = pApp->pos.y;
	pos.z = pApp->pos.z;
	for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
		pApp->particle[i].effect_cnt = 1;
		pApp->particle[i].scale = m_Edit_Scale;
		pApp->particle[i].time = m_Edit_Time;
		pApp->particle[i].Move();

		pApp->particle[i].EffectSet(&pos);
	}
}
