// --------------------------------------------------------
//	apcSystem.h
// --------------------------------------------------------
//	�V�X�e���֘A�̃N���X���L�ڂ���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	�K�v�ȃw�b�_�[��ǂݍ���
// --------------------------------------------------------
#include <Windows.h>
#include <dxlib/DxLib.h>
#include <boost/function.hpp>
#include <include/apcClassBase.hpp>
#include <include/apcSequence.hpp>
#include <include/apxTemplate.hpp>

// --------------------------------------------------------
//	define�}�N�����g�p����
// --------------------------------------------------------
//	�����֐�
#define ApocalypseSetUp(Name)	__ApcSystem::ApcSetUp(__ApcSetting &Name)

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::System)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace System
	{
		// --------------------------------------------------------
		//	Typedef
		// --------------------------------------------------------
		typedef boost::function<Sequence::Sequencer*()>	SeqFunc;
		typedef	boost::function<bool()>					ExitFunc;

		/// <summary>
		///		�V�X�e���𓮂������߂̊e�평���ݒ荀�ڂ��܂Ƃ߂��N���X�D
		/// </summary>
		/// <remarks>
		///		<para>���̃N���X��ApcSystem::ApcSetUp()�֐��̈����Ƃ��ēn����܂��D</para>
		///		<para>ApcSetUp���Œl��ύX���邱�Ƃɂ��C�ݒ肪�ύX����܂��D</para>
		/// </remarks>
		/// <example>
		///		�g�p��:
		///		<code>
		///		void ApocalypseSetUp(As)
		///		{
		///			// �����V�[�P���X�֐����w�肷��i�K�{�j
		///			As.Sequence	= [](){return new AnySequence();}
		///			As.Width	= 800;			// �������w��
		///			As.Height	= 600;			// �c�����w��
		///			As.Title	= "Apocalypse";	// �E�C���h�E�����w��
		///			As.DualBoot = true;			// ��d�N���ł���悤�ɂ���
		///			�c
		///		</code>
		/// </example>
		class __ApcSetting : virtual public Base::__ApcInside
		{
		public:
			/// <summary>
			///		�쐬�����E�C���h�E�̉����D
			/// </summary>
			UINT				Width;
			/// <summary>
			///		�쐬�����E�C���h�E�̏c���D
			/// </summary>
			UINT				Height;
			/// <summary>
			///		���t���b�V�����[�g�̒l�D�����l��60�D
			/// </summary>
			UINT				Refresh;
			/// <summary>
			///		�쐬�����E�C���h�E�̃^�C�g�����D
			/// </summary>
			Base::String		Title;
			/// <summary>
			///		�쐬�����E�C���h�E�̃^�C�g�����D
			/// </summary>
			Base::String		ClassName;
			/// <summary>
			///		�W���̃t�H���g���D
			/// </summary>
			Base::String		DefaultFontName;
			/// <summary>
			///		<para>�����V�[�P���X���w�肷��֐���o�^���܂��D�K���w�肷��K�v������܂��D</para>
			///		<para>�߂�l��Sequence::Sequencer*�̈��������֐����w�肵�܂��D</para>
			///		<para>�߂�l�Ɏw�肵��Sequwncer*�������V�[�P���X�ƂȂ�܂��D</para>
			/// </summary>
			/// <example>
			///		�����_�����g�p���āCSequencer���p������FirstSeq��
			///		�����V�[�P���X�Ɏw�肷���:
			///		<code>
			///		void ApocalypseSetUp(As)
			///		{
			///			As.Sequence	= [](){return new FirstSeq();};
			///		}
			///		</code>
			/// </example>
			SeqFunc				Sequence;
			/// <summary>
			///		<para>�I������O�ɌĂяo�����֐���o�^�ł��܂��D</para>
			///		<para>�֐��͖߂�l��bool�̈��������֐��ł��D�߂�l��true�̏ꍇ�I�����܂��D</para>
			///		<para>������Ԃł͉����Ăяo����܂���D</para>
			/// </summary>
			ExitFunc			ExitFunction;
			/// <summary>
			///		��A�N�e�B�u���ł���ɓ��삷�邩�ǂ����D�����l��false�D
			/// </summary>
			bool				ActiveAll;
			/// <summary>
			///		Windows Vista�ȍ~��Aero�𖳌������邩�ǂ����D�W���ł�false�D
			/// </summary>
			bool				AeroDisable;
			/// <summary>
			///		�񓯊��ǂݍ��݂��s�����ǂ����D�����l��false�D
			/// </summary>
			bool				ASyncLoad;
			/// <summary>
			///		�f�o�b�O���[�h�ŋN�����邩�ǂ����D
			///		�����l��DEBUG�R���p�C���Ȃ�true, ����ȊO�Ȃ�false�D
			/// </summary>
			bool				DebugMode;
			/// <summary>
			///		��d�N�����\���ǂ����D�����l��false�D
			/// </summary>
			bool				DualBoot;
			/// <summary>
			///		GDI�`����s�����ǂ����D�����l��false�D
			/// </summary>
			bool				GDIDraw;
			/// <summary>
			///		�E�C���h�E���[�h�ŊJ�n���邩�ǂ����D�����l��true�D
			/// </summary>
			bool				WindowMode;
			/// <summary>
			///		�R���X�g���N�^
			/// </summary>
								__ApcSetting();
		};

		/// <summary>
		///		�V�X�e���֘A�̃N���X�DSingleton�D
		/// </summary>
		/// <remarks>
		///		<para>���̃N���X���ł́C�Q�[���̋N���ƏI���֘A�̏������s���܂��D</para>
		///		<para>ApcSetup�֐��͓Ǝ��Ɏ�������K�v������܂��D</para>
		/// </remarks>
		class __ApcSystem : virtual public Template::__Singleton<__ApcSystem>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__ApcSystem>;
		public:
			/// <summary>
			///		�E�C���h�E�̉������擾����D
			/// </summary>
			static UINT			GetWindowWidth();
			/// <summary>
			///		�E�C���h�E�̉������擾����D
			/// </summary>
			static UINT			GetWindowHeight();
			/// <summary>
			///		Apocalypse�N���O�̃Z�b�g�A�b�v���s���֐��ł��D
			/// </summary>
			/// <remarks>
			///		���̊֐��̓��[�U�[���Ǝ��ɒ�`����K�v������܂��D
			/// </remarks>
			/// <paramref name="as">
			///		<para>�Q�[���̊e��ݒ荀�ڂ��i�[�����N���X�̎Q�ƁD</para>
			///		<para>���̒l��ύX���邱�ƂŐݒ��ύX���鎖���ł��܂��D</para>
			///	</paramref>
			/// <example>
			///		�g�p��:
			///		<code>
			///		void ApocalypseSetUp(As)
			///		{
			///			// �����ݒ���s���D�ڍׂ�__ApcSetting���Q�Ƃ��Ă��������D
			///		}
			///		</code>
			/// </example>
			void				ApcSetUp(__ApcSetting &As);
			/// <summary>
			///		�N������
			/// </summary>
			bool				ApcStart() const;
			/// <summary>
			///		�P�t���[�����ɕK�v�ȓ�����s���D
			/// </summary>
			bool				ApcProcess() const;
			/// <summary>
			///		�Q�[�����I������D
			/// </summary>
			void				ApcEnd() const;
			/// <summary>
			///		�ݒ��ۑ����邽�߂̍��ځD
			/// </summary>
			std::shared_ptr<__ApcSetting>
								GameSetting;
		private:
			/// <summary>
			///		�R���X�g���N�^
			/// </summary>
								__ApcSystem();
			/// <summary>
			///		�v���O�����̊�f�B���N�g����ݒ肷��D 
			/// </summary>
			void				_SetProgramDirectory() const;
			/// <summary>
			///		�Q�[���N���O�Ɋe��ݒ���s���D
			/// </summary>
			void				_InitGameProcess() const;
			/// <summary>
			///		�Q�[�����N������D
			/// </summary>
			void				_RunStartProcess() const;
			/// <summary>
			///		�Q�[�����I������D
	/// </summary>
			void				_RunEndProcess() const;
		};
	}
}
