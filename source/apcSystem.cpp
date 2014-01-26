// --------------------------------------------------------
//	apcSystem.cpp
// --------------------------------------------------------
//	apcSystem.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	ApplicationConfig
// ----------------------------------------------------
//	(Global Constructor)
// ----------------------------------------------------
UINT			ApplicationConfig::Width			= 640;
UINT			ApplicationConfig::Height			= 480;
String			ApplicationConfig::Title			= _T("Apocalypse");
String			ApplicationConfig::ClassName		= _T("APOCALYPSE_APPLICATION");
String			ApplicationConfig::DefaultFontName	= ApplicationConfig::_GetDefaultFontName();
UINT			ApplicationConfig::Refresh			= 0;
SeqFunc			ApplicationConfig::Sequence			= NULL;
ExitFunc		ApplicationConfig::ExitFunction		= NULL;
bool			ApplicationConfig::ActiveAll		= false;
bool			ApplicationConfig::DualBoot			= false;
bool			ApplicationConfig::GDIDraw			= true;
bool			ApplicationConfig::ASyncLoad		= false;
bool			ApplicationConfig::WindowMode		= true;
bool			ApplicationConfig::AeroDisable		= false;
// DEBUGの定義によってDebugModeの値を変える．
#ifdef _DEBUG
bool			ApplicationConfig::DebugMode		= true;
#else
bool			ApplicationConfig::DebugMode		= false;
#endif

// ----------------------------------------------------
//	GameSetting::Accept
// ----------------------------------------------------
void			ApplicationConfig::Accept()
{
	// ログ作成するかどうか．
	SetOutApplicationLogValidFlag(DebugMode);
	// 非同期読み込みするかどうか．
	SetUseASyncLoadFlag(ASyncLoad);
	// ウィンドウのタイトル変更．
	SetMainWindowText(Title);
	// ウィンドウのクラス名変更．
	SetMainWindowClassName(ClassName);
	// アイコン変更．
	SetWindowIconID(1);
	// GDI描画のフラグを指定する
	SetUseGDIFlag(GDIDraw);
	// 二重起動のフラグを指定する．
	SetDoubleStartValidFlag(DualBoot);
	// 常に動作させるかどうかのフラグを指定する．
	SetAlwaysRunFlag(ActiveAll);
	// 終了時関数を実行するかどうか
	SetWindowUserCloseEnableFlag(ExitFunction.empty());
	// ウィンドウモードを変更．
	ChangeWindowMode(WindowMode);
	// ウィンドウサイズの変更．
	SetWindowSize(Width, Height);
	// 描画ウインドウサイズの変更．
	SetGraphMode(Width, Height, 32, Refresh);
}

// ----------------------------------------------------
//	GameSetting::_GetDefaultFontName
// ----------------------------------------------------
String			ApplicationConfig::_GetDefaultFontName()
{
	// フォント名取得に使用する
	LOGFONT lgFont;
	// ------------------------------------------------
	// リセット
	memset(&lgFont, NULL, sizeof(LOGFONT));
	// システムのフォントを取得する
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lgFont, 0);
	// 返却
	return lgFont.lfFaceName;
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
	// カレントディレクトリを指定する
	_SetProgramDirectory();
};

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
	if(!ApplicationConfig::ExitFunction.empty() && GetWindowUserCloseFlag(TRUE) == TRUE){
		// 関数を実行した戻り値がTRUEなら
		if(ApplicationConfig::ExitFunction()){
			// 終了．
			return false;
		}
	}
	// ×ボタンが押されていたら
	if(ProcessMessage() == -1){
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
	// 設定を適用する
	ApplicationConfig::Accept();
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
