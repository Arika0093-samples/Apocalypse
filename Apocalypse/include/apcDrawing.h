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
#include <include/apcClassBase.h>
#include <include/apcCollection.h>
#include <include/apxEnum.h>
#include <include/apxTemplate.h>

// --------------------------------------------------------
//	名前空間を使用(Apocalypse::Draw)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Draw
	{
		// ------------------------------------------------
		//	Front Declaration
		// ------------------------------------------------
		class Color;
		class Font;

		///	<summary>
		///		フレームの位置を示す定数を収納した列挙型．
		///	</summary>
		///	<remark>
		///		C++の性質上enumを外に置くとサジェストが汚染されるので
		///		クラスの内部に隠蔽しています．
		///	</remark>
		class FramePosition : virtual public Base::__ApcEnumeration
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
		///		すべてのフレームの基盤．
		///	</summary>
		/// <remarks>
		///		<para>Apocalypseでは，描画に関連することはフレーム(Frame)クラスを</para>
		///		<para>関して描画・管理されます．そのフレームクラスの基盤がこのクラスです．</para>
		///		<para>このクラス自体は生成できません．</para>
		/// </remarks>
		class __FrameBase : virtual public Base::__ApcBase
		{
			/// <summary>
			///		FrameCollectionクラスからは全てのメンバにアクセス可能です．
			/// </summary>
			friend class		Collection::__FrameCollection;
			/// <summary>
			///		typedef
			/// </summary>
			typedef				FramePosition::_FramePosition FPosition;
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
			Base::Point			Points;
			/// <summary>
			///		<para>このフレームの描画順番．高いほど手前に描画される．</para>
			///		<para>0に指定すると親フレームのZ座標から自動で指定される．</para>
			/// </summary>
			unsigned int		DrawOrder;
			/// <summary>
			///		このフレームのαブレンド．255で不透明．0で透明．
			/// </summary>
			int					Alpha;
			/// <summary>
			///		このフレームの親フレーム．
			/// </summary>
			std::shared_ptr<__FrameBase>
								Parent;
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
			Base::Point			GetLocation() const;
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
			Base::Point			_Location;
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
			///		NULLが指定されている場合枠線を描画しません．標準ではNULLです．
			/// </remarks>
			std::shared_ptr<Color>
								BorderColor;
			///	<summary>
			///		グラディエーション開始色を指定する．
			///	</summary>
			/// <remarks>
			///		NULLが指定されている場合グラデーションを描画しません．
			/// </remarks>
			std::shared_ptr<Color>
								StartGradColor;
			///	<summary>
			///		グラディエーション終了色を指定する．
			///	</summary>
			/// <remarks>
			///		NULLが指定されている場合StartGradColorの色で塗りつぶします．
			/// </remarks>
			std::shared_ptr<Color>
								EndGradColor;
			///	<summary>
			///		コンストラクタ
			///	</summary>
								GradationFrame(){}
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual				~GradationFrame(){}
		private:
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void		_DrawThisFrame() const;
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
								PictureFrame(Base::String ImgPath = _T(""));
			///	<summary>
			///		表示する画像ファイルを差し替える関数．
			///	</summary>
			/// <param name = "ImgPath">
			///		差し替える画像ファイルの場所．
			/// </param>
			/// <param name = "Handle">
			///		<para>（任意指定）差し替える画像ハンドル．</para>
			///		<para>標準ではファイルから自動で読み込むため指定する必要はない．</para>
			/// </param>
			bool				ExchangePicture(Base::String ImgPath, int Handle = NULL);
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual				~PictureFrame();
		private:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void		_DrawThisFrame() const;
		protected:
			///	<summary>
			///		画像ファイルのハンドル
			///	</summary>
			int					_PictureHandle;
			///	<summary>
			///		画像ファイルの場所
			///	</summary>
			Base::String		_PicturePath;
		};

		///	<summary>
		///		タイル状に表示可能なPictureFrame.
		///	</summary>
		/// <remarks>
		///		Width, Heightの値を設定することで読み込んだ画像をタイル状に表示します．
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
		class TilePictureFrame : public PictureFrame, public EdgeFrame
		{
		public:
			///	<summary>
			///		タイル状に画像を描画するフレームを作成する際に
			///		実行される関数．
			///	</summary>
			/// <param name = "ImgPath">
			///		表示する画像ファイルの場所．
			/// </param>
								TilePictureFrame(Base::String ImgPath = _T(""));
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
			int					TileX;
			/// <summary>
			///		このフレームのタイル模様のY座標．
			/// </summary>
			/// <remark>
			///		この値を増加させるとタイルの模様がY方向に移動します．
			///	</remark>
			/// <example>
			///		TilePictureFrame::TileXの例をご覧ください．
			/// </example>
			int					TileY;
			/// <summary>
			///		引き伸ばして表示するかどうか．
			/// </summary>
			/// <remarks>
			///		枠内部の部分を引き伸ばして表示するか，それとも繰り返し描画するかを選択します．
			///		例としては，グラデーションを使用している場合はtrue，タイル模様ならばfalseなどです．
			///		このプロパティをtrueに指定すると，TileX, TileYは無視されます．
			/// </remarks>
			bool				StretchDraw;
		private:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void		_DrawThisFrame() const;
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
								MovieFrame(Base::String MovPath = _T(""));
			///	<summary>
			///		再生時の音量．0(最小)～10000(最大)で指定する．
			///	</summary>
			UINT				Volume;
			///	<summary>
			///		動画の再生を開始する．
			///	</summary>
			void				Play();
			///	<summary>
			///		動画の再生を一時的に中止する．
			///	</summary>
			void				Pause();
			///	<summary>
			///		動画の再生を中止する．
			///	</summary>
			void				Stop();
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
			UINT				State();
		private:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void		_DrawThisFrame() const;
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
		///		// StringFrameをnewで確保して，色を青にして，自身の情報を描画させる．
		///		StringFrame* Str = new StringFrame();
		///		Str->Text = Str->ToString();
		///		Str->Color = ColorList::Color(ColorList::Blue);
		///		</code>
		/// </example>
		class StringFrame : public __FrameBase
		{
		public:
			///	<summary>
			///		描画する文字列．
			///	</summary>
			Base::String		Text;
			///	<summary>
			///		描画するのに使用するフォントのデータ．
			///	</summary>
			std::shared_ptr<Font>	
								TextFont;
			///	<summary>
			///		フォントの色．
			///	</summary>
			std::shared_ptr<Color>
								TextColor;
			///	<summary>
			///		グラデーション・枠線を描画するフレームを作成する際に
			///		実行される関数．
			///	</summary>
			/// <param name = "String">
			///		描画する文字列．
			/// </param>
								StringFrame(Base::String String = _T(""));
			/// <summary>
			///		デストラクタ
			/// </summary>
			virtual				~StringFrame(){}
		private:
			///	<summary>
			///		自身のプロパティを指定する関数．
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		フレームを描画する関数．
			///	</summary>
			virtual void		_DrawThisFrame() const;
		};

		///	<summary>
		///		フォントデータを内蔵するクラス．
		///	</summary>
		/// <remarks>
		///		<para>フォント名，フォントサイズ，フォントの太さなどを管理します．</para>
		///		<para>標準のフォント名は初期化関数で指定した標準フォントです．</para>
		/// </remarks>
		class Font : virtual public Base::__ApcBase
		{
		public:
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
								Font(Base::String FontName, int FontSize);
			///	<summary>
			///		コンストラクタ(名前/サイズ/太さ指定版)
			///	</summary>
								Font(Base::String FontName, int FontSize, int FontThick);
			///	<summary>
			///		コンストラクタ(全部指定版)
			///	</summary>
								Font(Base::String FontName, int FontSize, int FontThick, int FontType);
			///	<summary>
			///		デストラクタ
			///	</summary>
			virtual				~Font();
			///	<summary>
			///		フォントハンドルを取得する．
			///	</summary>
			int					_GetFontHandle() const;
		private:
			///	<summary>
			///		フォント名
			///	</summary>
			Base::String		_Name;
			///	<summary>
			///		フォントサイズ．
			///	</summary>
			int					_Size;
			///	<summary>
			///		フォントの太さ．
			///	</summary>
			int					_Thick;
			///	<summary>
			///		フォントの種類．
			///	</summary>
			int					_Type;
			///	<summary>
			///		フォントハンドル
			///	</summary>
			int					_Handle;
		};
	
		///	<summary>
		///		色を管理するクラス
		///	</summary>
		/// <remarks>
		///		<para>GradationFrameやStringFrameで使用する色データを取得・管理します．</para>
		///		<para>色リストについてはColor::ColorListを参照してください．</para>
		/// </remarks>
		/// <example>
		///		使用例: 
		///		<code>
		///		// オレンジ色を取得します
		///		Color::Color(0xFF, 0x80, 0x00);
		///		// 白色を取得します
		///		Color::Color(Color::White);
		///		</code>
		/// </example>
		class Color : virtual public Base::__ApcBase
		{
		public:
			///	<summary>
			///		色リストデータの列挙体
			///	</summary>
			enum				ColorList
			{
				/// <summary>
				/// AliceBlue(#F0F8FF)の色を取得します．
				/// </summary>
				AliceBlue = 0xF0F8FF,
				/// <summary>
				/// AntiqueWhite(#FAEBD7)の色を取得します．
				/// </summary>
				AntiqueWhite = 0xFAEBD7,
				/// <summary>
				/// Aqua(#00FFFF)の色を取得します．
				/// </summary>
				Aqua = 0x00FFFF,
				/// <summary>
				/// Aquamarine(#7FFFD4)の色を取得します．
				/// </summary>
				Aquamarine = 0x7FFFD4,
				/// <summary>
				/// Azure(#F0FFFF)の色を取得します．
				/// </summary>
				Azure = 0xF0FFFF,
				/// <summary>
				/// Beige(#F5F5DC)の色を取得します．
				/// </summary>
				Beige = 0xF5F5DC,
				/// <summary>
				/// Bisque(#FFE4C4)の色を取得します．
				/// </summary>
				Bisque = 0xFFE4C4,
				/// <summary>
				/// Black(#000000)の色を取得します．
				/// </summary>
				Black = 0x000000,
				/// <summary>
				/// BlanchedAlmond(#FFEBCD)の色を取得します．
				/// </summary>
				BlanchedAlmond = 0xFFEBCD,
				/// <summary>
				/// Blue(#0000FF)の色を取得します．
				/// </summary>
				Blue = 0x0000FF,
				/// <summary>
				/// BlueViolet(#8A2BE2)の色を取得します．
				/// </summary>
				BlueViolet = 0x8A2BE2,
				/// <summary>
				/// Brown(#A52A2A)の色を取得します．
				/// </summary>
				Brown = 0xA52A2A,
				/// <summary>
				/// BurlyWood(#DEB887)の色を取得します．
				/// </summary>
				BurlyWood = 0xDEB887,
				/// <summary>
				/// CadetBlue(#5F9EA0)の色を取得します．
				/// </summary>
				CadetBlue = 0x5F9EA0,
				/// <summary>
				/// Chartreuse(#7FFF00)の色を取得します．
				/// </summary>
				Chartreuse = 0x7FFF00,
				/// <summary>
				/// Chocolate(#D2691E)の色を取得します．
				/// </summary>
				Chocolate = 0xD2691E,
				/// <summary>
				/// Coral(#FF7F50)の色を取得します．
				/// </summary>
				Coral = 0xFF7F50,
				/// <summary>
				/// CornflowerBlue(#6495ED)の色を取得します．
				/// </summary>
				CornflowerBlue = 0x6495ED,
				/// <summary>
				/// Cornsilk(#FFF8DC)の色を取得します．
				/// </summary>
				Cornsilk = 0xFFF8DC,
				/// <summary>
				/// Crimson(#DC143C)の色を取得します．
				/// </summary>
				Crimson = 0xDC143C,
				/// <summary>
				/// Cyan(#00FFFF)の色を取得します．
				/// </summary>
				Cyan = 0x00FFFF,
				/// <summary>
				/// DarkBlue(#00008B)の色を取得します．
				/// </summary>
				DarkBlue = 0x00008B,
				/// <summary>
				/// DarkCyan(#008B8B)の色を取得します．
				/// </summary>
				DarkCyan = 0x008B8B,
				/// <summary>
				/// DarkGoldenrod(#B8860B)の色を取得します．
				/// </summary>
				DarkGoldenrod = 0xB8860B,
				/// <summary>
				/// DarkGray(#A9A9A9)の色を取得します．
				/// </summary>
				DarkGray = 0xA9A9A9,
				/// <summary>
				/// DarkGreen(#006400)の色を取得します．
				/// </summary>
				DarkGreen = 0x006400,
				/// <summary>
				/// DarkKhaki(#BDB76B)の色を取得します．
				/// </summary>
				DarkKhaki = 0xBDB76B,
				/// <summary>
				/// DarkMagenta(#8B008B)の色を取得します．
				/// </summary>
				DarkMagenta = 0x8B008B,
				/// <summary>
				/// DarkOliveGreen(#556B2F)の色を取得します．
				/// </summary>
				DarkOliveGreen = 0x556B2F,
				/// <summary>
				/// DarkOrange(#FF8C00)の色を取得します．
				/// </summary>
				DarkOrange = 0xFF8C00,
				/// <summary>
				/// DarkOrchid(#9932CC)の色を取得します．
				/// </summary>
				DarkOrchid = 0x9932CC,
				/// <summary>
				/// DarkRed(#8B0000)の色を取得します．
				/// </summary>
				DarkRed = 0x8B0000,
				/// <summary>
				/// DarkSalmon(#E9967A)の色を取得します．
				/// </summary>
				DarkSalmon = 0xE9967A,
				/// <summary>
				/// DarkSeaGreen(#8FBC8B)の色を取得します．
				/// </summary>
				DarkSeaGreen = 0x8FBC8B,
				/// <summary>
				/// DarkSlateBlue(#483D8B)の色を取得します．
				/// </summary>
				DarkSlateBlue = 0x483D8B,
				/// <summary>
				/// DarkSlateGray(#2F4F4F)の色を取得します．
				/// </summary>
				DarkSlateGray = 0x2F4F4F,
				/// <summary>
				/// DarkTurquoise(#00CED1)の色を取得します．
				/// </summary>
				DarkTurquoise = 0x00CED1,
				/// <summary>
				/// DarkViolet(#9400D3)の色を取得します．
				/// </summary>
				DarkViolet = 0x9400D3,
				/// <summary>
				/// DeepPink(#FF1493)の色を取得します．
				/// </summary>
				DeepPink = 0xFF1493,
				/// <summary>
				/// DeepSkyBlue(#00BFFF)の色を取得します．
				/// </summary>
				DeepSkyBlue = 0x00BFFF,
				/// <summary>
				/// DimGray(#696969)の色を取得します．
				/// </summary>
				DimGray = 0x696969,
				/// <summary>
				/// DodgerBlue(#1E90FF)の色を取得します．
				/// </summary>
				DodgerBlue = 0x1E90FF,
				/// <summary>
				/// Firebrick(#B22222)の色を取得します．
				/// </summary>
				Firebrick = 0xB22222,
				/// <summary>
				/// FloralWhite(#FFFAF0)の色を取得します．
				/// </summary>
				FloralWhite = 0xFFFAF0,
				/// <summary>
				/// ForestGreen(#228B22)の色を取得します．
				/// </summary>
				ForestGreen = 0x228B22,
				/// <summary>
				/// Fuchsia(#FF00FF)の色を取得します．
				/// </summary>
				Fuchsia = 0xFF00FF,
				/// <summary>
				/// Gainsboro(#DCDCDC)の色を取得します．
				/// </summary>
				Gainsboro = 0xDCDCDC,
				/// <summary>
				/// GhostWhite(#F8F8FF)の色を取得します．
				/// </summary>
				GhostWhite = 0xF8F8FF,
				/// <summary>
				/// Gold(#FFD700)の色を取得します．
				/// </summary>
				Gold = 0xFFD700,
				/// <summary>
				/// Goldenrod(#DAA520)の色を取得します．
				/// </summary>
				Goldenrod = 0xDAA520,
				/// <summary>
				/// Gray(#808080)の色を取得します．
				/// </summary>
				Gray = 0x808080,
				/// <summary>
				/// Green(#008000)の色を取得します．
				/// </summary>
				Green = 0x008000,
				/// <summary>
				/// GreenYellow(#ADFF2F)の色を取得します．
				/// </summary>
				GreenYellow = 0xADFF2F,
				/// <summary>
				/// Honeydew(#F0FFF0)の色を取得します．
				/// </summary>
				Honeydew = 0xF0FFF0,
				/// <summary>
				/// HotPink(#FF69B4)の色を取得します．
				/// </summary>
				HotPink = 0xFF69B4,
				/// <summary>
				/// IndianRed(#CD5C5C)の色を取得します．
				/// </summary>
				IndianRed = 0xCD5C5C,
				/// <summary>
				/// Indigo(#4B0082)の色を取得します．
				/// </summary>
				Indigo = 0x4B0082,
				/// <summary>
				/// Ivory(#FFFFF0)の色を取得します．
				/// </summary>
				Ivory = 0xFFFFF0,
				/// <summary>
				/// Khaki(#F0E68C)の色を取得します．
				/// </summary>
				Khaki = 0xF0E68C,
				/// <summary>
				/// Lavender(#E6E6FA)の色を取得します．
				/// </summary>
				Lavender = 0xE6E6FA,
				/// <summary>
				/// LavenderBlush(#FFF0F5)の色を取得します．
				/// </summary>
				LavenderBlush = 0xFFF0F5,
				/// <summary>
				/// LawnGreen(#7CFC00)の色を取得します．
				/// </summary>
				LawnGreen = 0x7CFC00,
				/// <summary>
				/// LemonChiffon(#FFFACD)の色を取得します．
				/// </summary>
				LemonChiffon = 0xFFFACD,
				/// <summary>
				/// LightBlue(#ADD8E6)の色を取得します．
				/// </summary>
				LightBlue = 0xADD8E6,
				/// <summary>
				/// LightCoral(#F08080)の色を取得します．
				/// </summary>
				LightCoral = 0xF08080,
				/// <summary>
				/// LightCyan(#E0FFFF)の色を取得します．
				/// </summary>
				LightCyan = 0xE0FFFF,
				/// <summary>
				/// LightGoldenrodYellow(#FAFAD2)の色を取得します．
				/// </summary>
				LightGoldenrodYellow = 0xFAFAD2,
				/// <summary>
				/// LightGreen(#90EE90)の色を取得します．
				/// </summary>
				LightGreen = 0x90EE90,
				/// <summary>
				/// LightGray(#D3D3D3)の色を取得します．
				/// </summary>
				LightGray = 0xD3D3D3,
				/// <summary>
				/// LightPink(#FFB6C1)の色を取得します．
				/// </summary>
				LightPink = 0xFFB6C1,
				/// <summary>
				/// LightSalmon(#FFA07A)の色を取得します．
				/// </summary>
				LightSalmon = 0xFFA07A,
				/// <summary>
				/// LightSeaGreen(#20B2AA)の色を取得します．
				/// </summary>
				LightSeaGreen = 0x20B2AA,
				/// <summary>
				/// LightSkyBlue(#87CEFA)の色を取得します．
				/// </summary>
				LightSkyBlue = 0x87CEFA,
				/// <summary>
				/// LightSlateGray(#778899)の色を取得します．
				/// </summary>
				LightSlateGray = 0x778899,
				/// <summary>
				/// LightSteelBlue(#B0C4DE)の色を取得します．
				/// </summary>
				LightSteelBlue = 0xB0C4DE,
				/// <summary>
				/// LightYellow(#FFFFE0)の色を取得します．
				/// </summary>
				LightYellow = 0xFFFFE0,
				/// <summary>
				/// Lime(#00FF00)の色を取得します．
				/// </summary>
				Lime = 0x00FF00,
				/// <summary>
				/// LimeGreen(#32CD32)の色を取得します．
				/// </summary>
				LimeGreen = 0x32CD32,
				/// <summary>
				/// Linen(#FAF0E6)の色を取得します．
				/// </summary>
				Linen = 0xFAF0E6,
				/// <summary>
				/// Magenta(#FF00FF)の色を取得します．
				/// </summary>
				Magenta = 0xFF00FF,
				/// <summary>
				/// Maroon(#800000)の色を取得します．
				/// </summary>
				Maroon = 0x800000,
				/// <summary>
				/// MediumAquamarine(#66CDAA)の色を取得します．
				/// </summary>
				MediumAquamarine = 0x66CDAA,
				/// <summary>
				/// MediumBlue(#0000CD)の色を取得します．
				/// </summary>
				MediumBlue = 0x0000CD,
				/// <summary>
				/// MediumOrchid(#BA55D3)の色を取得します．
				/// </summary>
				MediumOrchid = 0xBA55D3,
				/// <summary>
				/// MediumPurple(#9370DB)の色を取得します．
				/// </summary>
				MediumPurple = 0x9370DB,
				/// <summary>
				/// MediumSeaGreen(#3CB371)の色を取得します．
				/// </summary>
				MediumSeaGreen = 0x3CB371,
				/// <summary>
				/// MediumSlateBlue(#7B68EE)の色を取得します．
				/// </summary>
				MediumSlateBlue = 0x7B68EE,
				/// <summary>
				/// MediumSpringGreen(#00FA9A)の色を取得します．
				/// </summary>
				MediumSpringGreen = 0x00FA9A,
				/// <summary>
				/// MediumTurquoise(#48D1CC)の色を取得します．
				/// </summary>
				MediumTurquoise = 0x48D1CC,
				/// <summary>
				/// MediumVioletRed(#C71585)の色を取得します．
				/// </summary>
				MediumVioletRed = 0xC71585,
				/// <summary>
				/// MidnightBlue(#191970)の色を取得します．
				/// </summary>
				MidnightBlue = 0x191970,
				/// <summary>
				/// MintCream(#F5FFFA)の色を取得します．
				/// </summary>
				MintCream = 0xF5FFFA,
				/// <summary>
				/// MistyRose(#FFE4E1)の色を取得します．
				/// </summary>
				MistyRose = 0xFFE4E1,
				/// <summary>
				/// Moccasin(#FFE4B5)の色を取得します．
				/// </summary>
				Moccasin = 0xFFE4B5,
				/// <summary>
				/// NavajoWhite(#FFDEAD)の色を取得します．
				/// </summary>
				NavajoWhite = 0xFFDEAD,
				/// <summary>
				/// Navy(#000080)の色を取得します．
				/// </summary>
				Navy = 0x000080,
				/// <summary>
				/// OldLace(#FDF5E6)の色を取得します．
				/// </summary>
				OldLace = 0xFDF5E6,
				/// <summary>
				/// Olive(#808000)の色を取得します．
				/// </summary>
				Olive = 0x808000,
				/// <summary>
				/// OliveDrab(#6B8E23)の色を取得します．
				/// </summary>
				OliveDrab = 0x6B8E23,
				/// <summary>
				/// Orange(#FFA500)の色を取得します．
				/// </summary>
				Orange = 0xFFA500,
				/// <summary>
				/// OrangeRed(#FF4500)の色を取得します．
				/// </summary>
				OrangeRed = 0xFF4500,
				/// <summary>
				/// Orchid(#DA70D6)の色を取得します．
				/// </summary>
				Orchid = 0xDA70D6,
				/// <summary>
				/// PaleGoldenrod(#EEE8AA)の色を取得します．
				/// </summary>
				PaleGoldenrod = 0xEEE8AA,
				/// <summary>
				/// PaleGreen(#98FB98)の色を取得します．
				/// </summary>
				PaleGreen = 0x98FB98,
				/// <summary>
				/// PaleTurquoise(#AFEEEE)の色を取得します．
				/// </summary>
				PaleTurquoise = 0xAFEEEE,
				/// <summary>
				/// PaleVioletRed(#DB7093)の色を取得します．
				/// </summary>
				PaleVioletRed = 0xDB7093,
				/// <summary>
				/// PapayaWhip(#FFEFD5)の色を取得します．
				/// </summary>
				PapayaWhip = 0xFFEFD5,
				/// <summary>
				/// PeachPuff(#FFDAB9)の色を取得します．
				/// </summary>
				PeachPuff = 0xFFDAB9,
				/// <summary>
				/// Peru(#CD853F)の色を取得します．
				/// </summary>
				Peru = 0xCD853F,
				/// <summary>
				/// Pink(#FFC0CB)の色を取得します．
				/// </summary>
				Pink = 0xFFC0CB,
				/// <summary>
				/// Plum(#DDA0DD)の色を取得します．
				/// </summary>
				Plum = 0xDDA0DD,
				/// <summary>
				/// PowderBlue(#B0E0E6)の色を取得します．
				/// </summary>
				PowderBlue = 0xB0E0E6,
				/// <summary>
				/// Purple(#800080)の色を取得します．
				/// </summary>
				Purple = 0x800080,
				/// <summary>
				/// Red(#FF0000)の色を取得します．
				/// </summary>
				Red = 0xFF0000,
				/// <summary>
				/// RosyBrown(#BC8F8F)の色を取得します．
				/// </summary>
				RosyBrown = 0xBC8F8F,
				/// <summary>
				/// RoyalBlue(#4169E1)の色を取得します．
				/// </summary>
				RoyalBlue = 0x4169E1,
				/// <summary>
				/// SaddleBrown(#8B4513)の色を取得します．
				/// </summary>
				SaddleBrown = 0x8B4513,
				/// <summary>
				/// Salmon(#FA8072)の色を取得します．
				/// </summary>
				Salmon = 0xFA8072,
				/// <summary>
				/// SandyBrown(#F4A460)の色を取得します．
				/// </summary>
				SandyBrown = 0xF4A460,
				/// <summary>
				/// SeaGreen(#2E8B57)の色を取得します．
				/// </summary>
				SeaGreen = 0x2E8B57,
				/// <summary>
				/// SeaShell(#FFF5EE)の色を取得します．
				/// </summary>
				SeaShell = 0xFFF5EE,
				/// <summary>
				/// Sienna(#A0522D)の色を取得します．
				/// </summary>
				Sienna = 0xA0522D,
				/// <summary>
				/// Silver(#C0C0C0)の色を取得します．
				/// </summary>
				Silver = 0xC0C0C0,
				/// <summary>
				/// SkyBlue(#87CEEB)の色を取得します．
				/// </summary>
				SkyBlue = 0x87CEEB,
				/// <summary>
				/// SlateBlue(#6A5ACD)の色を取得します．
				/// </summary>
				SlateBlue = 0x6A5ACD,
				/// <summary>
				/// SlateGray(#708090)の色を取得します．
				/// </summary>
				SlateGray = 0x708090,
				/// <summary>
				/// Snow(#FFFAFA)の色を取得します．
				/// </summary>
				Snow = 0xFFFAFA,
				/// <summary>
				/// SpringGreen(#00FF7F)の色を取得します．
				/// </summary>
				SpringGreen = 0x00FF7F,
				/// <summary>
				/// SteelBlue(#4682B4)の色を取得します．
				/// </summary>
				SteelBlue = 0x4682B4,
				/// <summary>
				/// Tan(#D2B48C)の色を取得します．
				/// </summary>
				Tan = 0xD2B48C,
				/// <summary>
				/// Teal(#008080)の色を取得します．
				/// </summary>
				Teal = 0x008080,
				/// <summary>
				/// Thistle(#D8BFD8)の色を取得します．
				/// </summary>
				Thistle = 0xD8BFD8,
				/// <summary>
				/// Tomato(#FF6347)の色を取得します．
				/// </summary>
				Tomato = 0xFF6347,
				/// <summary>
				/// Turquoise(#40E0D0)の色を取得します．
				/// </summary>
				Turquoise = 0x40E0D0,
				/// <summary>
				/// Violet(#EE82EE)の色を取得します．
				/// </summary>
				Violet = 0xEE82EE,
				/// <summary>
				/// Wheat(#F5DEB3)の色を取得します．
				/// </summary>
				Wheat = 0xF5DEB3,
				/// <summary>
				/// White(#FFFFFF)の色を取得します．
				/// </summary>
				White = 0xFFFFFF,
				/// <summary>
				/// WhiteSmoke(#F5F5F5)の色を取得します．
				/// </summary>
				WhiteSmoke = 0xF5F5F5,
				/// <summary>
				/// Yellow(#FFFF00)の色を取得します．
				/// </summary>
				Yellow = 0xFFFF00,
				/// <summary>
				/// YellowGreen(#9ACD32)の色を取得します．
				/// </summary>
				YellowGreen = 0x9ACD32,
				/// <summary>
				/// ActiveBorder(#B4B4B4)の色を取得します．
				/// </summary>
				ActiveBorder = 0xB4B4B4,
				/// <summary>
				/// ActiveCaption(#99B4D1)の色を取得します．
				/// </summary>
				ActiveCaption = 0x99B4D1,
				/// <summary>
				/// ActiveCaptionText(#000000)の色を取得します．
				/// </summary>
				ActiveCaptionText = 0x000000,
				/// <summary>
				/// AppWorkspace(#ABABAB)の色を取得します．
				/// </summary>
				AppWorkspace = 0xABABAB,
				/// <summary>
				/// ButtonFace(#F0F0F0)の色を取得します．
				/// </summary>
				ButtonFace = 0xF0F0F0,
				/// <summary>
				/// ButtonHighlight(#FFFFFF)の色を取得します．
				/// </summary>
				ButtonHighlight = 0xFFFFFF,
				/// <summary>
				/// ButtonShadow(#A0A0A0)の色を取得します．
				/// </summary>
				ButtonShadow = 0xA0A0A0,
				/// <summary>
				/// Control(#F0F0F0)の色を取得します．
				/// </summary>
				Control = 0xF0F0F0,
				/// <summary>
				/// ControlDark(#A0A0A0)の色を取得します．
				/// </summary>
				ControlDark = 0xA0A0A0,
				/// <summary>
				/// ControlDarkDark(#696969)の色を取得します．
				/// </summary>
				ControlDarkDark = 0x696969,
				/// <summary>
				/// ControlLight(#E3E3E3)の色を取得します．
				/// </summary>
				ControlLight = 0xE3E3E3,
				/// <summary>
				/// ControlLightLight(#FFFFFF)の色を取得します．
				/// </summary>
				ControlLightLight = 0xFFFFFF,
				/// <summary>
				/// ControlText(#000000)の色を取得します．
				/// </summary>
				ControlText = 0x000000,
				/// <summary>
				/// Desktop(#000000)の色を取得します．
				/// </summary>
				Desktop = 0x000000,
				/// <summary>
				/// GradientActiveCaption(#B9D1EA)の色を取得します．
				/// </summary>
				GradientActiveCaption = 0xB9D1EA,
				/// <summary>
				/// GradientInactiveCaption(#D7E4F2)の色を取得します．
				/// </summary>
				GradientInactiveCaption = 0xD7E4F2,
				/// <summary>
				/// GrayText(#6D6D6D)の色を取得します．
				/// </summary>
				GrayText = 0x6D6D6D,
				/// <summary>
				/// Highlight(#3399FF)の色を取得します．
				/// </summary>
				Highlight = 0x3399FF,
				/// <summary>
				/// HighlightText(#FFFFFF)の色を取得します．
				/// </summary>
				HighlightText = 0xFFFFFF,
				/// <summary>
				/// HotTrack(#0066CC)の色を取得します．
				/// </summary>
				HotTrack = 0x0066CC,
				/// <summary>
				/// InactiveBorder(#F4F7FC)の色を取得します．
				/// </summary>
				InactiveBorder = 0xF4F7FC,
				/// <summary>
				/// InactiveCaption(#BFCDDB)の色を取得します．
				/// </summary>
				InactiveCaption = 0xBFCDDB,
				/// <summary>
				/// InactiveCaptionText(#000000)の色を取得します．
				/// </summary>
				InactiveCaptionText = 0x000000,
				/// <summary>
				/// Info(#FFFFE1)の色を取得します．
				/// </summary>
				Info = 0xFFFFE1,
				/// <summary>
				/// InfoText(#000000)の色を取得します．
				/// </summary>
				InfoText = 0x000000,
				/// <summary>
				/// Menu(#F0F0F0)の色を取得します．
				/// </summary>
				Menu = 0xF0F0F0,
				/// <summary>
				/// MenuBar(#F0F0F0)の色を取得します．
				/// </summary>
				MenuBar = 0xF0F0F0,
				/// <summary>
				/// MenuHighlight(#3399FF)の色を取得します．
				/// </summary>
				MenuHighlight = 0x3399FF,
				/// <summary>
				/// MenuText(#000000)の色を取得します．
				/// </summary>
				MenuText = 0x000000,
				/// <summary>
				/// ScrollBar(#C8C8C8)の色を取得します．
				/// </summary>
				ScrollBar = 0xC8C8C8,
				/// <summary>
				/// Window(#FFFFFF)の色を取得します．
				/// </summary>
				Window = 0xFFFFFF,
				/// <summary>
				/// WindowFrame(#646464)の色を取得します．
				/// </summary>
				WindowFrame = 0x646464,
				/// <summary>
				/// WindowText(#000000)の色を取得します．
				/// </summary>
				WindowText = 0x000000,
			};
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
								Color(int R, int G, int B);
			/// <summary>
			///		色データを作成する（HTML等の色コード版）
			/// </summary>
			/// <param name = "RGBCode">
			///		RGBコード．<see cref="ColorList">ColorList</see>内で
			///		定義された値を使用することも可能です．
			/// </param>
								Color(ColorList RGBCode);
			/// <summary>
			///		クラスに登録されている色データを返却する
			/// </summary>
			inline DWORD		_GetColorToClass() const;
			/// <summary>
			///		自身と対象の色を一定割合でブレンドした結果を返却する．
			/// </summary>
			/// <param name = "Target">
			///		自身とブレンドする対象の色データのポインタ．
			/// </param>
			/// <param name = "Parcent">
			///		ブレンドする割合．
			/// </param>
			DWORD				_GetColorBlends(const std::shared_ptr<Color> Target, int Parcent) const;
			///	<summary>
			///		色の赤成分の強度．
			///	</summary>
			int					_Red;
			///	<summary>
			///		色の緑成分の強度．
			///	</summary>
			int					_Green;
			///	<summary>
			///		色の青成分の強度．
			///	</summary>
			int					_Blue;
		};

	}
}
