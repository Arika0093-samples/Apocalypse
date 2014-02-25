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
#include <vector>
#include <list>
#include <boost/foreach.hpp>
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
		class __FrameCollection :  public Template::__Singleton<__FrameCollection>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__FrameCollection>;
		public:
			///	<summary>
			///		�f�X�g���N�^
			///	</summary>
			virtual				~__FrameCollection();
			/// <summary>
			///		__FrameBase��shared_ptr��typedef�ŏȗ�
			/// </summary>
			typedef				Draw::__FrameBase*		FramePtr;
			/// <summary>
			///		__FrameBase��shared_ptr���Ǘ�����vector��typedef�ŏȗ�
			/// </summary>
			typedef				std::vector<FramePtr>*	FrameListPtr;
			/// <summary>
			///		const __FrameCollection::FramePtr&�������ɂƂ�bool��ԋp����function��typedef�ŏȗ�
			/// </summary>
			typedef				boost::function<bool(const FramePtr&)>	CheckFunc;
			///	<summary>
			///		�w�肵���t���[����ǉ�����D
			///	</summary>
			/// <param name = "Target">
			///		�ǉ�����Ώۂ̃t���[���D
			/// </param>
			void				Insert(Draw::__FrameBase *Target);
			///	<summary>
			///		���݈ꗗ�ɓo�^����Ă���t���[����vector�R���e�i�ŕԋp����D
			///	</summary>
			FrameListPtr		Enum() const;
			///	<summary>
			///		���݈ꗗ�ɓo�^����Ă���t���[���̂����C�������ƈ�v���鍀�ڂ�vector�R���e�i�ŕԋp����D
			///	</summary>
			/// <param name = "Func">
			///		const __FrameCollection::FramePtr�������ɂƂ�bool��Ԃ��֐��Dtrue�ԋp�ň�v�Ɣ��f����D
			/// </param>
			FrameListPtr		Enum(CheckFunc Func) const;
			///	<summary>
			///		�w�肵���t���[�������O����D
			///	</summary>
			/// <param name = "Target">
			///		���O����Ώۂ̃t���[���DNULL���w�肵���ꍇ���ׂč폜�����D
			/// </param>
			void				Erase(const Draw::__FrameBase *Target);
			///	<summary>
			///		�w�肵�������ƈ�v����t���[���̂����n�߂̈���擾����D
			///	</summary>
			/// <param name = "Func">
			///		const __FrameCollection::FramePtr�������ɂƂ�bool��Ԃ��֐��Dtrue�ԋp�ň�v�Ɣ��f����D
			/// </param>
			FramePtr			Find(CheckFunc Func) const;
			///	<summary>
			///		�R���e�i���̃t���[����Z�I�[�_�[���ɕ��ёւ���D
			///	</summary>
			void				Sort();
			///	<summary>
			///		�R���e�i���̃t���[����S�č폜����D
			///	</summary>
			void				Clear();
			///	<summary>
			///		���ׂẴt���[����`�悷��D
			///	</summary>
			void				DrawAll() const;
			///	<summary>
			///		�ŏ�ʃt���[�����擾����
			///	</summary>
			Draw::EdgeFrame*	GetTopParent() const;
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
				bool			operator()(const Draw::__FrameBase *A, const Draw::__FrameBase *B);
			};
			/// <summary>
			///		�e�t���[����Z���W�̍��v�l���w�肷��֐��D
			/// </summary>
			/// <param name = "Target">
			///		Z���W���w�肷��Ώۂ̃t���[���D
			/// </param>
			void				_SetZindex(Draw::__FrameBase *Target) const;
			///	<summary>
			///		�e�t���[���ɖ����t���[�������邩�ǂ����𒲂ׂ�D
			///	</summary>
			/// <param name = "Target">
			///		Enable�𒲂ׂ�Ώۂ̃t���[���D
			/// </param>
			bool				_EnableParent(const Draw::__FrameBase *Target) const;
			///	<summary>
			///		�ŏ�ʂ̃t���[���D
			///	</summary>
			Draw::EdgeFrame*	_TopParent;
			///	<summary>
			///		�t���[�����Ǘ����邽�߂̃R���e�i
			///	</summary>
			std::list<Draw::__FrameBase*>
								_Container;
		};

		///	<summary>
		///		���݂̃V�[�P���X���Ǘ�����p�̃N���X�D
		///	</summary>
		/// <remarks>
		///		<para>���̃N���X�ɂ���ăV�[�P���X�͊Ǘ�����܂��D</para>
		///		<para>���̃N���X��singleton�ł��D</para>
		/// </remarks>
		class __SequenceCollection : public Template::__Singleton<__SequenceCollection>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__SequenceCollection>;
		public:
			///	<summary>
			///		�f�X�g���N�^
			///	</summary>
			virtual				~__SequenceCollection();
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
			///	<summary>
			///		���݂̃V�[�P���X�̌����擾����
			///	</summary>
			unsigned int		Size() const;
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
		class __FrameCounter : public Template::__Singleton<__FrameCounter>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__FrameCounter>;
		public:
			/// <summary>
			///		�J�E���g�����擾����֐��D
			/// </summary>
			static double		GetCount();
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
			double				_Value;
		};
	}
}