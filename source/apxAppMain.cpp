// --------------------------------------------------------
//	apxAppMain.cpp
// --------------------------------------------------------
#include "Apocalypse.hpp"

// --------------------------------------------------------
//	Main Function
// --------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// システムクラスのポインタを取得
	__ApcSystem		ApcSys = __ApcSystem::GetInstance();
	// 最初に動作させるシーケンスを一時保存する
	Sequencer*		StartSeq = NULL;
	// ----------------------------------------------------
	// Apocalypse使用前の準備を行う
	ApcSys.ApcSetUp(*ApcSys.GameSetting);
	// Apocalypseを使用できるようにする
	ApcSys.ApcStart();
	// もしシーケンス取得関数を実行し，結果がNULLなら
	if((StartSeq = ApcSys.GameSetting->Sequence()) == NULL){
		// 終了
		return 0;
	}
	// コレクションに追加する
	__SequenceCollection::GetInstance().Add(StartSeq);
	// ループを発生させる
	while(ApcSys.ApcProcess()){
		// イベント処理を行う
		__SequenceCollection::GetInstance().Top()->Events._ArrayCheck();
		// フレームをまとめて描画．
		__FrameCollection::GetInstance().DrawAll();
	}
	// ゲームを終了させる．
	ApcSys.ApcEnd();
	// 関数を終了させる．
	return 0;
}
