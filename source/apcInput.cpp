// --------------------------------------------------------
//	apcInput.cpp
// --------------------------------------------------------
//	apcInput.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.hpp"

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
UINT			KeyBoard::Pushing(const _KeysData &TargetKey)
{
	// 結果返却用
	int Result = 0;
	// キーの状態を取得する
	for(size_t i = 0; i < TargetKey._Size(); i++){
		// もし初期状態or前の値より小さいなら
		if(Result == 0 || Result > GetInstance()._KeyInput[TargetKey._Get(i)]){
			// 取得
			Result = GetInstance()._KeyInput[TargetKey._Get(i)];
		}
		// もし値がマイナスで全押し判定なら
		if((Result < 0) && TargetKey.IsCheckAllKey){
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
bool			KeyBoard::PushStart(const _KeysData &TargetKey)
{
	// 結果返却用
	bool Result = false, NowTime = false;
	// キーの状態を取得する
	for(size_t i = 0; i < TargetKey._Size(); i++){
		// 対象のキーが押されてるか確認
		Result	= (GetInstance()._KeyInput[TargetKey._Get(i)] > 0);
		// 1つ以上のキーが現在押されたばかりかどうか取得
		NowTime = (NowTime ? true : (GetInstance()._KeyInput[TargetKey._Get(i)] == 1));
		// もし値がfalseで全押し判定なら
		if(!Result && TargetKey.IsCheckAllKey){
			// 押されていない
			return false;
		}
	}
	// 全押し判定なら対象キーが全て押されているかどうか + 現在どれか一つ以上が押されたか
	// そうでないなら現在どれか一つ以上が押されたかの情報を返却する
	return (( Result || !TargetKey.IsCheckAllKey) && NowTime);
}

// ----------------------------------------------------
//	Key::KeyPushStarted
// ----------------------------------------------------
bool			KeyBoard::OutStart(const _KeysData &TargetKey)
{
	// 結果返却用
	bool Result = false, NowTime = false;
	// キーの状態を取得する
	for(size_t i = 0; i < TargetKey._Size(); i++){
		// 対象のキーが離されているか確認
		Result	= (GetInstance()._KeyInput[TargetKey._Get(i)] < 0);
		// 1つ以上のキーが現在離されたばかりかどうか取得
		NowTime = (NowTime ? true : (GetInstance()._KeyInput[TargetKey._Get(i)] == -1));
		// もし値がfalseで全押し判定なら
		if(!Result && TargetKey.IsCheckAllKey){
			// 押されている
			return false;
		}
	}
	// 全押し判定なら対象キーが全て離されているかどうか + 現在どれか一つ以上が離されたか
	// そうでないなら現在どれか一つ以上が離されたかの情報を返却する
	return (( Result || !TargetKey.IsCheckAllKey) && NowTime);
}

// ----------------------------------------------------
//	Key::ToString
// ----------------------------------------------------
String			KeyBoard::ToString() const
{
	// 返却する文字列
	String Result;
	// forループで全キーボードの状態を文字に格納
	for(int i = 0; i < sizeof(_KeyInput) / sizeof(int); i++){
		// 流す
		Result << _KeyInput[i] << _T(",");
	}
	return Result;
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
Value::Point	Mouse::GetPosition()
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
//	Mouse::ToString
// ----------------------------------------------------
String			Mouse::ToString() const
{
	// 左の押されてる時間 / 右の押されてる時間 / 現在の座標
	return String()
		<< _T("Left: ") << LeftPushing()
		<< _T(", Right: ") << RightPushing()
		<< _T(", Point: ") << _MouseLocation;
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
//	_KeysData
// ----------------------------------------------------
//	_KeysData::_KeysData (Constructor)
// ----------------------------------------------------
				_KeysData::_KeysData()
{
	// 初期化
	_CheckKeyList.clear();
	// 判定モードを指定
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	_KeysData::_KeysData (Constructor)
// ----------------------------------------------------
				_KeysData::_KeysData(int FstKey)
{
	// 初期化
	_CheckKeyList.clear();
	// 追加
	_CheckKeyList.insert(FstKey);
	// 判定モードを指定
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	_KeysData::_KeysData (Constructor)
// ----------------------------------------------------
				_KeysData::_KeysData(int FstKey_1, int FstKey_2)
{
	// 初期化
	_CheckKeyList.clear();
	// 追加
	_CheckKeyList.insert(FstKey_1);
	_CheckKeyList.insert(FstKey_2);
	// 判定モードを指定
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	_KeysData::_KeysData (Constructor)
// ----------------------------------------------------
				_KeysData::_KeysData(int Fst_KeysData[], size_t Size)
{
	// 初期化
	_CheckKeyList.clear();
	// ループを回す
	for(size_t i = 0; i < Size; i++){
		// 追加
		_CheckKeyList.insert(Fst_KeysData[i]);
	}
	// 判定モードを指定
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	_KeysData::Compare
// ----------------------------------------------------
bool			_KeysData::Compare(const _KeysData &KeyList) const
{
	// もしサイズが違うなら
	if(_Size() != KeyList._Size()){
		// false
		return false;
	}
	// ループを回す
	for(size_t i = 0; i < _Size(); i++){
		// もし一致しない要素が存在するなら
		if(KeyList && _Get(i) == false){
			// false
			return false;
		}
	}
	return true;
}

// ----------------------------------------------------
//	_KeysData::operator+
// ----------------------------------------------------
_KeysData&		_KeysData::operator+(const _KeysData &KeyList) const
{
	// 自身をコピー
	_KeysData* New_KeysData = new _KeysData(*this);
	// 引数を追加
	*New_KeysData += KeyList;
	// 返却
	return *New_KeysData;
}

// ----------------------------------------------------
//	_KeysData::operator-
// ----------------------------------------------------
_KeysData&		_KeysData::operator-(const _KeysData &KeyList) const
{
	// 自身をコピー
	_KeysData* New_KeysData = new _KeysData(*this);
	// 引数を引く
	*New_KeysData -= KeyList;
	// 返却
	return *New_KeysData;
}

// ----------------------------------------------------
//	_KeysData::operator+=
// ----------------------------------------------------
_KeysData&		_KeysData::operator+=(const _KeysData &KeyList)
{
	// 追加していく
	for(size_t i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.insert(KeyList._Get(i));
	}
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	_KeysData::operator-=
// ----------------------------------------------------
_KeysData&		_KeysData::operator-=(const _KeysData &KeyList)
{
	// 削除していく
	for(size_t i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.erase(KeyList._Get(i));
	}
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	_KeysData::operator&&
// ----------------------------------------------------
bool			_KeysData::operator&&(int Key) const
{
	// 値が含まれているならtrue
	return (_CheckKeyList.count(Key) >= 1);
}

// ----------------------------------------------------
//	_KeysData::operator==
// ----------------------------------------------------
bool			_KeysData::operator==(const _KeysData &KeyList) const
{
	return Compare(KeyList);
}

// ----------------------------------------------------
//	_KeysData::_Size
// ----------------------------------------------------
size_t			_KeysData::_Size() const
{
	// サイズを返却
	return _CheckKeyList.size();
}

// ----------------------------------------------------
//	_KeysData::_Get
// ----------------------------------------------------
int				_KeysData::_Get(int Val) const
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
const _KeysData		Key::A			(KEY_INPUT_A);
const _KeysData		Key::B			(KEY_INPUT_B);
const _KeysData		Key::C			(KEY_INPUT_C);
const _KeysData		Key::D			(KEY_INPUT_D);
const _KeysData		Key::E			(KEY_INPUT_E);
const _KeysData		Key::F			(KEY_INPUT_F);
const _KeysData		Key::G			(KEY_INPUT_G);
const _KeysData		Key::H			(KEY_INPUT_H);
const _KeysData		Key::I			(KEY_INPUT_I);
const _KeysData		Key::J			(KEY_INPUT_J);
const _KeysData		Key::K			(KEY_INPUT_K);
const _KeysData		Key::L			(KEY_INPUT_L);
const _KeysData		Key::M			(KEY_INPUT_M);
const _KeysData		Key::N			(KEY_INPUT_N);
const _KeysData		Key::O			(KEY_INPUT_O);
const _KeysData		Key::P			(KEY_INPUT_P);
const _KeysData		Key::Q			(KEY_INPUT_Q);
const _KeysData		Key::R			(KEY_INPUT_R);
const _KeysData		Key::S			(KEY_INPUT_S);
const _KeysData		Key::T			(KEY_INPUT_T);
const _KeysData		Key::U			(KEY_INPUT_U);
const _KeysData		Key::V			(KEY_INPUT_V);
const _KeysData		Key::W			(KEY_INPUT_W);
const _KeysData		Key::X			(KEY_INPUT_X);
const _KeysData		Key::Y			(KEY_INPUT_Y);
const _KeysData		Key::Z			(KEY_INPUT_Z);
const _KeysData		Key::N1			(KEY_INPUT_1,			KEY_INPUT_NUMPAD1);
const _KeysData		Key::N2			(KEY_INPUT_2,			KEY_INPUT_NUMPAD2);
const _KeysData		Key::N3			(KEY_INPUT_3,			KEY_INPUT_NUMPAD3);
const _KeysData		Key::N4			(KEY_INPUT_4,			KEY_INPUT_NUMPAD4);
const _KeysData		Key::N5			(KEY_INPUT_5,			KEY_INPUT_NUMPAD5);
const _KeysData		Key::N6			(KEY_INPUT_6,			KEY_INPUT_NUMPAD6);
const _KeysData		Key::N7			(KEY_INPUT_7,			KEY_INPUT_NUMPAD7);
const _KeysData		Key::N8			(KEY_INPUT_8,			KEY_INPUT_NUMPAD8);
const _KeysData		Key::N9			(KEY_INPUT_9,			KEY_INPUT_NUMPAD9);
const _KeysData		Key::N0			(KEY_INPUT_0,			KEY_INPUT_NUMPAD0);
const _KeysData		Key::Enter		(KEY_INPUT_RETURN);
const _KeysData		Key::Escape		(KEY_INPUT_ESCAPE);
const _KeysData		Key::Tab		(KEY_INPUT_TAB);
const _KeysData		Key::Shift		(KEY_INPUT_LSHIFT,		KEY_INPUT_RSHIFT);
const _KeysData		Key::Control	(KEY_INPUT_LCONTROL,	KEY_INPUT_RCONTROL);
const _KeysData		Key::Alt		(KEY_INPUT_LALT,		KEY_INPUT_RALT);
const _KeysData		Key::Space		(KEY_INPUT_SPACE);
const _KeysData		Key::Up			(KEY_INPUT_UP);
const _KeysData		Key::Left		(KEY_INPUT_LEFT);
const _KeysData		Key::Right		(KEY_INPUT_RIGHT);
const _KeysData		Key::Down		(KEY_INPUT_DOWN);

