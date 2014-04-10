// --------------------------------------------------------
//	apcEvent.h
// --------------------------------------------------------
//	イベントハンドラ関連のクラスを記載する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <list>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <include/apcClassBase.hpp>
#include <include/apcInput.hpp>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Event)
// --------------------------------------------------------
namespace Apocalypse
{
	// ------------------------------------------------
	//	Front Declaration
	// ------------------------------------------------
	namespace Draw
	{
		class				_FrameBase;
		class				Color;
	};

	namespace Event
	{
		// ------------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class						EventHandle;

		// ------------------------------------------------
		//	Typedef
		// ------------------------------------------------
		typedef						boost::function<bool()>	EventFlag;
		typedef						boost::function<void()>	EventFunc;

		///	<summary>
		///		イベントの追加・削除・管理を行うクラス．
		///	</summary>
		class _EventHandleList : public Base::_ApcInside
		{
		public:
			/// <summary>
			///		登録されたイベントハンドルの関数を実行するかどうか確認する．
			/// </summary>
			void					_ArrayCheck() const;
			/// <summary>
			///		イベントハンドルを末尾に追加する．
			/// </summary>
			/// <param name = "Handle">
			///		追加する対象のイベント．
			/// </param>
			EventHandle*			operator+=(EventHandle* Handle);
			/// <summary>
			///		イベントハンドルを末尾に追加する．
			/// </summary>
			/// <param name = "Handle">
			///		追加する対象のイベント．
			/// </param>
			std::shared_ptr<EventHandle>
									operator+=(std::shared_ptr<EventHandle> Handle);
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String	ToString() const;
			/// <summary>
			///		デストラクタ．
			/// </summary>
			virtual					~_EventHandleList();
		private:
			/// <summary>
			///		代入演算子を無効化
			/// </summary>
			void					operator=(_EventHandleList){}
			/// <summary>
			///		イベントを管理するコンテナ．
			/// </summary>
			std::list<std::shared_ptr<EventHandle>>
									_EventItems;
		};

		///	<summary>
		///		イベントを管理する基本のハンドルクラス
		///	</summary>
		class EventHandle : public Base::_ApcBase
		{
		public:
			/// <summary>
			///		引数を指定しない版のコンストラクタ．作成したイベントは既定では何もしません．
			/// </summary>
									EventHandle();
			/// <summary>
			///		実行関数を指定するコンストラクタ．作成したイベントは毎フレームごとに実行されます．
			/// </summary>
			/// <param name = "Func">
			///		実行する関数．クラスメンバの関数の場合はboost::bind関数を使用する必要があります．
			/// </param>
									EventHandle(EventFunc Func);
			/// <summary>
			///		実行関数と実行条件関数を指定するコンストラクタ．
			/// </summary>
			/// <param name = "Func">
			///		実行する関数．クラスメンバの関数の場合はboost::bind関数を使用する必要があります．
			/// </param>
			/// <param name = "Ty">
			///		<para>判定の関数．クラスメンバの関数の場合はboost::bind関数を使用する必要があります．</para>
			///		<para>boost::bind関数を使用することで，引数を持った関数を実行させることもできます．</para>
			///		<para>また，EventTypeクラスの関数を引数に指定することもできます．</para>
			/// </param>
									EventHandle(EventFunc Func, EventFlag Ty);
			/// <summary>
			///		このイベントハンドルが有効かどうか．
			/// </summary>
			bool					Enable;
			/// <summary>
			///		引数が無く戻り値がvoidの関数．この関数内で各種処理を行う．
			/// </summary>
			EventFunc				Function;
			/// <summary>
			///		引数が無く戻り値がboolの関数．この関数の戻り値がtrueの場合にFunctionを実行する．
			/// </summary>
			EventFlag				Type;
			/// <summary>
			///		このイベントを処理する前に行うイベントをポインタで指定する．
			///		Eventsクラスに挿入する前に指定した場合のみ適用される．
			/// </summary>
			EventHandle*			BeforeEvent;
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String	ToString() const;
		};

