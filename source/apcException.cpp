// --------------------------------------------------------
//	apcException.cpp
// --------------------------------------------------------
//	apcException.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	ApcException
// ----------------------------------------------------
//	ApcException::ApcException (Constructor)
// ----------------------------------------------------
				ApcException::ApcException(String fName, int Line, String Str)
{
	// 設定する
	this->ExcFileName	= fName;
	this->ExcLine		= Line;
	this->ExcString		= Str;
}

// ----------------------------------------------------
//	ApcException::ShowDebugDialog
// ----------------------------------------------------
void			ApcException::ShowMessage() const
{
	// 表示
	MessageBox(GetMainWindowHandle(),
				StrOut << ExcFileName << _T("の") << ExcLine << _T("行目で例外が発生しました。\n") <<
				_T("詳細は以下の通りです。\n-----------------------------------------\n") << ExcString,
				_T("例外が発生しました"), NULL);
	// 終了
	return;
}
