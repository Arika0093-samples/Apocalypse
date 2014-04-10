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
				_FrameBase::_FrameBase()
{
	// 有効にする
	this->Enable				= true;
	this->Visible				= true;
	// 描画順番を初期状態にリセットする
	this->DrawOrder				= 0;
	// 標準で枠内描画する
	this->DrawFramework			= true;
	// 標準で位置合わせを行う
	this->_AutoAdjustPosition	= true;
	// 描画種類を初期化
	this->DrawMode				= FrameDrawMode::Bilinear;
	// Marginを初期化
	this->Margin.Left			= MarginRectangle::Auto;
	this->Margin.Right			= MarginRectangle::Auto;
	this->Margin.Top			= MarginRectangle::Auto;
	this->Margin.Bottom			= MarginRectangle::Auto;
	// 親フレームをTopParentに初期化
	this->Parent				= _FrameCollection::GetInstance().GetTopParent();
	// コレクションに追加
	_FrameCollection::GetInstance().Insert(this);
}

// ----------------------------------------------------
//	FrameBase::~FrameBase (Destructor)
// ----------------------------------------------------
				_FrameBase::~_FrameBase()
{
	// FrameCollectionから自身のデータを消す
	_FrameCollection::GetInstance().Erase(this);
}

// ----------------------------------------------------
//	FrameBase::GetFrameArea
// ----------------------------------------------------
RectangleArea	_FrameBase::GetFrameArea() const
{
	// 返却用に確保
	RectangleArea Rect;
	// ------------------------------------------------
	// 親フレームが存在するなら
	if(Parent != nullptr && Parent != _FrameCollection::GetInstance().GetTopParent()){
		// 親フレームのActualAreaを取得する
		Rect = Parent->GetActualArea();
	}
	// 存在しない or 一番上のフレームなら
	else {
		// 領域を指定する
		Rect.Location.X	= 0;
		Rect.Location.Y	= 0;
		Rect.Width		= System::ApplicationConfig::Width;
		Rect.Height		= System::ApplicationConfig::Height;
	}
	// 返却
	return Rect;
}

// ----------------------------------------------------
//	FrameBase::GetFrameLocation
// ----------------------------------------------------
RectangleArea	_FrameBase::GetActualArea() const
{
	// Maginを考慮した領域を取得
	RectangleArea Rect = GetFrameArea();
	// ------------------------------------------------
	// このフレームの縦横幅を取得
	Rect.Width	= (_GetActualWidth()  != -1 ? _GetActualWidth()  : Rect.Width);
	Rect.Height	= (_GetActualHeight() != -1 ? _GetActualHeight() : Rect.Height);
	// 領域を計算して返却
	return Margin.CalclationArea(Rect);
}

// ----------------------------------------------------
//	FrameBase::ToString
// ----------------------------------------------------
String			_FrameBase::ToString() const
{
	return String()
		<< _T("FrameRectangle: {") << GetFrameArea().ToString() << _T("}")
		<< _T(", ActualArea: {") << GetActualArea().ToString() << _T("}")
		<< _T(", Order: ") << DrawOrder;
}

// ----------------------------------------------------
//	GradationFrame
// ----------------------------------------------------
//	GradationFrame::ToString
// ----------------------------------------------------
String			GradationFrame::ToString() const
{
	return this->PanelFrame::ToString()
		<< _T(", Start: ")	<< StartGradColor.ToString()
		<< _T(", End: ")	<< EndGradColor.ToString()
		<< _T(", Border: ")<< BorderColor.ToString();
}

// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// もしグラデーション開始色が設定されていて
	if(StartGradColor.Enable){
		// 終了色が指定されていないor開始色と終了色が同じ場合なら
		if(!EndGradColor.Enable || StartGradColor == EndGradColor){
			// αブレンド適用
			StartGradColor._AppendAlpha();
			// 単色塗り
			DrawBox(Dr.Location.X, Dr.Location.Y, Dr.Width, Dr.Height, StartGradColor._GetColor(), TRUE);
		}
		// 終了色が指定されている場合は
		else {
			// 描画色を指定する
			Color GrDrawColor;
			GrDrawColor.Enable = true;
			// グラデーションを描画する
			for(int Y = 0; Y < Dr.Height; Y++){
				// 開始色と終了色の割合を取得する
				double DrParcent = Y*100.00/Dr.Height;
				// 描画色を割合から算出する
				GrDrawColor.A = (EndGradColor.A * DrParcent)/100 + (StartGradColor.A * (100-DrParcent))/100;
				GrDrawColor.R = (EndGradColor.R * DrParcent)/100 + (StartGradColor.R * (100-DrParcent))/100;
				GrDrawColor.G = (EndGradColor.G * DrParcent)/100 + (StartGradColor.G * (100-DrParcent))/100;
				GrDrawColor.B = (EndGradColor.B * DrParcent)/100 + (StartGradColor.B * (100-DrParcent))/100;
				// αブレンド適用
				GrDrawColor._AppendAlpha();
				// 一本ずつ描画する
				DrawLine(Dr.Location.X, Dr.Location.Y + Y, Dr.Width - 1,
						 Dr.Location.Y + Y, GrDrawColor._GetColor());
			}
		}
	}
	// 境界線描画の色が決まっているならば
	if(BorderColor.Enable){
		// αブレンド適用
		BorderColor._AppendAlpha();
		// 描画する．
		DrawBox(Dr.Location.X, Dr.Location.Y, Dr.Width, Dr.Height, BorderColor._GetColor(), FALSE);
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
	// 標準の描画種類を指定する
	Position				= DrawType::Default;
	// 標準幅を取得する
	GetGraphSize(_PictureHandle, &_DefaultSizeW, &_DefaultSizeH);
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
	// 画像が読み込めているなら
	if(_PictureHandle != -1){
		// 普通に返却
		return this->PanelFrame::ToString()
			<< _T(", Path: \"") << Path << _T("\"")
			<< _T(", Turned: ")<< Turned
			<< _T(", Alpha: ")<< Alpha;
	}
	// 読み込めていないなら
	else {
		// エラーを示す
		return this->PanelFrame::ToString()
			<< _T(", Handle: Error");
	}
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			PictureFrame::_SetProperties()
{
	// PanelFrameのものを呼び出す
	PanelFrame::_SetProperties();
	// もし指定されている画像ファイルが変わっているなら
	if(Path != _PicturePath){
		// 現在の画像を破棄して
		DeleteGraph(_PictureHandle);
		// 読み込み直す
		_PictureHandle = LoadGraph(Path);
		// 画像サイズを取得し直す
		GetGraphSize(_PictureHandle, &_DefaultSizeW, &_DefaultSizeH);
		// コピー
		_PicturePath = Path;
	}
}

// ----------------------------------------------------
//	PictureFrame::DrawThisFrame
// ----------------------------------------------------
void			PictureFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// αブレンドを有効化
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	// 描画位置を指定
	_SetDrawPoint(Dr);
	// 拡大描画の時
	if(Position == DrawType::Stretch){
		// 反転が無効なら
		if(!Turned){
			// 全体に広げて描画する
			DrawExtendGraphF(Dr.Location.X, Dr.Location.Y,
				Dr.Location.X + Dr.Width, Dr.Location.Y + Dr.Height, _PictureHandle, TRUE);
		}
		// 反転が有効なら
		else {
			// 横を反転させて描画する
			DrawExtendGraphF(Dr.Location.X + Dr.Width, Dr.Location.Y,
				Dr.Location.X, Dr.Location.Y + Dr.Height, _PictureHandle, TRUE);
		}
	}
	// もし中央拡大描画なら
	else if(Position == DrawType::Zoom){
		// 拡大割合を取得
		double ExtendRate = min((double)Dr.Width / _DefaultSizeW, (double)Dr.Height / _DefaultSizeH);
		// 中心を基準に描画
		DrawRotaGraphF(Dr.Location.X + Dr.Width/2, Dr.Location.Y + Dr.Height/2,
			ExtendRate, 0, _PictureHandle, TRUE, Turned);
	}
	// 普通に描画するなら
	else {
		// 反転描画が無効なら
		if(!Turned){
			// 普通に画像を描画する
			DrawGraphF(Dr.Location.X, Dr.Location.Y, _PictureHandle, TRUE);
		}
		// 反転描画が有効なら
		else {
			// 反転させて画像を描画する
			DrawTurnGraphF(Dr.Location.X, Dr.Location.Y, _PictureHandle, TRUE);
		}
	}
}

