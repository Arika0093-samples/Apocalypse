// --------------------------------------------------------
//	apcValue.hpp
// --------------------------------------------------------
//	数式関連のクラスを記載する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <Windows.h>
#include <tchar.h>
#include <sstream>
#include <memory>
#include <vector>
#include <boost/function.hpp>
#include <boost/algorithm/string.hpp>
#include <include/apcClassBase.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Value)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Value
	{
		// -----------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class String;

		///	<summary>
		///		一定間隔で増加していく値を管理する．
		///	</summary>
		class Timer : public virtual Base::__ApcInside
		{
		public:
			///	<summary>
			///		コンストラクタ
			///	</summary>
								Timer();
			///	<summary>
			///		タイマーの繰り返すタイプの一覧．
			///	</summary>
			enum				_LoopType
			{
				///	<summary>
				///		繰り返さない．最終地点で停止する．
				///	</summary>
				No,
				///	<summary>
				///		最後まで到達したら最初から繰り返す．
				///	</summary>
				Repeat,
				///	<summary>
				///		最後まで到達したら一度だけ折り返す．
				///	</summary>
				ReturnOnce,
				///	<summary>
				///		端まで到達したら折り返す．
				///	</summary>
				Return,
			};
			///	<summary>
			///		タイマーの値を取得する．
			///	</summary>
			double				operator()();
			///	<summary>
			///		更新タイミングで値をいくつ増加させるか．
			///	</summary>
			double				Add;
			///	<summary>
			///		1ループの周期．0で終点無し．
			///	</summary>
			int					Cycle;
			///	<summary>
			///		自身が有効なTimerかどうか．falseに指定すると値の自動増加を停止する．
			///	</summary>
			bool				Enable;
			///	<summary>
			///		折り返す種類．標準ではNo(折り返さない)．
			///	</summary>
			_LoopType			LoopType;
			/// <summary>
			///		Timerの値を初期化する．
			/// </summary>
			void				Reset();
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String
								ToString() const;
			/// <summary>
			///		Timerの値を値を更新せずに取得する．
			/// </summary>
			double				_GetValueNoReload() const;
		private:
			///	<summary>
			///		内部で保持する値．
			///	</summary>
			double				_Val;
			///	<summary>
			///		折り返しているかどうか．
			///	</summary>
			bool				_IsReturned;
			///	<summary>
			///		最後に呼び出された時のFC値．
			///	</summary>
			double				_LastCalledFrame;
			///	<summary>
			///		タイマー更新
			///	</summary>
			void				_TimerReload(int CallTimes);
			///	<summary>
			///		繰り返し時の処理関数
			///	</summary>
			bool				_RepeatFunc();
		};

		///	<summary>
		///		Numberで値を管理するPOINT構造体．
		///	</summary>
		class Point : public virtual Base::__ApcBase
		{
		public:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								Point();
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								Point(double X, double Y);
			///	<summary>
			///		位置のX座標．
			///	</summary>
			double				X;
			///	<summary>
			///		位置のY座標．
			///	</summary>
			double				Y;
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String
								ToString() const;
			///	<summary>
			///		代入する．
			///	</summary>
			void				operator()(double X, double Y);
			///	<summary>
			///		コピーする．
			///	</summary>
			Point&				operator=(Point& Pt);
			///	<summary>
			///		コピーする．
			///	</summary>
			Point&				operator=(double Val);
			///	<summary>
			///		比較する．
			///	</summary>
			bool				operator==(Point& Pt);
			///	<summary>
			///		比較する．
			///	</summary>
			bool				operator!=(Point& Pt);
		};

		///	<summary>
		///		文字列管理クラス．
		///	</summary>
		/// <remarks>
		///		<para>このクラスは，基本的にSTLのstringと同じように使用できます．</para>
		///		<para>stringstreamのように使用することが可能になっています．</para>
		///		<para>その他，便利そうな機能を追加しています．</para>
		/// </remarks>
		class String : public Base::__ApcBase, public std::basic_string<TCHAR>
		{
			///	<summary>
			///		typedef
			///	</summary>
			typedef				std::basic_string<TCHAR>		tstring;
		public:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								String(LPCTSTR Text = _T(""));
			///	<summary>
			///		文字列をデバッグウインドウに出力する
			///	</summary>
			void				DebugOutput() const;
			///	<summary>
			///		文字列をMessageBoxで表示する
			///	</summary>
			void				Message() const;
			///	<summary>
			///		文字列をMessageBoxで表示する
			///	</summary>
			/// <param name = "Style">
			///		MB_XXマクロを指定する．
			/// </param>
			/// <returns>
			///		IDYES，IDNOなどの結果．
			/// </returns>
			int					Message(unsigned int Style) const;
			///	<summary>
			///		自身を，引数の文字列の配列を繋げたものに置き換える．
			///	</summary>
			/// <param name = "Array">
			///		繋げる対象の配列．
			/// </param>
			static String&		Connect(const std::vector<String> &Array);
			///	<summary>
			///		自身を，引数の文字列の配列を特定文字で繋げたものに置き換える．
			///	</summary>
			/// <param name = "Array">
			///		繋げる対象の配列．
			/// </param>
			/// <param name = "Cs">
			///		文字と文字を繋げる文字列．
			/// </param>
			static String&		Connect(const std::vector<String> &Array, const String &Cs);
			///	<summary>
			///		文字列の特定部分を引数で置き換えたものを返却する．
			///	</summary>
			/// <param name = "From">
			///		置き換える対象の文字列．
			/// </param>
			/// <param name = "To">
			///		置き換えた先の文字列．
			/// </param>
			String&				Replace(const String &From, const String &To) const;
			///	<summary>
			///		文字列を特定部分で区切って配列に格納したものを返却する．
			///	</summary>
			/// <param name = "Sp">
			///		区切る文字列を列挙する．
			/// </param>
			std::vector<String> Split(const String &Sp) const;			
			///	<summary>
			///		文字列を特定部分で区切って配列に格納したものを返却する．
			///	</summary>
			/// <param name = "Sp">
			///		区切る文字列を列挙する．
			/// </param>
			/// <param name = "IsSpaceAble">
			///		空白の配列を返却するかどうかを指定する．
			/// </param>
			std::vector<String> Split(const String &Sp, bool IsSpaceAble) const;			
			///	<summary>
			///		operator LPCTSTR.
			///	</summary>
								operator LPCTSTR() const;
			///	<summary>
			///		文字列を代入する．
			///	</summary>
			String&				operator=(tstring Val);
			///	<summary>
			///		文字列を代入する．
			///	</summary>
			String&				operator=(LPCTSTR Val);
			///	<summary>
			///		文字列にboolを流す．
			///	</summary>
			String&				operator<<(const bool Val);
			///	<summary>
			///		文字列にintを流す．
			///	</summary>
			String&				operator<<(const int Val);
			///	<summary>
			///		文字列にUINTを流す．
			///	</summary>
			String&				operator<<(const UINT Val);
			///	<summary>
			///		文字列にshortを流す．
			///	</summary>
			String&				operator<<(const short Val);
			///	<summary>
			///		文字列にUSHORTを流す．
			///	</summary>
			String&				operator<<(const USHORT Val);
			///	<summary>
			///		文字列にlongを流す．
			///	</summary>
			String&				operator<<(const long Val);
			///	<summary>
			///		文字列にULONGを流す．
			///	</summary>
			String&				operator<<(const ULONG Val);
			///	<summary>
			///		文字列にdoubleを流す．
			///	</summary>
			String&				operator<<(const double Val);
			///	<summary>
			///		文字列にPointerを流す．
			///	</summary>
			String&				operator<<(const void *Val);
			///	<summary>
			///		文字列にTCHARを流す．
			///	</summary>
			String&				operator<<(const TCHAR Val);
			///	<summary>
			///		文字列にLPCTSTRを流す．
			///	</summary>
			String&				operator<<(const LPCTSTR Val);
			///	<summary>
			///		文字列にStringを流す．
			///	</summary>
			String&				operator<<(const String& Val);
			///	<summary>
			///		文字列にPointを流す．
			///	</summary>
			String&				operator<<(const Point& Val);
			template<typename Type>
			///	<summary>
			///		文字列を指定した型に変換する．
			///	</summary>
			Type				ToValue() const
			{
				// stringstreamを使用する
				std::basic_stringstream<TCHAR> Ts;
				// 値を取得する用の変数
				Type Result;
				// --------------------------------
				// 代入
				Ts << this->c_str();
				// 取得
				Ts >> Result;
				// 返却
				return Result;
			}
		private:
			template<typename Type>
			String&				FromValue(Type Val);
		};
	}
}