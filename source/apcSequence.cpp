// --------------------------------------------------------
//	apcSequence.cpp
// --------------------------------------------------------
//	apcSequence.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.hpp"

// --------------------------------------------------------
//	Sequencer
// --------------------------------------------------------
//	Sequencer::Sequencer(Constructer)
// --------------------------------------------------------
				Sequencer::Sequencer()
{
	// DrawOrderを0に初期化
	_DrawOrder = 0;
}

// --------------------------------------------------------
//	Sequencer::Move
// --------------------------------------------------------
void			Sequencer::Move(std::shared_ptr<Sequencer> To)
{
	// シーケンス管理クラスの削除関数を呼ぶ
	__SequenceCollection::GetInstance().Delete(this);
	// 描画順を指定する
	To->_DrawOrder = __SequenceCollection::GetInstance().Size();
	// 渡された値をシーケンスに追加する
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
	// 描画順を指定する
	To->_DrawOrder = __SequenceCollection::GetInstance().Size();
	// シーケンス管理クラスの追加関数を呼ぶ
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
	// シーケンス管理クラスの削除関数を呼ぶ
	__SequenceCollection::GetInstance().Delete(this);
}
