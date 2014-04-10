// --------------------------------------------------------
//	apcValue.cpp
// --------------------------------------------------------
//	apcValue.hpp �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	Timer
// ----------------------------------------------------
//	Timer::Timer (constructor)
// ----------------------------------------------------
				Timer::Timer()
{
	// �����l���w�肷��
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
	// �l������������
	_Val				= 0;
	_IsReturned			= false;
	_LastCalledValue	= (UseFrameCounter ? _FrameCounter::GetCount() : GetNowCount());
}

// ----------------------------------------------------
//	Timer::ToString
// ----------------------------------------------------
String			Timer::ToString() const
{
	// �l��ԋp����
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
	// ����UseFlag���X�V����Ă���Ȃ�
	if(UseFrameCounter != _BackupUseFlag){
		// Flag�ύX�𔽉f������
		_BackupUseFlag = UseFrameCounter;
		// �J�E���^������������
		_LastCalledValue = (UseFrameCounter ? _FrameCounter::GetCount() : GetNowCount());
	}
	// ����FrameCounter���g�p����Ȃ�
	if(UseFrameCounter){
		// �l���X�V����
		_TimerReload((int)(_FrameCounter::GetCount() - _LastCalledValue));
		// �ŏI�Ăяo���l���X�V����
		_LastCalledValue = _FrameCounter::GetCount();
	}
	// ����FrameCounter���g�p���Ȃ��Ȃ�
	else {
		int Count = GetNowCount();
		// �l���X�V����
		_TimerReload(Count - _LastCalledValue);
		// �ŏI�Ăяo���l���X�V����
		_LastCalledValue = Count;
	}
	// �l��ԋp����
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
	// Timer�̍X�V����~����Ă���󋵂Ȃ�
	if(TimerStop){
		// �������Ȃ�
		return;
	}
	// ����������0�łȂ��Ȃ�
	if(Cycle != 0){
		// �K�v�ȏ�ɌJ��Ԃ��Ȃ��悤�ɍŏ����ɗ}����
		CallTimes %= Cycle * 2;
	}
	// �J��Ԃ��񐔕��ǂݍ���
	while(CallTimes > 0 && Enable){
		// �J��Ԃ������֘A�̊֐����Ăяo���C���̏����ɐi�ނ悤�Ȗ߂�l��������
		if(!_RepeatFunc()){
			// �l���Ăяo���p�x�Ŋ��������̂�ǉ�����
			_Val += Add * (_IsReturned ? -1 : 1)
				/ (UseFrameCounter ? ApplicationConfig::Refresh : 1000);
		}
		// �J�E���g��1����
		CallTimes--;
	}
}

