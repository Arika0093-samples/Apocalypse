// --------------------------------------------------------
//	apcClassBase.h
// --------------------------------------------------------
//	Apocalypseの全クラスの基盤となるクラスを作成する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <Windows.h>
#include <tchar.h>
#include <sstream>
#include <boost/typeof/typeof.hpp>

// --------------------------------------------------------
//	名前空間を使用
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Base
	{
		// -----------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class String;

		///	<summary>
		///		Apocalypse内のユーザーが使用する全クラス（定数列挙クラスを除く）の継承元．
		///	</summary>
		class __ApcBase
		{
		protected:
			///	<summary>
			///		コンストラクタ
			///	</summary>
								__ApcBase(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~__ApcBase(){}
		};

		///	<summary>
		///		Apocalypse内の定数などを列挙したクラスの継承元．
		///	</summary>
		class __ApcEnumeration
		{
		protected:
			///	<summary>
			///		コンストラクタ
			///	</summary>
								__ApcEnumeration(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~__ApcEnumeration(){}
		};

		///	<summary>
		///		内部で使用するクラスの継承元．
		///	</summary>
		class __ApcInside
		{
		protected:
			///	<summary>
			///		コンストラクタ
			///	</summary>
								__ApcInside(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~__ApcInside(){}
		};

		///	<summary>
		///		小数点の値を管理するPOINT構造体．
		///	</summary>
		class Point : public __ApcBase
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
			///		足す．
			///	</summary>
			Point&				operator+(Point& Pt);
			///	<summary>
			///		足す．
			///	</summary>
			Point&				operator+(double Val);
			///	<summary>
			///		引く．
			///	</summary>
			Point&				operator-(Point& Pt);
			///	<summary>
			///		引く．
			///	</summary>
			Point&				operator-(double Val);
			///	<summary>
			///		掛ける．
			///	</summary>
			Point&				operator*(Point& Pt);
			///	<summary>
			///		掛ける．
			///	</summary>
			Point&				operator*(double Val);
			///	<summary>
			///		割る．
			///	</summary>
			Point&				operator/(Point& Pt);
			///	<summary>
			///		割る．
			///	</summary>
			Point&				operator/(double Val);
			///	<summary>
			///		足す．
			///	</summary>
			Point&				operator+=(Point& Pt);
			///	<summary>
			///		足す．
			///	</summary>
			Point&				operator+=(double Val);
			///	<summary>
			///		引く．
			///	</summary>
			Point&				operator-=(Point& Pt);
			///	<summary>
			///		引く．
			///	</summary>
			Point&				operator-=(double Val);
			///	<summary>
			///		掛ける．
			///	</summary>
			Point&				operator*=(Point& Pt);
			///	<summary>
			///		掛ける．
			///	</summary>
			Point&				operator*=(double Val);
			///	<summary>
			///		割る．
			///	</summary>
			Point&				operator/=(Point& Pt);
			///	<summary>
			///		割る．
			///	</summary>
			Point&				operator/=(double Val);
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
		/// <example>
		///		使用例: 
		///		<code>
		///		// String()クラスに数字の4.12を流してMessageBoxで出力
		///		String str;
		///		str << 4.12;
		///		MessageBox(NULL, str, _T(""), ID_OK);
		///		// Stringクラスが先頭に来ない場面または引数上で<<を使用する場合はString()を使用する．
		///		str = String() << _T("1+1=: ") << (1+1);
		///		MessageBox(NULL, (String() << _T("Value: ") << 6.132), _T(""), ID_OK);
		///		</code>
		/// </example>
		class String : public virtual __ApcBase, public std::basic_string<TCHAR>
		{
			typedef				std::basic_string<TCHAR> tstring;
		public:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								String(LPCTSTR Text = _T(""));
			///	<summary>
			///		文字列をMessageBoxで表示する
			///	</summary>
			void				Message() const;
			///	<summary>
			///		文字列を指定した型に変換する．
			///	</summary>
			template<typename Type>
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
			///	<summary>
			///		operator LPCTSTR.
			///	</summary>
								operator LPCTSTR() const;
			///	<summary>
			///		文字列を代入する．
			///	</summary>
			String&				operator=(LPCTSTR Val);
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
			///		文字列にTCHARを流す．
			///	</summary>
			String&				operator<<(const TCHAR Val);
			///	<summary>
			///		文字列にLPCTSTRを流す．
			///	</summary>
			String&				operator<<(LPCTSTR Val);
			///	<summary>
			///		文字列にStringを流す．
			///	</summary>
			String&				operator<<(const String& Val);
		private:
			template<typename Type>
			String&				FromValue(Type Val);
		};
	}
}