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
	this->Enable				= true;
	this->Visible				= true;
	// 描画順番を初期状態にリセットする
	this->DrawOrder				= 0;
	// 標準で位置合わせを行う
	this->_AutoAdjustPosition	= true;
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
		<< _T("Location: {") << _Location.ToString() << _T("}")
		<< _T(", Width: ") << _Width
		<< _T(", Height: ") << _Height
		<< _T(", Order: ") << DrawOrder;
}

// ----------------------------------------------------
//	FrameBase::SetDefaultPosition
// ----------------------------------------------------
void			__FrameBase::_SetDefaultPosition()
{
	// 親フレームを取得
	auto PrtPtr = Parent;
	// もし親フレームが存在しないなら
	if(!PrtPtr || !_AutoAdjustPosition){
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
		<< _T(", Start: ")	<< StartGradColor.ToString()
		<< _T(", End: ")	<< EndGradColor.ToString()
		<< _T(", Border: ")<< BorderColor.ToString();
}

// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame() const
{
	// もしグラデーション開始色が設定されていて
	if(StartGradColor.Enable){
		// 終了色が指定されていないor開始色と終了色が同じ場合なら
		if(!EndGradColor.Enable || StartGradColor == EndGradColor){
			// αブレンド適用
			StartGradColor._AppendAlpha();
			// 単色塗り
			DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
					(_Location.Y + GetHeight()), StartGradColor._GetColor(), TRUE);
		}
		// 終了色が指定されている場合は
		else {
			// グラデーションを描画する
			for(int Y = 0; Y < this->GetHeight(); Y++){
				// 描画する色を取得する
				auto DrawColor = StartGradColor._GetColorBlends(EndGradColor, (Y*100/GetHeight()));
				// αブレンド適用
				DrawColor->_AppendAlpha();
				// 一本ずつ描画する
				DrawLine(_Location.X, _Location.Y + Y, _Location.X + GetWidth() - 1,
						 _Location.Y + Y, DrawColor->_GetColor());
			}
		}
	}
	// 境界線描画の色が決まっているならば
	if(BorderColor.Enable){
		// αブレンド適用
		BorderColor._AppendAlpha();
		// 描画する．
		DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
				(_Location.Y + GetHeight()), BorderColor._GetColor(), FALSE);
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
	this->_PictureHandle	= (ImgPath.compare(_T("")) ? LoadGraph(ImgPath) : -1);
	// 画像パスをセットする
	this->Path				= ImgPath;
	this->_PicturePath		= ImgPath;
	// 反転描画しない
	Turned					= false;
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
	// 反転描画が有効でないなら
	if(!Turned){
		// 普通に画像を描画する
		DrawGraphF(_Location.X, _Location.Y, _PictureHandle, TRUE);
	// 反転描画が有効なら
	} else {
		// 反転して描画
		DrawTurnGraphF(_Location.X, _Location.Y, _PictureHandle, TRUE);
	}
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
	StretchDraw = true;
}

// ----------------------------------------------------
//	AreaPictureFrame::ToString
// ----------------------------------------------------
String			AreaPictureFrame::ToString() const
{
	return this->PictureFrame::ToString()
		<< _T("StretchDraw: ") << StretchDraw;
}

