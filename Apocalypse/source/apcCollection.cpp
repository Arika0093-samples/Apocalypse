// --------------------------------------------------------
//	apcCollection.cpp
// --------------------------------------------------------
//	apcCollection.h �̃����o�֐��̎��̂�u��
// --------------------------------------------------------
#include "Apocalypse.h"

// ----------------------------------------------------
//	FrameCollection
// ----------------------------------------------------
//	FrameCollection::FrameCollection (Constructor)
// ----------------------------------------------------
				__FrameCollection::__FrameCollection()
{
	// Get System Instance
	__ApcSystem gs = __ApcSystem::GetInstance();
	// ----------------------------------------------------
	// �ŏ�ʃt���[�����쐬����
	_TopParent = std::shared_ptr<EdgeFrame>(new EdgeFrame());
	// �����Əc�����w�肷��
	_TopParent->Width	= gs.GetWindowWidth();
	_TopParent->Height	= gs.GetWindowHeight();
	// ���w��𖳌��ɂ���D
	_TopParent->SpecifyWithParcent = false;
}

// ----------------------------------------------------
//	FrameCollection::Insert
// ----------------------------------------------------
void			__FrameCollection::Insert(const std::shared_ptr<__FrameBase> &Target)
{
	// ����NULL�t���[�����n���ꂽ��
	if(!Target.get()){
		// �������Ȃ�
		return;
	}
	// �}������
	_Container.insert(Target);
}

// ----------------------------------------------------
//	FrameCollection::Enum
// ----------------------------------------------------
std::shared_ptr<__FrameBase>	
				__FrameCollection::Enum(bool ResetFlag) const
{
	// ���݂̃J�E���g����ۑ�����
	static std::multiset<std::shared_ptr<__FrameBase>>::iterator Count;
	// �擾�����t���[����ۑ�����
	std::shared_ptr<__FrameBase> Result = NULL;
	// ------------------------------------------------
	// �����������t���O���w�肳��Ă����
	if(ResetFlag){
		// �J�E���g������������
		Count = _Container.begin();
	}
	// ������������Ȃ�
	if(Count != _Container.end()){
		// �擾����
		Result = *Count;
		// ���ɐi�߂�
		++Count;
	}
	// �����e��Enable��false�̃t���[��������Ȃ�
	if(Result && !_EnableParent(Result)){
		// �ēx�Ăяo��
		return Enum(false);
	}
	// �����e�t���[�����w�肳��Ă��Ȃ����
	if(!Result.get() && !Result->Parent.get()
	 && Result.GetPointer() != _TopParent.GetPointer()){
		// �e�t���[����TopParent�Ɏw�肷��
		Result->Parent = _TopParent.GetPointer();
	}
	// �ԋp����
	return Result;
}

// ----------------------------------------------------
//	FrameCollection::Erase
// ----------------------------------------------------
void			__FrameCollection::Erase(const std::shared_ptr<__FrameBase> &Target)
{
	// �C�e���[�^���m�ۂ��Đ擪�ɂ���
	auto Count = _Container.begin();
	// ------------------------------------------------
	// ���������ɖ����|�C���^�܂��͍ŏ�ʃt���[����n���ꂽ��
	if(!Target.get() || Target == _TopParent){
		// �������Ȃ�
		return;
	}
	// �I���܂Ń��[�v����i�����̃t���[����e�Ɏ��t���[����T���j
	while(Count != _Container.end()){
		// �����e�t���[���������̃t���[���Ɠ����Ȃ�
		if(Count->GetPointer()->Parent == Target){
			// �e�t���[��������������
			(*Count)->Parent = (*Count)->Parent->Parent;
		}
		// �C�e���[�^��i�߂�
		Count++;
	}
	// �w�肳�ꂽ�t���[�����폜����
	_Container.erase(Target);
	// �I��
	return;
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
bool			__FrameCollection::_Sort::operator()(const std::shared_ptr<__FrameBase> &A, const std::shared_ptr<__FrameBase> &B)
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
	// �ŏ��Ɉ�擾����
	auto fTemp = Enum(true);
	// �o�C���j�A�@�ŕ`��
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	// ���������Ȃ�
	if(fTemp.get() == NULL){
		// �I��
		return;
	}
	// ���[�v���N����
	do{
		// ���u�����h��L����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,
			(int)( fTemp->Alpha * _GetParentAlphaParcent(fTemp) ));
		// �����E�c���̕W���l���擾
		fTemp->_SetProperties();
		// �ʒu�����Z�b�g����
		fTemp->_SetDefaultPosition();
		// ������\���ݒ�Ȃ��
		if(fTemp->Visible == false){
			// �`�悹���ɌJ��Ԃ��D
			continue;
		}
		// �擾�����t���[���̕`��֐������s����
		fTemp->_DrawThisFrame();
	}
	// NULL���Ԃ����܂Ŏ擾�𑱂���
	while((fTemp = Enum(false)).get());
}

// ----------------------------------------------------
//	FrameBase::GetParentAlphaParcent
// ----------------------------------------------------
double			__FrameCollection::_GetParentAlphaParcent(const std::shared_ptr<__FrameBase> &Target) const
{
	// ������ԋp
	return ((double)Target->Alpha / 255.0)*(Target->Parent.get() ? _GetParentAlphaParcent(Target->Parent) : 1.00);
}

// ----------------------------------------------------
//	FrameBase::GetParentZindex
// ----------------------------------------------------
unsigned int	__FrameCollection::_GetParentZindex(const std::shared_ptr<__FrameBase> &Target) const
{
	// ���g�̐e�t���[����Z���W+���g��Z���W��ԋp
	return (Target->DrawOrder + (Target->Parent.get() ? _GetParentZindex(Target->Parent) : 1));
}

// ----------------------------------------------------
//	FrameCollection::EnableParent
// ----------------------------------------------------
bool			__FrameCollection::_EnableParent(const std::shared_ptr<__FrameBase> &Target) const
{
	// �����������Ȃ�
	if(!Target.get()){
		// TRUE��Ԃ�
		return true;
	}
	// ����.Enable��TRUE�Ȃ�
	return (Target->Enable ? _EnableParent(Target->Parent) : false);
}

// ----------------------------------------------------
//	SequenceCollection
// ----------------------------------------------------
//	SequenceCollection::Add
// ----------------------------------------------------
void			__SequenceCollection::Add(const std::shared_ptr<Sequencer> &Target)
{
	// ����NULL�Ȃ�
	if(Target.get() == NULL){
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
		return std::shared_ptr<Sequencer>::Empty();
	}
	// �X�^�b�N�̈�ԏ��Ԃ�
	return _Container.back();
}

// ----------------------------------------------------
//	SequenceCollection::Delete
// ----------------------------------------------------
void			__SequenceCollection::Delete(const std::shared_ptr<Sequencer> &Target)
{
	// �ꎞ�ۑ�����
	std::shared_ptr<Sequencer> TopSeq = Top();
	// ----------------------------------------------------
	// ����NULL�Ȃ�
	if(!Target.get() || !TopSeq.get()){
		// �������Ȃ�
		return;
	}
	// ���[�v
	do{
		// �����v�f���폜����
		_Container.pop_back();
	// �����̃V�[�P���X�ɂȂ�܂ő�����
	}while((TopSeq != Target) && (TopSeq = Top()).get());
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
UINT			__FrameCounter::GetCount()
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
