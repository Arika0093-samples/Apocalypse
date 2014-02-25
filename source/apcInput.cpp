// --------------------------------------------------------
//	apcInput.cpp
// --------------------------------------------------------
//	apcInput.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	Key
// ----------------------------------------------------
//	Key::Key (Constructor)
// ----------------------------------------------------
				KeyBoard::KeyBoard()
{
	// �L�[�̏�Ԓl�����Z�b�g����
	memset(_KeyInput, 0, sizeof(_KeyInput));
	return;
}

// ----------------------------------------------------
//	Key::AnyKeyPushing
// ----------------------------------------------------
bool			KeyBoard::AnyPushing()
{
	// ���͏�Ԃ�ԋp����
	return (CheckHitKeyAll() != 0);
}

// ----------------------------------------------------
//	Key::KeyPushing
// ----------------------------------------------------
UINT			KeyBoard::Pushing(const __KeysData &TargetKey)
{
	// ���ʕԋp�p
	int Result = 0;
	// �L�[�̏�Ԃ��擾����
	for(size_t i = 0; i < TargetKey._Size(); i++){
		// �����������or�O�̒l��菬�����Ȃ�
		if(Result == 0 || Result > GetInstance()._KeyInput[TargetKey._Get(i)]){
			// �擾
			Result = GetInstance()._KeyInput[TargetKey._Get(i)];
		}
		// �����l���}�C�i�X�őS��������Ȃ�
		if((Result < 0) && TargetKey.IsCheckAllKey){
			// ������Ă��Ȃ�
			return 0;
		}
	}
	// �ԋp
	return max(Result, 0);
}

// ----------------------------------------------------
//	Key::KeyPushStarted
// ----------------------------------------------------
bool			KeyBoard::PushStart(const __KeysData &TargetKey)
{
	// ���ʕԋp�p
	bool Result = false, NowTime = false;
	// �L�[�̏�Ԃ��擾����
	for(size_t i = 0; i < TargetKey._Size(); i++){
		// �Ώۂ̃L�[��������Ă邩�m�F
		Result	= (GetInstance()._KeyInput[TargetKey._Get(i)] > 0);
		// 1�ȏ�̃L�[�����݉����ꂽ�΂��肩�ǂ����擾
		NowTime = (NowTime ? true : (GetInstance()._KeyInput[TargetKey._Get(i)] == 1));
		// �����l��false�őS��������Ȃ�
		if(!Result && TargetKey.IsCheckAllKey){
			// ������Ă��Ȃ�
			return false;
		}
	}
	// �S��������Ȃ�ΏۃL�[���S�ĉ�����Ă��邩�ǂ��� + ���݂ǂꂩ��ȏオ�����ꂽ��
	// �����łȂ��Ȃ猻�݂ǂꂩ��ȏオ�����ꂽ���̏���ԋp����
	return (( Result || !TargetKey.IsCheckAllKey) && NowTime);
}

// ----------------------------------------------------
//	Key::KeyPushStarted
// ----------------------------------------------------
bool			KeyBoard::OutStart(const __KeysData &TargetKey)
{
	// ���ʕԋp�p
	bool Result = false, NowTime = false;
	// �L�[�̏�Ԃ��擾����
	for(size_t i = 0; i < TargetKey._Size(); i++){
		// �Ώۂ̃L�[��������Ă��邩�m�F
		Result	= (GetInstance()._KeyInput[TargetKey._Get(i)] < 0);
		// 1�ȏ�̃L�[�����ݗ����ꂽ�΂��肩�ǂ����擾
		NowTime = (NowTime ? true : (GetInstance()._KeyInput[TargetKey._Get(i)] == -1));
		// �����l��false�őS��������Ȃ�
		if(!Result && TargetKey.IsCheckAllKey){
			// ������Ă���
			return false;
		}
	}
	// �S��������Ȃ�ΏۃL�[���S�ė�����Ă��邩�ǂ��� + ���݂ǂꂩ��ȏオ�����ꂽ��
	// �����łȂ��Ȃ猻�݂ǂꂩ��ȏオ�����ꂽ���̏���ԋp����
	return (( Result || !TargetKey.IsCheckAllKey) && NowTime);
}

