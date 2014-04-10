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
	auto ApcSys = _System::GetInstance();
	// ----------------------------------------------------
	// Apocalypse使用前の準備を行う
	ApcSys.ApcSetUp();
	// Apocalypseを使用できるようにする
	ApcSys.ApcStart();
	// シーケンス取得関数を実行
	auto StartSeq = ( !ApplicationConfig::Sequence.empty() ? ApplicationConfig::Sequence() : nullptr);
	// もし結果がNULLなら
	if(StartSeq == nullptr){
		// ゲームを終了させる．
		ApcSys.ApcEnd();
		// 終了
		return 0;
	}
	// コレクションに追加する
	_SequenceCollection::GetInstance().Add(std::shared_ptr<Sequencer>(StartSeq));
	// ループを発生させる
	while(ApcSys.ApcProcess()){
		// イベント処理を行う
		_SequenceCollection::GetInstance().Top()->Events._ArrayCheck();
		// フレーム描画順を入れ替える．
		_FrameCollection::GetInstance().Sort();
		// フレームをまとめて描画．
		_FrameCollection::GetInstance().DrawAll();
	}
	// ゲームを終了させる．
	ApcSys.ApcEnd();
	// 関数を終了させる．
	return 0;
}
