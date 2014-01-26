// --------------------------------------------------------
//	apcEvent.cpp
// --------------------------------------------------------
//	apcEvent.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	EventHandleList
// ----------------------------------------------------
//	EventHandleList::EventArrayCheck
// ----------------------------------------------------
void			__EventHandleList::_ArrayCheck() const
{
	// �C�e���[�^��p�ӂ���
	auto Iterator = _EventItems.begin();
	// ------------------------------------
	// ���ԂɌ��Ă���
	while(Iterator != _EventItems.end()){
		// �擾����
		auto eHandle = *Iterator;
		// �C�x���g�����𖞂����Ă��邩�ǂ����m�F
		if(eHandle->_Type()){
			// �N�����Ă�Ȃ�C�x���g�̊֐������s�D
			eHandle->_Function();
		}
		// ���̂��̂�����
		Iterator++;
	}
}

// ----------------------------------------------------
//	EventHandleList::operator +=
// ----------------------------------------------------
std::shared_ptr<EventHandle>
				__EventHandleList::operator+=(std::shared_ptr<EventHandle> Handle)
{
	// �����œn���ꂽ�n���h����ǉ�����
	_EventItems.push_back(Handle);
	return Handle;
}

// ----------------------------------------------------
//	EventHandleList::ToString
// ----------------------------------------------------
String			__EventHandleList::ToString() const
{
	// ����ԋp����
	return String() << _T("EventCount: ") << _EventItems.size();
}

// ----------------------------------------------------
//	EventHandleList::~EventHandleList
// ----------------------------------------------------
				__EventHandleList::~__EventHandleList()
{
	// ���g��S�ď���
	_EventItems.clear();
}

// ----------------------------------------------------
//	EventHandle
// ----------------------------------------------------
//	EventHandle::EventHandleList (Constructor)
// ----------------------------------------------------
				EventHandle::EventHandle(EventFunc Func)
{
	// �֐����w��
	_Function		= Func;
	_Type			= EventType::Process();
	// �J��Ԃ��t���O��false�Ɏw�肷��
}

// ----------------------------------------------------
//	EventHandle::EventHandleList (Constructor)
// ----------------------------------------------------
				EventHandle::EventHandle(EventFunc Func, EventFlag Ty)
{
	// �֐����w��
	_Function		= Func;
	_Type			= Ty;
}

// ----------------------------------------------------
//	EventHandle::ToString
// ----------------------------------------------------
String			EventHandle::ToString() const
{
	// ����ԋp����
	return String() << _T("Function: ") << !_Function.empty()
		<< _T(", Flag: ") << _Type.empty();
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
EventFlag		EventType::MouseOnArea(Value::Point &Pt, int Margin)
{
	return MouseOnArea(Pt, Margin, Margin);
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
EventFlag		EventType::MouseOnArea(Value::Point &Pt, int MarginWidth, int MarginHeight)
{
	return([&](){ return (
		Mouse::GetPosition().X >= Pt.X - MarginWidth &&
		Mouse::GetPosition().X <= Pt.X + MarginWidth &&
		Mouse::GetPosition().Y >= Pt.Y - MarginHeight &&
		Mouse::GetPosition().Y <= Pt.Y + MarginHeight);
	});
}

// ----------------------------------------------------
//	EventType::MouseOnFrame
// ----------------------------------------------------
EventFlag		EventType::MouseOnFrame(Draw::__FrameBase &Frame)
{
	return([&](){
		// ���W�擾
		Point Pt = Frame.GetLocation();
		// �ԋp
		return (
			Mouse::GetPosition().X >= Pt.X &&
			Mouse::GetPosition().X <= Pt.X + Frame.GetWidth() &&
			Mouse::GetPosition().Y >= Pt.Y &&
			Mouse::GetPosition().Y <= Pt.Y + Frame.GetHeight());
	});
}

// ----------------------------------------------------
//	EventType::MouseLClick
// ----------------------------------------------------
EventFlag		EventType::MouseLClick()
{
	return [](){ return Mouse::LeftPushStart(); };
}

// ----------------------------------------------------
//	EventType::MouseRClick
// ----------------------------------------------------
EventFlag		EventType::MouseRClick()
{
	return [](){ return Mouse::RightPushStart(); };
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
	return [=](){ return KeyBoard::PushStart(CheckKey);};
}

// ----------------------------------------------------
//	EventType::KeyBoardDown
// ----------------------------------------------------
EventFlag		EventType::KeyBoardDown(Keys CheckKey)
{
	return [=](){ return (KeyBoard::Pushing(CheckKey) >= 1);};
}

// ----------------------------------------------------
//	EventType::KeyBoardUp
// ----------------------------------------------------
EventFlag		EventType::KeyBoardUp(Keys CheckKey)
{
	return [=](){ return KeyBoard::OutStart(CheckKey);};
}

// ----------------------------------------------------
//	EventType::AnyPush
// ----------------------------------------------------
EventFlag		EventType::AnyPush()
{
	return [](){ return KeyBoard::AnyPushing();};
}
