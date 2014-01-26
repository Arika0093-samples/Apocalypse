// --------------------------------------------------------
//	apcInput.h
// --------------------------------------------------------
//	入力を管理するクラスを作成する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <set>
#include <include/apcClassBase.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Input)
// --------------------------------------------------------
namespace Apocalypse
{
	// ----------------------------------------------------
	//	Input名前空間内のクラスを記載
	// ----------------------------------------------------
	namespace Input
	{
		// ------------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class Keys;

		///	<summary>
		///		キー情報を管理する用のクラス．
		///	</summary>
		/// <remarks>
		///		Key::XXの形でキー情報を取得できます．このクラスはsingletonです．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// もしZキーが押されていれば
		///		if(Key::Pushing(KeyList::Z)){
		///			…
		///		}
		///		// もしXキーが離された瞬間ならば
		///		if(Key::OutStart(KeyList::X)){
		///			…
		///		}
		///		</code>
		/// </example>
		class KeyBoard : public Template::__Singleton<KeyBoard>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<KeyBoard>;
		public:
			/// <summary>
			///		何かのキー/マウスが押されているかどうかの情報を取得する．
			/// </summary>
			static bool			AnyPushing();
			/// <summary>
			///		<para>指定したキーが押されているかどうかの情報を取得する．</para>
			///		<para>0なら押されていない．1以上なら押されている時間．</para>
			/// </summary>
			/// <param name = "TargetKey">
			///		取得する対象のキー．KeyListで定義された値を使用して下さい．
			/// </param>
			static int			Pushing(Keys TargetKey);
			/// <summary>
			///		指定したキーがこのフレームで初めて押されたかどうかの情報を取得する．
			/// </summary>
			/// <param name = "TargetKey">
			///		取得する対象のキー．KeyListで定義された値を使用して下さい．
			/// </param>
			static bool			PushStart(Keys TargetKey);
			/// <summary>
			///		指定したキーがこのフレームで初めて離されたかどうかの情報を取得する．
			/// </summary>
			/// <param name = "TargetKey">
			///		取得する対象のキー．KeyListで定義された値を使用して下さい．
			/// </param>
			static bool			OutStart(Keys TargetKey);
			/// <summary>
			///		キーの押されている状態を文字列で返却する．
			/// </summary>
			virtual Value::String
								ToString() const;
			/// <summary>
			///		キーの状態を更新する．1フレームに1度呼び出す．
			/// </summary>
			void				_CheckKeyEvent();
		private:
			/// <summary>
			///		Constructor
			/// </summary>
								KeyBoard();
			/// <summary>
			///		キーの入力情報を保存する変数．
			/// </summary>
			int					_KeyInput[256];
		};

