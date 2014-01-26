// --------------------------------------------------------
//	apcValue.hpp
// --------------------------------------------------------
//	�����֘A�̃N���X���L�ڂ���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <Windows.h>
#include <tchar.h>
#include <sstream>
#include <memory>
#include <vector>
#include <boost/function.hpp>
#include <boost/algorithm/string.hpp>
#include <include/apcClassBase.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Value)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Value
	{
		// -----------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class String;

		///	<summary>
		///		���Ԋu�ő������Ă����l���Ǘ�����D
		///	</summary>
		class Timer : public virtual Base::__ApcInside
		{
		public:
			///	<summary>
			///		�R���X�g���N�^
			///	</summary>
								Timer();
			///	<summary>
			///		�^�C�}�[�̌J��Ԃ��^�C�v�̈ꗗ�D
			///	</summary>
			enum				_LoopType
			{
				///	<summary>
				///		�J��Ԃ��Ȃ��D�ŏI�n�_�Œ�~����D
				///	</summary>
				No,
				///	<summary>
				///		�Ō�܂œ��B������ŏ�����J��Ԃ��D
				///	</summary>
				Repeat,
				///	<summary>
				///		�Ō�܂œ��B�������x�����܂�Ԃ��D
				///	</summary>
				ReturnOnce,
				///	<summary>
				///		�[�܂œ��B������܂�Ԃ��D
				///	</summary>
				Return,
			};
			///	<summary>
			///		�^�C�}�[�̒l���擾����D
			///	</summary>
			double				operator()();
			///	<summary>
			///		�X�V�^�C�~���O�Œl���������������邩�D
			///	</summary>
			double				Add;
			///	<summary>
			///		1���[�v�̎����D0�ŏI�_�����D
			///	</summary>
			int					Cycle;
			///	<summary>
			///		�܂�Ԃ���ށD
			///	</summary>
			_LoopType			LoopType;
			/// <summary>
			///		�N���X�̏��𕶎���Ŏ擾����D
			/// </summary>
			virtual Value::String
								ToString() const;
			/// <summary>
			///		Timer�̒l��l���X�V�����Ɏ擾����D
			/// </summary>
			double				_GetValueNoReload() const;
		private:
			///	<summary>
			///		�����ŕێ�����l�D
			///	</summary>
			double				_Val;
			///	<summary>
			///		�܂�Ԃ��Ă��邩�ǂ����D
			///	</summary>
			bool				_IsReturned;
			///	<summary>
			///		�Ō�ɌĂяo���ꂽ����FC�l�D
			///	</summary>
			double				_LastCalledFrame;
			///	<summary>
			///		�^�C�}�[�X�V
			///	</summary>
			void				_TimerReload(int CallTimes);
			///	<summary>
			///		�J��Ԃ����̏����֐�
			///	</summary>
			bool				_RepeatFunc();
		};

		///	<summary>
		///		Number�Œl���Ǘ�����POINT�\���́D
		///	</summary>
		class Point : public virtual Base::__ApcBase
		{
		public:
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
								Point();
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
								Point(double X, double Y);
			///	<summary>
			///		�ʒu��X���W�D
			///	</summary>
			double				X;
			///	<summary>
			///		�ʒu��Y���W�D
			///	</summary>
			double				Y;
			/// <summary>
			///		�N���X�̏��𕶎���Ŏ擾����D
			/// </summary>
			virtual Value::String
								ToString() const;
			///	<summary>
			///		�������D
			///	</summary>
			void				operator()(double X, double Y);
			///	<summary>
			///		�R�s�[����D
			///	</summary>
			Point&				operator=(Point& Pt);
			///	<summary>
			///		�R�s�[����D
			///	</summary>
			Point&				operator=(double Val);
			///	<summary>
			///		��r����D
			///	</summary>
			bool				operator==(Point& Pt);
			///	<summary>
			///		��r����D
			///	</summary>
			bool				operator!=(Point& Pt);
		};

		///	<summary>
		///		������Ǘ��N���X�D
		///	</summary>
		/// <remarks>
		///		<para>���̃N���X�́C��{�I��STL��string�Ɠ����悤�Ɏg�p�ł��܂��D</para>
		///		<para>stringstream�̂悤�Ɏg�p���邱�Ƃ��\�ɂȂ��Ă��܂��D</para>
		///		<para>���̑��C�֗������ȋ@�\��ǉ����Ă��܂��D</para>
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// String()�N���X�ɐ�����4.12�𗬂���MessageBox�ŏo��
		///		String str;
		///		str << 4.12;
		///		MessageBox(NULL, str, _T(""), ID_OK);
		///		// String�N���X���擪�ɗ��Ȃ���ʂ܂��͈������<<���g�p����ꍇ��String()���g�p����D
		///		str = String() << _T("1+1=: ") << (1+1);
		///		MessageBox(NULL, (String() << _T("Value: ") << 6.132), _T(""), ID_OK);
		///		</code>
		/// </example>
		class String : public Base::__ApcBase, public std::basic_string<TCHAR>
		{
			///	<summary>
			///		typedef
			///	</summary>
			typedef				std::basic_string<TCHAR>		tstring;
		public:
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
								String(LPCTSTR Text = _T(""));
			///	<summary>
			///		��������f�o�b�O�E�C���h�E�ɏo�͂���
			///	</summary>
			void				DebugOutput() const;
			///	<summary>
			///		�������MessageBox�ŕ\������
			///	</summary>
			void				Message() const;
			///	<summary>
			///		�������MessageBox�ŕ\������
			///	</summary>
			/// <param name = "Style">
			///		MB_XX�}�N�����w�肷��D
			/// </param>
			/// <returns>
			///		IDYES�CIDNO�Ȃǂ̌��ʁD
			/// </returns>
			int					Message(unsigned int Style) const;
			///	<summary>
			///		���g���C�����̕�����̔z����q�������̂ɒu��������D
			///	</summary>
			/// <param name = "Array">
			///		�q����Ώۂ̔z��D
			/// </param>
			void				Connect(const std::vector<String> &Array);
			///	<summary>
			///		���g���C�����̕�����̔z�����蕶���Ōq�������̂ɒu��������D
			///	</summary>
			/// <param name = "Array">
			///		�q����Ώۂ̔z��D
			/// </param>
			/// <param name = "Cs">
			///		�����ƕ������q���镶����D
			/// </param>
			void				Connect(const std::vector<String> &Array, const String &Cs);
			///	<summary>
			///		������̓��蕔���������Œu�����������̂�ԋp����D
			///	</summary>
			/// <param name = "From">
			///		�u��������Ώۂ̕�����D
			/// </param>
			/// <param name = "To">
			///		�u����������̕�����D
			/// </param>
			String&				Replace(const String &From, const String &To) const;
			///	<summary>
			///		���������蕔���ŋ�؂��Ĕz��Ɋi�[�������̂�ԋp����D
			///	</summary>
			/// <param name = "Sp">
			///		��؂镶�����񋓂���D
			/// </param>
			std::vector<String> Split(const String &Sp) const;			
			///	<summary>
			///		operator LPCTSTR.
			///	</summary>
								operator LPCTSTR() const;
			///	<summary>
			///		�������������D
			///	</summary>
			String&				operator=(tstring Val);
			///	<summary>
			///		�������������D
			///	</summary>
			String&				operator=(LPCTSTR Val);
			///	<summary>
			///		�������bool�𗬂��D
			///	</summary>
			String&				operator<<(const bool Val);
			///	<summary>
			///		�������int�𗬂��D
			///	</summary>
			String&				operator<<(const int Val);
			///	<summary>
			///		�������UINT�𗬂��D
			///	</summary>
			String&				operator<<(const UINT Val);
			///	<summary>
			///		�������short�𗬂��D
			///	</summary>
			String&				operator<<(const short Val);
			///	<summary>
			///		�������USHORT�𗬂��D
			///	</summary>
			String&				operator<<(const USHORT Val);
			///	<summary>
			///		�������long�𗬂��D
			///	</summary>
			String&				operator<<(const long Val);
			///	<summary>
			///		�������ULONG�𗬂��D
			///	</summary>
			String&				operator<<(const ULONG Val);
			///	<summary>
			///		�������double�𗬂��D
			///	</summary>
			String&				operator<<(const double Val);
			///	<summary>
			///		�������Pointer�𗬂��D
			///	</summary>
			String&				operator<<(const void *Val);
			///	<summary>
			///		�������TCHAR�𗬂��D
			///	</summary>
			String&				operator<<(const TCHAR Val);
			///	<summary>
			///		�������LPCTSTR�𗬂��D
			///	</summary>
			String&				operator<<(const LPCTSTR Val);
			///	<summary>
			///		�������String�𗬂��D
			///	</summary>
			String&				operator<<(const String& Val);
			///	<summary>
			///		�������Point�𗬂��D
			///	</summary>
			String&				operator<<(const Point& Val);
			///	<summary>
			///		��������r����D
			///	</summary>
			bool				operator==(const String& Val) const;
			///	<summary>
			///		��������r����(NOT��)�D
			///	</summary>
			bool				operator!=(const String& Val) const;
			template<typename Type>
			///	<summary>
			///		��������w�肵���^�ɕϊ�����D
			///	</summary>
			Type				ToValue() const
			{
				// stringstream���g�p����
				std::basic_stringstream<TCHAR> Ts;
				// �l���擾����p�̕ϐ�
				Type Result;
				// --------------------------------
				// ���
				Ts << this->c_str();
				// �擾
				Ts >> Result;
				// �ԋp
				return Result;
			}
		private:
			template<typename Type>
			String&				FromValue(Type Val);
		};
	}
}