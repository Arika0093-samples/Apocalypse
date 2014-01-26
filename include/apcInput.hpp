// --------------------------------------------------------
//	apcInput.h
// --------------------------------------------------------
//	���͂��Ǘ�����N���X���쐬����D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <set>
#include <include/apcClassBase.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Input)
// --------------------------------------------------------
namespace Apocalypse
{
	// ----------------------------------------------------
	//	Input���O��ԓ��̃N���X���L��
	// ----------------------------------------------------
	namespace Input
	{
		// ------------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class Keys;

		///	<summary>
		///		�L�[�����Ǘ�����p�̃N���X�D
		///	</summary>
		/// <remarks>
		///		Key::XX�̌`�ŃL�[�����擾�ł��܂��D���̃N���X��singleton�ł��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// ����Z�L�[��������Ă����
		///		if(Key::Pushing(KeyList::Z)){
		///			�c
		///		}
		///		// ����X�L�[�������ꂽ�u�ԂȂ��
		///		if(Key::OutStart(KeyList::X)){
		///			�c
		///		}
		///		</code>
		/// </example>
		class KeyBoard : public Template::__Singleton<KeyBoard>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<KeyBoard>;
		public:
			/// <summary>
			///		�����̃L�[/�}�E�X��������Ă��邩�ǂ����̏����擾����D
			/// </summary>
			static bool			AnyPushing();
			/// <summary>
			///		<para>�w�肵���L�[��������Ă��邩�ǂ����̏����擾����D</para>
			///		<para>0�Ȃ牟����Ă��Ȃ��D1�ȏ�Ȃ牟����Ă��鎞�ԁD</para>
			/// </summary>
			/// <param name = "TargetKey">
			///		�擾����Ώۂ̃L�[�DKeyList�Œ�`���ꂽ�l���g�p���ĉ������D
			/// </param>
			static int			Pushing(Keys TargetKey);
			/// <summary>
			///		�w�肵���L�[�����̃t���[���ŏ��߂ĉ����ꂽ���ǂ����̏����擾����D
			/// </summary>
			/// <param name = "TargetKey">
			///		�擾����Ώۂ̃L�[�DKeyList�Œ�`���ꂽ�l���g�p���ĉ������D
			/// </param>
			static bool			PushStart(Keys TargetKey);
			/// <summary>
			///		�w�肵���L�[�����̃t���[���ŏ��߂ė����ꂽ���ǂ����̏����擾����D
			/// </summary>
			/// <param name = "TargetKey">
			///		�擾����Ώۂ̃L�[�DKeyList�Œ�`���ꂽ�l���g�p���ĉ������D
			/// </param>
			static bool			OutStart(Keys TargetKey);
			/// <summary>
			///		�L�[�̉�����Ă����Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String
								ToString() const;
			/// <summary>
			///		�L�[�̏�Ԃ��X�V����D1�t���[����1�x�Ăяo���D
			/// </summary>
			void				_CheckKeyEvent();
		private:
			/// <summary>
			///		Constructor
			/// </summary>
								KeyBoard();
			/// <summary>
			///		�L�[�̓��͏���ۑ�����ϐ��D
			/// </summary>
			int					_KeyInput[256];
		};