// ----------------------------------------------------
//	PictureFrame::GetActualWidth
// ----------------------------------------------------
double			PictureFrame::_GetActualWidth() const
{
	return _DefaultSizeW;
}

// ----------------------------------------------------
//	PictureFrame::GetActualWidth
// ----------------------------------------------------
double			PictureFrame::_GetActualHeight() const
{
	return _DefaultSizeH;
}

// ----------------------------------------------------
//	PictureFrame::GetDrawPosition
// ----------------------------------------------------
void			PictureFrame::_SetDrawPoint(RectangleArea &Dr) const
{
	// 基準とする位置で判定(X座標)．
	switch(this->Position){
		// (X座標)一番左を基準にするなら
		case DrawType::TopLeft:
		case DrawType::MiddleLeft:
		case DrawType::BottomLeft:
			// 特に変化を加えない
			break;
		// (X座標)中心を基準に表示するなら
		case DrawType::TopCenter:
		case DrawType::MiddleCenter:
		case DrawType::BottomCenter:
			// 幅/2
			Dr.Location.X -= Dr.Width/2;
			break;
		// (X座標)一番右を基準に表示するなら
		case DrawType::TopRight:
		case DrawType::MiddleRight:
		case DrawType::BottomRight:
			// 幅
			Dr.Location.X -= Dr.Width;
			break;
		// それ以外なら何もしない
		default:
			break;
	}
	// 基準とする位置で判定(Y座標)．
	switch(this->Position){
		// (Y座標)一番上を基準にするなら
		case DrawType::TopLeft:
		case DrawType::TopCenter:
		case DrawType::TopRight:
			// 特に何もしない
			break;
		// (Y座標)中心を基準に表示するなら
		case DrawType::MiddleLeft:
		case DrawType::MiddleCenter:
		case DrawType::MiddleRight:
			// 縦幅/2
			Dr.Location.X -= Dr.Height / 2;
			break;
		// (Y座標)一番下を基準に表示するなら
		case DrawType::BottomLeft:
		case DrawType::BottomCenter:
		case DrawType::BottomRight:
			// 縦幅
			Dr.Location.X -= Dr.Height;
			break;
		// それ以外なら何もしない
		default:
			break;
	}
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
	return this->PictureFrame::ToString();
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
void			MovieFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// αブレンドを有効化
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	// 描画位置を指定
	_SetDrawPoint(Dr);
}

// ----------------------------------------------------
//	TextFrame
// ----------------------------------------------------
//	TextFrame::TextFrame (Constructor)
// ----------------------------------------------------
				TextFrame::TextFrame()
{
	// 詳細版を呼ぶ
	this->TextFrame::TextFrame(_T(""));
}

// ----------------------------------------------------
//	TextFrame::TextFrame (Constructor)
// ----------------------------------------------------
				TextFrame::TextFrame(String Str)
{
	// 文字列をコピーする
	Text					= Str;
	_Property._BackupStr	= Str;
	// 標準設定に合わせる
	ShowType				= TextShowType::Default;
	Position				= TextPosition::TopLeft;
	HeightInterval			= 0;
	// 標準で文字送りしない
	TextAdvance				= false;
	// PropertyのOwnerを指定する
	_Property._Owner		= this;
}

