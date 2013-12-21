// --------------------------------------------------------
//	apcEvent.cpp
// --------------------------------------------------------
//	apcEvent.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	EventHandleList
// ----------------------------------------------------
//	EventHandleList::EventArrayCheck
// ----------------------------------------------------
void			__EventHandleList::_ArrayCheck() const
{
	// イテレータを用意する
	std::list<std::shared_ptr<EventHandle>>::const_iterator Iterator = _EventItems.begin();
	// ------------------------------------
	// 例外を捉える
	try{
		// 順番に見ていく
		while(Iterator != _EventItems.end()){
			// 取得する
			EventHandle* eHandle = *Iterator;
			// イベント条件を満たしているかどうか確認
			if(eHandle->_ContinueFlag || eHandle->_Type()){
				// 起こってるならイベントの関数を実行．
				eHandle->_ContinueFlag = !eHandle->_Function();
			}
			// 次のものを見る
			Iterator++;
		}
	}
	// 捕捉
	catch(Sequencer* Sq){
		// 消す
		delete Sq;
	}
}

// ----------------------------------------------------
//	EventHandleList::operator +=
// ----------------------------------------------------
std::shared_ptr<EventHandle>
				__EventHandleList::operator+=(std::shared_ptr<EventHandle> Handle)
{
	// 引数で渡されたハンドルを追加する
	_EventItems.push_back(Handle);
	return Handle;
}

// ----------------------------------------------------
//	EventHandleList::~EventHandleList
// ----------------------------------------------------
				__EventHandleList::~__EventHandleList()
{
	// イテレータを用意する
	std::list<std::shared_ptr<EventHandle>>::const_iterator Iterator = _EventItems.begin();
	// ------------------------------------
	// 順番に見ていく
	while(Iterator != _EventItems.end()){
		// 取得する
		EventHandle* eHandle = *Iterator;
		// deleteする
		delete eHandle;
		// 次のものを見る
		Iterator++;
	}
	// 中身を全て消す
	_EventItems.clear();
}

// ----------------------------------------------------
//	EventHandle
// ----------------------------------------------------
//	EventHandle::EventHandleList (Constructor)
// ----------------------------------------------------
				EventHandle::EventHandle(EventFunc Func)
{
	// 関数を指定
	_Function		= Func;
	_Type			= EventType::Process();
	// 繰り返しフラグをfalseに指定する
	_ContinueFlag	= false;
}

// ----------------------------------------------------
//	EventHandle::EventHandleList (Constructor)
// ----------------------------------------------------
				EventHandle::EventHandle(EventFunc Func, EventFlag Ty)
{
	// 関数を指定
	_Function		= Func;
	_Type			= Ty;
	// 繰り返しフラグをfalseに指定する
	_ContinueFlag	= false;
}

// ----------------------------------------------------
//	EventType
// ----------------------------------------------------
//	EventType::Process
// ----------------------------------------------------
EventFlag		EventType::Process()
{
	return [](){ return true; };
}

// ----------------------------------------------------
//	EventType::MouseMove
// ----------------------------------------------------
EventFlag		EventType::MouseMove()
{
	return [](){ return Mouse::IsMove(); };
}

// ----------------------------------------------------
//	EventType::MouseOnArea
// ----------------------------------------------------
EventFlag		EventType::MouseOnArea(int X, int Y, int Margin)
{
	return MouseOnArea(X, Y, Margin, Margin);
}

// ----------------------------------------------------
//	EventType::MouseOnArea
// ----------------------------------------------------
EventFlag		EventType::MouseOnArea(Base::Point &Pt, int Margin)
{
	return MouseOnArea((int)Pt.X, (int)Pt.Y, Margin, Margin);
}

// ----------------------------------------------------
//	EventType::MouseOnArea
// ----------------------------------------------------
EventFlag		EventType::MouseOnArea(int X, int Y, int MarginWidth, int MarginHeight)
{
	return([&](){ return (
		Mouse::GetPosition().X >= X - MarginWidth &&
		Mouse::GetPosition().X <= X + MarginWidth &&
		Mouse::GetPosition().Y >= Y - MarginHeight &&
		Mouse::GetPosition().Y <= Y + MarginHeight);
	});
}

// ----------------------------------------------------
//	EventType::MouseOnArea
// ----------------------------------------------------
EventFlag		EventType::MouseOnArea(Base::Point &Pt, int MarginWidth, int MarginHeight)
{
	return MouseOnArea((int)Pt.X, (int)Pt.Y, MarginWidth, MarginHeight);
}

// ----------------------------------------------------
//	EventType::MouseOnFrame
// ----------------------------------------------------
EventFlag		EventType::MouseOnFrame(Draw::__FrameBase &Frame)
{
	return MouseOnArea(Frame.Points, Frame.GetWidth(), Frame.GetHeight());
}

// ----------------------------------------------------
//	EventType::MouseLClick
// ----------------------------------------------------
EventFlag		EventType::MouseLClick()
{
	return [](){ return Mouse::LeftPushStart; };
}

// ----------------------------------------------------
//	EventType::MouseRClick
// ----------------------------------------------------
EventFlag		EventType::MouseRClick()
{
	return [](){ return Mouse::RightPushStart; };
}

// ----------------------------------------------------
//	EventType::MouseLPush
// ----------------------------------------------------
EventFlag		EventType::MouseLPush()
{
	return [](){ return (Mouse::LeftPushing() >= 1);};
}

// ----------------------------------------------------
//	EventType::MouseRPush
// ----------------------------------------------------
EventFlag		EventType::MouseRPush()
{
	return [](){ return (Mouse::RightPushing() >= 1);};
}

// ----------------------------------------------------
//	EventType::MouseLUp
// ----------------------------------------------------
EventFlag		EventType::MouseLUp()
{
	return [](){ return Mouse::LeftOutStart();};
}

// ----------------------------------------------------
//	EventType::MouseRUp
// ----------------------------------------------------
EventFlag		EventType::MouseRUp()
{
	return [](){ return Mouse::RightOutStart();};
}

// ----------------------------------------------------
//	EventType::KeyBoardPush
// ----------------------------------------------------
EventFlag		EventType::KeyBoardPush(Keys CheckKey)
{
	return [&](){ return KeyBoard::PushStart(CheckKey);};
}

// ----------------------------------------------------
//	EventType::KeyBoardDown
// ----------------------------------------------------
EventFlag		EventType::KeyBoardDown(Keys CheckKey)
{
	return [&](){ return (KeyBoard::Pushing(CheckKey) >= 1);};
}

// ----------------------------------------------------
//	EventType::KeyBoardUp
// ----------------------------------------------------
EventFlag		EventType::KeyBoardUp(Keys CheckKey)
{
	return [&](){ return KeyBoard::OutStart(CheckKey);};
}

// ----------------------------------------------------
//	EventType::AnyPush
// ----------------------------------------------------
EventFlag		EventType::AnyPush()
{
	return [&](){ return KeyBoard::AnyPushing();};
}
