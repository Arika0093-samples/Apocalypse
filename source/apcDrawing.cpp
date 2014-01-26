// --------------------------------------------------------
//	apcDrawing.cpp
// --------------------------------------------------------
//	apcDrawing.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
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
	// �`���ނ�������
	this->DrawMode			= FrameDrawMode::Nearest;
	// �e�t���[����TopParent�ɏ�����
	this->Parent			= __FrameCollection::GetInstance().GetTopParent();
	// �R���N�V�����ɒǉ�
	__FrameCollection::GetInstance().Insert(this);
}

// ----------------------------------------------------
//	FrameBase::~FrameBase (Destructor)
// ----------------------------------------------------
				__FrameBase::~__FrameBase()
{
	// FrameCollection���玩�g�̃f�[�^������
	__FrameCollection::GetInstance().Erase(this);
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
Point			__FrameBase::GetLocation() const
{
	return this->_Location;
}

// ----------------------------------------------------
//	FrameBase::ToString
// ----------------------------------------------------
String			__FrameBase::ToString() const
{
	return String()
		<< _T("Location: {") << _Location.ToString() << _T("}, ")
		<< _T("Width: ") << _Width
		<< _T(", Height: ") << _Height;
}

// ----------------------------------------------------
//	FrameBase::SetDefaultPosition
// ----------------------------------------------------
void			__FrameBase::_SetDefaultPosition()
{
	// �e�t���[�����擾
	auto PrtPtr = Parent;
	// �����e�t���[�������݂��Ȃ��Ȃ�
	if(!PrtPtr){
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
			this->_Location.X += ((PrtPtr->_Location.X) + (this->Points.X));
			break;
		// (X���W)���S����ɕ\������Ȃ�
		case FramePosition::TopCenter:
		case FramePosition::MiddleCenter:
		case FramePosition::BottomCenter:
			// �e��X���W + (�e�̕�/2)��ǉ��D
			this->_Location.X += ((PrtPtr->_Location.X) + (this->Points.X)
							  + ((PrtPtr->_Width) / 2));
			break;
		// (X���W)��ԉE����ɕ\������Ȃ�
		case FramePosition::TopRight:
		case FramePosition::MiddleRight:
		case FramePosition::BottomRight:
			// �e��X���W + �e�̕���ǉ��D
			this->_Location.X += ((PrtPtr->_Location.X) + (this->Points.X)
							  +  (PrtPtr->_Width));
			break;
	}
	// ��Ƃ���ʒu�Ŕ���(Y���W)�D
	switch(this->Position){
		// (Y���W)��ԏ����ɂ���Ȃ�
		case FramePosition::TopLeft:
		case FramePosition::TopCenter:
		case FramePosition::TopRight:
			// �e��Y���W�����̂܂ܒǉ��D
			this->_Location.Y += ((PrtPtr->_Location.Y) + (this->Points.Y));
			break;
		// (Y���W)���S����ɕ\������Ȃ�
		case FramePosition::MiddleLeft:
		case FramePosition::MiddleCenter:
		case FramePosition::MiddleRight:
			// �e��Y���W + (�e�̍���/2)��ǉ��D
			this->_Location.Y += ((PrtPtr->_Location.Y) + (this->Points.Y)
							  + ((PrtPtr->_Height) / 2));
			break;
		// (Y���W)��ԉ�����ɕ\������Ȃ�
		case FramePosition::BottomLeft:
		case FramePosition::BottomCenter:
		case FramePosition::BottomRight:
			// �e��Y���W + �e�̍�����ǉ��D
			this->_Location.Y += ((PrtPtr->_Location.Y) + (this->Points.Y)
							  +  (PrtPtr->_Height));
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
		// �e�t���[�����擾
		auto PrtPtr = Parent;
		// ���������Ȃ�
		if(!PrtPtr){
			// ��O�𓊂��Ă������C������
			// throw XXXX;
			return;
		}
		// �����Əc�����w�肷��
		_Width  = (PrtPtr->GetWidth ())* (Width)/100;
		_Height = (PrtPtr->GetHeight())*(Height)/100;
	}
	// �I���D
	return;
}

// ----------------------------------------------------
//	GradationFrame
// ----------------------------------------------------
//	GradationFrame::ToString
// ----------------------------------------------------
String			GradationFrame::ToString() const
{
	return this->__FrameBase::ToString()
		<< _T(", Start: {")	<< (StartGradColor	? StartGradColor->ToString(): _T("empty")) << _T("}")
		<< _T(", End: {")	<< (EndGradColor	? EndGradColor->ToString()	: _T("empty")) << _T("}")
		<< _T(", Border: {")<< (BorderColor		? BorderColor->ToString()	: _T("empty")) << _T("}");
}

// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame() const
{
	// �����O���f�[�V�����J�n�F���ݒ肳��Ă���
	if(this->StartGradColor){
		// �I���F���w�肳��Ă��Ȃ�or�J�n�F�ƏI���F�������ꍇ�Ȃ�
		if(EndGradColor == NULL || StartGradColor->_Compare(EndGradColor)){
			// ���u�����h�K�p
			StartGradColor->_AppendAlpha();
			// �P�F�h��
			DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
					(_Location.Y + GetHeight()), StartGradColor->_GetColor(), TRUE);
		}
		// �I���F���w�肳��Ă���ꍇ��
		else {
			// �O���f�[�V������`�悷��
			for(int Y = 0; Y < this->GetHeight(); Y++){
				// �`�悷��F���擾����
				auto DrawColor = StartGradColor->_GetColorBlends(EndGradColor, (Y*100/GetHeight()));
				// ���u�����h�K�p
				DrawColor->_AppendAlpha();
				// ��{���`�悷��
				DrawLine(_Location.X, _Location.Y + Y, _Location.X + GetWidth() - 1,
						 _Location.Y + Y, DrawColor->_GetColor());
			}
		}
	}
	// ���E���`��̐F�����܂��Ă���Ȃ��
	if(this->BorderColor){
		// ���u�����h�K�p
		BorderColor->_AppendAlpha();
		// �`�悷��D
		DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
				(_Location.Y + GetHeight()), BorderColor->_GetColor(), FALSE);
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
	this->Path				= ImgPath;
	this->_PicturePath		= ImgPath;
	// �摜�T�C�Y�������Əc���Ɏw�肷��
	GetGraphSize(_PictureHandle, &_Width, &_Height);
	// �s�����x��255�Ɏw�肷��
	Alpha = 255;
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
//	PictureFrame::ToString
// ----------------------------------------------------
String			PictureFrame::ToString() const
{
	return this->__FrameBase::ToString()
		<< _T(", Path: \"") << Path << _T("\"")
		<< _T(", Alpha: ")<< Alpha;
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			PictureFrame::_SetProperties()
{
	// �����w�肳��Ă���摜�t�@�C�����ς���Ă���Ȃ�
	if(Path != _PicturePath){
		// ���݂̉摜��j������
		DeleteGraph(_PictureHandle);
		// �ǂݍ��ݒ���
		_PictureHandle = LoadGraph(Path);
		// �R�s�[
		_PicturePath = Path;
	}
	// �摜�T�C�Y�������Əc���Ɏw�肷��
	GetGraphSize(_PictureHandle, &_Width, &_Height);
}

// ----------------------------------------------------
//	PictureFrame::DrsawThisFrame
// ----------------------------------------------------
void			PictureFrame::_DrawThisFrame() const
{
	// ���u�����h��L����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	// �摜��`�悷��
	DrawGraph(_Location.X, _Location.Y, _PictureHandle, TRUE);
}

// ----------------------------------------------------
//	AreaPictureFrame
// ----------------------------------------------------
//	AreaPictureFrame::AreaPictureFrame (Constructor)
// ----------------------------------------------------
				AreaPictureFrame::AreaPictureFrame(String ImgPath)
					: PictureFrame(ImgPath)
{
	// ����������
	TileX = 0;
	TileY = 0;
	StretchDraw = false;
}

// ----------------------------------------------------
//	AreaPictureFrame::ToString
// ----------------------------------------------------
String			AreaPictureFrame::ToString() const
{
	return this->PictureFrame::ToString();
}

// ----------------------------------------------------
//	AreaPictureFrame::SetProperties
// ----------------------------------------------------
void			AreaPictureFrame::_SetProperties()
{
	// EdgeFrame�̕����Ăяo��
	this->EdgeFrame::_SetProperties();
}

// ----------------------------------------------------
//	AreaPictureFrame::DrawThisFrame
// ----------------------------------------------------
void			AreaPictureFrame::_DrawThisFrame() const
{
	// �`��摜�̏c����
	int PictWidth, PictHeight;
	// -------------------------------------
	// �`��̈���w�肵�Ă���
	SetDrawArea(_Location.X, _Location.Y, (_Location.X + _Width), (_Location.Y + _Height));
	// �`��摜�̏c�������擾����
	GetGraphSize(_PictureHandle, &PictWidth, &PictHeight);
	// ���u�����h��L����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
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
//	MovieFrame::ToString
// ----------------------------------------------------
String			MovieFrame::ToString() const
{
	return this->__FrameBase::ToString();
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
	// ���u�����h��L����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);

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
	// �W���ŕ������肵�Ȃ�
	AdvanceTimer.Add = 0;
	// �F������������
	TextColor	= std::shared_ptr<Color>(new Color(255,255,255));
}

// ----------------------------------------------------
//	StringFrame::ToString
// ----------------------------------------------------
String			StringFrame::ToString() const
{
	return this->__FrameBase::ToString()
		<< _T(", Text: \"") << Text << _T("\"")
		<< (AdvanceTimer.Add != 0 ? String() << _T(", ShowTextLenght: ")
		<< (int)AdvanceTimer._GetValueNoReload() / 100 : _T(""))
		<< _T(", Font: {") << TextFont->ToString() << _T("}")
		<< _T(", Color: {") << TextColor->ToString() << _T("}");
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
	// �`�敶�����X�V
	_SetDrawString();
}

// ----------------------------------------------------
//	StringFrame::DrawThisFrame
// ----------------------------------------------------
void			StringFrame::_DrawThisFrame() const
{
	// ���u�����h��L����
	TextColor->_AppendAlpha();
	// �������`�悷��D
	DrawStringToHandle(_Location.X, _Location.Y, _DrawText,
			this->TextColor->_GetColor(), this->TextFont->_GetFontHandle());
}

// ----------------------------------------------------
//	StringFrame::GetDrawString
// ----------------------------------------------------
void			StringFrame::_SetDrawString()
{
	// Timer�l���ŕ�����擪���珇�Ɏ擾����
	_DrawText = Text.substr(0, (AdvanceTimer.Add != 0 ? AdvanceTimer() / 100 : Text.length()));
}

// ----------------------------------------------------
//	Font
// ----------------------------------------------------
//	Font::Font (Constructor/None)
// ----------------------------------------------------
				Font::Font()
{
	// �W���t�H���g���g�p����
	_Name	= ApplicationConfig::DefaultFontName;
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
	_Name	= ApplicationConfig::DefaultFontName;
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
//	StringFrame::ToString
// ----------------------------------------------------
String			Font::ToString() const
{
	return String() << _T("Name: \"") << _Name << _T("\"")
		<< _T(", Size: ") << _Size
		<< _T(", Thick: ") << _Thick;
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
				Color::Color(int Rp, int Gp, int Bp)
{
	// �l���w�肷��
	this->R	= Rp;
	this->G	= Gp;
	this->B	= Bp;
	this->A	= 255;
}

// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color(int Ap, int Rp, int Gp, int Bp)
{
	// �l���w�肷��
	this->R	= Rp;
	this->G	= Gp;
	this->B	= Bp;
	this->A	= Ap;
}

// ----------------------------------------------------
//	Color::Color (RGB Code version)
// ----------------------------------------------------
				Color::Color(Color::_ColorList ARGBCode)
{
	// �l���V�t�g���Z�Ŏw�肷��
	this->A	= ((ARGBCode >> 24) & 0xFF);
	this->R	= ((ARGBCode >> 16) & 0xFF);
	this->G	= ((ARGBCode >>  8) & 0xFF);
	this->B	= ((ARGBCode >>  0) & 0xFF);
}

// ----------------------------------------------------
//	Color::Color (RGB Code version, Set Alpha)
// ----------------------------------------------------
				Color::Color(Color::_ColorList RGBCode, int Alpha)
{
	// �l���V�t�g���Z�Ŏw�肷��
	this->R	= ((RGBCode >> 16) & 0xFF);
	this->G	= ((RGBCode >>  8) & 0xFF);
	this->B	= ((RGBCode >>  0) & 0xFF);
	// �����̒l���w�肷��
	this->A	= Alpha;
}

// ----------------------------------------------------
//	Color::ToString
// ----------------------------------------------------
String			Color::ToString() const
{
	return String() << _T("Alpha: ") << A
		<< _T(", Red: ") << R
		<< _T(", Blue: ") << B
		<< _T(", Green: ") << G;
}

// ----------------------------------------------------
//	Color::GetColor
// ----------------------------------------------------
inline DWORD	Color::_GetColor() const
{
	return GetColor(this->R, this->G, this->B);
}

// ----------------------------------------------------
//	Color::AppendAlpha
// ----------------------------------------------------
inline void		Color::_AppendAlpha() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, A);
}

// ----------------------------------------------------
//	Color::Compare
// ----------------------------------------------------
bool			Color::_Compare(const std::shared_ptr<Color> Target) const
{
	return Target->A == A
		&& Target->R == R
		&& Target->B == B
		&& Target->G == G;
}

// ----------------------------------------------------
//	Color::GetColorBlends
// ----------------------------------------------------
std::shared_ptr<Color>
				Color::_GetColorBlends(const std::shared_ptr<Color> Target, int Parcent) const
{
	// �F���ƂɎ擾����
	int _Red	= (Target->R * Parcent)/100 + (R * (100-Parcent))/100;
	int _Green	= (Target->G * Parcent)/100 + (G * (100-Parcent))/100;
	int _Blue	= (Target->B * Parcent)/100 + (B * (100-Parcent))/100;
	int _Alpha	= (Target->A * Parcent)/100 + (A * (100-Parcent))/100;
	// �쐬���ĕԋp����
	return New(Color, _Alpha, _Red, _Green, _Blue);
}