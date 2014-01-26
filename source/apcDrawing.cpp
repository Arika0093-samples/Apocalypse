// --------------------------------------------------------
//	apcDrawing.cpp
// --------------------------------------------------------
//	apcDrawing.h のメンバ関数の実体を置く
// --------------------------------------------------------
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
	// 描画種類を初期化
	this->DrawMode			= FrameDrawMode::Nearest;
	// 親フレームをTopParentに初期化
	this->Parent			= __FrameCollection::GetInstance().GetTopParent();
	// コレクションに追加
	__FrameCollection::GetInstance().Insert(this);
}

// ----------------------------------------------------
//	FrameBase::~FrameBase (Destructor)
// ----------------------------------------------------
				__FrameBase::~__FrameBase()
{
	// FrameCollectionから自身のデータを消す
	__FrameCollection::GetInstance().Erase(this);
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
Point			__FrameBase::GetLocation() const
{
	return this->_Location;
}

// ----------------------------------------------------
//	FrameBase::ToString
// ----------------------------------------------------
String			__FrameBase::ToString() const
{
	return String()
		<< _T("Location: {") << _Location.ToString() << _T("}, ")
		<< _T("Width: ") << _Width
		<< _T(", Height: ") << _Height;
}

// ----------------------------------------------------
//	FrameBase::SetDefaultPosition
// ----------------------------------------------------
void			__FrameBase::_SetDefaultPosition()
{
	// 親フレームを取得
	auto PrtPtr = Parent;
	// もし親フレームが存在しないなら
	if(!PrtPtr){
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
			this->_Location.X += ((PrtPtr->_Location.X) + (this->Points.X));
			break;
		// (X座標)中心を基準に表示するなら
		case FramePosition::TopCenter:
		case FramePosition::MiddleCenter:
		case FramePosition::BottomCenter:
			// 親のX座標 + (親の幅/2)を追加．
			this->_Location.X += ((PrtPtr->_Location.X) + (this->Points.X)
							  + ((PrtPtr->_Width) / 2));
			break;
		// (X座標)一番右を基準に表示するなら
		case FramePosition::TopRight:
		case FramePosition::MiddleRight:
		case FramePosition::BottomRight:
			// 親のX座標 + 親の幅を追加．
			this->_Location.X += ((PrtPtr->_Location.X) + (this->Points.X)
							  +  (PrtPtr->_Width));
			break;
	}
	// 基準とする位置で判定(Y座標)．
	switch(this->Position){
		// (Y座標)一番上を基準にするなら
		case FramePosition::TopLeft:
		case FramePosition::TopCenter:
		case FramePosition::TopRight:
			// 親のY座標をそのまま追加．
			this->_Location.Y += ((PrtPtr->_Location.Y) + (this->Points.Y));
			break;
		// (Y座標)中心を基準に表示するなら
		case FramePosition::MiddleLeft:
		case FramePosition::MiddleCenter:
		case FramePosition::MiddleRight:
			// 親のY座標 + (親の高さ/2)を追加．
			this->_Location.Y += ((PrtPtr->_Location.Y) + (this->Points.Y)
							  + ((PrtPtr->_Height) / 2));
			break;
		// (Y座標)一番下を基準に表示するなら
		case FramePosition::BottomLeft:
		case FramePosition::BottomCenter:
		case FramePosition::BottomRight:
			// 親のY座標 + 親の高さを追加．
			this->_Location.Y += ((PrtPtr->_Location.Y) + (this->Points.Y)
							  +  (PrtPtr->_Height));
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
		// 親フレームを取得
		auto PrtPtr = Parent;
		// もし無効なら
		if(!PrtPtr){
			// 例外を投げてもいい気がする
			// throw XXXX;
			return;
		}
		// 横幅と縦幅を指定する
		_Width  = (PrtPtr->GetWidth ())* (Width)/100;
		_Height = (PrtPtr->GetHeight())*(Height)/100;
	}
	// 終了．
	return;
}

// ----------------------------------------------------
//	GradationFrame
// ----------------------------------------------------
//	GradationFrame::ToString
// ----------------------------------------------------
String			GradationFrame::ToString() const
{
	return this->__FrameBase::ToString()
		<< _T(", Start: {")	<< (StartGradColor	? StartGradColor->ToString(): _T("empty")) << _T("}")
		<< _T(", End: {")	<< (EndGradColor	? EndGradColor->ToString()	: _T("empty")) << _T("}")
		<< _T(", Border: {")<< (BorderColor		? BorderColor->ToString()	: _T("empty")) << _T("}");
}

// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame() const
{
	// もしグラデーション開始色が設定されていて
	if(this->StartGradColor){
		// 終了色が指定されていないor開始色と終了色が同じ場合なら
		if(EndGradColor == NULL || StartGradColor->_Compare(EndGradColor)){
			// αブレンド適用
			StartGradColor->_AppendAlpha();
			// 単色塗り
			DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
					(_Location.Y + GetHeight()), StartGradColor->_GetColor(), TRUE);
		}
		// 終了色が指定されている場合は
		else {
			// グラデーションを描画する
			for(int Y = 0; Y < this->GetHeight(); Y++){
				// 描画する色を取得する
				auto DrawColor = StartGradColor->_GetColorBlends(EndGradColor, (Y*100/GetHeight()));
				// αブレンド適用
				DrawColor->_AppendAlpha();
				// 一本ずつ描画する
				DrawLine(_Location.X, _Location.Y + Y, _Location.X + GetWidth() - 1,
						 _Location.Y + Y, DrawColor->_GetColor());
			}
		}
	}
	// 境界線描画の色が決まっているならば
	if(this->BorderColor){
		// αブレンド適用
		BorderColor->_AppendAlpha();
		// 描画する．
		DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
				(_Location.Y + GetHeight()), BorderColor->_GetColor(), FALSE);
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
	this->Path				= ImgPath;
	this->_PicturePath		= ImgPath;
	// 画像サイズを横幅と縦幅に指定する
	GetGraphSize(_PictureHandle, &_Width, &_Height);
	// 不透明度を255に指定する
	Alpha = 255;
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
//	PictureFrame::ToString
// ----------------------------------------------------
String			PictureFrame::ToString() const
{
	return this->__FrameBase::ToString()
		<< _T(", Path: \"") << Path << _T("\"")
		<< _T(", Alpha: ")<< Alpha;
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			PictureFrame::_SetProperties()
{
	// もし指定されている画像ファイルが変わっているなら
	if(Path != _PicturePath){
		// 現在の画像を破棄して
		DeleteGraph(_PictureHandle);
		// 読み込み直す
		_PictureHandle = LoadGraph(Path);
		// コピー
		_PicturePath = Path;
	}
	// 画像サイズを横幅と縦幅に指定する
	GetGraphSize(_PictureHandle, &_Width, &_Height);
}

// ----------------------------------------------------
//	PictureFrame::DrsawThisFrame
// ----------------------------------------------------
void			PictureFrame::_DrawThisFrame() const
{
	// αブレンドを有効化
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	// 画像を描画する
	DrawGraph(_Location.X, _Location.Y, _PictureHandle, TRUE);
}

// ----------------------------------------------------
//	AreaPictureFrame
// ----------------------------------------------------
//	AreaPictureFrame::AreaPictureFrame (Constructor)
// ----------------------------------------------------
				AreaPictureFrame::AreaPictureFrame(String ImgPath)
					: PictureFrame(ImgPath)
{
	// 初期化する
	TileX = 0;
	TileY = 0;
	StretchDraw = false;
}

// ----------------------------------------------------
//	AreaPictureFrame::ToString
// ----------------------------------------------------
String			AreaPictureFrame::ToString() const
{
	return this->PictureFrame::ToString();
}

// ----------------------------------------------------
//	AreaPictureFrame::SetProperties
// ----------------------------------------------------
void			AreaPictureFrame::_SetProperties()
{
	// EdgeFrameの方を呼び出す
	this->EdgeFrame::_SetProperties();
}

// ----------------------------------------------------
//	AreaPictureFrame::DrawThisFrame
// ----------------------------------------------------
void			AreaPictureFrame::_DrawThisFrame() const
{
	// 描画画像の縦横幅
	int PictWidth, PictHeight;
	// -------------------------------------
	// 描画領域を指定しておく
	SetDrawArea(_Location.X, _Location.Y, (_Location.X + _Width), (_Location.Y + _Height));
	// 描画画像の縦横幅を取得する
	GetGraphSize(_PictureHandle, &PictWidth, &PictHeight);
	// αブレンドを有効化
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
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
//	MovieFrame::ToString
// ----------------------------------------------------
String			MovieFrame::ToString() const
{
	return this->__FrameBase::ToString();
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
	// αブレンドを有効化
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);

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
	// 標準で文字送りしない
	AdvanceTimer.Add = 0;
	// 色を初期化する
	TextColor	= std::shared_ptr<Color>(new Color(255,255,255));
}

// ----------------------------------------------------
//	StringFrame::ToString
// ----------------------------------------------------
String			StringFrame::ToString() const
{
	return this->__FrameBase::ToString()
		<< _T(", Text: \"") << Text << _T("\"")
		<< (AdvanceTimer.Add != 0 ? String() << _T(", ShowTextLenght: ")
		<< (int)AdvanceTimer._GetValueNoReload() / 100 : _T(""))
		<< _T(", Font: {") << TextFont->ToString() << _T("}")
		<< _T(", Color: {") << TextColor->ToString() << _T("}");
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
	// 描画文字を更新
	_SetDrawString();
}

// ----------------------------------------------------
//	StringFrame::DrawThisFrame
// ----------------------------------------------------
void			StringFrame::_DrawThisFrame() const
{
	// αブレンドを有効化
	TextColor->_AppendAlpha();
	// 文字列を描画する．
	DrawStringToHandle(_Location.X, _Location.Y, _DrawText,
			this->TextColor->_GetColor(), this->TextFont->_GetFontHandle());
}

// ----------------------------------------------------
//	StringFrame::GetDrawString
// ----------------------------------------------------
void			StringFrame::_SetDrawString()
{
	// Timer考慮で文字を先頭から順に取得する
	_DrawText = Text.substr(0, (AdvanceTimer.Add != 0 ? AdvanceTimer() / 100 : Text.length()));
}

// ----------------------------------------------------
//	Font
// ----------------------------------------------------
//	Font::Font (Constructor/None)
// ----------------------------------------------------
				Font::Font()
{
	// 標準フォントを使用する
	_Name	= ApplicationConfig::DefaultFontName;
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
	_Name	= ApplicationConfig::DefaultFontName;
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
//	StringFrame::ToString
// ----------------------------------------------------
String			Font::ToString() const
{
	return String() << _T("Name: \"") << _Name << _T("\"")
		<< _T(", Size: ") << _Size
		<< _T(", Thick: ") << _Thick;
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
				Color::Color(int Rp, int Gp, int Bp)
{
	// 値を指定する
	this->R	= Rp;
	this->G	= Gp;
	this->B	= Bp;
	this->A	= 255;
}

// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color(int Ap, int Rp, int Gp, int Bp)
{
	// 値を指定する
	this->R	= Rp;
	this->G	= Gp;
	this->B	= Bp;
	this->A	= Ap;
}

// ----------------------------------------------------
//	Color::Color (RGB Code version)
// ----------------------------------------------------
				Color::Color(Color::_ColorList ARGBCode)
{
	// 値をシフト演算で指定する
	this->A	= ((ARGBCode >> 24) & 0xFF);
	this->R	= ((ARGBCode >> 16) & 0xFF);
	this->G	= ((ARGBCode >>  8) & 0xFF);
	this->B	= ((ARGBCode >>  0) & 0xFF);
}

// ----------------------------------------------------
//	Color::Color (RGB Code version, Set Alpha)
// ----------------------------------------------------
				Color::Color(Color::_ColorList RGBCode, int Alpha)
{
	// 値をシフト演算で指定する
	this->R	= ((RGBCode >> 16) & 0xFF);
	this->G	= ((RGBCode >>  8) & 0xFF);
	this->B	= ((RGBCode >>  0) & 0xFF);
	// 引数の値を指定する
	this->A	= Alpha;
}

// ----------------------------------------------------
//	Color::ToString
// ----------------------------------------------------
String			Color::ToString() const
{
	return String() << _T("Alpha: ") << A
		<< _T(", Red: ") << R
		<< _T(", Blue: ") << B
		<< _T(", Green: ") << G;
}

// ----------------------------------------------------
//	Color::GetColor
// ----------------------------------------------------
inline DWORD	Color::_GetColor() const
{
	return GetColor(this->R, this->G, this->B);
}

// ----------------------------------------------------
//	Color::AppendAlpha
// ----------------------------------------------------
inline void		Color::_AppendAlpha() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, A);
}

// ----------------------------------------------------
//	Color::Compare
// ----------------------------------------------------
bool			Color::_Compare(const std::shared_ptr<Color> Target) const
{
	return Target->A == A
		&& Target->R == R
		&& Target->B == B
		&& Target->G == G;
}

// ----------------------------------------------------
//	Color::GetColorBlends
// ----------------------------------------------------
std::shared_ptr<Color>
				Color::_GetColorBlends(const std::shared_ptr<Color> Target, int Parcent) const
{
	// 色ごとに取得する
	int _Red	= (Target->R * Parcent)/100 + (R * (100-Parcent))/100;
	int _Green	= (Target->G * Parcent)/100 + (G * (100-Parcent))/100;
	int _Blue	= (Target->B * Parcent)/100 + (B * (100-Parcent))/100;
	int _Alpha	= (Target->A * Parcent)/100 + (A * (100-Parcent))/100;
	// 作成して返却する
	return New(Color, _Alpha, _Red, _Green, _Blue);
}