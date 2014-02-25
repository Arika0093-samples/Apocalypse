// --------------------------------------------------------
//	apcDrawing.h
// --------------------------------------------------------
//	�`��֘A�̃N���X���L�ڂ���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <Windows.h>
#include <dxlib/DxLib.h>
#include <include/apcClassBase.hpp>
#include <include/apcCollection.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Draw)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Draw
	{
		///	<summary>
		///		�t���[���̈ʒu�������萔���`�����񋓌^�D
		///	</summary>
		///	<remark>
		///		C++�̐�����enum���O�ɒu���ƃT�W�F�X�g�����������̂�
		///		�N���X�̓����ɉB�����Ă��܂��D
		///	</remark>
		class FramePosition : public Base::__ApcEnumeration
		{
		public:
			///	<summary>
			///		�t���[���̈ʒu�������萔�����[�����񋓌^�D
			///	</summary>
			enum				_FramePosition
			{
				///	<summary>
				///		����������D
				///	</summary>
				TopLeft,
				///	<summary>
				///		������������D
				///	</summary>
				TopCenter,
				///	<summary>
				///		�E��������D
				///	</summary>
				TopRight,
				///	<summary>
				///		�������������D
				///	</summary>
				MiddleLeft,
				///	<summary>
				///		���S�������D
				///	</summary>
				MiddleCenter,
				///	<summary>
				///		�E�����������D
				///	</summary>
				MiddleRight,
				///	<summary>
				///		�����������D
				///	</summary>
				BottomLeft,
				///	<summary>
				///		�������������D
				///	</summary>
				BottomCenter,
				///	<summary>
				///		�E���������D
				///	</summary>
				BottomRight,
				///	<summary>
				///		�W���̈ʒu�������D
				///	</summary>
				Default			= MiddleCenter,
			};
		};

		///	<summary>
		///		�`��̎�ނ������萔���`�����񋓌^�D
		///	</summary>
		///	<remark>
		///		C++�̐�����enum���O�ɒu���ƃT�W�F�X�g�����������̂�
		///		�N���X�̓����ɉB�����Ă��܂��D
		///	</remark>
		class FrameDrawMode : public Base::__ApcEnumeration
		{
		public:
			///	<summary>
			///		�`��̎�ނ������萔���`�����񋓌^�D
			///	</summary>
			enum				_FrameDrawMode
			{
				///	<summary>
				///		�l�A���X�g�l�C�o�[�@�ŕ`��
				///	</summary>
				Nearest		= DX_DRAWMODE_NEAREST,
				///	<summary>
				///		�o�C���j�A�@�ŕ`�悷��
				///	</summary>
				Bilinear	= DX_DRAWMODE_BILINEAR,
				///	<summary>
				///		�ٕ����t�B���^�����O�@�ŕ`�悷��
				///	</summary>
				Anisotropic	= DX_DRAWMODE_ANISOTROPIC,
				///	<summary>
				///		����ȊO
				///	</summary>
				Other		= DX_DRAWMODE_OTHER,
			};
		};

		///	<summary>
		///		�F���Ǘ�����N���X
		///	</summary>
		/// <remarks>
		///		<para>GradationFrame��TextFrame�Ŏg�p����F�f�[�^���擾�E�Ǘ����܂��D</para>
		///		<para>�F���X�g�ɂ��Ă�Color::ColorList���Q�Ƃ��Ă��������D</para>
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// �����x50%�̃I�����W�F���擾���܂�(0x80 = 128 = 255/2)
		///		Color::Color(0x80, 0xFF, 0x80, 0x00);
		///		// �����x0%�̔��F���擾���܂�
		///		Color::Color(Color::White);
		///		// �����x10%�̐ԐF���擾���܂�(0xE5 = 229 = 255*0.9)
		///		Color::Color(Color::Red, 0xE5);
		///		// �����F���擾���܂�
		///		Color::Color(Color::Transparent);
		///		</code>
		/// </example>
		class Color : public Base::__ApcBase
		{
		public:
			///	<summary>
			///		�F���X�g�f�[�^�̗񋓑�
			///	</summary>
			enum			_ColorList
			{
				/// <summary>
				/// AliceBlue(#F0F8FF)�̐F���擾���܂��D
				/// </summary>
				AliceBlue = 0xFFF0F8FF,
				/// <summary>
				/// AntiqueWhite(#FAEBD7)�̐F���擾���܂��D
				/// </summary>
				AntiqueWhite = 0xFFFAEBD7,
				/// <summary>
				/// Aqua(#00FFFF)�̐F���擾���܂��D
				/// </summary>
				Aqua = 0xFF00FFFF,
				/// <summary>
				/// Aquamarine(#7FFFD4)�̐F���擾���܂��D
				/// </summary>
				Aquamarine = 0xFF7FFFD4,
				/// <summary>
				/// Azure(#F0FFFF)�̐F���擾���܂��D
				/// </summary>
				Azure = 0xFFF0FFFF,
				/// <summary>
				/// Beige(#F5F5DC)�̐F���擾���܂��D
				/// </summary>
				Beige = 0xFFF5F5DC,
				/// <summary>
				/// Bisque(#FFE4C4)�̐F���擾���܂��D
				/// </summary>
				Bisque = 0xFFFFE4C4,
				/// <summary>
				/// Black(#000000)�̐F���擾���܂��D
				/// </summary>
				Black = 0xFF000000,
				/// <summary>
				/// BlanchedAlmond(#FFEBCD)�̐F���擾���܂��D
				/// </summary>
				BlanchedAlmond = 0xFFFFEBCD,
				/// <summary>
				/// Blue(#0000FF)�̐F���擾���܂��D
				/// </summary>
				Blue = 0xFF0000FF,
				/// <summary>
				/// BlueViolet(#8A2BE2)�̐F���擾���܂��D
				/// </summary>
				BlueViolet = 0xFF8A2BE2,
				/// <summary>
				/// Brown(#A52A2A)�̐F���擾���܂��D
				/// </summary>
				Brown = 0xFFA52A2A,
				/// <summary>
				/// BurlyWood(#DEB887)�̐F���擾���܂��D
				/// </summary>
				BurlyWood = 0xFFDEB887,
				/// <summary>
				/// CadetBlue(#5F9EA0)�̐F���擾���܂��D
				/// </summary>
				CadetBlue = 0xFF5F9EA0,
				/// <summary>
				/// Chartreuse(#7FFF00)�̐F���擾���܂��D
				/// </summary>
				Chartreuse = 0xFF7FFF00,
				/// <summary>
				/// Chocolate(#D2691E)�̐F���擾���܂��D
				/// </summary>
				Chocolate = 0xFFD2691E,
				/// <summary>
				/// Coral(#FF7F50)�̐F���擾���܂��D
				/// </summary>
				Coral = 0xFFFF7F50,
				/// <summary>
				/// CornflowerBlue(#6495ED)�̐F���擾���܂��D
				/// </summary>
				CornflowerBlue = 0xFF6495ED,
				/// <summary>
				/// Cornsilk(#FFF8DC)�̐F���擾���܂��D
				/// </summary>
				Cornsilk = 0xFFFFF8DC,
				/// <summary>
				/// Crimson(#DC143C)�̐F���擾���܂��D
				/// </summary>
				Crimson = 0xFFDC143C,
				/// <summary>
				/// Cyan(#00FFFF)�̐F���擾���܂��D
				/// </summary>
				Cyan = 0xFF00FFFF,
				/// <summary>
				/// DarkBlue(#00008B)�̐F���擾���܂��D
				/// </summary>
				DarkBlue = 0xFF00008B,
				/// <summary>
				/// DarkCyan(#008B8B)�̐F���擾���܂��D
				/// </summary>
				DarkCyan = 0xFF008B8B,
				/// <summary>
				/// DarkGoldenrod(#B8860B)�̐F���擾���܂��D
				/// </summary>
				DarkGoldenrod = 0xFFB8860B,
				/// <summary>
				/// DarkGray(#A9A9A9)�̐F���擾���܂��D
				/// </summary>
				DarkGray = 0xFFA9A9A9,
				/// <summary>
				/// DarkGreen(#006400)�̐F���擾���܂��D
				/// </summary>
				DarkGreen = 0xFF006400,
				/// <summary>
				/// DarkKhaki(#BDB76B)�̐F���擾���܂��D
				/// </summary>
				DarkKhaki = 0xFFBDB76B,
				/// <summary>
				/// DarkMagenta(#8B008B)�̐F���擾���܂��D
				/// </summary>
				DarkMagenta = 0xFF8B008B,
				/// <summary>
				/// DarkOliveGreen(#556B2F)�̐F���擾���܂��D
				/// </summary>
				DarkOliveGreen = 0xFF556B2F,
				/// <summary>
				/// DarkOrange(#FF8C00)�̐F���擾���܂��D
				/// </summary>
				DarkOrange = 0xFFFF8C00,
				/// <summary>
				/// DarkOrchid(#9932CC)�̐F���擾���܂��D
				/// </summary>
				DarkOrchid = 0xFF9932CC,
				/// <summary>
				/// DarkRed(#8B0000)�̐F���擾���܂��D
				/// </summary>
				DarkRed = 0xFF8B0000,
				/// <summary>
				/// DarkSalmon(#E9967A)�̐F���擾���܂��D
				/// </summary>
				DarkSalmon = 0xFFE9967A,
				/// <summary>
				/// DarkSeaGreen(#8FBC8B)�̐F���擾���܂��D
				/// </summary>
				DarkSeaGreen = 0xFF8FBC8B,
				/// <summary>
				/// DarkSlateBlue(#483D8B)�̐F���擾���܂��D
				/// </summary>
				DarkSlateBlue = 0xFF483D8B,
				/// <summary>
				/// DarkSlateGray(#2F4F4F)�̐F���擾���܂��D
				/// </summary>
				DarkSlateGray = 0xFF2F4F4F,
				/// <summary>
				/// DarkTurquoise(#00CED1)�̐F���擾���܂��D
				/// </summary>
				DarkTurquoise = 0xFF00CED1,
				/// <summary>
				/// DarkViolet(#9400D3)�̐F���擾���܂��D
				/// </summary>
				DarkViolet = 0xFF9400D3,
				/// <summary>
				/// DeepPink(#FF1493)�̐F���擾���܂��D
				/// </summary>
				DeepPink = 0xFFFF1493,
				/// <summary>
				/// DeepSkyBlue(#00BFFF)�̐F���擾���܂��D
				/// </summary>
				DeepSkyBlue = 0xFF00BFFF,
				/// <summary>
				/// DimGray(#696969)�̐F���擾���܂��D
				/// </summary>
				DimGray = 0xFF696969,
				/// <summary>
				/// DodgerBlue(#1E90FF)�̐F���擾���܂��D
				/// </summary>
				DodgerBlue = 0xFF1E90FF,
				/// <summary>
				/// Firebrick(#B22222)�̐F���擾���܂��D
				/// </summary>
				Firebrick = 0xFFB22222,
				/// <summary>
				/// FloralWhite(#FFFAF0)�̐F���擾���܂��D
				/// </summary>
				FloralWhite = 0xFFFFFAF0,
				/// <summary>
				/// ForestGreen(#228B22)�̐F���擾���܂��D
				/// </summary>
				ForestGreen = 0xFF228B22,
				/// <summary>
				/// Fuchsia(#FF00FF)�̐F���擾���܂��D
				/// </summary>
				Fuchsia = 0xFFFF00FF,
				/// <summary>
				/// Gainsboro(#DCDCDC)�̐F���擾���܂��D
				/// </summary>
				Gainsboro = 0xFFDCDCDC,
				/// <summary>
				/// GhostWhite(#F8F8FF)�̐F���擾���܂��D
				/// </summary>
				GhostWhite = 0xFFF8F8FF,
				/// <summary>
				/// Gold(#FFD700)�̐F���擾���܂��D
				/// </summary>
				Gold = 0xFFFFD700,
				/// <summary>
				/// Goldenrod(#DAA520)�̐F���擾���܂��D
				/// </summary>
				Goldenrod = 0xFFDAA520,
				/// <summary>
				/// Gray(#808080)�̐F���擾���܂��D
				/// </summary>
				Gray = 0xFF808080,
				/// <summary>
				/// Green(#008000)�̐F���擾���܂��D
				/// </summary>
				Green = 0xFF008000,
				/// <summary>
				/// GreenYellow(#ADFF2F)�̐F���擾���܂��D
				/// </summary>
				GreenYellow = 0xFFADFF2F,
				/// <summary>
				/// Honeydew(#F0FFF0)�̐F���擾���܂��D
				/// </summary>
				Honeydew = 0xFFF0FFF0,
				/// <summary>
				/// HotPink(#FF69B4)�̐F���擾���܂��D
				/// </summary>
				HotPink = 0xFFFF69B4,
				/// <summary>
				/// IndianRed(#CD5C5C)�̐F���擾���܂��D
				/// </summary>
				IndianRed = 0xFFCD5C5C,
				/// <summary>
				/// Indigo(#4B0082)�̐F���擾���܂��D
				/// </summary>
				Indigo = 0xFF4B0082,
				/// <summary>
				/// Ivory(#FFFFF0)�̐F���擾���܂��D
				/// </summary>
				Ivory = 0xFFFFFFF0,
				/// <summary>
				/// Khaki(#F0E68C)�̐F���擾���܂��D
				/// </summary>
				Khaki = 0xFFF0E68C,
				/// <summary>
				/// Lavender(#E6E6FA)�̐F���擾���܂��D
				/// </summary>
				Lavender = 0xFFE6E6FA,
				/// <summary>
				/// LavenderBlush(#FFF0F5)�̐F���擾���܂��D
				/// </summary>
				LavenderBlush = 0xFFFFF0F5,
				/// <summary>
				/// LawnGreen(#7CFC00)�̐F���擾���܂��D
				/// </summary>
				LawnGreen = 0xFF7CFC00,
				/// <summary>
				/// LemonChiffon(#FFFACD)�̐F���擾���܂��D
				/// </summary>
				LemonChiffon = 0xFFFFFACD,
				/// <summary>
				/// LightBlue(#ADD8E6)�̐F���擾���܂��D
				/// </summary>
				LightBlue = 0xFFADD8E6,
				/// <summary>
				/// LightCoral(#F08080)�̐F���擾���܂��D
				/// </summary>
				LightCoral = 0xFFF08080,
				/// <summary>
				/// LightCyan(#E0FFFF)�̐F���擾���܂��D
				/// </summary>
				LightCyan = 0xFFE0FFFF,
				/// <summary>
				/// LightGoldenrodYellow(#FAFAD2)�̐F���擾���܂��D
				/// </summary>
				LightGoldenrodYellow = 0xFFFAFAD2,
				/// <summary>
				/// LightGreen(#90EE90)�̐F���擾���܂��D
				/// </summary>
				LightGreen = 0xFF90EE90,
				/// <summary>
				/// LightGray(#D3D3D3)�̐F���擾���܂��D
				/// </summary>
				LightGray = 0xFFD3D3D3,
				/// <summary>
				/// LightPink(#FFB6C1)�̐F���擾���܂��D
				/// </summary>
				LightPink = 0xFFFFB6C1,
				/// <summary>
				/// LightSalmon(#FFA07A)�̐F���擾���܂��D
				/// </summary>
				LightSalmon = 0xFFFFA07A,
				/// <summary>
				/// LightSeaGreen(#20B2AA)�̐F���擾���܂��D
				/// </summary>
				LightSeaGreen = 0xFF20B2AA,
				/// <summary>
				/// LightSkyBlue(#87CEFA)�̐F���擾���܂��D
				/// </summary>
				LightSkyBlue = 0xFF87CEFA,
				/// <summary>
				/// LightSlateGray(#778899)�̐F���擾���܂��D
				/// </summary>
				LightSlateGray = 0xFF778899,
				/// <summary>
				/// LightSteelBlue(#B0C4DE)�̐F���擾���܂��D
				/// </summary>
				LightSteelBlue = 0xFFB0C4DE,
				/// <summary>
				/// LightYellow(#FFFFE0)�̐F���擾���܂��D
				/// </summary>
				LightYellow = 0xFFFFFFE0,
				/// <summary>
				/// Lime(#00FF00)�̐F���擾���܂��D
				/// </summary>
				Lime = 0xFF00FF00,
				/// <summary>
				/// LimeGreen(#32CD32)�̐F���擾���܂��D
				/// </summary>
				LimeGreen = 0xFF32CD32,
				/// <summary>
				/// Linen(#FAF0E6)�̐F���擾���܂��D
				/// </summary>
				Linen = 0xFFFAF0E6,
				/// <summary>
				/// Magenta(#FF00FF)�̐F���擾���܂��D
				/// </summary>
				Magenta = 0xFFFF00FF,
				/// <summary>
				/// Maroon(#800000)�̐F���擾���܂��D
				/// </summary>
				Maroon = 0xFF800000,
				/// <summary>
				/// MediumAquamarine(#66CDAA)�̐F���擾���܂��D
				/// </summary>
				MediumAquamarine = 0xFF66CDAA,
				/// <summary>
				/// MediumBlue(#0000CD)�̐F���擾���܂��D
				/// </summary>
				MediumBlue = 0xFF0000CD,
				/// <summary>
				/// MediumOrchid(#BA55D3)�̐F���擾���܂��D
				/// </summary>
				MediumOrchid = 0xFFBA55D3,
				/// <summary>
				/// MediumPurple(#9370DB)�̐F���擾���܂��D
				/// </summary>
				MediumPurple = 0xFF9370DB,
				/// <summary>
				/// MediumSeaGreen(#3CB371)�̐F���擾���܂��D
				/// </summary>
				MediumSeaGreen = 0xFF3CB371,
				/// <summary>
				/// MediumSlateBlue(#7B68EE)�̐F���擾���܂��D
				/// </summary>
				MediumSlateBlue = 0xFF7B68EE,
				/// <summary>
				/// MediumSpringGreen(#00FA9A)�̐F���擾���܂��D
				/// </summary>
				MediumSpringGreen = 0xFF00FA9A,
				/// <summary>
				/// MediumTurquoise(#48D1CC)�̐F���擾���܂��D
				/// </summary>
				MediumTurquoise = 0xFF48D1CC,
				/// <summary>
				/// MediumVioletRed(#C71585)�̐F���擾���܂��D
				/// </summary>
				MediumVioletRed = 0xFFC71585,
				/// <summary>
				/// MidnightBlue(#191970)�̐F���擾���܂��D
				/// </summary>
				MidnightBlue = 0xFF191970,
				/// <summary>
				/// MintCream(#F5FFFA)�̐F���擾���܂��D
				/// </summary>
				MintCream = 0xFFF5FFFA,
				/// <summary>
				/// MistyRose(#FFE4E1)�̐F���擾���܂��D
				/// </summary>
				MistyRose = 0xFFFFE4E1,
				/// <summary>
				/// Moccasin(#FFE4B5)�̐F���擾���܂��D
				/// </summary>
				Moccasin = 0xFFFFE4B5,
				/// <summary>
				/// NavajoWhite(#FFDEAD)�̐F���擾���܂��D
				/// </summary>
				NavajoWhite = 0xFFFFDEAD,
				/// <summary>
				/// Navy(#000080)�̐F���擾���܂��D
				/// </summary>
				Navy = 0xFF000080,
				/// <summary>
				/// OldLace(#FDF5E6)�̐F���擾���܂��D
				/// </summary>
				OldLace = 0xFFFDF5E6,
				/// <summary>
				/// Olive(#808000)�̐F���擾���܂��D
				/// </summary>
				Olive = 0xFF808000,
				/// <summary>
				/// OliveDrab(#6B8E23)�̐F���擾���܂��D
				/// </summary>
				OliveDrab = 0xFF6B8E23,
				/// <summary>
				/// Orange(#FFA500)�̐F���擾���܂��D
				/// </summary>
				Orange = 0xFFFFA500,
				/// <summary>
				/// OrangeRed(#FF4500)�̐F���擾���܂��D
				/// </summary>
				OrangeRed = 0xFFFF4500,
				/// <summary>
				/// Orchid(#DA70D6)�̐F���擾���܂��D
				/// </summary>
				Orchid = 0xFFDA70D6,
				/// <summary>
				/// PaleGoldenrod(#EEE8AA)�̐F���擾���܂��D
				/// </summary>
				PaleGoldenrod = 0xFFEEE8AA,
				/// <summary>
				/// PaleGreen(#98FB98)�̐F���擾���܂��D
				/// </summary>
				PaleGreen = 0xFF98FB98,
				/// <summary>
				/// PaleTurquoise(#AFEEEE)�̐F���擾���܂��D
				/// </summary>
				PaleTurquoise = 0xFFAFEEEE,
				/// <summary>
				/// PaleVioletRed(#DB7093)�̐F���擾���܂��D
				/// </summary>
				PaleVioletRed = 0xFFDB7093,
				/// <summary>
				/// PapayaWhip(#FFEFD5)�̐F���擾���܂��D
				/// </summary>
				PapayaWhip = 0xFFFFEFD5,
				/// <summary>
				/// PeachPuff(#FFDAB9)�̐F���擾���܂��D
				/// </summary>
				PeachPuff = 0xFFFFDAB9,
				/// <summary>
				/// Peru(#CD853F)�̐F���擾���܂��D
				/// </summary>
				Peru = 0xFFCD853F,
				/// <summary>
				/// Pink(#FFC0CB)�̐F���擾���܂��D
				/// </summary>
				Pink = 0xFFFFC0CB,
				/// <summary>
				/// Plum(#DDA0DD)�̐F���擾���܂��D
				/// </summary>
				Plum = 0xFFDDA0DD,
				/// <summary>
				/// PowderBlue(#B0E0E6)�̐F���擾���܂��D
				/// </summary>
				PowderBlue = 0xFFB0E0E6,
				/// <summary>
				/// Purple(#800080)�̐F���擾���܂��D
				/// </summary>
				Purple = 0xFF800080,
				/// <summary>
				/// Red(#FF0000)�̐F���擾���܂��D
				/// </summary>
				Red = 0xFFFF0000,
				/// <summary>
				/// RosyBrown(#BC8F8F)�̐F���擾���܂��D
				/// </summary>
				RosyBrown = 0xFFBC8F8F,
				/// <summary>
				/// RoyalBlue(#4169E1)�̐F���擾���܂��D
				/// </summary>
				RoyalBlue = 0xFF4169E1,
				/// <summary>
				/// SaddleBrown(#8B4513)�̐F���擾���܂��D
				/// </summary>
				SaddleBrown = 0xFF8B4513,
				/// <summary>
				/// Salmon(#FA8072)�̐F���擾���܂��D
				/// </summary>
				Salmon = 0xFFFA8072,
				/// <summary>
				/// SandyBrown(#F4A460)�̐F���擾���܂��D
				/// </summary>
				SandyBrown = 0xFFF4A460,
				/// <summary>
				/// SeaGreen(#2E8B57)�̐F���擾���܂��D
				/// </summary>
				SeaGreen = 0xFF2E8B57,
				/// <summary>
				/// SeaShell(#FFF5EE)�̐F���擾���܂��D
				/// </summary>
				SeaShell = 0xFFFFF5EE,
				/// <summary>
				/// Sienna(#A0522D)�̐F���擾���܂��D
				/// </summary>
				Sienna = 0xFFA0522D,
				/// <summary>
				/// Silver(#C0C0C0)�̐F���擾���܂��D
				/// </summary>
				Silver = 0xFFC0C0C0,
				/// <summary>
				/// SkyBlue(#87CEEB)�̐F���擾���܂��D
				/// </summary>
				SkyBlue = 0xFF87CEEB,
				/// <summary>
				/// SlateBlue(#6A5ACD)�̐F���擾���܂��D
				/// </summary>
				SlateBlue = 0xFF6A5ACD,
				/// <summary>
				/// SlateGray(#708090)�̐F���擾���܂��D
				/// </summary>
				SlateGray = 0xFF708090,
				/// <summary>
				/// Snow(#FFFAFA)�̐F���擾���܂��D
				/// </summary>
				Snow = 0xFFFFFAFA,
				/// <summary>
				/// SpringGreen(#00FF7F)�̐F���擾���܂��D
				/// </summary>
				SpringGreen = 0xFF00FF7F,
				/// <summary>
				/// SteelBlue(#4682B4)�̐F���擾���܂��D
				/// </summary>
				SteelBlue = 0xFF4682B4,
				/// <summary>
				/// Tan(#D2B48C)�̐F���擾���܂��D
				/// </summary>
				Tan = 0xFFD2B48C,
				/// <summary>
				/// Teal(#008080)�̐F���擾���܂��D
				/// </summary>
				Teal = 0xFF008080,
				/// <summary>
				/// Thistle(#D8BFD8)�̐F���擾���܂��D
				/// </summary>
				Thistle = 0xFFD8BFD8,
				/// <summary>
				/// Tomato(#FF6347)�̐F���擾���܂��D
				/// </summary>
				Tomato = 0xFFFF6347,
				/// <summary>
				/// Transparent(�����F)�̐F���擾���܂��D
				/// </summary>
				Transparent = 0x00FFFFFF,
				/// <summary>
				/// Turquoise(#40E0D0)�̐F���擾���܂��D
				/// </summary>
				Turquoise = 0xFF40E0D0,
				/// <summary>
				/// Violet(#EE82EE)�̐F���擾���܂��D
				/// </summary>
				Violet = 0xFFEE82EE,
				/// <summary>
				/// Wheat(#F5DEB3)�̐F���擾���܂��D
				/// </summary>
				Wheat = 0xFFF5DEB3,
				/// <summary>
				/// White(#FFFFFF)�̐F���擾���܂��D
				/// </summary>
				White = 0xFFFFFFFF,
				/// <summary>
				/// WhiteSmoke(#F5F5F5)�̐F���擾���܂��D
				/// </summary>
				WhiteSmoke = 0xFFF5F5F5,
				/// <summary>
				/// Yellow(#FFFF00)�̐F���擾���܂��D
				/// </summary>
				Yellow = 0xFFFFFF00,
				/// <summary>
				/// YellowGreen(#9ACD32)�̐F���擾���܂��D
				/// </summary>
				YellowGreen = 0xFF9ACD32,
			};
			/// <summary>
			///		��̐F�f�[�^���쐬����i�����ɉ����w�肵�Ȃ��j�D
			/// </summary>
							Color();
			/// <summary>
			///		�F�f�[�^���쐬����iDx���C�u������GetColor�Ɠ����j
			/// </summary>
			/// <param name = "R">
			///		�Ԃ̋��x�D0����255�܂ł͈̔͂Ŏw�肷��D
			/// </param>
			/// <param name = "G">
			///		�΂̋��x�D0����255�܂ł͈̔͂Ŏw�肷��D
			/// </param>
			/// <param name = "B">
			///		�̋��x�D0����255�܂ł͈̔͂Ŏw�肷��D
			/// </param>
							Color(int Rp, int Gp, int Bp);
			/// <summary>
			///		�F�f�[�^���쐬����
			/// </summary>
			/// <param name = "A">
			///		�����x�D0����255�܂ł͈̔͂Ŏw�肷��D0�œ����D
			/// </param>
			/// <param name = "R">
			///		�Ԃ̋��x�D0����255�܂ł͈̔͂Ŏw�肷��D
			/// </param>
			/// <param name = "G">
			///		�΂̋��x�D0����255�܂ł͈̔͂Ŏw�肷��D
			/// </param>
			/// <param name = "B">
			///		�̋��x�D0����255�܂ł͈̔͂Ŏw�肷��D
			/// </param>
							Color(int Ap, int Rp, int Gp, int Bp);
			/// <summary>
			///		�F�f�[�^���쐬����iHTML���̐F�R�[�h�Łj
			/// </summary>
			/// <param name = "ARGBCode">
			///		�����x�����܂�RGB�R�[�h�D<see cref="_ColorList">ColorList</see>����
			///		��`���ꂽ�l���g�p���邱�Ƃ��\�ł��D
			/// </param>
							Color(_ColorList ARGBCode);
			/// <summary>
			///		�F�f�[�^���쐬����i���u�����h�������Ŏw�肷��j
			/// </summary>
			/// <param name = "RGBCode">
			///		<para>�����x�����܂܂Ȃ�RGB�R�[�h�D�܂܂��ꍇ��������܂��D</para>
			///		<para><see cref="_ColorList">ColorList</see>���Œ�`���ꂽ�l���g�p���邱�Ƃ��\�ł��D</para>
			/// </param>
			/// <param name = "Alpha">
			///		���̐F�̃��u�����h�D
			/// </param>
							Color(_ColorList RGBCode, int Alpha);
			/// <summary>
			///		�F�f�[�^��������
			/// </summary>
			Color&			operator=(const Color &Cr);
			/// <summary>
			///		�F�f�[�^��������
			/// </summary>
			Color&			operator=(const _ColorList ARGBCode);
			/// <summary>
			///		�F�f�[�^���r����
			/// </summary>
			bool			operator==(const Color &Cr) const;
			/// <summary>
			///		�F�f�[�^��NOT��r����
			/// </summary>
			bool			operator!=(const Color &Cr) const;
			/// <summary>
			///		�F�f�[�^���r����֐��D
			/// </summary>
			/// <param name = "Target">
			///		��r����Ώۂ̐F�N���X�D
			/// </param>
			bool			Compare(const Color &Target) const;
			/// <summary>
			///		%�œn���ꂽAlpha��256�i�K�ɕϊ����ĕԋp����D
			/// </summary>
			static int		AlphaFromParcent(double Bs);
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String
							ToString() const;
			///	<summary>
			///		�L���ȐF���ǂ����D
			///	</summary>
			bool			Enable;
			///	<summary>
			///		�F�̓����x�̋��x�D
			///	</summary>
			int				A;
			///	<summary>
			///		�F�̐Ԑ����̋��x�D
			///	</summary>
			int				R;
			///	<summary>
			///		�F�̗ΐ����̋��x�D
			///	</summary>
			int				G;
			///	<summary>
			///		�F�̐����̋��x�D
			///	</summary>
			int				B;
			/// <summary>
			///		�N���X�ɓo�^����Ă���F�f�[�^��ԋp����
			/// </summary>
			inline DWORD	_GetColor() const;
			/// <summary>
			///		�N���X�ɓo�^����Ă��铧���x��K�p����
			/// </summary>
			inline void		_AppendAlpha() const;
			/// <summary>
			///		���g�ƑΏۂ̐F����芄���Ńu�����h�������ʂ�Color�̃|�C���^��ԋp����D
			/// </summary>
			/// <param name = "Target">
			///		���g�ƃu�����h����Ώۂ̐F�f�[�^�̃|�C���^�D
			/// </param>
			/// <param name = "Parcent">
			///		�u�����h���銄���D
			/// </param>
			std::shared_ptr<Color>
							_GetColorBlends(const Color &Target, int Parcent) const;
		};

		///	<summary>
		///		�t�H���g�f�[�^���������N���X�D
		///	</summary>
		/// <remarks>
		///		<para>�t�H���g���C�t�H���g�T�C�Y�C�t�H���g�̑����Ȃǂ��Ǘ����܂��D</para>
		///		<para>�W���̃t�H���g���͏������֐��Ŏw�肵���W���t�H���g�ł��D</para>
		/// </remarks>
		class Font : public Base::__ApcBase
		{
		public:
			///	<summary>
			///		�t�H���g�̕`����@���w�肷��D
			///	</summary>
			class			FontType
			{
			public:
				enum		_FontType
				{
					///	<summary>
					///		���ʂɕ`�悷��D
					///	</summary>
					Normal,
					///	<summary>
					///		�A���`�G�C���A�X�������ĕ`�悷��D
					///	</summary>
					Antialiase,
					///	<summary>
					///		�ǎ��ȃA���`�G�C���A�X�������ĕ`�悷��D
					///	</summary>
					AntialiaseHiQuality,
				};
			};
			///	<summary>
			///		�R���X�g���N�^(���w���)
			///	</summary>
							Font();
			///	<summary>
			///		�R���X�g���N�^(�T�C�Y�w���)
			///	</summary>
							Font(int FontSize);
			///	<summary>
			///		�R���X�g���N�^(���O/�T�C�Y�w���)
			///	</summary>
							Font(Value::String FontName, int FontSize);
			///	<summary>
			///		�R���X�g���N�^(���O/�T�C�Y/�����w���)
			///	</summary>
							Font(Value::String FontName, int FontSize, int FontThick);
			///	<summary>
			///		�R���X�g���N�^(���O/�T�C�Y/����/���T�C�Y�w���)
			///	</summary>
							Font(Value::String FontName, int FontSize, int FontThick, int eSize);
			///	<summary>
			///		�R���X�g���N�^(�S���w���)
			///	</summary>
							Font(Value::String FontName, int FontSize, int FontThick, int eSize, FontType::_FontType Type);
			///	<summary>
			///		�f�X�g���N�^
			///	</summary>
			virtual			~Font();
			///	<summary>
			///		�t�H���g���D
			///	</summary>
			Value::String	Name;
			///	<summary>
			///		�t�H���g�T�C�Y�D
			///	</summary>
			int				Size;
			///	<summary>
			///		�t�H���g�̑����D
			///	</summary>
			int				Thick;
			///	<summary>
			///		�`����@�̎�ށDFontType����I������D
			///	</summary>
			FontType::_FontType
							Type;
			///	<summary>
			///		�t�H���g�̉��̑����D
			///	</summary>
			int				EdgeSize;
			///	<summary>
			///		�t�H���g�̐F�D
			///	</summary>
			Color			FontColor;
			///	<summary>
			///		�`�悷�镶���̉��̐F�DColor::Transparent���w�肷��Ɖ���`�悵�܂���D
			///	</summary>
			Color			EdgeColor;
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String
							ToString() const;
			///	<summary>
			///		�t�H���g�n���h�����X�V���邩�ǂ����m�F���C�X�V����K�v������΍X�V����D
			///	</summary>
			void			_ReloadFontHandle();
			///	<summary>
			///		�t�H���g�n���h�����擾����D
			///	</summary>
			int				_GetFontHandle() const;
			///	<summary>
			///		�`���ނ��擾����D
			///	</summary>
			int				_GetFontDrawType() const;
		private:
			///	<summary>
			///		�t�H���g���i�����ۑ��p�j�D
			///	</summary>
			Value::String	_Name;
			///	<summary>
			///		�t�H���g�T�C�Y�i�����ۑ��p�j�D
			///	</summary>
			int				_Size;
			///	<summary>
			///		�t�H���g�̑����i�����ۑ��p�j�D
			///	</summary>
			int				_Thick;
			///	<summary>
			///		�t�H���g�̉��̑����i�����ۑ��p�j�D
			///	</summary>
			int				_Edge;
			///	<summary>
			///		�t�H���g�̎�ށi�����ۑ��p�j�D
			///	</summary>
			FontType::_FontType
							_Type;
			///	<summary>
			///		�t�H���g�̉����L�����ǂ����D
			///	</summary>
			bool			_IsEnableEdge;
			///	<summary>
			///		�t�H���g�n���h��
			///	</summary>
			int				_Handle;
		};
	
		///	<summary>
		///		���ׂẴt���[���̊�ՁD
		///	</summary>
		/// <remarks>
		///		<para>Apocalypse�ł́C�`��Ɋ֘A���邱�Ƃ̓t���[��(Frame)�N���X��</para>
		///		<para>�ւ��ĕ`��E�Ǘ�����܂��D���̃t���[���N���X�̊�Ղ����̃N���X�ł��D</para>
		///		<para>���̃N���X���̂͐����ł��܂���D</para>
		/// </remarks>
		class __FrameBase : public Base::__ApcBase
		{
			/// <summary>
			///		FrameCollection�N���X����͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Collection::__FrameCollection;
			/// <summary>
			///		typedef
			/// </summary>
			typedef				FramePosition::_FramePosition	FPosition;
			typedef				FrameDrawMode::_FrameDrawMode	FDrawMode;
		public:
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual				~__FrameBase();
			/// <summary>
			///		���̃t���[�����L�����ǂ����D
			/// </summary>
			/// <remarks>
			///		<para>�t���[���������ȏꍇ�C���g�Ǝ��g��e�Ɏ��t���[����</para>
			///		<para>�ʒu�ړ��E�`�悪�s���Ȃ��Ȃ�܂��D</para>
			/// </remarks>
			bool				Enable;
			/// <summary>
			///		���̃t���[����`�悷�邩�ǂ����D
			/// </summary>
			/// <remarks>
			///		<para>false�Ɏw�肷��ƃt���[����`�悵�Ȃ��Ȃ�܂��D</para>
			///		<para>Enable�Ƃ̈Ⴂ�́C�q�t���[���ɂ��e�����y�ڂ����ǂ����ł��D</para>
			/// </remarks>
			bool				Visible;
			/// <summary>
			///		���̃t���[���̊�ʒu����̍��W�D
			/// </summary>
			Value::Point		Points;
			/// <summary>
			///		<para>���̃t���[���̕`�揇�ԁD�����قǎ�O�ɕ`�悳���D</para>
			///		<para>0�Ɏw�肷��Ɛe�t���[����Z���W���玩���Ŏw�肳���D</para>
			/// </summary>
			unsigned int		DrawOrder;
			/// <summary>
			///		�ݒu�ʒu�����肷��萔�D
			/// </summary>
			/// <remarks>
			///		<para>�e�t���[���̂ǂ̈ʒu�ɐݒu���邩�����肵�܂��D</para>
			///		<para><see cref="FramePosition">FramePosition</see>�Œ�`���ꂽ�萔���g�p���ĉ������D</para>
			/// </remarks>
			FPosition			Position;
			/// <summary>
			///		���S�ʒu�����肷��萔�D
			/// </summary>
			/// <remarks>
			///		<para>���̃t���[���̒��S���ǂ̈ʒu�ɐݒu���邩�����肷��萔�D</para>
			///		<para><see cref="FramePosition">FramePosition</see>�Œ�`���ꂽ�萔���g�p���ĉ������D</para>
			/// </remarks>
			FPosition			Interpret;
			/// <summary>
			///		�`����@�̎�ށD
			/// </summary>
			/// <remarks>
			///		<see cref="FrameDrawMode">FrameDrawMode</see>�Œ�`���ꂽ�萔���g�p���ĉ������D
			/// </remarks>
			FDrawMode			DrawMode;
			/// <summary>
			///		���̃t���[���̐e�t���[���D
			/// </summary>
			__FrameBase*		Parent;
			/// <summary>
			///		�t���[���̉������擾����
			/// </summary>
			int					GetWidth() const;
			/// <summary>
			///		�t���[���̏c�����擾����
			/// </summary>
			int					GetHeight() const;
			/// <summary>
			///		�t���[���̍���̍��W���擾����
			/// </summary>
			Value::Point		GetLocation() const;
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String
								ToString() const;
		private:
			/// <summary>
			///		���g�̕W����X, Y���W���w�肷��֐��D
			/// </summary>
			void				_SetDefaultPosition();
			/// <summary>
			///		���g�̕W���̏c���Ɖ������w�肷��֐��D���z�֐��ł��D
			/// </summary>
			virtual void		_SetProperties() = 0;
			/// <summary>
			///		���g�̃t���[����`�悷��֐��ł��D���z�֐��ł��D
			/// </summary>
			virtual void		_DrawThisFrame() const = 0;
		protected:
			/// <summary>
			///		���̃t���[����`�悷�鍶��̏ꏊ
			/// </summary>
			Value::Point		_Location;
			/// <summary>
			///		�t���[���̈ʒu���킹���s�����ǂ����D�W����true�D
			/// </summary>
			bool				_AutoAdjustPosition;
			/// <summary>
			///		���̃t���[���̉����D
			/// </summary>
			int					_Width;
			/// <summary>
			///		���̃t���[���̏c���D
			/// </summary>
			int					_Height;
			/// <summary>
			///		�R���X�g���N�^
			/// </summary>
			/// <param name = "fParent">
			///		�e�t���[���D
			/// </param>
								__FrameBase();
		};

		///	<summary>
		///		�����`�悵�Ȃ��t���[���D
		///	</summary>
		/// <remarks>
		///		<para>���̃N���X�́C�����`�悵�Ȃ�����ɁC�����Əc�����w��ł��܂��D</para>
		///		<para>�t���[���̈ʒu�����ȂǂɎg�p���邱�Ƃ��ł��܂��D</para>
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// EdgeFrame��new�Ŋm�ۂ��ĕ���e�t���[����100%�Ɏw�肷��D
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
			///		��(Width, Height)�����Ŏw�肷�邩�ǂ����D
			///	</summary>
			/// <remarks>
			///		true�Ł��w��ɂȂ�܂�(100%�Őe�Ɠ�����)�Dfalse�Ő�Βl�w��ɂȂ�܂��D
			/// </remarks>
			bool				SpecifyWithParcent;
			///	<summary>
			///		�������w�肷��D
			///	</summary>
			int					Width;
			///	<summary>
			///		�c�����w�肷��D
			///	</summary>
			int					Height;
			///	<summary>
			///		�����`�悵�Ȃ��t���[�����쐬����ۂɎ��s�����֐��D
			///	</summary>
								EdgeFrame();
			///	<summary>
			///		�f�X�g���N�^
			///	</summary>
			virtual				~EdgeFrame(){}
		protected:
			///	<summary>
			///		�t���[����`�悷��֐��D���̃t���[���̏ꍇ�͉������Ȃ��D
			///	</summary>
			virtual void		_DrawThisFrame() const {}
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void		_SetProperties();
		};

		///	<summary>
		///		�O���f�[�V�����E�g����`�悷��t���[���DEdgeFrame�Ɠ��������o�������܂��D
		///	</summary>
		/// <remarks>
		///		<para>���̃t���[���̓O���f�[�V������g���̕`����s���܂��D</para>
		///		<para>�O���f�[�V�����̊J�n�F�����w�肷�邱�ƂŒP�F�`��ɂȂ�܂��D</para>
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// GradationFrame��new�Ŋm�ۂ��ăO���f�[�V�����𔒁����C�g����ɐݒ肷��D
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
			///		�g���̐F���w�肷��D
			///	</summary>
			/// <remarks>
			///		Color::Transparent���w�肳��Ă���ꍇ�g����`�悵�܂���D
			/// </remarks>
			Color					BorderColor;
			///	<summary>
			///		�O���f�[�V�����J�n�F���w�肷��D
			///	</summary>
			/// <remarks>
			///		Color::Transparent���w�肳��Ă���ꍇ�O���f�[�V������`�悵�܂���D
			/// </remarks>
			Color					StartGradColor;
			///	<summary>
			///		�O���f�[�V�����I���F���w�肷��D
			///	</summary>
			/// <remarks>
			///		Color::Transparent���w�肳��Ă���ꍇStartGradColor�̐F�œh��Ԃ��܂��D
			/// </remarks>
			Color					EndGradColor;
			///	<summary>
			///		�R���X�g���N�^
			///	</summary>
									GradationFrame(){}
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual					~GradationFrame(){}
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String	ToString() const;
		private:
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void			_DrawThisFrame() const;
		};

		///	<summary>
		///		�摜�t�@�C����ǂݍ���ŕ`�悷��t���[���D
		///	</summary>
		/// <remarks>
		///		<para>���̃t���[���͉摜�t�@�C����ǂݍ��݁C�`����s���܂��D</para>
		///		<para>�摜��r���ō����ւ���ꍇ��ExchangePicture���g�p���܂��D</para>
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// PictureFrame��new�Ŋm�ۂ��āC�u�摜001�v�Ƃ����t�@�C����ǂݍ��ށD
		///		PictureFrame* Pict = new PictureFrame("�摜001.png");
		///		</code>
		/// </example>
		class PictureFrame : virtual public __FrameBase
		{
		public:
			///	<summary>
			///		�O���f�[�V�����E�g����`�悷��t���[�����쐬����ۂ�
			///		���s�����֐��D
			///	</summary>
			/// <param name = "ImgPath">
			///		�\������摜�t�@�C���̏ꏊ�D
			/// </param>
							PictureFrame(Value::String ImgPath = _T(""));
			///	<summary>
			///		�摜�t�@�C���̏ꏊ�D
			///	</summary>
			Value::String	Path;
			/// <summary>
			///		���̃t���[���̃��u�����h�D
			/// </summary>
			/// <remarks>
			///		255�ŕs�����D0�œ����D
			/// </remarks>
			int				Alpha;
			/// <summary>
			///		�`��𔽓]���邩�ǂ����D
			/// </summary>
			bool			Turned;
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual			~PictureFrame();
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String
							ToString() const;
		protected:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void	_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void	_DrawThisFrame() const;
			///	<summary>
			///		�摜�t�@�C���̃n���h��
			///	</summary>
			int				_PictureHandle;
			///	<summary>
			///		�摜�t�@�C���̏ꏊ
			///	</summary>
			Value::String	_PicturePath;
		};

		///	<summary>
		///		�^�C����C�g��\�����\���\��PictureFrame.
		///	</summary>
		/// <remarks>
		///		Width, Height�̒l��ݒ肷�邱�Ƃœǂݍ��񂾉摜���^�C����ɁC���邢�͊g��\�����ĕ\�����܂��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// TilePictureFrame��new�Ŋm�ۂ��āC600/400�̗̈�Ƀ^�C���\��������D
		///		TilePictureFrame* TlPict = new TilePictureFrame("�摜.png");
		///		TlPict->Width = 600;
		///		TlPict->Height = 400;
		///		TlPict->SpecifyWithParcent = false;
		///		</code>
		/// </example>
		class AreaPictureFrame : virtual public PictureFrame, virtual public EdgeFrame
		{
		public:
			///	<summary>
			///		�^�C����ɉ摜��`�悷��t���[�����쐬����ۂ�
			///		���s�����֐��D
			///	</summary>
			/// <param name = "ImgPath">
			///		�\������摜�t�@�C���̏ꏊ�D
			/// </param>
							AreaPictureFrame(Value::String ImgPath = _T(""));
			/// <summary>
			///		���̃t���[���̃^�C���͗l��X���W�D
			/// </summary>
			/// <remark>
			///		���̒l�𑝉�������ƃ^�C���̖͗l��X�����Ɉړ����܂��D
			///	</remark>
			/// <example>
			///		�g�p��: 
			///		<code>
			///		// �^�C���̖͗l���E���Ɉړ������Ă����D
			///		static TilePictureFrame* TlPict = new TilePictureFrame("�i�q.png");
			///		TlPict->TileX++;
			///		TlPict->TileY++;
			///		</code>
			/// </example>
			int				TileX;
			/// <summary>
			///		���̃t���[���̃^�C���͗l��Y���W�D
			/// </summary>
			/// <remark>
			///		���̒l�𑝉�������ƃ^�C���̖͗l��Y�����Ɉړ����܂��D
			///	</remark>
			/// <example>
			///		TilePictureFrame::TileX�̗���������������D
			/// </example>
			int				TileY;
			/// <summary>
			///		�����L�΂��ĕ\�����邩�ǂ����D
			/// </summary>
			/// <remarks>
			///		�g�����̕����������L�΂��ĕ\�����邩�C����Ƃ��J��Ԃ��`�悷�邩��I�����܂��D
			///		��Ƃ��ẮC�O���f�[�V�������g�p���Ă���ꍇ��true�C�^�C���͗l�Ȃ��false�Ȃǂł��D
			///		���̃v���p�e�B��true�Ɏw�肷��ƁCTileX, TileY�͖�������܂��D
			/// </remarks>
			bool			StretchDraw;
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String
							ToString() const;
		private:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void	_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void	_DrawThisFrame() const;
		};

		///	<summary>
		///		����Đ����s���t���[���D
		///	</summary>
		/// <remarks>
		///		<para>�Đ��J�n����Play()�֐����Ăяo�����ƂōĐ��\�ł��D</para>
		///		<para>�Ή��g���q�� avi, mpg, gif�Ȃǂł��D</para>
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		MovieFrame* Mov = new MovieFrame("Action.gif");
		///		Mov->Play();	// �Đ��J�n
		///		</code>
		/// </example>
		class MovieFrame : public PictureFrame
		{
		public:
			///	<summary>
			///		�����`�悷��t���[�����쐬����ۂɎ��s�����֐��D
			///	</summary>
			/// <param name = "ImgPath">
			///		�\������摜�t�@�C���̏ꏊ�D
			/// </param>
							MovieFrame(Value::String MovPath = _T(""));
			///	<summary>
			///		�Đ����̉��ʁD0(�ŏ�)�`10000(�ő�)�Ŏw�肷��D
			///	</summary>
			UINT			Volume;
			///	<summary>
			///		����̍Đ����J�n����D
			///	</summary>
			void			Play();
			///	<summary>
			///		����̍Đ����ꎞ�I�ɒ��~����D
			///	</summary>
			void			Pause();
			///	<summary>
			///		����̍Đ��𒆎~����D
			///	</summary>
			void			Stop();
			///	<summary>
			///		����̍Đ���Ԃ��擾����D
			///		�߂�l�� MoviePlayState �N���X�̒l�Ƃ��r���Z���邱�ƂŔ��肷��D
			///	</summary>
			/// <example>
			///		�g�p��: 
			///		<code>
			///		MovieFrame* Mov = new MovieFrame("Action.gif");
			///		if( Mov->State() == MoviePlayState::Stop ){	// ������~���Ă���Ȃ�
			///			Mov->Play();
			///		}
			///		</code>
			/// </example>
			UINT			State();
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String
							ToString() const;
		private:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void	_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void	_DrawThisFrame() const;
		};

		///	<summary>
		///		�������`�悷��t���[���D
		///	</summary>
		/// <remarks>
		///		Text�v���p�e�B�̒l��ύX���邱�Ƃŕ`�悷�镶����ύX���܂��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// TextFrame��new�Ŋm�ۂ��āC�F��ɂ��āC���g�̏���`�悳����D
		///		TextFrame* Str = new TextFrame();
		///		Str->Color = ColorList::Color(Color::Blue);
		///		Str->Text = Str->ToString();
		///		</code>
		/// </example>
		class TextFrame : public __FrameBase
		{
		public:
			///	<summary>
			///		�`�悷�镶����D
			///	</summary>
			Value::String			Text;
			///	<summary>
			///		�`�悷��̂Ɏg�p����t�H���g�̃f�[�^�D
			///		�`��F�̏��������Ɋ܂܂�܂��D
			///	</summary>
			Font					TextFont;
			/// <summary>
			///		<para>����������s�����ǂ����D�W���ł�false�D</para>
			///		<para>����������s����Ԃł��S�������肪�I�������i�K��false�ɕύX�����D</para>
			/// </summary>
			bool					TextAdvance;
			/// <summary>
			///		<para>��������p�̃^�C�}�[�D������Ԃł͕�����������Ȃ��D</para>
			///		<para>�l��1000������x��1�����\������D</para>
			/// </summary>
			Value::Timer			TextTimer;
			/// <summary>
			///		�t���[���̏�Ԃ𕶎���ŕԋp����D
			/// </summary>
			virtual Value::String	ToString() const;
			///	<summary>
			///		�O���f�[�V�����E�g����`�悷��t���[�����쐬����ۂ�
			///		���s�����֐��D
			///	</summary>
			/// <param name = "String">
			///		�`�悷�镶����D
			/// </param>
									TextFrame(Value::String String = _T(""));
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual					~TextFrame(){}
		private:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void			_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void			_DrawThisFrame() const;
		protected:
			///	<summary>
			///		�`�悷�镶��(Text����Timer�Ȃǂ��l����������)�D
			///	</summary>
			Value::String			_DrawText;
			///	<summary>
			///		�`�悷�镶�����擾�iTimer�l���j�D
			///	</summary>
			virtual void			_SetDrawString();
		};
	}
}
