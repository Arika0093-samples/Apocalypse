// --------------------------------------------------------
//	apcInterface.cpp
// --------------------------------------------------------
//	apcInterface.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	ControlBase
// ----------------------------------------------------
//	ControlBase::ControlBase (Constructor)
// ----------------------------------------------------
				ControlBase::ControlBase(String Path)
{
	// 繰り返し描画
	StretchDraw				= false;
	// メンバフレームの親を自身に設定する
	TopLeft.Parent			= this;
	TopCenter.Parent		= this;
	TopRight.Parent			= this;
	MiddleLeft.Parent		= this;
	MiddleCenter.Parent		= this;
	MiddleRight.Parent		= this;
	BottomLeft.Parent		= this;
	BottomCenter.Parent		= this;
	BottomRight.Parent		= this;
	// 絶対値指定
	TopCenter.SpecifyWithParcent	= false;
	MiddleLeft.SpecifyWithParcent	= false;
	MiddleCenter.SpecifyWithParcent	= false;
	MiddleRight.SpecifyWithParcent	= false;
	BottomCenter.SpecifyWithParcent	= false;
	// 表示位置を指定
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
	// 画像をセットする
	ExchangeBackground(Path);
}

// ----------------------------------------------------
//	ControlBase::ExchangeBackground
// ----------------------------------------------------
void			ControlBase::ExchangeBackground(String Path)
{
	// 一時的に画像ハンドルを保存
	int PictHandle[9];
	// -------------------------------------------
	// 仮取得
	PictHandle[0] = LoadGraph(Path);
	// 取得できなければ
	if(PictHandle[0] == -1){
		// 終了
		return;
	}
	// サイズ取得
	GetGraphSize(PictHandle[0], &PictWidth, &PictHeight);
	// サイズ取得したら即ハンドルを閉じる
	DeleteGraph(PictHandle[0]);
	// -------------------------------------------
	// 今度は分割して取得
	LoadDivGraph(Path, 9, 3, 3, (PictWidth/3), (PictHeight/3), PictHandle);
	// 分ける
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
	// 子フレームの幅設定用
	int ChildWidth, ChildHeight;
	// ------------------------------------------
	// Visibleプロパティを一括指定
	TopLeft.Visible				=
	TopCenter.Visible			=
	TopRight.Visible			=
	MiddleLeft.Visible			=
	MiddleCenter.Visible		=
	MiddleRight.Visible			=
	BottomLeft.Visible			=
	BottomCenter.Visible		=
	BottomRight.Visible			= Visible;
	// StreachDrawのプロパティを一括指定
	TopCenter.StretchDraw		=
	MiddleLeft.StretchDraw		=
	MiddleCenter.StretchDraw	=
	MiddleRight.StretchDraw		=
	BottomCenter.StretchDraw	= StretchDraw;
	// このフレームの位置を合わせる
	this->EdgeFrame::SetProperties();
	// 子フレームの幅を指定する
	ChildWidth					= Width-((PictWidth*2)/3);
	ChildHeight					= Height-((PictHeight*2)/3);
	// 子フレームの位置を合わせる
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
