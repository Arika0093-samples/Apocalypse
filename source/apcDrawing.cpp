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
				_FrameBase::_FrameBase()
{
	// �L���ɂ���
	this->Enable				= true;
	this->Visible				= true;
	// �`�揇�Ԃ�������ԂɃ��Z�b�g����
	this->DrawOrder				= 0;
	// �W���Řg���`�悷��
	this->DrawFramework			= true;
	// �W���ňʒu���킹���s��
	this->_AutoAdjustPosition	= true;
	// �`���ނ�������
	this->DrawMode				= FrameDrawMode::Bilinear;
	// Margin��������
	this->Margin.Left			= MarginRectangle::Auto;
	this->Margin.Right			= MarginRectangle::Auto;
	this->Margin.Top			= MarginRectangle::Auto;
	this->Margin.Bottom			= MarginRectangle::Auto;
	// �e�t���[����TopParent�ɏ�����
	this->Parent				= _FrameCollection::GetInstance().GetTopParent();
	// �R���N�V�����ɒǉ�
	_FrameCollection::GetInstance().Insert(this);
}

// ----------------------------------------------------
//	FrameBase::~FrameBase (Destructor)
// ----------------------------------------------------
				_FrameBase::~_FrameBase()
{
	// FrameCollection���玩�g�̃f�[�^������
	_FrameCollection::GetInstance().Erase(this);
}

// ----------------------------------------------------
//	FrameBase::GetFrameArea
// ----------------------------------------------------
RectangleArea	_FrameBase::GetFrameArea() const
{
	// �ԋp�p�Ɋm��
	RectangleArea Rect;
	// ------------------------------------------------
	// �e�t���[�������݂���Ȃ�
	if(Parent != nullptr && Parent != _FrameCollection::GetInstance().GetTopParent()){
		// �e�t���[����ActualArea���擾����
		Rect = Parent->GetActualArea();
	}
	// ���݂��Ȃ� or ��ԏ�̃t���[���Ȃ�
	else {
		// �̈���w�肷��
		Rect.Location.X	= 0;
		Rect.Location.Y	= 0;
		Rect.Width		= System::ApplicationConfig::Width;
		Rect.Height		= System::ApplicationConfig::Height;
	}
	// �ԋp
	return Rect;
}

// ----------------------------------------------------
//	FrameBase::GetFrameLocation
// ----------------------------------------------------
RectangleArea	_FrameBase::GetActualArea() const
{
	// Magin���l�������̈���擾
	RectangleArea Rect = GetFrameArea();
	// ------------------------------------------------
	// ���̃t���[���̏c�������擾
	Rect.Width	= (_GetActualWidth()  != -1 ? _GetActualWidth()  : Rect.Width);
	Rect.Height	= (_GetActualHeight() != -1 ? _GetActualHeight() : Rect.Height);
	// �̈���v�Z���ĕԋp
	return Margin.CalclationArea(Rect);
}

// ----------------------------------------------------
//	FrameBase::ToString
// ----------------------------------------------------
String			_FrameBase::ToString() const
{
	return String()
		<< _T("FrameRectangle: {") << GetFrameArea().ToString() << _T("}")
		<< _T(", ActualArea: {") << GetActualArea().ToString() << _T("}")
		<< _T(", Order: ") << DrawOrder;
}

// ----------------------------------------------------
//	GradationFrame
// ----------------------------------------------------
//	GradationFrame::ToString
// ----------------------------------------------------
String			GradationFrame::ToString() const
{
	return this->PanelFrame::ToString()
		<< _T(", Start: ")	<< StartGradColor.ToString()
		<< _T(", End: ")	<< EndGradColor.ToString()
		<< _T(", Border: ")<< BorderColor.ToString();
}

// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// �����O���f�[�V�����J�n�F���ݒ肳��Ă���
	if(StartGradColor.Enable){
		// �I���F���w�肳��Ă��Ȃ�or�J�n�F�ƏI���F�������ꍇ�Ȃ�
		if(!EndGradColor.Enable || StartGradColor == EndGradColor){
			// ���u�����h�K�p
			StartGradColor._AppendAlpha();
			// �P�F�h��
			DrawBox(Dr.Location.X, Dr.Location.Y, Dr.Width, Dr.Height, StartGradColor._GetColor(), TRUE);
		}
		// �I���F���w�肳��Ă���ꍇ��
		else {
			// �`��F���w�肷��
			Color GrDrawColor;
			GrDrawColor.Enable = true;
			// �O���f�[�V������`�悷��
			for(int Y = 0; Y < Dr.Height; Y++){
				// �J�n�F�ƏI���F�̊������擾����
				double DrParcent = Y*100.00/Dr.Height;
				// �`��F����������Z�o����
				GrDrawColor.A = (EndGradColor.A * DrParcent)/100 + (StartGradColor.A * (100-DrParcent))/100;
				GrDrawColor.R = (EndGradColor.R * DrParcent)/100 + (StartGradColor.R * (100-DrParcent))/100;
				GrDrawColor.G = (EndGradColor.G * DrParcent)/100 + (StartGradColor.G * (100-DrParcent))/100;
				GrDrawColor.B = (EndGradColor.B * DrParcent)/100 + (StartGradColor.B * (100-DrParcent))/100;
				// ���u�����h�K�p
				GrDrawColor._AppendAlpha();
				// ��{���`�悷��
				DrawLine(Dr.Location.X, Dr.Location.Y + Y, Dr.Width - 1,
						 Dr.Location.Y + Y, GrDrawColor._GetColor());
			}
		}
	}
	// ���E���`��̐F�����܂��Ă���Ȃ��
	if(BorderColor.Enable){
		// ���u�����h�K�p
		BorderColor._AppendAlpha();
		// �`�悷��D
		DrawBox(Dr.Location.X, Dr.Location.Y, Dr.Width, Dr.Height, BorderColor._GetColor(), FALSE);
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
	this->_PictureHandle	= (ImgPath.compare(_T("")) ? LoadGraph(ImgPath) : -1);
	// �摜�p�X���Z�b�g����
	this->Path				= ImgPath;
	this->_PicturePath		= ImgPath;
	// ���]�`�悵�Ȃ�
	Turned					= false;
	// �W���̕`���ނ��w�肷��
	Position				= DrawType::Default;
	// �W�������擾����
	GetGraphSize(_PictureHandle, &_DefaultSizeW, &_DefaultSizeH);
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
	// �摜���ǂݍ��߂Ă���Ȃ�
	if(_PictureHandle != -1){
		// ���ʂɕԋp
		return this->PanelFrame::ToString()
			<< _T(", Path: \"") << Path << _T("\"")
			<< _T(", Turned: ")<< Turned
			<< _T(", Alpha: ")<< Alpha;
	}
	// �ǂݍ��߂Ă��Ȃ��Ȃ�
	else {
		// �G���[������
		return this->PanelFrame::ToString()
			<< _T(", Handle: Error");
	}
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			PictureFrame::_SetProperties()
{
	// PanelFrame�̂��̂��Ăяo��
	PanelFrame::_SetProperties();
	// �����w�肳��Ă���摜�t�@�C�����ς���Ă���Ȃ�
	if(Path != _PicturePath){
		// ���݂̉摜��j������
		DeleteGraph(_PictureHandle);
		// �ǂݍ��ݒ���
		_PictureHandle = LoadGraph(Path);
		// �摜�T�C�Y���擾������
		GetGraphSize(_PictureHandle, &_DefaultSizeW, &_DefaultSizeH);
		// �R�s�[
		_PicturePath = Path;
	}
}

// ----------------------------------------------------
//	PictureFrame::DrawThisFrame
// ----------------------------------------------------
void			PictureFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// ���u�����h��L����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	// �`��ʒu���w��
	_SetDrawPoint(Dr);
	// �g��`��̎�
	if(Position == DrawType::Stretch){
		// ���]�������Ȃ�
		if(!Turned){
			// �S�̂ɍL���ĕ`�悷��
			DrawExtendGraphF(Dr.Location.X, Dr.Location.Y,
				Dr.Location.X + Dr.Width, Dr.Location.Y + Dr.Height, _PictureHandle, TRUE);
		}
		// ���]���L���Ȃ�
		else {
			// ���𔽓]�����ĕ`�悷��
			DrawExtendGraphF(Dr.Location.X + Dr.Width, Dr.Location.Y,
				Dr.Location.X, Dr.Location.Y + Dr.Height, _PictureHandle, TRUE);
		}
	}
	// ���������g��`��Ȃ�
	else if(Position == DrawType::Zoom){
		// �g�劄�����擾
		double ExtendRate = min((double)Dr.Width / _DefaultSizeW, (double)Dr.Height / _DefaultSizeH);
		// ���S����ɕ`��
		DrawRotaGraphF(Dr.Location.X + Dr.Width/2, Dr.Location.Y + Dr.Height/2,
			ExtendRate, 0, _PictureHandle, TRUE, Turned);
	}
	// ���ʂɕ`�悷��Ȃ�
	else {
		// ���]�`�悪�����Ȃ�
		if(!Turned){
			// ���ʂɉ摜��`�悷��
			DrawGraphF(Dr.Location.X, Dr.Location.Y, _PictureHandle, TRUE);
		}
		// ���]�`�悪�L���Ȃ�
		else {
			// ���]�����ĉ摜��`�悷��
			DrawTurnGraphF(Dr.Location.X, Dr.Location.Y, _PictureHandle, TRUE);
		}
	}
}