// ----------------------------------------------------
//	Timer::RepeatFunc
// ----------------------------------------------------
bool			Timer::_RepeatFunc()
{
	// Timer�����ێ��l���猻�݂̌Ăяo���񐔂��v�Z
	double NowLoop = _Val * (UseFrameCounter ? ApplicationConfig::Refresh : 1000) / Add;
	// �����l��(�������|0��艺)�Ȃ��
	if(Cycle != 0 && (NowLoop >= Cycle || NowLoop < 0)){
		// RepeatType�ŏ�����ς���
		switch(LoopType){
			// �������Ȃ��Ȃ�
			case LoopType::No:
				// true��ԋp���Ēl���ω����Ȃ��悤�ɂ���
				return true;
			// �J��Ԃ��Ȃ�
			case LoopType::Repeat:
				// 0�ɖ߂�
				_Val = 0;
				// true��ԋp���Ēl���ω����Ȃ��悤�ɂ���
				return true;
			// �߂��Ȃ�
			case LoopType::Return:
				// �J��Ԃ���bool���g�O������
				_IsReturned = !_IsReturned;
				// �l�͕ω����Ă����Ȃ�
				return false;
			case LoopType::ReturnOnce:
				// IsReturned��true�Ȃ�l���ω����Ȃ��悤�ɂ���
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
	// �l��ԋp����
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
	// ���
	Location(0, 0);
	Width = 0;
	Height = 0;
}

// ----------------------------------------------------
//	RectangleArea::RectangleArea (constructor)
// ----------------------------------------------------
				RectangleArea::RectangleArea(Point &Pt, int Wid, int Hgt)
{
	// ���
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
	// operator()���Ăяo��
	(*this)(Left, Right, Top, Bottom);
}

// ----------------------------------------------------
//	MarginRectangle::Percentage
// ----------------------------------------------------
MarginRectangle::_Property
				MarginRectangle::Percentage(double Per)
{
	// �����w�肵�ĕԋp����
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
	// ��r���ĕԋp
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
	// �ԋp�p�̗̈�
	RectangleArea Rect;
	// ------------------------------------------------
	// ���ꂼ��̈ʒu�̒l���w�肷��
	Rect.Location.X = ArBase.Location.X + Left.CalclateValue(ArBase.Width);
	Rect.Location.Y = ArBase.Location.Y + Top.CalclateValue(ArBase.Height);
	Rect.Width		= Rect.Location.X + Rect.Width - Right.CalclateValue(ArBase.Width);
	Rect.Height		= Rect.Location.X + Rect.Height- Bottom.CalclateValue(ArBase.Height);
	// �ԋp
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
	// �e�l�ɂ��ꂼ��w�肷��
	this->Left		= Left;
	this->Right		= Right;
	this->Top		= Top;
	this->Bottom	= Bottom;
	// ���g��ԋp����
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
	// �o��
	OutputDebugString(c_str());
	// ���s�𑫂�
	OutputDebugString(_T("\n"));
}

// ----------------------------------------------------
//	String::LogOutput
// ----------------------------------------------------
void			String::LogOutput() const
{
	// ���O�t�@�C���ɏo��
	ErrorLogAdd((*this + _T("\n")).c_str());
}

// ----------------------------------------------------
//	String::Connect
// ----------------------------------------------------
String&			String::Connect(const std::vector<String> &Array)
{
	// �ڍ׃o�[�W�����ɓ�����
	return Connect(Array, _T(""));
}

// ----------------------------------------------------
//	String::Connect
// ----------------------------------------------------
String&			String::Connect(const std::vector<String> &Array, const String& Cs)
{
	// join���g�p���Č�������
	auto StrPtr = new String(boost::join(Array, Cs));
	// �ԋp
	return *StrPtr;
}

// ----------------------------------------------------
//	String::Replace
// ----------------------------------------------------
String&			String::Replace(const String &From, const String &To) const
{
	// String��V�����쐬
	auto Result = new String(*this);
	// From�������Ȃ�܂�
	for(tstring::size_type Pos = 0; (Pos = Result->find(From, Pos)) != tstring::npos;){
		// From��To�ɒu��������
		Result->replace(Pos, From.length(), To.c_str());
		// Pos��u�������������񕪐i�߂�
		Pos += To.length();
	}
	// �Q�Ƃ�ԋp
	return *Result;
}

// ----------------------------------------------------
//	String::Split
// ----------------------------------------------------
std::vector<String>&
				String::Split(const String &Sp) const
{
	// �ڍהłɓ�����
	return Split(Sp, true);
}

// ----------------------------------------------------
//	String::Split
// ----------------------------------------------------
std::vector<String>&
				String::Split(const String &Sp, bool IsSpaceAble) const
{
	// �ꎞ�I�Ɏg�p
	tstring Str;
	// �ԋp����z����쐬
	auto ArgT = std::vector<tstring>();
	auto ArgS = new std::vector<String>();
	// �Ώۂ̕�����replace����
	Str = Replace(Sp, _T("\x01"));
	// boost��split���g�p����
	boost::split(ArgT, Str, boost::is_any_of(_T("\x01")),
		IsSpaceAble ? boost::token_compress_off : boost::token_compress_on);
	// �R�s�[
	for(auto Iter = ArgT.begin(); Iter != ArgT.end(); Iter++)
		ArgS->push_back(Iter->c_str());
	// �ԋp
	return *ArgS;
}

// ----------------------------------------------------
//	String::operator LPCTSTR
// ----------------------------------------------------
				String::operator LPCTSTR() const
{
	// �擾���ĕԋp
	return this->c_str();
}

// ----------------------------------------------------
//	String::operator = (tstring)
// ----------------------------------------------------
String&			String::operator=(tstring Val)
{
	assign(Val);
	// ���g��ԋp
	return *this;
}

// ----------------------------------------------------
//	String::operator = (LPCTSTR)
// ----------------------------------------------------
String&			String::operator=(LPCTSTR Val)
{
	assign(Val);
	// ���g��ԋp
	return *this;
}

// ----------------------------------------------------
//	String::operator ==
// ----------------------------------------------------
bool			String::operator==(String &Str) const
{
	// Compare���Č��ʂ�Ԃ�
	return compare(Str.c_str()) == 0;
}

// ----------------------------------------------------
//	String::operator !=
// ----------------------------------------------------
bool			String::operator!=(String &Str) const
{
	// Compare���Č��ʂ�Ԃ�
	return compare(Str.c_str()) != 0;
}

// ----------------------------------------------------
//	String::operator << (bool)
// ----------------------------------------------------
String&			String::operator<<(const bool Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<LPCTSTR>(Val ? _T("true") : _T("false"));
}

// ----------------------------------------------------
//	String::operator << (int)
// ----------------------------------------------------
String&			String::operator<<(const int Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<int>(Val);
}

// ----------------------------------------------------
//	String::operator << (UINT)
// ----------------------------------------------------
String&			String::operator<<(const UINT Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<UINT>(Val);
}

// ----------------------------------------------------
//	String::operator << (short)
// ----------------------------------------------------
String&			String::operator<<(const short Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<short>(Val);
}

// ----------------------------------------------------
//	String::operator << (USHORT)
// ----------------------------------------------------
String&			String::operator<<(const USHORT Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<USHORT>(Val);
}

// ----------------------------------------------------
//	String::operator << (long)
// ----------------------------------------------------
String&			String::operator<<(const long Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<long>(Val);
}

// ----------------------------------------------------
//	String::operator << (ULONG)
// ----------------------------------------------------
String&			String::operator<<(const ULONG Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<ULONG>(Val);
}

// ----------------------------------------------------
//	String::operator << (double)
// ----------------------------------------------------
String&			String::operator<<(const double Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<double>(Val);
}

// ----------------------------------------------------
//	String::operator << (LPCTSTR)
// ----------------------------------------------------
String&			String::operator<<(const void *Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<const void*>(Val);
}

// ----------------------------------------------------
//	String::operator << (TCHAR)
// ----------------------------------------------------
String&			String::operator<<(const TCHAR Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<TCHAR>(Val);
}

// ----------------------------------------------------
//	String::operator << (LPCTSTR)
// ----------------------------------------------------
String&			String::operator<<(const LPCTSTR Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<LPCTSTR>(Val);
}

// ----------------------------------------------------
//	String::operator << (String)
// ----------------------------------------------------
String&			String::operator<<(const String& Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<String>(Val);
}

// ----------------------------------------------------
//	String::operator << (Point)
// ----------------------------------------------------
String&			String::operator<<(const Point& Val)
{
	// �ǉ����ĕԋp
	return this->FromValue<String>(String() << Val.X << _T(", ") << Val.Y);
}

// ----------------------------------------------------
//	String::FromValue
// ----------------------------------------------------
template<typename Type>
String&			String::FromValue(const Type Val)
{
	// stringstream���g�p����
	std::basic_stringstream<TCHAR> Ss;
	// ----------------------------------------------------
	// ������ɒǉ�
	Ss << Val;
	// �u��������
	append(Ss.str().c_str());
	// �ԋp
	return *this;
}
