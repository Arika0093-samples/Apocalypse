// --------------------------------------------------------
//	apcSystem.h
// --------------------------------------------------------
//	システム関連のクラスを記載する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <Windows.h>
#include <dxlib/DxLib.h>
#include <boost/function.hpp>
#include <include/apcClassBase.hpp>
#include <include/apcSequence.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::System)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace System
	{
		// --------------------------------------------------------
		//	Typedef
		// --------------------------------------------------------
		typedef boost::function<std::shared_ptr<Sequence::Sequencer>()>	SeqFunc;
		typedef	boost::function<bool()>									ExitFunc;

		/// <summary>
		///		システムを動かすための各種初期設定項目をまとめたクラス．
		/// </summary>
		/// <remarks>
		///		<para>このクラスの値を変更して，Accept関数を実行することで適用されます．</para>
		///		<para>ApcSetUp関数内で値を変更することで，自動で設定が適用されます．</para>
		/// </remarks>
		/// <example>
		///		使用例:
		///		<code>
		///		void ApocalypseSetUp()
		///		{
		///			// 初期シーケンス関数を指定する（必須）
		///			ApplicationConfig::Sequence	= [](){return new AnySequence();}
		///			ApplicationConfig::Width	= 800;			// 横幅を指定
		///			ApplicationConfig::Height	= 600;			// 縦幅を指定
		///			ApplicationConfig::Title	= "GameTest";	// ウインドウ名を指定
		///			ApplicationConfig::DualBoot = true;			// 二重起動できるようにする
		///			// etc...
		///		}
		///		</code>
		/// </example>
		class ApplicationConfig : public Base::__ApcBase
		{
		public:
			/// <summary>
			///		作成されるウインドウの横幅．
			/// </summary>
			static UINT				Width;
			/// <summary>
			///		作成されるウインドウの縦幅．
			/// </summary>
			static UINT				Height;
			/// <summary>
			///		リフレッシュレートの値．初期値は60．
			/// </summary>
			static UINT				Refresh;
			/// <summary>
			///		作成されるウインドウのタイトル名．
			/// </summary>
			static Value::String	Title;
			/// <summary>
			///		作成されるウインドウのタイトル名．
			/// </summary>
			static Value::String	ClassName;
			/// <summary>
			///		標準のフォント名．
			/// </summary>
			static Value::String	DefaultFontName;
			/// <summary>
			///		<para>初期シーケンスを指定する関数を登録します．必ず指定する必要があります．</para>
			///		<para>戻り値がshared_ptr(Sequence::Sequencer)の引数無し関数を指定します．</para>
			///		<para>戻り値に指定したSequencerが初期シーケンスとなります．</para>
			/// </summary>
			/// <example>
			///		ラムダ式を使用して，Sequencerを継承したFirstSeqを
			///		初期シーケンスに指定する例:
			///		<code>
			///		void ApocalypseSetUp()
			///		{
			///			ApplicationConfig::Sequence	= [](){return new FirstSeq();};
			///		}
			///		</code>
			/// </example>
			static SeqFunc			Sequence;
			/// <summary>
			///		<para>終了する前に呼び出される関数を登録できます．</para>
			///		<para>関数は戻り値がboolの引数無し関数です．戻り値がtrueの場合終了します．</para>
			///		<para>初期状態では何も呼び出されません．</para>
			/// </summary>
			static ExitFunc			ExitFunction;
			/// <summary>
			///		非アクティブ時でも常に動作するかどうか．初期値はfalse．
			/// </summary>
			static bool				ActiveAll;
			/// <summary>
			///		Windows Vista以降のAeroを無効化するかどうか．標準ではfalse．
			/// </summary>
			static bool				AeroDisable;
			/// <summary>
			///		非同期読み込みを行うかどうか．初期値はfalse．
			/// </summary>
			static bool				ASyncLoad;
			/// <summary>
			///		デバッグモードで起動するかどうか．
			///		初期値はDEBUGコンパイルならtrue, それ以外ならfalse．
			/// </summary>
			static bool				DebugMode;
			/// <summary>
			///		二重起動が可能かどうか．初期値はfalse．
			/// </summary>
			static bool				DualBoot;
			/// <summary>
			///		GDI描画を行うかどうか．初期値はfalse．
			/// </summary>
			static bool				GDIDraw;
			/// <summary>
			///		ウインドウモードで開始するかどうか．初期値はtrue．
			/// </summary>
			static bool				WindowMode;
			/// <summary>
			///		環境設定を適用する関数
			/// </summary>
			static void				Accept();
			/// <summary>
			///		標準のフォント名を取得
			/// </summary>
			static Value::String	_GetDefaultFontName();
		};

		/// <summary>
		///		システム関連のクラス．Singleton．
		/// </summary>
		/// <remarks>
		///		<para>このクラス内では，ゲームの起動と終了関連の処理を行います．</para>
		///		<para>ApcSetup関数は独自に実装する必要があります．</para>
		/// </remarks>
		class __ApcSystem : public Template::__Singleton<__ApcSystem>
		{
			/// <summary>
			///		Singletonクラスは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Template::__Singleton<__ApcSystem>;
		public:
			/// <summary>
			///		Apocalypse起動前のセットアップを行う関数です．
			/// </summary>
			/// <remarks>
			///		この関数はユーザーが独自に定義する必要があります．
			/// </remarks>
			/// <example>
			///		使用例:
			///		<code>
			///		void ApocalypseSetUp()
			///		{
			///			// 初期設定を行う．詳細はApplicationConfig::を参照してください．
			///		}
			///		</code>
			/// </example>
			void				ApcSetUp() const;
			/// <summary>
			///		起動する
			/// </summary>
			bool				ApcStart() const;
			/// <summary>
			///		１フレーム毎に必要な動作を行う．
			/// </summary>
			bool				ApcProcess() const;
			/// <summary>
			///		ゲームを終了する．
			/// </summary>
			void				ApcEnd() const;
		private:
			/// <summary>
			///		コンストラクタ
			/// </summary>
								__ApcSystem();
			/// <summary>
			///		プログラムの基準ディレクトリを設定する． 
			/// </summary>
			void				_SetProgramDirectory() const;
			/// <summary>
			///		ゲーム起動前に各種設定を行う．
			/// </summary>
			void				_InitGameProcess() const;
			/// <summary>
			///		ゲームを起動する．
			/// </summary>
			void				_RunStartProcess() const;
			/// <summary>
			///		ゲームを終了する．
	/// </summary>
			void				_RunEndProcess() const;
		};
	}
}