// ----------------------------------------------------
//	PictureFrame::GetActualWidth
// ----------------------------------------------------
double			PictureFrame::_GetActualWidth() const
{
	return _DefaultSizeW;
}

// ----------------------------------------------------
//	PictureFrame::GetActualWidth
// ----------------------------------------------------
double			PictureFrame::_GetActualHeight() const
{
	return _DefaultSizeH;
}

// ----------------------------------------------------
//	PictureFrame::GetDrawPosition
// ----------------------------------------------------
void			PictureFrame::_SetDrawPoint(RectangleArea &Dr) const
{
	// ��Ƃ���ʒu�Ŕ���(X���W)�D
	switch(this->Position){
		// (X���W)��ԍ�����ɂ���Ȃ�
		case DrawType::TopLeft:
		case DrawType::MiddleLeft:
		case DrawType::BottomLeft:
			// ���ɕω��������Ȃ�
			break;
		// (X���W)���S����ɕ\������Ȃ�
		case DrawType::TopCenter:
		case DrawType::MiddleCenter:
		case DrawType::BottomCenter:
			// ��/2
			Dr.Location.X -= Dr.Width/2;
			break;
		// (X���W)��ԉE����ɕ\������Ȃ�
		case DrawType::TopRight:
		case DrawType::MiddleRight:
		case DrawType::BottomRight:
			// ��
			Dr.Location.X -= Dr.Width;
			break;
		// ����ȊO�Ȃ牽�����Ȃ�
		default:
			break;
	}
	// ��Ƃ���ʒu�Ŕ���(Y���W)�D
	switch(this->Position){
		// (Y���W)��ԏ����ɂ���Ȃ�
		case DrawType::TopLeft:
		case DrawType::TopCenter:
		case DrawType::TopRight:
			// ���ɉ������Ȃ�
			break;
		// (Y���W)���S����ɕ\������Ȃ�
		case DrawType::MiddleLeft:
		case DrawType::MiddleCenter:
		case DrawType::MiddleRight:
			// �c��/2
			Dr.Location.X -= Dr.Height / 2;
			break;
		// (Y���W)��ԉ�����ɕ\������Ȃ�
		case DrawType::BottomLeft:
		case DrawType::BottomCenter:
		case DrawType::BottomRight:
			// �c��
			Dr.Location.X -= Dr.Height;
			break;
		// ����ȊO�Ȃ牽�����Ȃ�
		default:
			break;
	}
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
	return this->PictureFrame::ToString();
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
void			MovieFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// ���u�����h��L����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	// �`��ʒu���w��
	_SetDrawPoint(Dr);
}