// ----------------------------------------------------
//	Key::ToString
// ----------------------------------------------------
String			KeyBoard::ToString() const
{
	// �ԋp���镶����
	String Result;
	// for���[�v�őS�L�[�{�[�h�̏�Ԃ𕶎��Ɋi�[
	for(int i = 0; i < sizeof(_KeyInput) / sizeof(int); i++){
		// ����
		Result << _KeyInput[i] << _T(",");
	}
	return Result;
}

// ----------------------------------------------------
//	Key::_CheckKeyEvent
// ----------------------------------------------------
void			KeyBoard::_CheckKeyEvent()
{
	// �L�[�̏�Ԃ��擾���邽�߂̕ϐ�
	char KeyEvent[256];
	// ------------------------------------------------
	// �擾����
	GetHitKeyStateAll(KeyEvent);
	// �v�f���������[�v����
	for(int Loop = 0; Loop < 256; Loop++)
	{
		// ����������Ă���
		if(KeyEvent[Loop] == 1){
			// ���߂ĉ�����Ă��Ȃ�
			if(_KeyInput[Loop] < 0){
				// 0�Ƀ��Z�b�g
				_KeyInput[Loop] = 0;
			}
			// �C���N�������g����
			_KeyInput[Loop]++;
		}
		// ����������Ă��Ȃ���
		else{
			// �����L�[�̒l��0�Ȃ�i������ԂȂ�j
			if(_KeyInput[Loop] == 0){
				// �������đ��s����
				continue;
			}
			// ���߂ė����ꂽ�Ȃ�
			if(_KeyInput[Loop] > 0){
				// 0�Ƀ��Z�b�g
				_KeyInput[Loop] = 0;
			}
			// �f�N�������g����
			_KeyInput[Loop]--;
		}
	}
	// �I��
	return;
}

// ----------------------------------------------------
//	Mouse
// ----------------------------------------------------
//	Mouse::Mouse
// ----------------------------------------------------
				Mouse::Mouse()
{
	_MousePushTimeLeft = 0;
	_MousePushTimeRight = 0;
}

// ----------------------------------------------------
//	Mouse::MousePushing
// ----------------------------------------------------
int				Mouse::LeftPushing()
{
	// �}�E�X�̏�Ԃ��擾���Đ��̒l�Ȃ炻�̂܂ܕԋp����
	return (GetInstance()._MousePushTimeLeft > 0 ?
			GetInstance()._MousePushTimeLeft : 0);
}

// ----------------------------------------------------
//	Mouse::MousePushStarted
// ----------------------------------------------------
bool			Mouse::LeftPushStart()
{
	// �}�E�X��Ԃ��擾���ĉ����ꂽ�u�ԂȂ�true��Ԃ�
	return (GetInstance()._MousePushTimeLeft == 1);
}

// ----------------------------------------------------
//	Mouse::MouseOutStart
// ----------------------------------------------------
bool			Mouse::LeftOutStart()
{
	// �}�E�X��Ԃ��擾���ė����ꂽ�u�ԂȂ�true��Ԃ�
	return (GetInstance()._MousePushTimeLeft == -1);
}

// ----------------------------------------------------
//	Mouse::MousePushing
// ----------------------------------------------------
int				Mouse::RightPushing()
{
	// �}�E�X�̏�Ԃ��擾���Đ��̒l�Ȃ炻�̂܂ܕԋp����
	return (GetInstance()._MousePushTimeRight > 0 ?
			GetInstance()._MousePushTimeRight : 0);
}

