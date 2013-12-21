// --------------------------------------------------------
//	apcException.h
// --------------------------------------------------------
//	��O�N���X���`����B
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <include/apcClassBase.h>

// --------------------------------------------------------
//	define�}�N�����g�p����
// --------------------------------------------------------
//	��O����}�N��
#define ThrowException(Str)			\
			throw new ApcException(_T(__FILE__), __LINE__, Apocalypse::Base::StrOut << Str)

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Exception)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Exception
	{
		///	<summary>
		///		Apocalypse�̗�O�N���X�B
		///	</summary>
		/// <remarks>
		///		���̗�O�N���X�́A��O�����������t�@�C�����E�s�ԍ��E�G���[�̏ڍׂ�
		///		�ۑ����āA���̌��ʂ�MessageBox�ɕ\�����邱�Ƃ��ł��܂��B<br />
		///		Exception()�}�N�����g�p����ƃt�@�C�����ƍs�ԍ����Ȃ����Ƃ��ł��܂��B
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		Exception("ApcException��O���}�N�����g�p���Ĕ��������܂��B");
		///		</code>
		/// </example>
		class ApcException : virtual public Base::ApcBase
		{
		public:
			///	<summary>
			///		��O�������ɓ�����N���X�i������Łj�BException�}�N�����g�p�����
			///		�t�@�C�����ƍs�ԍ����Ȃ���B
			///	</summary>
			/// <param name = "fName">
			///		��O�����������ӏ��̃t�@�C���̖��O�B__FILE__�}�N�����g�p����B
			/// </param>
			/// <param name = "Line">
			///		��O�����������ӏ��̃t�@�C���̍s�ԍ��B__LINE__�}�N�����g�p����B
			/// </param>
			/// <param name = "Str">
			///		�G���[���b�Z�[�W�ɕ\����������e�Bprintf�Ɠ��l�Ɏg�p�o����B
			/// </param>
								ApcException(Base::String fName, int Line, Base::String Str);
			///	<summary>
			///		�f�X�g���N�^
			///	</summary>
			virtual				~ApcException(){}
			///	<summary>
			///		��O����\������B
			///	</summary>
			void				ShowMessage() const;
		private:
			///	<summary>
			///		��O�����������t�@�C���̖��O
			///	</summary>
			Base::String		ExcFileName;
			///	<summary>
			///		��O�����������t�@�C���̍s��
			///	</summary>
			int					ExcLine;
			///	<summary>
			///		��O���̃R�����g�Ȃ�
			///	</summary>
			Base::String		ExcString;
		};
	}
}
