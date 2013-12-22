// --------------------------------------------------------
//	apcDrawing.cpp
// --------------------------------------------------------
//	apcDrawing.h のメンバ関数の実体を置く
// --------------------------------------------------------
//#define APOCALYPSE_USEALLNAMESPACE
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	FrameBase
// ----------------------------------------------------
//	FrameBase::FrameBase (Constructor)
// ----------------------------------------------------
				__FrameBase::__FrameBase()
{
	// 有効にする
	this->Enable			= true;
	this->Visible			= true;
	// 描画順番を初期状態にリセットする
	this->DrawOrder			= 0;
	// 横幅縦幅をリセットする
	this->_Width			= 0;
	this->_Height			= 0;
	// 描画位置を初期化
	this->Position			= FramePosition::Default;
	this->Interpret			= FramePosition::Default;
	// 親フレームを標準値に初期化
	this->Parent			= NULL;
	// 不透明に設定．
	this->Alpha				= 255;
	// コレクションに追加
	__FrameCollection::GetInstance().Insert(std::shared_ptr<__FrameBase>(this));
}

// ----------------------------------------------------
//	FrameBase::~FrameBase (Destructor)
// ----------------------------------------------------
				__FrameBase::~__FrameBase()
{
	// FrameCollectionから自身のデータを消す
	__FrameCollection::GetInstance().Erase(std::shared_ptr<__FrameBase>(this));
}

// ----------------------------------------------------
//	FrameBase::GetWidth
// ----------------------------------------------------
inline int		__FrameBase::GetWidth() const
{
	return this->_Width;
}

// ----------------------------------------------------
//	FrameBase::GetFrameHeight
// ----------------------------------------------------
inline int		__FrameBase::GetHeight() const
{
	return this->_Height;
}

// ----------------------------------------------------
//	FrameBase::GetFrameLocation
// ----------------------------------------------------
inline Point	__FrameBase::GetLocation() const
{
	return this->_Location;
}

// ----------------------------------------------------
//	FrameBase::SetDefaultPosition
// ----------------------------------------------------
void			__FrameBase::_SetDefaultPosition()
{
	// もし親フレームが存在しないなら
	if(!this->Parent){
		// 終了
		return;
	}
	// 描画場所を0で初期化する．
	this->_Location = 0;
	// 基準とする位置で判定(X座標)．
	switch(this->Position){
		// (X座標)一番左を基準にするなら
		case FramePosition::TopLeft:
		case FramePosition::MiddleLeft:
		case FramePosition::BottomLeft:
			// 親のX座標をそのまま追加．
			this->_Location.X += ((this->Parent->_Location.X) + (this->Points.X));
			break;
		// (X座標)中心を基準に表示するなら
		case FramePosition::TopCenter:
		case FramePosition::MiddleCenter:
		case FramePosition::BottomCenter:
			// 親のX座標 + (親の幅/2)を追加．
			this->_Location.X += ((this->Parent->_Location.X) + (this->Points.X)
							  + ((this->Parent->_Width) / 2));
			break;
		// (X座標)一番右を基準に表示するなら
		case FramePosition::TopRight:
		case FramePosition::MiddleRight:
		case FramePosition::BottomRight:
			// 親のX座標 + 親の幅を追加．
			this->_Location.X += ((this->Parent->_Location.X) + (this->Points.X)
							  +  (this->Parent->_Width));
			break;
	}
	// 基準とする位置で判定(Y座標)．
	switch(this->Position){
		// (Y座標)一番上を基準にするなら
		case FramePosition::TopLeft:
		case FramePosition::TopCenter:
		case FramePosition::TopRight:
			// 親のY座標をそのまま追加．
			this->_Location.Y += ((this->Parent->_Location.Y) + (this->Points.Y));
			break;
		// (Y座標)中心を基準に表示するなら
		case FramePosition::MiddleLeft:
		case FramePosition::MiddleCenter:
		case FramePosition::MiddleRight:
			// 親のY座標 + (親の高さ/2)を追加．
			this->_Location.Y += ((this->Parent->_Location.Y) + (this->Points.Y)
							  + ((this->Parent->_Height) / 2));
			break;
		// (Y座標)一番下を基準に表示するなら
		case FramePosition::BottomLeft:
		case FramePosition::BottomCenter:
		case FramePosition::BottomRight:
			// 親のY座標 + 親の高さを追加．
			this->_Location.Y += ((this->Parent->_Location.Y) + (this->Points.Y)
							  +  (this->Parent->_Height));
			break;
	}
	// 解釈位置を確認(X座標)
	switch(this->Interpret){
		// 一番左を基準にするなら
		case FramePosition::TopLeft:
		case FramePosition::MiddleLeft:
		case FramePosition::BottomLeft:
			// 特に何もしない
			break;
		// 中央を基準にするなら
		case FramePosition::TopCenter:
		case FramePosition::MiddleCenter:
		case FramePosition::BottomCenter:
			// 幅の半分を引く．
			this->_Location.X -= (this->_Width / 2);
			break;
		// 一番右を基準にするなら
		case FramePosition::TopRight:
		case FramePosition::MiddleRight:
		case FramePosition::BottomRight:
			// 幅を引く．
			this->_Location.X -= (this->_Width);
			break;
	}
	// 解釈位置を確認(Y座標)
	switch(this->Interpret){
		// 一番上を基準にするなら
		case FramePosition::TopLeft:
		case FramePosition::TopCenter:
		case FramePosition::TopRight:
			// 特に何もしない
			break;
		// 中心を基準にするなら
		case FramePosition::MiddleLeft:
		case FramePosition::MiddleCenter:
		case FramePosition::MiddleRight:
			// 高さの半分を引く．
			this->_Location.Y -= (this->_Height / 2);
			break;
		// 一番下を基準にするなら
		case FramePosition::BottomLeft:
		case FramePosition::BottomCenter:
		case FramePosition::BottomRight:
			// 高さを引く．
			this->_Location.Y -= (this->_Height);
			break;
	}
}

