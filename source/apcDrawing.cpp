// --------------------------------------------------------
//	apcDrawing.cpp
// --------------------------------------------------------
//	apcDrawing.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
//#define APOCALYPSE_USEALLNAMESPACE
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	FrameBase
// ----------------------------------------------------
//	FrameBase::FrameBase (Constructor)
// ----------------------------------------------------
				__FrameBase::__FrameBase()
{
	// �L���ɂ���
	this->Enable			= true;
	this->Visible			= true;
	// �`�揇�Ԃ�������ԂɃ��Z�b�g����
	this->DrawOrder			= 0;
	// �����c�������Z�b�g����
	this->_Width			= 0;
	this->_Height			= 0;
	// �`��ʒu��������
	this->Position			= FramePosition::Default;
	this->Interpret			= FramePosition::Default;
	// �e�t���[����W���l�ɏ�����
	this->Parent			= NULL;
	// �s�����ɐݒ�D
	this->Alpha				= 255;
	// �R���N�V�����ɒǉ�
	__FrameCollection::GetInstance().Insert(std::shared_ptr<__FrameBase>(this));
}

// ----------------------------------------------------
//	FrameBase::~FrameBase (Destructor)
// ----------------------------------------------------
				__FrameBase::~__FrameBase()
{
	// FrameCollection���玩�g�̃f�[�^������
	__FrameCollection::GetInstance().Erase(std::shared_ptr<__FrameBase>(this));
}

// ----------------------------------------------------
//	FrameBase::GetWidth
// ----------------------------------------------------
inline int		__FrameBase::GetWidth() const
{
	return this->_Width;
}

// ----------------------------------------------------
//	FrameBase::GetFrameHeight
// ----------------------------------------------------
inline int		__FrameBase::GetHeight() const
{
	return this->_Height;
}

// ----------------------------------------------------
//	FrameBase::GetFrameLocation
// ----------------------------------------------------
inline Point	__FrameBase::GetLocation() const
{
	return this->_Location;
}

// ----------------------------------------------------
//	FrameBase::SetDefaultPosition
// ----------------------------------------------------
void			__FrameBase::_SetDefaultPosition()
{
	// �����e�t���[�������݂��Ȃ��Ȃ�
	if(!this->Parent){
		// �I��
		return;
	}
	// �`��ꏊ��0�ŏ���������D
	this->_Location = 0;
	// ��Ƃ���ʒu�Ŕ���(X���W)�D
	switch(this->Position){
		// (X���W)��ԍ�����ɂ���Ȃ�
		case FramePosition::TopLeft:
		case FramePosition::MiddleLeft:
		case FramePosition::BottomLeft:
			// �e��X���W�����̂܂ܒǉ��D
			this->_Location.X += ((this->Parent->_Location.X) + (this->Points.X));
			break;
		// (X���W)���S����ɕ\������Ȃ�
		case FramePosition::TopCenter:
		case FramePosition::MiddleCenter:
		case FramePosition::BottomCenter:
			// �e��X���W + (�e�̕�/2)��ǉ��D
			this->_Location.X += ((this->Parent->_Location.X) + (this->Points.X)
							  + ((this->Parent->_Width) / 2));
			break;
		// (X���W)��ԉE����ɕ\������Ȃ�
		case FramePosition::TopRight:
		case FramePosition::MiddleRight:
		case FramePosition::BottomRight:
			// �e��X���W + �e�̕���ǉ��D
			this->_Location.X += ((this->Parent->_Location.X) + (this->Points.X)
							  +  (this->Parent->_Width));
			break;
	}
	// ��Ƃ���ʒu�Ŕ���(Y���W)�D
	switch(this->Position){
		// (Y���W)��ԏ����ɂ���Ȃ�
		case FramePosition::TopLeft:
		case FramePosition::TopCenter:
		case FramePosition::TopRight:
			// �e��Y���W�����̂܂ܒǉ��D
			this->_Location.Y += ((this->Parent->_Location.Y) + (this->Points.Y));
			break;
		// (Y���W)���S����ɕ\������Ȃ�
		case FramePosition::MiddleLeft:
		case FramePosition::MiddleCenter:
		case FramePosition::MiddleRight:
			// �e��Y���W + (�e�̍���/2)��ǉ��D
			this->_Location.Y += ((this->Parent->_Location.Y) + (this->Points.Y)
							  + ((this->Parent->_Height) / 2));
			break;
		// (Y���W)��ԉ�����ɕ\������Ȃ�
		case FramePosition::BottomLeft:
		case FramePosition::BottomCenter:
		case FramePosition::BottomRight:
			// �e��Y���W + �e�̍�����ǉ��D
			this->_Location.Y += ((this->Parent->_Location.Y) + (this->Points.Y)
							  +  (this->Parent->_Height));
			break;
	}
	// ���߈ʒu���m�F(X���W)
	switch(this->Interpret){
		// ��ԍ�����ɂ���Ȃ�
		case FramePosition::TopLeft:
		case FramePosition::MiddleLeft:
		case FramePosition::BottomLeft:
			// ���ɉ������Ȃ�
			break;
		// ��������ɂ���Ȃ�
		case FramePosition::TopCenter:
		case FramePosition::MiddleCenter:
		case FramePosition::BottomCenter:
			// ���̔����������D
			this->_Location.X -= (this->_Width / 2);
			break;
		// ��ԉE����ɂ���Ȃ�
		case FramePosition::TopRight:
		case FramePosition::MiddleRight:
		case FramePosition::BottomRight:
			// ���������D
			this->_Location.X -= (this->_Width);
			break;
	}
	// ���߈ʒu���m�F(Y���W)
	switch(this->Interpret){
		// ��ԏ����ɂ���Ȃ�
		case FramePosition::TopLeft:
		case FramePosition::TopCenter:
		case FramePosition::TopRight:
			// ���ɉ������Ȃ�
			break;
		// ���S����ɂ���Ȃ�
		case FramePosition::MiddleLeft:
		case FramePosition::MiddleCenter:
		case FramePosition::MiddleRight:
			// �����̔����������D
			this->_Location.Y -= (this->_Height / 2);
			break;
		// ��ԉ�����ɂ���Ȃ�
		case FramePosition::BottomLeft:
		case FramePosition::BottomCenter:
		case FramePosition::BottomRight:
			// �����������D
			this->_Location.Y -= (this->_Height);
			break;
	}
}

