// --------------------------------------------------------
//	apcValue.cpp
// --------------------------------------------------------
//	apcValue.hpp のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	Timer
// ----------------------------------------------------
//	Timer::Timer (constructor)
// ----------------------------------------------------
				Timer::Timer()
{
	// 初期値を指定する
	_Val				= 0;
	Add					= 0.0;
	Cycle				= 0;
	Enable				= true;
	LoopType			= LoopType::No;
	TimerStop			= false;
	UseFrameCounter		=
	_BackupUseFlag		= false;
	_IsReturned			= false;
	_LastCalledValue	= (UseFrameCounter ? _FrameCounter::GetCount() : GetNowCount());
}

// ----------------------------------------------------
//	Timer::Reset
// ----------------------------------------------------
void			Timer::Reset()
{
	// 値を初期化する
	_Val				= 0;
	_IsReturned			= false;
	_LastCalledValue	= (UseFrameCounter ? _FrameCounter::GetCount() : GetNowCount());
}

// ----------------------------------------------------
//	Timer::ToString
// ----------------------------------------------------
String			Timer::ToString() const
{
	// 値を返却する
	return String()
		<< _T("Value: ") << _Val
		<< _T(", Add: ") << Add
		<< _T(", Cycle: ") << Cycle
		<< _T(", UseFrameCounter: ") << UseFrameCounter;
}

// ----------------------------------------------------
//	Timer::operator()
// ----------------------------------------------------
double			Timer::operator()()
{
	// もしUseFlagが更新されているなら
	if(UseFrameCounter != _BackupUseFlag){
		// Flag変更を反映させる
		_BackupUseFlag = UseFrameCounter;
		// カウンタを初期化する
		_LastCalledValue = (UseFrameCounter ? _FrameCounter::GetCount() : GetNowCount());
	}
	// もしFrameCounterを使用するなら
	if(UseFrameCounter){
		// 値を更新する
		_TimerReload((int)(_FrameCounter::GetCount() - _LastCalledValue));
		// 最終呼び出し値を更新する
		_LastCalledValue = _FrameCounter::GetCount();
	}
	// もしFrameCounterを使用しないなら
	else {
		int Count = GetNowCount();
		// 値を更新する
		_TimerReload(Count - _LastCalledValue);
		// 最終呼び出し値を更新する
		_LastCalledValue = Count;
	}
	// 値を返却する
	return _Val;
}

// ----------------------------------------------------
//	Timer::GetValueNoReload
// ----------------------------------------------------
double			Timer::_GetValueNoReload() const
{
	return _Val;
}

// ----------------------------------------------------
//	Timer::TimerReload
// ----------------------------------------------------
void			Timer::_TimerReload(int CallTimes)
{
	// Timerの更新が停止されている状況なら
	if(TimerStop){
		// 何もしない
		return;
	}
	// もし周期が0でないなら
	if(Cycle != 0){
		// 必要以上に繰り返さないように最小限に抑える
		CallTimes %= Cycle * 2;
	}
	// 繰り返す回数分読み込む
	while(CallTimes > 0 && Enable){
		// 繰り返し処理関連の関数を呼び出し，次の処理に進むような戻り値だったら
		if(!_RepeatFunc()){
			// 値を呼び出し頻度で割ったものを追加する
			_Val += Add * (_IsReturned ? -1 : 1)
				/ (UseFrameCounter ? ApplicationConfig::Refresh : 1000);
		}
		// カウントを1減少
		CallTimes--;
	}
}

// ----------------------------------------------------
//	Timer::RepeatFunc
// ----------------------------------------------------
bool			Timer::_RepeatFunc()
{
	// Timer内部保持値から現在の呼び出し回数を計算
	double NowLoop = _Val * (UseFrameCounter ? ApplicationConfig::Refresh : 1000) / Add;
	// もし値が(上限より上|0より下)ならば
	if(Cycle != 0 && (NowLoop >= Cycle || NowLoop < 0)){
		// RepeatTypeで処理を変える
		switch(LoopType){
			// 何もしないなら
			case LoopType::No:
				// trueを返却して値が変化しないようにする
				return true;
			// 繰り返すなら
			case LoopType::Repeat:
				// 0に戻す
				_Val = 0;
				// trueを返却して値が変化しないようにする
				return true;
			// 戻すなら
			case LoopType::Return:
				// 繰り返しのboolをトグルする
				_IsReturned = !_IsReturned;
				// 値は変化しても問題なし
				return false;
			case LoopType::ReturnOnce:
				// IsReturnedがtrueなら値が変化しないようにする
				return (!_IsReturned ? !(_IsReturned = !_IsReturned) : true);
		}
	}
	return false;
}

