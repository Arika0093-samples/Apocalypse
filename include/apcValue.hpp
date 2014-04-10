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
		class Timer : public virtual Base::_ApcInside
		{
		public:
			///	<summary>
			///		タイマーの繰り返すタイプの一覧．
			///	</summary>
			class					LoopType : public Base::_ApcEnumeration
			{
			public:
				///	<summary>
				///		タイマーの繰り返すタイプの一覧．
				///	</summary>
				enum					_LoopType
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
			};
			///	<summary>
			///		コンストラクタ
			///	</summary>
									Timer();
			///	<summary>
			///		タイマーの値を取得する．
			///	</summary>
			double					operator()();
			///	<summary>
			///		1秒間に値をいくつ増加させるか．
			///	</summary>
			double					Add;
			///	<summary>
			///		1ループの周期．0で終点無し．
			///	</summary>
			int						Cycle;
			///	<summary>
			///		自身が有効なTimerかどうか．falseに指定すると値の自動増加を停止する．
			///	</summary>
			bool					Enable;
			///	<summary>
			///		タイマーが停止しているかどうかを指定，取得する．
			///	</summary>
			bool					TimerStop;
			///	<summary>
			///		値の増加にフレームカウンタを使用するかどうか．
			///	</summary>
			bool					UseFrameCounter;
			///	<summary>
			///		折り返す種類．標準ではNo(折り返さない)．
			///	</summary>
			LoopType::_LoopType		LoopType;
			/// <summary>
			///		Timerの値を初期化する．
			/// </summary>
			void					Reset();
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String	ToString() const;
			/// <summary>
			///		Timerの値を値を更新せずに取得する．
			/// </summary>
			double					_GetValueNoReload() const;
		private:
			///	<summary>
			///		折り返しているかどうか．
			///	</summary>
			bool					_IsReturned;
			///	<summary>
			///		最後に呼び出された時のFC値またはカウンタ値．
			///	</summary>
			double					_LastCalledValue;
			///	<summary>
			///		タイマー更新
			///	</summary>
			void					_TimerReload(int CallTimes);
			///	<summary>
			///		繰り返し時の処理関数
			///	</summary>
			bool					_RepeatFunc();
			///	<summary>
			///		内部で保持する値．
			///	</summary>
			double					_Val;
			///	<summary>
			///		UseFrameCounterの変更検知用変数．
			///	</summary>
			bool					_BackupUseFlag;
		};

		///	<summary>
		///		doubleで座標を管理するPOINT構造体．
		///	</summary>
		class Point : public virtual Base::_ApcBase
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
			double					X;
			///	<summary>
			///		位置のY座標．
			///	</summary>
			double					Y;
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String	ToString() const;
			///	<summary>
			///		代入する．
			///	</summary>
			void					operator()(double X, double Y);
			///	<summary>
			///		コピーする．
			///	</summary>
			Point&					operator=(const Point& Pt);
			///	<summary>
			///		コピーする．
			///	</summary>
			Point&					operator=(double Val);
			///	<summary>
			///		比較する．
			///	</summary>
			bool					operator==(const Point& Pt) const;
			///	<summary>
			///		比較する．
			///	</summary>
			bool					operator!=(const Point& Pt) const;
		};

		///	<summary>
		///		開始位置と縦横幅で四角形を管理する構造体．
		///	</summary>
		class RectangleArea : public Base::_ApcBase
		{
		public:
			/// <summary>
			///		コンストラクタ．
			/// </summary>
									RectangleArea();
			/// <summary>
			///		コンストラクタ．
			/// </summary>
									RectangleArea(Value::Point &Pt, int Width, int Height);
			/// <summary>
			///		四角形の開始地点．
			/// </summary>
			Point					Location;
			/// <summary>
			///		四角形の横幅
			/// </summary>
			double					Width;
			/// <summary>
			///		四角形の縦幅
			/// </summary>
			double					Height;
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String	ToString() const;
		};

		///	<summary>
		///		doubleで四角形を管理するMargin/Padding用の構造体．
		///	</summary>
		class MarginRectangle : public Base::_ApcBase
		{
			/// <summary>
			///		プロパティの値を管理するクラス．
			/// </summary>
			class					_Property : public Base::_ApcInside
			{
			public:
				/// <summary>
				///		コンストラクタ．
				/// </summary>
									_Property(){ _Value = 0, Auto = false; }
				/// <summary>
				///		コンストラクタ．
				/// </summary>
									_Property(bool IsAuto){ _Value = 0, Auto = IsAuto; }
				/// <summary>
				///		プロパティの値を取得する．
				/// </summary>
									operator double(){ return _Value; }
				/// <summary>
				///		プロパティに値を代入する．
				/// </summary>
				double				operator=(double Val){ return _Value = Val; }
				/// <summary>
				///		プロパティに値を代入する．
				/// </summary>
				_Property&			operator=(const _Property &Val)
				{
					Auto = Val.Auto, Percent = Val.Percent, _Value = Val._Value;
					return *this;
				}
				/// <summary>
				///		プロパティと値を比較する．
				/// </summary>
				bool				operator==(const _Property &Val) const
				{
					return (Auto == Val.Auto && Percent == Val.Percent && _Value == Val._Value);
				}
				/// <summary>
				///		プロパティと値をNOT比較する．
				/// </summary>
				bool				operator!=(const _Property &Val) const{ return !(*this == Val); }
				/// <summary>
				///		プロパティを自動で指定するかどうか．
				/// </summary>
				bool				Auto;
				/// <summary>
				///		プロパティを%で指定するかどうか．
				/// </summary>
				bool				Percent;
				/// <summary>
				///		引数の値から実際の値を算出する
				/// </summary>
				double				CalclateValue(double BaseSize) const;
				/// <summary>
				///		クラスの情報を文字列で取得する．
				/// </summary>
				virtual Value::String
									ToString() const;
			private:
				/// <summary>
				///		プロパティの値．
				/// </summary>
				double				_Value;
			};
		public:
			/// <summary>
			///		コンストラクタ．
			/// </summary>
									MarginRectangle();
			/// <summary>
			///		コンストラクタ．
			/// </summary>
									MarginRectangle(double Left, double Right, double Top, double Bottom);
			/// <summary>
			///		左側の値．
			/// </summary>
			_Property				Left;
			/// <summary>
			///		右側の値．
			/// </summary>
			_Property				Right;
			/// <summary>
			///		上側の値．
			/// </summary>
			_Property				Top;
			/// <summary>
			///		下側の値．
			/// </summary>
			_Property				Bottom;
			/// <summary>
			///		値を自動指定するよう設定する際に使用する値．
			/// </summary>
			static const _Property	Auto;
			/// <summary>
			///		値を%指定するよう設定する際に使用する関数．
			/// </summary>
			static _Property		Percentage(double Percent);
			/// <summary>
			///		Rectangleクラスを比較する．
			/// </summary>
			bool					Compare(const MarginRectangle& Rc) const;
			/// <summary>
			///		自身の情報を元にRectangleを構成して返却する
			/// </summary>
			RectangleArea			CalclationArea(const RectangleArea &ArBase) const;
			/// <summary>
			///		クラスの情報を文字列で取得する．
			/// </summary>
			virtual Value::String	ToString() const;
			///	<summary>
			///		代入する．
			///	</summary>
			MarginRectangle&		operator()(double Left, double Right, double Top, double Bottom);
			///	<summary>
			///		代入する．
			///	</summary>
			MarginRectangle&		operator()(_Property Left, _Property Right, _Property Top, _Property Bottom);
			///	<summary>
			///		コピーする．
			///	</summary>
			MarginRectangle&		operator=(const MarginRectangle& Rc);
			///	<summary>
			///		同じ領域を示すか比較する．
			///	</summary>
			bool					operator==(const MarginRectangle& Rc) const;
			///	<summary>
			///		同じ領域を示していないか比較する．
			///	</summary>
			bool					operator!=(const MarginRectangle& Rc) const;
		};

		///	<summary>
		///		文字列管理クラス．
		///	</summary>
		/// <remarks>
		///		<para>このクラスは，基本的にSTLのstringと同じように使用できます．</para>
		///		<para>stringstreamのように使用することが可能になっています．</para>
		///		<para>その他，便利そうな機能を追加しています．</para>
		/// </remarks>
		class String : public Base::_ApcBase, public std::basic_string<TCHAR>
		{
			///	<summary>
			///		typedef
			///	</summary>
			typedef					std::basic_string<TCHAR>		tstring;
		public:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
									String(LPCTSTR Text = _T(""));
			///	<summary>
			///		文字列をデバッグウインドウに出力する
			///	</summary>
			void					DebugOutput() const;
			///	<summary>
			///		文字列をログファイルに出力する
			///	</summary>
			void					LogOutput() const;
			///	<summary>
			///		自身を，引数の文字列の配列を繋げたものに置き換える．
			///	</summary>
			/// <param name = "Array">
			///		繋げる対象の配列．
			/// </param>
			static String&			Connect(const std::vector<String> &Array);
			///	<summary>
			///		自身を，引数の文字列の配列を特定文字で繋げたものに置き換える．
			///	</summary>
			/// <param name = "Array">
			///		繋げる対象の配列．
			/// </param>
			/// <param name = "Cs">
			///		文字と文字を繋げる文字列．
			/// </param>
			static String&			Connect(const std::vector<String> &Array, const String &Cs);
			///	<summary>
			///		文字列の特定部分を引数で置き換えたものを返却する．
			///	</summary>
			/// <param name = "From">
			///		置き換える対象の文字列．
			/// </param>
			/// <param name = "To">
			///		置き換えた先の文字列．
			/// </param>
			String&					Replace(const String &From, const String &To) const;
			///	<summary>
			///		文字列を特定部分で区切って配列に格納したものを返却する．
			///	</summary>
			/// <param name = "Sp">
			///		区切る文字列を列挙する．
			/// </param>
			std::vector<String>&	Split(const String &Sp) const;			
			///	<summary>
			///		文字列を特定部分で区切って配列に格納したものを返却する．
			///	</summary>
			/// <param name = "Sp">
			///		区切る文字列を列挙する．
			/// </param>
			/// <param name = "IsSpaceAble">
			///		空白の配列を返却するかどうかを指定する．
			/// </param>
			std::vector<String>&	Split(const String &Sp, bool IsSpaceAble) const;			
			///	<summary>
			///		operator LPCTSTR.
			///	</summary>
									operator LPCTSTR() const;
			///	<summary>
			///		文字列を代入する．
			///	</summary>
			String&					operator=(tstring Val);
			///	<summary>
			///		文字列を代入する．
			///	</summary>
			String&					operator=(LPCTSTR Val);
			///	<summary>
			///		文字列を比較する．
			///	</summary>
			bool					operator==(String &Str) const;
			///	<summary>
			///		文字列をNOT比較する．
			///	</summary>
			bool					operator!=(String &Str) const;
			///	<summary>
			///		文字列にboolを流す．
			///	</summary>
			String&					operator<<(const bool Val);
			///	<summary>
			///		文字列にintを流す．
			///	</summary>
			String&					operator<<(const int Val);
			///	<summary>
			///		文字列にUINTを流す．
			///	</summary>
			String&					operator<<(const UINT Val);
			///	<summary>
			///		文字列にshortを流す．
			///	</summary>
			String&					operator<<(const short Val);
			///	<summary>
			///		文字列にUSHORTを流す．
			///	</summary>
			String&					operator<<(const USHORT Val);
			///	<summary>
			///		文字列にlongを流す．
			///	</summary>
			String&					operator<<(const long Val);
			///	<summary>
			///		文字列にULONGを流す．
			///	</summary>
			String&					operator<<(const ULONG Val);
			///	<summary>
			///		文字列にdoubleを流す．
			///	</summary>
			String&					operator<<(const double Val);
			///	<summary>
			///		文字列にPointerを流す．
			///	</summary>
			String&					operator<<(const void *Val);
			///	<summary>
			///		文字列にTCHARを流す．
			///	</summary>
			String&					operator<<(const TCHAR Val);
			///	<summary>
			///		文字列にLPCTSTRを流す．
			///	</summary>
			String&					operator<<(const LPCTSTR Val);
			///	<summary>
			///		文字列にStringを流す．
			///	</summary>
			String&					operator<<(const String& Val);
			///	<summary>
			///		文字列にPointを流す．
			///	</summary>
			String&					operator<<(const Point& Val);
			template<typename Type>
			///	<summary>
			///		文字列を指定した型に変換する．
			///	</summary>  
			Type					ToValue() const
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
			String&					FromValue(Type Val);
		};
	}
}