// ----------------------------------------------------
//	EdgeFrame
// ----------------------------------------------------
//	EdgeFrame::EdgeFrame (Constructor)
// ----------------------------------------------------
				EdgeFrame::EdgeFrame()
{
	// ���w��ŕ`�悷��悤�w��
	this->SpecifyWithParcent = true;
	// �c������100%�Ɏw��
	this->Width		= 100;
	this->Height	= 100;
}

// ----------------------------------------------------
//	EdgeFrame::SetProperties
// ----------------------------------------------------
void			EdgeFrame::_SetProperties()
{
	// �������w��łȂ��Ȃ�
	if(this->SpecifyWithParcent == false){
		// Param�Ɏw�肳�ꂽ�l�����̂܂܎g�p����
		this->_Width	= Width;
		this->_Height	= Height;
	}
	// ����%�w��Ȃ�
	else {
		// �����Əc�����w�肷��
		_Width  = (Parent->GetWidth ())* (Width)/100;
		_Height = (Parent->GetHeight())*(Height)/100;
	}
	// �I���D
	return;
}

// ----------------------------------------------------
//	GradationFrame
// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame() const
{
	// �����O���f�[�V�����J�n�F���ݒ肳��Ă���
	if(this->StartGradColor){
		// �I���F���w�肳��Ă��Ȃ�or�J�n�F�ƏI���F�������ꍇ�Ȃ�
		if(this->EndGradColor == NULL
		|| this->StartGradColor->_GetColorToClass() == this->EndGradColor->_GetColorToClass()){
			// �P�F�h��
			DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
					(_Location.Y + GetHeight()), StartGradColor->_GetColorToClass(), TRUE);
		}
		// �I���F���w�肳��Ă���ꍇ��
		else {
			// �O���f�[�V������`�悷��
			for(int Y = 0; Y < this->GetHeight(); Y++){
				// ��{���`�悷��D
				DrawLine(_Location.Y, _Location.Y + Y,
						 _Location.X + GetWidth() - 1, _Location.Y + Y,
						 StartGradColor->_GetColorBlends(EndGradColor, (Y*100/GetHeight())));
			}
		}
	}
	// ���E���`��̐F�����܂��Ă���Ȃ��
	if(this->BorderColor){
		// �`�悷��D
		DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
				(_Location.Y + GetHeight()), BorderColor->_GetColorToClass(), FALSE);
	}
}

// ----------------------------------------------------
//	PictureFrame
// ----------------------------------------------------
//	PictureFrame::PictureFrame (Constructor)
// ----------------------------------------------------
				PictureFrame::PictureFrame(String ImgPath)
{
	// �n���h�����Z�b�g����
	this->_PictureHandle	= LoadGraph(ImgPath);
	// �摜�p�X���Z�b�g����
	this->_PicturePath		= ImgPath;
	// �摜�T�C�Y�������Əc���Ɏw�肷��
	GetGraphSize(_PictureHandle, &_Width, &_Height);
}

