// --------------------------------------------------------
//	apcSequence.cpp
// --------------------------------------------------------
//	apcSequence.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.h"

// --------------------------------------------------------
//	Sequencer
// --------------------------------------------------------
//	Sequencer::Move
// --------------------------------------------------------
void			Sequencer::Move(std::shared_ptr<Sequencer> To)
{
	// �V�[�P���X�Ǘ��N���X�̍폜�֐����Ă�
	__SequenceCollection::GetInstance().Delete(this);
	// �n���ꂽ�l���V�[�P���X�ɒǉ�����
	Add(To);
	// ������
	throw this;
}

// --------------------------------------------------------
//	Sequencer::Add
// --------------------------------------------------------
void			Sequencer::Add(std::shared_ptr<Sequencer> To)
{
	// �V�[�P���X�Ǘ��N���X�̒ǉ��֐����Ă�
	__SequenceCollection::GetInstance().Add(To);
}

// --------------------------------------------------------
//	Sequencer::Delete
// --------------------------------------------------------
void			Sequencer::Delete()
{
	// �V�[�P���X�Ǘ��N���X�̍폜�֐����Ă�
	__SequenceCollection::GetInstance().Delete(this);
	// ������
	throw this;
}
