// --------------------------------------------------------
//	apxAppMain.cpp
// --------------------------------------------------------
#include "Apocalypse.hpp"

// --------------------------------------------------------
//	Main Function
// --------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �V�X�e���N���X�̃|�C���^���擾
	__ApcSystem		ApcSys = __ApcSystem::GetInstance();
	// �ŏ��ɓ��삳����V�[�P���X���ꎞ�ۑ�����
	Sequencer*		StartSeq = NULL;
	// ----------------------------------------------------
	// Apocalypse�g�p�O�̏������s��
	ApcSys.ApcSetUp(*ApcSys.GameSetting);
	// Apocalypse���g�p�ł���悤�ɂ���
	ApcSys.ApcStart();
	// �����V�[�P���X�擾�֐������s���C���ʂ�NULL�Ȃ�
	if((StartSeq = ApcSys.GameSetting->Sequence()) == NULL){
		// �I��
		return 0;
	}
	// �R���N�V�����ɒǉ�����
	__SequenceCollection::GetInstance().Add(StartSeq);
	// ���[�v�𔭐�������
	while(ApcSys.ApcProcess()){
		// �C�x���g�������s��
		__SequenceCollection::GetInstance().Top()->Events._ArrayCheck();
		// �t���[�����܂Ƃ߂ĕ`��D
		__FrameCollection::GetInstance().DrawAll();
	}
	// �Q�[�����I��������D
	ApcSys.ApcEnd();
	// �֐����I��������D
	return 0;
}
