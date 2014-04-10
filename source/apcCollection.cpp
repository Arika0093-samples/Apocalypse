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
				_FrameCollection::_FrameCollection()
{
	// 最上位フレームを作成する
	_TopParent = new PanelFrame();
	// Marginを指定する
	_TopParent->Margin(0, 0, 0, 0);
}

// ----------------------------------------------------
//	FrameCollection::~FrameCollection (Destructor)
// ----------------------------------------------------
				_FrameCollection::~_FrameCollection()
{
	// 全削除
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Insert
// ----------------------------------------------------
void			_FrameCollection::Insert(_FrameBase *Target)
{
	// もしNULLフレームが渡されたら
	if(!Target){
		// 何もしない
		return;
	}
	// 挿入する
	_Container.push_back(Target);
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
_FrameCollection::FrameListPtr	
				_FrameCollection::Enum() const
{
	// 引数あり版を呼び出す
	return Enum([](const FramePtr){ return true; });
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
_FrameCollection::FrameListPtr	
				_FrameCollection::Enum(_FrameCollection::CheckFunc Func) const
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
		if(!Ptr->Parent && Ptr != _TopParent){
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
void			_FrameCollection::Erase(const _FrameBase *Target)
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
_FrameCollection::FramePtr
				_FrameCollection::Find(_FrameCollection::CheckFunc Func) const
{
	// 取得
	auto Vector = *Enum(Func);
	// もし取得した結果がemptyならNULLを返却
	if(Vector.empty()){ return NULL; }
	// 最初の項目を返却
	return Vector[0];
}

// ----------------------------------------------------
//	FrameCollection::Sort
// ----------------------------------------------------
void			_FrameCollection::Sort()
{
	// 全フレームに対して，DrawOrderを適切なものに変更する
	for(auto Iter = _Container.begin(); Iter != _Container.end(); Iter++){
		// 親を考慮して並び替える
		_FrameCollection::GetInstance()._SetZindex(*Iter);
	}
	// 並び順を変える
	_Container.sort(_Sort());
}

// ----------------------------------------------------
//	FrameCollection::Clear
// ----------------------------------------------------
void			_FrameCollection::Clear()
{
	// 全て削除する．
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Sort
// ----------------------------------------------------
bool			_FrameCollection::_Sort::operator()(const _FrameBase *A, const _FrameBase *B)
{
	// Z座標を比較する．
	return A->DrawOrder < B->DrawOrder;
}

// ----------------------------------------------------
//	FrameCollection::DrawAll
// ----------------------------------------------------
void			_FrameCollection::DrawAll() const
{
	// 一覧を取得する(Visibleがtrueかつ親にEnable=falseが存在しない)
	auto List = Enum([this](const FramePtr &Val){ return (Val->Visible && _EnableParent(Val)); });
	// 列挙する
	BOOST_FOREACH(auto Ptr, *List){
		// 横幅・縦幅の標準値を取得
  		Ptr->_SetProperties();
		// 描画モードを指定する
		SetDrawMode(Ptr->DrawMode);
		// 描画領域を取得する
		RectangleArea Rect = Ptr->GetActualArea();
		// 枠内領域に描画する設定なら有効にする
		if(Ptr->DrawFramework){
			SetDrawArea(Rect.Location.X, Rect.Location.Y,
				Rect.Location.X + Rect.Width, Rect.Location.Y + Rect.Height);
		}
		// 全領域に描画する設定なら初期化する
		else {
			SetDrawAreaFull();
		}
		// 取得したフレームの描画関数を実行する
		Ptr->_DrawThisFrame(Rect);
	}
}

// ----------------------------------------------------
//	FrameCollection::GetTopParent
// ----------------------------------------------------
PanelFrame*		_FrameCollection::GetTopParent() const
{
	return _TopParent;
}

// ----------------------------------------------------
//	FrameBase::SetZindex
// ----------------------------------------------------
void			_FrameCollection::_SetZindex(_FrameBase *Tgt) const
{
	// 加算値（仮置き）
	const int FRAME_IN_SEQUENCER_MAX = 0xFF;
	// もしDrawOrderが指定済みならば
	if(Tgt->DrawOrder != 0){
		// 何もしない
		return;
	}
	// もし親が有効なら
	if(Tgt->Parent){
		// 親に同様の操作を行う
		_SetZindex(Tgt->Parent);
	}
	// もし自身の親がTopParentなら
	if(Tgt->Parent == _TopParent){
		// SequencerのDrawOrderを最初に加味する
		Tgt->DrawOrder = _SequenceCollection::GetInstance().Top()->_DrawOrder * FRAME_IN_SEQUENCER_MAX;
	}
	// 自身の親フレームのZ座標を足して返却
	Tgt->DrawOrder += (Tgt->Parent ? Tgt->Parent->DrawOrder : 0) + 1;
}

// ----------------------------------------------------
//	FrameCollection::EnableParent
// ----------------------------------------------------
bool			_FrameCollection::_EnableParent(const _FrameBase *Tgt) const
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
				_SequenceCollection::~_SequenceCollection()
{
	// 全削除
	_Container.clear();
}

// ----------------------------------------------------
//	SequenceCollection::Add
// ----------------------------------------------------
void			_SequenceCollection::Add(const std::shared_ptr<Sequencer> &Target)
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
				_SequenceCollection::Top() const
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
void			_SequenceCollection::Delete(const Sequencer *Target)
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
//	SequenceCollection::Size
// ----------------------------------------------------
unsigned int	_SequenceCollection::Size() const
{
	// 個数を返却
	return _Container.size();
}