// ----------------------------------------------------
//	AreaPictureFrame::SetProperties
// ----------------------------------------------------
void			AreaPictureFrame::_SetProperties()
{
	// 先にPictureFrameの方を呼び出してから
	this->PictureFrame::_SetProperties();
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
		// 反転描画しないなら
		if(!Turned){
			// 拡大描画
			DrawExtendGraph(_Location.X, _Location.Y, _Location.X + _Width,
							_Location.Y + _Height, _PictureHandle, TRUE);
		// 反転描画するなら
		} else {
			// 拡大反転描画
			DrawExtendGraph(_Location.X + _Width, _Location.Y,
							_Location.X, _Location.Y + _Height, _PictureHandle, TRUE);
		}
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
//	TextFrame
// ----------------------------------------------------
//	TextFrame::TextFrame (Constructor)
// ----------------------------------------------------
				TextFrame::TextFrame(String Str)
{
	// 文字列をコピーする
	this->Text			= Str;
	// 標準で文字送りしない
	TextAdvance			= false;
}

// ----------------------------------------------------
//	TextFrame::ToString
// ----------------------------------------------------
String			TextFrame::ToString() const
{
	return this->__FrameBase::ToString()
		<< _T(", Text: \"") << Text << _T("\"")
		<< _T(", AdvanceShow: ") << TextAdvance
		<< _T(", Font: {") << TextFont.ToString() << _T("}");
}

// ----------------------------------------------------
//	TextFrame::SetProperties
// ----------------------------------------------------
void			TextFrame::_SetProperties()
{
	// 縦幅を取得する
	int HeightSave = 0;
	// ----------------------------------------------------
	// 横幅を取得する
	this->_Width  = GetDrawStringWidthToHandle(Text,
						Text.length(), TextFont._GetFontHandle());
	// 縦幅を指定する
	GetFontStateToHandle(NULL, &HeightSave, NULL, TextFont._GetFontHandle());
	// 設定
	_Height = HeightSave;
	// もし文字送り設定で，全表示が終わっていれば
	if(TextAdvance && TextTimer.LoopType == Timer::No
	&&(TextTimer() / 1000) >= Text.length()){
		// 文字送りを終了する
		TextAdvance = false;
	}
	// 描画文字を更新
	_SetDrawString();
	// フォント情報を更新
	TextFont._ReloadFontHandle();
}

// ----------------------------------------------------
//	TextFrame::DrawThisFrame
// ----------------------------------------------------
void			TextFrame::_DrawThisFrame() const
{
	// αブレンドを有効化
	TextFont.FontColor._AppendAlpha();
	// 文字列を描画する．
	DrawStringToHandle(_Location.X, _Location.Y, _DrawText,
		TextFont.FontColor._GetColor(), TextFont._GetFontHandle(), TextFont.EdgeColor._GetColor());
}

// ----------------------------------------------------
//	TextFrame::GetDrawString
// ----------------------------------------------------
void			TextFrame::_SetDrawString()
{
	// Timer考慮で文字を先頭から順に取得する
	_DrawText = Text.substr(0, (TextAdvance ? TextTimer() / 1000 : Text.length()));
}

// ----------------------------------------------------
//	Font
// ----------------------------------------------------
//	Font::Font (Constructor/None)
// ----------------------------------------------------
				Font::Font()
{
	// 詳細版を呼び出す
	this->Font::Font(ApplicationConfig::DefaultFontName, 16, 0, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Size)
// ----------------------------------------------------
				Font::Font(int FontSize)
{
	// 詳細版を呼び出す
	this->Font::Font(ApplicationConfig::DefaultFontName, FontSize, 0, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize)
{
	// 詳細版を呼び出す
	this->Font::Font(FontName, FontSize, 0, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size,Thick)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick)
{
	// 詳細版を呼び出す
	this->Font::Font(FontName, FontSize, FontThick, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size,Thick,EdgeSize)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick, int eSize)
{
	// 詳細版を呼び出す
	this->Font::Font(FontName, FontSize, FontThick, EdgeSize, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/All)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick, int eSize, Font::FontType::_FontType FontType)
{
	// プロパティをセットする
	Name		= FontName;
	Size		= FontSize;
	Thick		= FontThick;
	Type		= FontType;
	EdgeSize	= eSize;
	// 色を初期化する
	FontColor	= Color::White;
	// ハンドルを初期化する
	_Handle		= NULL;
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
//	TextFrame::ToString
// ----------------------------------------------------
String			Font::ToString() const
{
	return String()
		<< _T("Name: \"") << _Name << _T("\"")
		<< _T(", Size: ") << _Size
		<< _T(", Thick: ") << _Thick
		<< _T(", Color: ") << FontColor.ToString()
		<< _T(", Edge: ") << EdgeColor.ToString();
}

// ----------------------------------------------------
//	Font::ReloadFontHandle
// ----------------------------------------------------
void			Font::_ReloadFontHandle()
{
	// もしプロパティの中のどれかの値が変更されていたら
	if( Name != _Name || Size != _Size || Thick != _Thick
		|| EdgeSize != _Edge || Type != _Type || EdgeColor.Enable != _IsEnableEdge){
		// プロパティを新しい値に更新して
		_Name = Name;
		_Size = Size;
		_Thick = Thick;
		_Edge = EdgeSize;
		_Type = Type;
		_IsEnableEdge = EdgeColor.Enable;
		// 現在のフォントハンドルを解放して
		DeleteFontToHandle(_Handle);
		// フォントハンドルを更新する
		_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _GetFontDrawType(), -1, _Edge);
	}
}

// ----------------------------------------------------
//	Font::GetFontHandle
// ----------------------------------------------------
inline int		Font::_GetFontHandle() const
{
	// フォントハンドルを返却する
	return this->_Handle;
}

// ----------------------------------------------------
//	Font::GetFontDrawType
// ----------------------------------------------------
inline int		Font::_GetFontDrawType() const
{
	// 一時用
	int Result = 0;
	// 描画の種類に応じてDEFINE定義された値をセットする
	switch(_Type){
	case FontType::Normal:
		Result = DX_FONTTYPE_NORMAL;
		break;
	case FontType::Antialiase:
		Result = DX_FONTTYPE_ANTIALIASING;
		break;
	case FontType::AntialiaseHiQuality:
		Result = DX_FONTTYPE_ANTIALIASING_8X8;
		break;
	default:
		return -1;
	}
	// エッジ色が指定されているならエッジも描画するように指定
	Result += (_IsEnableEdge ? 1 : 0);
	// 返却
	return Result;
}

// ----------------------------------------------------
//	Color
// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color()
{
	// 色を無効に指定する
	Enable = false;
}

// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color(int Rp, int Gp, int Bp)
{
	// 詳細版を呼び出す
	this->Color::Color(255, Rp, Gp, Bp);
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
	// 有効に設定
	Enable = true;
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
	// 有効に設定
	Enable = true;
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
	// 有効に設定
	Enable = true;
}

// ----------------------------------------------------
//	Color::operator= (Color version)
// ----------------------------------------------------
Color&			Color::operator=(const Color &Cr)
{
	// 代入する
	this->A	= Cr.A;
	this->R	= Cr.R;
	this->G	= Cr.G;
	this->B	= Cr.B;
	// 色の有効度を引数に合わせる
	Enable = Cr.Enable;
	// 自身を返却する
	return *this;
}

// ----------------------------------------------------
//	Color::operator= (RGB Code version)
// ----------------------------------------------------
Color&			Color::operator=(const Color::_ColorList ARGBCode)
{
	// 代入する
	this->A	= ((ARGBCode >> 24) & 0xFF);
	this->R	= ((ARGBCode >> 16) & 0xFF);
	this->G	= ((ARGBCode >>  8) & 0xFF);
	this->B	= ((ARGBCode >>  0) & 0xFF);
	// 有効に設定
	Enable = true;
	// 自身を返却する
	return *this;
}

// ----------------------------------------------------
//	Color::operator==
// ----------------------------------------------------
bool			Color::operator==(const Color& Cr) const
{
	return Compare(Cr);
}

// ----------------------------------------------------
//	Color::operator!=
// ----------------------------------------------------
bool			Color::operator!=(const Color& Cr) const
{
	return !Compare(Cr);
}

// ----------------------------------------------------
//	Color::AlphaToParcent
// ----------------------------------------------------
int				Color::AlphaFromParcent(double Bs)
{
	return (Bs * 256.0)/100;
}

// ----------------------------------------------------
//	Color::ToString
// ----------------------------------------------------
String			Color::ToString() const
{
	// もし有効なら
	if(Enable){
		// ARGBコードを返却する
		return String()
			<< A << _T("|")
			<< R << _T("|") 
			<< B << _T("|")
			<< G;
	}
	// もし無効なら
	else {
		// Invalidを返却する
		return String(_T("Invalid"));
	}
}

// ----------------------------------------------------
//	Color::GetColor
// ----------------------------------------------------
inline DWORD	Color::_GetColor() const
{
	// 有効なら色を作成して返却，そうでないならエラーコードを返す
	return (Enable ? GetColor(this->R, this->G, this->B) : -1);
}

// ----------------------------------------------------
//	Color::AppendAlpha
// ----------------------------------------------------
inline void		Color::_AppendAlpha() const
{
	// 有効な色なら
	if(Enable){
		// 透過度を設定する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, A);
	}
}

// ----------------------------------------------------
//	Color::Compare
// ----------------------------------------------------
bool			Color::Compare(const Color &Target) const
{
	return Target.A == A
		&& Target.R == R
		&& Target.B == B
		&& Target.G == G
		&& Target.Enable == Enable;
}

// ----------------------------------------------------
//	Color::GetColorBlends
// ----------------------------------------------------
std::shared_ptr<Color>
				Color::_GetColorBlends(const Color &Target, int Parcent) const
{
	// 色ごとに取得する
	int _Red	= (Target.R * Parcent)/100 + (R * (100-Parcent))/100;
	int _Green	= (Target.G * Parcent)/100 + (G * (100-Parcent))/100;
	int _Blue	= (Target.B * Parcent)/100 + (B * (100-Parcent))/100;
	int _Alpha	= (Target.A * Parcent)/100 + (A * (100-Parcent))/100;
	// 作成して返却する
	return std::shared_ptr<Color>(new Color(_Alpha, _Red, _Green, _Blue));
}
