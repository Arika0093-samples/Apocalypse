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
	auto ApcSys = _System::GetInstance();
	// ----------------------------------------------------
	// Apocalypse�g�p�O�̏������s��
	ApcSys.ApcSetUp();
	// Apocalypse���g�p�ł���悤�ɂ���
	ApcSys.ApcStart();
	// �V�[�P���X�擾�֐������s
	auto StartSeq = ( !ApplicationConfig::Sequence.empty() ? ApplicationConfig::Sequence() : nullptr);
	// �������ʂ�NULL�Ȃ�
	if(StartSeq == nullptr){
		// �Q�[�����I��������D
		ApcSys.ApcEnd();
		// �I��
		return 0;
	}
	// �R���N�V�����ɒǉ�����
	_SequenceCollection::GetInstance().Add(std::shared_ptr<Sequencer>(StartSeq));
	// ���[�v�𔭐�������
	while(ApcSys.ApcProcess()){
		// �C�x���g�������s��
		_SequenceCollection::GetInstance().Top()->Events._ArrayCheck();
		// �t���[���`�揇�����ւ���D
		_FrameCollection::GetInstance().Sort();
		// �t���[�����܂Ƃ߂ĕ`��D
		_FrameCollection::GetInstance().DrawAll();
	}
	// �Q�[�����I��������D
	ApcSys.ApcEnd();
	// �֐����I��������D
	return 0;
}
