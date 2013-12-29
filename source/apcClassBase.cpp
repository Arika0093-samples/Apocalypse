// --------------------------------------------------------
//	apcClassBase.cpp
// --------------------------------------------------------
//	apcClassBase.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.hpp"

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
//	Point::operator =
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
//	Point::operator +
// ----------------------------------------------------
Point&			Point::operator+(Point& Pt)
{
	Point *Result = new Point();
	Result->X = this->X + Pt.X;
	Result->Y = this->Y + Pt.Y;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator +
// ----------------------------------------------------
Point&			Point::operator+(double Val)
{
	Point *Result = new Point();
	Result->X = this->X + Val;
	Result->Y = this->Y + Val;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator -
// ----------------------------------------------------
Point&			Point::operator-(Point& Pt)
{
	Point *Result = new Point();
	Result->X = this->X - Pt.X;
	Result->Y = this->Y - Pt.Y;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator -
// ----------------------------------------------------
Point&			Point::operator-(double Val)
{
	Point *Result = new Point();
	Result->X = this->X - Val;
	Result->Y = this->Y - Val;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator *
// ----------------------------------------------------
Point&			Point::operator*(Point& Pt)
{
	Point *Result = new Point();
	Result->X = this->X * Pt.X;
	Result->Y = this->Y * Pt.Y;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator *
// ----------------------------------------------------
Point&			Point::operator*(double Val)
{
	Point *Result = new Point();
	Result->X = this->X * Val;
	Result->Y = this->Y * Val;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator /
// ----------------------------------------------------
Point&			Point::operator/(Point& Pt)
{
	Point *Result = new Point();
	Result->X = this->X / Pt.X;
	Result->Y = this->Y / Pt.Y;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator /
// ----------------------------------------------------
Point&			Point::operator/(double Val)
{
	Point *Result = new Point();
	Result->X = this->X / Val;
	Result->Y = this->Y / Val;
	return *Result;
}

// ----------------------------------------------------
//	Point::operator +=
// ----------------------------------------------------
Point&			Point::operator+=(Point& Pt)
{
	this->X += Pt.X;
	this->Y += Pt.Y;
	return *this;
}

// ----------------------------------------------------
//	Point::operator +=
// ----------------------------------------------------
Point&			Point::operator+=(double Val)
{
	this->X += Val;
	this->Y += Val;
	return *this;
}

// ----------------------------------------------------
//	Point::operator -=
// ----------------------------------------------------
Point&			Point::operator-=(Point& Pt)
{
	this->X -= Pt.X;
	this->Y -= Pt.Y;
	return *this;
}

// ----------------------------------------------------
//	Point::operator -=
// ----------------------------------------------------
Point&			Point::operator-=(double Val)
{
	this->X -= Val;
	this->Y -= Val;
	return *this;
}

// ----------------------------------------------------
//	Point::operator *=
// ----------------------------------------------------
Point&			Point::operator*=(Point& Pt)
{
	this->X *= Pt.X;
	this->Y *= Pt.Y;
	return *this;
}

// ----------------------------------------------------
//	Point::operator *=
// ----------------------------------------------------
Point&			Point::operator*=(double Val)
{
	this->X *= Val;
	this->Y *= Val;
	return *this;
}

// ----------------------------------------------------
//	Point::operator /=
// ----------------------------------------------------
Point&			Point::operator/=(Point& Pt)
{
	this->X /= Pt.X;
	this->Y /= Pt.Y;
	return *this;
}

// ----------------------------------------------------
//	Point::operator /=
// ----------------------------------------------------
Point&			Point::operator/=(double Val)
{
	this->X /= Val;
	this->Y /= Val;
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
//	String::operator LPCTSTR
// ----------------------------------------------------
				String::operator LPCTSTR() const
{
	// 取得して返却
	return this->c_str();
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
String&			String::operator<<(LPCTSTR Val)
{
	// 追加して返却
	return this->FromValue<LPCTSTR>(Val);
}

// ----------------------------------------------------
//	String::operator << (LPCTSTR)
// ----------------------------------------------------
String&			String::operator<<(const String& Val)
{
	// 追加して返却
	return this->FromValue<String>(Val);
}

// ----------------------------------------------------
//	String::Message
// ----------------------------------------------------
void			String::Message() const
{
	// 表示
	MessageBox(GetMainWindowHandle(), c_str(), _T(""), MB_OK | MB_ICONINFORMATION);
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
