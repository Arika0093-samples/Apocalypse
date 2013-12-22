// --------------------------------------------------------
//	apcSequence.cpp
// --------------------------------------------------------
//	apcSequence.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.hpp"

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
}

// --------------------------------------------------------
//	Sequencer::Move
// --------------------------------------------------------
void			Sequencer::Move(Sequencer *To)
{
	this->Move(std::shared_ptr<Sequencer>(To));
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
//	Sequencer::Add
// --------------------------------------------------------
void			Sequencer::Add(Sequencer *To)
{
	this->Add(std::shared_ptr<Sequencer>(To));
}

// --------------------------------------------------------
//	Sequencer::Delete
// --------------------------------------------------------
void			Sequencer::Delete()
{
	// �V�[�P���X�Ǘ��N���X�̍폜�֐����Ă�
	__SequenceCollection::GetInstance().Delete(this);
}
