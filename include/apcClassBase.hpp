// --------------------------------------------------------
//	apcClassBase.h
// --------------------------------------------------------
//	Apocalypseの全クラスの基盤となるクラスを作成する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	名前空間を使用
// --------------------------------------------------------
namespace Apocalypse
{
	// -----------------------------------------------
	//	Front Declaration
	// ------------------------------------------------
	namespace Value
	{
		class String;
	}

	namespace Base
	{
		///	<summary>
		///		Apocalypse内のユーザーが使用する全クラス（定数列挙クラスを除く）の継承元．
		///	</summary>
		class __ApcBase
		{
		public:
			///	<summary>
			///		クラスの情報を文字列で得る．
			///	</summary>
			virtual Value::String	ToString() const;
		protected:
			///	<summary>
			///		コンストラクタ
			///	</summary>
									__ApcBase(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual					~__ApcBase(){}
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
			virtual					~__ApcEnumeration(){}
		};

		///	<summary>
		///		内部で使用するクラスの継承元．
		///	</summary>
		class __ApcInside
		{
		public:
			///	<summary>
			///		クラスの情報を文字列で得る．
			///	</summary>
			virtual Value::String	ToString() const;
		protected:
			///	<summary>
			///		コンストラクタ
			///	</summary>
									__ApcInside(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual					~__ApcInside(){}
		};
	}
}