// --------------------------------------------------------
//	apcCollection.cpp
// --------------------------------------------------------
//	apcCollection.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.hpp"

// ----------------------------------------------------
//	FrameCollection
// ----------------------------------------------------
//	FrameCollection::FrameCollection (Constructor)
// ----------------------------------------------------
				_FrameCollection::_FrameCollection()
{
	// �ŏ�ʃt���[�����쐬����
	_TopParent = new PanelFrame();
	// Margin���w�肷��
	_TopParent->Margin(0, 0, 0, 0);
}

// ----------------------------------------------------
//	FrameCollection::~FrameCollection (Destructor)
// ----------------------------------------------------
				_FrameCollection::~_FrameCollection()
{
	// �S�폜
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Insert
// ----------------------------------------------------
void			_FrameCollection::Insert(_FrameBase *Target)
{
	// ����NULL�t���[�����n���ꂽ��
	if(!Target){
		// �������Ȃ�
		return;
	}
	// �}������
	_Container.push_back(Target);
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
_FrameCollection::FrameListPtr	
				_FrameCollection::Enum() const
{
	// ��������ł��Ăяo��
	return Enum([](const FramePtr){ return true; });
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
_FrameCollection::FrameListPtr	
				_FrameCollection::Enum(_FrameCollection::CheckFunc Func) const
{
	// �ԋp����ꗗ��p��
	auto FVector = new std::vector<FramePtr>();
	// �C�e���[�^���擾
	auto Iter = _Container.begin();
	// ------------------------------------------------
	// �I�[�܂őS�Ċm�F
	while(Iter != _Container.end()){
		// �擾
		auto Ptr = *Iter;
		// 1�i�߂�
		Iter++;
		// �����֐��̌��ʂ�false�Ȃ�
		if(!Func(Ptr)){
			// �ēx�Ăяo��
			continue;
		}
		// �����e�t���[�����w�肳��Ă��Ȃ����
		if(!Ptr->Parent && Ptr != _TopParent){
			// �e�t���[����TopParent�Ɏw�肷��
			Ptr->Parent = _TopParent;
		}
		// vector�ɒǉ�
		FVector->push_back(Ptr);
	}
	// �ԋp
	return FVector;
}

// ----------------------------------------------------
//	FrameCollection::Erase
// ----------------------------------------------------
void			_FrameCollection::Erase(const _FrameBase *Target)
{
	// ���������ɖ����|�C���^�܂��͍ŏ�ʃt���[����n���ꂽ��
	if(!Target || Target == _TopParent){
		// �������Ȃ�
		return;
	}
	// �����̃t���[����e�Ɏ��t���[�����擾����
	auto List = Enum([Target](const FramePtr Pr){return(Pr->Parent == Target);});
	// ���ԂɌ���
	BOOST_FOREACH(auto Ptr, *List){
		// �e�t���[�����擾
		auto ParentPtr = Ptr->Parent;
		// �e�t���[��������������
		Ptr->Parent = ParentPtr->Parent;
	}
	// �擾����
	auto ErasePtr = Find([Target](const FramePtr Pr){return Pr == Target;});
	// �����폜����Ώۂ����݂���Ȃ�
	if(ErasePtr){
		// ���ԂɌ���
		auto Iter = _Container.begin();
		for(; Iter != _Container.end(); Iter++){
			if((*Iter) == Target){
				break;
			}
		}
		// �w�肳�ꂽ�t���[�����R���e�i����폜����
		_Container.erase(Iter);
	}
	// �I��
	return;
}

// ----------------------------------------------------
//	FrameCollection::Find
// ----------------------------------------------------
_FrameCollection::FramePtr
				_FrameCollection::Find(_FrameCollection::CheckFunc Func) const
{
	// �擾
	auto Vector = *Enum(Func);
	// �����擾�������ʂ�empty�Ȃ�NULL��ԋp
	if(Vector.empty()){ return NULL; }
	// �ŏ��̍��ڂ�ԋp
	return Vector[0];
}

// ----------------------------------------------------
//	FrameCollection::Sort
// ----------------------------------------------------
void			_FrameCollection::Sort()
{
	// �S�t���[���ɑ΂��āCDrawOrder��K�؂Ȃ��̂ɕύX����
	for(auto Iter = _Container.begin(); Iter != _Container.end(); Iter++){
		// �e���l�����ĕ��ёւ���
		_FrameCollection::GetInstance()._SetZindex(*Iter);
	}
	// ���я���ς���
	_Container.sort(_Sort());
}

// ----------------------------------------------------
//	FrameCollection::Clear
// ----------------------------------------------------
void			_FrameCollection::Clear()
{
	// �S�č폜����D
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Sort
// ----------------------------------------------------
bool			_FrameCollection::_Sort::operator()(const _FrameBase *A, const _FrameBase *B)
{
	// Z���W���r����D
	return A->DrawOrder < B->DrawOrder;
}

// ----------------------------------------------------
//	FrameCollection::DrawAll
// ----------------------------------------------------
void			_FrameCollection::DrawAll() const
{
	// �ꗗ���擾����(Visible��true���e��Enable=false�����݂��Ȃ�)
	auto List = Enum([this](const FramePtr &Val){ return (Val->Visible && _EnableParent(Val)); });
	// �񋓂���
	BOOST_FOREACH(auto Ptr, *List){
		// �����E�c���̕W���l���擾
  		Ptr->_SetProperties();
		// �`�惂�[�h���w�肷��
		SetDrawMode(Ptr->DrawMode);
		// �`��̈���擾����
		RectangleArea Rect = Ptr->GetActualArea();
		// �g���̈�ɕ`�悷��ݒ�Ȃ�L���ɂ���
		if(Ptr->DrawFramework){
			SetDrawArea(Rect.Location.X, Rect.Location.Y,
				Rect.Location.X + Rect.Width, Rect.Location.Y + Rect.Height);
		}
		// �S�̈�ɕ`�悷��ݒ�Ȃ珉��������
		else {
			SetDrawAreaFull();
		}
		// �擾�����t���[���̕`��֐������s����
		Ptr->_DrawThisFrame(Rect);
	}
}

// ----------------------------------------------------
//	FrameCollection::GetTopParent
// ----------------------------------------------------
PanelFrame*		_FrameCollection::GetTopParent() const
{
	return _TopParent;
}

// ----------------------------------------------------
//	FrameBase::SetZindex
// ----------------------------------------------------
void			_FrameCollection::_SetZindex(_FrameBase *Tgt) const
{
	// ���Z�l�i���u���j
	const int FRAME_IN_SEQUENCER_MAX = 0xFF;
	// ����DrawOrder���w��ς݂Ȃ��
	if(Tgt->DrawOrder != 0){
		// �������Ȃ�
		return;
	}
	// �����e���L���Ȃ�
	if(Tgt->Parent){
		// �e�ɓ��l�̑�����s��
		_SetZindex(Tgt->Parent);
	}
	// �������g�̐e��TopParent�Ȃ�
	if(Tgt->Parent == _TopParent){
		// Sequencer��DrawOrder���ŏ��ɉ�������
		Tgt->DrawOrder = _SequenceCollection::GetInstance().Top()->_DrawOrder * FRAME_IN_SEQUENCER_MAX;
	}
	// ���g�̐e�t���[����Z���W�𑫂��ĕԋp
	Tgt->DrawOrder += (Tgt->Parent ? Tgt->Parent->DrawOrder : 0) + 1;
}

// ----------------------------------------------------
//	FrameCollection::EnableParent
// ----------------------------------------------------
bool			_FrameCollection::_EnableParent(const _FrameBase *Tgt) const
{
	// ���������Ȃ�
	if(!Tgt || !Tgt->Enable){
		// �e���Ȃ��Ȃ�true�C���g�������Ȃ�false��Ԃ�
		return !Tgt;
	}
	// �e�ł������֐������s
	return _EnableParent(Tgt->Parent);
}

// ----------------------------------------------------
//	SequenceCollection
// ----------------------------------------------------
//	SequenceCollection::~SequenceCollection (Destructor)
// ----------------------------------------------------
				_SequenceCollection::~_SequenceCollection()
{
	// �S�폜
	_Container.clear();
}

// ----------------------------------------------------
//	SequenceCollection::Add
// ----------------------------------------------------
void			_SequenceCollection::Add(const std::shared_ptr<Sequencer> &Target)
{
	// ����NULL�Ȃ�
	if(!Target){
		// �������Ȃ�
		return;
	}
	// �R���e�i�̖����ɒǉ�����
	_Container.push_back(Target);
}

// ----------------------------------------------------
//	SequenceCollection::Delete
// ----------------------------------------------------
std::shared_ptr<Sequencer>
				_SequenceCollection::Top() const
{
	// �����X�^�b�N����Ȃ�
	if(_Container.empty()){
		// NULL��Ԃ�
		return NULL;
	}
	// �X�^�b�N�̈�ԏ��Ԃ�
	return _Container.back();
}

// ----------------------------------------------------
//	SequenceCollection::Delete
// ----------------------------------------------------
void			_SequenceCollection::Delete(const Sequencer *Target)
{
	// �ۑ��p
	std::shared_ptr<Sequencer> TopFrame;
	// ����NULL�Ȃ�
	if(!Target || !Top()){
		// �������Ȃ�
		return;
	}
	// �����̃V�[�P���X�ɂȂ�܂ő�����
	while( TopFrame = Top() ){
		// �����v�f���폜����
		_Container.pop_back();
		// ������v�����Ȃ��
		if(TopFrame.get() == Target){
			// �I���
			break;
		}
	};
}

// ----------------------------------------------------
//	SequenceCollection::Size
// ----------------------------------------------------
unsigned int	_SequenceCollection::Size() const
{
	// ����ԋp
	return _Container.size();
}