		///	<summary>
		///		イベント条件の一覧クラス．
		///	</summary>
		class EventType : public Base::_ApcEnumeration
		{
		public:
			template<typename Type>
			/// <summary>
			///		引数に渡した値が変更されている場合にTRUEを返す．
			/// </summary>
			static EventFlag		PropertyChanged(const Type &Target)
			{
				// 値比較用の参照
				Type &Obj = *(new Type(Target));
				// 比較関数のlambda式を返す
				return [&Obj, &Target](){
					// 値を比較する
					bool Result = !(Target == Obj);
					// 値をコピーする
					Obj = Target;
					// 返却する
					return Result;
				};
			}
			template<typename Type>
			/// <summary>
			///		引数に渡した関数の戻り値が変更されている場合にTRUEを返す．
			/// </summary>
			static EventFlag		ResultChanged(boost::function<Type()> Func)
			{
				// 値比較用の参照
				Type &Obj = *(new Type(Func()));
				// 関数の参照の保存
				boost::function<Type()> &Fc = *(new boost::function<Type()>(Func));
				// 比較関数のlambda式を返す
				return [&Obj, &Fc](){
					// 値を取得する
					Type Val = Fc();
					// 値を比較する
					bool Result = !(Val == Obj);
					// 値をコピーする
					Obj = Val;
					// 返却する
					return Result;
				};
			}
			/// <summary>
			///		常にTRUEを返します．
			/// </summary>
			static EventFlag		Process();
			/// <summary>
			///		2つの項目を比較して，両方がTRUEを返したならTRUEを返します．
			/// </summary>
			static EventFlag		And(const EventFlag &A, const EventFlag &B);
			/// <summary>
			///		2つの項目を比較して，片方がTRUEを返したならTRUEを返します．
			/// </summary>
			static EventFlag		Or(const EventFlag &A, const EventFlag &B);
			/// <summary>
			///		2つの項目を比較して，両方がFALSEを返したならTRUEを返します．
			/// </summary>
			static EventFlag		Nor(const EventFlag &A, const EventFlag &B);
			/// <summary>
			///		2つの項目を比較して，片方がFALSEを返したならTRUEを返します．
			/// </summary>
			static EventFlag		Not(const EventFlag &A, const EventFlag &B);
			/// <summary>
			///		キーかマウスが押された場合にTRUEを返します．
			/// </summary>
			static EventFlag		AnyPush();
			/// <summary>
			///		マウスが動いた際にTRUEを返します．
			/// </summary>
			static EventFlag		MouseMove();
			/// <summary>
			///		マウスが指定した領域に存在する際にTRUEを返します．
			/// </summary>
			/// <param name = "X">
			///		指定する領域の中心部分のX座標を指定します．
			/// </param>
			/// <param name = "Y">
			///		指定する領域の中心部分のY座標を指定します．
			/// </param>
			/// <param name = "Margin">
			///		指定する領域の中心部分からの枠の大きさを指定します．
			/// </param>
			static EventFlag		MouseOnArea(int X, int Y, int Margin);
			/// <summary>
			///		マウスが指定した領域に存在する際にTRUEを返します．
			/// </summary>
			/// <param name = "Pt">
			///		指定する領域の中心部分の座標を指定します．
			/// </param>
			/// <param name = "Margin">
			///		指定する領域の中心部分からの枠の大きさを指定します．
			/// </param>
			static EventFlag		MouseOnArea(Value::Point &Pt, int Margin);
			/// <summary>
			///		マウスが指定した領域に存在する際にTRUEを返します．
			/// </summary>
			/// <param name = "X">
			///		指定する領域の中心部分のX座標を指定します．
			/// </param>
			/// <param name = "Y">
			///		指定する領域の中心部分のY座標を指定します．
			/// </param>
			/// <param name = "MarginWidth">
			///		指定する領域の中心部分からの枠の横部分の大きさを指定します．
			/// </param>
			/// <param name = "MarginHeight">
			///		指定する領域の中心部分からの枠の縦部分の大きさを指定します．
			/// </param>
			static EventFlag		MouseOnArea(int X, int Y, int MarginWidth, int MarginHeight);
			/// <summary>
			///		マウスが指定した領域に存在する際にTRUEを返します．
			/// </summary>
			/// <param name = "Pt">
			///		指定する領域の中心部分の座標を指定します．
			/// </param>
			/// <param name = "MarginWidth">
			///		指定する領域の中心部分からの枠の横部分の大きさを指定します．
			/// </param>
			/// <param name = "MarginHeight">
			///		指定する領域の中心部分からの枠の縦部分の大きさを指定します．
			/// </param>
			static EventFlag		MouseOnArea(Value::Point &Pt, int MarginWidth, int MarginHeight);
			/// <summary>
			///		マウスが指定したフレーム上に領域に存在する際にTRUEを返します．
			/// </summary>
			/// <param name = "Frame">
			///		フレームを指定します．
			/// </param>
			static EventFlag		MouseOnFrame(Draw::_FrameBase &Frame);
			/// <summary>
			///		マウスの左ボタンがクリックされた際にTRUEを返します．
			/// </summary>
			static EventFlag		MouseLClick();
			/// <summary>
			///		マウスの右ボタンがクリックされた際にTRUEを返します．
			/// </summary>
			static EventFlag		MouseRClick();
			/// <summary>
			///		マウスの左ボタンが押されている間TRUEを返します．
			/// </summary>
			static EventFlag		MouseLPush();
			/// <summary>
			///		マウスの右ボタンが押されている間TRUEを返します．
			/// </summary>
			static EventFlag		MouseRPush();
			/// <summary>
			///		マウスの左ボタンが離された瞬間のみ間TRUEを返します．
			/// </summary>
			static EventFlag		MouseLUp();
			/// <summary>
			///		マウスの右ボタンが離された瞬間のみ間TRUEを返します．
			/// </summary>
			static EventFlag		MouseRUp();
			/// <summary>
			///		引数に指定したキーが押された瞬間のみTRUEを返します．
			/// </summary>
			/// <param name = "CheckKey">
			///		確認するキーを指定します．
			/// </param>
			static EventFlag		KeyBoardPush(const Input::_KeysData &CheckKey);
			/// <summary>
			///		引数に指定したキーが押されている間TRUEを返します．
			/// </summary>
			/// <param name = "CheckKey">
			///		確認するキーを指定します．
			/// </param>
			static EventFlag		KeyBoardDown(const Input::_KeysData &CheckKey);
			/// <summary>
			///		引数に指定したキーが離された瞬間のみTRUEを返します．
			/// </summary>
			/// <param name = "CheckKey">
			///		確認するキーを指定します．
			/// </param>
			static EventFlag		KeyBoardUp(const Input::_KeysData &CheckKey);
			/// <summary>
			///		引数に指定した色クラスが示す色が変更された時TRUEを返します．
			/// </summary>
			/// <param name = "Cr">
			///		確認する色クラスを指定します．
			/// </param>
			static EventFlag		ColorChanged(const Draw::Color &Cr);
		};
	}
}