// ----------------------------------------------------
//	Mouse::MousePushStarted
// ----------------------------------------------------
bool			Mouse::RightPushStart()
{
	// �}�E�X��Ԃ��擾���ĉ����ꂽ�u�ԂȂ�true��Ԃ�
	return (GetInstance()._MousePushTimeRight == 1);
}

// ----------------------------------------------------
//	Mouse::MouseOutStart
// ----------------------------------------------------
bool			Mouse::RightOutStart()
{
	// �}�E�X��Ԃ��擾���ė����ꂽ�u�ԂȂ�true��Ԃ�
	return (GetInstance()._MousePushTimeRight == -1);
}

// ----------------------------------------------------
//	Mouse::IsMove
// ----------------------------------------------------
bool			Mouse::IsMove()
{
	return (GetInstance()._MouseLocation != GetInstance()._MouseBeforeLoc);
}

// ----------------------------------------------------
//	Mouse::GetMousePosition
// ----------------------------------------------------
Value::Point	Mouse::GetPosition()
{
	// �擾���Ă������}�E�X�ʒu��ԋp����
	return GetInstance()._MouseLocation;
}

// ----------------------------------------------------
//	Mouse::SetMousePosition
// ----------------------------------------------------
void			Mouse::SetPosition(int X, int Y)
{
	// �}�E�X�ʒu���w��̈ʒu�Ɉړ�������
	SetMousePoint( X, Y);
	// ���炩���ߎ擾�����ʒu���ύX����
	GetInstance()._MouseLocation.X = X;
	GetInstance()._MouseLocation.Y = Y;
	// �I��
	return;
}

// ----------------------------------------------------
//	Mouse::ToString
// ----------------------------------------------------
String			Mouse::ToString() const
{
	// ���̉�����Ă鎞�� / �E�̉�����Ă鎞��
	return String() << _T("Left: ") << LeftPushing()
		<< _T(", Right: ") << RightPushing();
}

// ----------------------------------------------------
//	Mouse::CheckMouseEvent
// ----------------------------------------------------
void			Mouse::_CheckMouseEvent()
{
	// �}�E�X��X, Y���W���擾���邽�߂̕ϐ�
	int MouseX, MouseY;
	// ------------------------------------------------
	// �����}�E�X��������Ă���
	if(GetMouseInput() & MOUSE_INPUT_LEFT){
		// ���߂ĉ�����Ă��Ȃ�
		if(_MousePushTimeLeft < 0){
			// 0�Ƀ��Z�b�g
			_MousePushTimeLeft = 0;
		}
		// �C���N�������g����
		_MousePushTimeLeft++;
	}
	// �����}�E�X��������Ă��Ȃ���
	else{
		// ���߂ė����ꂽ�Ȃ�
		if(_MousePushTimeLeft > 0){
			// 0�Ƀ��Z�b�g
			_MousePushTimeLeft = 0;
		}
		// �f�N�������g����
		_MousePushTimeLeft--;
	}
	// �����}�E�X��������Ă���
	if(GetMouseInput() & MOUSE_INPUT_RIGHT){
		// ���߂ĉ�����Ă��Ȃ�
		if(_MousePushTimeRight < 0){
			// 0�Ƀ��Z�b�g
			_MousePushTimeRight = 0;
		}
		// �C���N�������g����
		_MousePushTimeRight++;
	}
	// �����}�E�X��������Ă��Ȃ���
	else{
		// ���߂ė����ꂽ�Ȃ�
		if(_MousePushTimeRight > 0){
			// 0�Ƀ��Z�b�g
			_MousePushTimeRight = 0;
		}
		// �f�N�������g����
		_MousePushTimeRight--;
	}
	// ���݈ʒu���擾
	GetMousePoint( &MouseX, &MouseY );
	// ���݂̍��W��ۑ�
	_MouseBeforeLoc = _MouseLocation;
	// �擾�������ʂ�������
	_MouseLocation( MouseX, MouseY);
	// �I��
	return;
}

