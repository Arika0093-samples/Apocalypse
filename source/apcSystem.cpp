// --------------------------------------------------------
//	apcSystem.cpp
// --------------------------------------------------------
//	apcSystem.h �̃����o�֐��̎��̂�u��
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
UINT			ApplicationConfig::Refresh			= 60;
SeqFunc			ApplicationConfig::Sequence			= NULL;
ExitFunc		ApplicationConfig::ExitFunction		= NULL;
bool			ApplicationConfig::ActiveAll		= false;
bool			ApplicationConfig::DualBoot			= false;
bool			ApplicationConfig::GDIDraw			= true;
bool			ApplicationConfig::ASyncLoad		= false;
bool			ApplicationConfig::WindowMode		= true;
bool			ApplicationConfig::AeroDisable		= false;
// DEBUG�̒�`�ɂ����DebugMode�̒l��ς���D
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
	// ���O�쐬���邩�ǂ����D
	SetOutApplicationLogValidFlag(DebugMode);
	// �񓯊��ǂݍ��݂��邩�ǂ����D
	SetUseASyncLoadFlag(ASyncLoad);
	// �E�B���h�E�̃^�C�g���ύX�D
	SetMainWindowText(Title);
	// �E�B���h�E�̃N���X���ύX�D
	SetMainWindowClassName(ClassName);
	// �A�C�R���ύX�D
	SetWindowIconID(1);
	// GDI�`��̃t���O���w�肷��
	SetUseGDIFlag(GDIDraw);
	// ��d�N���̃t���O���w�肷��D
	SetDoubleStartValidFlag(DualBoot);
	// ��ɓ��삳���邩�ǂ����̃t���O���w�肷��D
	SetAlwaysRunFlag(ActiveAll);
	// �I�����֐������s���邩�ǂ���
	SetWindowUserCloseEnableFlag(ExitFunction.empty());
	// �E�B���h�E���[�h��ύX�D
	ChangeWindowMode(WindowMode);
	// �E�B���h�E�T�C�Y�̕ύX�D
	SetWindowSize(Width, Height);
	// �`��E�C���h�E�T�C�Y�̕ύX�D
	SetGraphMode(Width, Height, 32, Refresh);
}

// ----------------------------------------------------
//	GameSetting::_GetDefaultFontName
// ----------------------------------------------------
String			ApplicationConfig::_GetDefaultFontName()
{
	// �t�H���g���擾�Ɏg�p����
	LOGFONT lgFont;
	// ------------------------------------------------
	// ���Z�b�g
	memset(&lgFont, NULL, sizeof(LOGFONT));
	// �V�X�e���̃t�H���g���擾����
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lgFont, 0);
	// �ԋp
	return lgFont.lfFaceName;
}	
	
// ----------------------------------------------------
//	ApcSystem
// ----------------------------------------------------
//	ApcSystem::ApcSystem (Constructor)
// ----------------------------------------------------
				_System::_System()
{
	// Locale�����݂̕W������Ŏw�肷��
	// _tsetlocale(LC_ALL, _T(""));
	// �J�����g�f�B���N�g�����w�肷��
	_SetProgramDirectory();
};

// ----------------------------------------------------
//	ApcSystem::SetProgramDirectory
// ----------------------------------------------------
void			_System::_SetProgramDirectory() const
{
	// �v���O�����̊�f�B���N�g����ۑ����邽�߂̕ϐ�
	TCHAR DirPath[1024];
	// _splitpath���g�p���邽�߂̈ꎞ�ϐ�
	TCHAR Drive[16], Dir[MAX_PATH], Name[256], Ext[32];
	// ----------------------------------------------------
	// �v���O�����{�̂̃p�X���擾����
	GetModuleFileName(NULL, DirPath, 1024);
	// �擾�����p�X���e�v�f�ɕ�������
	_tsplitpath_s(DirPath, Drive, 16, Dir, MAX_PATH, Name, 256, Ext, 32);
	// ���������p�X���č\�z����
	wsprintf(DirPath, _T("%s%s"), Drive, Dir);
	// �J�����g�f�B���N�g���Ɏw�肷��
	SetCurrentDirectory(DirPath);
	// �I��
	return;
}

// ----------------------------------------------------
//	ApcSystem::ApcStart
// ----------------------------------------------------
bool			_System::ApcStart() const
{
	// �N���O�������s��
	_InitGameProcess();
	// �N������
	_RunStartProcess();
	return true;
}

// ----------------------------------------------------
//	ApcSystem::ApcProcess
// ----------------------------------------------------
bool			_System::ApcProcess() const
{
	// ����ʂ�\��ʂɔ��f�D
	ScreenFlip();
	// ����ʂɕ`�悳��Ă�����e�������D
	ClearDrawScreen();
	// �����V�[�P���X����Ȃ��
	if(_SequenceCollection::GetInstance().Top() == NULL){
		// �I���D
		return false;
	}
	// �I�����֐����o�^����Ă��āC�I���R�}���h�������Ă����Ȃ�
	if(!ApplicationConfig::ExitFunction.empty() && GetWindowUserCloseFlag(TRUE) == TRUE){
		// �֐������s�����߂�l��TRUE�Ȃ�
		if(ApplicationConfig::ExitFunction()){
			// �I���D
			return false;
		}
	}
	// �~�{�^����������Ă�����
	if(ProcessMessage() == -1){
		// �I���D
		return false;
	}
	// �J�E���^�̒l�𑝉������Ă����D
	_FrameCounter::GetInstance()._CountAdd();
	// �L�[�{�[�h�̏�Ԃ��X�V����D
	KeyBoard::GetInstance()._CheckKeyEvent();
	// �}�E�X�̏�Ԃ��X�V����D
	Mouse::GetInstance()._CheckMouseEvent();
	// ���s�D
	return true;
}

// ----------------------------------------------------
//	ApcSystem::ApcEnd
// ----------------------------------------------------
void			_System::ApcEnd() const
{
	//	�I���v���Z�X���R�[������
	_RunEndProcess();
};

// ----------------------------------------------------
//	ApcSystem::InitGameProcess
// ----------------------------------------------------
void			_System::_InitGameProcess() const
{
	// �ݒ��K�p����
	ApplicationConfig::Accept();
};

// ----------------------------------------------------
//	ApcSystem::RunStartProcess
// ----------------------------------------------------
void			_System::_RunStartProcess() const
{
	//	�N���D���s������A��D
	if(DxLib_Init() == -1){
		throw;
	}
	//	�`���𗠉�ʂɐݒ�D
	SetDrawScreen(DX_SCREEN_BACK);
};

// ----------------------------------------------------
//	ApcSystem::RunEndProcess
// ----------------------------------------------------
void			_System::_RunEndProcess() const
{
	// �I������D
	DxLib_End();
};

// ----------------------------------------------------
//	FrameCounter
// ----------------------------------------------------
//	FrameCounter::FrameCounter
// ----------------------------------------------------
				_FrameCounter::_FrameCounter()
{
	// �l������������
	_Value = 0;
	// �I��
	return;
}

// ----------------------------------------------------
//	FrameCounter::GetCount
// ----------------------------------------------------
double			_FrameCounter::GetCount()
{
	// �ԋp����
	return GetInstance()._Value;
}

// ----------------------------------------------------
//	FrameCounter::CountAdd
// ----------------------------------------------------
void			_FrameCounter::_CountAdd()
{
	// �l��1��������
	_Value++;
}