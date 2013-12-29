// --------------------------------------------------------
//	apcInterface.h
// --------------------------------------------------------
//	UI�֘A�̃N���X���L�ڂ���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <include/apcClassBase.h>
#include <include/apcDrawing.h>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::UI)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace UI
	{
		///	<summary>
		///		���ׂẴR���g���[���̊�ՁD
		///	</summary>
		/// <remarks>
		///		�R���g���[�����쐬���C�\�����܂��D
		/// </remarks>
		class ControlBase : public Draw::EdgeFrame
		{
		public:
			/// <summary>
			///		�R���X�g���N�^�D
			/// </summary>
			/// <param name = "Path">
			///		�R���g���[���̔w�i�̉摜�̃p�X�D
			/// </param>
									ControlBase(Base::String Path = _T(""));
			/// <summary>
			///		�f�X�g���N�^�D
			/// </summary>
			virtual					~ControlBase(){}
			/// <summary>
			///		�R���g���[���̔w�i�̉摜�������ւ���D
			/// </summary>
			/// <param name = "Path">
			///		�R���g���[���̔w�i�̉摜�̃p�X�D
			/// </param>
			void					ExchangeBackground(Base::String Path);
			/// <summary>
			///		�����L�΂��ĕ\�����邩�ǂ����D
			/// </summary>
			/// <remarks>
			///		�g�����̕����������L�΂��ĕ\�����邩�C����Ƃ��J��Ԃ��`�悷�邩��I�����܂��D
			///		��Ƃ��ẮC�O���f�[�V�������g�p���Ă���ꍇ��true�C�^�C���͗l�Ȃ��false�Ȃǂł��D
			/// </remarks>
			bool					StretchDraw;
		private:
			///	<summary>
			///		�ǂݍ��񂾉摜�̉����D
			///	</summary>
			int						PictWidth;
			///	<summary>
			///		�ǂݍ��񂾉摜�̏c���D
			///	</summary>
			int						PictHeight;
		protected:
			///	<summary>
			///		�t���[����`�悷��֐��D���̃t���[���̏ꍇ�͉������Ȃ��D
			///	</summary>
			virtual void			DrawThisFrame() const {}
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void			SetProperties();
			/// <summary>
			///		UI�w�i����̉摜�D
			/// </summary>
			Draw::PictureFrame		TopLeft;
			/// <summary>
			///		UI�w�i�����̉摜�D
			/// </summary>
			Draw::PictureFrame		BottomLeft;
			/// <summary>
			///		UI�w�i�E��̉摜�D
			/// </summary>
			Draw::PictureFrame		TopRight;
			/// <summary>
			///		UI�w�i�E���̉摜�D
			/// </summary>
			Draw::PictureFrame		BottomRight;
			/// <summary>
			///		UI�w�i������̉摜�D
			/// </summary>
			Draw::TilePictureFrame	TopCenter;
			/// <summary>
			///		UI�w�i���S���̉摜�D
			/// </summary>
			Draw::TilePictureFrame	MiddleLeft;
			/// <summary>
			///		UI�w�i�^�񒆂̉摜�D
			/// </summary>
			Draw::TilePictureFrame	MiddleCenter;
			/// <summary>
			///		UI�w�i���S�E�̉摜�D
			/// </summary>
			Draw::TilePictureFrame	MiddleRight;
			/// <summary>
			///		UI�w�i�������̉摜�D
			/// </summary>
			Draw::TilePictureFrame	BottomCenter;
		};
	}
}