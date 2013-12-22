// --------------------------------------------------------
//	apcCollection.h
// --------------------------------------------------------
//	いろいろ管理したり収集したりするクラスを作成する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <list>
#include <set>
#include <include/apcClassBase.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Collection)
// --------------------------------------------------------
namespace Apocalypse
{
	// ------------------------------------------------
	//	Front Declaration
	// ------------------------------------------------
	namespace Draw
	{
		class __FrameBase;
		class EdgeFrame;
	}
	namespace Sequence
	{
		class Sequencer;
	}

	// ----------------------------------------------------
	//	Collection名前空間内のクラスを記載
	// ----------------------------------------------------
	namespace Collection
	{
		///	<summary>
		///		フレームを管理する用のクラス．
		///	</summary>
		/// <remarks>
		///		<para>このクラスによってフレームは自動収集・描画されます．</para>
		///		<para>このクラスはsingletonです．</para>
		/// </remarks>
		class __FrameCollection : virtual public Template::__Singleton<__FrameCollection>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<__FrameCollection>;
		public:
			///	<summary>
			///		指定したフレームを追加する．
			///	</summary>
			/// <param name = "ResetFlag">
			///		追加する対象のフレーム．
			/// </param>
			void				Insert(const std::shared_ptr<Draw::__FrameBase> &Target);
			///	<summary>
			///		現在一覧に登録されているフレームを列挙する．
			///	</summary>
			/// <param name = "ResetFlag">
			///		true
			///		<para>最初から列挙を開始する．</para>
			///		false
			///		<para>前回の途中から列挙を続ける．</para>
			/// </param>
			std::shared_ptr<Draw::__FrameBase>	
								Enum(bool ResetFlag) const;
			///	<summary>
			///		指定したフレームを除外する．
			///	</summary>
			/// <param name = "Target">
			///		除外する対象のフレーム．NULLを指定した場合すべて削除される．
			/// </param>
			void				Erase(const std::shared_ptr<Draw::__FrameBase> &Target);
			///	<summary>
			///		コンテナ内のフレームを全て削除する．
			///	</summary>
			void				Clear();
			///	<summary>
			///		すべてのフレームを描画する．
			///	</summary>
			void				DrawAll() const;
		private:
			///	<summary>
			///		コンストラクタ
			///	</summary>
								__FrameCollection();
			///	<summary>
			///		ソート用のクラス．setコンテナ内の要素をソートする用に使用する．
			///	</summary>
			class				_Sort
			{
			public:
				bool			operator()(const std::shared_ptr<Draw::__FrameBase> &A, const std::shared_ptr<Draw::__FrameBase> &B);
			};
			/// <summary>
			///		親フレームのα値の割合を取得する．
			///		親フレームのαがすべて255の場合に1.0が返る．
			/// </summary>
			/// <param name = "Target">
			///		α値割合を調べる対象のフレーム．
			/// </param>
			double				_GetParentAlphaParcent(const std::shared_ptr<Draw::__FrameBase> &Target) const;
			/// <summary>
			///		親フレームのZ座標の合計値を取得する関数．
			/// </summary>
			/// <param name = "Target">
			///		Z座標を調べる対象のフレーム．
			/// </param>
			unsigned int		_GetParentZindex(const std::shared_ptr<Draw::__FrameBase> &Target) const;
			///	<summary>
			///		親フレームに無効フレームがあるかどうかを調べる．
			///	</summary>
			/// <param name = "Target">
			///		Enableを調べる対象のフレーム．
			/// </param>
			bool				_EnableParent(const std::shared_ptr<Draw::__FrameBase> &Target) const;
			///	<summary>
			///		最上位のフレーム．
			///	</summary>
			std::shared_ptr<Draw::EdgeFrame>
								_TopParent;
			///	<summary>
			///		フレームを管理するためのコンテナ
			///	</summary>
			std::multiset<std::shared_ptr<Draw::__FrameBase>, __FrameCollection::_Sort>
								_Container;
		};

		///	<summary>
		///		現在のシーケンスを管理する用のクラス．
		///	</summary>
		/// <remarks>
		///		<para>このクラスによってシーケンスは管理されます．</para>
		///		<para>このクラスはsingletonです．</para>
		/// </remarks>
		class __SequenceCollection : virtual public Template::__Singleton<__SequenceCollection>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<__SequenceCollection>;
		public:
			///	<summary>
			///		指定したシーケンスを末尾に追加する．
			///	</summary>
			void				Add(const std::shared_ptr<Sequence::Sequencer> &Target);
			///	<summary>
			///		最上位のシーケンスを取り出す．
			///	</summary>
			std::shared_ptr<Sequence::Sequencer>
								Top() const;
			///	<summary>
			///		指定したシーケンスまでのすべてのシーケンスを削除する．
			///	</summary>
			void				Delete(const Sequence::Sequencer *Target);
		private:
			///	<summary>
			///		コンストラクタ
			///	</summary>
								__SequenceCollection(){}
			///	<summary>
			///		シーケンスを管理するための単方向コンテナ．
			///	</summary>
			std::list<std::shared_ptr<Sequence::Sequencer>>
								_Container;
		};

		///	<summary>
		///		起動してからのフレーム数を取得する．単純増加するカウンタとしても使用可能．
		///	</summary>
		/// <remarks>
		///		このクラスはsingletonです．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// 現在のカウンタ値を取得する
		///		int Counter = FrameCounter::GetCount();
		///		</code>
		/// </example>
		class __FrameCounter : virtual public Template::__Singleton<__FrameCounter>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<__FrameCounter>;
		public:
			/// <summary>
			///		カウント数を取得する関数．
			/// </summary>
			static UINT			GetCount();
			/// <summary>
			///		カウント数を増加させる関数．1フレームに一度だけ呼ぶ．
			/// </summary>
			void				_CountAdd();
		private:
			/// <summary>
			///		Countructor．
			/// </summary>
								__FrameCounter();
			/// <summary>
			///		カウント数を保存しておく変数．
			/// </summary>
			unsigned int		_Value;
		};
	}
}

