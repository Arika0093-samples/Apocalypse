// --------------------------------------------------------
//	apcInterface.h
// --------------------------------------------------------
//	UI関連のクラスを記載する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <include/apcClassBase.h>
#include <include/apcDrawing.h>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::UI)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace UI
	{
		///	<summary>
		///		すべてのコントロールの基盤．
		///	</summary>
		/// <remarks>
		///		コントロールを作成し，表示します．
		/// </remarks>
		class ControlBase : public Draw::EdgeFrame
		{
		public:
			/// <summary>
			///		コンストラクタ．
			/// </summary>
			/// <param name = "Path">
			///		コントロールの背景の画像のパス．
			/// </param>
									ControlBase(Base::String Path = _T(""));
			/// <summary>
			///		デストラクタ．
			/// </summary>
			virtual					~ControlBase(){}
			/// <summary>
			///		コントロールの背景の画像を差し替える．
			/// </summary>
			/// <param name = "Path">
			///		コントロールの背景の画像のパス．
			/// </param>
			void					ExchangeBackground(Base::String Path);
			/// <summary>
			///		引き伸ばして表示するかどうか．
			/// </summary>
			/// <remarks>
			///		枠内部の部分を引き伸ばして表示するか，それとも繰り返し描画するかを選択します．
			///		例としては，グラデーションを使用している場合はtrue，タイル模様ならばfalseなどです．
			/// </remarks>
			bool					StretchDraw;
		private:
			///	<summary>
			///		読み込んだ画像の横幅．
			///	</summary>
			int						PictWidth;
			///	<summary>
			///		読み込んだ画像の縦幅．
			///	</summary>
			int						PictHeight;
		protected:
			///	<summary>
			///		フレームを描画する関数．このフレームの場合は何もしない．
			///	</summary>
			virtual void			DrawThisFrame() const {}
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void			SetProperties();
			/// <summary>
			///		UI背景左上の画像．
			/// </summary>
			Draw::PictureFrame		TopLeft;
			/// <summary>
			///		UI背景左下の画像．
			/// </summary>
			Draw::PictureFrame		BottomLeft;
			/// <summary>
			///		UI背景右上の画像．
			/// </summary>
			Draw::PictureFrame		TopRight;
			/// <summary>
			///		UI背景右下の画像．
			/// </summary>
			Draw::PictureFrame		BottomRight;
			/// <summary>
			///		UI背景中央上の画像．
			/// </summary>
			Draw::TilePictureFrame	TopCenter;
			/// <summary>
			///		UI背景中心左の画像．
			/// </summary>
			Draw::TilePictureFrame	MiddleLeft;
			/// <summary>
			///		UI背景真ん中の画像．
			/// </summary>
			Draw::TilePictureFrame	MiddleCenter;
			/// <summary>
			///		UI背景中心右の画像．
			/// </summary>
			Draw::TilePictureFrame	MiddleRight;
			/// <summary>
			///		UI背景中央下の画像．
			/// </summary>
			Draw::TilePictureFrame	BottomCenter;
		};
	}
}