		///	<summary>
		///		�}�E�X�����Ǘ�����p�̃N���X�D
		///	</summary>
		/// <remarks>
		///		Mouse::XX�̌`�ŃL�[�����擾�ł��܂��D���̃N���X��singleton�ł��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// �����}�E�X��������Ă����
		///		if(Mouse::Pushing()){
		///			�c
		///		}
		///		// �����}�E�X�������ꂽ�u�ԂȂ��
		///		if(Mouse::OutStart()){
		///			�c
		///		}
		///		</code>
		/// </example>
		class Mouse : public Template::__Singleton<Mouse>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<Mouse>;
		public:
			/// <summary>
			///		<para>�}�E�X��������Ă��邩�ǂ����̏����擾����D</para>
			///		<para>0�Ȃ牟����Ă��Ȃ��D1�ȏ�Ȃ牟����Ă��鎞�ԁD</para>
			/// </summary>
			static int			LeftPushing();
			/// <summary>
			///		�}�E�X�����̃t���[���ŏ��߂ĉ����ꂽ���ǂ����̏����擾����D
			/// </summary>
			static bool			LeftPushStart();
			/// <summary>
			///		�}�E�X�����̃t���[���Ŏn�߂ė����ꂽ���ǂ����̏����擾����D
			/// </summary>
			static bool			LeftOutStart();
			/// <summary>
			///		<para>�}�E�X��������Ă��邩�ǂ����̏����擾����D</para>
			///		<para>0�Ȃ牟����Ă��Ȃ��D1�ȏ�Ȃ牟����Ă��鎞�ԁD</para>
			/// </summary>
			static int			RightPushing();
			/// <summary>
			///		�}�E�X�����̃t���[���ŏ��߂ĉ����ꂽ���ǂ����̏����擾����D
			/// </summary>
			static bool			RightPushStart();
			/// <summary>
			///		�}�E�X�����̃t���[���Ŏn�߂ė����ꂽ���ǂ����̏����擾����D
			/// </summary>
			static bool			RightOutStart();
			/// <summary>
			///		�}�E�X�̈ʒu���擾����D
			/// </summary>
			static bool			IsMove();
			/// <summary>
			///		�}�E�X�̈ʒu���擾����D
			/// </summary>
			static Value::Point	GetPosition();
			/// <summary>
			///		�}�E�X�̈ʒu��ݒ肷��D
			/// </summary>
			/// <param name = "X">
			///		�w�肷��X���W�D
			/// </param>
			/// <param name = "Y">
			///		�w�肷��Y���W�D
			/// </param>
			static void			SetPosition(int X, int Y);
			/// <summary>
			///		�N���X�̏��𕶎���Ŏ擾����D
			/// </summary>
			virtual Value::String
								ToString() const;
			/// <summary>
			///		�}�E�X�̏�Ԃ��X�V����D1�t���[����1�x�Ăяo���D
			/// </summary>
			void				_CheckMouseEvent();
		private:
			/// <summary>
			///		�R���X�g���N�^
			/// </summary>
								Mouse();
			/// <summary>
			///		<para>(��)�}�E�X���͂̎��Ԃ��擾���܂��D</para>
			///		<para>���̒l: ������Ă��鎞�� / ���̒l: ������Ă��鎞��</para>
			/// </summary>
			int					_MousePushTimeLeft;
			/// <summary>
			///		<para>(�E)�}�E�X���͂̎��Ԃ��擾���܂��D</para>
			///		<para>���̒l: ������Ă��鎞�� / ���̒l: ������Ă��鎞��</para>
			/// </summary>
			int					_MousePushTimeRight;
			/// <summary>
			///		�}�E�X�̈ʒu���擾����
			/// </summary>
			Value::Point		_MouseLocation;
			/// <summary>
			///		1�t���[���O�̃}�E�X�̈ʒu���擾����
			/// </summary>
			Value::Point		_MouseBeforeLoc;
		};

		///	<summary>
		///		�L�[�����Ǘ�����N���X�D
		///	</summary>
		/// <remarks>
		///		�L�[�̏�Ԃ��擾����֐��̈����Ɏg�p���܂��D
		/// </remarks>
		class Keys : public virtual Base::__ApcBase
		{
		public:
			///	<summary>
			///		�����L�[�Ƃ��ē��ɉ��������Ȃ�Keys�N���X�̃R���X�g���N�^�D
			///	</summary>
								Keys();
			///	<summary>
			///		�����L�[�Ƃ��Ĉ����Ɏw�肳�ꂽ�L�[������Keys�N���X�̃R���X�g���N�^�D
			///	</summary>
			///	<param name = "FstKey">
			///		�����L�[�D
			///	</param>
								Keys(int FstKey);
			///	<summary>
			///		�����L�[�Ƃ��Ĉ����Ɏw�肳�ꂽ2�̃L�[������Keys�N���X�̃R���X�g���N�^�D
			///	</summary>
			///	<param name = "FstKey_1">
			///		�����L�[����1�D
			///	</param>
			///	<param name = "FstKey_2">
			///		�����L�[����2�D
			///	</param>
								Keys(int FstKey_1, int FstKey_2);
			///	<summary>
			///		�����L�[�Ƃ��Ĉ����Ɏw�肳�ꂽ�����̃L�[������Keys�N���X�̃R���X�g���N�^�D
			///	</summary>
			///	<param name = "FstKeys">
			///		�����̏����L�[�D
			///	</param>
			///	<param name = "Size">
			///		�o�^����L�[�̌��D
			///	</param>
								Keys(int FstKey[], size_t Size);
			///	<summary>
			///		�f�X�g���N�^�D
			///	</summary>
								~Keys(){}
			///	<summary>
			///		2�̃L�[�̏�Ԃ��r����֐��D
			///	</summary>
			///	<param name = "KeysList">
			///		��r����L�[�̏�ԃN���X�D
			///	</param>
			bool				Compare(const Keys &KeysList) const;
			///	<summary>
			///		�L�[�ǉ���operator�D
			///	</summary>
			///	<param name = "KeysList">
			///		�ǉ�����L�[�̏�ԃN���X�D
			///	</param>
			Keys&				operator+(const Keys &KeysList) const;
			///	<summary>
			///		�L�[�폜��operator�D
			///	</summary>
			///	<param name = "KeysList">
			///		�폜����L�[�̏�ԃN���X�D
			///	</param>
			Keys&				operator-(const Keys &KeysList) const;
			///	<summary>
			///		�L�[�ǉ���operator�D
			///	</summary>
			///	<param name = "KeysList">
			///		�ǉ�����L�[�̏�ԃN���X�D
			///	</param>
			Keys&				operator+=(const Keys &KeysList);
			///	<summary>
			///		�L�[�폜��operator�D
			///	</summary>
			///	<param name = "KeysList">
			///		�폜����L�[�̏�ԃN���X�D
			///	</param>
			Keys&				operator-=(const Keys &KeysList);
			///	<summary>
			///		��r��operator�D
			///	</summary>
			///	<param name = "Key">
			///		��r����L�[�̃R�[�h�D
			///	</param>
			bool				operator&&(int Key) const;
			///	<summary>
			///		��r��operator�D
			///	</summary>
			///	<param name = "KeysList">
			///		��r����L�[�̏�ԃN���X�D
			///	</param>
			bool				operator==(const Keys &KeysList) const;
			///	<summary>
			///		�o�^�L�[�T�C�Y���擾����D
			///	</summary>
			unsigned int		_Size() const;
			///	<summary>
			///		�o�^�L�[�̔ԍ����擾����D
			///	</summary>
			int					_Get(int Val) const;
		private:
			///	<summary>
			///		�m�F����L�[�̎�ށD
			///	</summary>
			std::set<int>		_CheckKeyList;
		};

		///	<summary>
		///		�L�[�{�[�h�̑Ή�������񋓂����N���X�D
		///	</summary>
		class Key : public virtual Base::__ApcEnumeration
		{
		public:
			///	<summary>
			///		�L�[�{�[�h��A�L�[�D
			///	</summary>
			static const Keys	A;
			///	<summary>
			///		�L�[�{�[�h��B�L�[�D
			///	</summary>
			static const Keys	B;
			///	<summary>
			///		�L�[�{�[�h��C�L�[�D
			///	</summary>
			static const Keys	C;
			///	<summary>
			///		�L�[�{�[�h��D�L�[�D
			///	</summary>
			static const Keys	D;
			///	<summary>
			///		�L�[�{�[�h��E�L�[�D
			///	</summary>
			static const Keys	E;
			///	<summary>
			///		�L�[�{�[�h��F�L�[�D
			///	</summary>
			static const Keys	F;
			///	<summary>
			///		�L�[�{�[�h��G�L�[�D
			///	</summary>
			static const Keys	G;
			///	<summary>
			///		�L�[�{�[�h��H�L�[�D
			///	</summary>
			static const Keys	H;
			///	<summary>
			///		�L�[�{�[�h��I�L�[�D
			///	</summary>
			static const Keys	I;
			///	<summary>
			///		�L�[�{�[�h��J�L�[�D
			///	</summary>
			static const Keys	J;
			///	<summary>
			///		�L�[�{�[�h��K�L�[�D
			///	</summary>
			static const Keys	K;
			///	<summary>
			///		�L�[�{�[�h��L�L�[�D
			///	</summary>
			static const Keys	L;
			///	<summary>
			///		�L�[�{�[�h��M�L�[�D
			///	</summary>
			static const Keys	M;
			///	<summary>
			///		�L�[�{�[�h��N�L�[�D
			///	</summary>
			static const Keys	N;
			///	<summary>
			///		�L�[�{�[�h��O�L�[�D
			///	</summary>
			static const Keys	O;
			///	<summary>
			///		�L�[�{�[�h��P�L�[�D
			///	</summary>
			static const Keys	P;
			///	<summary>
			///		�L�[�{�[�h��Q�L�[�D
			///	</summary>
			static const Keys	Q;
			///	<summary>
			///		�L�[�{�[�h��R�L�[�D
			///	</summary>
			static const Keys	R;
			///	<summary>
			///		�L�[�{�[�h��S�L�[�D
			///	</summary>
			static const Keys	S;
			///	<summary>
			///		�L�[�{�[�h��T�L�[�D
			///	</summary>
			static const Keys	T;
			///	<summary>
			///		�L�[�{�[�h��U�L�[�D
			///	</summary>
			static const Keys	U;
			///	<summary>
			///		�L�[�{�[�h��V�L�[�D
			///	</summary>
			static const Keys	V;
			///	<summary>
			///		�L�[�{�[�h��W�L�[�D
			///	</summary>
			static const Keys	W;
			///	<summary>
			///		�L�[�{�[�h��X�L�[�D
			///	</summary>
			static const Keys	X;
			///	<summary>
			///		�L�[�{�[�h��Y�L�[�D
			///	</summary>
			static const Keys	Y;
			///	<summary>
			///		�L�[�{�[�h��Z�L�[�D
			///	</summary>
			static const Keys	Z;
			///	<summary>
			///		�L�[�{�[�h��Enter�L�[�D
			///	</summary>
			static const Keys	Enter;
			///	<summary>
			///		�L�[�{�[�h��Esc�L�[�D
			///	</summary>
			static const Keys	Escape;
			///	<summary>
			///		�L�[�{�[�h��Tab�L�[�D
			///	</summary>
			static const Keys	Tab;
			///	<summary>
			///		�L�[�{�[�h�̗�Shift�L�[�D
			///	</summary>
			static const Keys	Shift;
			///	<summary>
			///		�L�[�{�[�h�̗�Ctrl�L�[�D
			///	</summary>
			static const Keys	Control;
			///	<summary>
			///		�L�[�{�[�h�̗�Alt�L�[�D
			///	</summary>
			static const Keys	Alt;
			///	<summary>
			///		�L�[�{�[�h��Space�L�[�D
			///	</summary>
			static const Keys	Space;
			///	<summary>
			///		�L�[�{�[�h��BackSpace�L�[�D
			///	</summary>
			static const Keys	BackSpace;
			///	<summary>
			///		�L�[�{�[�h��Delete�L�[�D
			///	</summary>
			static const Keys	Delete;
			///	<summary>
			///		�L�[�{�[�h�̏�L�[�D
			///	</summary>
			static const Keys	Up;
			///	<summary>
			///		�L�[�{�[�h�̍��L�[�D
			///	</summary>
			static const Keys	Left;
			///	<summary>
			///		�L�[�{�[�h�̉E�L�[�D
			///	</summary>
			static const Keys	Right;
			///	<summary>
			///		�L�[�{�[�h�̉��L�[�D
			///	</summary>
			static const Keys	Down;
		};
	}
}
