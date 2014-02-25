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
	auto ApcSys = __ApcSystem::GetInstance();
	// ----------------------------------------------------
	// Apocalypse�g�p�O�̏������s��
	ApcSys.ApcSetUp();
	// Apocalypse���g�p�ł���悤�ɂ���
	ApcSys.ApcStart();
	// �V�[�P���X�擾�֐������s
	auto StartSeq = ApplicationConfig::Sequence();
	// �������ʂ�NULL�Ȃ�
	if(!StartSeq){
		// �Q�[�����I��������D
		ApcSys.ApcEnd();
		// �I��
		return 0;
	}
	// �R���N�V�����ɒǉ�����
	__SequenceCollection::GetInstance().Add(StartSeq);
	// ���[�v�𔭐�������
	while(ApcSys.ApcProcess()){
		// �C�x���g�������s��
		__SequenceCollection::GetInstance().Top()->Events._ArrayCheck();
		// �t���[���`�揇�����ւ���D
		__FrameCollection::GetInstance().Sort();
		// �t���[�����܂Ƃ߂ĕ`��D
		__FrameCollection::GetInstance().DrawAll();
	}
	// �Q�[�����I��������D
	ApcSys.ApcEnd();
	// �֐����I��������D
	return 0;
}
