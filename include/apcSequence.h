// --------------------------------------------------------
//	apcSequence.h
// --------------------------------------------------------
//	�V�[�P���X�̃N���X���쐬����D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <include/apcClassBase.h>
#include <include/apcEvent.h>
#include <include/apxTemplate.h>

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Sequence)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Sequence
	{
		///	<summary>
		///		�V�[�P���X�̊�ՃN���X�D
		///	</summary>
		/// <remarks>
		///		���̃N���X���̂͐����ł��܂���D���̃N���X���p�������N���X���g�p���܂��D
		/// </remarks>
		/// <example>
		///		�g�p��: 
		///		<code>
		///		class MainSequence : public Sequencer
		///		{
		///		public:
		///			�c
		///		};
		///		</code>
		/// </example>
		class Sequencer : virtual public Base::__ApcBase
		{
		public:
			/// <summary>
			///		���̃t���[���̃C�x���g���X�g�D
			/// </summary>
			Event::__EventHandleList
								Events;
			///	<summary>
			///		�ʂ̃V�[�P���X�ɐ�����ړ�������p�̊֐��D
			///	</summary>
			/// <remarks>
			///		���݂̃V�[�P���X�N���X���C�����ɓn���ꂽ�V�[�P���X�ɕύX���܂��D
			/// </remarks>
			///	<param name = "To">
			///		������ړ��������̃V�[�P���X�Dnew�ňړ�����m�ۂ��ēn���D<br />
			///	</param>
			/// <example>
			///		�g�p��: 
			///		<code>
			///		void MainSequence::FrameProcess()
			///		{
			///			if(Key::AnyPushing()){				// ����������������Ă����
			///				MoveSequence(new XSequence());	// ���g��j������XSequence�Ɉړ�����
			///			}
			///		}
			///		</code>
			/// </example>
			void				Move(std::shared_ptr<Sequencer> To);
			///	<summary>
			///		���݂̃V�[�P���X�ɐV�����V�[�P���X���d�˂�D
			///	</summary>
			/// <remarks>
			///		<para>���݂̃V�[�P���X�N���X�����̂܂܂ɁC���ɃV�[�P���X���ڂ��Đ�����ړ����܂��D</para>
			///		<para>Add�Œǉ������V�[�P���X��j���������Ƃ��� DeleteSequence(); ���g�p���܂��D</para>
			/// </remarks>
			///	<param name = "To">
			///		������ړ��������̃V�[�P���X�Dnew�ňړ�����m�ۂ��ēn���D<br />
			///	</param>
			/// <example>
			///		�g�p��: 
			///		<code>
			///		void MainSequence::FrameProcess()
			///		{
			///			if(Key::AnyPushing()){				// ����������������Ă����
			///				AddSequence(new XSequence());	// XSequence�Ɉړ�����
			///			}
			///		}
			///		</code>
			/// </example>
			void				Add(std::shared_ptr<Sequencer> To);
			///	<summary>
			///		���݂̃V�[�P���X���I��������D
			///	</summary>
			/// <remarks>
			///		<para>���݂̃V�[�P���X�N���X��j�����āC����̃V�[�P���X�Ɉړ����܂��D</para>
			///		<para>�V�[�P���X���c���Ă��Ȃ��ꍇ�̓Q�[�����I�����܂��D</para>
			/// </remarks>
			/// <example>
			///		�g�p��: 
			///		<code>
			///		void MainSequence::FrameProcess()
			///		{
			///			if(Key::AnyPushing()){	// ����������������Ă����
			///				DeleteSequence();	// ���݂̃V�[�P���X���폜
			///			}
			///		}
			///		</code>
			/// </example>
			void				Delete();
			///	<summary>
			///		Destructor.
			///	</summary>
			virtual				~Sequencer(){}
		protected:
			///	<summary>
			///		�R���X�g���N�^�D���̃N���X���g�͌Ăяo���Ȃ��D
			///	</summary>
								Sequencer(){}
		};
	}
}

