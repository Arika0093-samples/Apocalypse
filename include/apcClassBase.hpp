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

	// ----------------------------------------------------
	//	Base名前空間内のクラスを記載
	// ----------------------------------------------------
	namespace Base
	{
		///	<summary>
		///		Apocalypse内のユーザーが使用する全クラス（定数列挙クラスを除く）の継承元．
		///	</summary>
		class _ApcBase
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
									_ApcBase(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual					~_ApcBase(){}
		};

		///	<summary>
		///		Apocalypse内の定数などを列挙したクラスの継承元．
		///	</summary>
		class _ApcEnumeration
		{
		protected:
			///	<summary>
			///		コンストラクタ
			///	</summary>
									_ApcEnumeration(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual					~_ApcEnumeration(){}
		};

		///	<summary>
		///		内部で使用するクラスの継承元．
		///	</summary>
		class _ApcInside
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
									_ApcInside(){}
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual					~_ApcInside(){}
		};
	}
}