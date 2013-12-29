// ----------------------------------------------------
//	Apocalypse.hpp
//						Copyright (C) 2013-2014 Arika.
// ----------------------------------------------------
//	Apocalypseの全機能を使用するのにincludeするヘッダーです．
//	使用時の手間を減らすために，
//	　・全ファイルをinclude
//	　・全名前空間を標準でusing
//	　・いくつかのdefineマクロを定義
//	　・libを自動で読み込む
//	の4つを行っています．
//	気になる人は自分で個別にincludeしてください．
// ----------------------------------------------------
//	read once
#pragma once

// ----------------------------------------------------
//	読み込み時の設定
// ----------------------------------------------------
//	設定を有効にするには，先頭のコメントアウトを外して下さい．
//	#define NOTUSING_DEFINEMACRO	// マクロを使用しません
//	#define NOTUSING_NAMESPACE		// 名前空間をusingしません
//	#define NOTLOADING_LIB			// .libを読み込みません

// ----------------------------------------------------
//	Include(定義関連)
// ----------------------------------------------------
//	マクロ定義
#include "include/apxMacro.hpp"
// ----------------------------------------------------
//	基底クラス(名前空間: Apocalypse::Base)
#include "include/apcClassBase.hpp"
// ----------------------------------------------------
//	テンプレートクラス(名前空間: Apocalypse::Template)
#include "include/apxTemplate.hpp"
// ----------------------------------------------------
//	ヘルプファイル作成用ヘッダー
#include "include/apxDoxygen.hpp"

// ----------------------------------------------------
//	Include(クラス関連)
// ----------------------------------------------------
//	イベントクラス(名前空間: Apocalypse::Event)
#include "include/apcEvent.hpp"
// ----------------------------------------------------
//	要素管理クラス(名前空間: Apocalypse::Collection)
#include "include/apcCollection.hpp"
// ----------------------------------------------------
//	入力管理クラス(名前空間: Apocalypse::Input)
#include "include/apcInput.hpp"
// ----------------------------------------------------
//	シーケンスクラス(名前空間: Apocalypse::Sequence)
#include "include/apcSequence.hpp"
// ----------------------------------------------------
//	描画クラス(名前空間: Apocalypse::Draw)
#include "include/apcDrawing.hpp"
// ----------------------------------------------------
//	音声クラス(名前空間: Apocalypse::Sound)
//#include "include/apcSound.hpp"
// ----------------------------------------------------
//	数式クラス(名前空間: Apocalypse::Expression)
//#include "include/apcExpression.hpp"
// ----------------------------------------------------
//	システム管理クラス(名前空間: Apocalypse::System)
#include "include/apcSystem.hpp"
// ----------------------------------------------------
//	UI描画/管理クラス(名前空間: Apocalypse::UI)
//#include "include/apcInterface.hpp"

// ----------------------------------------------------
//	libファイル読み込み
// ----------------------------------------------------
//	NOTLOADING_LIBが定義されている場合既定で読み込みません． 
#ifndef NOTLOADING_LIB
	#ifndef _WIN64
		#ifndef _DEBUG
			#pragma comment(lib, "lib/Apocalypse.lib")
		#else
			#pragma comment(lib, "lib/Apocalypse_d.lib")
		#endif
	#else
		#ifndef _DEBUG
			#pragma comment(lib, "lib/Apocalypse_x64.lib")
		#else
			#pragma comment(lib, "lib/Apocalypse_x64_d.lib")
		#endif
	#endif
#endif

// ----------------------------------------------------
//	名前空間を使用する
// ----------------------------------------------------
//	NOTUSING_NAMESPACEが定義されている場合既定でusingしません
#ifndef NOTUSING_NAMESPACE
	using namespace Apocalypse;
	using namespace Apocalypse::Base;
	using namespace Apocalypse::System;
	using namespace Apocalypse::Sequence;
	using namespace Apocalypse::Draw;
	using namespace Apocalypse::Event;
	using namespace Apocalypse::Collection;
	using namespace Apocalypse::Input;
	//using namespace Apocalypse::Expression;
	//using namespace Apocalypse::Sound;
	//using namespace Apocalypse::UI;
#endif