// ----------------------------------------------------
//	EdgeFrame
// ----------------------------------------------------
//	EdgeFrame::EdgeFrame (Constructor)
// ----------------------------------------------------
				EdgeFrame::EdgeFrame()
{
	// ％指定で描画するよう指定
	this->SpecifyWithParcent = true;
	// 縦幅幅を100%に指定
	this->Width		= 100;
	this->Height	= 100;
}

// ----------------------------------------------------
//	EdgeFrame::SetProperties
// ----------------------------------------------------
void			EdgeFrame::_SetProperties()
{
	// もし％指定でないなら
	if(this->SpecifyWithParcent == false){
		// Paramに指定された値をそのまま使用する
		this->_Width	= Width;
		this->_Height	= Height;
	}
	// もし%指定なら
	else {
		// 横幅と縦幅を指定する
		_Width  = (Parent->GetWidth ())* (Width)/100;
		_Height = (Parent->GetHeight())*(Height)/100;
	}
	// 終了．
	return;
}

// ----------------------------------------------------
//	GradationFrame
// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame() const
{
	// もしグラデーション開始色が設定されていて
	if(this->StartGradColor){
		// 終了色が指定されていないor開始色と終了色が同じ場合なら
		if(this->EndGradColor == NULL
		|| this->StartGradColor->_GetColorToClass() == this->EndGradColor->_GetColorToClass()){
			// 単色塗り
			DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
					(_Location.Y + GetHeight()), StartGradColor->_GetColorToClass(), TRUE);
		}
		// 終了色が指定されている場合は
		else {
			// グラデーションを描画する
			for(int Y = 0; Y < this->GetHeight(); Y++){
				// 一本ずつ描画する．
				DrawLine(_Location.Y, _Location.Y + Y,
						 _Location.X + GetWidth() - 1, _Location.Y + Y,
						 StartGradColor->_GetColorBlends(EndGradColor, (Y*100/GetHeight())));
			}
		}
	}
	// 境界線描画の色が決まっているならば
	if(this->BorderColor){
		// 描画する．
		DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
				(_Location.Y + GetHeight()), BorderColor->_GetColorToClass(), FALSE);
	}
}

// ----------------------------------------------------
//	PictureFrame
// ----------------------------------------------------
//	PictureFrame::PictureFrame (Constructor)
// ----------------------------------------------------
				PictureFrame::PictureFrame(String ImgPath)
{
	// ハンドルをセットする
	this->_PictureHandle	= LoadGraph(ImgPath);
	// 画像パスをセットする
	this->_PicturePath		= ImgPath;
	// 画像サイズを横幅と縦幅に指定する
	GetGraphSize(_PictureHandle, &_Width, &_Height);
}

