// --------------------------------------------------------
//	apcExpression.h
// --------------------------------------------------------
//	�e�퐔���̊֐����L�ڂ���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <math.h>
#include <include/apcClassBase.h>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Expression)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Expression
	{
		///	<summary>
		///		�ꎟ�������N���X�̊�ՁD���̃N���X���͍̂쐬�ł��Ȃ��D
		///	</summary>
		/// <remarks>
		///		Function�֐������s���邱�Ƃł��ꂼ��̐����̒l���擾�ł��܂��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// VibrateExp(���̃N���X���p�������N���X)�Ő������܂��D���̃N���X�ł���{�͓����ł��D
		///		// �����N���X��p��
		///		VibrateExp vre;
		///		// �l���擾�i�߂�l��double�Ȃ̂�int�ɃL���X�g���܂��j
		///		int Num = (int)vre.Function();
		///		</code>
		/// </example>
		class __SingleExpression : virtual public Base::__ApcBase
		{
		public:
			///	<summary>
			///		�����̉������߂�֐��D
			///	</summary>
			double				Function() const;
			///	<summary>
			///		���ʂ̍Œ�l�D���ʂ����̒l�ȉ��̏ꍇ���̒l�ɂȂ�D
			///	</summary>
			double				Min;
			///	<summary>
			///		���ʂ̍ō��l�D���ʂ����̒l�ȏ�̏ꍇ���̒l�ɂȂ�D
			///	</summary>
			double				Max;
		private:
			///	<summary>
			///		1�t���[�����ƂɈ��̒l��������l��������
			///		������ԋp����֐��D���z�֐��D
			///	</summary>
			///	<param name = "x">
			///		�����l�D
			///	</param>
			virtual double		_f(int x) const = 0;
			///	<summary>
			///		�J�E���^�̏����l��ۑ�����ϐ��D
			///	</summary>
			unsigned int		_StartCount;
		protected:
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
								__SingleExpression();
		};

		///	<summary>
		///		�j���������N���X�̊�ՁD���̃N���X���͍̂쐬�ł��Ȃ��D
		///	</summary>
		/// <remarks>
		///		Function�֐������s���邱�Ƃł��ꂼ��̐����̒l���擾�ł��܂��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// HermiteExp(���̃N���X���p�������N���X)�Ő������܂��D���̃N���X�ł���{�͓����ł��D
		///		// �����N���X��p��
		///		HermiteExp hme;
		///		// �l���擾
		///		Point Num = hme.Function();
		///		// X���W�̂ݎ擾���������͈ȉ��̂悤�ɂ��܂�
		///		double Xval = hme.Function().X;
		///		</code>
		/// </example>
		class __DoubleExpression : virtual public Base::__ApcBase
		{
		public:
			///	<summary>
			///		�����̉������߂�֐��D
			///	</summary>
			Base::Point			Function() const;
			///	<summary>
			///		���ʂ̍Œ�l�D���ʂ����̒l�ȉ��̏ꍇ���̒l�ɂȂ�D
			///	</summary>
			double				Min;
			///	<summary>
			///		���ʂ̍ō��l�D���ʂ����̒l�ȏ�̏ꍇ���̒l�ɂȂ�D
			///	</summary>
			double				Max;
		private:
			///	<summary>
			///		1�t���[�����ƂɈ��̒l��������l��������
			///		������ԋp����֐��D���z�֐��D
			///	</summary>
			///	<param name = "t">
			///		�����l�D
			///	</param>
			virtual Base::Point	_f(int t) const = 0;
			///	<summary>
			///		�J�E���^�̏����l��ۑ�����ϐ��D
			///	</summary>
			unsigned int		_StartCount;
		protected:
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
								__DoubleExpression();
		};

		///	<summary>
		///		�U���g�̐����N���X�D
		///	</summary>
		/// <remarks>
		///		������sin�֐����g�p���Ă��܂��D
		/// </remarks>
		class VibrateExp : public __SingleExpression
		{
		public:
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
								VibrateExp();
			///	<summary>
			///		�U���̒l�D
			///	</summary>
			double				Amplitude;
			///	<summary>
			///		����(/Frame)�D��Frame�ň�񃋁[�v���邩�D
			///		1Frame = 1�Ƃ��Ďw�肷��D
			///	</summary>
			double				Cycle;
		private:
			///	<summary>
			///		1�t���[�����ƂɈ��̒l��������l��������
			///		������ԋp����֐��D
			///	</summary>
			///	<param name = "x">
			///		�����l�D
			///	</param>
			double				_f(int x) const;
			///	<summary>
			///		���x��rad�x�Ɋ��Z����D
			///	</summary>
			///	<param name = "Deg">
			///		�����l�D
			///	</param>
			double				_DegToRad(double Deg) const;
		};

		///	<summary>
		///		�����I�Ɏg�p�ł���Ȑ�����\�����鐔���N���X�D
		///	</summary>
		/// <remarks>
		///		�����ŃG���~�[�g�Ȑ����g�p���Ă��܂��D
		/// </remarks>
		class HermiteExp : public __DoubleExpression
		{
		public:
			///	<summary>
			///		�R���X�g���N�^�D
			///	</summary>
								HermiteExp();
			///	<summary>
			///		�����̊J�n�_�D
			///	</summary>
			Base::Point			Start;
			///	<summary>
			///		�����̏I���_�D
			///	</summary>
			Base::Point			End;
			///	<summary>
			///		�����̎n�_�x�N�g���D
			///	</summary>
			Base::Point			StartVector;
			///	<summary>
			///		�����̏I�_�x�N�g���D
			///	</summary>
			Base::Point			EndVector;
			///	<summary>
			///		�ړ��̏��v����(Frame�P��)�D
			///	</summary>
			unsigned int		Time;
		private:
			///	<summary>
			///		1�t���[�����ƂɈ��̒l��������l��������
			///		������ԋp����֐��D
			///	</summary>
			///	<param name = "x">
			///		�����l�D
			///	</param>
			Base::Point			_f(int t) const;
		};
	}
}
