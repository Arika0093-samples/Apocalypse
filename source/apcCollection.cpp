// --------------------------------------------------------
//	apcCollection.cpp
// --------------------------------------------------------
//	apcCollection.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	FrameCollection
// ----------------------------------------------------
//	FrameCollection::FrameCollection (Constructor)
// ----------------------------------------------------
				__FrameCollection::__FrameCollection()
{
	// 最上位フレームを作成する
	_TopParent = new EdgeFrame();
	// 横幅と縦幅を指定する
	_TopParent->Width	= ApplicationConfig::Width;
	_TopParent->Height	= ApplicationConfig::Height;
	// ％指定を無効にする．
	_TopParent->SpecifyWithParcent = false;
}

// ----------------------------------------------------
//	FrameCollection::~FrameCollection (Destructor)
// ----------------------------------------------------
				__FrameCollection::~__FrameCollection()
{
	// 全削除
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Insert
// ----------------------------------------------------
void			__FrameCollection::Insert(__FrameBase *Target)
{
	// もしNULLフレームが渡されたら
	if(!Target){
		// 何もしない
		return;
	}
	// 挿入する
	_Container.insert(Target);
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
__FrameCollection::FrameListPtr	
				__FrameCollection::Enum() const
{
	// 引数あり版を呼び出す
	return Enum([](const FramePtr){ return true; });
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
__FrameCollection::FrameListPtr	
				__FrameCollection::Enum(__FrameCollection::CheckFunc Func) const
{
	// 返却する一覧を用意
	auto FVector = new std::vector<FramePtr>();
	// イテレータを取得
	auto Iter = _Container.begin();
	// ------------------------------------------------
	// 終端まで全て確認
	while(Iter != _Container.end()){
		// 取得
		auto Ptr = *Iter;
		// 1つ進める
		Iter++;
		// もし関数の結果がfalseなら
		if(!Func(Ptr)){
			// 再度呼び出す
			continue;
		}
		// もし親フレームが指定されていなければ
		if(Ptr->Parent && Ptr != _TopParent){
			// 親フレームをTopParentに指定する
			Ptr->Parent = _TopParent;
		}
		// vectorに追加
		FVector->push_back(Ptr);
	}
	// 返却
	return FVector;
}

// ----------------------------------------------------
//	FrameCollection::Erase
// ----------------------------------------------------
void			__FrameCollection::Erase(const __FrameBase *Target)
{
	// もし引数に無効ポインタまたは最上位フレームを渡されたら
	if(!Target || Target == _TopParent){
		// 何もしない
		return;
	}
	// 引数のフレームを親に持つフレームを取得する
	auto List = Enum([Target](const FramePtr Pr){return(Pr->Parent == Target);});
	// 順番に見る
	BOOST_FOREACH(auto Ptr, *List){
		// 親フレームを取得
		auto ParentPtr = Ptr->Parent;
		// 親フレームを書き換える
		Ptr->Parent = ParentPtr->Parent;
	}
	// 取得する
	auto ErasePtr = Find([Target](const FramePtr Pr){return Pr == Target;});
	// もし削除する対象が存在するなら
	if(ErasePtr){
		// 順番に見る
		auto Iter = _Container.begin();
		for(; Iter != _Container.end(); Iter++){
			if((*Iter) == Target){
				break;
			}
		}
		// 指定されたフレームをコンテナから削除する
		_Container.erase(Iter);
	}
	// 終了
	return;
}

// ----------------------------------------------------
//	FrameCollection::Find
// ----------------------------------------------------
__FrameCollection::FramePtr
				__FrameCollection::Find(__FrameCollection::CheckFunc Func) const
{
	// 取得
	auto Vector = *Enum(Func);
	// もし取得した結果がemptyならNULLを返却
	if(Vector.empty()){ return NULL; }
	// 最初の項目を返却
	return Vector[0];
}

// ----------------------------------------------------
//	FrameCollection::Clear
// ----------------------------------------------------
void			__FrameCollection::Clear()
{
	// 全て削除する．
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Sort
// ----------------------------------------------------
bool			__FrameCollection::_Sort::operator()(const __FrameBase *A, const __FrameBase *B)
{
	// Z座標を比較する．この際Z座標が0なら標準値を使用する
	return	(A->DrawOrder != 0 ? A->DrawOrder : __FrameCollection::GetInstance()._GetParentZindex(A))
		>	(B->DrawOrder != 0 ? B->DrawOrder : __FrameCollection::GetInstance()._GetParentZindex(B));
}

// ----------------------------------------------------
//	FrameCollection::DrawAll
// ----------------------------------------------------
void			__FrameCollection::DrawAll() const
{
	// 一覧を取得する(Visibleがtrueかつ親にEnable=falseが存在しない)
	auto List = Enum([this](const FramePtr &Val){ return (Val->Visible && _EnableParent(Val)); });
	// 列挙する
	BOOST_FOREACH(auto Ptr, *List){
		// 横幅・縦幅の標準値を取得
		Ptr->_SetProperties();
		// 位置をリセットする
		Ptr->_SetDefaultPosition();
		// 描画モードを指定する
		SetDrawMode(Ptr->DrawMode);
		// 取得したフレームの描画関数を実行する
		Ptr->_DrawThisFrame();
	}
}

// ----------------------------------------------------
//	FrameCollection::GetTopParent
// ----------------------------------------------------
EdgeFrame*		__FrameCollection::GetTopParent() const
{
	return _TopParent;
}

// ----------------------------------------------------
//	FrameBase::GetParentZindex
// ----------------------------------------------------
unsigned int	__FrameCollection::_GetParentZindex(const __FrameBase *Tgt) const
{
	// もし無効なら
	if(!Tgt){
		// 1を返す
		return 1.00;
	}
	// 自身の親フレームのZ座標+自身のZ座標を返却
	return (Tgt->DrawOrder + _GetParentZindex(Tgt->Parent));
}

// ----------------------------------------------------
//	FrameCollection::EnableParent
// ----------------------------------------------------
bool			__FrameCollection::_EnableParent(const __FrameBase *Tgt) const
{
	// もし無効なら
	if(!Tgt || !Tgt->Enable){
		// 親がないならtrue，自身が無効ならfalseを返す
		return !Tgt;
	}
	// 親でも同じ関数を実行
	return _EnableParent(Tgt->Parent);
}

// ----------------------------------------------------
//	SequenceCollection
// ----------------------------------------------------
//	SequenceCollection::~SequenceCollection (Destructor)
// ----------------------------------------------------
				__SequenceCollection::~__SequenceCollection()
{
	// 全削除
	_Container.clear();
}

// ----------------------------------------------------
//	SequenceCollection::Add
// ----------------------------------------------------
void			__SequenceCollection::Add(const std::shared_ptr<Sequencer> &Target)
{
	// もしNULLなら
	if(!Target){
		// 何もしない
		return;
	}
	// コンテナの末尾に追加する
	_Container.push_back(Target);
}

// ----------------------------------------------------
//	SequenceCollection::Delete
// ----------------------------------------------------
std::shared_ptr<Sequencer>
				__SequenceCollection::Top() const
{
	// もしスタックが空なら
	if(_Container.empty()){
		// NULLを返す
		return NULL;
	}
	// スタックの一番上を返す
	return _Container.back();
}

// ----------------------------------------------------
//	SequenceCollection::Delete
// ----------------------------------------------------
void			__SequenceCollection::Delete(const Sequencer *Target)
{
	// 保存用
	std::shared_ptr<Sequencer> TopFrame;
	// もしNULLなら
	if(!Target || !Top()){
		// 何もしない
		return;
	}
	// 引数のシーケンスになるまで続ける
	while( TopFrame = Top() ){
		// 末尾要素を削除する
		_Container.pop_back();
		// もし一致したならば
		if(TopFrame.get() == Target){
			// 終わる
			break;
		}
	};
}

// ----------------------------------------------------
//	FrameCounter
// ----------------------------------------------------
//	FrameCounter::FrameCounter
// ----------------------------------------------------
				__FrameCounter::__FrameCounter()
{
	// 値を初期化する
	_Value = 0;
	// 終了
	return;
}

// ----------------------------------------------------
//	FrameCounter::GetCount
// ----------------------------------------------------
double			__FrameCounter::GetCount()
{
	// 返却する
	return GetInstance()._Value;
}

// ----------------------------------------------------
//	FrameCounter::CountAdd
// ----------------------------------------------------
void			__FrameCounter::_CountAdd()
{
	// 値を1増加する
	_Value++;
}