// ----------------------------------------------------
//	TextFrame
// ----------------------------------------------------
//	TextFrame::TextFrame (Constructor)
// ----------------------------------------------------
				TextFrame::TextFrame()
{
	// �ڍהł��Ă�
	this->TextFrame::TextFrame(_T(""));
}

// ----------------------------------------------------
//	TextFrame::TextFrame (Constructor)
// ----------------------------------------------------
				TextFrame::TextFrame(String Str)
{
	// ��������R�s�[����
	Text					= Str;
	_Property._BackupStr	= Str;
	// �W���ݒ�ɍ��킹��
	ShowType				= TextShowType::Default;
	Position				= TextPosition::TopLeft;
	HeightInterval			= 0;
	// �W���ŕ������肵�Ȃ�
	TextAdvance				= false;
	// Property��Owner���w�肷��
	_Property._Owner		= this;
}

// ----------------------------------------------------
//	TextFrame::ToString
// ----------------------------------------------------
String			TextFrame::ToString() const
{
	return this->PanelFrame::ToString()
		<< _T(", Text: \"") << Text << _T("\"")
		<< _T(", AdvanceShow: ") << TextAdvance
		<< _T(", Font: {") << TextFont.ToString() << _T("}");
}

// ----------------------------------------------------
//	TextFrame::SetProperties
// ----------------------------------------------------
void			TextFrame::_SetProperties()
{
	// �����c�����擾����
	this->PanelFrame::_SetProperties();
	auto DrArea = GetActualArea();
	// �t�H���g�����X�V
	TextFont._ReloadFontHandle();
	// Text�v���p�e�B���ύX����Ă���/Return�\����(����|�t�H���g)���ύX���ꂽ�ꍇ
	if(Text != _Property._BackupStr
	|| (ShowType == TextShowType::Return && (DrArea.Width != _Property._Width || TextFont.IsFontChanged()))){
		// �ۑ����Ȃ���
		_Property._BackupStr = Text;
		_Property._Width = DrArea.Width;
		// DrawTextArray���w�肵�Ȃ���
		_Property._SetDrawTextArray();
	}
	// ������������ݒ�ŁC�S�\�����I����Ă����
	if(TextAdvance && TextTimer.LoopType == Timer::LoopType::No && TextTimer() >= _Property._TotalTextLenght){
		// ����������I������
		TextAdvance = false;
	}
	// Timer���X�V����
	TextTimer();
}

