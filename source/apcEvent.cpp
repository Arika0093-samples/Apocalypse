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
void			_EventHandleList::_ArrayCheck() const
{
	// �C�e���[�^��p�ӂ���
	auto Iterator = _EventItems.begin();
	// ------------------------------------
	// ���ԂɌ��Ă���
	while(Iterator != _EventItems.end()){
		// �擾����
		auto eHandle = *Iterator;
		// �C�x���g�����𖞂����Ă��邩�ǂ����m�F
		if(eHandle->Enable && eHandle->Type()){
			// OK�Ȃ�C�x���g�̊֐������s�D
			eHandle->Function();
		}
		// ���̂��̂�����
		Iterator++;
	}
}

// ----------------------------------------------------
//	EventHandleList::operator +=
// ----------------------------------------------------
EventHandle*	_EventHandleList::operator+=(EventHandle* Handle)
{
	// �����œn���ꂽ�n���h����shared_ptr�ɒ����ǉ�����
	*this += (std::shared_ptr<EventHandle>(Handle));
	return Handle;
}

// ----------------------------------------------------
//	EventHandleList::operator +=
// ----------------------------------------------------
std::shared_ptr<EventHandle>	
				_EventHandleList::operator+=(std::shared_ptr<EventHandle> Handle)
{
	// �����œn���ꂽ�n���h����ǉ�����
	_EventItems.push_back(Handle);
	return Handle;
}

// ----------------------------------------------------
//	EventHandleList::ToString
// ----------------------------------------------------
String			_EventHandleList::ToString() const
{
	// ����ԋp����
	return String() << _T("EventCount: ") << _EventItems.size();
}

// ----------------------------------------------------
//	EventHandleList::~EventHandleList
// ----------------------------------------------------
				_EventHandleList::~_EventHandleList()
{
	// ���g��S�ď���
	_EventItems.clear();
}

// ----------------------------------------------------
//	EventHandle
// ----------------------------------------------------
//	EventHandle::EventHandleList (Constructor)
// ----------------------------------------------------
				EventHandle::EventHandle()
{
	// �ڍהł��Ăяo��
	this->EventHandle::EventHandle([](){}, EventType::Process());
}
				
// ----------------------------------------------------
//	EventHandle::EventHandleList (Constructor)
// ----------------------------------------------------
				EventHandle::EventHandle(EventFunc Func)
{
	// �ڍהł��Ăяo��
	this->EventHandle::EventHandle(Func, EventType::Process());
}

// ----------------------------------------------------
//	EventHandle::EventHandle (Constructor)
// ----------------------------------------------------
				EventHandle::EventHandle(EventFunc Func, EventFlag Ty)
{
	// �֐����w��
	Function	= Func;
	Type		= Ty;
	// �n���h����L����
	Enable		= true;
	BeforeEvent	= nullptr;
}

// ----------------------------------------------------
//	EventHandle::ToString
// ----------------------------------------------------
String			EventHandle::ToString() const
{
	// ����ԋp����
	return String()
		<< _T("Enable: ") << Enable
		<< _T(", Function: ") << !Function.empty()
		<< _T(", Flag: ") << !Type.empty();
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
//	EventType::And
// ----------------------------------------------------
EventFlag		EventType::And(const EventFlag &A, const EventFlag &B)
{
	return [=](){ return A() && B(); };
}

// ----------------------------------------------------
//	EventType::Or
// ----------------------------------------------------
EventFlag		EventType::Or(const EventFlag &A, const EventFlag &B)
{
	return [=](){ return A() || B(); };
}

// ----------------------------------------------------
//	EventType::Nor
// ----------------------------------------------------
EventFlag		EventType::Nor(const EventFlag &A, const EventFlag &B)
{
	return [=](){ return !A() || !B(); };
}

// ----------------------------------------------------
//	EventType::Not
// ----------------------------------------------------
EventFlag		EventType::Not(const EventFlag &A, const EventFlag &B)
{
	return [=](){ return !A() && !B(); };
}

// ----------------------------------------------------
//	EventType::AnyPush
// ----------------------------------------------------
EventFlag		EventType::AnyPush()
{
	return [](){ return KeyBoard::AnyPushing();};
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
EventFlag		EventType::MouseOnFrame(Draw::_FrameBase &Frame)
{
	return([&](){
		// ���W�擾
		auto Area = Frame.GetFrameArea();
		// �ԋp
		return (
			Mouse::GetPosition().X >= Area.Location.X &&
			Mouse::GetPosition().X <= Area.Location.X + Area.Width &&
			Mouse::GetPosition().Y >= Area.Location.Y &&
			Mouse::GetPosition().Y <= Area.Location.Y + Area.Height);
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
EventFlag		EventType::KeyBoardPush(const _KeysData &CheckKey)
{
	return [=](){ return KeyBoard::PushStart(CheckKey);};
}

// ----------------------------------------------------
//	EventType::KeyBoardDown
// ----------------------------------------------------
EventFlag		EventType::KeyBoardDown(const _KeysData &CheckKey)
{
	return [=](){ return (KeyBoard::Pushing(CheckKey) >= 1);};
}

// ----------------------------------------------------
//	EventType::KeyBoardUp
// ----------------------------------------------------
EventFlag		EventType::KeyBoardUp(const _KeysData &CheckKey)
{
	return [=](){ return KeyBoard::OutStart(CheckKey);};
}

// ----------------------------------------------------
//	EventType::ColorChanged
// ----------------------------------------------------
EventFlag		EventType::ColorChanged(const Color &Cr)
{
	return PropertyChanged<Color>(Cr);
}
