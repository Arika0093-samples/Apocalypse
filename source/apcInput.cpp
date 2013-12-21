// --------------------------------------------------------
//	apcInput.cpp
// --------------------------------------------------------
//	apcInput.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	Key
// ----------------------------------------------------
//	Key::Key (Constructor)
// ----------------------------------------------------
				KeyBoard::KeyBoard()
{
	// キーの状態値をリセットする
	memset(_KeyInput, 0, sizeof(_KeyInput));
	return;
}

// ----------------------------------------------------
//	Key::AnyKeyPushing
// ----------------------------------------------------
bool			KeyBoard::AnyPushing()
{
	// 入力状態を返却する
	return (CheckHitKeyAll() != 0);
}

// ----------------------------------------------------
//	Key::KeyPushing
// ----------------------------------------------------
int				KeyBoard::Pushing(Keys TargetKey)
{
	// 結果返却用
	int Result = 0;
	// キーの状態を取得する
	for(int i = 0; i < TargetKey._Size(); i++){
		// もし初期状態or前の値より小さいなら
		if(Result == 0 || Result > TargetKey._Get(i)){
			// 取得
			Result = TargetKey._Get(i);
		}
		// もし値がマイナスなら
		if(Result < 0){
			// 押されていない
			return 0;
		}
	}
	// 返却
	return max(Result, 0);
}

// ----------------------------------------------------
//	Key::KeyPushStarted
// ----------------------------------------------------
bool			KeyBoard::PushStart(Keys TargetKey)
{
	// 結果返却用
	bool Result = false, NowTime = false;
	// キーの状態を取得する
	for(int i = 0; i < TargetKey._Size(); i++){
		// 全てのキーが押されてるか確認
		Result	= (TargetKey._Get(i) > 0);
		// 1つ以上のキーが現在押されたばかりかどうか取得
		NowTime = (NowTime ? true : (TargetKey._Get(i) == 1));
		// もし値がfalseなら
		if(!Result){
			// 押されていない
			return false;
		}
	}
	// 返却
	return (Result && NowTime);
}

// ----------------------------------------------------
//	Key::KeyPushStarted
// ----------------------------------------------------
bool			KeyBoard::OutStart(Keys TargetKey)
{
	// 結果返却用
	bool Result = false, NowTime = false;
	// キーの状態を取得する
	for(int i = 0; i < TargetKey._Size(); i++){
		// 全てのキーが離されているか確認
		Result	= (TargetKey._Get(i) < 0);
		// 1つ以上のキーが現在離されたばかりかどうか取得
		NowTime = (NowTime ? true : (TargetKey._Get(i) == -1));
		// もし値がfalseなら
		if(!Result){
			// 押されている
			return false;
		}
	}
	// 返却
	return (Result && NowTime);
}

// ----------------------------------------------------
//	Key::_CheckKeyEvent
// ----------------------------------------------------
void			KeyBoard::_CheckKeyEvent()
{
	// キーの状態を取得するための変数
	char KeyEvent[256];
	// ------------------------------------------------
	// 取得する
	GetHitKeyStateAll(KeyEvent);
	// 要素数だけループする
	for(int Loop = 0; Loop < 256; Loop++)
	{
		// もし押されていて
		if(KeyEvent[Loop] == 1){
			// 初めて押されてたなら
			if(_KeyInput[Loop] < 0){
				// 0にリセット
				_KeyInput[Loop] = 0;
			}
			// インクリメントする
			_KeyInput[Loop]++;
		}
		// もし押されていなくて
		else{
			// もしキーの値が0なら（初期状態なら）
			if(_KeyInput[Loop] == 0){
				// 無視して続行する
				continue;
			}
			// 初めて離されたなら
			if(_KeyInput[Loop] > 0){
				// 0にリセット
				_KeyInput[Loop] = 0;
			}
			// デクリメントする
			_KeyInput[Loop]--;
		}
	}
	// 終了
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
	// マウスの状態を取得して正の値ならそのまま返却する
	return (GetInstance()._MousePushTimeLeft > 0 ?
			GetInstance()._MousePushTimeLeft : 0);
}

// ----------------------------------------------------
//	Mouse::MousePushStarted
// ----------------------------------------------------
bool			Mouse::LeftPushStart()
{
	// マウス状態を取得して押された瞬間ならtrueを返す
	return (GetInstance()._MousePushTimeLeft == 1);
}

// ----------------------------------------------------
//	Mouse::MouseOutStart
// ----------------------------------------------------
bool			Mouse::LeftOutStart()
{
	// マウス状態を取得して離された瞬間ならtrueを返す
	return (GetInstance()._MousePushTimeLeft == -1);
}

// ----------------------------------------------------
//	Mouse::MousePushing
// ----------------------------------------------------
int				Mouse::RightPushing()
{
	// マウスの状態を取得して正の値ならそのまま返却する
	return (GetInstance()._MousePushTimeRight > 0 ?
			GetInstance()._MousePushTimeRight : 0);
}

// ----------------------------------------------------
//	Mouse::MousePushStarted
// ----------------------------------------------------
bool			Mouse::RightPushStart()
{
	// マウス状態を取得して押された瞬間ならtrueを返す
	return (GetInstance()._MousePushTimeRight == 1);
}