// ----------------------------------------------------
//	TextFrame::DrawThisFrame
// ----------------------------------------------------
void			TextFrame::_DrawThisFrame(RectangleArea &Dr) const
{
	// �`�悷�镶���̑����������擾����
	int DrawStrLenght = (TextAdvance ? TextTimer._GetValueNoReload() : _Property._TotalTextLenght);
	// ���u�����h��L����
	TextFont.FontColor._AppendAlpha();
	// ��s���`����s��
	for(int i = 0; DrawStrLenght > 0; i++){
		// �`�悷��s�̕�����̏����擾����
		auto StrDt = _Property._DrawTextsArray[i];
		// �`��ʒu���擾����
		_Property._SetTextDrawStartPoint(Dr, StrDt, i);
		// �`�悷�镶������擾����
		String DrawStr = (StrDt.Text.length() <= DrawStrLenght ? StrDt.Text :
			StrDt.Text.substr(0, DrawStrLenght).c_str());
		// �����k���`�悪�K�v�Ȃ�
		if(ShowType == TextShowType::Pack && StrDt.Width > Dr.Width){
			// �g��k�����ĕ`����s��
			DrawExtendStringToHandle(StrDt.DrStartPt.X, StrDt.DrStartPt.Y,
				(double)Dr.Width / StrDt.Width, 1,
				DrawStr, TextFont.FontColor._GetColor(),
				TextFont._GetFontHandle(), TextFont.EdgeColor._GetColor());
		}
		// �k�����Ȃ��Ȃ�
		else {
			// ���ʂɕ������`�悷��
			DrawStringToHandle(StrDt.DrStartPt.X, StrDt.DrStartPt.Y,
				DrawStr, TextFont.FontColor._GetColor(),
				TextFont._GetFontHandle(), TextFont.EdgeColor._GetColor());
		}
		// �`�悵�����������c��̕`�敶���������炷
		DrawStrLenght -= DrawStr.length();
	}
}

// ----------------------------------------------------
//	TextFrame::GetSingleLineTextWidth
// ----------------------------------------------------
int				TextFrame::_GetSingleLineTextWidth(const String &DrStr) const
{
	// �擾�֐����Ăяo���C���ʂ�ԋp����
	return GetDrawStringWidthToHandle(DrStr, DrStr.length(), TextFont._GetFontHandle());
}

// ----------------------------------------------------
//	TextFrame::GetSingleLineTextHeight
// ----------------------------------------------------
int				TextFrame::_GetSingleLineTextHeight(const String &DrStr) const
{
	// �t�H���g����ԋp
	return TextFont.Size;
}

// ----------------------------------------------------
//	TextFrame::SetDrawTextArray
// ----------------------------------------------------
void			TextFrame::_PropertySaved::_SetDrawTextArray()
{
	// �S�폜����
	_DrawTextsArray.clear();
	// �����񒷂�����������
	_TotalTextLenght = 0;
	// ���s������Split����
	auto StBaseAry = _BackupStr.Split(_T("\n"), true);
	// �s�ʂɕ�����
	for(auto Itr = StBaseAry.begin(); Itr != StBaseAry.end(); Itr++){
		// �쐬
		TextFrame::_SingleLineTextData StData;
		// ����Return�\���Ȃ�
		if(_Owner->ShowType == TextShowType::Return){
			// �K�؂Ȓ����̕����擾����
			auto Len = _GetFitTextLenght(*Itr);
			// �擾���������當������w�肷��
			StData.Text = Itr->substr(0, Len).c_str();
			// �����c��̕�������Ȃ�
			if(Len < Itr->length()){
				// �c��̕��͎��̍s�Ɏ����z��
				Itr = StBaseAry.insert(Itr + 1, Itr->substr(Len, Itr->length()).c_str()) - 1;
			}
		}
		// �����łȂ��Ȃ�
		else {
			// ���ʂɕ�������w�肷��
			StData.Text = *Itr;
		}
		// �����񒷂��w�肷��
		_TotalTextLenght += StData.Text.length();
		// �c�������w�肷��
		StData.Width = _Owner->_GetSingleLineTextWidth(StData.Text);
		StData.Height = _Owner->_GetSingleLineTextHeight(StData.Text);
		// �`�敶���ꗗ�ɒǉ�
		_DrawTextsArray.push_back(StData);
	}
}

// ----------------------------------------------------
//	TextFrame::GetFitTextLenght
// ----------------------------------------------------
unsigned int	TextFrame::_PropertySaved::_GetFitTextLenght(const String &Str) const
{
	// �����̕����񂩂�tstring��������쐬
	std::basic_string<TCHAR> tStr = Str;
	// �ԋp�p
	unsigned int Lenght = tStr.length();
	// ������̒�������蕝�ȉ��ɂȂ�܂Ń��[�v���N����
	while(_Owner->_GetSingleLineTextWidth(tStr.c_str()) > _Width){
		// �����c��������1�ȉ��Ȃ�
		if(Lenght <= 1){
			// 1��ԋp�i�������Ȃ��ƃo�O��j
			return 1;
		}
		// �������̒������ꕶ�����炷
		tStr = tStr.substr(0, Lenght - 1);
		// �ԋp�p�̕����񒷂��ꕶ�����炷
		Lenght--;
	}
	// �ԋp
	return Lenght;
}