// ----------------------------------------------------
//	PictureFrame::~PictureFrame (Destructor)
// ----------------------------------------------------
				PictureFrame::~PictureFrame()
{
	// �摜���폜����
	DeleteGraph(this->_PictureHandle);
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			PictureFrame::_SetProperties()
{
	// �摜�T�C�Y�������Əc���Ɏw�肷��
	GetGraphSize(_PictureHandle, &_Width, &_Height);
}

// ----------------------------------------------------
//	PictureFrame::DrawThisFrame
// ----------------------------------------------------
void			PictureFrame::_DrawThisFrame() const
{
	// �摜��`�悷��
	DrawGraph(_Location.X, _Location.Y, _PictureHandle, TRUE);
}

// ----------------------------------------------------
//	PictureFrame::ExchangePicture
// ----------------------------------------------------
bool			PictureFrame::ExchangePicture(String ImgPath, int Handle)
{
	// �����摜���������̂�������
	if(_PicturePath == ImgPath){
		// false��Ԃ��D
		return false;
	}
	// ���݂̃n���h�����폜����
	DeleteGraph(_PictureHandle);
	// �n���h�����Z�b�g����
	this->_PictureHandle	= ( Handle ? Handle : LoadGraph(ImgPath) );
	// �摜�p�X���Z�b�g����
	this->_PicturePath		= ImgPath;
	// �摜�T�C�Y�������Əc���Ɏw�肷��
	GetGraphSize(_PictureHandle, &_Width, &_Height);
	// true��Ԃ�
	return true;
}

// ----------------------------------------------------
//	TilePictureFrame
// ----------------------------------------------------
//	TilePictureFrame::TilePictureFrame (Constructor)
// ----------------------------------------------------
				TilePictureFrame::TilePictureFrame(String ImgPath)
					: PictureFrame(ImgPath)
{
	// ����������
	TileX = 0;
	TileY = 0;
	StretchDraw = false;
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			TilePictureFrame::_SetProperties()
{
	// EdgeFrame�̕����Ăяo��
	this->EdgeFrame::_SetProperties();
}

// ----------------------------------------------------
//	PictureFrame::DrawThisFrame
// ----------------------------------------------------
void			TilePictureFrame::_DrawThisFrame() const
{
	// �`��摜�̏c����
	int PictWidth, PictHeight;
	// -------------------------------------
	// �`��̈���w�肵�Ă���
	SetDrawArea(_Location.X, _Location.Y, (_Location.X + _Width), (_Location.Y + _Height));
	// �`��摜�̏c�������擾����
	GetGraphSize(_PictureHandle, &PictWidth, &PictHeight);
	// ���������L�΂��ĕ`�悷��Ȃ�
	if(StretchDraw){
		// �g��`��
		DrawExtendGraph(_Location.X, _Location.Y, _Location.X + _Width,
						_Location.Y + _Height, _PictureHandle, TRUE);
	}
	// �J��Ԃ��ŕ`�悷��Ȃ�
	else{
		// X���W�̃��[�v
		for(int LocX=(_Location.X+(TileX%PictWidth)-PictWidth); LocX<(_Location.X+_Width); LocX+=PictWidth){
			// Y���W�̃��[�v
			for(int LocY=(_Location.Y+(TileY%PictHeight)-PictHeight);LocY<(_Location.Y+_Height);LocY+=PictHeight){
				// �摜��`�悷��
				DrawGraph(LocX, LocY, _PictureHandle, TRUE);
			}
		}
	}
	// �`��̈�����ɖ߂�
	SetDrawAreaFull();
}

// ----------------------------------------------------
//	MovieFrame
// ----------------------------------------------------
//	MovieFrame::MovieFrame (Constructor)
// ----------------------------------------------------
				MovieFrame::MovieFrame(String MovPath)
{
}

// ----------------------------------------------------
//	MovieFrame::SetProperties
// ----------------------------------------------------
void			MovieFrame::_SetProperties()
{

}

// ----------------------------------------------------
//	MovieFrame::DrawThisFrame
// ----------------------------------------------------
void			MovieFrame::_DrawThisFrame() const
{

}

// ----------------------------------------------------
//	StringFrame
// ----------------------------------------------------
//	StringFrame::StringFrame (Constructor)
// ----------------------------------------------------
				StringFrame::StringFrame(String Str)
{
	// ��������R�s�[����
	this->Text	= Str;
	// �F������������
	TextColor	= std::shared_ptr<Color>(new Color(255,255,255));
}

// ----------------------------------------------------
//	StringFrame::SetProperties
// ----------------------------------------------------
void			StringFrame::_SetProperties()
{
	// �c�����擾����
	int HeightSave = 0;
	// ----------------------------------------------------
	// �����t�H���g�����쐬�Ȃ�
	if(!this->TextFont){
		// �t�H���g��V�K�쐬
		this->TextFont = std::shared_ptr<Font>(new Font());
	}
	// �������擾����
	this->_Width  = GetDrawStringWidthToHandle(Text,
						Text.length(), TextFont->_GetFontHandle());
	// �c�����w�肷��
	GetFontStateToHandle(NULL, &HeightSave, NULL, TextFont->_GetFontHandle());
	// �ݒ�
	_Height = HeightSave;
}

// ----------------------------------------------------
//	StringFrame::DrawThisFrame
// ----------------------------------------------------
void			StringFrame::_DrawThisFrame() const
{
	// �������`�悷��D
	DrawStringToHandle(_Location.X, _Location.Y, this->Text,
			this->TextColor->_GetColorToClass(), this->TextFont->_GetFontHandle());
}

// ----------------------------------------------------
//	Font
// ----------------------------------------------------
//	Font::Font (Constructor/None)
// ----------------------------------------------------
				Font::Font()
{
	// �W���t�H���g���g�p����
	_Name	= __ApcSystem::GetInstance().GameSetting->DefaultFontName;
	// �v���p�e�B���Z�b�g����
	_Size	= 16;
	_Thick	= 0;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// �t�H���g�n���h�����쐬����
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Size)
// ----------------------------------------------------
				Font::Font(int FontSize)
{
	// �W���t�H���g���g�p����
	_Name	= __ApcSystem::GetInstance().GameSetting->DefaultFontName;
	// �v���p�e�B���Z�b�g����
	_Size	= FontSize;
	_Thick	= 0;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// �t�H���g�n���h�����쐬����
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize)
{
	// �W���t�H���g���g�p����
	_Name	= FontName;
	// �v���p�e�B���Z�b�g����
	_Size	= FontSize;
	_Thick	= 0;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// �t�H���g�n���h�����쐬����
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size,Thick)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick)
{
	// �W���t�H���g���g�p����
	_Name	= FontName;
	// �v���p�e�B���Z�b�g����
	_Size	= FontSize;
	_Thick	= FontThick;
	_Type	= DX_FONTTYPE_ANTIALIASING;
	// �t�H���g�n���h�����쐬����
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::Font (Constructor/All)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick, int FontType)
{
	// �W���t�H���g���g�p����
	_Name	= FontName;
	// �v���p�e�B���Z�b�g����
	_Size	= FontSize;
	_Thick	= FontThick;
	_Type	= FontType;
	// �t�H���g�n���h�����쐬����
	_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _Type);
}

