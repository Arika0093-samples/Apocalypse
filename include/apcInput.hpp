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
		class _KeysData;

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
		class KeyBoard : public Template::_Singleton<KeyBoard>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::_Singleton<KeyBoard>;
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
			static UINT			Pushing(const _KeysData &TargetKey);
			/// <summary>
			///		指定したキーがこのフレームで初めて押されたかどうかの情報を取得する．
			/// </summary>
			/// <param name = "TargetKey">
			///		取得する対象のキー．KeyListで定義された値を使用して下さい．
			/// </param>
			static bool			PushStart(const _KeysData &TargetKey);
			/// <summary>
			///		指定したキーがこのフレームで初めて離されたかどうかの情報を取得する．
			/// </summary>
			/// <param name = "TargetKey">
			///		取得する対象のキー．KeyListで定義された値を使用して下さい．
			/// </param>
			static bool			OutStart(const _KeysData &TargetKey);
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
		class Mouse : public Template::_Singleton<Mouse>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::_Singleton<Mouse>;
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
		class _KeysData : public virtual Base::_ApcBase
		{
		public:
			///	<summary>
			///		初期キーとして特に何も持たない_KeysDataクラスのコンストラクタ．
			///	</summary>
								_KeysData();
			///	<summary>
			///		初期キーとして引数に指定されたキーを持つ_KeysDataクラスのコンストラクタ．
			///	</summary>
			///	<param name = "FstKey">
			///		初期キー．
			///	</param>
								_KeysData(int FstKey);
			///	<summary>
			///		初期キーとして引数に指定された2つのキーを持つ_KeysDataクラスのコンストラクタ．
			///	</summary>
			///	<param name = "FstKey_1">
			///		初期キーその1．
			///	</param>
			///	<param name = "FstKey_2">
			///		初期キーその2．
			///	</param>
								_KeysData(int FstKey_1, int FstKey_2);
			///	<summary>
			///		初期キーとして引数に指定された複数のキーを持つ_KeysDataクラスのコンストラクタ．
			///	</summary>
			///	<param name = "Fst_KeysData">
			///		複数の初期キー．
			///	</param>
			///	<param name = "Size">
			///		登録するキーの個数．
			///	</param>
								_KeysData(int FstKey[], size_t Size);
			///	<summary>
			///		デストラクタ．
			///	</summary>
								~_KeysData(){}
			///	<summary>
			///		2つのキーの状態を比較する関数．
			///	</summary>
			///	<param name = "_KeysDataList">
			///		比較するキーの状態クラス．
			///	</param>
			bool				Compare(const _KeysData &_KeysDataList) const;
			///	<summary>
			///		キー追加のoperator．
			///	</summary>
			///	<param name = "_KeysDataList">
			///		追加するキーの状態クラス．
			///	</param>
			_KeysData&			operator+(const _KeysData &_KeysDataList) const;
			///	<summary>
			///		キー削除のoperator．
			///	</summary>
			///	<param name = "_KeysDataList">
			///		削除するキーの状態クラス．
			///	</param>
			_KeysData&			operator-(const _KeysData &_KeysDataList) const;
			///	<summary>
			///		キー追加のoperator．
			///	</summary>
			///	<param name = "_KeysDataList">
			///		追加するキーの状態クラス．
			///	</param>
			_KeysData&			operator+=(const _KeysData &_KeysDataList);
			///	<summary>
			///		キー削除のoperator．
			///	</summary>
			///	<param name = "_KeysDataList">
			///		削除するキーの状態クラス．
			///	</param>
			_KeysData&			operator-=(const _KeysData &_KeysDataList);
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
			///	<param name = "_KeysDataList">
			///		比較するキーの状態クラス．
			///	</param>
			bool				operator==(const _KeysData &_KeysDataList) const;
			///	<summary>
			///		<para>判定関数で全てが押されてる場合を判定するかどうか．</para>
			///		<para>標準ではfalse（どれか一つが押されている場合を判定する）．</para>
			///	</summary>
			bool				IsCheckAllKey;
			///	<summary>
			///		登録キーサイズを取得する．
			///	</summary>
			size_t				_Size() const;
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
		class Key : public virtual Base::_ApcEnumeration
		{
		public:
			///	<summary>
			///		キーボードのAキー．
			///	</summary>
			static const _KeysData	A;
			///	<summary>
			///		キーボードのBキー．
			///	</summary>
			static const _KeysData	B;
			///	<summary>
			///		キーボードのCキー．
			///	</summary>
			static const _KeysData	C;
			///	<summary>
			///		キーボードのDキー．
			///	</summary>
			static const _KeysData	D;
			///	<summary>
			///		キーボードのEキー．
			///	</summary>
			static const _KeysData	E;
			///	<summary>
			///		キーボードのFキー．
			///	</summary>
			static const _KeysData	F;
			///	<summary>
			///		キーボードのGキー．
			///	</summary>
			static const _KeysData	G;
			///	<summary>
			///		キーボードのHキー．
			///	</summary>
			static const _KeysData	H;
			///	<summary>
			///		キーボードのIキー．
			///	</summary>
			static const _KeysData	I;
			///	<summary>
			///		キーボードのJキー．
			///	</summary>
			static const _KeysData	J;
			///	<summary>
			///		キーボードのKキー．
			///	</summary>
			static const _KeysData	K;
			///	<summary>
			///		キーボードのLキー．
			///	</summary>
			static const _KeysData	L;
			///	<summary>
			///		キーボードのMキー．
			///	</summary>
			static const _KeysData	M;
			///	<summary>
			///		キーボードのNキー．
			///	</summary>
			static const _KeysData	N;
			///	<summary>
			///		キーボードのOキー．
			///	</summary>
			static const _KeysData	O;
			///	<summary>
			///		キーボードのPキー．
			///	</summary>
			static const _KeysData	P;
			///	<summary>
			///		キーボードのQキー．
			///	</summary>
			static const _KeysData	Q;
			///	<summary>
			///		キーボードのRキー．
			///	</summary>
			static const _KeysData	R;
			///	<summary>
			///		キーボードのSキー．
			///	</summary>
			static const _KeysData	S;
			///	<summary>
			///		キーボードのTキー．
			///	</summary>
			static const _KeysData	T;
			///	<summary>
			///		キーボードのUキー．
			///	</summary>
			static const _KeysData	U;
			///	<summary>
			///		キーボードのVキー．
			///	</summary>
			static const _KeysData	V;
			///	<summary>
			///		キーボードのWキー．
			///	</summary>
			static const _KeysData	W;
			///	<summary>
			///		キーボードのXキー．
			///	</summary>
			static const _KeysData	X;
			///	<summary>
			///		キーボードのYキー．
			///	</summary>
			static const _KeysData	Y;
			///	<summary>
			///		キーボードのZキー．
			///	</summary>
			static const _KeysData	Z;
			///	<summary>
			///		キーボードの1キー．
			///	</summary>
			static const _KeysData	N1;
			///	<summary>
			///		キーボードの2キー．
			///	</summary>
			static const _KeysData	N2;
			///	<summary>
			///		キーボードの3キー．
			///	</summary>
			static const _KeysData	N3;
			///	<summary>
			///		キーボードの4キー．
			///	</summary>
			static const _KeysData	N4;
			///	<summary>
			///		キーボードの5キー．
			///	</summary>
			static const _KeysData	N5;
			///	<summary>
			///		キーボードの6キー．
			///	</summary>
			static const _KeysData	N6;
			///	<summary>
			///		キーボードの7キー．
			///	</summary>
			static const _KeysData	N7;
			///	<summary>
			///		キーボードの8キー．
			///	</summary>
			static const _KeysData	N8;
			///	<summary>
			///		キーボードの9キー．
			///	</summary>
			static const _KeysData	N9;
			///	<summary>
			///		キーボードの0キー．
			///	</summary>
			static const _KeysData	N0;
			///	<summary>
			///		キーボードのEnterキー．
			///	</summary>
			static const _KeysData	Enter;
			///	<summary>
			///		キーボードのEscキー．
			///	</summary>
			static const _KeysData	Escape;
			///	<summary>
			///		キーボードのTabキー．
			///	</summary>
			static const _KeysData	Tab;
			///	<summary>
			///		キーボードの両Shiftキー．
			///	</summary>
			static const _KeysData	Shift;
			///	<summary>
			///		キーボードの両Ctrlキー．
			///	</summary>
			static const _KeysData	Control;
			///	<summary>
			///		キーボードの両Altキー．
			///	</summary>
			static const _KeysData	Alt;
			///	<summary>
			///		キーボードのSpaceキー．
			///	</summary>
			static const _KeysData	Space;
			///	<summary>
			///		キーボードのBackSpaceキー．
			///	</summary>
			static const _KeysData	BackSpace;
			///	<summary>
			///		キーボードのDeleteキー．
			///	</summary>
			static const _KeysData	Delete;
			///	<summary>
			///		キーボードの上キー．
			///	</summary>
			static const _KeysData	Up;
			///	<summary>
			///		キーボードの左キー．
			///	</summary>
			static const _KeysData	Left;
			///	<summary>
			///		キーボードの右キー．
			///	</summary>
			static const _KeysData	Right;
			///	<summary>
			///		キーボードの下キー．
			///	</summary>
			static const _KeysData	Down;
		};
	}
}
