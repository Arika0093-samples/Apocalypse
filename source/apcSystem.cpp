// --------------------------------------------------------
//	apcSystem.cpp
// --------------------------------------------------------
//	apcSystem.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	GameSetting
// ----------------------------------------------------
//	GameSetting::GameSetting (Constructor)
// ----------------------------------------------------
				__ApcSetting::__ApcSetting()
{
	// フォント名取得に使用する
	LOGFONT lgFont;
	// ------------------------------------------------
	// リセット
	memset(&lgFont, NULL, sizeof(LOGFONT));
	// システムのフォントを取得する
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lgFont, 0);
	// 各種ステータスの初期化
	Width			= 640;
	Height			= 480;
	Title			= _T("Apocalypse");
	ClassName		= _T("APOCALYPSE_APPLICATION");
	DefaultFontName	= lgFont.lfFaceName;
	Refresh			= 0;
	ActiveAll		= false;
	DualBoot		= false;
	GDIDraw			= true;
	ASyncLoad		= false;
	WindowMode		= true;
	AeroDisable		= false;
	// DEBUGの定義によってDebugModeの値を変える．
	#ifdef _DEBUG
		DebugMode	= true;
	#else
		DebugMode	= false;
	#endif
}

// ----------------------------------------------------
//	ApcSystem
// ----------------------------------------------------
//	ApcSystem::ApcSystem (Constructor)
// ----------------------------------------------------
				__ApcSystem::__ApcSystem()
{
	// Localeを現在の標準言語で指定する
	_tsetlocale(LC_ALL, _T(""));
	// 保存領域を新規作成する
	GameSetting = New( __ApcSetting);
	// カレントディレクトリを指定する
	_SetProgramDirectory();
};

// ----------------------------------------------------
//	ApcSystem::GetWindowWidth
// ----------------------------------------------------
UINT			__ApcSystem::GetWindowWidth()
{
	return (GetInstance().GameSetting->Width);
}

// ----------------------------------------------------
//	ApcSystem::GetWindowHeight
// ----------------------------------------------------
UINT			__ApcSystem::GetWindowHeight()
{
	return (GetInstance().GameSetting->Height);
}

// ----------------------------------------------------
//	ApcSystem::SetProgramDirectory
// ----------------------------------------------------
void			__ApcSystem::_SetProgramDirectory() const
{
	// プログラムの基準ディレクトリを保存するための変数
	TCHAR DirPath[1024];
	// _splitpathを使用するための一時変数
	TCHAR Drive[16], Dir[MAX_PATH], Name[256], Ext[32];
	// ----------------------------------------------------
	// プログラム本体のパスを取得する
	GetModuleFileName(NULL, DirPath, 1024);
	// 取得したパスを各要素に分解する
	_tsplitpath_s(DirPath, Drive, 16, Dir, MAX_PATH, Name, 256, Ext, 32);
	// 分解したパスを再構築する
	wsprintf(DirPath, _T("%s%s"), Drive, Dir);
	// カレントディレクトリに指定する
	SetCurrentDirectory(DirPath);
	// 終了
	return;
}

// ----------------------------------------------------
//	ApcSystem::ApcStart
// ----------------------------------------------------
bool			__ApcSystem::ApcStart() const
{
	// 起動前準備を行う
	_InitGameProcess();
	// 起動する
	_RunStartProcess();
	return true;
}

// ----------------------------------------------------
//	ApcSystem::ApcProcess
// ----------------------------------------------------
bool			__ApcSystem::ApcProcess() const
{
	// 裏画面を表画面に反映．
	ScreenFlip();
	// 裏画面に描画されている内容を消去．
	ClearDrawScreen();
	// もしシーケンスが空ならば
	if(__SequenceCollection::GetInstance().Top() == NULL){
		// 終了．
		return false;
	}
	// 終了時関数が登録されていて，終了コマンドが送られてきたなら
	if(!GameSetting->ExitFunction.empty() && GetWindowUserCloseFlag(TRUE) == TRUE){
		// 関数を実行した戻り値がTRUEなら
		if((int)GameSetting->ExitFunction() == TRUE){
			// 終了．
			return false;
		}
	}
	// ×ボタンが押されていたら
	if(ProcessMessage() == 0){
		// 終了．
		return false;
	}
	// カウンタの値を増加させておく．
	__FrameCounter::GetInstance()._CountAdd();
	// キーボードの状態を更新する．
	KeyBoard::GetInstance()._CheckKeyEvent();
	// マウスの状態を更新する．
	Mouse::GetInstance()._CheckMouseEvent();
	// 続行．
	return true;
}

// ----------------------------------------------------
//	ApcSystem::ApcEnd
// ----------------------------------------------------
void			__ApcSystem::ApcEnd() const
{
	//	終了プロセスをコールする
	_RunEndProcess();
};

// ----------------------------------------------------
//	ApcSystem::InitGameProcess
// ----------------------------------------------------
void			__ApcSystem::_InitGameProcess() const
{
	// ログ作成するかどうか．
	SetOutApplicationLogValidFlag(GameSetting->DebugMode);
	// 非同期読み込みするかどうか．
	SetUseASyncLoadFlag(GameSetting->ASyncLoad);
	// ウィンドウのタイトル変更．
	SetMainWindowText(GameSetting->Title);
	// ウィンドウのクラス名変更．
	SetMainWindowClassName(GameSetting->ClassName);
	// アイコン変更．
	SetWindowIconID(1);
	// GDI描画のフラグを指定する
	SetUseGDIFlag(GameSetting->GDIDraw);
	// 二重起動のフラグを指定する．
	SetDoubleStartValidFlag(GameSetting->DualBoot);
	// 常に動作させるかどうかのフラグを指定する．
	SetAlwaysRunFlag(GameSetting->ActiveAll);
	// ウィンドウモードを変更．
	ChangeWindowMode(GameSetting->WindowMode);
	// ウィンドウサイズの変更．
	SetWindowSize(GameSetting->Width, GameSetting->Height);
	// 描画ウインドウサイズの変更．
	SetGraphMode(GameSetting->Width, GameSetting->Height, 32, GameSetting->Refresh);
};

// ----------------------------------------------------
//	ApcSystem::RunStartProcess
// ----------------------------------------------------
void			__ApcSystem::_RunStartProcess() const
{
	//	起動．失敗したら帰る．
	if(DxLib_Init() == -1){
		throw;
	}
	//	描画先を裏画面に設定．
	SetDrawScreen(DX_SCREEN_BACK);
};

// ----------------------------------------------------
//	ApcSystem::RunEndProcess
// ----------------------------------------------------
void			__ApcSystem::_RunEndProcess() const
{
	// 終了する．
	DxLib_End();
};
