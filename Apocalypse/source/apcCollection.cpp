// --------------------------------------------------------
//	apcCollection.cpp
// --------------------------------------------------------
//	apcCollection.h のメンバ関数の実体を置く
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	FrameCollection
// ----------------------------------------------------
//	FrameCollection::FrameCollection (Constructor)
// ----------------------------------------------------
				__FrameCollection::__FrameCollection()
{
	// Get System Instance
	__ApcSystem gs = __ApcSystem::GetInstance();
	// ----------------------------------------------------
	// 最上位フレームを作成する
	_TopParent = std::shared_ptr<EdgeFrame>(new EdgeFrame());
	// 横幅と縦幅を指定する
	_TopParent->Width	= gs.GetWindowWidth();
	_TopParent->Height	= gs.GetWindowHeight();
	// ％指定を無効にする．
	_TopParent->SpecifyWithParcent = false;
}

// ----------------------------------------------------
//	FrameCollection::Insert
// ----------------------------------------------------
void			__FrameCollection::Insert(const std::shared_ptr<__FrameBase> &Target)
{
	// もしNULLフレームが渡されたら
	if(!Target.get()){
		// 何もしない
		return;
	}
	// 挿入する
	_Container.insert(Target);
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
std::shared_ptr<__FrameBase>	
				__FrameCollection::Enum(bool ResetFlag) const
{
	// 現在のカウント数を保存する
	static std::multiset<std::shared_ptr<__FrameBase>>::iterator Count;
	// 取得したフレームを保存する
	std::shared_ptr<__FrameBase> Result = NULL;
	// ------------------------------------------------
	// もし初期化フラグが指定されていれば
	if(ResetFlag){
		// カウントを初期化する
		Count = _Container.begin();
	}
	// もし次があるなら
	if(Count != _Container.end()){
		// 取得する
		Result = *Count;
		// 次に進める
		++Count;
	}
	// もし親にEnableがfalseのフレームがあるなら
	if(Result && !_EnableParent(Result)){
		// 再度呼び出す
		return Enum(false);
	}
	// もし親フレームが指定されていなければ
	if(!Result.get() && !Result->Parent.get()
	 && Result.GetPointer() != _TopParent.GetPointer()){
		// 親フレームをTopParentに指定する
		Result->Parent = _TopParent.GetPointer();
	}
	// 返却する
	return Result;
}

// ----------------------------------------------------
//	FrameCollection::Erase
// ----------------------------------------------------
void			__FrameCollection::Erase(const std::shared_ptr<__FrameBase> &Target)
{
	// イテレータを確保して先頭にする
	auto Count = _Container.begin();
	// ------------------------------------------------
	// もし引数に無効ポインタまたは最上位フレームを渡されたら
	if(!Target.get() || Target == _TopParent){
		// 何もしない
		return;
	}
	// 終わりまでループする（引数のフレームを親に持つフレームを探す）
	while(Count != _Container.end()){
		// もし親フレームが引数のフレームと同じなら
		if(Count->GetPointer()->Parent == Target){
			// 親フレームを書き換える
			(*Count)->Parent = (*Count)->Parent->Parent;
		}
		// イテレータを進める
		Count++;
	}
	// 指定されたフレームを削除する
	_Container.erase(Target);
	// 終了
	return;
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
bool			__FrameCollection::_Sort::operator()(const std::shared_ptr<__FrameBase> &A, const std::shared_ptr<__FrameBase> &B)
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
	// 最初に一つ取得する
	auto fTemp = Enum(true);
	// バイリニア法で描画
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	// もし無効なら
	if(fTemp.get() == NULL){
		// 終了
		return;
	}
	// ループを起こす
	do{
		// αブレンドを有効化
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,
			(int)( fTemp->Alpha * _GetParentAlphaParcent(fTemp) ));
		// 横幅・縦幅の標準値を取得
		fTemp->_SetProperties();
		// 位置をリセットする
		fTemp->_SetDefaultPosition();
		// もし非表示設定ならば
		if(fTemp->Visible == false){
			// 描画せずに繰り返す．
			continue;
		}
		// 取得したフレームの描画関数を実行する
		fTemp->_DrawThisFrame();
	}
	// NULLが返されるまで取得を続ける
	while((fTemp = Enum(false)).get());
}

// ----------------------------------------------------
//	FrameBase::GetParentAlphaParcent
// ----------------------------------------------------
double			__FrameCollection::_GetParentAlphaParcent(const std::shared_ptr<__FrameBase> &Target) const
{
	// 割合を返却
	return ((double)Target->Alpha / 255.0)*(Target->Parent.get() ? _GetParentAlphaParcent(Target->Parent) : 1.00);
}

// ----------------------------------------------------
//	FrameBase::GetParentZindex
// ----------------------------------------------------
unsigned int	__FrameCollection::_GetParentZindex(const std::shared_ptr<__FrameBase> &Target) const
{
	// 自身の親フレームのZ座標+自身のZ座標を返却
	return (Target->DrawOrder + (Target->Parent.get() ? _GetParentZindex(Target->Parent) : 1));
}

// ----------------------------------------------------
//	FrameCollection::EnableParent
// ----------------------------------------------------
bool			__FrameCollection::_EnableParent(const std::shared_ptr<__FrameBase> &Target) const
{
	// 引数が無効なら
	if(!Target.get()){
		// TRUEを返す
		return true;
	}
	// 引数.EnableがTRUEなら
	return (Target->Enable ? _EnableParent(Target->Parent) : false);
}

// ----------------------------------------------------
//	SequenceCollection
// ----------------------------------------------------
//	SequenceCollection::Add
// ----------------------------------------------------
void			__SequenceCollection::Add(const std::shared_ptr<Sequencer> &Target)
{
	// もしNULLなら
	if(Target.get() == NULL){
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
		return std::shared_ptr<Sequencer>::Empty();
	}
	// スタックの一番上を返す
	return _Container.back();
}

// ----------------------------------------------------
//	SequenceCollection::Delete
// ----------------------------------------------------
void			__SequenceCollection::Delete(const std::shared_ptr<Sequencer> &Target)
{
	// 一時保存する
	std::shared_ptr<Sequencer> TopSeq = Top();
	// ----------------------------------------------------
	// もしNULLなら
	if(!Target.get() || !TopSeq.get()){
		// 何もしない
		return;
	}
	// ループ
	do{
		// 末尾要素を削除する
		_Container.pop_back();
	// 引数のシーケンスになるまで続ける
	}while((TopSeq != Target) && (TopSeq = Top()).get());
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
UINT			__FrameCounter::GetCount()
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