		///	<summary>
		///		マウス情報を管理する用のクラス．
		///	</summary>
		/// <remarks>
		///		Mouse::XXの形でキー情報を取得できます．このクラスはsingletonです．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// もしマウスが押されていれば
		///		if(Mouse::Pushing()){
		///			…
		///		}
		///		// もしマウスが離された瞬間ならば
		///		if(Mouse::OutStart()){
		///			…
		///		}
		///		</code>
		/// </example>
		class Mouse : public Template::__Singleton<Mouse>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<Mouse>;
		public:
			/// <summary>
			///		<para>マウスが押されているかどうかの情報を取得する．</para>
			///		<para>0なら押されていない．1以上なら押されている時間．</para>
			/// </summary>
			static int			LeftPushing();
			/// <summary>
			///		マウスがこのフレームで初めて押されたかどうかの情報を取得する．
			/// </summary>
			static bool			LeftPushStart();
			/// <summary>
			///		マウスがこのフレームで始めて離されたかどうかの情報を取得する．
			/// </summary>
			static bool			LeftOutStart();
			/// <summary>
			///		<para>マウスが押されているかどうかの情報を取得する．</para>
			///		<para>0なら押されていない．1以上なら押されている時間．</para>
			/// </summary>
			static int			RightPushing();
			/// <summary>
			///		マウスがこのフレームで初めて押されたかどうかの情報を取得する．
			/// </summary>
			static bool			RightPushStart();
			/// <summary>
			///		マウスがこのフレームで始めて離されたかどうかの情報を取得する．
			/// </summary>
			static bool			RightOutStart();
			/// <summary>
			///		マウスの位置を取得する．
			/// </summary>
			static bool			IsMove();
			/// <summary>
			///		マウスの位置を取得する．
			/// </summary>
			static Value::Point	GetPosition();
			/// <summary>
			///		マウスの位置を設定する．
			/// </summary>
			/// <param name = "X">
			///		指定するX座標．
			/// </param>
			/// <param name = "Y">
			///		指定するY座標．
			/// </param>
			static void			SetPosition(int X, int Y);
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String
								ToString() const;
			/// <summary>
			///		マウスの状態を更新する．1フレームに1度呼び出す．
			/// </summary>
			void				_CheckMouseEvent();
		private:
			/// <summary>
			///		コンストラクタ
			/// </summary>
								Mouse();
			/// <summary>
			///		<para>(左)マウス入力の時間を取得します．</para>
			///		<para>正の値: 押されている時間 / 負の値: 離されている時間</para>
			/// </summary>
			int					_MousePushTimeLeft;
			/// <summary>
			///		<para>(右)マウス入力の時間を取得します．</para>
			///		<para>正の値: 押されている時間 / 負の値: 離されている時間</para>
			/// </summary>
			int					_MousePushTimeRight;
			/// <summary>
			///		マウスの位置を取得する
			/// </summary>
			Value::Point		_MouseLocation;
			/// <summary>
			///		1フレーム前のマウスの位置を取得する
			/// </summary>
			Value::Point		_MouseBeforeLoc;
		};

		///	<summary>
		///		キー情報を管理するクラス．
		///	</summary>
		/// <remarks>
		///		キーの状態を取得する関数の引数に使用します．
		/// </remarks>
		class Keys : public virtual Base::__ApcBase
		{
		public:
			///	<summary>
			///		初期キーとして特に何も持たないKeysクラスのコンストラクタ．
			///	</summary>
								Keys();
			///	<summary>
			///		初期キーとして引数に指定されたキーを持つKeysクラスのコンストラクタ．
			///	</summary>
			///	<param name = "FstKey">
			///		初期キー．
			///	</param>
								Keys(int FstKey);
			///	<summary>
			///		初期キーとして引数に指定された2つのキーを持つKeysクラスのコンストラクタ．
			///	</summary>
			///	<param name = "FstKey_1">
			///		初期キーその1．
			///	</param>
			///	<param name = "FstKey_2">
			///		初期キーその2．
			///	</param>
								Keys(int FstKey_1, int FstKey_2);
			///	<summary>
			///		初期キーとして引数に指定された複数のキーを持つKeysクラスのコンストラクタ．
			///	</summary>
			///	<param name = "FstKeys">
			///		複数の初期キー．
			///	</param>
			///	<param name = "Size">
			///		登録するキーの個数．
			///	</param>
								Keys(int FstKey[], size_t Size);
			///	<summary>
			///		デストラクタ．
			///	</summary>
								~Keys(){}
			///	<summary>
			///		2つのキーの状態を比較する関数．
			///	</summary>
			///	<param name = "KeysList">
			///		比較するキーの状態クラス．
			///	</param>
			bool				Compare(const Keys &KeysList) const;
			///	<summary>
			///		キー追加のoperator．
			///	</summary>
			///	<param name = "KeysList">
			///		追加するキーの状態クラス．
			///	</param>
			Keys&				operator+(const Keys &KeysList) const;
			///	<summary>
			///		キー削除のoperator．
			///	</summary>
			///	<param name = "KeysList">
			///		削除するキーの状態クラス．
			///	</param>
			Keys&				operator-(const Keys &KeysList) const;
			///	<summary>
			///		キー追加のoperator．
			///	</summary>
			///	<param name = "KeysList">
			///		追加するキーの状態クラス．
			///	</param>
			Keys&				operator+=(const Keys &KeysList);
			///	<summary>
			///		キー削除のoperator．
			///	</summary>
			///	<param name = "KeysList">
			///		削除するキーの状態クラス．
			///	</param>
			Keys&				operator-=(const Keys &KeysList);
			///	<summary>
			///		比較のoperator．
			///	</summary>
			///	<param name = "Key">
			///		比較するキーのコード．
			///	</param>
			bool				operator&&(int Key) const;
			///	<summary>
			///		比較のoperator．
			///	</summary>
			///	<param name = "KeysList">
			///		比較するキーの状態クラス．
			///	</param>
			bool				operator==(const Keys &KeysList) const;
			///	<summary>
			///		登録キーサイズを取得する．
			///	</summary>
			unsigned int		_Size() const;
			///	<summary>
			///		登録キーの番号を取得する．
			///	</summary>
			int					_Get(int Val) const;
		private:
			///	<summary>
			///		確認するキーの種類．
			///	</summary>
			std::set<int>		_CheckKeyList;
		};

		///	<summary>
		///		キーボードの対応数字を列挙したクラス．
		///	</summary>
		class Key : public virtual Base::__ApcEnumeration
		{
		public:
			///	<summary>
			///		キーボードのAキー．
			///	</summary>
			static const Keys	A;
			///	<summary>
			///		キーボードのBキー．
			///	</summary>
			static const Keys	B;
			///	<summary>
			///		キーボードのCキー．
			///	</summary>
			static const Keys	C;
			///	<summary>
			///		キーボードのDキー．
			///	</summary>
			static const Keys	D;
			///	<summary>
			///		キーボードのEキー．
			///	</summary>
			static const Keys	E;
			///	<summary>
			///		キーボードのFキー．
			///	</summary>
			static const Keys	F;
			///	<summary>
			///		キーボードのGキー．
			///	</summary>
			static const Keys	G;
			///	<summary>
			///		キーボードのHキー．
			///	</summary>
			static const Keys	H;
			///	<summary>
			///		キーボードのIキー．
			///	</summary>
			static const Keys	I;
			///	<summary>
			///		キーボードのJキー．
			///	</summary>
			static const Keys	J;
			///	<summary>
			///		キーボードのKキー．
			///	</summary>
			static const Keys	K;
			///	<summary>
			///		キーボードのLキー．
			///	</summary>
			static const Keys	L;
			///	<summary>
			///		キーボードのMキー．
			///	</summary>
			static const Keys	M;
			///	<summary>
			///		キーボードのNキー．
			///	</summary>
			static const Keys	N;
			///	<summary>
			///		キーボードのOキー．
			///	</summary>
			static const Keys	O;
			///	<summary>
			///		キーボードのPキー．
			///	</summary>
			static const Keys	P;
			///	<summary>
			///		キーボードのQキー．
			///	</summary>
			static const Keys	Q;
			///	<summary>
			///		キーボードのRキー．
			///	</summary>
			static const Keys	R;
			///	<summary>
			///		キーボードのSキー．
			///	</summary>
			static const Keys	S;
			///	<summary>
			///		キーボードのTキー．
			///	</summary>
			static const Keys	T;
			///	<summary>
			///		キーボードのUキー．
			///	</summary>
			static const Keys	U;
			///	<summary>
			///		キーボードのVキー．
			///	</summary>
			static const Keys	V;
			///	<summary>
			///		キーボードのWキー．
			///	</summary>
			static const Keys	W;
			///	<summary>
			///		キーボードのXキー．
			///	</summary>
			static const Keys	X;
			///	<summary>
			///		キーボードのYキー．
			///	</summary>
			static const Keys	Y;
			///	<summary>
			///		キーボードのZキー．
			///	</summary>
			static const Keys	Z;
			///	<summary>
			///		キーボードのEnterキー．
			///	</summary>
			static const Keys	Enter;
			///	<summary>
			///		キーボードのEscキー．
			///	</summary>
			static const Keys	Escape;
			///	<summary>
			///		キーボードのTabキー．
			///	</summary>
			static const Keys	Tab;
			///	<summary>
			///		キーボードの両Shiftキー．
			///	</summary>
			static const Keys	Shift;
			///	<summary>
			///		キーボードの両Ctrlキー．
			///	</summary>
			static const Keys	Control;
			///	<summary>
			///		キーボードの両Altキー．
			///	</summary>
			static const Keys	Alt;
			///	<summary>
			///		キーボードのSpaceキー．
			///	</summary>
			static const Keys	Space;
			///	<summary>
			///		キーボードのBackSpaceキー．
			///	</summary>
			static const Keys	BackSpace;
			///	<summary>
			///		キーボードのDeleteキー．
			///	</summary>
			static const Keys	Delete;
			///	<summary>
			///		キーボードの上キー．
			///	</summary>
			static const Keys	Up;
			///	<summary>
			///		キーボードの左キー．
			///	</summary>
			static const Keys	Left;
			///	<summary>
			///		キーボードの右キー．
			///	</summary>
			static const Keys	Right;
			///	<summary>
			///		キーボードの下キー．
			///	</summary>
			static const Keys	Down;
		};
	}
}
