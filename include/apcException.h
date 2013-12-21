// --------------------------------------------------------
//	apcException.h
// --------------------------------------------------------
//	例外クラスを定義する。
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <include/apcClassBase.h>

// --------------------------------------------------------
//	defineマクロを使用する
// --------------------------------------------------------
//	例外を放つマクロ
#define ThrowException(Str)			\
			throw new ApcException(_T(__FILE__), __LINE__, Apocalypse::Base::StrOut << Str)

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Exception)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Exception
	{
		///	<summary>
		///		Apocalypseの例外クラス。
		///	</summary>
		/// <remarks>
		///		この例外クラスは、例外が発生したファイル名・行番号・エラーの詳細を
		///		保存して、その結果をMessageBoxに表示することができます。<br />
		///		Exception()マクロを使用するとファイル名と行番号を省くことができます。
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		Exception("ApcException例外をマクロを使用して発生させます。");
		///		</code>
		/// </example>
		class ApcException : virtual public Base::ApcBase
		{
		public:
			///	<summary>
			///		例外発生時に投げるクラス（文字列版）。Exceptionマクロを使用すると
			///		ファイル名と行番号を省ける。
			///	</summary>
			/// <param name = "fName">
			///		例外が発生した箇所のファイルの名前。__FILE__マクロを使用する。
			/// </param>
			/// <param name = "Line">
			///		例外が発生した箇所のファイルの行番号。__LINE__マクロを使用する。
			/// </param>
			/// <param name = "Str">
			///		エラーメッセージに表示させる内容。printfと同様に使用出来る。
			/// </param>
								ApcException(Base::String fName, int Line, Base::String Str);
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~ApcException(){}
			///	<summary>
			///		例外情報を表示する。
			///	</summary>
			void				ShowMessage() const;
		private:
			///	<summary>
			///		例外が発生したファイルの名前
			///	</summary>
			Base::String		ExcFileName;
			///	<summary>
			///		例外が発生したファイルの行数
			///	</summary>
			int					ExcLine;
			///	<summary>
			///		例外時のコメントなど
			///	</summary>
			Base::String		ExcString;
		};
	}
}