// ----------------------------------------------------
//	TextFrame::ToString
// ----------------------------------------------------
String			TextFrame::ToString() const
{
	return this->PanelFrame::ToString()
		<< _T(", Text: \"") << Text << _T("\"")
		<< _T(", AdvanceShow: ") << TextAdvance
		<< _T(", Font: {") << TextFont.ToString() << _T("}");
}

// ----------------------------------------------------
//	TextFrame::SetProperties
// ----------------------------------------------------
void			TextFrame::_SetProperties()
{
	// 横幅縦幅を取得する
	this->PanelFrame::_SetProperties();
	auto DrArea = GetActualArea();
	// フォント情報を更新
	TextFont._ReloadFontHandle();
	// Textプロパティが変更されていた/Return表示で(横幅|フォント)が変更された場合
	if(Text != _Property._BackupStr
	|| (ShowType == TextShowType::Return && (DrArea.Width != _Property._Width || TextFont.IsFontChanged()))){
		// 保存しなおす
		_Property._BackupStr = Text;
		_Property._Width = DrArea.Width;
		// DrawTextArrayを指定しなおす
		_Property._SetDrawTextArray();
	}
	// もし文字送り設定で，全表示が終わっていれば
	if(TextAdvance && TextTimer.LoopType == Timer::LoopType::No && TextTimer() >= _Property._TotalTextLenght){
		// 文字送りを終了する
		TextAdvance = false;
	}
	// Timerを更新する
	TextTimer();
}

// ----------------------------------------------------
//	TextFrame::DrawThisFrame
// ----------------------------------------------------
void			TextFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// 描画する文字の総文字数を取得する
	int DrawStrLenght = (TextAdvance ? TextTimer._GetValueNoReload() : _Property._TotalTextLenght);
	// αブレンドを有効化
	TextFont.FontColor._AppendAlpha();
	// 一行ずつ描画を行う
	for(int i = 0; DrawStrLenght > 0; i++){
		// 描画する行の文字列の情報を取得する
		auto StrDt = _Property._DrawTextsArray[i];
		// 描画位置を取得する
		_Property._SetTextDrawStartPoint(Dr, StrDt, i);
		// 描画する文字列を取得する
		String DrawStr = (StrDt.Text.length() <= DrawStrLenght ? StrDt.Text :
			StrDt.Text.substr(0, DrawStrLenght).c_str());
		// もし縮小描画が必要なら
		if(ShowType == TextShowType::Pack && StrDt.Width > Dr.Width){
			// 拡大縮小して描画を行う
			DrawExtendStringToHandle(StrDt.DrStartPt.X, StrDt.DrStartPt.Y,
				(double)Dr.Width / StrDt.Width, 1,
				DrawStr, TextFont.FontColor._GetColor(),
				TextFont._GetFontHandle(), TextFont.EdgeColor._GetColor());
		}
		// 縮小しないなら
		else {
			// 普通に文字列を描画する
			DrawStringToHandle(StrDt.DrStartPt.X, StrDt.DrStartPt.Y,
				DrawStr, TextFont.FontColor._GetColor(),
				TextFont._GetFontHandle(), TextFont.EdgeColor._GetColor());
		}
		// 描画した文字数分残りの描画文字数を減らす
		DrawStrLenght -= DrawStr.length();
	}
}

// ----------------------------------------------------
//	TextFrame::GetSingleLineTextWidth
// ----------------------------------------------------
int				TextFrame::_GetSingleLineTextWidth(const String &DrStr) const
{
	// 取得関数を呼び出し，結果を返却する
	return GetDrawStringWidthToHandle(DrStr, DrStr.length(), TextFont._GetFontHandle());
}

// ----------------------------------------------------
//	TextFrame::GetSingleLineTextHeight
// ----------------------------------------------------
int				TextFrame::_GetSingleLineTextHeight(const String &DrStr) const
{
	// フォント幅を返却
	return TextFont.Size;
}

