// --------------------------------------------------------
//	apcEvent.h
// --------------------------------------------------------
//	�C�x���g�n���h���֘A�̃N���X���L�ڂ���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <list>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <include/apcClassBase.hpp>
#include <include/apcInput.hpp>

// --------------------------------------------------------
//	define�}�N�����g�p����
// --------------------------------------------------------
//	�C�x���g���X�g�ɃN���X�����o�֐���ǉ�����}�N���D
#define ClassFunc(FuncName)		boost::bind(&FuncName, this)

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Event)
// --------------------------------------------------------
namespace Apocalypse
{
	// ------------------------------------------------
	//	Front Declaration
	// ------------------------------------------------
	namespace Draw
	{
		class				__FrameBase;
	};

	namespace Event
	{
		// ------------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class				EventHandle;

		// ------------------------------------------------
		//	Typedef
		// ------------------------------------------------
		typedef				boost::function<bool()>		EventFunc, EventFlag;

		///	<summary>
		///		�C�x���g�̒ǉ��E�폜�E�Ǘ����s���N���X�D
		///	</summary>
		class __EventHandleList : public Base::__ApcInside
		{
		public:
			/// <summary>
			///		�o�^���ꂽ�C�x���g�n���h���̊֐������s���邩�ǂ����m�F����D
			/// </summary>
			void			_ArrayCheck() const;
			/// <summary>
			///		�C�x���g�n���h���𖖔��ɒǉ�����D
			/// </summary>
			/// <param name = "Handle">
			///		�ǉ�����Ώۂ̃C�x���g�D
			/// </param>
			std::shared_ptr<EventHandle>
							operator+=(std::shared_ptr<EventHandle> Handle);
			/// <summary>
			///		�f�X�g���N�^�D
			/// </summary>
			virtual			~__EventHandleList();
		private:
			/// <summary>
			///		������Z�q�𖳌���
			/// </summary>
			void			operator=(__EventHandleList){}
			/// <summary>
			///		�C�x���g���Ǘ�����R���e�i�D
			/// </summary>
			std::list<std::shared_ptr<EventHandle>>
							_EventItems;
		};

		///	<summary>
		///		�C�x���g�̊�N���X�D���̃C�x���g���̂͐����ł��Ȃ��D
		///	</summary>
		class EventHandle : public Base::__ApcBase
		{
			friend class	__EventHandleList;
		public:
			/// <summary>
			///		<para>EventType���w�肵�Ȃ��ŃR���X�g���N�^�D</para>
			///		<para>���̃R���X�g���N�^�ł͖��t���[���֐������s����܂�(EventList::Process()�Ɠ���)�D</para>
			/// </summary>
			/// <param name = "Func">
			///		���s����֐��D�N���X�����o�̊֐��̏ꍇ��boost::bind�֐����g�p����K�v������܂��D
			/// </param>
							EventHandle(EventFunc Func);
			/// <summary>
			///		EventType���w�肷��ŃR���X�g���N�^�D
			/// </summary>
			/// <param name = "Func">
			///		���s����֐��D�N���X�����o�̊֐��̏ꍇ��boost::bind�֐����g�p����K�v������܂��D
			/// </param>
			/// <param name = "Ty">
			///		<para>����̊֐��D�N���X�����o�̊֐��̏ꍇ��boost::bind�֐����g�p����K�v������܂��D</para>
			///		<para>boost::bind�֐����g�p���邱�ƂŁC�������������֐������s�����邱�Ƃ��ł��܂��D</para>
			///		<para>�܂��CEventType�N���X�̊֐��������Ɏw�肷�邱�Ƃ��ł��܂��D</para>
			/// </param>
							EventHandle(EventFunc Func, EventFlag Ty);
		private:
			/// <summary>
			///		�C�x���g�֐��D���̊֐����Ŋe�폈�����s���D
			/// </summary>
			EventFunc		_Function;
			/// <summary>
			///		�C�x���g����֐��D���̊֐����Ŋe�픻����s���D
			/// </summary>
			EventFlag		_Type;
			/// <summary>
			///		�C�x���g���J��Ԃ����s�ƂȂ��Ă��邩�ǂ����D
			/// </summary>
			bool			_ContinueFlag;
		};

