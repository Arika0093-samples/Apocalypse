// --------------------------------------------------------
//	apcSound.h
// --------------------------------------------------------
//	音関連のクラスを記載する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Sound)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Sound
	{
		/// <summary>
		///		音を再生するための各種項目をまとめたクラス．
		/// </summary>
		/// <remarks>
		///		このクラスを使用することでSE（効果音）とBGMと両方に対応できます．
		/// </remarks>
		/// <example>
		///		使用例:
		///		<code>
		///		ApcSound* Bgm = new ApcSound("BGM.wav");
		///		Bgm->Play();	// 再生する
		///		</code>
		/// </example>
		class SoundObject : virtual public Base::__ApcBase
		{
		public:
			/// <summary>
			///		ApcSoundクラスのコンストラクタ．
			/// </summary>
			/// <remarks>
			///		引数にファイル名を指定することでそのファイルを再生する用意を行います．
			/// </remarks>
			/// <param name="FilePath">
			///		再生する対象のファイル名．
			///	</param>
								SoundObject(Base::String FilePath);
			/// <summary>
			///		再生時の音量を指定する．
			/// </summary>
			/// <remarks>
			///		0（無音）～255（最大）までの間で指定します．
			/// </remarks>
			UINT				Volume;
			/// <summary>
			///		再生時のパンを指定する．
			/// </summary>
			/// <remarks>
			///		-10000（左耳だけ）～10000（右耳だけ）の間で指定します．
			/// </remarks>
			int					Pan;
			/// <summary>
			///		再生中か取得する関数．
			/// </summary>
			bool				IsPlaying();
			/// <summary>
			///		再生を行う関数．
			/// </summary>
			/// <remarks>
			///		内部のサウンドハンドルを元に再生を行います．
			///		停止する際は Stop() 関数を使用します．
			/// </remarks>
			void				Play();
			/// <summary>
			///		再生停止を行う関数．
			/// </summary>
			/// <remarks>
			///		現在音を再生している場合停止します．
			/// </remarks>
			void				Stop();
		private:
			/// <summary>
			///		音データを保持するハンドル．
	/// </summary>
			int					_Handle;
		};
	}
}