// ----------------------------------------------------
//	Point
// ----------------------------------------------------
//	Point::Point (constructor)
// ----------------------------------------------------
				Point::Point()
{
	X = 0;
	Y = 0;
}

// ----------------------------------------------------
//	Point::Point (constructor)
// ----------------------------------------------------
				Point::Point(double X, double Y)
{
	this->X = X;
	this->Y = Y;
}

// ----------------------------------------------------
//	Point::ToString
// ----------------------------------------------------
String			Point::ToString() const
{
	// 値を返却する
	return String() << _T("X: ") << X << _T(", Y: ") << Y;
}

// ----------------------------------------------------
//	Point::operator ()
// ----------------------------------------------------
void			Point::operator()(double X, double Y)
{
	this->X = X;
	this->Y = Y;
}

// ----------------------------------------------------
//	Point::operator =
// ----------------------------------------------------
Point&			Point::operator=(const Point& Pt)
{
	X = Pt.X;
	Y = Pt.Y;
	return *this;
}

// ----------------------------------------------------
//	Point::operator =
// ----------------------------------------------------
Point&			Point::operator=(double Val)
{
	X = Val;
	Y = Val;
	return *this;
}

// ----------------------------------------------------
//	Point::operator ==
// ----------------------------------------------------
bool			Point::operator==(const Point& Pt) const
{
	return ((this->X == Pt.X) && (this->Y == Pt.Y));
}

// ----------------------------------------------------
//	Point::operator ==
// ----------------------------------------------------
bool			Point::operator!=(const Point& Pt) const 
{
	return ((this->X != Pt.X) || (this->Y != Pt.Y));
}

// ----------------------------------------------------
//	RectangleArea
// ----------------------------------------------------
//	RectangleArea::RectangleArea (constructor)
// ----------------------------------------------------
				RectangleArea::RectangleArea()
{
	// 代入
	Location(0, 0);
	Width = 0;
	Height = 0;
}

// ----------------------------------------------------
//	RectangleArea::RectangleArea (constructor)
// ----------------------------------------------------
				RectangleArea::RectangleArea(Point &Pt, int Wid, int Hgt)
{
	// 代入
	Location = Pt;
	Width = Wid;
	Height = Hgt;
}

// ----------------------------------------------------
//	RectangleArea::ToString
// ----------------------------------------------------
String			RectangleArea::ToString() const
{
	return String()
		<< _T("Location: ") << Location.ToString()
		<< _T(", Width") << Width
		<< _T(", Height") << Height;
}

// ----------------------------------------------------
//	MarginRectangle
// ----------------------------------------------------
//	MarginRectangle::Auto (Global)
// ----------------------------------------------------
const MarginRectangle::_Property
				MarginRectangle::Auto(true);

// ----------------------------------------------------
//	MarginRectangle::MarginRectangle (constructor)
// ----------------------------------------------------
				MarginRectangle::MarginRectangle(){}

// ----------------------------------------------------
//	MarginRectangle::MarginRectangle (constructor)
// ----------------------------------------------------
				MarginRectangle::MarginRectangle(double Left, double Right, double Top, double Bottom)
{
	// operator()を呼び出す
	(*this)(Left, Right, Top, Bottom);
}

// ----------------------------------------------------
//	MarginRectangle::Percentage
// ----------------------------------------------------
MarginRectangle::_Property
				MarginRectangle::Percentage(double Per)
{
	// 割合指定して返却する
	_Property Prop;
	Prop.Auto = false;
	Prop.Percent = true;
	Prop = Per;
	return Prop;
}

// ----------------------------------------------------
//	MarginRectangle::Compare
// ----------------------------------------------------
bool			MarginRectangle::Compare(const MarginRectangle &Rc) const
{
	// 比較して返却
	return Left == Rc.Left
		&& Right == Rc.Right
		&& Top == Rc.Top
		&& Bottom == Rc.Bottom;
}

