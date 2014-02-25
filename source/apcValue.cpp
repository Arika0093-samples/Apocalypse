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
	LoopType			= _LoopType::No;
	_IsReturned			= false;
	_LastCalledFrame	= __FrameCounter::GetCount();
}

// ----------------------------------------------------
//	Timer::Reset
// ----------------------------------------------------
void			Timer::Reset()
{
	_Val				= 0;
	_IsReturned			= false;
	_LastCalledFrame	= __FrameCounter::GetCount();
}

// ----------------------------------------------------
//	Timer::ToString
// ----------------------------------------------------
String			Timer::ToString() const
{
	// 値を返却する
	return String() << _T("Value: ") << _Val <<
		_T(", Add: ") << Add << _T(", Cycle: ") << Cycle;
}

// ----------------------------------------------------
//	Timer::operator()
// ----------------------------------------------------
double			Timer::operator()()
{
	// 値を更新する
	_TimerReload((int)(__FrameCounter::GetCount() - _LastCalledFrame));
	// FC値を更新する
	_LastCalledFrame = __FrameCounter::GetCount();
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
	// もし周期が0でないなら
	if(Cycle != 0){
		// 必要以上に繰り返さないように最小限に抑える
		CallTimes %= Cycle * 2;
	}
	// 繰り返す回数分読み込む
	while(CallTimes > 0 && Enable){
		// 繰り返し処理関連の関数を呼び出し，次の処理に進むような戻り値だったら
		if(!_RepeatFunc()){
			// 値を追加する
			_Val += Add * (_IsReturned ? -1 : 1);
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
	// もし周期が(上限|0)より(上|下)ならば
	if(Cycle != 0 && (_Val / Add >= Cycle || _Val / Add < 0)){
		// RepeatTypeで処理を変える
		switch(LoopType){
			// 何もしないなら
			case _LoopType::No:
				// trueを返却して値が変化しないようにする
				return true;
			// 繰り返すなら
			case _LoopType::Repeat:
				// 0に戻す
				_Val = 0;
				// trueを返却して値が変化しないようにする
				return true;
			// 戻すなら
			case _LoopType::Return:
				// 繰り返しのboolをトグルする
				_IsReturned = !_IsReturned;
				// 値は変化しても問題なし
				return false;
			case _LoopType::ReturnOnce:
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
Point&			Point::operator=(Point& Pt)
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
bool			Point::operator==(Point& Pt)
{
	return ((this->X == Pt.X) && (this->Y == Pt.Y));
}

// ----------------------------------------------------
//	Point::operator ==
// ----------------------------------------------------
bool			Point::operator!=(Point& Pt)
{
	return ((this->X != Pt.X) || (this->Y != Pt.Y));
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
//	String::Message
// ----------------------------------------------------
void			String::Message() const
{
	// 表示
	MessageBox(GetMainWindowHandle(), c_str(), _T("Message"), MB_OK | MB_ICONINFORMATION);
}

// ----------------------------------------------------
//	String::Message
// ----------------------------------------------------
int				String::Message(unsigned int Style) const
{
	// 表示
	return MessageBox(GetMainWindowHandle(), c_str(), _T("Information"), Style);
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
std::vector<String>
				String::Split(const String &Sp) const
{
	// 詳細版に投げる
	return Split(Sp, true);
}

// ----------------------------------------------------
//	String::Split
// ----------------------------------------------------
std::vector<String>
				String::Split(const String &Sp, bool IsSpaceAble) const
{
	// 一時的に使用
	tstring Str;
	// 返却する配列を作成
	auto ArgT = std::vector<tstring>();
	auto ArgS = std::vector<String>();
	// 対象の文字をreplaceする
	Str = Replace(Sp, _T("\x01"));
	// boostのsplitを使用する
	boost::split(ArgT, Str, boost::is_any_of(_T("\x01")),
		IsSpaceAble ? boost::token_compress_on : boost::token_compress_off);
	// コピー
	for(auto Iter = ArgT.begin(); Iter != ArgT.end(); Iter++)
		ArgS.push_back(Iter->c_str());
	// 返却
	return ArgS;
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
