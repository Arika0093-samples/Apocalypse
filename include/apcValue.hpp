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
		class Timer : public virtual Base::_ApcInside
		{
		public:
			///	<summary>
			///		�^�C�}�[�̌J��Ԃ��^�C�v�̈ꗗ�D
			///	</summary>
			class					LoopType : public Base::_ApcEnumeration
			{
			public:
				///	<summary>
				///		�^�C�}�[�̌J��Ԃ��^�C�v�̈ꗗ�D
				///	</summary>
				enum					_LoopType
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
			};
			///	<summary>
			///		�R���X�g���N�^
			///	</summary>
									Timer();
			///	<summary>
			///		�^�C�}�[�̒l���擾����D
			///	</summary>
			double					operator()();
			///	<summary>
			///		1�b�Ԃɒl���������������邩�D
			///	</summary>
			double					Add;
			///	<summary>
			///		1���[�v�̎����D0�ŏI�_�����D
			///	</summary>
			int						Cycle;
			///	<summary>
			///		���g���L����Timer���ǂ����Dfalse�Ɏw�肷��ƒl�̎����������~����D
			///	</summary>
			bool					Enable;
			///	<summary>
			///		�^�C�}�[����~���Ă��邩�ǂ������w��C�擾����D
			///	</summary>
			bool					TimerStop;
			///	<summary>
			///		�l�̑����Ƀt���[���J�E���^���g�p���邩�ǂ����D
			///	</summary>
			bool					UseFrameCounter;
			///	<summary>
			///		�܂�Ԃ���ށD�W���ł�No(�܂�Ԃ��Ȃ�)�D
			///	</summary>
			LoopType::_LoopType		LoopType;
			/// <summary>
			///		Timer�̒l������������D
			/// </summary>
			void					Reset();
			/// <summary>
			///		�N���X�̏��𕶎���Ŏ擾����D
			/// </summary>
			virtual Value::String	ToString() const;
			/// <summary>
			///		Timer�̒l��l���X�V�����Ɏ擾����D
			/// </summary>
			double					_GetValueNoReload() const;
		private:
			///	<summary>
			///		�܂�Ԃ��Ă��邩�ǂ����D
			///	</summary>
			bool					_IsReturned;
			///	<summary>
			///		�Ō�ɌĂяo���ꂽ����FC�l�܂��̓J�E���^�l�D
			///	</summary>
			double					_LastCalledValue;
			///	<summary>
			///		�^�C�}�[�X�V
			///	</summary>
			void					_TimerReload(int CallTimes);
			///	<summary>
			///		�J��Ԃ����̏����֐�
			///	</summary>
			bool					_RepeatFunc();
			///	<summary>
			///		�����ŕێ�����l�D
			///	</summary>
			double					_Val;
			///	<summary>
			///		UseFrameCounter�̕ύX���m�p�ϐ��D
			///	</summary>
			bool					_BackupUseFlag;
		};

		///	<summary>
		///		double�ō��W���Ǘ�����POINT�\���́D
		///	</summary>
		class Point : public virtual Base::_ApcBase
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
			double					X;
			///	<summary>
			///		�ʒu��Y���W�D
			///	</summary>
			double					Y;
			/// <summary>
			///		�N���X�̏��𕶎���Ŏ擾����D
			/// </summary>
			virtual Value::String	ToString() const;
			///	<summary>
			///		�������D
			///	</summary>
			void					operator()(double X, double Y);
			///	<summary>
			///		�R�s�[����D
			///	</summary>
			Point&					operator=(const Point& Pt);
			///	<summary>
			///		�R�s�[����D
			///	</summary>
			Point&					operator=(double Val);
			///	<summary>
			///		��r����D
			///	</summary>
			bool					operator==(const Point& Pt) const;
			///	<summary>
			///		��r����D
			///	</summary>
			bool					operator!=(const Point& Pt) const;
		};

		///	<summary>
		///		�J�n�ʒu�Əc�����Ŏl�p�`���Ǘ�����\���́D
		///	</summary>
		class RectangleArea : public Base::_ApcBase
		{
		public:
			/// <summary>
			///		�R���X�g���N�^�D
			/// </summary>
									RectangleArea();
			/// <summary>
			///		�R���X�g���N�^�D
			/// </summary>
									RectangleArea(Value::Point &Pt, int Width, int Height);
			/// <summary>
			///		�l�p�`�̊J�n�n�_�D
			/// </summary>
			Point					Location;
			/// <summary>
			///		�l�p�`�̉���
			/// </summary>
			double					Width;
			/// <summary>
			///		�l�p�`�̏c��
			/// </summary>
			double					Height;
			/// <summary>
			///		�N���X�̏��𕶎���Ŏ擾����D
			/// </summary>
			virtual Value::String	ToString() const;
		};

		///	<summary>
		///		double�Ŏl�p�`���Ǘ�����Margin/Padding�p�̍\���́D
		///	</summary>
		class MarginRectangle : public Base::_ApcBase
		{
			/// <summary>
			///		�v���p�e�B�̒l���Ǘ�����N���X�D
			/// </summary>
			class					_Property : public Base::_ApcInside
			{
			public:
				/// <summary>
				///		�R���X�g���N�^�D
				/// </summary>
									_Property(){ _Value = 0, Auto = false; }
				/// <summary>
				///		�R���X�g���N�^�D
				/// </summary>
									_Property(bool IsAuto){ _Value = 0, Auto = IsAuto; }
				/// <summary>
				///		�v���p�e�B�̒l���擾����D
				/// </summary>
									operator double(){ return _Value; }
				/// <summary>
				///		�v���p�e�B�ɒl��������D
				/// </summary>
				double				operator=(double Val){ return _Value = Val; }
				/// <summary>
				///		�v���p�e�B�ɒl��������D
				/// </summary>
				_Property&			operator=(const _Property &Val)
				{
					Auto = Val.Auto, Percent = Val.Percent, _Value = Val._Value;
					return *this;
				}
				/// <summary>
				///		�v���p�e�B�ƒl���r����D
				/// </summary>
				bool				operator==(const _Property &Val) const
				{
					return (Auto == Val.Auto && Percent == Val.Percent && _Value == Val._Value);
				}
				/// <summary>
				///		�v���p�e�B�ƒl��NOT��r����D
				/// </summary>
				bool				operator!=(const _Property &Val) const{ return !(*this == Val); }
				/// <summary>
				///		�v���p�e�B�������Ŏw�肷�邩�ǂ����D
				/// </summary>
				bool				Auto;
				/// <summary>
				///		�v���p�e�B��%�Ŏw�肷�邩�ǂ����D
				/// </summary>
				bool				Percent;
				/// <summary>
				///		�����̒l������ۂ̒l���Z�o����
				/// </summary>
				double				CalclateValue(double BaseSize) const;
				/// <summary>
				///		�N���X�̏��𕶎���Ŏ擾����D
				/// </summary>
				virtual Value::String
									ToString() const;
			private:
				/// <summary>
				///		�v���p�e�B�̒l�D
				/// </summary>
				double				_Value;
			};
		public:
			/// <summary>
			///		�R���X�g���N�^�D
			/// </summary>
									MarginRectangle();
			/// <summary>
			///		�R���X�g���N�^�D
			/// </summary>
									MarginRectangle(double Left, double Right, double Top, double Bottom);
			/// <summary>
			///		�����̒l�D
			/// </summary>
			_Property				Left;
			/// <summary>
			///		�E���̒l�D
			/// </summary>
			_Property				Right;
			/// <summary>
			///		�㑤�̒l�D
			/// </summary>
			_Property				Top;
			/// <summary>
			///		�����̒l�D
			/// </summary>
			_Property				Bottom;
			/// <summary>
			///		�l�������w�肷��悤�ݒ肷��ۂɎg�p����l�D
			/// </summary>
			static const _Property	Auto;
			/// <summary>
			///		�l��%�w�肷��悤�ݒ肷��ۂɎg�p����֐��D
			/// </summary>
			static _Property		Percentage(double Percent);
			/// <summary>
			///		Rectangle�N���X���r����D
			/// </summary>
			bool					Compare(const MarginRectangle& Rc) const;
			/// <summary>
			///		���g�̏�������Rectangle���\�����ĕԋp����
			/// </summary>
			RectangleArea			CalclationArea(const RectangleArea &ArBase) const;
			/// <summary>
			///		�N���X�̏��𕶎���Ŏ擾����D
			/// </summary>
			virtual Value::String	ToString() const;
			///	<summary>
			///		�������D
			///	</summary>
			MarginRectangle&		operator()(double Left, double Right, double Top, double Bottom);
			///	<summary>
			///		�������D
			///	</summary>
			MarginRectangle&		operator()(_Property Left, _Property Right, _Property Top, _Property Bottom);
			///	<summary>
			///		�R�s�[����D
			///	</summary>
			MarginRectangle&		operator=(const MarginRectangle& Rc);
			///	<summary>
			///		�����̈����������r����D
			///	</summary>
			bool					operator==(const MarginRectangle& Rc) const;
			///	<summary>
			///		�����̈�������Ă��Ȃ�����r����D
			///	</summary>
			bool					operator!=(const MarginRectangle& Rc) const;
		};

		///	<summary>
		///		������Ǘ��N���X�D
		///	</summary>
		/// <remarks>
		///		<para>���̃N���X�́C��{�I��STL��string�Ɠ����悤�Ɏg�p�ł��܂��D</para>
		///		<para>stringstream�̂悤�Ɏg�p���邱�Ƃ��\�ɂȂ��Ă��܂��D</para>
		///		<para>���̑��C�֗������ȋ@�\��ǉ����Ă��܂��D</para>
		/// </remarks>
		class String : public Base::_ApcBase, public std::basic_string<TCHAR>
		{
			///	<summary>
			///		typedef
			///	</summary>
			typedef					std::basic_string<TCHAR>		tstring;
		public:
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
									String(LPCTSTR Text = _T(""));
			///	<summary>
			///		��������f�o�b�O�E�C���h�E�ɏo�͂���
			///	</summary>
			void					DebugOutput() const;
			///	<summary>
			///		����������O�t�@�C���ɏo�͂���
			///	</summary>
			void					LogOutput() const;
			///	<summary>
			///		���g���C�����̕�����̔z����q�������̂ɒu��������D
			///	</summary>
			/// <param name = "Array">
			///		�q����Ώۂ̔z��D
			/// </param>
			static String&			Connect(const std::vector<String> &Array);
			///	<summary>
			///		���g���C�����̕�����̔z�����蕶���Ōq�������̂ɒu��������D
			///	</summary>
			/// <param name = "Array">
			///		�q����Ώۂ̔z��D
			/// </param>
			/// <param name = "Cs">
			///		�����ƕ������q���镶����D
			/// </param>
			static String&			Connect(const std::vector<String> &Array, const String &Cs);
			///	<summary>
			///		������̓��蕔���������Œu�����������̂�ԋp����D
			///	</summary>
			/// <param name = "From">
			///		�u��������Ώۂ̕�����D
			/// </param>
			/// <param name = "To">
			///		�u����������̕�����D
			/// </param>
			String&					Replace(const String &From, const String &To) const;
			///	<summary>
			///		���������蕔���ŋ�؂��Ĕz��Ɋi�[�������̂�ԋp����D
			///	</summary>
			/// <param name = "Sp">
			///		��؂镶�����񋓂���D
			/// </param>
			std::vector<String>&	Split(const String &Sp) const;			
			///	<summary>
			///		���������蕔���ŋ�؂��Ĕz��Ɋi�[�������̂�ԋp����D
			///	</summary>
			/// <param name = "Sp">
			///		��؂镶�����񋓂���D
			/// </param>
			/// <param name = "IsSpaceAble">
			///		�󔒂̔z���ԋp���邩�ǂ������w�肷��D
			/// </param>
			std::vector<String>&	Split(const String &Sp, bool IsSpaceAble) const;			
			///	<summary>
			///		operator LPCTSTR.
			///	</summary>
									operator LPCTSTR() const;
			///	<summary>
			///		�������������D
			///	</summary>
			String&					operator=(tstring Val);
			///	<summary>
			///		�������������D
			///	</summary>
			String&					operator=(LPCTSTR Val);
			///	<summary>
			///		��������r����D
			///	</summary>
			bool					operator==(String &Str) const;
			///	<summary>
			///		�������NOT��r����D
			///	</summary>
			bool					operator!=(String &Str) const;
			///	<summary>
			///		�������bool�𗬂��D
			///	</summary>
			String&					operator<<(const bool Val);
			///	<summary>
			///		�������int�𗬂��D
			///	</summary>
			String&					operator<<(const int Val);
			///	<summary>
			///		�������UINT�𗬂��D
			///	</summary>
			String&					operator<<(const UINT Val);
			///	<summary>
			///		�������short�𗬂��D
			///	</summary>
			String&					operator<<(const short Val);
			///	<summary>
			///		�������USHORT�𗬂��D
			///	</summary>
			String&					operator<<(const USHORT Val);
			///	<summary>
			///		�������long�𗬂��D
			///	</summary>
			String&					operator<<(const long Val);
			///	<summary>
			///		�������ULONG�𗬂��D
			///	</summary>
			String&					operator<<(const ULONG Val);
			///	<summary>
			///		�������double�𗬂��D
			///	</summary>
			String&					operator<<(const double Val);
			///	<summary>
			///		�������Pointer�𗬂��D
			///	</summary>
			String&					operator<<(const void *Val);
			///	<summary>
			///		�������TCHAR�𗬂��D
			///	</summary>
			String&					operator<<(const TCHAR Val);
			///	<summary>
			///		�������LPCTSTR�𗬂��D
			///	</summary>
			String&					operator<<(const LPCTSTR Val);
			///	<summary>
			///		�������String�𗬂��D
			///	</summary>
			String&					operator<<(const String& Val);
			///	<summary>
			///		�������Point�𗬂��D
			///	</summary>
			String&					operator<<(const Point& Val);
			template<typename Type>
			///	<summary>
			///		��������w�肵���^�ɕϊ�����D
			///	</summary>  
			Type					ToValue() const
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
			String&					FromValue(Type Val);
		};
	}
}