// ----------------------------------------------------
//	MarginRectangle::CalcrationArea
// ----------------------------------------------------
RectangleArea	MarginRectangle::CalclationArea(const RectangleArea &ArBase) const
{
	// 返却用の領域
	RectangleArea Rect;
	// ------------------------------------------------
	// それぞれの位置の値を指定する
	Rect.Location.X = ArBase.Location.X + Left.CalclateValue(ArBase.Width);
	Rect.Location.Y = ArBase.Location.Y + Top.CalclateValue(ArBase.Height);
	Rect.Width		= Rect.Location.X + Rect.Width - Right.CalclateValue(ArBase.Width);
	Rect.Height		= Rect.Location.X + Rect.Height- Bottom.CalclateValue(ArBase.Height);
	// 返却
	return Rect;
}
// ----------------------------------------------------
//	MarginRectangle::ToString
// ----------------------------------------------------
String			MarginRectangle::ToString() const
{
	return String()
		<< _T("Left: ")		<< Left.ToString()
		<< _T(", Right: ")	<< Right.ToString()
		<< _T(", Top: ")	<< Top.ToString()
		<< _T(", Bottom: ")	<< Bottom.ToString();
}

// ----------------------------------------------------
//	MarginRectangle::operator()
// ----------------------------------------------------
MarginRectangle&
				MarginRectangle::operator()(double Left, double Right, double Top, double Bottom)
{
	// 各値にそれぞれ指定する
	this->Left		= Left;
	this->Right		= Right;
	this->Top		= Top;
	this->Bottom	= Bottom;
	// 自身を返却する
	return *this;
}

// ----------------------------------------------------
//	String
// ----------------------------------------------------
//	String::String (constructor)
// ----------------------------------------------------
				String::String(LPCTSTR Text)
{
	assign(Text);
}

// ----------------------------------------------------
//	String::DebugOutput
// ----------------------------------------------------
void			String::DebugOutput() const
{
	// 出力
	OutputDebugString(c_str());
	// 改行を足す
	OutputDebugString(_T("\n"));
}

// ----------------------------------------------------
//	String::LogOutput
// ----------------------------------------------------
void			String::LogOutput() const
{
	// ログファイルに出力
	ErrorLogAdd((*this + _T("\n")).c_str());
}

// ----------------------------------------------------
//	String::Connect
// ----------------------------------------------------
String&			String::Connect(const std::vector<String> &Array)
{
	// 詳細バージョンに投げる
	return Connect(Array, _T(""));
}

// ----------------------------------------------------
//	String::Connect
// ----------------------------------------------------
String&			String::Connect(const std::vector<String> &Array, const String& Cs)
{
	// joinを使用して結合する
	auto StrPtr = new String(boost::join(Array, Cs));
	// 返却
	return *StrPtr;
}

// ----------------------------------------------------
//	String::Replace
// ----------------------------------------------------
String&			String::Replace(const String &From, const String &To) const
{
	// Stringを新しく作成
	auto Result = new String(*this);
	// Fromが無くなるまで
	for(tstring::size_type Pos = 0; (Pos = Result->find(From, Pos)) != tstring::npos;){
		// FromをToに置き換える
		Result->replace(Pos, From.length(), To.c_str());
		// Posを置き換えた文字列分進める
		Pos += To.length();
	}
	// 参照を返却
	return *Result;
}

// ----------------------------------------------------
//	String::Split
// ----------------------------------------------------
std::vector<String>&
				String::Split(const String &Sp) const
{
	// 詳細版に投げる
	return Split(Sp, true);
}

// ----------------------------------------------------
//	String::Split
// ----------------------------------------------------
std::vector<String>&
				String::Split(const String &Sp, bool IsSpaceAble) const
{
	// 一時的に使用
	tstring Str;
	// 返却する配列を作成
	auto ArgT = std::vector<tstring>();
	auto ArgS = new std::vector<String>();
	// 対象の文字をreplaceする
	Str = Replace(Sp, _T("\x01"));
	// boostのsplitを使用する
	boost::split(ArgT, Str, boost::is_any_of(_T("\x01")),
		IsSpaceAble ? boost::token_compress_off : boost::token_compress_on);
	// コピー
	for(auto Iter = ArgT.begin(); Iter != ArgT.end(); Iter++)
		ArgS->push_back(Iter->c_str());
	// 返却
	return *ArgS;
}

