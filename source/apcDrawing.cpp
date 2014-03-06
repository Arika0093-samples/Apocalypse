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
	this->Enable				= true;
	this->Visible				= true;
	// �`�揇�Ԃ�������ԂɃ��Z�b�g����
	this->DrawOrder				= 0;
	// �W���Řg���`�悷��
	this->DrawFramework			= true;
	// �W���ňʒu���킹���s��
	this->_AutoAdjustPosition	= true;
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
		<< _T("Location: {") << _Location.ToString() << _T("}")
		<< _T(", Width: ") << _Width
		<< _T(", Height: ") << _Height
		<< _T(", Order: ") << DrawOrder;
}

// ----------------------------------------------------
//	FrameBase::SetDefaultPosition
// ----------------------------------------------------
void			__FrameBase::_SetDefaultPosition()
{
	// �e�t���[�����擾
	auto PrtPtr = Parent;
	// �����e�t���[�������݂��Ȃ��Ȃ�
	if(!PrtPtr || !_AutoAdjustPosition){
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
	return this->EdgeFrame::ToString()
		<< _T(", Start: ")	<< StartGradColor.ToString()
		<< _T(", End: ")	<< EndGradColor.ToString()
		<< _T(", Border: ")<< BorderColor.ToString();
}

// ----------------------------------------------------
//	GradationFrame::DrawThisFrame
// ----------------------------------------------------
void			GradationFrame::_DrawThisFrame() const
{
	// �����O���f�[�V�����J�n�F���ݒ肳��Ă���
	if(StartGradColor.Enable){
		// �I���F���w�肳��Ă��Ȃ�or�J�n�F�ƏI���F�������ꍇ�Ȃ�
		if(!EndGradColor.Enable || StartGradColor == EndGradColor){
			// ���u�����h�K�p
			StartGradColor._AppendAlpha();
			// �P�F�h��
			DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
					(_Location.Y + GetHeight()), StartGradColor._GetColor(), TRUE);
		}
		// �I���F���w�肳��Ă���ꍇ��
		else {
			// �O���f�[�V������`�悷��
			for(int Y = 0; Y < this->GetHeight(); Y++){
				// �`�悷��F���擾����
				auto DrawColor = StartGradColor._GetColorBlends(EndGradColor, (Y*100/GetHeight()));
				// ���u�����h�K�p
				DrawColor->_AppendAlpha();
				// ��{���`�悷��
				DrawLine(_Location.X, _Location.Y + Y, _Location.X + GetWidth() - 1,
						 _Location.Y + Y, DrawColor->_GetColor());
			}
		}
	}
	// ���E���`��̐F�����܂��Ă���Ȃ��
	if(BorderColor.Enable){
		// ���u�����h�K�p
		BorderColor._AppendAlpha();
		// �`�悷��D
		DrawBox(_Location.X, _Location.Y, (_Location.X + GetWidth()),
				(_Location.Y + GetHeight()), BorderColor._GetColor(), FALSE);
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
	PositionType			= DrawType::Default;
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
//	PictureFrame::GetDefaultSize
// ----------------------------------------------------
void			PictureFrame::GetDefaultSize(int* Wth, int* Hgt) const
{
	// �G���[�`�F�b�N
	if(!Wth || !Hgt){
		return;
	}
	// ���
	*Wth = _DefaultSizeW;
	*Hgt = _DefaultSizeH;
}

// ----------------------------------------------------
//	PictureFrame::ToString
// ----------------------------------------------------
String			PictureFrame::ToString() const
{
	// �摜���ǂݍ��߂Ă���Ȃ�
	if(_PictureHandle != -1){
		// ���ʂɕԋp
		return this->EdgeFrame::ToString()
			<< _T(", Path: \"") << Path << _T("\"")
			<< _T(", PictureSize: {") << _DefaultSizeW << _T(", ") << _DefaultSizeH << _T("}")
			<< _T(", Turned: ")<< Turned
			<< _T(", Alpha: ")<< Alpha;
	}
	// �ǂݍ��߂Ă��Ȃ��Ȃ�
	else {
		// �G���[������
		return this->EdgeFrame::ToString()
			<< _T(", Handle: Error");
	}
}

// ----------------------------------------------------
//	PictureFrame::SetProperties
// ----------------------------------------------------
void			PictureFrame::_SetProperties()
{
	// EdgeFrame�̂��̂��Ăяo��
	EdgeFrame::_SetProperties();
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
void			PictureFrame::_DrawThisFrame() const
{
	// ���u�����h��L����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	// �g��`��̎�
	if(PositionType == DrawType::Stretch){
		// ���]�������Ȃ�
		if(!Turned){
			// �S�̂ɍL���ĕ`�悷��
			DrawExtendGraphF(_Location.X, _Location.Y,
				_Location.X + _Width, _Location.Y + _Height, _PictureHandle, TRUE);
		}
		// ���]���L���Ȃ�
		else {
			// ���𔽓]�����ĕ`�悷��
			DrawExtendGraphF(_Location.X + _Width, _Location.Y,
				_Location.X, _Location.Y + _Height, _PictureHandle, TRUE);
		}
	}
	// ���������g��`��Ȃ�
	else if(PositionType == DrawType::Zoom){
		// �g�劄�����擾
		double ExtendRate = min((double)_Width / _DefaultSizeW, (double)_Height / _DefaultSizeH);
		// ���S����ɕ`��
		DrawRotaGraphF(_Location.X + _Width/2, _Location.Y + _Height/2,
			ExtendRate, 0, _PictureHandle, TRUE, Turned);
	}
	// ���ʂɕ`�悷��Ȃ�
	else {
		// �`����W���擾����
		Point Pt = _GetDrawPoint();
		// ���]�`�悪�����Ȃ�
		if(!Turned){
			// ���ʂɉ摜��`�悷��
			DrawGraphF(Pt.X, Pt.Y, _PictureHandle, TRUE);
		}
		// ���]�`�悪�L���Ȃ�
		else {
			// ���]�����ĉ摜��`�悷��
			DrawTurnGraphF(Pt.X, Pt.Y, _PictureHandle, TRUE);
		}
	}
}

// ----------------------------------------------------
//	PictureFrame::GetDrawPosition
// ----------------------------------------------------
Point			PictureFrame::_GetDrawPoint() const
{
	// �ԋp������W
	double LocX = 0, LocY = 0;
	// ��Ƃ���ʒu�Ŕ���(X���W)�D
	switch(this->PositionType){
		// (X���W)��ԍ�����ɂ���Ȃ�
		case DrawType::TopLeft:
		case DrawType::MiddleLeft:
		case DrawType::BottomLeft:
			// ���ɕω��������Ȃ�
			LocX = _Location.X;
			break;
		// (X���W)���S����ɕ\������Ȃ�
		case DrawType::TopCenter:
		case DrawType::MiddleCenter:
		case DrawType::BottomCenter:
			// ��/2�𑫂�
			LocX = _Location.X + ((_Width - _DefaultSizeW) / 2);
			break;
		// (X���W)��ԉE����ɕ\������Ȃ�
		case DrawType::TopRight:
		case DrawType::MiddleRight:
		case DrawType::BottomRight:
			// ���𑫂�
			LocX = _Location.X + (_Width - _DefaultSizeW);
			break;
		// ����ȊO�Ȃ牽�����Ȃ�
		default:
			break;
	}
	// ��Ƃ���ʒu�Ŕ���(Y���W)�D
	switch(this->PositionType){
		// (Y���W)��ԏ����ɂ���Ȃ�
		case DrawType::TopLeft:
		case DrawType::TopCenter:
		case DrawType::TopRight:
			// ���ɉ������Ȃ�
			LocY = _Location.Y;
			break;
		// (Y���W)���S����ɕ\������Ȃ�
		case DrawType::MiddleLeft:
		case DrawType::MiddleCenter:
		case DrawType::MiddleRight:
			// �c���̔����𑫂�
			LocY = _Location.Y + ((_Height - _DefaultSizeH) / 2);
			break;
		// (Y���W)��ԉ�����ɕ\������Ȃ�
		case DrawType::BottomLeft:
		case DrawType::BottomCenter:
		case DrawType::BottomRight:
			// �c���𑫂�
			LocY = _Location.Y + (_Height - _DefaultSizeH);
			break;
		// ����ȊO�Ȃ牽�����Ȃ�
		default:
			break;
	}
	// �ԋp
	return Point(LocX, LocY);
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
void			MovieFrame::_DrawThisFrame() const
{
	// ���u�����h��L����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);

}

// ----------------------------------------------------
//	TextFrame
// ----------------------------------------------------
//	TextFrame::TextFrame (Constructor)
// ----------------------------------------------------
				TextFrame::TextFrame(String Str)
{
	// ��������R�s�[����
	Text				= Str;
	_BackupStr			= Str;
	// �W���ݒ�ɍ��킹��
	ShowType			= TextShowType::Default;
	ShowPlace			= TextPosition::Default;
	HeightInterval		= 0;
	// �W���ŕ������肵�Ȃ�
	TextAdvance			= false;
}

// ----------------------------------------------------
//	TextFrame::ToString
// ----------------------------------------------------
String			TextFrame::ToString() const
{
	return this->EdgeFrame::ToString()
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
	this->EdgeFrame::_SetProperties();
	// ----------------------------------------------------
	// Text�v���p�e�B���ύX����Ă����ꍇ
	if(Text != _BackupStr){
		// Timer�����Z�b�g
		TextTimer.Reset();
		// �ۑ����Ȃ���
		_BackupStr = Text;
		// ���s������Split����
		_DrawTextsArray = _BackupStr.Split(_T("\n"), true);
		// ����Return�\���Ȃ�
		if(ShowType == TextShowType::Return){
			// �Ȃ񂽂炩�񂽂�


		}
	}
	// ----------------------------------------------------
	// ������������ݒ�ŁC�S�\�����I����Ă����
	if(TextAdvance && TextTimer.LoopType == Timer::No
		&& (TextTimer() / 1000) >= Text.length() - _DrawTextsArray.size()){
		// ����������I������
		TextAdvance = false;
	}
	// ----------------------------------------------------
	// Timer���X�V����
	TextTimer();
	// �t�H���g�����X�V
	TextFont._ReloadFontHandle();
}

// ----------------------------------------------------
//	TextFrame::DrawThisFrame
// ----------------------------------------------------
void			TextFrame::_DrawThisFrame() const
{
	// �`�悷�镶���̑����������擾����
	int DrawStrLenght = (TextAdvance ? TextTimer._GetValueNoReload() / 1000 : Text.length() - _DrawTextsArray.size());
	// ���u�����h��L����
	TextFont.FontColor._AppendAlpha();
	// ��s���`����s��
	for(int i = 0; DrawStrLenght > 0; i++){
		// �`��J�n�ʒu���擾����
		auto Pt = _GetSingleLineTextDrawPoint(_DrawTextsArray[i], _DrawTextsArray.size() - 1, i);
		// �`�悷�镶������擾����
		String DrawStr = (_DrawTextsArray[i].length() <= DrawStrLenght ?
			_DrawTextsArray[i] : _DrawTextsArray[i].substr(0, DrawStrLenght).c_str());
		// �����k���`�悪�K�v�Ȃ�
		if(ShowType == TextShowType::Pack && _GetSingleLineTextWidth(_DrawTextsArray[i]) > _Width){
			// �g��k�����ĕ`����s��
			DrawExtendStringToHandle(Pt.X, Pt.Y,
				(double)_Width / _GetSingleLineTextWidth(_DrawTextsArray[i]), 1,
				DrawStr, TextFont.FontColor._GetColor(),
				TextFont._GetFontHandle(), TextFont.EdgeColor._GetColor());
		}
		// �k�����Ȃ��Ȃ�
		else {
			// ���ʂɕ������`�悷��
			DrawStringToHandle(Pt.X, Pt.Y, DrawStr, TextFont.FontColor._GetColor(),
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
//	TextFrame::GetSingleLineTextDrawXPoint
// ----------------------------------------------------
Point			TextFrame::_GetSingleLineTextDrawPoint(const String &DrStr, UINT DefLines, UINT Line) const
{
	// �ꎞ�ۑ��p
	double LocX = 0, LocY = 0;
	// ����Pack�\���ŕ������g�̃t���[�������傫���Ȃ�
	if(ShowType == TextShowType::Pack && _GetSingleLineTextWidth(DrStr) >= _Width){
		// ShowPlace�Ɋ֌W�Ȃ����̂܂�X���W���w�肷��
		LocX = _Location.X;
	}
	// �����łȂ��Ȃ�
	else{
		// ShowPlace�ŕ�����
		switch(ShowPlace){
			// �����`��Ȃ�
			case TextPosition::TopLeft:
			case TextPosition::MiddleLeft:
			case TextPosition::BottomLeft:
				// ���̂܂܎w��
				LocX = _Location.X;
				break;
			// �����`��Ȃ�
			case TextPosition::TopCenter:
			case TextPosition::MiddleCenter:
			case TextPosition::BottomCenter:
				// ��/2�𑫂��Ďw��
				LocX = _Location.X + (double)(_Width - _GetSingleLineTextWidth(DrStr)) / 2;
				break;
			// �E���`��Ȃ�
			case TextPosition::TopRight:
			case TextPosition::MiddleRight:
			case TextPosition::BottomRight:
				// ���𑫂��Ďw��
				LocX = _Location.X + _Width - _GetSingleLineTextWidth(DrStr);
				break;
			// ����ȊO�Ȃ�
			default:
				LocX = -1;
				break;
		}
	}
	// ShowPlace�ŕ�����
	switch(ShowPlace){
		// �㑤�`��Ȃ�
		case TextPosition::TopLeft:
		case TextPosition::TopCenter:
		case TextPosition::TopRight:
			// Y���W + (�����c��+Margin)*(�s��-1)
			LocY = _Location.Y + (TextFont.Size + HeightInterval) * (Line);
			break;
		// �����`��Ȃ�
		case TextPosition::MiddleLeft:
		case TextPosition::MiddleCenter:
		case TextPosition::MiddleRight:
			// Y���W + (�����c��+Margin)*(�s��-1) + (�c�� - (�����c��+Margin)*(���X�̍s��-1))/2
			LocY = _Location.Y + (TextFont.Size + HeightInterval) * (Line)
				+ (_Height - (TextFont.Size + HeightInterval) * (DefLines)) / 2;
			break;
		// �����`��Ȃ�
		case TextPosition::BottomLeft:
		case TextPosition::BottomCenter:
		case TextPosition::BottomRight:
			// Y���W + (�����c��+Margin)*(�s��-1) + (�c�� - (�����c��+Margin)*(���X�̍s��-1))
			LocY = _Location.Y + (TextFont.Size + HeightInterval) * (Line)
				+ (_Height - (TextFont.Size + HeightInterval) * (DefLines));
			break;
		// ����ȊO�Ȃ�
		default:
			LocY = -1;
			break;
	}
	// �ԋp����
	return Point(LocX, LocY);
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
				Font::Font(String FontName, int FontSize, int FontThick, int eSize, Font::FontType::_FontType FontType)
{
	// �v���p�e�B���Z�b�g����
	Name		= FontName;
	Size		= FontSize;
	Thick		= FontThick;
	Type		= FontType;
	EdgeSize	= eSize;
	// �F������������
	FontColor	= Color::White;
	// �n���h��������������
	_Handle		= NULL;
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
//	Font::ToString
// ----------------------------------------------------
String			Font::ToString() const
{
	return String()
		<< _T("Name: \"") << _Name << _T("\"")
		<< _T(", Size: ") << _Size
		<< _T(", Thick: ") << _Thick
		<< _T(", Color: ") << FontColor.ToString()
		<< _T(", Edge: ") << EdgeColor.ToString();
}

// ----------------------------------------------------
//	Font::ReloadFontHandle
// ----------------------------------------------------
void			Font::_ReloadFontHandle()
{
	// �����v���p�e�B�̒��̂ǂꂩ�̒l���ύX����Ă�����
	if( Name != _Name || Size != _Size || Thick != _Thick
		|| EdgeSize != _Edge || Type != _Type || EdgeColor.Enable != _IsEnableEdge){
		// �v���p�e�B��V�����l�ɍX�V����
		_Name = Name;
		_Size = Size;
		_Thick = Thick;
		_Edge = EdgeSize;
		_Type = Type;
		_IsEnableEdge = EdgeColor.Enable;
		// ���݂̃t�H���g�n���h�����������
		DeleteFontToHandle(_Handle);
		// �t�H���g�n���h�����X�V����
		_Handle	= CreateFontToHandle(_Name, _Size, _Thick, _GetFontDrawType(), -1, _Edge);
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
	switch(_Type){
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
	Result += (_IsEnableEdge ? 1 : 0);
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
//	Color::GetColorBlends
// ----------------------------------------------------
std::shared_ptr<Color>
				Color::_GetColorBlends(const Color &Target, int Parcent) const
{
	// �F���ƂɎ擾����
	int _Red	= (Target.R * Parcent)/100 + (R * (100-Parcent))/100;
	int _Green	= (Target.G * Parcent)/100 + (G * (100-Parcent))/100;
	int _Blue	= (Target.B * Parcent)/100 + (B * (100-Parcent))/100;
	int _Alpha	= (Target.A * Parcent)/100 + (A * (100-Parcent))/100;
	// �쐬���ĕԋp����
	return std::shared_ptr<Color>(new Color(_Alpha, _Red, _Green, _Blue));
}
