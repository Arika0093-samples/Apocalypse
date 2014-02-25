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
#include <vector>
#include <list>
#include <boost/foreach.hpp>
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
		class __FrameCollection :  public Template::__Singleton<__FrameCollection>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<__FrameCollection>;
		public:
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~__FrameCollection();
			/// <summary>
			///		__FrameBaseのshared_ptrをtypedefで省略
			/// </summary>
			typedef				Draw::__FrameBase*		FramePtr;
			/// <summary>
			///		__FrameBaseのshared_ptrを管理するvectorをtypedefで省略
			/// </summary>
			typedef				std::vector<FramePtr>*	FrameListPtr;
			/// <summary>
			///		const __FrameCollection::FramePtr&を引数にとりboolを返却するfunctionをtypedefで省略
			/// </summary>
			typedef				boost::function<bool(const FramePtr&)>	CheckFunc;
			///	<summary>
			///		指定したフレームを追加する．
			///	</summary>
			/// <param name = "Target">
			///		追加する対象のフレーム．
			/// </param>
			void				Insert(Draw::__FrameBase *Target);
			///	<summary>
			///		現在一覧に登録されているフレームをvectorコンテナで返却する．
			///	</summary>
			FrameListPtr		Enum() const;
			///	<summary>
			///		現在一覧に登録されているフレームのうち，条件式と一致する項目をvectorコンテナで返却する．
			///	</summary>
			/// <param name = "Func">
			///		const __FrameCollection::FramePtrを引数にとりboolを返す関数．true返却で一致と判断する．
			/// </param>
			FrameListPtr		Enum(CheckFunc Func) const;
			///	<summary>
			///		指定したフレームを除外する．
			///	</summary>
			/// <param name = "Target">
			///		除外する対象のフレーム．NULLを指定した場合すべて削除される．
			/// </param>
			void				Erase(const Draw::__FrameBase *Target);
			///	<summary>
			///		指定した条件と一致するフレームのうち始めの一つを取得する．
			///	</summary>
			/// <param name = "Func">
			///		const __FrameCollection::FramePtrを引数にとりboolを返す関数．true返却で一致と判断する．
			/// </param>
			FramePtr			Find(CheckFunc Func) const;
			///	<summary>
			///		コンテナ内のフレームをZオーダー順に並び替える．
			///	</summary>
			void				Sort();
			///	<summary>
			///		コンテナ内のフレームを全て削除する．
			///	</summary>
			void				Clear();
			///	<summary>
			///		すべてのフレームを描画する．
			///	</summary>
			void				DrawAll() const;
			///	<summary>
			///		最上位フレームを取得する
			///	</summary>
			Draw::EdgeFrame*	GetTopParent() const;
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
				bool			operator()(const Draw::__FrameBase *A, const Draw::__FrameBase *B);
			};
			/// <summary>
			///		親フレームのZ座標の合計値を指定する関数．
			/// </summary>
			/// <param name = "Target">
			///		Z座標を指定する対象のフレーム．
			/// </param>
			void				_SetZindex(Draw::__FrameBase *Target) const;
			///	<summary>
			///		親フレームに無効フレームがあるかどうかを調べる．
			///	</summary>
			/// <param name = "Target">
			///		Enableを調べる対象のフレーム．
			/// </param>
			bool				_EnableParent(const Draw::__FrameBase *Target) const;
			///	<summary>
			///		最上位のフレーム．
			///	</summary>
			Draw::EdgeFrame*	_TopParent;
			///	<summary>
			///		フレームを管理するためのコンテナ
			///	</summary>
			std::list<Draw::__FrameBase*>
								_Container;
		};

		///	<summary>
		///		現在のシーケンスを管理する用のクラス．
		///	</summary>
		/// <remarks>
		///		<para>このクラスによってシーケンスは管理されます．</para>
		///		<para>このクラスはsingletonです．</para>
		/// </remarks>
		class __SequenceCollection : public Template::__Singleton<__SequenceCollection>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<__SequenceCollection>;
		public:
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~__SequenceCollection();
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
			///	<summary>
			///		現在のシーケンスの個数を取得する
			///	</summary>
			unsigned int		Size() const;
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
		class __FrameCounter : public Template::__Singleton<__FrameCounter>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<__FrameCounter>;
		public:
			/// <summary>
			///		カウント数を取得する関数．
			/// </summary>
			static double		GetCount();
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
			double				_Value;
		};
	}
}