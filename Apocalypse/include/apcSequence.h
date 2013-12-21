// --------------------------------------------------------
//	apcSequence.h
// --------------------------------------------------------
//	シーケンスのクラスを作成する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <include/apcClassBase.h>
#include <include/apcEvent.h>
#include <include/apxTemplate.h>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Sequence)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Sequence
	{
		///	<summary>
		///		シーケンスの基盤クラス．
		///	</summary>
		/// <remarks>
		///		このクラス自体は生成できません．このクラスを継承したクラスを使用します．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		class MainSequence : public Sequencer
		///		{
		///		public:
		///			…
		///		};
		///		</code>
		/// </example>
		class Sequencer : virtual public Base::__ApcBase
		{
		public:
			/// <summary>
			///		このフレームのイベントリスト．
			/// </summary>
			Event::__EventHandleList
								Events;
			///	<summary>
			///		別のシーケンスに制御を移動させる用の関数．
			///	</summary>
			/// <remarks>
			///		現在のシーケンスクラスを，引数に渡されたシーケンスに変更します．
			/// </remarks>
			///	<param name = "To">
			///		制御を移動させる先のシーケンス．newで移動先を確保して渡す．<br />
			///	</param>
			/// <example>
			///		使用例: 
			///		<code>
			///		void MainSequence::FrameProcess()
			///		{
			///			if(Key::AnyPushing()){				// もし何かが押されていれば
			///				MoveSequence(new XSequence());	// 自身を破棄してXSequenceに移動する
			///			}
			///		}
			///		</code>
			/// </example>
			void				Move(std::shared_ptr<Sequencer> To);
			///	<summary>
			///		現在のシーケンスに新しくシーケンスを重ねる．
			///	</summary>
			/// <remarks>
			///		<para>現在のシーケンスクラスをそのままに，一つ上にシーケンスを載せて制御を移動します．</para>
			///		<para>Addで追加したシーケンスを破棄したいときは DeleteSequence(); を使用します．</para>
			/// </remarks>
			///	<param name = "To">
			///		制御を移動させる先のシーケンス．newで移動先を確保して渡す．<br />
			///	</param>
			/// <example>
			///		使用例: 
			///		<code>
			///		void MainSequence::FrameProcess()
			///		{
			///			if(Key::AnyPushing()){				// もし何かが押されていれば
			///				AddSequence(new XSequence());	// XSequenceに移動する
			///			}
			///		}
			///		</code>
			/// </example>
			void				Add(std::shared_ptr<Sequencer> To);
			///	<summary>
			///		現在のシーケンスを終了させる．
			///	</summary>
			/// <remarks>
			///		<para>現在のシーケンスクラスを破棄して，一つ下のシーケンスに移動します．</para>
			///		<para>シーケンスが残っていない場合はゲームを終了します．</para>
			/// </remarks>
			/// <example>
			///		使用例: 
			///		<code>
			///		void MainSequence::FrameProcess()
			///		{
			///			if(Key::AnyPushing()){	// もし何かが押されていれば
			///				DeleteSequence();	// 現在のシーケンスを削除
			///			}
			///		}
			///		</code>
			/// </example>
			void				Delete();
			///	<summary>
			///		Destructor.
			///	</summary>
			virtual				~Sequencer(){}
		protected:
			///	<summary>
			///		コンストラクタ．このクラス自身は呼び出せない．
			///	</summary>
								Sequencer(){}
		};
	}
}

