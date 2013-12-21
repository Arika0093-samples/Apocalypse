// --------------------------------------------------------
//	apcInterface.cpp
// --------------------------------------------------------
//	apcInterface.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	ControlBase
// ----------------------------------------------------
//	ControlBase::ControlBase (Constructor)
// ----------------------------------------------------
				ControlBase::ControlBase(String Path)
{
	// �J��Ԃ��`��
	StretchDraw				= false;
	// �����o�t���[���̐e�����g�ɐݒ肷��
	TopLeft.Parent			= this;
	TopCenter.Parent		= this;
	TopRight.Parent			= this;
	MiddleLeft.Parent		= this;
	MiddleCenter.Parent		= this;
	MiddleRight.Parent		= this;
	BottomLeft.Parent		= this;
	BottomCenter.Parent		= this;
	BottomRight.Parent		= this;
	// ��Βl�w��
	TopCenter.SpecifyWithParcent	= false;
	MiddleLeft.SpecifyWithParcent	= false;
	MiddleCenter.SpecifyWithParcent	= false;
	MiddleRight.SpecifyWithParcent	= false;
	BottomCenter.SpecifyWithParcent	= false;
	// �\���ʒu���w��
	TopLeft.Position		= FramePosition::TopLeft;
	TopLeft.Interpret		= FramePosition::TopLeft;
	TopCenter.Position		= FramePosition::TopCenter;
	TopCenter.Interpret		= FramePosition::TopCenter;
	TopRight.Position		= FramePosition::TopRight;
	TopRight.Interpret		= FramePosition::TopRight;
	MiddleLeft.Position		= FramePosition::MiddleLeft;
	MiddleLeft.Interpret	= FramePosition::MiddleLeft;
	MiddleCenter.Position	= FramePosition::MiddleCenter;
	MiddleCenter.Interpret	= FramePosition::MiddleCenter;
	MiddleRight.Position	= FramePosition::MiddleRight;
	MiddleRight.Interpret	= FramePosition::MiddleRight;
	BottomLeft.Position		= FramePosition::BottomLeft;
	BottomLeft.Interpret	= FramePosition::BottomLeft;
	BottomCenter.Position	= FramePosition::BottomCenter;
	BottomCenter.Interpret	= FramePosition::BottomCenter;
	BottomRight.Position	= FramePosition::BottomRight;
	BottomRight.Interpret	= FramePosition::BottomRight;
	// �摜���Z�b�g����
	ExchangeBackground(Path);
}

// ----------------------------------------------------
//	ControlBase::ExchangeBackground
// ----------------------------------------------------
void			ControlBase::ExchangeBackground(String Path)
{
	// �ꎞ�I�ɉ摜�n���h����ۑ�
	int PictHandle[9];
	// -------------------------------------------
	// ���擾
	PictHandle[0] = LoadGraph(Path);
	// �擾�ł��Ȃ����
	if(PictHandle[0] == -1){
		// �I��
		return;
	}
	// �T�C�Y�擾
	GetGraphSize(PictHandle[0], &PictWidth, &PictHeight);
	// �T�C�Y�擾�����瑦�n���h�������
	DeleteGraph(PictHandle[0]);
	// -------------------------------------------
	// ���x�͕������Ď擾
	LoadDivGraph(Path, 9, 3, 3, (PictWidth/3), (PictHeight/3), PictHandle);
	// ������
	TopLeft.ExchangePicture(Path, PictHandle[0]);
	TopCenter.ExchangePicture(Path, PictHandle[1]);
	TopRight.ExchangePicture(Path, PictHandle[2]);
	MiddleLeft.ExchangePicture(Path, PictHandle[3]);
	MiddleCenter.ExchangePicture(Path, PictHandle[4]);
	MiddleRight.ExchangePicture(Path, PictHandle[5]);
	BottomLeft.ExchangePicture(Path, PictHandle[6]);
	BottomCenter.ExchangePicture(Path, PictHandle[7]);
	BottomRight.ExchangePicture(Path, PictHandle[8]);
}

// ----------------------------------------------------
//	ControlBase::SetProperties
// ----------------------------------------------------
void			ControlBase::SetProperties()
{
	// �q�t���[���̕��ݒ�p
	int ChildWidth, ChildHeight;
	// ------------------------------------------
	// Visible�v���p�e�B���ꊇ�w��
	TopLeft.Visible				=
	TopCenter.Visible			=
	TopRight.Visible			=
	MiddleLeft.Visible			=
	MiddleCenter.Visible		=
	MiddleRight.Visible			=
	BottomLeft.Visible			=
	BottomCenter.Visible		=
	BottomRight.Visible			= Visible;
	// StreachDraw�̃v���p�e�B���ꊇ�w��
	TopCenter.StretchDraw		=
	MiddleLeft.StretchDraw		=
	MiddleCenter.StretchDraw	=
	MiddleRight.StretchDraw		=
	BottomCenter.StretchDraw	= StretchDraw;
	// ���̃t���[���̈ʒu�����킹��
	this->EdgeFrame::SetProperties();
	// �q�t���[���̕����w�肷��
	ChildWidth					= Width-((PictWidth*2)/3);
	ChildHeight					= Height-((PictHeight*2)/3);
	// �q�t���[���̈ʒu�����킹��
	TopCenter.WidthParam		= ChildWidth;
	TopCenter.HeightParam		= PictHeight/3;
	MiddleLeft.WidthParam		= PictWidth/3;
	MiddleLeft.HeightParam		= ChildHeight;
	MiddleCenter.WidthParam		= ChildWidth;
	MiddleCenter.HeightParam	= ChildHeight;
	MiddleRight.WidthParam		= PictWidth/3;
	MiddleRight.HeightParam		= ChildHeight;
	BottomCenter.WidthParam		= ChildWidth;
	BottomCenter.HeightParam	= PictHeight/3;
	MiddleCenter.Visible	= false;
}
