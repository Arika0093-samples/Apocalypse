// --------------------------------------------------------
//	apcDrawing.h
// --------------------------------------------------------
//	描画関連のクラスを記載する．
// --------------------------------------------------------
//	一度だけ読み込む
#pragma once

// --------------------------------------------------------
//	必要なヘッダーを読み込む
// --------------------------------------------------------
#include <Windows.h>
#include <dxlib/DxLib.h>
#include <include/apcClassBase.hpp>
#include <include/apcCollection.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Draw)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Draw
	{
		///	<summary>
		///		フレームの位置を示す定数を定義した列挙型．
		///	</summary>
		///	<remark>
		///		C++の性質上enumを外に置くとサジェストが汚染されるので
		///		クラスの内部に隠蔽しています．
		///	</remark>
		class FramePosition : public Base::__ApcEnumeration
		{
		public:
			///	<summary>
			///		フレームの位置を示す定数を収納した列挙型．
			///	</summary>
			enum				_FramePosition
			{
				///	<summary>
				///		左上を示す．
				///	</summary>
				TopLeft,
				///	<summary>
				///		中央上を示す．
				///	</summary>
				TopCenter,
				///	<summary>
				///		右上を示す．
				///	</summary>
				TopRight,
				///	<summary>
				///		左中央を示す．
				///	</summary>
				MiddleLeft,
				///	<summary>
				///		中心を示す．
				///	</summary>
				MiddleCenter,
				///	<summary>
				///		右中央を示す．
				///	</summary>
				MiddleRight,
				///	<summary>
				///		左下を示す．
				///	</summary>
				BottomLeft,
				///	<summary>
				///		中央下を示す．
				///	</summary>
				BottomCenter,
				///	<summary>
				///		右下を示す．
				///	</summary>
				BottomRight,
				///	<summary>
				///		標準の位置を示す．
				///	</summary>
				Default			= MiddleCenter,
			};
		};

		///	<summary>
		///		描画の種類を示す定数を定義した列挙型．
		///	</summary>
		///	<remark>
		///		C++の性質上enumを外に置くとサジェストが汚染されるので
		///		クラスの内部に隠蔽しています．
		///	</remark>
		class FrameDrawMode : public Base::__ApcEnumeration
		{
		public:
			///	<summary>
			///		描画の種類を示す定数を定義した列挙型．
			///	</summary>
			enum				_FrameDrawMode
			{
				///	<summary>
				///		ネアレストネイバー法で描画
				///	</summary>
				Nearest		= DX_DRAWMODE_NEAREST,
				///	<summary>
				///		バイリニア法で描画する
				///	</summary>
				Bilinear	= DX_DRAWMODE_BILINEAR,
				///	<summary>
				///		異方性フィルタリング法で描画する
				///	</summary>
				Anisotropic	= DX_DRAWMODE_ANISOTROPIC,
				///	<summary>
				///		それ以外
				///	</summary>
				Other		= DX_DRAWMODE_OTHER,
			};
		};

		///	<summary>
		///		色を管理するクラス
		///	</summary>
		/// <remarks>
		///		<para>GradationFrameやTextFrameで使用する色データを取得・管理します．</para>
		///		<para>色リストについてはColor::ColorListを参照してください．</para>
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// 透明度50%のオレンジ色を取得します(0x80 = 128 = 255/2)
		///		Color::Color(0x80, 0xFF, 0x80, 0x00);
		///		// 透明度0%の白色を取得します
		///		Color::Color(Color::White);
		///		// 透明度10%の赤色を取得します(0xE5 = 229 = 255*0.9)
		///		Color::Color(Color::Red, 0xE5);
		///		// 透明色を取得します
		///		Color::Color(Color::Transparent);
		///		</code>
		/// </example>
		class Color : public Base::__ApcBase
		{
		public:
			///	<summary>
			///		色リストデータの列挙体
			///	</summary>
			enum			_ColorList
			{
				/// <summary>
				/// AliceBlue(#F0F8FF)の色を取得します．
				/// </summary>
				AliceBlue = 0xFFF0F8FF,
				/// <summary>
				/// AntiqueWhite(#FAEBD7)の色を取得します．
				/// </summary>
				AntiqueWhite = 0xFFFAEBD7,
				/// <summary>
				/// Aqua(#00FFFF)の色を取得します．
				/// </summary>
				Aqua = 0xFF00FFFF,
				/// <summary>
				/// Aquamarine(#7FFFD4)の色を取得します．
				/// </summary>
				Aquamarine = 0xFF7FFFD4,
				/// <summary>
				/// Azure(#F0FFFF)の色を取得します．
				/// </summary>
				Azure = 0xFFF0FFFF,
				/// <summary>
				/// Beige(#F5F5DC)の色を取得します．
				/// </summary>
				Beige = 0xFFF5F5DC,
				/// <summary>
				/// Bisque(#FFE4C4)の色を取得します．
				/// </summary>
				Bisque = 0xFFFFE4C4,
				/// <summary>
				/// Black(#000000)の色を取得します．
				/// </summary>
				Black = 0xFF000000,
				/// <summary>
				/// BlanchedAlmond(#FFEBCD)の色を取得します．
				/// </summary>
				BlanchedAlmond = 0xFFFFEBCD,
				/// <summary>
				/// Blue(#0000FF)の色を取得します．
				/// </summary>
				Blue = 0xFF0000FF,
				/// <summary>
				/// BlueViolet(#8A2BE2)の色を取得します．
				/// </summary>
				BlueViolet = 0xFF8A2BE2,
				/// <summary>
				/// Brown(#A52A2A)の色を取得します．
				/// </summary>
				Brown = 0xFFA52A2A,
				/// <summary>
				/// BurlyWood(#DEB887)の色を取得します．
				/// </summary>
				BurlyWood = 0xFFDEB887,
				/// <summary>
				/// CadetBlue(#5F9EA0)の色を取得します．
				/// </summary>
				CadetBlue = 0xFF5F9EA0,
				/// <summary>
				/// Chartreuse(#7FFF00)の色を取得します．
				/// </summary>
				Chartreuse = 0xFF7FFF00,
				/// <summary>
				/// Chocolate(#D2691E)の色を取得します．
				/// </summary>
				Chocolate = 0xFFD2691E,
				/// <summary>
				/// Coral(#FF7F50)の色を取得します．
				/// </summary>
				Coral = 0xFFFF7F50,
				/// <summary>
				/// CornflowerBlue(#6495ED)の色を取得します．
				/// </summary>
				CornflowerBlue = 0xFF6495ED,
				/// <summary>
				/// Cornsilk(#FFF8DC)の色を取得します．
				/// </summary>
				Cornsilk = 0xFFFFF8DC,
				/// <summary>
				/// Crimson(#DC143C)の色を取得します．
				/// </summary>
				Crimson = 0xFFDC143C,
				/// <summary>
				/// Cyan(#00FFFF)の色を取得します．
				/// </summary>
				Cyan = 0xFF00FFFF,
				/// <summary>
				/// DarkBlue(#00008B)の色を取得します．
				/// </summary>
				DarkBlue = 0xFF00008B,
				/// <summary>
				/// DarkCyan(#008B8B)の色を取得します．
				/// </summary>
				DarkCyan = 0xFF008B8B,
				/// <summary>
				/// DarkGoldenrod(#B8860B)の色を取得します．
				/// </summary>
				DarkGoldenrod = 0xFFB8860B,
				/// <summary>
				/// DarkGray(#A9A9A9)の色を取得します．
				/// </summary>
				DarkGray = 0xFFA9A9A9,
				/// <summary>
				/// DarkGreen(#006400)の色を取得します．
				/// </summary>
				DarkGreen = 0xFF006400,
				/// <summary>
				/// DarkKhaki(#BDB76B)の色を取得します．
				/// </summary>
				DarkKhaki = 0xFFBDB76B,
				/// <summary>
				/// DarkMagenta(#8B008B)の色を取得します．
				/// </summary>
				DarkMagenta = 0xFF8B008B,
				/// <summary>
				/// DarkOliveGreen(#556B2F)の色を取得します．
				/// </summary>
				DarkOliveGreen = 0xFF556B2F,
				/// <summary>
				/// DarkOrange(#FF8C00)の色を取得します．
				/// </summary>
				DarkOrange = 0xFFFF8C00,
				/// <summary>
				/// DarkOrchid(#9932CC)の色を取得します．
				/// </summary>
				DarkOrchid = 0xFF9932CC,
				/// <summary>
				/// DarkRed(#8B0000)の色を取得します．
				/// </summary>
				DarkRed = 0xFF8B0000,
				/// <summary>
				/// DarkSalmon(#E9967A)の色を取得します．
				/// </summary>
				DarkSalmon = 0xFFE9967A,
				/// <summary>
				/// DarkSeaGreen(#8FBC8B)の色を取得します．
				/// </summary>
				DarkSeaGreen = 0xFF8FBC8B,
				/// <summary>
				/// DarkSlateBlue(#483D8B)の色を取得します．
				/// </summary>
				DarkSlateBlue = 0xFF483D8B,
				/// <summary>
				/// DarkSlateGray(#2F4F4F)の色を取得します．
				/// </summary>
				DarkSlateGray = 0xFF2F4F4F,
				/// <summary>
				/// DarkTurquoise(#00CED1)の色を取得します．
				/// </summary>
				DarkTurquoise = 0xFF00CED1,
				/// <summary>
				/// DarkViolet(#9400D3)の色を取得します．
				/// </summary>
				DarkViolet = 0xFF9400D3,
				/// <summary>
				/// DeepPink(#FF1493)の色を取得します．
				/// </summary>
				DeepPink = 0xFFFF1493,
				/// <summary>
				/// DeepSkyBlue(#00BFFF)の色を取得します．
				/// </summary>
				DeepSkyBlue = 0xFF00BFFF,
				/// <summary>
				/// DimGray(#696969)の色を取得します．
				/// </summary>
				DimGray = 0xFF696969,
				/// <summary>
				/// DodgerBlue(#1E90FF)の色を取得します．
				/// </summary>
				DodgerBlue = 0xFF1E90FF,
				/// <summary>
				/// Firebrick(#B22222)の色を取得します．
				/// </summary>
				Firebrick = 0xFFB22222,
				/// <summary>
				/// FloralWhite(#FFFAF0)の色を取得します．
				/// </summary>
				FloralWhite = 0xFFFFFAF0,
				/// <summary>
				/// ForestGreen(#228B22)の色を取得します．
				/// </summary>
				ForestGreen = 0xFF228B22,
				/// <summary>
				/// Fuchsia(#FF00FF)の色を取得します．
				/// </summary>
				Fuchsia = 0xFFFF00FF,
				/// <summary>
				/// Gainsboro(#DCDCDC)の色を取得します．
				/// </summary>
				Gainsboro = 0xFFDCDCDC,
				/// <summary>
				/// GhostWhite(#F8F8FF)の色を取得します．
				/// </summary>
				GhostWhite = 0xFFF8F8FF,
				/// <summary>
				/// Gold(#FFD700)の色を取得します．
				/// </summary>
				Gold = 0xFFFFD700,
				/// <summary>
				/// Goldenrod(#DAA520)の色を取得します．
				/// </summary>
				Goldenrod = 0xFFDAA520,
				/// <summary>
				/// Gray(#808080)の色を取得します．
				/// </summary>
				Gray = 0xFF808080,
				/// <summary>
				/// Green(#008000)の色を取得します．
				/// </summary>
				Green = 0xFF008000,
				/// <summary>
				/// GreenYellow(#ADFF2F)の色を取得します．
				/// </summary>
				GreenYellow = 0xFFADFF2F,
				/// <summary>
				/// Honeydew(#F0FFF0)の色を取得します．
				/// </summary>
				Honeydew = 0xFFF0FFF0,
				/// <summary>
				/// HotPink(#FF69B4)の色を取得します．
				/// </summary>
				HotPink = 0xFFFF69B4,
				/// <summary>
				/// IndianRed(#CD5C5C)の色を取得します．
				/// </summary>
				IndianRed = 0xFFCD5C5C,
				/// <summary>
				/// Indigo(#4B0082)の色を取得します．
				/// </summary>
				Indigo = 0xFF4B0082,
				/// <summary>
				/// Ivory(#FFFFF0)の色を取得します．
				/// </summary>
				Ivory = 0xFFFFFFF0,
				/// <summary>
				/// Khaki(#F0E68C)の色を取得します．
				/// </summary>
				Khaki = 0xFFF0E68C,
				/// <summary>
				/// Lavender(#E6E6FA)の色を取得します．
				/// </summary>
				Lavender = 0xFFE6E6FA,
				/// <summary>
				/// LavenderBlush(#FFF0F5)の色を取得します．
				/// </summary>
				LavenderBlush = 0xFFFFF0F5,
				/// <summary>
				/// LawnGreen(#7CFC00)の色を取得します．
				/// </summary>
				LawnGreen = 0xFF7CFC00,
				/// <summary>
				/// LemonChiffon(#FFFACD)の色を取得します．
				/// </summary>
				LemonChiffon = 0xFFFFFACD,
				/// <summary>
				/// LightBlue(#ADD8E6)の色を取得します．
				/// </summary>
				LightBlue = 0xFFADD8E6,
				/// <summary>
				/// LightCoral(#F08080)の色を取得します．
				/// </summary>
				LightCoral = 0xFFF08080,
				/// <summary>
				/// LightCyan(#E0FFFF)の色を取得します．
				/// </summary>
				LightCyan = 0xFFE0FFFF,
				/// <summary>
				/// LightGoldenrodYellow(#FAFAD2)の色を取得します．
				/// </summary>
				LightGoldenrodYellow = 0xFFFAFAD2,
				/// <summary>
				/// LightGreen(#90EE90)の色を取得します．
				/// </summary>
				LightGreen = 0xFF90EE90,
				/// <summary>
				/// LightGray(#D3D3D3)の色を取得します．
				/// </summary>
				LightGray = 0xFFD3D3D3,
				/// <summary>
				/// LightPink(#FFB6C1)の色を取得します．
				/// </summary>
				LightPink = 0xFFFFB6C1,
				/// <summary>
				/// LightSalmon(#FFA07A)の色を取得します．
				/// </summary>
				LightSalmon = 0xFFFFA07A,
				/// <summary>
				/// LightSeaGreen(#20B2AA)の色を取得します．
				/// </summary>
				LightSeaGreen = 0xFF20B2AA,
				/// <summary>
				/// LightSkyBlue(#87CEFA)の色を取得します．
				/// </summary>
				LightSkyBlue = 0xFF87CEFA,
				/// <summary>
				/// LightSlateGray(#778899)の色を取得します．
				/// </summary>
				LightSlateGray = 0xFF778899,
				/// <summary>
				/// LightSteelBlue(#B0C4DE)の色を取得します．
				/// </summary>
				LightSteelBlue = 0xFFB0C4DE,
				/// <summary>
				/// LightYellow(#FFFFE0)の色を取得します．
				/// </summary>
				LightYellow = 0xFFFFFFE0,
				/// <summary>
				/// Lime(#00FF00)の色を取得します．
				/// </summary>
				Lime = 0xFF00FF00,
				/// <summary>
				/// LimeGreen(#32CD32)の色を取得します．
				/// </summary>
				LimeGreen = 0xFF32CD32,
				/// <summary>
				/// Linen(#FAF0E6)の色を取得します．
				/// </summary>
				Linen = 0xFFFAF0E6,
				/// <summary>
				/// Magenta(#FF00FF)の色を取得します．
				/// </summary>
				Magenta = 0xFFFF00FF,
				/// <summary>
				/// Maroon(#800000)の色を取得します．
				/// </summary>
				Maroon = 0xFF800000,
				/// <summary>
				/// MediumAquamarine(#66CDAA)の色を取得します．
				/// </summary>
				MediumAquamarine = 0xFF66CDAA,
				/// <summary>
				/// MediumBlue(#0000CD)の色を取得します．
				/// </summary>
				MediumBlue = 0xFF0000CD,
				/// <summary>
				/// MediumOrchid(#BA55D3)の色を取得します．
				/// </summary>
				MediumOrchid = 0xFFBA55D3,
				/// <summary>
				/// MediumPurple(#9370DB)の色を取得します．
				/// </summary>
				MediumPurple = 0xFF9370DB,
				/// <summary>
				/// MediumSeaGreen(#3CB371)の色を取得します．
				/// </summary>
				MediumSeaGreen = 0xFF3CB371,
				/// <summary>
				/// MediumSlateBlue(#7B68EE)の色を取得します．
				/// </summary>
				MediumSlateBlue = 0xFF7B68EE,
				/// <summary>
				/// MediumSpringGreen(#00FA9A)の色を取得します．
				/// </summary>
				MediumSpringGreen = 0xFF00FA9A,
				/// <summary>
				/// MediumTurquoise(#48D1CC)の色を取得します．
				/// </summary>
				MediumTurquoise = 0xFF48D1CC,
				/// <summary>
				/// MediumVioletRed(#C71585)の色を取得します．
				/// </summary>
				MediumVioletRed = 0xFFC71585,
				/// <summary>
				/// MidnightBlue(#191970)の色を取得します．
				/// </summary>
				MidnightBlue = 0xFF191970,
				/// <summary>
				/// MintCream(#F5FFFA)の色を取得します．
				/// </summary>
				MintCream = 0xFFF5FFFA,
				/// <summary>
				/// MistyRose(#FFE4E1)の色を取得します．
				/// </summary>
				MistyRose = 0xFFFFE4E1,
				/// <summary>
				/// Moccasin(#FFE4B5)の色を取得します．
				/// </summary>
				Moccasin = 0xFFFFE4B5,
				/// <summary>
				/// NavajoWhite(#FFDEAD)の色を取得します．
				/// </summary>
				NavajoWhite = 0xFFFFDEAD,
				/// <summary>
				/// Navy(#000080)の色を取得します．
				/// </summary>
				Navy = 0xFF000080,
				/// <summary>
				/// OldLace(#FDF5E6)の色を取得します．
				/// </summary>
				OldLace = 0xFFFDF5E6,
				/// <summary>
				/// Olive(#808000)の色を取得します．
				/// </summary>
				Olive = 0xFF808000,
				/// <summary>
				/// OliveDrab(#6B8E23)の色を取得します．
				/// </summary>
				OliveDrab = 0xFF6B8E23,
				/// <summary>
				/// Orange(#FFA500)の色を取得します．
				/// </summary>
				Orange = 0xFFFFA500,
				/// <summary>
				/// OrangeRed(#FF4500)の色を取得します．
				/// </summary>
				OrangeRed = 0xFFFF4500,
				/// <summary>
				/// Orchid(#DA70D6)の色を取得します．
				/// </summary>
				Orchid = 0xFFDA70D6,
				/// <summary>
				/// PaleGoldenrod(#EEE8AA)の色を取得します．
				/// </summary>
				PaleGoldenrod = 0xFFEEE8AA,
				/// <summary>
				/// PaleGreen(#98FB98)の色を取得します．
				/// </summary>
				PaleGreen = 0xFF98FB98,
				/// <summary>
				/// PaleTurquoise(#AFEEEE)の色を取得します．
				/// </summary>
				PaleTurquoise = 0xFFAFEEEE,
				/// <summary>
				/// PaleVioletRed(#DB7093)の色を取得します．
				/// </summary>
				PaleVioletRed = 0xFFDB7093,
				/// <summary>
				/// PapayaWhip(#FFEFD5)の色を取得します．
				/// </summary>
				PapayaWhip = 0xFFFFEFD5,
				/// <summary>
				/// PeachPuff(#FFDAB9)の色を取得します．
				/// </summary>
				PeachPuff = 0xFFFFDAB9,
				/// <summary>
				/// Peru(#CD853F)の色を取得します．
				/// </summary>
				Peru = 0xFFCD853F,
				/// <summary>
				/// Pink(#FFC0CB)の色を取得します．
				/// </summary>
				Pink = 0xFFFFC0CB,
				/// <summary>
				/// Plum(#DDA0DD)の色を取得します．
				/// </summary>
				Plum = 0xFFDDA0DD,
				/// <summary>
				/// PowderBlue(#B0E0E6)の色を取得します．
				/// </summary>
				PowderBlue = 0xFFB0E0E6,
				/// <summary>
				/// Purple(#800080)の色を取得します．
				/// </summary>
				Purple = 0xFF800080,
				/// <summary>
				/// Red(#FF0000)の色を取得します．
				/// </summary>
				Red = 0xFFFF0000,
				/// <summary>
				/// RosyBrown(#BC8F8F)の色を取得します．
				/// </summary>
				RosyBrown = 0xFFBC8F8F,
				/// <summary>
				/// RoyalBlue(#4169E1)の色を取得します．
				/// </summary>
				RoyalBlue = 0xFF4169E1,
				/// <summary>
				/// SaddleBrown(#8B4513)の色を取得します．
				/// </summary>
				SaddleBrown = 0xFF8B4513,
				/// <summary>
				/// Salmon(#FA8072)の色を取得します．
				/// </summary>
				Salmon = 0xFFFA8072,
				/// <summary>
				/// SandyBrown(#F4A460)の色を取得します．
				/// </summary>
				SandyBrown = 0xFFF4A460,
				/// <summary>
				/// SeaGreen(#2E8B57)の色を取得します．
				/// </summary>
				SeaGreen = 0xFF2E8B57,
				/// <summary>
				/// SeaShell(#FFF5EE)の色を取得します．
				/// </summary>
				SeaShell = 0xFFFFF5EE,
				/// <summary>
				/// Sienna(#A0522D)の色を取得します．
				/// </summary>
				Sienna = 0xFFA0522D,
				/// <summary>
				/// Silver(#C0C0C0)の色を取得します．
				/// </summary>
				Silver = 0xFFC0C0C0,
				/// <summary>
				/// SkyBlue(#87CEEB)の色を取得します．
				/// </summary>
				SkyBlue = 0xFF87CEEB,
				/// <summary>
				/// SlateBlue(#6A5ACD)の色を取得します．
				/// </summary>
				SlateBlue = 0xFF6A5ACD,
				/// <summary>
				/// SlateGray(#708090)の色を取得します．
				/// </summary>
				SlateGray = 0xFF708090,
				/// <summary>
				/// Snow(#FFFAFA)の色を取得します．
				/// </summary>
				Snow = 0xFFFFFAFA,
				/// <summary>
				/// SpringGreen(#00FF7F)の色を取得します．
				/// </summary>
				SpringGreen = 0xFF00FF7F,
				/// <summary>
				/// SteelBlue(#4682B4)の色を取得します．
				/// </summary>
				SteelBlue = 0xFF4682B4,
				/// <summary>
				/// Tan(#D2B48C)の色を取得します．
				/// </summary>
				Tan = 0xFFD2B48C,
				/// <summary>
				/// Teal(#008080)の色を取得します．
				/// </summary>
				Teal = 0xFF008080,
				/// <summary>
				/// Thistle(#D8BFD8)の色を取得します．
				/// </summary>
				Thistle = 0xFFD8BFD8,
				/// <summary>
				/// Tomato(#FF6347)の色を取得します．
				/// </summary>
				Tomato = 0xFFFF6347,
				/// <summary>
				/// Transparent(透明色)の色を取得します．
				/// </summary>
				Transparent = 0x00FFFFFF,
				/// <summary>
				/// Turquoise(#40E0D0)の色を取得します．
				/// </summary>
				Turquoise = 0xFF40E0D0,
				/// <summary>
				/// Violet(#EE82EE)の色を取得します．
				/// </summary>
				Violet = 0xFFEE82EE,
				/// <summary>
				/// Wheat(#F5DEB3)の色を取得します．
				/// </summary>
				Wheat = 0xFFF5DEB3,
				/// <summary>
				/// White(#FFFFFF)の色を取得します．
				/// </summary>
				White = 0xFFFFFFFF,
				/// <summary>
				/// WhiteSmoke(#F5F5F5)の色を取得します．
				/// </summary>
				WhiteSmoke = 0xFFF5F5F5,
				/// <summary>
				/// Yellow(#FFFF00)の色を取得します．
				/// </summary>
				Yellow = 0xFFFFFF00,
				/// <summary>
				/// YellowGreen(#9ACD32)の色を取得します．
				/// </summary>
				YellowGreen = 0xFF9ACD32,
			};
			/// <summary>
			///		空の色データを作成する（引数に何も指定しない）．
			/// </summary>
							Color();
			/// <summary>
			///		色データを作成する（DxライブラリのGetColorと同じ）
			/// </summary>
			/// <param name = "R">
			///		赤の強度．0から255までの範囲で指定する．
			/// </param>
			/// <param name = "G">
			///		緑の強度．0から255までの範囲で指定する．
			/// </param>
			/// <param name = "B">
			///		青の強度．0から255までの範囲で指定する．
			/// </param>
							Color(int Rp, int Gp, int Bp);
			/// <summary>
			///		色データを作成する
			/// </summary>
			/// <param name = "A">
			///		透明度．0から255までの範囲で指定する．0で透明．
			/// </param>
			/// <param name = "R">
			///		赤の強度．0から255までの範囲で指定する．
			/// </param>
			/// <param name = "G">
			///		緑の強度．0から255までの範囲で指定する．
			/// </param>
			/// <param name = "B">
			///		青の強度．0から255までの範囲で指定する．
			/// </param>
							Color(int Ap, int Rp, int Gp, int Bp);
			/// <summary>
			///		色データを作成する（HTML等の色コード版）
			/// </summary>
			/// <param name = "ARGBCode">
			///		透明度情報を含むRGBコード．<see cref="_ColorList">ColorList</see>内で
			///		定義された値を使用することも可能です．
			/// </param>
							Color(_ColorList ARGBCode);
			/// <summary>
			///		色データを作成する（αブレンドを自分で指定する）
			/// </summary>
			/// <param name = "RGBCode">
			///		<para>透明度情報を含まないRGBコード．含まれる場合無視されます．</para>
			///		<para><see cref="_ColorList">ColorList</see>内で定義された値を使用することも可能です．</para>
			/// </param>
			/// <param name = "Alpha">
			///		この色のαブレンド．
			/// </param>
							Color(_ColorList RGBCode, int Alpha);
			/// <summary>
			///		色データを代入する
			/// </summary>
			Color&			operator=(const Color &Cr);
			/// <summary>
			///		色データを代入する
			/// </summary>
			Color&			operator=(const _ColorList ARGBCode);
			/// <summary>
			///		色データを比較する
			/// </summary>
			bool			operator==(const Color &Cr) const;
			/// <summary>
			///		色データをNOT比較する
			/// </summary>
			bool			operator!=(const Color &Cr) const;
			/// <summary>
			///		色データを比較する関数．
			/// </summary>
			/// <param name = "Target">
			///		比較する対象の色クラス．
			/// </param>
			bool			Compare(const Color &Target) const;
			/// <summary>
			///		%で渡されたAlphaを256段階に変換して返却する．
			/// </summary>
			static int		AlphaFromParcent(double Bs);
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String
							ToString() const;
			///	<summary>
			///		有効な色かどうか．
			///	</summary>
			bool			Enable;
			///	<summary>
			///		色の透明度の強度．
			///	</summary>
			int				A;
			///	<summary>
			///		色の赤成分の強度．
			///	</summary>
			int				R;
			///	<summary>
			///		色の緑成分の強度．
			///	</summary>
			int				G;
			///	<summary>
			///		色の青成分の強度．
			///	</summary>
			int				B;
			/// <summary>
			///		クラスに登録されている色データを返却する
			/// </summary>
			inline DWORD	_GetColor() const;
			/// <summary>
			///		クラスに登録されている透明度を適用する
			/// </summary>
			inline void		_AppendAlpha() const;
			/// <summary>
			///		自身と対象の色を一定割合でブレンドした結果のColorのポインタを返却する．
			/// </summary>
			/// <param name = "Target">
			///		自身とブレンドする対象の色データのポインタ．
			/// </param>
			/// <param name = "Parcent">
			///		ブレンドする割合．
			/// </param>
			std::shared_ptr<Color>
							_GetColorBlends(const Color &Target, int Parcent) const;
		};

		///	<summary>
		///		フォントデータを内蔵するクラス．
		///	</summary>
		/// <remarks>
		///		<para>フォント名，フォントサイズ，フォントの太さなどを管理します．</para>
		///		<para>標準のフォント名は初期化関数で指定した標準フォントです．</para>
		/// </remarks>
		class Font : public Base::__ApcBase
		{
		public:
			///	<summary>
			///		フォントの描画方法を指定する．
			///	</summary>
			class			FontType
			{
			public:
				enum		_FontType
				{
					///	<summary>
					///		普通に描画する．
					///	</summary>
					Normal,
					///	<summary>
					///		アンチエイリアスをかけて描画する．
					///	</summary>
					Antialiase,
					///	<summary>
					///		良質なアンチエイリアスをかけて描画する．
					///	</summary>
					AntialiaseHiQuality,
				};
			};
			///	<summary>
			///		コンストラクタ(無指定版)
			///	</summary>
							Font();
			///	<summary>
			///		コンストラクタ(サイズ指定版)
			///	</summary>
							Font(int FontSize);
			///	<summary>
			///		コンストラクタ(名前/サイズ指定版)
			///	</summary>
							Font(Value::String FontName, int FontSize);
			///	<summary>
			///		コンストラクタ(名前/サイズ/太さ指定版)
			///	</summary>
							Font(Value::String FontName, int FontSize, int FontThick);
			///	<summary>
			///		コンストラクタ(名前/サイズ/太さ/縁サイズ指定版)
			///	</summary>
							Font(Value::String FontName, int FontSize, int FontThick, int eSize);
			///	<summary>
			///		コンストラクタ(全部指定版)
			///	</summary>
							Font(Value::String FontName, int FontSize, int FontThick, int eSize, FontType::_FontType Type);
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual			~Font();
			///	<summary>
			///		フォント名．
			///	</summary>
			Value::String	Name;
			///	<summary>
			///		フォントサイズ．
			///	</summary>
			int				Size;
			///	<summary>
			///		フォントの太さ．
			///	</summary>
			int				Thick;
			///	<summary>
			///		描画方法の種類．FontTypeから選択する．
			///	</summary>
			FontType::_FontType
							Type;
			///	<summary>
			///		フォントの縁の太さ．
			///	</summary>
			int				EdgeSize;
			///	<summary>
			///		フォントの色．
			///	</summary>
			Color			FontColor;
			///	<summary>
			///		描画する文字の縁の色．Color::Transparentを指定すると縁を描画しません．
			///	</summary>
			Color			EdgeColor;
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String
							ToString() const;
			///	<summary>
			///		フォントハンドルを更新するかどうか確認し，更新する必要があれば更新する．
			///	</summary>
			void			_ReloadFontHandle();
			///	<summary>
			///		フォントハンドルを取得する．
			///	</summary>
			int				_GetFontHandle() const;
			///	<summary>
			///		描画種類を取得する．
			///	</summary>
			int				_GetFontDrawType() const;
		private:
			///	<summary>
			///		フォント名（内部保存用）．
			///	</summary>
			Value::String	_Name;
			///	<summary>
			///		フォントサイズ（内部保存用）．
			///	</summary>
			int				_Size;
			///	<summary>
			///		フォントの太さ（内部保存用）．
			///	</summary>
			int				_Thick;
			///	<summary>
			///		フォントの縁の太さ（内部保存用）．
			///	</summary>
			int				_Edge;
			///	<summary>
			///		フォントの種類（内部保存用）．
			///	</summary>
			FontType::_FontType
							_Type;
			///	<summary>
			///		フォントの縁が有効かどうか．
			///	</summary>
			bool			_IsEnableEdge;
			///	<summary>
			///		フォントハンドル
			///	</summary>
			int				_Handle;
		};
	
		///	<summary>
		///		すべてのフレームの基盤．
		///	</summary>
		/// <remarks>
		///		<para>Apocalypseでは，描画に関連することはフレーム(Frame)クラスを</para>
		///		<para>関して描画・管理されます．そのフレームクラスの基盤がこのクラスです．</para>
		///		<para>このクラス自体は生成できません．</para>
		/// </remarks>
		class __FrameBase : public Base::__ApcBase
		{
			/// <summary>
			///		FrameCollectionクラスからは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Collection::__FrameCollection;
			/// <summary>
			///		typedef
			/// </summary>
			typedef				FramePosition::_FramePosition	FPosition;
			typedef				FrameDrawMode::_FrameDrawMode	FDrawMode;
		public:
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual				~__FrameBase();
			/// <summary>
			///		このフレームが有効かどうか．
			/// </summary>
			/// <remarks>
			///		<para>フレームが無効な場合，自身と自身を親に持つフレームの</para>
			///		<para>位置移動・描画が行われなくなります．</para>
			/// </remarks>
			bool				Enable;
			/// <summary>
			///		このフレームを描画するかどうか．
			/// </summary>
			/// <remarks>
			///		<para>falseに指定するとフレームを描画しなくなります．</para>
			///		<para>Enableとの違いは，子フレームにも影響を及ぼすかどうかです．</para>
			/// </remarks>
			bool				Visible;
			/// <summary>
			///		このフレームの基準位置からの座標．
			/// </summary>
			Value::Point		Points;
			/// <summary>
			///		<para>このフレームの描画順番．高いほど手前に描画される．</para>
			///		<para>0に指定すると親フレームのZ座標から自動で指定される．</para>
			/// </summary>
			unsigned int		DrawOrder;
			/// <summary>
			///		設置位置を決定する定数．
			/// </summary>
			/// <remarks>
			///		<para>親フレームのどの位置に設置するかを決定します．</para>
			///		<para><see cref="FramePosition">FramePosition</see>で定義された定数を使用して下さい．</para>
			/// </remarks>
			FPosition			Position;
			/// <summary>
			///		中心位置を決定する定数．
			/// </summary>
			/// <remarks>
			///		<para>このフレームの中心をどの位置に設置するかを決定する定数．</para>
			///		<para><see cref="FramePosition">FramePosition</see>で定義された定数を使用して下さい．</para>
			/// </remarks>
			FPosition			Interpret;
			/// <summary>
			///		描画方法の種類．
			/// </summary>
			/// <remarks>
			///		<see cref="FrameDrawMode">FrameDrawMode</see>で定義された定数を使用して下さい．
			/// </remarks>
			FDrawMode			DrawMode;
			/// <summary>
			///		このフレームの親フレーム．
			/// </summary>
			__FrameBase*		Parent;
			/// <summary>
			///		フレームの横幅を取得する
			/// </summary>
			int					GetWidth() const;
			/// <summary>
			///		フレームの縦幅を取得する
			/// </summary>
			int					GetHeight() const;
			/// <summary>
			///		フレームの左上の座標を取得する
			/// </summary>
			Value::Point		GetLocation() const;
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String
								ToString() const;
		private:
			/// <summary>
			///		自身の標準のX, Y座標を指定する関数．
			/// </summary>
			void				_SetDefaultPosition();
			/// <summary>
			///		自身の標準の縦幅と横幅を指定する関数．仮想関数です．
			/// </summary>
			virtual void		_SetProperties() = 0;
			/// <summary>
			///		自身のフレームを描画する関数です．仮想関数です．
			/// </summary>
			virtual void		_DrawThisFrame() const = 0;
		protected:
			/// <summary>
			///		このフレームを描画する左上の場所
			/// </summary>
			Value::Point		_Location;
			/// <summary>
			///		フレームの位置合わせを行うかどうか．標準でtrue．
			/// </summary>
			bool				_AutoAdjustPosition;
			/// <summary>
			///		このフレームの横幅．
			/// </summary>
			int					_Width;
			/// <summary>
			///		このフレームの縦幅．
			/// </summary>
			int					_Height;
			/// <summary>
			///		コンストラクタ
			/// </summary>
			/// <param name = "fParent">
			///		親フレーム．
			/// </param>
								__FrameBase();
		};

		///	<summary>
		///		何も描画しないフレーム．
		///	</summary>
		/// <remarks>
		///		<para>このクラスは，何も描画しない代わりに，横幅と縦幅を指定できます．</para>
		///		<para>フレームの位置調整などに使用することができます．</para>
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// EdgeFrameをnewで確保して幅を親フレーム比100%に指定する．
		///		EdgeFrame* Base = new EdgeFrame();
		///		Base->SpecifyWithParcent = true;
		///		Base->Width = 100;
		///		Base->Height = 100;
		///		</code>
		/// </example>
		class EdgeFrame : virtual public __FrameBase
		{
		public:
			///	<summary>
			///		幅(Width, Height)を％で指定するかどうか．
			///	</summary>
			/// <remarks>
			///		trueで％指定になります(100%で親と同じ幅)．falseで絶対値指定になります．
			/// </remarks>
			bool				SpecifyWithParcent;
			///	<summary>
			///		横幅を指定する．
			///	</summary>
			int					Width;
			///	<summary>
			///		縦幅を指定する．
			///	</summary>
			int					Height;
			///	<summary>
			///		何も描画しないフレームを作成する際に実行される関数．
			///	</summary>
								EdgeFrame();
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~EdgeFrame(){}
		protected:
			///	<summary>
			///		フレームを描画する関数．このフレームの場合は何もしない．
			///	</summary>
			virtual void		_DrawThisFrame() const {}
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void		_SetProperties();
		};

		///	<summary>
		///		グラデーション・枠線を描画するフレーム．EdgeFrameと同じメンバを持ちます．
		///	</summary>
		/// <remarks>
		///		<para>このフレームはグラデーションや枠線の描画を行います．</para>
		///		<para>グラデーションの開始色だけ指定することで単色描画になります．</para>
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// GradationFrameをnewで確保してグラデーションを白→黒，枠線を青に設定する．
		///		GradationFrame* Grad = new GradationFrame();
		///		Grad->StartGradColor = Color::Color(ColorList::White);
		///		Grad->EndGradColor = Color::Color(ColorList::Black);
		///		Grad->StartGradColor = Color::Color(ColorList::Black);
		///		</code>
		/// </example>
		class GradationFrame : public EdgeFrame
		{
		public:
			///	<summary>
			///		枠線の色を指定する．
			///	</summary>
			/// <remarks>
			///		Color::Transparentが指定されている場合枠線を描画しません．
			/// </remarks>
			Color					BorderColor;
			///	<summary>
			///		グラデーション開始色を指定する．
			///	</summary>
			/// <remarks>
			///		Color::Transparentが指定されている場合グラデーションを描画しません．
			/// </remarks>
			Color					StartGradColor;
			///	<summary>
			///		グラデーション終了色を指定する．
			///	</summary>
			/// <remarks>
			///		Color::Transparentが指定されている場合StartGradColorの色で塗りつぶします．
			/// </remarks>
			Color					EndGradColor;
			///	<summary>
			///		コンストラクタ
			///	</summary>
									GradationFrame(){}
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual					~GradationFrame(){}
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String	ToString() const;
		private:
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void			_DrawThisFrame() const;
		};

		///	<summary>
		///		画像ファイルを読み込んで描画するフレーム．
		///	</summary>
		/// <remarks>
		///		<para>このフレームは画像ファイルを読み込み，描画を行います．</para>
		///		<para>画像を途中で差し替える場合はExchangePictureを使用します．</para>
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// PictureFrameをnewで確保して，「画像001」というファイルを読み込む．
		///		PictureFrame* Pict = new PictureFrame("画像001.png");
		///		</code>
		/// </example>
		class PictureFrame : virtual public __FrameBase
		{
		public:
			///	<summary>
			///		グラデーション・枠線を描画するフレームを作成する際に
			///		実行される関数．
			///	</summary>
			/// <param name = "ImgPath">
			///		表示する画像ファイルの場所．
			/// </param>
							PictureFrame(Value::String ImgPath = _T(""));
			///	<summary>
			///		画像ファイルの場所．
			///	</summary>
			Value::String	Path;
			/// <summary>
			///		このフレームのαブレンド．
			/// </summary>
			/// <remarks>
			///		255で不透明．0で透明．
			/// </remarks>
			int				Alpha;
			/// <summary>
			///		描画を反転するかどうか．
			/// </summary>
			bool			Turned;
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual			~PictureFrame();
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String
							ToString() const;
		protected:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void	_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void	_DrawThisFrame() const;
			///	<summary>
			///		画像ファイルのハンドル
			///	</summary>
			int				_PictureHandle;
			///	<summary>
			///		画像ファイルの場所
			///	</summary>
			Value::String	_PicturePath;
		};

		///	<summary>
		///		タイル状，拡大表示が表示可能なPictureFrame.
		///	</summary>
		/// <remarks>
		///		Width, Heightの値を設定することで読み込んだ画像をタイル状に，あるいは拡大表示して表示します．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// TilePictureFrameをnewで確保して，600/400の領域にタイル表示させる．
		///		TilePictureFrame* TlPict = new TilePictureFrame("画像.png");
		///		TlPict->Width = 600;
		///		TlPict->Height = 400;
		///		TlPict->SpecifyWithParcent = false;
		///		</code>
		/// </example>
		class AreaPictureFrame : virtual public PictureFrame, virtual public EdgeFrame
		{
		public:
			///	<summary>
			///		タイル状に画像を描画するフレームを作成する際に
			///		実行される関数．
			///	</summary>
			/// <param name = "ImgPath">
			///		表示する画像ファイルの場所．
			/// </param>
							AreaPictureFrame(Value::String ImgPath = _T(""));
			/// <summary>
			///		このフレームのタイル模様のX座標．
			/// </summary>
			/// <remark>
			///		この値を増加させるとタイルの模様がX方向に移動します．
			///	</remark>
			/// <example>
			///		使用例: 
			///		<code>
			///		// タイルの模様を右下に移動させていく．
			///		static TilePictureFrame* TlPict = new TilePictureFrame("格子.png");
			///		TlPict->TileX++;
			///		TlPict->TileY++;
			///		</code>
			/// </example>
			int				TileX;
			/// <summary>
			///		このフレームのタイル模様のY座標．
			/// </summary>
			/// <remark>
			///		この値を増加させるとタイルの模様がY方向に移動します．
			///	</remark>
			/// <example>
			///		TilePictureFrame::TileXの例をご覧ください．
			/// </example>
			int				TileY;
			/// <summary>
			///		引き伸ばして表示するかどうか．
			/// </summary>
			/// <remarks>
			///		枠内部の部分を引き伸ばして表示するか，それとも繰り返し描画するかを選択します．
			///		例としては，グラデーションを使用している場合はtrue，タイル模様ならばfalseなどです．
			///		このプロパティをtrueに指定すると，TileX, TileYは無視されます．
			/// </remarks>
			bool			StretchDraw;
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String
							ToString() const;
		private:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void	_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void	_DrawThisFrame() const;
		};

		///	<summary>
		///		動画再生を行うフレーム．
		///	</summary>
		/// <remarks>
		///		<para>再生開始時にPlay()関数を呼び出すことで再生可能です．</para>
		///		<para>対応拡張子は avi, mpg, gifなどです．</para>
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		MovieFrame* Mov = new MovieFrame("Action.gif");
		///		Mov->Play();	// 再生開始
		///		</code>
		/// </example>
		class MovieFrame : public PictureFrame
		{
		public:
			///	<summary>
			///		動画を描画するフレームを作成する際に実行される関数．
			///	</summary>
			/// <param name = "ImgPath">
			///		表示する画像ファイルの場所．
			/// </param>
							MovieFrame(Value::String MovPath = _T(""));
			///	<summary>
			///		再生時の音量．0(最小)～10000(最大)で指定する．
			///	</summary>
			UINT			Volume;
			///	<summary>
			///		動画の再生を開始する．
			///	</summary>
			void			Play();
			///	<summary>
			///		動画の再生を一時的に中止する．
			///	</summary>
			void			Pause();
			///	<summary>
			///		動画の再生を中止する．
			///	</summary>
			void			Stop();
			///	<summary>
			///		動画の再生状態を取得する．
			///		戻り値と MoviePlayState クラスの値とを比較演算することで判定する．
			///	</summary>
			/// <example>
			///		使用例: 
			///		<code>
			///		MovieFrame* Mov = new MovieFrame("Action.gif");
			///		if( Mov->State() == MoviePlayState::Stop ){	// もし停止しているなら
			///			Mov->Play();
			///		}
			///		</code>
			/// </example>
			UINT			State();
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String
							ToString() const;
		private:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void	_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void	_DrawThisFrame() const;
		};

		///	<summary>
		///		文字列を描画するフレーム．
		///	</summary>
		/// <remarks>
		///		Textプロパティの値を変更することで描画する文字を変更します．
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// TextFrameをnewで確保して，色を青にして，自身の情報を描画させる．
		///		TextFrame* Str = new TextFrame();
		///		Str->Color = ColorList::Color(Color::Blue);
		///		Str->Text = Str->ToString();
		///		</code>
		/// </example>
		class TextFrame : public __FrameBase
		{
		public:
			///	<summary>
			///		描画する文字列．
			///	</summary>
			Value::String			Text;
			///	<summary>
			///		描画するのに使用するフォントのデータ．
			///		描画色の情報もここに含まれます．
			///	</summary>
			Font					TextFont;
			/// <summary>
			///		<para>文字送りを行うかどうか．標準ではfalse．</para>
			///		<para>文字送りを行う状態でも全文字送りが終了した段階でfalseに変更される．</para>
			/// </summary>
			bool					TextAdvance;
			/// <summary>
			///		<para>文字送り用のタイマー．初期状態では文字送りをしない．</para>
			///		<para>値が1000増える度に1文字表示する．</para>
			/// </summary>
			Value::Timer			TextTimer;
			/// <summary>
			///		フレームの状態を文字列で返却する．
			/// </summary>
			virtual Value::String	ToString() const;
			///	<summary>
			///		グラデーション・枠線を描画するフレームを作成する際に
			///		実行される関数．
			///	</summary>
			/// <param name = "String">
			///		描画する文字列．
			/// </param>
									TextFrame(Value::String String = _T(""));
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual					~TextFrame(){}
		private:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void			_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void			_DrawThisFrame() const;
		protected:
			///	<summary>
			///		描画する文字(TextからTimerなどを考慮した文字)．
			///	</summary>
			Value::String			_DrawText;
			///	<summary>
			///		描画する文字を取得（Timer考慮）．
			///	</summary>
			virtual void			_SetDrawString();
		};
	}
}
