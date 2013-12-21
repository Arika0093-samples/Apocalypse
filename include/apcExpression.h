// --------------------------------------------------------
//	apcExpression.h
// --------------------------------------------------------
//	各種数式の関数を記載する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <math.h>
#include <include/apcClassBase.h>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Expression)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Expression
	{
		///	<summary>
		///		一次元数式クラスの基盤．このクラス自体は作成できない．
		///	</summary>
		/// <remarks>
		///		Function関数を実行することでそれぞれの数式の値を取得できます．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// VibrateExp(このクラスを継承したクラス)で説明します．他のクラスでも基本は同じです．
		///		// 数式クラスを用意
		///		VibrateExp vre;
		///		// 値を取得（戻り値はdoubleなのでintにキャストします）
		///		int Num = (int)vre.Function();
		///		</code>
		/// </example>
		class __SingleExpression : virtual public Base::__ApcBase
		{
		public:
			///	<summary>
			///		数式の解を求める関数．
			///	</summary>
			double				Function() const;
			///	<summary>
			///		結果の最低値．結果がこの値以下の場合この値になる．
			///	</summary>
			double				Min;
			///	<summary>
			///		結果の最高値．結果がこの値以上の場合この値になる．
			///	</summary>
			double				Max;
		private:
			///	<summary>
			///		1フレームごとに一定の値増加する値を引数に
			///		数字を返却する関数．仮想関数．
			///	</summary>
			///	<param name = "x">
			///		増加値．
			///	</param>
			virtual double		_f(int x) const = 0;
			///	<summary>
			///		カウンタの初期値を保存する変数．
			///	</summary>
			unsigned int		_StartCount;
		protected:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								__SingleExpression();
		};

		///	<summary>
		///		ニ次元数式クラスの基盤．このクラス自体は作成できない．
		///	</summary>
		/// <remarks>
		///		Function関数を実行することでそれぞれの数式の値を取得できます．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// HermiteExp(このクラスを継承したクラス)で説明します．他のクラスでも基本は同じです．
		///		// 数式クラスを用意
		///		HermiteExp hme;
		///		// 値を取得
		///		Point Num = hme.Function();
		///		// X座標のみ取得したい時は以下のようにします
		///		double Xval = hme.Function().X;
		///		</code>
		/// </example>
		class __DoubleExpression : virtual public Base::__ApcBase
		{
		public:
			///	<summary>
			///		数式の解を求める関数．
			///	</summary>
			Base::Point			Function() const;
			///	<summary>
			///		結果の最低値．結果がこの値以下の場合この値になる．
			///	</summary>
			double				Min;
			///	<summary>
			///		結果の最高値．結果がこの値以上の場合この値になる．
			///	</summary>
			double				Max;
		private:
			///	<summary>
			///		1フレームごとに一定の値増加する値を引数に
			///		数字を返却する関数．仮想関数．
			///	</summary>
			///	<param name = "t">
			///		増加値．
			///	</param>
			virtual Base::Point	_f(int t) const = 0;
			///	<summary>
			///		カウンタの初期値を保存する変数．
			///	</summary>
			unsigned int		_StartCount;
		protected:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								__DoubleExpression();
		};

		///	<summary>
		///		振幅波の数式クラス．
		///	</summary>
		/// <remarks>
		///		内部でsin関数を使用しています．
		/// </remarks>
		class VibrateExp : public __SingleExpression
		{
		public:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								VibrateExp();
			///	<summary>
			///		振幅の値．
			///	</summary>
			double				Amplitude;
			///	<summary>
			///		周期(/Frame)．何Frameで一回ループするか．
			///		1Frame = 1として指定する．
			///	</summary>
			double				Cycle;
		private:
			///	<summary>
			///		1フレームごとに一定の値増加する値を引数に
			///		数字を返却する関数．
			///	</summary>
			///	<param name = "x">
			///		増加値．
			///	</param>
			double				_f(int x) const;
			///	<summary>
			///		°度をrad度に換算する．
			///	</summary>
			///	<param name = "Deg">
			///		増加値．
			///	</param>
			double				_DegToRad(double Deg) const;
		};

		///	<summary>
		///		直感的に使用できる曲線式を表現する数式クラス．
		///	</summary>
		/// <remarks>
		///		内部でエルミート曲線を使用しています．
		/// </remarks>
		class HermiteExp : public __DoubleExpression
		{
		public:
			///	<summary>
			///		コンストラクタ．
			///	</summary>
								HermiteExp();
			///	<summary>
			///		数式の開始点．
			///	</summary>
			Base::Point			Start;
			///	<summary>
			///		数式の終了点．
			///	</summary>
			Base::Point			End;
			///	<summary>
			///		数式の始点ベクトル．
			///	</summary>
			Base::Point			StartVector;
			///	<summary>
			///		数式の終点ベクトル．
			///	</summary>
			Base::Point			EndVector;
			///	<summary>
			///		移動の所要時間(Frame単位)．
			///	</summary>
			unsigned int		Time;
		private:
			///	<summary>
			///		1フレームごとに一定の値増加する値を引数に
			///		数字を返却する関数．
			///	</summary>
			///	<param name = "x">
			///		増加値．
			///	</param>
			Base::Point			_f(int t) const;
		};
	}
}