// ----------------------------------------------------
//	TextFrame::GetTextDrawStartPoint
// ----------------------------------------------------
void			TextFrame::_PropertySaved::_SetTextDrawStartPoint(RectangleArea &Ar, TextFrame::_SingleLineTextData &StrDt, UINT LineNo) const
{
	// �ꎞ�ۑ��p
	double LocX = Ar.Location.X, LocY = Ar.Location.Y;
	// ����Pack�\���łȂ��C�܂��͕������g�̃t���[������菬�����Ȃ�
	if(_Owner->ShowType != TextShowType::Pack || StrDt.Width < Ar.Width){
		// ShowPlace�ŕ�����
		switch(_Owner->Position){
			// �����`��Ȃ�
			case TextPosition::TopLeft:
			case TextPosition::MiddleLeft:
			case TextPosition::BottomLeft:
				// ���̂܂�
				LocX += 0;
				break;
			// �����`��Ȃ�
			case TextPosition::TopCenter:
			case TextPosition::MiddleCenter:
			case TextPosition::BottomCenter:
				// ��/2�𑫂��Ďw��
				LocX += (double)(Ar.Width - StrDt.Width) / 2;
				break;
			// �E���`��Ȃ�
			case TextPosition::TopRight:
			case TextPosition::MiddleRight:
			case TextPosition::BottomRight:
				// ���𑫂��Ďw��
				LocX += Ar.Width - StrDt.Width;
				break;
			// ����ȊO�Ȃ�
			default:
				LocX = -1;
				break;
		}
	}
	// ShowPlace�ŕ�����
	switch(_Owner->Position){
		// �㑤�`��Ȃ�
		case TextPosition::TopLeft:
		case TextPosition::TopCenter:
		case TextPosition::TopRight:
			// Y���W���̂܂�
			LocY += 0;
			break;
		// �����`��Ȃ�
		case TextPosition::MiddleLeft:
		case TextPosition::MiddleCenter:
		case TextPosition::MiddleRight:
			// + (�c�� - (�����c��+Margin)*(���X�̍s��-1))/2
			LocY += (Ar.Height - (StrDt.Height + _Owner->HeightInterval) * (int)(_DrawTextsArray.size())) / 2;
			break;
		// �����`��Ȃ�
		case TextPosition::BottomLeft:
		case TextPosition::BottomCenter:
		case TextPosition::BottomRight:
			// + (�c�� - (�����c��+Margin)*(���X�̍s��-1))
			LocY += (Ar.Height - (StrDt.Height + _Owner->HeightInterval) * (int)(_DrawTextsArray.size()));
			break;
		// ����ȊO�Ȃ�
		default:
			LocY = -1;
			break;
	}
	// �s����Y���W��ǉ�����
	LocY += (StrDt.Height + _Owner->HeightInterval) * (LineNo);
	// �������
	StrDt.DrStartPt = Point(LocX, LocY);
}