// ----------------------------------------------------
//	String::operator LPCTSTR
// ----------------------------------------------------
				String::operator LPCTSTR() const
{
	// 取得して返却
	return this->c_str();
}

// ----------------------------------------------------
//	String::operator = (tstring)
// ----------------------------------------------------
String&			String::operator=(tstring Val)
{
	assign(Val);
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	String::operator = (LPCTSTR)
// ----------------------------------------------------
String&			String::operator=(LPCTSTR Val)
{
	assign(Val);
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	String::operator ==
// ----------------------------------------------------
bool			String::operator==(String &Str) const
{
	// Compareして結果を返す
	return compare(Str.c_str()) == 0;
}

// ----------------------------------------------------
//	String::operator !=
// ----------------------------------------------------
bool			String::operator!=(String &Str) const
{
	// Compareして結果を返す
	return compare(Str.c_str()) != 0;
}

// ----------------------------------------------------
//	String::operator << (bool)
// ----------------------------------------------------
String&			String::operator<<(const bool Val)
{
	// 追加して返却
	return this->FromValue<LPCTSTR>(Val ? _T("true") : _T("false"));
}

// ----------------------------------------------------
//	String::operator << (int)
// ----------------------------------------------------
String&			String::operator<<(const int Val)
{
	// 追加して返却
	return this->FromValue<int>(Val);
}

// ----------------------------------------------------
//	String::operator << (UINT)
// ----------------------------------------------------
String&			String::operator<<(const UINT Val)
{
	// 追加して返却
	return this->FromValue<UINT>(Val);
}

// ----------------------------------------------------
//	String::operator << (short)
// ----------------------------------------------------
String&			String::operator<<(const short Val)
{
	// 追加して返却
	return this->FromValue<short>(Val);
}

// ----------------------------------------------------
//	String::operator << (USHORT)
// ----------------------------------------------------
String&			String::operator<<(const USHORT Val)
{
	// 追加して返却
	return this->FromValue<USHORT>(Val);
}

// ----------------------------------------------------
//	String::operator << (long)
// ----------------------------------------------------
String&			String::operator<<(const long Val)
{
	// 追加して返却
	return this->FromValue<long>(Val);
}

// ----------------------------------------------------
//	String::operator << (ULONG)
// ----------------------------------------------------
String&			String::operator<<(const ULONG Val)
{
	// 追加して返却
	return this->FromValue<ULONG>(Val);
}

// ----------------------------------------------------
//	String::operator << (double)
// ----------------------------------------------------
String&			String::operator<<(const double Val)
{
	// 追加して返却
	return this->FromValue<double>(Val);
}

// ----------------------------------------------------
//	String::operator << (LPCTSTR)
// ----------------------------------------------------
String&			String::operator<<(const void *Val)
{
	// 追加して返却
	return this->FromValue<const void*>(Val);
}

// ----------------------------------------------------
//	String::operator << (TCHAR)
// ----------------------------------------------------
String&			String::operator<<(const TCHAR Val)
{
	// 追加して返却
	return this->FromValue<TCHAR>(Val);
}

// ----------------------------------------------------
//	String::operator << (LPCTSTR)
// ----------------------------------------------------
String&			String::operator<<(const LPCTSTR Val)
{
	// 追加して返却
	return this->FromValue<LPCTSTR>(Val);
}

// ----------------------------------------------------
//	String::operator << (String)
// ----------------------------------------------------
String&			String::operator<<(const String& Val)
{
	// 追加して返却
	return this->FromValue<String>(Val);
}

// ----------------------------------------------------
//	String::operator << (Point)
// ----------------------------------------------------
String&			String::operator<<(const Point& Val)
{
	// 追加して返却
	return this->FromValue<String>(String() << Val.X << _T(", ") << Val.Y);
}

// ----------------------------------------------------
//	String::FromValue
// ----------------------------------------------------
template<typename Type>
String&			String::FromValue(const Type Val)
{
	// stringstreamを使用する
	std::basic_stringstream<TCHAR> Ss;
	// ----------------------------------------------------
	// 文字列に追加
	Ss << Val;
	// 置き換える
	append(Ss.str().c_str());
	// 返却
	return *this;
}
