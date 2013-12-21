// --------------------------------------------------------
//	apcInput.cpp
// --------------------------------------------------------
//	apcInput.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.h"

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
int				KeyBoard::Pushing(Keys TargetKey)
{
	// ���ʕԋp�p
	int Result = 0;
	// �L�[�̏�Ԃ��擾����
	for(int i = 0; i < TargetKey._Size(); i++){
		// �����������or�O�̒l��菬�����Ȃ�
		if(Result == 0 || Result > TargetKey._Get(i)){
			// �擾
			Result = TargetKey._Get(i);
		}
		// �����l���}�C�i�X�Ȃ�
		if(Result < 0){
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
bool			KeyBoard::PushStart(Keys TargetKey)
{
	// ���ʕԋp�p
	bool Result = false, NowTime = false;
	// �L�[�̏�Ԃ��擾����
	for(int i = 0; i < TargetKey._Size(); i++){
		// �S�ẴL�[��������Ă邩�m�F
		Result	= (TargetKey._Get(i) > 0);
		// 1�ȏ�̃L�[�����݉����ꂽ�΂��肩�ǂ����擾
		NowTime = (NowTime ? true : (TargetKey._Get(i) == 1));
		// �����l��false�Ȃ�
		if(!Result){
			// ������Ă��Ȃ�
			return false;
		}
	}
	// �ԋp
	return (Result && NowTime);
}

// ----------------------------------------------------
//	Key::KeyPushStarted
// ----------------------------------------------------
bool			KeyBoard::OutStart(Keys TargetKey)
{
	// ���ʕԋp�p
	bool Result = false, NowTime = false;
	// �L�[�̏�Ԃ��擾����
	for(int i = 0; i < TargetKey._Size(); i++){
		// �S�ẴL�[��������Ă��邩�m�F
		Result	= (TargetKey._Get(i) < 0);
		// 1�ȏ�̃L�[�����ݗ����ꂽ�΂��肩�ǂ����擾
		NowTime = (NowTime ? true : (TargetKey._Get(i) == -1));
		// �����l��false�Ȃ�
		if(!Result){
			// ������Ă���
			return false;
		}
	}
	// �ԋp
	return (Result && NowTime);
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
Base::Point		Mouse::GetPosition()
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
//	Keys
// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys()
{
	// ������
	_CheckKeyList.clear();
}

// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys(int FstKey)
{
	// ������
	_CheckKeyList.clear();
	// �ǉ�
	_CheckKeyList.insert(FstKey);
}

// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys(int FstKey_1, int FstKey_2)
{
	// ������
	_CheckKeyList.clear();
	// �ǉ�
	_CheckKeyList.insert(FstKey_1);
	_CheckKeyList.insert(FstKey_2);
}

// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys(int FstKeys[], size_t Size)
{
	// ������
	_CheckKeyList.clear();
	// ���[�v����
	for(int i = 0; i < Size; i++){
		// �ǉ�
		_CheckKeyList.insert(FstKeys[i]);
	}
}

// ----------------------------------------------------
//	Keys::Compare
// ----------------------------------------------------
bool			Keys::Compare(const Keys &KeyList) const
{
	// �����T�C�Y���Ⴄ�Ȃ�
	if(_Size() != KeyList._Size()){
		// false
		return false;
	}
	// ���[�v����
	for(int i = 0; i < _Size(); i++){
		// ������v���Ȃ��v�f�����݂���Ȃ�
		if(KeyList && _Get(i) == false){
			// false
			return false;
		}
	}
	return true;
}

// ----------------------------------------------------
//	Keys::operator+
// ----------------------------------------------------
Keys&			Keys::operator+(const Keys &KeyList) const
{
	// ���g���R�s�[
	Keys* NewKeys = new Keys(*this);
	// ������ǉ�
	*NewKeys += KeyList;
	// �ԋp
	return *NewKeys;
}

// ----------------------------------------------------
//	Keys::operator-
// ----------------------------------------------------
Keys&			Keys::operator-(const Keys &KeyList) const
{
	// ���g���R�s�[
	Keys* NewKeys = new Keys(*this);
	// ����������
	*NewKeys -= KeyList;
	// �ԋp
	return *NewKeys;
}

// ----------------------------------------------------
//	Keys::operator+=
// ----------------------------------------------------
Keys&			Keys::operator+=(const Keys &KeyList)
{
	// �ǉ����Ă���
	for(int i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.insert(KeyList._Get(i));
	}
	// ���g��ԋp
	return *this;
}

// ----------------------------------------------------
//	Keys::operator-=
// ----------------------------------------------------
Keys&			Keys::operator-=(const Keys &KeyList)
{
	// �폜���Ă���
	for(int i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.erase(KeyList._Get(i));
	}
	// ���g��ԋp
	return *this;
}

// ----------------------------------------------------
//	Keys::operator&&
// ----------------------------------------------------
bool			Keys::operator&&(int Key) const
{
	// �l���܂܂�Ă���Ȃ�true
	return (_CheckKeyList.count(Key) >= 1);
}

// ----------------------------------------------------
//	Keys::operator==
// ----------------------------------------------------
bool			Keys::operator==(const Keys &KeyList) const
{
	return Compare(KeyList);
}

// ----------------------------------------------------
//	Keys::_Size
// ----------------------------------------------------
unsigned int	Keys::_Size() const
{
	// �T�C�Y��ԋp
	return _CheckKeyList.size();
}

// ----------------------------------------------------
//	Keys::_Get
// ----------------------------------------------------
int				Keys::_Get(int Val) const
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
const Keys		Key::A			(KEY_INPUT_A);
const Keys		Key::B			(KEY_INPUT_B);
const Keys		Key::C			(KEY_INPUT_C);
const Keys		Key::D			(KEY_INPUT_D);
const Keys		Key::E			(KEY_INPUT_E);
const Keys		Key::F			(KEY_INPUT_F);
const Keys		Key::G			(KEY_INPUT_G);
const Keys		Key::H			(KEY_INPUT_H);
const Keys		Key::I			(KEY_INPUT_I);
const Keys		Key::J			(KEY_INPUT_J);
const Keys		Key::K			(KEY_INPUT_K);
const Keys		Key::L			(KEY_INPUT_L);
const Keys		Key::M			(KEY_INPUT_M);
const Keys		Key::N			(KEY_INPUT_N);
const Keys		Key::O			(KEY_INPUT_O);
const Keys		Key::P			(KEY_INPUT_P);
const Keys		Key::Q			(KEY_INPUT_Q);
const Keys		Key::R			(KEY_INPUT_R);
const Keys		Key::S			(KEY_INPUT_S);
const Keys		Key::T			(KEY_INPUT_T);
const Keys		Key::U			(KEY_INPUT_U);
const Keys		Key::V			(KEY_INPUT_V);
const Keys		Key::W			(KEY_INPUT_W);
const Keys		Key::X			(KEY_INPUT_X);
const Keys		Key::Y			(KEY_INPUT_Y);
const Keys		Key::Z			(KEY_INPUT_Z);
const Keys		Key::Enter		(KEY_INPUT_RETURN);
const Keys		Key::Escape		(KEY_INPUT_ESCAPE);
const Keys		Key::Tab		(KEY_INPUT_TAB);
const Keys		Key::Shift		(KEY_INPUT_LSHIFT,		KEY_INPUT_RSHIFT);
const Keys		Key::Control	(KEY_INPUT_LCONTROL,	KEY_INPUT_RCONTROL);
const Keys		Key::Alt		(KEY_INPUT_LALT,		KEY_INPUT_RALT);
const Keys		Key::Space		(KEY_INPUT_SPACE);
const Keys		Key::Up			(KEY_INPUT_UP);
const Keys		Key::Left		(KEY_INPUT_LEFT);
const Keys		Key::Right		(KEY_INPUT_RIGHT);
const Keys		Key::Down		(KEY_INPUT_DOWN);

