// --------------------------------------------------------
//	apcCollection.h
// --------------------------------------------------------
//	���낢��Ǘ���������W�����肷��N���X���쐬����D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <list>
#include <set>
#include <include/apcClassBase.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Collection)
// --------------------------------------------------------
namespace Apocalypse
{
	// ------------------------------------------------
	//	Front Declaration
	// ------------------------------------------------
	namespace Draw
	{
		class __FrameBase;
		class EdgeFrame;
	}
	namespace Sequence
	{
		class Sequencer;
	}

	// ----------------------------------------------------
	//	Collection���O��ԓ��̃N���X���L��
	// ----------------------------------------------------
	namespace Collection
	{
		///	<summary>
		///		�t���[�����Ǘ�����p�̃N���X�D
		///	</summary>
		/// <remarks>
		///		<para>���̃N���X�ɂ���ăt���[���͎������W�E�`�悳��܂��D</para>
		///		<para>���̃N���X��singleton�ł��D</para>
		/// </remarks>
		class __FrameCollection : virtual public Template::__Singleton<__FrameCollection>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__FrameCollection>;
		public:
			///	<summary>
			///		�w�肵���t���[����ǉ�����D
			///	</summary>
			/// <param name = "ResetFlag">
			///		�ǉ�����Ώۂ̃t���[���D
			/// </param>
			void				Insert(const std::shared_ptr<Draw::__FrameBase> &Target);
			///	<summary>
			///		���݈ꗗ�ɓo�^����Ă���t���[����񋓂���D
			///	</summary>
			/// <param name = "ResetFlag">
			///		true
			///		<para>�ŏ�����񋓂��J�n����D</para>
			///		false
			///		<para>�O��̓r������񋓂𑱂���D</para>
			/// </param>
			std::shared_ptr<Draw::__FrameBase>	
								Enum(bool ResetFlag) const;
			///	<summary>
			///		�w�肵���t���[�������O����D
			///	</summary>
			/// <param name = "Target">
			///		���O����Ώۂ̃t���[���DNULL���w�肵���ꍇ���ׂč폜�����D
			/// </param>
			void				Erase(const std::shared_ptr<Draw::__FrameBase> &Target);
			///	<summary>
			///		�R���e�i���̃t���[����S�č폜����D
			///	</summary>
			void				Clear();
			///	<summary>
			///		���ׂẴt���[����`�悷��D
			///	</summary>
			void				DrawAll() const;
		private:
			///	<summary>
			///		�R���X�g���N�^
			///	</summary>
								__FrameCollection();
			///	<summary>
			///		�\�[�g�p�̃N���X�Dset�R���e�i���̗v�f���\�[�g����p�Ɏg�p����D
			///	</summary>
			class				_Sort
			{
			public:
				bool			operator()(const std::shared_ptr<Draw::__FrameBase> &A, const std::shared_ptr<Draw::__FrameBase> &B);
			};
			/// <summary>
			///		�e�t���[���̃��l�̊������擾����D
			///		�e�t���[���̃������ׂ�255�̏ꍇ��1.0���Ԃ�D
			/// </summary>
			/// <param name = "Target">
			///		���l�����𒲂ׂ�Ώۂ̃t���[���D
			/// </param>
			double				_GetParentAlphaParcent(const std::shared_ptr<Draw::__FrameBase> &Target) const;
			/// <summary>
			///		�e�t���[����Z���W�̍��v�l���擾����֐��D
			/// </summary>
			/// <param name = "Target">
			///		Z���W�𒲂ׂ�Ώۂ̃t���[���D
			/// </param>
			unsigned int		_GetParentZindex(const std::shared_ptr<Draw::__FrameBase> &Target) const;
			///	<summary>
			///		�e�t���[���ɖ����t���[�������邩�ǂ����𒲂ׂ�D
			///	</summary>
			/// <param name = "Target">
			///		Enable�𒲂ׂ�Ώۂ̃t���[���D
			/// </param>
			bool				_EnableParent(const std::shared_ptr<Draw::__FrameBase> &Target) const;
			///	<summary>
			///		�ŏ�ʂ̃t���[���D
			///	</summary>
			std::shared_ptr<Draw::EdgeFrame>
								_TopParent;
			///	<summary>
			///		�t���[�����Ǘ����邽�߂̃R���e�i
			///	</summary>
			std::multiset<std::shared_ptr<Draw::__FrameBase>, __FrameCollection::_Sort>
								_Container;
		};

		///	<summary>
		///		���݂̃V�[�P���X���Ǘ�����p�̃N���X�D
		///	</summary>
		/// <remarks>
		///		<para>���̃N���X�ɂ���ăV�[�P���X�͊Ǘ�����܂��D</para>
		///		<para>���̃N���X��singleton�ł��D</para>
		/// </remarks>
		class __SequenceCollection : virtual public Template::__Singleton<__SequenceCollection>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__SequenceCollection>;
		public:
			///	<summary>
			///		�w�肵���V�[�P���X�𖖔��ɒǉ�����D
			///	</summary>
			void				Add(const std::shared_ptr<Sequence::Sequencer> &Target);
			///	<summary>
			///		�ŏ�ʂ̃V�[�P���X�����o���D
			///	</summary>
			std::shared_ptr<Sequence::Sequencer>
								Top() const;
			///	<summary>
			///		�w�肵���V�[�P���X�܂ł̂��ׂẴV�[�P���X���폜����D
			///	</summary>
			void				Delete(const Sequence::Sequencer *Target);
		private:
			///	<summary>
			///		�R���X�g���N�^
			///	</summary>
								__SequenceCollection(){}
			///	<summary>
			///		�V�[�P���X���Ǘ����邽�߂̒P�����R���e�i�D
			///	</summary>
			std::list<std::shared_ptr<Sequence::Sequencer>>
								_Container;
		};

		///	<summary>
		///		�N�����Ă���̃t���[�������擾����D�P����������J�E���^�Ƃ��Ă��g�p�\�D
		///	</summary>
		/// <remarks>
		///		���̃N���X��singleton�ł��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		// ���݂̃J�E���^�l���擾����
		///		int Counter = FrameCounter::GetCount();
		///		</code>
		/// </example>
		class __FrameCounter : virtual public Template::__Singleton<__FrameCounter>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__FrameCounter>;
		public:
			/// <summary>
			///		�J�E���g�����擾����֐��D
			/// </summary>
			static UINT			GetCount();
			/// <summary>
			///		�J�E���g���𑝉�������֐��D1�t���[���Ɉ�x�����ĂԁD
			/// </summary>
			void				_CountAdd();
		private:
			/// <summary>
			///		Countructor�D
			/// </summary>
								__FrameCounter();
			/// <summary>
			///		�J�E���g����ۑ����Ă����ϐ��D
			/// </summary>
			unsigned int		_Value;
		};
	}
}

