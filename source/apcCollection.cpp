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
				__FrameCollection::__FrameCollection()
{
	// �ŏ�ʃt���[�����쐬����
	_TopParent = new EdgeFrame();
	// �����Əc�����w�肷��
	_TopParent->Width	= ApplicationConfig::Width;
	_TopParent->Height	= ApplicationConfig::Height;
	// ���w��𖳌��ɂ���D
	_TopParent->SpecifyWithParcent = false;
}

// ----------------------------------------------------
//	FrameCollection::~FrameCollection (Destructor)
// ----------------------------------------------------
				__FrameCollection::~__FrameCollection()
{
	// �S�폜
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Insert
// ----------------------------------------------------
void			__FrameCollection::Insert(__FrameBase *Target)
{
	// ����NULL�t���[�����n���ꂽ��
	if(!Target){
		// �������Ȃ�
		return;
	}
	// �}������
	_Container.insert(Target);
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
__FrameCollection::FrameListPtr	
				__FrameCollection::Enum() const
{
	// ��������ł��Ăяo��
	return Enum([](const FramePtr){ return true; });
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
__FrameCollection::FrameListPtr	
				__FrameCollection::Enum(__FrameCollection::CheckFunc Func) const
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
		if(Ptr->Parent && Ptr != _TopParent){
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
void			__FrameCollection::Erase(const __FrameBase *Target)
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
__FrameCollection::FramePtr
				__FrameCollection::Find(__FrameCollection::CheckFunc Func) const
{
	// �擾
	auto Vector = *Enum(Func);
	// �����擾�������ʂ�empty�Ȃ�NULL��ԋp
	if(Vector.empty()){ return NULL; }
	// �ŏ��̍��ڂ�ԋp
	return Vector[0];
}

// ----------------------------------------------------
//	FrameCollection::Clear
// ----------------------------------------------------
void			__FrameCollection::Clear()
{
	// �S�č폜����D
	_Container.clear();
}

// ----------------------------------------------------
//	FrameCollection::Sort
// ----------------------------------------------------
bool			__FrameCollection::_Sort::operator()(const __FrameBase *A, const __FrameBase *B)
{
	// Z���W���r����D���̍�Z���W��0�Ȃ�W���l���g�p����
	return	(A->DrawOrder != 0 ? A->DrawOrder : __FrameCollection::GetInstance()._GetParentZindex(A))
		>	(B->DrawOrder != 0 ? B->DrawOrder : __FrameCollection::GetInstance()._GetParentZindex(B));
}

// ----------------------------------------------------
//	FrameCollection::DrawAll
// ----------------------------------------------------
void			__FrameCollection::DrawAll() const
{
	// �ꗗ���擾����(Visible��true���e��Enable=false�����݂��Ȃ�)
	auto List = Enum([this](const FramePtr &Val){ return (Val->Visible && _EnableParent(Val)); });
	// �񋓂���
	BOOST_FOREACH(auto Ptr, *List){
		// �����E�c���̕W���l���擾
		Ptr->_SetProperties();
		// �ʒu�����Z�b�g����
		Ptr->_SetDefaultPosition();
		// �`�惂�[�h���w�肷��
		SetDrawMode(Ptr->DrawMode);
		// �擾�����t���[���̕`��֐������s����
		Ptr->_DrawThisFrame();
	}
}

// ----------------------------------------------------
//	FrameCollection::GetTopParent
// ----------------------------------------------------
EdgeFrame*		__FrameCollection::GetTopParent() const
{
	return _TopParent;
}

// ----------------------------------------------------
//	FrameBase::GetParentZindex
// ----------------------------------------------------
unsigned int	__FrameCollection::_GetParentZindex(const __FrameBase *Tgt) const
{
	// ���������Ȃ�
	if(!Tgt){
		// 1��Ԃ�
		return 1.00;
	}
	// ���g�̐e�t���[����Z���W+���g��Z���W��ԋp
	return (Tgt->DrawOrder + _GetParentZindex(Tgt->Parent));
}

// ----------------------------------------------------
//	FrameCollection::EnableParent
// ----------------------------------------------------
bool			__FrameCollection::_EnableParent(const __FrameBase *Tgt) const
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
				__SequenceCollection::~__SequenceCollection()
{
	// �S�폜
	_Container.clear();
}

// ----------------------------------------------------
//	SequenceCollection::Add
// ----------------------------------------------------
void			__SequenceCollection::Add(const std::shared_ptr<Sequencer> &Target)
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
				__SequenceCollection::Top() const
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
void			__SequenceCollection::Delete(const Sequencer *Target)
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
//	FrameCounter
// ----------------------------------------------------
//	FrameCounter::FrameCounter
// ----------------------------------------------------
				__FrameCounter::__FrameCounter()
{
	// �l������������
	_Value = 0;
	// �I��
	return;
}

// ----------------------------------------------------
//	FrameCounter::GetCount
// ----------------------------------------------------
double			__FrameCounter::GetCount()
{
	// �ԋp����
	return GetInstance()._Value;
}

// ----------------------------------------------------
//	FrameCounter::CountAdd
// ----------------------------------------------------
void			__FrameCounter::_CountAdd()
{
	// �l��1��������
	_Value++;
}
