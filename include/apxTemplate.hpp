// --------------------------------------------------------
//	apcTemplate.h
// --------------------------------------------------------
//	�e���v���[�g�N���X���`����t�@�C���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <include/apcClassBase.hpp>

// --------------------------------------------------------
//	���O��Ԃ��g�p
// --------------------------------------------------------
namespace Apocalypse
{
	// ----------------------------------------------------
	//	Template���O��ԓ��̃N���X���L��
	// ----------------------------------------------------
	namespace Template
	{
		template <class T>
		///	<summary>
		///		<para>Singleton�N���X����������ۂɎg�p����N���X�̃e���v���[�g�D</para>
		///		<para>�p������`�Ŏg�p����D</para>
		///	</summary>
		class __Singleton : public virtual Base::__ApcBase
		{
		public:
			/// <summary>
			///		���̂��擾����
			/// </summary>
			static T&			GetInstance()
			{
				static T Instance;
				return Instance;
			}
		protected:
			/// <summary>
			///		�R���X�g���N�^
			/// </summary>
								__Singleton(){}
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual				~__Singleton(){}
			/// <summary>
			///		�R�s�[�R���X�g���N�^
			/// </summary>
								__Singleton(const __Singleton& r){}
			/// <summary>
			///		������Z�q
			/// </summary>
			void*				operator=(const __Singleton& r){}
		};
	}
}