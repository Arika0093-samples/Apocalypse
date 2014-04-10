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
		class _FrameBase;
		class PanelFrame;
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
		class _FrameCollection :  public Template::_Singleton<_FrameCollection>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::_Singleton<_FrameCollection>;
		public:
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~_FrameCollection();
			/// <summary>
			///		_FrameBaseのshared_ptrをtypedefで省略
			/// </summary>
			typedef				Draw::_FrameBase*		FramePtr;
			/// <summary>
			///		_FrameBaseのshared_ptrを管理するvectorをtypedefで省略
			/// </summary>
			typedef				std::vector<FramePtr>*	FrameListPtr;
			/// <summary>
			///		const _FrameCollection::FramePtr&を引数にとりboolを返却するfunctionをtypedefで省略
			/// </summary>
			typedef				boost::function<bool(const FramePtr&)>	CheckFunc;
			///	<summary>
			///		指定したフレームを追加する．
			///	</summary>
			/// <param name = "Target">
			///		追加する対象のフレーム．
			/// </param>
			void				Insert(Draw::_FrameBase *Target);
			///	<summary>
			///		現在一覧に登録されているフレームをvectorコンテナで返却する．
			///	</summary>
			FrameListPtr		Enum() const;
			///	<summary>
			///		現在一覧に登録されているフレームのうち，条件式と一致する項目をvectorコンテナで返却する．
			///	</summary>
			/// <param name = "Func">
			///		const _FrameCollection::FramePtrを引数にとりboolを返す関数．true返却で一致と判断する．
			/// </param>
			FrameListPtr		Enum(CheckFunc Func) const;
			///	<summary>
			///		指定したフレームを除外する．
			///	</summary>
			/// <param name = "Target">
			///		除外する対象のフレーム．NULLを指定した場合すべて削除される．
			/// </param>
			void				Erase(const Draw::_FrameBase *Target);
			///	<summary>
			///		指定した条件と一致するフレームのうち始めの一つを取得する．
			///	</summary>
			/// <param name = "Func">
			///		const _FrameCollection::FramePtrを引数にとりboolを返す関数．true返却で一致と判断する．
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
			Draw::PanelFrame*	GetTopParent() const;
		private:
			///	<summary>
			///		コンストラクタ
			///	</summary>
								_FrameCollection();
			///	<summary>
			///		ソート用のクラス．setコンテナ内の要素をソートする用に使用する．
			///	</summary>
			class				_Sort
			{
			public:
				bool			operator()(const Draw::_FrameBase *A, const Draw::_FrameBase *B);
			};
			/// <summary>
			///		親フレームのZ座標の合計値を指定する関数．
			/// </summary>
			/// <param name = "Target">
			///		Z座標を指定する対象のフレーム．
			/// </param>
			void				_SetZindex(Draw::_FrameBase *Target) const;
			///	<summary>
			///		親フレームに無効フレームがあるかどうかを調べる．
			///	</summary>
			/// <param name = "Target">
			///		Enableを調べる対象のフレーム．
			/// </param>
			bool				_EnableParent(const Draw::_FrameBase *Target) const;
			///	<summary>
			///		最上位のフレーム．
			///	</summary>
			Draw::PanelFrame*	_TopParent;
			///	<summary>
			///		フレームを管理するためのコンテナ
			///	</summary>
			std::list<Draw::_FrameBase*>
								_Container;
		};

		///	<summary>
		///		現在のシーケンスを管理する用のクラス．
		///	</summary>
		/// <remarks>
		///		<para>このクラスによってシーケンスは管理されます．</para>
		///		<para>このクラスはsingletonです．</para>
		/// </remarks>
		class _SequenceCollection : public Template::_Singleton<_SequenceCollection>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::_Singleton<_SequenceCollection>;
		public:
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~_SequenceCollection();
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
								_SequenceCollection(){}
			///	<summary>
			///		シーケンスを管理するための単方向コンテナ．
			///	</summary>
			std::list<std::shared_ptr<Sequence::Sequencer>>
								_Container;
		};
	}
}