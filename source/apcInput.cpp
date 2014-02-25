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
UINT			KeyBoard::Pushing(const __KeysData &TargetKey)
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
bool			KeyBoard::PushStart(const __KeysData &TargetKey)
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
bool			KeyBoard::OutStart(const __KeysData &TargetKey)
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
	// 左の押されてる時間 / 右の押されてる時間
	return String() << _T("Left: ") << LeftPushing()
		<< _T(", Right: ") << RightPushing();
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
//	__KeysData
// ----------------------------------------------------
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData()
{
	// 初期化
	_CheckKeyList.clear();
	// 判定モードを指定
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData(int FstKey)
{
	// 初期化
	_CheckKeyList.clear();
	// 追加
	_CheckKeyList.insert(FstKey);
	// 判定モードを指定
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData(int FstKey_1, int FstKey_2)
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
//	__KeysData::__KeysData (Constructor)
// ----------------------------------------------------
				__KeysData::__KeysData(int Fst__KeysData[], size_t Size)
{
	// 初期化
	_CheckKeyList.clear();
	// ループを回す
	for(size_t i = 0; i < Size; i++){
		// 追加
		_CheckKeyList.insert(Fst__KeysData[i]);
	}
	// 判定モードを指定
	IsCheckAllKey = false;
}

// ----------------------------------------------------
//	__KeysData::Compare
// ----------------------------------------------------
bool			__KeysData::Compare(const __KeysData &KeyList) const
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
//	__KeysData::operator+
// ----------------------------------------------------
__KeysData&		__KeysData::operator+(const __KeysData &KeyList) const
{
	// 自身をコピー
	__KeysData* New__KeysData = new __KeysData(*this);
	// 引数を追加
	*New__KeysData += KeyList;
	// 返却
	return *New__KeysData;
}

// ----------------------------------------------------
//	__KeysData::operator-
// ----------------------------------------------------
__KeysData&		__KeysData::operator-(const __KeysData &KeyList) const
{
	// 自身をコピー
	__KeysData* New__KeysData = new __KeysData(*this);
	// 引数を引く
	*New__KeysData -= KeyList;
	// 返却
	return *New__KeysData;
}

// ----------------------------------------------------
//	__KeysData::operator+=
// ----------------------------------------------------
__KeysData&		__KeysData::operator+=(const __KeysData &KeyList)
{
	// 追加していく
	for(size_t i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.insert(KeyList._Get(i));
	}
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	__KeysData::operator-=
// ----------------------------------------------------
__KeysData&		__KeysData::operator-=(const __KeysData &KeyList)
{
	// 削除していく
	for(size_t i = 0; i < KeyList._Size(); i++){
		_CheckKeyList.erase(KeyList._Get(i));
	}
	// 自身を返却
	return *this;
}

// ----------------------------------------------------
//	__KeysData::operator&&
// ----------------------------------------------------
bool			__KeysData::operator&&(int Key) const
{
	// 値が含まれているならtrue
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
	// サイズを返却
	return _CheckKeyList.size();
}

// ----------------------------------------------------
//	__KeysData::_Get
// ----------------------------------------------------
int				__KeysData::_Get(int Val) const
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