// ----------------------------------------------------
//	Mouse::MouseOutStart
// ----------------------------------------------------
bool			Mouse::RightOutStart()
{
	// マウス状態を取得して離された瞬間ならtrueを返す
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
	// 取得しておいたマウス位置を返却する
	return GetInstance()._MouseLocation;
}

// ----------------------------------------------------
//	Mouse::SetMousePosition
// ----------------------------------------------------
void			Mouse::SetPosition(int X, int Y)
{
	// マウス位置を指定の位置に移動させる
	SetMousePoint( X, Y);
	// あらかじめ取得した位置も変更する
	GetInstance()._MouseLocation.X = X;
	GetInstance()._MouseLocation.Y = Y;
	// 終了
	return;
}

// ----------------------------------------------------
//	Mouse::CheckMouseEvent
// ----------------------------------------------------
void			Mouse::_CheckMouseEvent()
{
	// マウスのX, Y座標を取得するための変数
	int MouseX, MouseY;
	// ------------------------------------------------
	// もしマウスが押されていて
	if(GetMouseInput() & MOUSE_INPUT_LEFT){
		// 初めて押されてたなら
		if(_MousePushTimeLeft < 0){
			// 0にリセット
			_MousePushTimeLeft = 0;
		}
		// インクリメントする
		_MousePushTimeLeft++;
	}
	// もしマウスが押されていなくて
	else{
		// 初めて離されたなら
		if(_MousePushTimeLeft > 0){
			// 0にリセット
			_MousePushTimeLeft = 0;
		}
		// デクリメントする
		_MousePushTimeLeft--;
	}
	// もしマウスが押されていて
	if(GetMouseInput() & MOUSE_INPUT_RIGHT){
		// 初めて押されてたなら
		if(_MousePushTimeRight < 0){
			// 0にリセット
			_MousePushTimeRight = 0;
		}
		// インクリメントする
		_MousePushTimeRight++;
	}
	// もしマウスが押されていなくて
	else{
		// 初めて離されたなら
		if(_MousePushTimeRight > 0){
			// 0にリセット
			_MousePushTimeRight = 0;
		}
		// デクリメントする
		_MousePushTimeRight--;
	}
	// 現在位置を取得
	GetMousePoint( &MouseX, &MouseY );
	// 現在の座標を保存
	_MouseBeforeLoc = _MouseLocation;
	// 取得した結果を代入する
	_MouseLocation( MouseX, MouseY);
	// 終了
	return;
}

// ----------------------------------------------------
//	Keys
// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys()
{
	// 初期化
	_CheckKeyList.clear();
}

// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys(int FstKey)
{
	// 初期化
	_CheckKeyList.clear();
	// 追加
	_CheckKeyList.insert(FstKey);
}

// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys(int FstKey_1, int FstKey_2)
{
	// 初期化
	_CheckKeyList.clear();
	// 追加
	_CheckKeyList.insert(FstKey_1);
	_CheckKeyList.insert(FstKey_2);
}

// ----------------------------------------------------
//	Keys::Keys (Constructor)
// ----------------------------------------------------
				Keys::Keys(int FstKeys[], size_t Size)
{
	// 初期化
	_CheckKeyList.clear();
	// ループを回す
	for(int i = 0; i < Size; i++){
		// 追加
		_CheckKeyList.insert(FstKeys[i]);
	}
}

// ----------------------------------------------------
//	Keys::Compare
// ----------------------------------------------------
bool			Keys::Compare(const Keys &KeyList) const
{
	// もしサイズが違うなら
	if(_Size() != KeyList._Size()){
		// false
		return false;
	}
	// ループを回す
	for(int i = 0; i < _Size(); i++){
		// もし一致しない要素が存在するなら
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
	// 自身をコピー
	Keys* NewKeys = new Keys(*this);
	// 引数を追加
	*NewKeys += KeyList;
	// 返却
	return *NewKeys;
}

// ----------------------------------------------------
//	Keys::operator-
// ----------------------------------------------------
Keys&			Keys::operator-(const Keys &KeyList) const
{
	// 自身をコピー
	Keys* NewKeys = new Keys(*this);
	// 引数を引く
	*NewKeys -= KeyList;
	// 返却
	return *NewKeys;
}

// ----------------------------------------------------
//	Keys::operator+=
// ----------------------------------------------------
Keys&			Keys::operator+=(const Keys &KeyList)
{
	// 追加していく
	for(int i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.insert(KeyList._Get(i));
	}
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	Keys::operator-=
// ----------------------------------------------------
Keys&			Keys::operator-=(const Keys &KeyList)
{
	// 削除していく
	for(int i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.erase(KeyList._Get(i));
	}
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	Keys::operator&&
// ----------------------------------------------------
bool			Keys::operator&&(int Key) const
{
	// 値が含まれているならtrue
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
	// サイズを返却
	return _CheckKeyList.size();
}

// ----------------------------------------------------
//	Keys::_Get
// ----------------------------------------------------
int				Keys::_Get(int Val) const
{
	// イテレータ
	auto Iterator = _CheckKeyList.begin();
	// 引数の値分すすめる
	for(int i = 0; i < Val; i++){
		// 1追加
		Iterator++;
		// もし終端まで見たなら
		if(Iterator == _CheckKeyList.end()){
			// -1を返す
			return -1;
		}
	}
	// 返却
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