// ----------------------------------------------------
//	TextFrame::SetDrawTextArray
// ----------------------------------------------------
void			TextFrame::_PropertySaved::_SetDrawTextArray()
{
	// 全削除する
	_DrawTextsArray.clear();
	// 文字列長を初期化する
	_TotalTextLenght = 0;
	// 改行文字でSplitする
	auto StBaseAry = _BackupStr.Split(_T("\n"), true);
	// 行別に分ける
	for(auto Itr = StBaseAry.begin(); Itr != StBaseAry.end(); Itr++){
		// 作成
		TextFrame::_SingleLineTextData StData;
		// もしReturn表示なら
		if(_Owner->ShowType == TextShowType::Return){
			// 適切な長さの幅を取得する
			auto Len = _GetFitTextLenght(*Itr);
			// 取得した幅から文字列を指定する
			StData.Text = Itr->substr(0, Len).c_str();
			// もし残りの分があるなら
			if(Len < Itr->length()){
				// 残りの分は次の行に持ち越す
				Itr = StBaseAry.insert(Itr + 1, Itr->substr(Len, Itr->length()).c_str()) - 1;
			}
		}
		// そうでないなら
		else {
			// 普通に文字列を指定する
			StData.Text = *Itr;
		}
		// 文字列長を指定する
		_TotalTextLenght += StData.Text.length();
		// 縦横幅を指定する
		StData.Width = _Owner->_GetSingleLineTextWidth(StData.Text);
		StData.Height = _Owner->_GetSingleLineTextHeight(StData.Text);
		// 描画文字一覧に追加
		_DrawTextsArray.push_back(StData);
	}
}

// ----------------------------------------------------
//	TextFrame::GetFitTextLenght
// ----------------------------------------------------
unsigned int	TextFrame::_PropertySaved::_GetFitTextLenght(const String &Str) const
{
	// 引数の文字列からtstring文字列を作成
	std::basic_string<TCHAR> tStr = Str;
	// 返却用
	unsigned int Lenght = tStr.length();
	// 文字列の長さが一定幅以下になるまでループを起こす
	while(_Owner->_GetSingleLineTextWidth(tStr.c_str()) > _Width){
		// もし残文字長が1以下なら
		if(Lenght <= 1){
			// 1を返却（こうしないとバグる）
			return 1;
		}
		// 文字数の長さを一文字減らす
		tStr = tStr.substr(0, Lenght - 1);
		// 返却用の文字列長も一文字減らす
		Lenght--;
	}
	// 返却
	return Lenght;
}