// ----------------------------------------------------
//	PictureFrame::~PictureFrame (Destructor)
// ----------------------------------------------------
				PictureFrame::~PictureFrame()
{
	// 画像を削除する
	DeleteGraph(this->_PictureHandle);
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			PictureFrame::_SetProperties()
{
	// 画像サイズを横幅と縦幅に指定する
	GetGraphSize(_PictureHandle, &_Width, &_Height);
}

// ----------------------------------------------------
//	PictureFrame::DrawThisFrame
// ----------------------------------------------------
void			PictureFrame::_DrawThisFrame() const
{
	// 画像を描画する
	DrawGraph(_Location.X, _Location.Y, _PictureHandle, TRUE);
}

// ----------------------------------------------------
//	PictureFrame::ExchangePicture
// ----------------------------------------------------
bool			PictureFrame::ExchangePicture(String ImgPath, int Handle)
{
	// もし画像が同じものだったら
	if(_PicturePath == ImgPath){
		// falseを返す．
		return false;
	}
	// 現在のハンドルを削除する
	DeleteGraph(_PictureHandle);
	// ハンドルをセットする
	this->_PictureHandle	= ( Handle ? Handle : LoadGraph(ImgPath) );
	// 画像パスをセットする
	this->_PicturePath		= ImgPath;
	// 画像サイズを横幅と縦幅に指定する
	GetGraphSize(_PictureHandle, &_Width, &_Height);
	// trueを返す
	return true;
}

// ----------------------------------------------------
//	TilePictureFrame
// ----------------------------------------------------
//	TilePictureFrame::TilePictureFrame (Constructor)
// ----------------------------------------------------
				TilePictureFrame::TilePictureFrame(String ImgPath)
					: PictureFrame(ImgPath)
{
	// 初期化する
	TileX = 0;
	TileY = 0;
	StretchDraw = false;
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			TilePictureFrame::_SetProperties()
{
	// EdgeFrameの方を呼び出す
	this->EdgeFrame::_SetProperties();
}

// ----------------------------------------------------
//	PictureFrame::DrawThisFrame
// ----------------------------------------------------
void			TilePictureFrame::_DrawThisFrame() const
{
	// 描画画像の縦横幅
	int PictWidth, PictHeight;
	// -------------------------------------
	// 描画領域を指定しておく
	SetDrawArea(_Location.X, _Location.Y, (_Location.X + _Width), (_Location.Y + _Height));
	// 描画画像の縦横幅を取得する
	GetGraphSize(_PictureHandle, &PictWidth, &PictHeight);
	// もし引き伸ばして描画するなら
	if(StretchDraw){
		// 拡大描画
		DrawExtendGraph(_Location.X, _Location.Y, _Location.X + _Width,
						_Location.Y + _Height, _PictureHandle, TRUE);
	}
	// 繰り返しで描画するなら
	else{
		// X座標のループ
		for(int LocX=(_Location.X+(TileX%PictWidth)-PictWidth); LocX<(_Location.X+_Width); LocX+=PictWidth){
			// Y座標のループ
			for(int LocY=(_Location.Y+(TileY%PictHeight)-PictHeight);LocY<(_Location.Y+_Height);LocY+=PictHeight){
				// 画像を描画する
				DrawGraph(LocX, LocY, _PictureHandle, TRUE);
			}
		}
	}
	// 描画領域を元に戻す
	SetDrawAreaFull();
}

// ----------------------------------------------------
//	MovieFrame
// ----------------------------------------------------
//	MovieFrame::MovieFrame (Constructor)
// ----------------------------------------------------
				MovieFrame::MovieFrame(String MovPath)
{
}

// ----------------------------------------------------
//	MovieFrame::SetProperties
// ----------------------------------------------------
void			MovieFrame::_SetProperties()
{

}

// ----------------------------------------------------
//	MovieFrame::DrawThisFrame
// ----------------------------------------------------
void			MovieFrame::_DrawThisFrame() const
{

}

// ----------------------------------------------------
//	StringFrame
// ----------------------------------------------------
//	StringFrame::StringFrame (Constructor)
// ----------------------------------------------------
				StringFrame::StringFrame(String Str)
{
	// 文字列をコピーする
	this->Text	= Str;
	// 色を初期化する
	TextColor	= std::shared_ptr<Color>(new Color(255,255,255));
}

// ----------------------------------------------------
//	StringFrame::SetProperties
// ----------------------------------------------------
void			StringFrame::_SetProperties()
{
	// 縦幅を取得する
	int HeightSave = 0;
	// ----------------------------------------------------
	// もしフォントが未作成なら
	if(!this->TextFont){
		// フォントを新規作成
		this->TextFont = std::shared_ptr<Font>(new Font());
	}
	// 横幅を取得する
	this->_Width  = GetDrawStringWidthToHandle(Text,
						Text.length(), TextFont->_GetFontHandle());
	// 縦幅を指定する
	GetFontStateToHandle(NULL, &HeightSave, NULL, TextFont->_GetFontHandle());
	// 設定
	_Height = HeightSave;
}

// ----------------------------------------------------
//	StringFrame::DrawThisFrame
// ----------------------------------------------------
void			StringFrame::_DrawThisFrame() const
{
	// 文字列を描画する．
	DrawStringToHandle(_Location.X, _Location.Y, this->Text,
			this->TextColor->_GetColorToClass(), this->TextFont->_GetFontHandle());
}

// ----------------------------------------------------
//	Font
// ----------------------------------------------------
//	Font::Font (Constructor/None)
// ----------------------------------------------------
				Font::Font()
{
	// 標準フォントを使用する
	_Name	= __ApcSystem::GetInstance().GameSetting->DefaultFontName;
	// プロパティをセットする
	_Size	= 16;
	_Thick	= 0;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// フォントハンドルを作成する
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Size)
// ----------------------------------------------------
				Font::Font(int FontSize)
{
	// 標準フォントを使用する
	_Name	= __ApcSystem::GetInstance().GameSetting->DefaultFontName;
	// プロパティをセットする
	_Size	= FontSize;
	_Thick	= 0;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// フォントハンドルを作成する
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize)
{
	// 標準フォントを使用する
	_Name	= FontName;
	// プロパティをセットする
	_Size	= FontSize;
	_Thick	= 0;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// フォントハンドルを作成する
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size,Thick)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick)
{
	// 標準フォントを使用する
	_Name	= FontName;
	// プロパティをセットする
	_Size	= FontSize;
	_Thick	= FontThick;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// フォントハンドルを作成する
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/All)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick, int FontType)
{
	// 標準フォントを使用する
	_Name	= FontName;
	// プロパティをセットする
	_Size	= FontSize;
	_Thick	= FontThick;
	_Type	= FontType;
	// フォントハンドルを作成する
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::~Font (Destructor)
// ----------------------------------------------------
				Font::~Font()
{
	// フォントを削除する
	DeleteFontToHandle(this->_Handle);
}

// ----------------------------------------------------
//	Font::GetFontHandle
// ----------------------------------------------------
inline int		Font::_GetFontHandle() const
{
	return this->_Handle;
}

// ----------------------------------------------------
//	Color
// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color(int R, int G, int B)
{
	// 値を指定する
	this->_Red		= R;
	this->_Green	= G;
	this->_Blue		= B;
}

// ----------------------------------------------------
//	Color::Color (RGB Code version)
// ----------------------------------------------------
				Color::Color(Color::ColorList RGBCode)
{
	// 値をシフト演算で指定する
	this->_Red		= ((RGBCode >> 16) & 0xFF);
	this->_Green	= ((RGBCode >>  8) & 0xFF);
	this->_Blue		= ((RGBCode >>  0) & 0xFF);
}

// ----------------------------------------------------
//	Color::ColorToClass
// ----------------------------------------------------
inline DWORD	Color::_GetColorToClass() const
{
	return GetColor(this->_Red, this->_Green, this->_Blue);
}

// ----------------------------------------------------
//	Color::ColorToClass
// ----------------------------------------------------
DWORD			Color::_GetColorBlends(const std::shared_ptr<Color> Target, int Parcent) const
{
	// 色ごとに取得する
	int Red		= ((Target->_Red)*(Parcent)/(100))	+ ((this->_Red)*(100-(Parcent))/(100));
	int Green	= ((Target->_Green)*(Parcent)/(100))+ ((this->_Green)*(100-(Parcent))/(100));
	int Blue	= ((Target->_Blue)*(Parcent)/(100))	+ ((this->_Blue)*(100-(Parcent))/(100));
	// 作成して返却する
	return DxLib::GetColor(Red, Green, Blue);
}
