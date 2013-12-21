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
#include <include/apcClassBase.h>
#include <include/apcCollection.h>
#include <include/apxEnum.h>
#include <include/apxTemplate.h>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Draw)
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
		///		�t���[���̈ʒu�������萔�����[�����񋓌^�D
		///	</summary>
		///	<remark>
		///		C++�̐�����enum���O�ɒu���ƃT�W�F�X�g�����������̂�
		///		�N���X�̓����ɉB�����Ă��܂��D
		///	</remark>
		class FramePosition : virtual public Base::__ApcEnumeration
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
		///		���ׂẴt���[���̊�ՁD
		///	</summary>
		/// <remarks>
		///		<para>Apocalypse�ł́C�`��Ɋ֘A���邱�Ƃ̓t���[��(Frame)�N���X��</para>
		///		<para>�ւ��ĕ`��E�Ǘ�����܂��D���̃t���[���N���X�̊�Ղ����̃N���X�ł��D</para>
		///		<para>���̃N���X���̂͐����ł��܂���D</para>
		/// </remarks>
		class __FrameBase : virtual public Base::__ApcBase
		{
			/// <summary>
			///		FrameCollection�N���X����͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Collection::__FrameCollection;
			/// <summary>
			///		typedef
			/// </summary>
			typedef				FramePosition::_FramePosition FPosition;
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
			Base::Point			Points;
			/// <summary>
			///		<para>���̃t���[���̕`�揇�ԁD�����قǎ�O�ɕ`�悳���D</para>
			///		<para>0�Ɏw�肷��Ɛe�t���[����Z���W���玩���Ŏw�肳���D</para>
			/// </summary>
			unsigned int		DrawOrder;
			/// <summary>
			///		���̃t���[���̃��u�����h�D255�ŕs�����D0�œ����D
			/// </summary>
			int					Alpha;
			/// <summary>
			///		���̃t���[���̐e�t���[���D
			/// </summary>
			std::shared_ptr<__FrameBase>
								Parent;
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
			Base::Point			GetLocation() const;
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
			Base::Point			_Location;
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
			///		NULL���w�肳��Ă���ꍇ�g����`�悵�܂���D�W���ł�NULL�ł��D
			/// </remarks>
			std::shared_ptr<Color>
								BorderColor;
			///	<summary>
			///		�O���f�B�G�[�V�����J�n�F���w�肷��D
			///	</summary>
			/// <remarks>
			///		NULL���w�肳��Ă���ꍇ�O���f�[�V������`�悵�܂���D
			/// </remarks>
			std::shared_ptr<Color>
								StartGradColor;
			///	<summary>
			///		�O���f�B�G�[�V�����I���F���w�肷��D
			///	</summary>
			/// <remarks>
			///		NULL���w�肳��Ă���ꍇStartGradColor�̐F�œh��Ԃ��܂��D
			/// </remarks>
			std::shared_ptr<Color>
								EndGradColor;
			///	<summary>
			///		�R���X�g���N�^
			///	</summary>
								GradationFrame(){}
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual				~GradationFrame(){}
		private:
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void		_DrawThisFrame() const;
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
								PictureFrame(Base::String ImgPath = _T(""));
			///	<summary>
			///		�\������摜�t�@�C���������ւ���֐��D
			///	</summary>
			/// <param name = "ImgPath">
			///		�����ւ���摜�t�@�C���̏ꏊ�D
			/// </param>
			/// <param name = "Handle">
			///		<para>�i�C�ӎw��j�����ւ���摜�n���h���D</para>
			///		<para>�W���ł̓t�@�C�����玩���œǂݍ��ނ��ߎw�肷��K�v�͂Ȃ��D</para>
			/// </param>
			bool				ExchangePicture(Base::String ImgPath, int Handle = NULL);
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual				~PictureFrame();
		private:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void		_DrawThisFrame() const;
		protected:
			///	<summary>
			///		�摜�t�@�C���̃n���h��
			///	</summary>
			int					_PictureHandle;
			///	<summary>
			///		�摜�t�@�C���̏ꏊ
			///	</summary>
			Base::String		_PicturePath;
		};

		///	<summary>
		///		�^�C����ɕ\���\��PictureFrame.
		///	</summary>
		/// <remarks>
		///		Width, Height�̒l��ݒ肷�邱�Ƃœǂݍ��񂾉摜���^�C����ɕ\�����܂��D
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
		class TilePictureFrame : public PictureFrame, public EdgeFrame
		{
		public:
			///	<summary>
			///		�^�C����ɉ摜��`�悷��t���[�����쐬����ۂ�
			///		���s�����֐��D
			///	</summary>
			/// <param name = "ImgPath">
			///		�\������摜�t�@�C���̏ꏊ�D
			/// </param>
								TilePictureFrame(Base::String ImgPath = _T(""));
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
			int					TileX;
			/// <summary>
			///		���̃t���[���̃^�C���͗l��Y���W�D
			/// </summary>
			/// <remark>
			///		���̒l�𑝉�������ƃ^�C���̖͗l��Y�����Ɉړ����܂��D
			///	</remark>
			/// <example>
			///		TilePictureFrame::TileX�̗���������������D
			/// </example>
			int					TileY;
			/// <summary>
			///		�����L�΂��ĕ\�����邩�ǂ����D
			/// </summary>
			/// <remarks>
			///		�g�����̕����������L�΂��ĕ\�����邩�C����Ƃ��J��Ԃ��`�悷�邩��I�����܂��D
			///		��Ƃ��ẮC�O���f�[�V�������g�p���Ă���ꍇ��true�C�^�C���͗l�Ȃ��false�Ȃǂł��D
			///		���̃v���p�e�B��true�Ɏw�肷��ƁCTileX, TileY�͖�������܂��D
			/// </remarks>
			bool				StretchDraw;
		private:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void		_DrawThisFrame() const;
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
								MovieFrame(Base::String MovPath = _T(""));
			///	<summary>
			///		�Đ����̉��ʁD0(�ŏ�)�`10000(�ő�)�Ŏw�肷��D
			///	</summary>
			UINT				Volume;
			///	<summary>
			///		����̍Đ����J�n����D
			///	</summary>
			void				Play();
			///	<summary>
			///		����̍Đ����ꎞ�I�ɒ��~����D
			///	</summary>
			void				Pause();
			///	<summary>
			///		����̍Đ��𒆎~����D
			///	</summary>
			void				Stop();
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
			UINT				State();
		private:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void		_DrawThisFrame() const;
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
		///		// StringFrame��new�Ŋm�ۂ��āC�F��ɂ��āC���g�̏���`�悳����D
		///		StringFrame* Str = new StringFrame();
		///		Str->Text = Str->ToString();
		///		Str->Color = ColorList::Color(ColorList::Blue);
		///		</code>
		/// </example>
		class StringFrame : public __FrameBase
		{
		public:
			///	<summary>
			///		�`�悷�镶����D
			///	</summary>
			Base::String		Text;
			///	<summary>
			///		�`�悷��̂Ɏg�p����t�H���g�̃f�[�^�D
			///	</summary>
			std::shared_ptr<Font>	
								TextFont;
			///	<summary>
			///		�t�H���g�̐F�D
			///	</summary>
			std::shared_ptr<Color>
								TextColor;
			///	<summary>
			///		�O���f�[�V�����E�g����`�悷��t���[�����쐬����ۂ�
			///		���s�����֐��D
			///	</summary>
			/// <param name = "String">
			///		�`�悷�镶����D
			/// </param>
								StringFrame(Base::String String = _T(""));
			/// <summary>
			///		�f�X�g���N�^
			/// </summary>
			virtual				~StringFrame(){}
		private:
			///	<summary>
			///		���g�̃v���p�e�B���w�肷��֐��D
			///	</summary>
			virtual void		_SetProperties();
			///	<summary>
			///		�t���[����`�悷��֐��D
			///	</summary>
			virtual void		_DrawThisFrame() const;
		};

		///	<summary>
		///		�t�H���g�f�[�^���������N���X�D
		///	</summary>
		/// <remarks>
		///		<para>�t�H���g���C�t�H���g�T�C�Y�C�t�H���g�̑����Ȃǂ��Ǘ����܂��D</para>
		///		<para>�W���̃t�H���g���͏������֐��Ŏw�肵���W���t�H���g�ł��D</para>
		/// </remarks>
		class Font : virtual public Base::__ApcBase
		{
		public:
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
								Font(Base::String FontName, int FontSize);
			///	<summary>
			///		�R���X�g���N�^(���O/�T�C�Y/�����w���)
			///	</summary>
								Font(Base::String FontName, int FontSize, int FontThick);
			///	<summary>
			///		�R���X�g���N�^(�S���w���)
			///	</summary>
								Font(Base::String FontName, int FontSize, int FontThick, int FontType);
			///	<summary>
			///		�f�X�g���N�^
			///	</summary>
			virtual				~Font();
			///	<summary>
			///		�t�H���g�n���h�����擾����D
			///	</summary>
			int					_GetFontHandle() const;
		private:
			///	<summary>
			///		�t�H���g��
			///	</summary>
			Base::String		_Name;
			///	<summary>
			///		�t�H���g�T�C�Y�D
			///	</summary>
			int					_Size;
			///	<summary>
			///		�t�H���g�̑����D
			///	</summary>
			int					_Thick;
			///	<summary>
			///		�t�H���g�̎�ށD
			///	</summary>
			int					_Type;
			///	<summary>
			///		�t�H���g�n���h��
			///	</summary>
			int					_Handle;
		};
	
		///	<summary>
		///		�F���Ǘ�����N���X
		///	</summary>
		/// <remarks>
		///		<para>GradationFrame��StringFrame�Ŏg�p����F�f�[�^���擾�E�Ǘ����܂��D</para>
		///		<para>�F���X�g�ɂ��Ă�Color::ColorList���Q�Ƃ��Ă��������D</para>
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// �I�����W�F���擾���܂�
		///		Color::Color(0xFF, 0x80, 0x00);
		///		// ���F���擾���܂�
		///		Color::Color(Color::White);
		///		</code>
		/// </example>
		class Color : virtual public Base::__ApcBase
		{
		public:
			///	<summary>
			///		�F���X�g�f�[�^�̗񋓑�
			///	</summary>
			enum				ColorList
			{
				/// <summary>
				/// AliceBlue(#F0F8FF)�̐F���擾���܂��D
				/// </summary>
				AliceBlue = 0xF0F8FF,
				/// <summary>
				/// AntiqueWhite(#FAEBD7)�̐F���擾���܂��D
				/// </summary>
				AntiqueWhite = 0xFAEBD7,
				/// <summary>
				/// Aqua(#00FFFF)�̐F���擾���܂��D
				/// </summary>
				Aqua = 0x00FFFF,
				/// <summary>
				/// Aquamarine(#7FFFD4)�̐F���擾���܂��D
				/// </summary>
				Aquamarine = 0x7FFFD4,
				/// <summary>
				/// Azure(#F0FFFF)�̐F���擾���܂��D
				/// </summary>
				Azure = 0xF0FFFF,
				/// <summary>
				/// Beige(#F5F5DC)�̐F���擾���܂��D
				/// </summary>
				Beige = 0xF5F5DC,
				/// <summary>
				/// Bisque(#FFE4C4)�̐F���擾���܂��D
				/// </summary>
				Bisque = 0xFFE4C4,
				/// <summary>
				/// Black(#000000)�̐F���擾���܂��D
				/// </summary>
				Black = 0x000000,
				/// <summary>
				/// BlanchedAlmond(#FFEBCD)�̐F���擾���܂��D
				/// </summary>
				BlanchedAlmond = 0xFFEBCD,
				/// <summary>
				/// Blue(#0000FF)�̐F���擾���܂��D
				/// </summary>
				Blue = 0x0000FF,
				/// <summary>
				/// BlueViolet(#8A2BE2)�̐F���擾���܂��D
				/// </summary>
				BlueViolet = 0x8A2BE2,
				/// <summary>
				/// Brown(#A52A2A)�̐F���擾���܂��D
				/// </summary>
				Brown = 0xA52A2A,
				/// <summary>
				/// BurlyWood(#DEB887)�̐F���擾���܂��D
				/// </summary>
				BurlyWood = 0xDEB887,
				/// <summary>
				/// CadetBlue(#5F9EA0)�̐F���擾���܂��D
				/// </summary>
				CadetBlue = 0x5F9EA0,
				/// <summary>
				/// Chartreuse(#7FFF00)�̐F���擾���܂��D
				/// </summary>
				Chartreuse = 0x7FFF00,
				/// <summary>
				/// Chocolate(#D2691E)�̐F���擾���܂��D
				/// </summary>
				Chocolate = 0xD2691E,
				/// <summary>
				/// Coral(#FF7F50)�̐F���擾���܂��D
				/// </summary>
				Coral = 0xFF7F50,
				/// <summary>
				/// CornflowerBlue(#6495ED)�̐F���擾���܂��D
				/// </summary>
				CornflowerBlue = 0x6495ED,
				/// <summary>
				/// Cornsilk(#FFF8DC)�̐F���擾���܂��D
				/// </summary>
				Cornsilk = 0xFFF8DC,
				/// <summary>
				/// Crimson(#DC143C)�̐F���擾���܂��D
				/// </summary>
				Crimson = 0xDC143C,
				/// <summary>
				/// Cyan(#00FFFF)�̐F���擾���܂��D
				/// </summary>
				Cyan = 0x00FFFF,
				/// <summary>
				/// DarkBlue(#00008B)�̐F���擾���܂��D
				/// </summary>
				DarkBlue = 0x00008B,
				/// <summary>
				/// DarkCyan(#008B8B)�̐F���擾���܂��D
				/// </summary>
				DarkCyan = 0x008B8B,
				/// <summary>
				/// DarkGoldenrod(#B8860B)�̐F���擾���܂��D
				/// </summary>
				DarkGoldenrod = 0xB8860B,
				/// <summary>
				/// DarkGray(#A9A9A9)�̐F���擾���܂��D
				/// </summary>
				DarkGray = 0xA9A9A9,
				/// <summary>
				/// DarkGreen(#006400)�̐F���擾���܂��D
				/// </summary>
				DarkGreen = 0x006400,
				/// <summary>
				/// DarkKhaki(#BDB76B)�̐F���擾���܂��D
				/// </summary>
				DarkKhaki = 0xBDB76B,
				/// <summary>
				/// DarkMagenta(#8B008B)�̐F���擾���܂��D
				/// </summary>
				DarkMagenta = 0x8B008B,
				/// <summary>
				/// DarkOliveGreen(#556B2F)�̐F���擾���܂��D
				/// </summary>
				DarkOliveGreen = 0x556B2F,
				/// <summary>
				/// DarkOrange(#FF8C00)�̐F���擾���܂��D
				/// </summary>
				DarkOrange = 0xFF8C00,
				/// <summary>
				/// DarkOrchid(#9932CC)�̐F���擾���܂��D
				/// </summary>
				DarkOrchid = 0x9932CC,
				/// <summary>
				/// DarkRed(#8B0000)�̐F���擾���܂��D
				/// </summary>
				DarkRed = 0x8B0000,
				/// <summary>
				/// DarkSalmon(#E9967A)�̐F���擾���܂��D
				/// </summary>
				DarkSalmon = 0xE9967A,
				/// <summary>
				/// DarkSeaGreen(#8FBC8B)�̐F���擾���܂��D
				/// </summary>
				DarkSeaGreen = 0x8FBC8B,
				/// <summary>
				/// DarkSlateBlue(#483D8B)�̐F���擾���܂��D
				/// </summary>
				DarkSlateBlue = 0x483D8B,
				/// <summary>
				/// DarkSlateGray(#2F4F4F)�̐F���擾���܂��D
				/// </summary>
				DarkSlateGray = 0x2F4F4F,
				/// <summary>
				/// DarkTurquoise(#00CED1)�̐F���擾���܂��D
				/// </summary>
				DarkTurquoise = 0x00CED1,
				/// <summary>
				/// DarkViolet(#9400D3)�̐F���擾���܂��D
				/// </summary>
				DarkViolet = 0x9400D3,
				/// <summary>
				/// DeepPink(#FF1493)�̐F���擾���܂��D
				/// </summary>
				DeepPink = 0xFF1493,
				/// <summary>
				/// DeepSkyBlue(#00BFFF)�̐F���擾���܂��D
				/// </summary>
				DeepSkyBlue = 0x00BFFF,
				/// <summary>
				/// DimGray(#696969)�̐F���擾���܂��D
				/// </summary>
				DimGray = 0x696969,
				/// <summary>
				/// DodgerBlue(#1E90FF)�̐F���擾���܂��D
				/// </summary>
				DodgerBlue = 0x1E90FF,
				/// <summary>
				/// Firebrick(#B22222)�̐F���擾���܂��D
				/// </summary>
				Firebrick = 0xB22222,
				/// <summary>
				/// FloralWhite(#FFFAF0)�̐F���擾���܂��D
				/// </summary>
				FloralWhite = 0xFFFAF0,
				/// <summary>
				/// ForestGreen(#228B22)�̐F���擾���܂��D
				/// </summary>
				ForestGreen = 0x228B22,
				/// <summary>
				/// Fuchsia(#FF00FF)�̐F���擾���܂��D
				/// </summary>
				Fuchsia = 0xFF00FF,
				/// <summary>
				/// Gainsboro(#DCDCDC)�̐F���擾���܂��D
				/// </summary>
				Gainsboro = 0xDCDCDC,
				/// <summary>
				/// GhostWhite(#F8F8FF)�̐F���擾���܂��D
				/// </summary>
				GhostWhite = 0xF8F8FF,
				/// <summary>
				/// Gold(#FFD700)�̐F���擾���܂��D
				/// </summary>
				Gold = 0xFFD700,
				/// <summary>
				/// Goldenrod(#DAA520)�̐F���擾���܂��D
				/// </summary>
				Goldenrod = 0xDAA520,
				/// <summary>
				/// Gray(#808080)�̐F���擾���܂��D
				/// </summary>
				Gray = 0x808080,
				/// <summary>
				/// Green(#008000)�̐F���擾���܂��D
				/// </summary>
				Green = 0x008000,
				/// <summary>
				/// GreenYellow(#ADFF2F)�̐F���擾���܂��D
				/// </summary>
				GreenYellow = 0xADFF2F,
				/// <summary>
				/// Honeydew(#F0FFF0)�̐F���擾���܂��D
				/// </summary>
				Honeydew = 0xF0FFF0,
				/// <summary>
				/// HotPink(#FF69B4)�̐F���擾���܂��D
				/// </summary>
				HotPink = 0xFF69B4,
				/// <summary>
				/// IndianRed(#CD5C5C)�̐F���擾���܂��D
				/// </summary>
				IndianRed = 0xCD5C5C,
				/// <summary>
				/// Indigo(#4B0082)�̐F���擾���܂��D
				/// </summary>
				Indigo = 0x4B0082,
				/// <summary>
				/// Ivory(#FFFFF0)�̐F���擾���܂��D
				/// </summary>
				Ivory = 0xFFFFF0,
				/// <summary>
				/// Khaki(#F0E68C)�̐F���擾���܂��D
				/// </summary>
				Khaki = 0xF0E68C,
				/// <summary>
				/// Lavender(#E6E6FA)�̐F���擾���܂��D
				/// </summary>
				Lavender = 0xE6E6FA,
				/// <summary>
				/// LavenderBlush(#FFF0F5)�̐F���擾���܂��D
				/// </summary>
				LavenderBlush = 0xFFF0F5,
				/// <summary>
				/// LawnGreen(#7CFC00)�̐F���擾���܂��D
				/// </summary>
				LawnGreen = 0x7CFC00,
				/// <summary>
				/// LemonChiffon(#FFFACD)�̐F���擾���܂��D
				/// </summary>
				LemonChiffon = 0xFFFACD,
				/// <summary>
				/// LightBlue(#ADD8E6)�̐F���擾���܂��D
				/// </summary>
				LightBlue = 0xADD8E6,
				/// <summary>
				/// LightCoral(#F08080)�̐F���擾���܂��D
				/// </summary>
				LightCoral = 0xF08080,
				/// <summary>
				/// LightCyan(#E0FFFF)�̐F���擾���܂��D
				/// </summary>
				LightCyan = 0xE0FFFF,
				/// <summary>
				/// LightGoldenrodYellow(#FAFAD2)�̐F���擾���܂��D
				/// </summary>
				LightGoldenrodYellow = 0xFAFAD2,
				/// <summary>
				/// LightGreen(#90EE90)�̐F���擾���܂��D
				/// </summary>
				LightGreen = 0x90EE90,
				/// <summary>
				/// LightGray(#D3D3D3)�̐F���擾���܂��D
				/// </summary>
				LightGray = 0xD3D3D3,
				/// <summary>
				/// LightPink(#FFB6C1)�̐F���擾���܂��D
				/// </summary>
				LightPink = 0xFFB6C1,
				/// <summary>
				/// LightSalmon(#FFA07A)�̐F���擾���܂��D
				/// </summary>
				LightSalmon = 0xFFA07A,
				/// <summary>
				/// LightSeaGreen(#20B2AA)�̐F���擾���܂��D
				/// </summary>
				LightSeaGreen = 0x20B2AA,
				/// <summary>
				/// LightSkyBlue(#87CEFA)�̐F���擾���܂��D
				/// </summary>
				LightSkyBlue = 0x87CEFA,
				/// <summary>
				/// LightSlateGray(#778899)�̐F���擾���܂��D
				/// </summary>
				LightSlateGray = 0x778899,
				/// <summary>
				/// LightSteelBlue(#B0C4DE)�̐F���擾���܂��D
				/// </summary>
				LightSteelBlue = 0xB0C4DE,
				/// <summary>
				/// LightYellow(#FFFFE0)�̐F���擾���܂��D
				/// </summary>
				LightYellow = 0xFFFFE0,
				/// <summary>
				/// Lime(#00FF00)�̐F���擾���܂��D
				/// </summary>
				Lime = 0x00FF00,
				/// <summary>
				/// LimeGreen(#32CD32)�̐F���擾���܂��D
				/// </summary>
				LimeGreen = 0x32CD32,
				/// <summary>
				/// Linen(#FAF0E6)�̐F���擾���܂��D
				/// </summary>
				Linen = 0xFAF0E6,
				/// <summary>
				/// Magenta(#FF00FF)�̐F���擾���܂��D
				/// </summary>
				Magenta = 0xFF00FF,
				/// <summary>
				/// Maroon(#800000)�̐F���擾���܂��D
				/// </summary>
				Maroon = 0x800000,
				/// <summary>
				/// MediumAquamarine(#66CDAA)�̐F���擾���܂��D
				/// </summary>
				MediumAquamarine = 0x66CDAA,
				/// <summary>
				/// MediumBlue(#0000CD)�̐F���擾���܂��D
				/// </summary>
				MediumBlue = 0x0000CD,
				/// <summary>
				/// MediumOrchid(#BA55D3)�̐F���擾���܂��D
				/// </summary>
				MediumOrchid = 0xBA55D3,
				/// <summary>
				/// MediumPurple(#9370DB)�̐F���擾���܂��D
				/// </summary>
				MediumPurple = 0x9370DB,
				/// <summary>
				/// MediumSeaGreen(#3CB371)�̐F���擾���܂��D
				/// </summary>
				MediumSeaGreen = 0x3CB371,
				/// <summary>
				/// MediumSlateBlue(#7B68EE)�̐F���擾���܂��D
				/// </summary>
				MediumSlateBlue = 0x7B68EE,
				/// <summary>
				/// MediumSpringGreen(#00FA9A)�̐F���擾���܂��D
				/// </summary>
				MediumSpringGreen = 0x00FA9A,
				/// <summary>
				/// MediumTurquoise(#48D1CC)�̐F���擾���܂��D
				/// </summary>
				MediumTurquoise = 0x48D1CC,
				/// <summary>
				/// MediumVioletRed(#C71585)�̐F���擾���܂��D
				/// </summary>
				MediumVioletRed = 0xC71585,
				/// <summary>
				/// MidnightBlue(#191970)�̐F���擾���܂��D
				/// </summary>
				MidnightBlue = 0x191970,
				/// <summary>
				/// MintCream(#F5FFFA)�̐F���擾���܂��D
				/// </summary>
				MintCream = 0xF5FFFA,
				/// <summary>
				/// MistyRose(#FFE4E1)�̐F���擾���܂��D
				/// </summary>
				MistyRose = 0xFFE4E1,
				/// <summary>
				/// Moccasin(#FFE4B5)�̐F���擾���܂��D
				/// </summary>
				Moccasin = 0xFFE4B5,
				/// <summary>
				/// NavajoWhite(#FFDEAD)�̐F���擾���܂��D
				/// </summary>
				NavajoWhite = 0xFFDEAD,
				/// <summary>
				/// Navy(#000080)�̐F���擾���܂��D
				/// </summary>
				Navy = 0x000080,
				/// <summary>
				/// OldLace(#FDF5E6)�̐F���擾���܂��D
				/// </summary>
				OldLace = 0xFDF5E6,
				/// <summary>
				/// Olive(#808000)�̐F���擾���܂��D
				/// </summary>
				Olive = 0x808000,
				/// <summary>
				/// OliveDrab(#6B8E23)�̐F���擾���܂��D
				/// </summary>
				OliveDrab = 0x6B8E23,
				/// <summary>
				/// Orange(#FFA500)�̐F���擾���܂��D
				/// </summary>
				Orange = 0xFFA500,
				/// <summary>
				/// OrangeRed(#FF4500)�̐F���擾���܂��D
				/// </summary>
				OrangeRed = 0xFF4500,
				/// <summary>
				/// Orchid(#DA70D6)�̐F���擾���܂��D
				/// </summary>
				Orchid = 0xDA70D6,
				/// <summary>
				/// PaleGoldenrod(#EEE8AA)�̐F���擾���܂��D
				/// </summary>
				PaleGoldenrod = 0xEEE8AA,
				/// <summary>
				/// PaleGreen(#98FB98)�̐F���擾���܂��D
				/// </summary>
				PaleGreen = 0x98FB98,
				/// <summary>
				/// PaleTurquoise(#AFEEEE)�̐F���擾���܂��D
				/// </summary>
				PaleTurquoise = 0xAFEEEE,
				/// <summary>
				/// PaleVioletRed(#DB7093)�̐F���擾���܂��D
				/// </summary>
				PaleVioletRed = 0xDB7093,
				/// <summary>
				/// PapayaWhip(#FFEFD5)�̐F���擾���܂��D
				/// </summary>
				PapayaWhip = 0xFFEFD5,
				/// <summary>
				/// PeachPuff(#FFDAB9)�̐F���擾���܂��D
				/// </summary>
				PeachPuff = 0xFFDAB9,
				/// <summary>
				/// Peru(#CD853F)�̐F���擾���܂��D
				/// </summary>
				Peru = 0xCD853F,
				/// <summary>
				/// Pink(#FFC0CB)�̐F���擾���܂��D
				/// </summary>
				Pink = 0xFFC0CB,
				/// <summary>
				/// Plum(#DDA0DD)�̐F���擾���܂��D
				/// </summary>
				Plum = 0xDDA0DD,
				/// <summary>
				/// PowderBlue(#B0E0E6)�̐F���擾���܂��D
				/// </summary>
				PowderBlue = 0xB0E0E6,
				/// <summary>
				/// Purple(#800080)�̐F���擾���܂��D
				/// </summary>
				Purple = 0x800080,
				/// <summary>
				/// Red(#FF0000)�̐F���擾���܂��D
				/// </summary>
				Red = 0xFF0000,
				/// <summary>
				/// RosyBrown(#BC8F8F)�̐F���擾���܂��D
				/// </summary>
				RosyBrown = 0xBC8F8F,
				/// <summary>
				/// RoyalBlue(#4169E1)�̐F���擾���܂��D
				/// </summary>
				RoyalBlue = 0x4169E1,
				/// <summary>
				/// SaddleBrown(#8B4513)�̐F���擾���܂��D
				/// </summary>
				SaddleBrown = 0x8B4513,
				/// <summary>
				/// Salmon(#FA8072)�̐F���擾���܂��D
				/// </summary>
				Salmon = 0xFA8072,
				/// <summary>
				/// SandyBrown(#F4A460)�̐F���擾���܂��D
				/// </summary>
				SandyBrown = 0xF4A460,
				/// <summary>
				/// SeaGreen(#2E8B57)�̐F���擾���܂��D
				/// </summary>
				SeaGreen = 0x2E8B57,
				/// <summary>
				/// SeaShell(#FFF5EE)�̐F���擾���܂��D
				/// </summary>
				SeaShell = 0xFFF5EE,
				/// <summary>
				/// Sienna(#A0522D)�̐F���擾���܂��D
				/// </summary>
				Sienna = 0xA0522D,
				/// <summary>
				/// Silver(#C0C0C0)�̐F���擾���܂��D
				/// </summary>
				Silver = 0xC0C0C0,
				/// <summary>
				/// SkyBlue(#87CEEB)�̐F���擾���܂��D
				/// </summary>
				SkyBlue = 0x87CEEB,
				/// <summary>
				/// SlateBlue(#6A5ACD)�̐F���擾���܂��D
				/// </summary>
				SlateBlue = 0x6A5ACD,
				/// <summary>
				/// SlateGray(#708090)�̐F���擾���܂��D
				/// </summary>
				SlateGray = 0x708090,
				/// <summary>
				/// Snow(#FFFAFA)�̐F���擾���܂��D
				/// </summary>
				Snow = 0xFFFAFA,
				/// <summary>
				/// SpringGreen(#00FF7F)�̐F���擾���܂��D
				/// </summary>
				SpringGreen = 0x00FF7F,
				/// <summary>
				/// SteelBlue(#4682B4)�̐F���擾���܂��D
				/// </summary>
				SteelBlue = 0x4682B4,
				/// <summary>
				/// Tan(#D2B48C)�̐F���擾���܂��D
				/// </summary>
				Tan = 0xD2B48C,
				/// <summary>
				/// Teal(#008080)�̐F���擾���܂��D
				/// </summary>
				Teal = 0x008080,
				/// <summary>
				/// Thistle(#D8BFD8)�̐F���擾���܂��D
				/// </summary>
				Thistle = 0xD8BFD8,
				/// <summary>
				/// Tomato(#FF6347)�̐F���擾���܂��D
				/// </summary>
				Tomato = 0xFF6347,
				/// <summary>
				/// Turquoise(#40E0D0)�̐F���擾���܂��D
				/// </summary>
				Turquoise = 0x40E0D0,
				/// <summary>
				/// Violet(#EE82EE)�̐F���擾���܂��D
				/// </summary>
				Violet = 0xEE82EE,
				/// <summary>
				/// Wheat(#F5DEB3)�̐F���擾���܂��D
				/// </summary>
				Wheat = 0xF5DEB3,
				/// <summary>
				/// White(#FFFFFF)�̐F���擾���܂��D
				/// </summary>
				White = 0xFFFFFF,
				/// <summary>
				/// WhiteSmoke(#F5F5F5)�̐F���擾���܂��D
				/// </summary>
				WhiteSmoke = 0xF5F5F5,
				/// <summary>
				/// Yellow(#FFFF00)�̐F���擾���܂��D
				/// </summary>
				Yellow = 0xFFFF00,
				/// <summary>
				/// YellowGreen(#9ACD32)�̐F���擾���܂��D
				/// </summary>
				YellowGreen = 0x9ACD32,
				/// <summary>
				/// ActiveBorder(#B4B4B4)�̐F���擾���܂��D
				/// </summary>
				ActiveBorder = 0xB4B4B4,
				/// <summary>
				/// ActiveCaption(#99B4D1)�̐F���擾���܂��D
				/// </summary>
				ActiveCaption = 0x99B4D1,
				/// <summary>
				/// ActiveCaptionText(#000000)�̐F���擾���܂��D
				/// </summary>
				ActiveCaptionText = 0x000000,
				/// <summary>
				/// AppWorkspace(#ABABAB)�̐F���擾���܂��D
				/// </summary>
				AppWorkspace = 0xABABAB,
				/// <summary>
				/// ButtonFace(#F0F0F0)�̐F���擾���܂��D
				/// </summary>
				ButtonFace = 0xF0F0F0,
				/// <summary>
				/// ButtonHighlight(#FFFFFF)�̐F���擾���܂��D
				/// </summary>
				ButtonHighlight = 0xFFFFFF,
				/// <summary>
				/// ButtonShadow(#A0A0A0)�̐F���擾���܂��D
				/// </summary>
				ButtonShadow = 0xA0A0A0,
				/// <summary>
				/// Control(#F0F0F0)�̐F���擾���܂��D
				/// </summary>
				Control = 0xF0F0F0,
				/// <summary>
				/// ControlDark(#A0A0A0)�̐F���擾���܂��D
				/// </summary>
				ControlDark = 0xA0A0A0,
				/// <summary>
				/// ControlDarkDark(#696969)�̐F���擾���܂��D
				/// </summary>
				ControlDarkDark = 0x696969,
				/// <summary>
				/// ControlLight(#E3E3E3)�̐F���擾���܂��D
				/// </summary>
				ControlLight = 0xE3E3E3,
				/// <summary>
				/// ControlLightLight(#FFFFFF)�̐F���擾���܂��D
				/// </summary>
				ControlLightLight = 0xFFFFFF,
				/// <summary>
				/// ControlText(#000000)�̐F���擾���܂��D
				/// </summary>
				ControlText = 0x000000,
				/// <summary>
				/// Desktop(#000000)�̐F���擾���܂��D
				/// </summary>
				Desktop = 0x000000,
				/// <summary>
				/// GradientActiveCaption(#B9D1EA)�̐F���擾���܂��D
				/// </summary>
				GradientActiveCaption = 0xB9D1EA,
				/// <summary>
				/// GradientInactiveCaption(#D7E4F2)�̐F���擾���܂��D
				/// </summary>
				GradientInactiveCaption = 0xD7E4F2,
				/// <summary>
				/// GrayText(#6D6D6D)�̐F���擾���܂��D
				/// </summary>
				GrayText = 0x6D6D6D,
				/// <summary>
				/// Highlight(#3399FF)�̐F���擾���܂��D
				/// </summary>
				Highlight = 0x3399FF,
				/// <summary>
				/// HighlightText(#FFFFFF)�̐F���擾���܂��D
				/// </summary>
				HighlightText = 0xFFFFFF,
				/// <summary>
				/// HotTrack(#0066CC)�̐F���擾���܂��D
				/// </summary>
				HotTrack = 0x0066CC,
				/// <summary>
				/// InactiveBorder(#F4F7FC)�̐F���擾���܂��D
				/// </summary>
				InactiveBorder = 0xF4F7FC,
				/// <summary>
				/// InactiveCaption(#BFCDDB)�̐F���擾���܂��D
				/// </summary>
				InactiveCaption = 0xBFCDDB,
				/// <summary>
				/// InactiveCaptionText(#000000)�̐F���擾���܂��D
				/// </summary>
				InactiveCaptionText = 0x000000,
				/// <summary>
				/// Info(#FFFFE1)�̐F���擾���܂��D
				/// </summary>
				Info = 0xFFFFE1,
				/// <summary>
				/// InfoText(#000000)�̐F���擾���܂��D
				/// </summary>
				InfoText = 0x000000,
				/// <summary>
				/// Menu(#F0F0F0)�̐F���擾���܂��D
				/// </summary>
				Menu = 0xF0F0F0,
				/// <summary>
				/// MenuBar(#F0F0F0)�̐F���擾���܂��D
				/// </summary>
				MenuBar = 0xF0F0F0,
				/// <summary>
				/// MenuHighlight(#3399FF)�̐F���擾���܂��D
				/// </summary>
				MenuHighlight = 0x3399FF,
				/// <summary>
				/// MenuText(#000000)�̐F���擾���܂��D
				/// </summary>
				MenuText = 0x000000,
				/// <summary>
				/// ScrollBar(#C8C8C8)�̐F���擾���܂��D
				/// </summary>
				ScrollBar = 0xC8C8C8,
				/// <summary>
				/// Window(#FFFFFF)�̐F���擾���܂��D
				/// </summary>
				Window = 0xFFFFFF,
				/// <summary>
				/// WindowFrame(#646464)�̐F���擾���܂��D
				/// </summary>
				WindowFrame = 0x646464,
				/// <summary>
				/// WindowText(#000000)�̐F���擾���܂��D
				/// </summary>
				WindowText = 0x000000,
			};
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
								Color(int R, int G, int B);
			/// <summary>
			///		�F�f�[�^���쐬����iHTML���̐F�R�[�h�Łj
			/// </summary>
			/// <param name = "RGBCode">
			///		RGB�R�[�h�D<see cref="ColorList">ColorList</see>����
			///		��`���ꂽ�l���g�p���邱�Ƃ��\�ł��D
			/// </param>
								Color(ColorList RGBCode);
			/// <summary>
			///		�N���X�ɓo�^����Ă���F�f�[�^��ԋp����
			/// </summary>
			inline DWORD		_GetColorToClass() const;
			/// <summary>
			///		���g�ƑΏۂ̐F����芄���Ńu�����h�������ʂ�ԋp����D
			/// </summary>
			/// <param name = "Target">
			///		���g�ƃu�����h����Ώۂ̐F�f�[�^�̃|�C���^�D
			/// </param>
			/// <param name = "Parcent">
			///		�u�����h���銄���D
			/// </param>
			DWORD				_GetColorBlends(const std::shared_ptr<Color> Target, int Parcent) const;
			///	<summary>
			///		�F�̐Ԑ����̋��x�D
			///	</summary>
			int					_Red;
			///	<summary>
			///		�F�̗ΐ����̋��x�D
			///	</summary>
			int					_Green;
			///	<summary>
			///		�F�̐����̋��x�D
			///	</summary>
			int					_Blue;
		};

	}
}
