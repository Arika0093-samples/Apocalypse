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
//	defineマクロを使用する
// --------------------------------------------------------
//	イベントリストにクラスメンバ関数を追加するマクロ．
#define ClassFunc(FuncName)		boost::bind(&FuncName, this)

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
		class				__FrameBase;
	};

	namespace Event
	{
		// ------------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class				EventHandle;

		// ------------------------------------------------
		//	Typedef
		// ------------------------------------------------
		typedef				boost::function<bool()>		EventFunc, EventFlag;

		///	<summary>
		///		イベントの追加・削除・管理を行うクラス．
		///	</summary>
		class __EventHandleList : public Base::__ApcInside
		{
		public:
			/// <summary>
			///		登録されたイベントハンドルの関数を実行するかどうか確認する．
			/// </summary>
			void			_ArrayCheck() const;
			/// <summary>
			///		イベントハンドルを末尾に追加する．
			/// </summary>
			/// <param name = "Handle">
			///		追加する対象のイベント．
			/// </param>
			std::shared_ptr<EventHandle>
							operator+=(std::shared_ptr<EventHandle> Handle);
			/// <summary>
			///		デストラクタ．
			/// </summary>
			virtual			~__EventHandleList();
		private:
			/// <summary>
			///		代入演算子を無効化
			/// </summary>
			void			operator=(__EventHandleList){}
			/// <summary>
			///		イベントを管理するコンテナ．
			/// </summary>
			std::list<std::shared_ptr<EventHandle>>
							_EventItems;
		};

		///	<summary>
		///		イベントの基板クラス．このイベント自体は生成できない．
		///	</summary>
		class EventHandle : public Base::__ApcBase
		{
			friend class	__EventHandleList;
		public:
			/// <summary>
			///		<para>EventTypeを指定しない版コンストラクタ．</para>
			///		<para>このコンストラクタでは毎フレーム関数が実行されます(EventList::Process()と同じ)．</para>
			/// </summary>
			/// <param name = "Func">
			///		実行する関数．クラスメンバの関数の場合はboost::bind関数を使用する必要があります．
			/// </param>
							EventHandle(EventFunc Func);
			/// <summary>
			///		EventTypeを指定する版コンストラクタ．
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
		private:
			/// <summary>
			///		イベント関数．この関数内で各種処理を行う．
			/// </summary>
			EventFunc		_Function;
			/// <summary>
			///		イベント判定関数．この関数内で各種判定を行う．
			/// </summary>
			EventFlag		_Type;
			/// <summary>
			///		イベントが繰り返し実行となっているかどうか．
			/// </summary>
			bool			_ContinueFlag;
		};

		///	<summary>
		///		イベント条件の一覧クラス．
		///	</summary>
		class EventType : public Base::__ApcEnumeration
		{
		public:
			/// <summary>
			///		常にTRUEを返します．
			/// </summary>
			static EventFlag	Process();
			/// <summary>
			///		マウスが動いた際にTRUEを返します．
			/// </summary>
			static EventFlag	MouseMove();
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
			static EventFlag	MouseOnArea(int X, int Y, int Margin);
			/// <summary>
			///		マウスが指定した領域に存在する際にTRUEを返します．
			/// </summary>
			/// <param name = "Pt">
			///		指定する領域の中心部分の座標を指定します．
			/// </param>
			/// <param name = "Margin">
			///		指定する領域の中心部分からの枠の大きさを指定します．
			/// </param>
			static EventFlag	MouseOnArea(Base::Point &Pt, int Margin);
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
			static EventFlag	MouseOnArea(int X, int Y, int MarginWidth, int MarginHeight);
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
			static EventFlag	MouseOnArea(Base::Point &Pt, int MarginWidth, int MarginHeight);
			/// <summary>
			///		マウスが指定したフレーム上に領域に存在する際にTRUEを返します．
			/// </summary>
			/// <param name = "Frame">
			///		フレームを指定します．
			/// </param>
			static EventFlag	MouseOnFrame(Draw::__FrameBase &Frame);
			/// <summary>
			///		マウスの左ボタンがクリックされた際にTRUEを返します．
			/// </summary>
			static EventFlag	MouseLClick();
			/// <summary>
			///		マウスの右ボタンがクリックされた際にTRUEを返します．
			/// </summary>
			static EventFlag	MouseRClick();
			/// <summary>
			///		マウスの左ボタンが押されている間TRUEを返します．
			/// </summary>
			static EventFlag	MouseLPush();
			/// <summary>
			///		マウスの右ボタンが押されている間TRUEを返します．
			/// </summary>
			static EventFlag	MouseRPush();
			/// <summary>
			///		マウスの左ボタンが離された瞬間のみ間TRUEを返します．
			/// </summary>
			static EventFlag	MouseLUp();
			/// <summary>
			///		マウスの右ボタンが離された瞬間のみ間TRUEを返します．
			/// </summary>
			static EventFlag	MouseRUp();
			/// <summary>
			///		引数に指定したキーが押された瞬間のみTRUEを返します．
			/// </summary>
			/// <param name = "CheckKey">
			///		確認するキーを指定します．
			/// </param>
			static EventFlag	KeyBoardPush(Input::Keys CheckKey);
			/// <summary>
			///		引数に指定したキーが押された瞬間のみTRUEを返します．
			/// </summary>
			/// <param name = "CheckKey">
			///		確認するキーを指定します．
			/// </param>
			static EventFlag	KeyBoardDown(Input::Keys CheckKey);
			/// <summary>
			///		引数に指定したキーが離された瞬間のみTRUEを返します．
			/// </summary>
			/// <param name = "CheckKey">
			///		確認するキーを指定します．
			/// </param>
			static EventFlag	KeyBoardUp(Input::Keys CheckKey);
			/// <summary>
			///		キーかマウスが押された場合にTRUEを返します．
			/// </summary>
			static EventFlag	AnyPush();
		};
	}
}
