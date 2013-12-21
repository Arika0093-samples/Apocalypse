// --------------------------------------------------------
//	apcException.cpp
// --------------------------------------------------------
//	apcException.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	ApcException
// ----------------------------------------------------
//	ApcException::ApcException (Constructor)
// ----------------------------------------------------
				ApcException::ApcException(String fName, int Line, String Str)
{
	// �ݒ肷��
	this->ExcFileName	= fName;
	this->ExcLine		= Line;
	this->ExcString		= Str;
}

// ----------------------------------------------------
//	ApcException::ShowDebugDialog
// ----------------------------------------------------
void			ApcException::ShowMessage() const
{
	// �\��
	MessageBox(GetMainWindowHandle(),
				StrOut << ExcFileName << _T("��") << ExcLine << _T("�s�ڂŗ�O���������܂����B\n") <<
				_T("�ڍׂ͈ȉ��̒ʂ�ł��B\n-----------------------------------------\n") << ExcString,
				_T("��O���������܂���"), NULL);
	// �I��
	return;
}