// ----------------------------------------------------
//	Font
// ----------------------------------------------------
//	Font::Font (Constructor/None)
// ----------------------------------------------------
				Font::Font()
{
	// �ڍהł��Ăяo��
	this->Font::Font(ApplicationConfig::DefaultFontName, 16, 0, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Size)
// ----------------------------------------------------
				Font::Font(int FontSize)
{
	// �ڍהł��Ăяo��
	this->Font::Font(ApplicationConfig::DefaultFontName, FontSize, 0, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize)
{
	// �ڍהł��Ăяo��
	this->Font::Font(FontName, FontSize, 0, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size,Thick)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick)
{
	// �ڍהł��Ăяo��
	this->Font::Font(FontName, FontSize, FontThick, -1, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/Name,Size,Thick,EdgeSize)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick, int eSize)
{
	// �ڍהł��Ăяo��
	this->Font::Font(FontName, FontSize, FontThick, EdgeSize, FontType::Antialiase);
}

// ----------------------------------------------------
//	Font::Font (Constructor/All)
// ----------------------------------------------------
				Font::Font(String FontName, int FontSize, int FontThick, int eSize, Font::FontType::_FontType Ty)
{
	// �v���p�e�B���Z�b�g����
	Name			= FontName;
	Size			= FontSize;
	Thick			= FontThick;
	Type			= Ty;
	EdgeSize		= eSize;
	// �F������������
	FontColor		= Color::White;
	// �n���h��������������
	_Handle			= -1;
	_IsFontHandleChanged = false;
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
//	Font::IsFontPropertyChange
// ----------------------------------------------------
bool			Font::IsFontChanged() const
{
	// �����ύX����Ă���悤�Ȃ�true��Ԃ�
	return (
		Name != _Changed._Name ||
		Size != _Changed._Size ||
		Thick != _Changed._Thick ||
		Type != _Changed._Type ||
		EdgeSize != _Changed._EdgeSize ||
		EdgeColor.Enable != _Changed._IsEnableEdge
	);
}

// ----------------------------------------------------
//	Font::ToString
// ----------------------------------------------------
String			Font::ToString() const
{
	return String()
		<< _T("Name: \"") << Name << _T("\"")
		<< _T(", Size: ") << Size
		<< _T(", Thick: ") << Thick
		<< _T(", Color: ") << FontColor.ToString()
		<< _T(", Edge: ") << EdgeColor.ToString()
		<< _T(", IsChanged: ") << IsFontChanged();
}

// ----------------------------------------------------
//	Font::ReloadFontHandle
// ----------------------------------------------------
void			Font::_ReloadFontHandle()
{
	// �����t�H���g�n���h�������ɒ��O�̃t���[���ŕύX����Ă���Ȃ�
	if(_IsFontHandleChanged){
		// �v���p�e�B��V�����l�ɍX�V
		_Changed._Name = Name;
		_Changed._Size = Size;
		_Changed._Thick = Thick;
		_Changed._EdgeSize = EdgeSize;
		_Changed._Type = Type;
		_Changed._IsEnableEdge = EdgeColor.Enable;
		// �ύX�t���O��false��
		_IsFontHandleChanged = false;
	}
	// �����v���p�e�B�̒��̂ǂꂩ�̒l���ύX����Ă�����
	else if(IsFontChanged()){
		// ���݂̃t�H���g�n���h�����������
		DeleteFontToHandle(_Handle);
		// �t�H���g�n���h�����X�V����
		_Handle	= CreateFontToHandle(Name, Size, Thick, _GetFontDrawType(), -1, EdgeSize);
		// �ύX�t���O��true�ɂ���
		_IsFontHandleChanged = true;
	}
}

// ----------------------------------------------------
//	Font::GetFontHandle
// ----------------------------------------------------
inline int		Font::_GetFontHandle() const
{
	// �t�H���g�n���h����ԋp����
	return this->_Handle;
}

// ----------------------------------------------------
//	Font::GetFontDrawType
// ----------------------------------------------------
inline int		Font::_GetFontDrawType() const
{
	// �ꎞ�p
	int Result = 0;
	// �`��̎�ނɉ�����DEFINE��`���ꂽ�l���Z�b�g����
	switch(Type){
		case FontType::Normal:
			Result = DX_FONTTYPE_NORMAL;
			break;
		case FontType::Antialiase:
			Result = DX_FONTTYPE_ANTIALIASING;
			break;
		case FontType::AntialiaseHiQuality:
			Result = DX_FONTTYPE_ANTIALIASING_8X8;
			break;
		default:
			return -1;
	}
	// �G�b�W�F���w�肳��Ă���Ȃ�G�b�W���`�悷��悤�Ɏw��
	Result += (EdgeColor.Enable ? 1 : 0);
	// �ԋp
	return Result;
}

// ----------------------------------------------------
//	Color
// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color()
{
	// �F�𖳌��Ɏw�肷��
	Enable = false;
}

// ----------------------------------------------------
//	Color::Color
// ----------------------------------------------------
				Color::Color(int Rp, int Gp, int Bp)
{
	// �ڍהł��Ăяo��
	this->Color::Color(255, Rp, Gp, Bp);
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
	// �L���ɐݒ�
	Enable = true;
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
	// �L���ɐݒ�
	Enable = true;
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
	// �L���ɐݒ�
	Enable = true;
}

// ----------------------------------------------------
//	Color::operator= (Color version)
// ----------------------------------------------------
Color&			Color::operator=(const Color &Cr)
{
	// �������
	this->A	= Cr.A;
	this->R	= Cr.R;
	this->G	= Cr.G;
	this->B	= Cr.B;
	// �F�̗L���x�������ɍ��킹��
	Enable = Cr.Enable;
	// ���g��ԋp����
	return *this;
}

// ----------------------------------------------------
//	Color::operator= (RGB Code version)
// ----------------------------------------------------
Color&			Color::operator=(const Color::_ColorList ARGBCode)
{
	// �������
	this->A	= ((ARGBCode >> 24) & 0xFF);
	this->R	= ((ARGBCode >> 16) & 0xFF);
	this->G	= ((ARGBCode >>  8) & 0xFF);
	this->B	= ((ARGBCode >>  0) & 0xFF);
	// �L���ɐݒ�
	Enable = true;
	// ���g��ԋp����
	return *this;
}

// ----------------------------------------------------
//	Color::operator==
// ----------------------------------------------------
bool			Color::operator==(const Color& Cr) const
{
	return Compare(Cr);
}

// ----------------------------------------------------
//	Color::operator!=
// ----------------------------------------------------
bool			Color::operator!=(const Color& Cr) const
{
	return !Compare(Cr);
}

// ----------------------------------------------------
//	Color::AlphaToParcent
// ----------------------------------------------------
int				Color::AlphaFromParcent(double Bs)
{
	return (Bs * 256.0)/100;
}

// ----------------------------------------------------
//	Color::ToString
// ----------------------------------------------------
String			Color::ToString() const
{
	// �����L���Ȃ�
	if(Enable){
		// ARGB�R�[�h��ԋp����
		return String()
			<< A << _T("|")
			<< R << _T("|") 
			<< B << _T("|")
			<< G;
	}
	// ���������Ȃ�
	else {
		// Invalid��ԋp����
		return String(_T("Invalid"));
	}
}

// ----------------------------------------------------
//	Color::Compare
// ----------------------------------------------------
bool			Color::Compare(const Color &Target) const
{
	return Target.A == A
		&& Target.R == R
		&& Target.B == B
		&& Target.G == G
		&& Target.Enable == Enable;
}

// ----------------------------------------------------
//	Color::GetColor
// ----------------------------------------------------
inline DWORD	Color::_GetColor() const
{
	// �L���Ȃ�F���쐬���ĕԋp�C�����łȂ��Ȃ�G���[�R�[�h��Ԃ�
	return (Enable ? GetColor(this->R, this->G, this->B) : -1);
}

// ----------------------------------------------------
//	Color::AppendAlpha
// ----------------------------------------------------
inline void		Color::_AppendAlpha() const
{
	// �L���ȐF�Ȃ�
	if(Enable){
		// ���ߓx��ݒ肷��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, A);
	}
}