		///	<summary>
		///		�C�x���g�����̈ꗗ�N���X�D
		///	</summary>
		class EventType : public Base::__ApcEnumeration
		{
		public:
			/// <summary>
			///		���TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	Process();
			/// <summary>
			///		�}�E�X���������ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	MouseMove();
			/// <summary>
			///		�}�E�X���w�肵���̈�ɑ��݂���ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "X">
			///		�w�肷��̈�̒��S������X���W���w�肵�܂��D
			/// </param>
			/// <param name = "Y">
			///		�w�肷��̈�̒��S������Y���W���w�肵�܂��D
			/// </param>
			/// <param name = "Margin">
			///		�w�肷��̈�̒��S��������̘g�̑傫�����w�肵�܂��D
			/// </param>
			static EventFlag	MouseOnArea(int X, int Y, int Margin);
			/// <summary>
			///		�}�E�X���w�肵���̈�ɑ��݂���ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "Pt">
			///		�w�肷��̈�̒��S�����̍��W���w�肵�܂��D
			/// </param>
			/// <param name = "Margin">
			///		�w�肷��̈�̒��S��������̘g�̑傫�����w�肵�܂��D
			/// </param>
			static EventFlag	MouseOnArea(Base::Point &Pt, int Margin);
			/// <summary>
			///		�}�E�X���w�肵���̈�ɑ��݂���ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "X">
			///		�w�肷��̈�̒��S������X���W���w�肵�܂��D
			/// </param>
			/// <param name = "Y">
			///		�w�肷��̈�̒��S������Y���W���w�肵�܂��D
			/// </param>
			/// <param name = "MarginWidth">
			///		�w�肷��̈�̒��S��������̘g�̉������̑傫�����w�肵�܂��D
			/// </param>
			/// <param name = "MarginHeight">
			///		�w�肷��̈�̒��S��������̘g�̏c�����̑傫�����w�肵�܂��D
			/// </param>
			static EventFlag	MouseOnArea(int X, int Y, int MarginWidth, int MarginHeight);
			/// <summary>
			///		�}�E�X���w�肵���̈�ɑ��݂���ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "Pt">
			///		�w�肷��̈�̒��S�����̍��W���w�肵�܂��D
			/// </param>
			/// <param name = "MarginWidth">
			///		�w�肷��̈�̒��S��������̘g�̉������̑傫�����w�肵�܂��D
			/// </param>
			/// <param name = "MarginHeight">
			///		�w�肷��̈�̒��S��������̘g�̏c�����̑傫�����w�肵�܂��D
			/// </param>
			static EventFlag	MouseOnArea(Base::Point &Pt, int MarginWidth, int MarginHeight);
			/// <summary>
			///		�}�E�X���w�肵���t���[����ɗ̈�ɑ��݂���ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "Frame">
			///		�t���[�����w�肵�܂��D
			/// </param>
			static EventFlag	MouseOnFrame(Draw::__FrameBase &Frame);
			/// <summary>
			///		�}�E�X�̍��{�^�����N���b�N���ꂽ�ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	MouseLClick();
			/// <summary>
			///		�}�E�X�̉E�{�^�����N���b�N���ꂽ�ۂ�TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	MouseRClick();
			/// <summary>
			///		�}�E�X�̍��{�^����������Ă����TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	MouseLPush();
			/// <summary>
			///		�}�E�X�̉E�{�^����������Ă����TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	MouseRPush();
			/// <summary>
			///		�}�E�X�̍��{�^���������ꂽ�u�Ԃ̂݊�TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	MouseLUp();
			/// <summary>
			///		�}�E�X�̉E�{�^���������ꂽ�u�Ԃ̂݊�TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	MouseRUp();
			/// <summary>
			///		�����Ɏw�肵���L�[�������ꂽ�u�Ԃ̂�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "CheckKey">
			///		�m�F����L�[���w�肵�܂��D
			/// </param>
			static EventFlag	KeyBoardPush(Input::Keys CheckKey);
			/// <summary>
			///		�����Ɏw�肵���L�[�������ꂽ�u�Ԃ̂�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "CheckKey">
			///		�m�F����L�[���w�肵�܂��D
			/// </param>
			static EventFlag	KeyBoardDown(Input::Keys CheckKey);
			/// <summary>
			///		�����Ɏw�肵���L�[�������ꂽ�u�Ԃ̂�TRUE��Ԃ��܂��D
			/// </summary>
			/// <param name = "CheckKey">
			///		�m�F����L�[���w�肵�܂��D
			/// </param>
			static EventFlag	KeyBoardUp(Input::Keys CheckKey);
			/// <summary>
			///		�L�[���}�E�X�������ꂽ�ꍇ��TRUE��Ԃ��܂��D
			/// </summary>
			static EventFlag	AnyPush();
		};
	}
}
