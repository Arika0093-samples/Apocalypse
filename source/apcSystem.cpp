// --------------------------------------------------------
//	apcSystem.cpp
// --------------------------------------------------------
//	apcSystem.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	GameSetting
// ----------------------------------------------------
//	GameSetting::GameSetting (Constructor)
// ----------------------------------------------------
				__ApcSetting::__ApcSetting()
{
	// �t�H���g���擾�Ɏg�p����
	LOGFONT lgFont;
	// ------------------------------------------------
	// ���Z�b�g
	memset(&lgFont, NULL, sizeof(LOGFONT));
	// �V�X�e���̃t�H���g���擾����
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lgFont, 0);
	// �e��X�e�[�^�X�̏�����
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
	// DEBUG�̒�`�ɂ����DebugMode�̒l��ς���D
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
	// Locale�����݂̕W������Ŏw�肷��
	_tsetlocale(LC_ALL, _T(""));
	// �ۑ��̈��V�K�쐬����
	GameSetting = New( __ApcSetting);
	// �J�����g�f�B���N�g�����w�肷��
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
bool			__ApcSystem::ApcStart() const
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
bool			__ApcSystem::ApcProcess() const
{
	// ����ʂ�\��ʂɔ��f�D
	ScreenFlip();
	// ����ʂɕ`�悳��Ă�����e�������D
	ClearDrawScreen();
	// �����V�[�P���X����Ȃ��
	if(__SequenceCollection::GetInstance().Top() == NULL){
		// �I���D
		return false;
	}
	// �I�����֐����o�^����Ă��āC�I���R�}���h�������Ă����Ȃ�
	if(!GameSetting->ExitFunction.empty() && GetWindowUserCloseFlag(TRUE) == TRUE){
		// �֐������s�����߂�l��TRUE�Ȃ�
		if((int)GameSetting->ExitFunction() == TRUE){
			// �I���D
			return false;
		}
	}
	// �~�{�^����������Ă�����
	if(ProcessMessage() == 0){
		// �I���D
		return false;
	}
	// �J�E���^�̒l�𑝉������Ă����D
	__FrameCounter::GetInstance()._CountAdd();
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
void			__ApcSystem::ApcEnd() const
{
	//	�I���v���Z�X���R�[������
	_RunEndProcess();
};

// ----------------------------------------------------
//	ApcSystem::InitGameProcess
// ----------------------------------------------------
void			__ApcSystem::_InitGameProcess() const
{
	// ���O�쐬���邩�ǂ����D
	SetOutApplicationLogValidFlag(GameSetting->DebugMode);
	// �񓯊��ǂݍ��݂��邩�ǂ����D
	SetUseASyncLoadFlag(GameSetting->ASyncLoad);
	// �E�B���h�E�̃^�C�g���ύX�D
	SetMainWindowText(GameSetting->Title);
	// �E�B���h�E�̃N���X���ύX�D
	SetMainWindowClassName(GameSetting->ClassName);
	// �A�C�R���ύX�D
	SetWindowIconID(1);
	// GDI�`��̃t���O���w�肷��
	SetUseGDIFlag(GameSetting->GDIDraw);
	// ��d�N���̃t���O���w�肷��D
	SetDoubleStartValidFlag(GameSetting->DualBoot);
	// ��ɓ��삳���邩�ǂ����̃t���O���w�肷��D
	SetAlwaysRunFlag(GameSetting->ActiveAll);
	// �E�B���h�E���[�h��ύX�D
	ChangeWindowMode(GameSetting->WindowMode);
	// �E�B���h�E�T�C�Y�̕ύX�D
	SetWindowSize(GameSetting->Width, GameSetting->Height);
	// �`��E�C���h�E�T�C�Y�̕ύX�D
	SetGraphMode(GameSetting->Width, GameSetting->Height, 32, GameSetting->Refresh);
};

// ----------------------------------------------------
//	ApcSystem::RunStartProcess
// ----------------------------------------------------
void			__ApcSystem::_RunStartProcess() const
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
void			__ApcSystem::_RunEndProcess() const
{
	// �I������D
	DxLib_End();
};