// ----------------------------------------------------
//	Font::~Font (Destructor)
// ----------------------------------------------------
				Font::~Font()
{
	// �t�H���g���폜����
	DeleteFontToHandle(this->_Handle);
}

// ----------------------------------------------------
//	Font::GetFontHandle
// ----------------------------------------------------
inline int		Font::_GetFontHandle() const
{
	return this->_Handle;
}

// ----------------------------------------------------
//	Color
// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color(int R, int G, int B)
{
	// �l���w�肷��
	this->_Red		= R;
	this->_Green	= G;
	this->_Blue		= B;
}

// ----------------------------------------------------
//	Color::Color (RGB Code version)
// ----------------------------------------------------
				Color::Color(Color::ColorList RGBCode)
{
	// �l���V�t�g���Z�Ŏw�肷��
	this->_Red		= ((RGBCode >> 16) & 0xFF);
	this->_Green	= ((RGBCode >>  8) & 0xFF);
	this->_Blue		= ((RGBCode >>  0) & 0xFF);
}

// ----------------------------------------------------
//	Color::ColorToClass
// ----------------------------------------------------
inline DWORD	Color::_GetColorToClass() const
{
	return GetColor(this->_Red, this->_Green, this->_Blue);
}

// ----------------------------------------------------
//	Color::ColorToClass
// ----------------------------------------------------
DWORD			Color::_GetColorBlends(const std::shared_ptr<Color> Target, int Parcent) const
{
	// �F���ƂɎ擾����
	int Red		= ((Target->_Red)*(Parcent)/(100))	+ ((this->_Red)*(100-(Parcent))/(100));
	int Green	= ((Target->_Green)*(Parcent)/(100))+ ((this->_Green)*(100-(Parcent))/(100));
	int Blue	= ((Target->_Blue)*(Parcent)/(100))	+ ((this->_Blue)*(100-(Parcent))/(100));
	// �쐬���ĕԋp����
	return DxLib::GetColor(Red, Green, Blue);
}