// ----------------------------------------------------
//	__KeysData
// ----------------------------------------------------
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData()
{
	// ������
	_CheckKeyList.clear();
	// ���胂�[�h���w��
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData(int FstKey)
{
	// ������
	_CheckKeyList.clear();
	// �ǉ�
	_CheckKeyList.insert(FstKey);
	// ���胂�[�h���w��
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData(int FstKey_1, int FstKey_2)
{
	// ������
	_CheckKeyList.clear();
	// �ǉ�
	_CheckKeyList.insert(FstKey_1);
	_CheckKeyList.insert(FstKey_2);
	// ���胂�[�h���w��
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData(int Fst__KeysData[], size_t Size)
{
	// ������
	_CheckKeyList.clear();
	// ���[�v����
	for(size_t i = 0; i < Size; i++){
		// �ǉ�
		_CheckKeyList.insert(Fst__KeysData[i]);
	}
	// ���胂�[�h���w��
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	__KeysData::Compare
// ----------------------------------------------------
bool			__KeysData::Compare(const __KeysData &KeyList) const
{
	// �����T�C�Y���Ⴄ�Ȃ�
	if(_Size() != KeyList._Size()){
		// false
		return false;
	}
	// ���[�v����
	for(size_t i = 0; i < _Size(); i++){
		// ������v���Ȃ��v�f�����݂���Ȃ�
		if(KeyList && _Get(i) == false){
			// false
			return false;
		}
	}
	return true;
}

// ----------------------------------------------------
//	__KeysData::operator+
// ----------------------------------------------------
__KeysData&		__KeysData::operator+(const __KeysData &KeyList) const
{
	// ���g���R�s�[
	__KeysData* New__KeysData = new __KeysData(*this);
	// ������ǉ�
	*New__KeysData += KeyList;
	// �ԋp
	return *New__KeysData;
}

// ----------------------------------------------------
//	__KeysData::operator-
// ----------------------------------------------------
__KeysData&		__KeysData::operator-(const __KeysData &KeyList) const
{
	// ���g���R�s�[
	__KeysData* New__KeysData = new __KeysData(*this);
	// ����������
	*New__KeysData -= KeyList;
	// �ԋp
	return *New__KeysData;
}

// ----------------------------------------------------
//	__KeysData::operator+=
// ----------------------------------------------------
__KeysData&		__KeysData::operator+=(const __KeysData &KeyList)
{
	// �ǉ����Ă���
	for(size_t i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.insert(KeyList._Get(i));
	}
	// ���g��ԋp
	return *this;
}

// ----------------------------------------------------
//	__KeysData::operator-=
// ----------------------------------------------------
__KeysData&		__KeysData::operator-=(const __KeysData &KeyList)
{
	// �폜���Ă���
	for(size_t i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.erase(KeyList._Get(i));
	}
	// ���g��ԋp
	return *this;
}

// ----------------------------------------------------
//	__KeysData::operator&&
// ----------------------------------------------------
bool			__KeysData::operator&&(int Key) const
{
	// �l���܂܂�Ă���Ȃ�true
	return (_CheckKeyList.count(Key) >= 1);
}

// ----------------------------------------------------
//	__KeysData::operator==
// ----------------------------------------------------
bool			__KeysData::operator==(const __KeysData &KeyList) const
{
	return Compare(KeyList);
}

// ----------------------------------------------------
//	__KeysData::_Size
// ----------------------------------------------------
size_t			__KeysData::_Size() const
{
	// �T�C�Y��ԋp
	return _CheckKeyList.size();
}

// ----------------------------------------------------
//	__KeysData::_Get
// ----------------------------------------------------
int				__KeysData::_Get(int Val) const
{
	// �C�e���[�^
	auto Iterator = _CheckKeyList.begin();
	// �����̒l�������߂�
	for(int i = 0; i < Val; i++){
		// 1�ǉ�
		Iterator++;
		// �����I�[�܂Ō����Ȃ�
		if(Iterator == _CheckKeyList.end()){
			// -1��Ԃ�
			return -1;
		}
	}
	// �ԋp
	return *Iterator;
}

// ----------------------------------------------------
//	Key
// ----------------------------------------------------
//	Initialization
// ----------------------------------------------------
const __KeysData		Key::A			(KEY_INPUT_A);
const __KeysData		Key::B			(KEY_INPUT_B);
const __KeysData		Key::C			(KEY_INPUT_C);
const __KeysData		Key::D			(KEY_INPUT_D);
const __KeysData		Key::E			(KEY_INPUT_E);
const __KeysData		Key::F			(KEY_INPUT_F);
const __KeysData		Key::G			(KEY_INPUT_G);
const __KeysData		Key::H			(KEY_INPUT_H);
const __KeysData		Key::I			(KEY_INPUT_I);
const __KeysData		Key::J			(KEY_INPUT_J);
const __KeysData		Key::K			(KEY_INPUT_K);
const __KeysData		Key::L			(KEY_INPUT_L);
const __KeysData		Key::M			(KEY_INPUT_M);
const __KeysData		Key::N			(KEY_INPUT_N);
const __KeysData		Key::O			(KEY_INPUT_O);
const __KeysData		Key::P			(KEY_INPUT_P);
const __KeysData		Key::Q			(KEY_INPUT_Q);
const __KeysData		Key::R			(KEY_INPUT_R);
const __KeysData		Key::S			(KEY_INPUT_S);
const __KeysData		Key::T			(KEY_INPUT_T);
const __KeysData		Key::U			(KEY_INPUT_U);
const __KeysData		Key::V			(KEY_INPUT_V);
const __KeysData		Key::W			(KEY_INPUT_W);
const __KeysData		Key::X			(KEY_INPUT_X);
const __KeysData		Key::Y			(KEY_INPUT_Y);
const __KeysData		Key::Z			(KEY_INPUT_Z);
const __KeysData		Key::N1			(KEY_INPUT_1,			KEY_INPUT_NUMPAD1);
const __KeysData		Key::N2			(KEY_INPUT_2,			KEY_INPUT_NUMPAD2);
const __KeysData		Key::N3			(KEY_INPUT_3,			KEY_INPUT_NUMPAD3);
const __KeysData		Key::N4			(KEY_INPUT_4,			KEY_INPUT_NUMPAD4);
const __KeysData		Key::N5			(KEY_INPUT_5,			KEY_INPUT_NUMPAD5);
const __KeysData		Key::N6			(KEY_INPUT_6,			KEY_INPUT_NUMPAD6);
const __KeysData		Key::N7			(KEY_INPUT_7,			KEY_INPUT_NUMPAD7);
const __KeysData		Key::N8			(KEY_INPUT_8,			KEY_INPUT_NUMPAD8);
const __KeysData		Key::N9			(KEY_INPUT_9,			KEY_INPUT_NUMPAD9);
const __KeysData		Key::N0			(KEY_INPUT_0,			KEY_INPUT_NUMPAD0);
const __KeysData		Key::Enter		(KEY_INPUT_RETURN);
const __KeysData		Key::Escape		(KEY_INPUT_ESCAPE);
const __KeysData		Key::Tab		(KEY_INPUT_TAB);
const __KeysData		Key::Shift		(KEY_INPUT_LSHIFT,		KEY_INPUT_RSHIFT);
const __KeysData		Key::Control	(KEY_INPUT_LCONTROL,	KEY_INPUT_RCONTROL);
const __KeysData		Key::Alt		(KEY_INPUT_LALT,		KEY_INPUT_RALT);
const __KeysData		Key::Space		(KEY_INPUT_SPACE);
const __KeysData		Key::Up			(KEY_INPUT_UP);
const __KeysData		Key::Left		(KEY_INPUT_LEFT);
const __KeysData		Key::Right		(KEY_INPUT_RIGHT);
const __KeysData		Key::Down		(KEY_INPUT_DOWN);