// ----------------------------------------------------
//	TextFrame::GetTextDrawStartPoint
// ----------------------------------------------------
void			TextFrame::_PropertySaved::_SetTextDrawStartPoint(RectangleArea &Ar, TextFrame::_SingleLineTextData &StrDt, UINT LineNo) const
{
	// 一時保存用
	double LocX = Ar.Location.X, LocY = Ar.Location.Y;
	// もしPack表示でなく，または幅が自身のフレーム幅より小さいなら
	if(_Owner->ShowType != TextShowType::Pack || StrDt.Width < Ar.Width){
		// ShowPlaceで分ける
		switch(_Owner->Position){
			// 左側描画なら
			case TextPosition::TopLeft:
			case TextPosition::MiddleLeft:
			case TextPosition::BottomLeft:
				// そのまま
				LocX += 0;
				break;
			// 中央描画なら
			case TextPosition::TopCenter:
			case TextPosition::MiddleCenter:
			case TextPosition::BottomCenter:
				// 幅/2を足して指定
				LocX += (double)(Ar.Width - StrDt.Width) / 2;
				break;
			// 右側描画なら
			case TextPosition::TopRight:
			case TextPosition::MiddleRight:
			case TextPosition::BottomRight:
				// 幅を足して指定
				LocX += Ar.Width - StrDt.Width;
				break;
			// それ以外なら
			default:
				LocX = -1;
				break;
		}
	}
	// ShowPlaceで分ける
	switch(_Owner->Position){
		// 上側描画なら
		case TextPosition::TopLeft:
		case TextPosition::TopCenter:
		case TextPosition::TopRight:
			// Y座標そのまま
			LocY += 0;
			break;
		// 中央描画なら
		case TextPosition::MiddleLeft:
		case TextPosition::MiddleCenter:
		case TextPosition::MiddleRight:
			// + (縦幅 - (文字縦幅+Margin)*(元々の行数-1))/2
			LocY += (Ar.Height - (StrDt.Height + _Owner->HeightInterval) * (int)(_DrawTextsArray.size())) / 2;
			break;
		// 下側描画なら
		case TextPosition::BottomLeft:
		case TextPosition::BottomCenter:
		case TextPosition::BottomRight:
			// + (縦幅 - (文字縦幅+Margin)*(元々の行数-1))
			LocY += (Ar.Height - (StrDt.Height + _Owner->HeightInterval) * (int)(_DrawTextsArray.size()));
			break;
		// それ以外なら
		default:
			LocY = -1;
			break;
	}
	// 行数分Y座標を追加する
	LocY += (StrDt.Height + _Owner->HeightInterval) * (LineNo);
	// 代入する
	StrDt.DrStartPt = Point(LocX, LocY);
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
				Font::Font(String FontName, int FontSize, int FontThick, int eSize, Font::FontType::_FontType Ty)
{
	// プロパティをセットする
	Name			= FontName;
	Size			= FontSize;
	Thick			= FontThick;
	Type			= Ty;
	EdgeSize		= eSize;
	// 色を初期化する
	FontColor		= Color::White;
	// ハンドルを初期化する
	_Handle			= -1;
	_IsFontHandleChanged = false;
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
//	Font::IsFontPropertyChange
// ----------------------------------------------------
bool			Font::IsFontChanged() const
{
	// もし変更されているようならtrueを返す
	return (
		Name != _Changed._Name ||
		Size != _Changed._Size ||
		Thick != _Changed._Thick ||
		Type != _Changed._Type ||
		EdgeSize != _Changed._EdgeSize ||
		EdgeColor.Enable != _Changed._IsEnableEdge
	);
}

// ----------------------------------------------------
//	Font::ToString
// ----------------------------------------------------
String			Font::ToString() const
{
	return String()
		<< _T("Name: \"") << Name << _T("\"")
		<< _T(", Size: ") << Size
		<< _T(", Thick: ") << Thick
		<< _T(", Color: ") << FontColor.ToString()
		<< _T(", Edge: ") << EdgeColor.ToString()
		<< _T(", IsChanged: ") << IsFontChanged();
}

// ----------------------------------------------------
//	Font::ReloadFontHandle
// ----------------------------------------------------
void			Font::_ReloadFontHandle()
{
	// もしフォントハンドルが既に直前のフレームで変更されているなら
	if(_IsFontHandleChanged){
		// プロパティを新しい値に更新
		_Changed._Name = Name;
		_Changed._Size = Size;
		_Changed._Thick = Thick;
		_Changed._EdgeSize = EdgeSize;
		_Changed._Type = Type;
		_Changed._IsEnableEdge = EdgeColor.Enable;
		// 変更フラグをfalseに
		_IsFontHandleChanged = false;
	}
	// もしプロパティの中のどれかの値が変更されていたら
	else if(IsFontChanged()){
		// 現在のフォントハンドルを解放して
		DeleteFontToHandle(_Handle);
		// フォントハンドルを更新する
		_Handle	= CreateFontToHandle(Name, Size, Thick, _GetFontDrawType(), -1, EdgeSize);
		// 変更フラグをtrueにする
		_IsFontHandleChanged = true;
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
	switch(Type){
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
	Result += (EdgeColor.Enable ? 1 : 0);
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
