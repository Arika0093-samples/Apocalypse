// --------------------------------------------------------
//	apcTemplate.h
// --------------------------------------------------------
//	テンプレートクラスを定義するファイル．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <include/apcClassBase.hpp>

// --------------------------------------------------------
//	名前空間を使用
// --------------------------------------------------------
namespace Apocalypse
{
	// ----------------------------------------------------
	//	Template名前空間内のクラスを記載
	// ----------------------------------------------------
	namespace Template
	{
		template <class T>
		///	<summary>
		///		<para>Singletonクラスを実装する際に使用するクラスのテンプレート．</para>
		///		<para>継承する形で使用する．</para>
		///	</summary>
		class __Singleton : public virtual Base::__ApcBase
		{
		public:
			/// <summary>
			///		実体を取得する
			/// </summary>
			static T&			GetInstance()
			{
				static T Instance;
				return Instance;
			}
		protected:
			/// <summary>
			///		コンストラクタ
			/// </summary>
								__Singleton(){}
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual				~__Singleton(){}
			/// <summary>
			///		コピーコンストラクタ
			/// </summary>
								__Singleton(const __Singleton& r){}
			/// <summary>
			///		代入演算子
			/// </summary>
			void*				operator=(const __Singleton& r){}
		};
	}
}