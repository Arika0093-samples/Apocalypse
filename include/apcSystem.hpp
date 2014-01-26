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
//	���O��Ԃ��g�p(Apocalypse::System)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace System
	{
		// --------------------------------------------------------
		//	Typedef
		// --------------------------------------------------------
		typedef boost::function<std::shared_ptr<Sequence::Sequencer>()>	SeqFunc;
		typedef	boost::function<bool()>									ExitFunc;

		/// <summary>
		///		�V�X�e���𓮂������߂̊e�평���ݒ荀�ڂ��܂Ƃ߂��N���X�D
		/// </summary>
		/// <remarks>
		///		<para>���̃N���X�̒l��ύX���āCAccept�֐������s���邱�ƂœK�p����܂��D</para>
		///		<para>ApcSetUp�֐����Œl��ύX���邱�ƂŁC�����Őݒ肪�K�p����܂��D</para>
		/// </remarks>
		/// <example>
		///		�g�p��:
		///		<code>
		///		void ApocalypseSetUp()
		///		{
		///			// �����V�[�P���X�֐����w�肷��i�K�{�j
		///			ApplicationConfig::Sequence	= [](){return new AnySequence();}
		///			ApplicationConfig::Width	= 800;			// �������w��
		///			ApplicationConfig::Height	= 600;			// �c�����w��
		///			ApplicationConfig::Title	= "GameTest";	// �E�C���h�E�����w��
		///			ApplicationConfig::DualBoot = true;			// ��d�N���ł���悤�ɂ���
		///			// etc...
		///		}
		///		</code>
		/// </example>
		class ApplicationConfig : public Base::__ApcBase
		{
		public:
			/// <summary>
			///		�쐬�����E�C���h�E�̉����D
			/// </summary>
			static UINT				Width;
			/// <summary>
			///		�쐬�����E�C���h�E�̏c���D
			/// </summary>
			static UINT				Height;
			/// <summary>
			///		���t���b�V�����[�g�̒l�D�����l��60�D
			/// </summary>
			static UINT				Refresh;
			/// <summary>
			///		�쐬�����E�C���h�E�̃^�C�g�����D
			/// </summary>
			static Value::String	Title;
			/// <summary>
			///		�쐬�����E�C���h�E�̃^�C�g�����D
			/// </summary>
			static Value::String	ClassName;
			/// <summary>
			///		�W���̃t�H���g���D
			/// </summary>
			static Value::String	DefaultFontName;
			/// <summary>
			///		<para>�����V�[�P���X���w�肷��֐���o�^���܂��D�K���w�肷��K�v������܂��D</para>
			///		<para>�߂�l��shared_ptr(Sequence::Sequencer)�̈��������֐����w�肵�܂��D</para>
			///		<para>�߂�l�Ɏw�肵��Sequencer�������V�[�P���X�ƂȂ�܂��D</para>
			/// </summary>
			/// <example>
			///		�����_�����g�p���āCSequencer���p������FirstSeq��
			///		�����V�[�P���X�Ɏw�肷���:
			///		<code>
			///		void ApocalypseSetUp()
			///		{
			///			ApplicationConfig::Sequence	= [](){return new FirstSeq();};
			///		}
			///		</code>
			/// </example>
			static SeqFunc			Sequence;
			/// <summary>
			///		<para>�I������O�ɌĂяo�����֐���o�^�ł��܂��D</para>
			///		<para>�֐��͖߂�l��bool�̈��������֐��ł��D�߂�l��true�̏ꍇ�I�����܂��D</para>
			///		<para>������Ԃł͉����Ăяo����܂���D</para>
			/// </summary>
			static ExitFunc			ExitFunction;
			/// <summary>
			///		��A�N�e�B�u���ł���ɓ��삷�邩�ǂ����D�����l��false�D
			/// </summary>
			static bool				ActiveAll;
			/// <summary>
			///		Windows Vista�ȍ~��Aero�𖳌������邩�ǂ����D�W���ł�false�D
			/// </summary>
			static bool				AeroDisable;
			/// <summary>
			///		�񓯊��ǂݍ��݂��s�����ǂ����D�����l��false�D
			/// </summary>
			static bool				ASyncLoad;
			/// <summary>
			///		�f�o�b�O���[�h�ŋN�����邩�ǂ����D
			///		�����l��DEBUG�R���p�C���Ȃ�true, ����ȊO�Ȃ�false�D
			/// </summary>
			static bool				DebugMode;
			/// <summary>
			///		��d�N�����\���ǂ����D�����l��false�D
			/// </summary>
			static bool				DualBoot;
			/// <summary>
			///		GDI�`����s�����ǂ����D�����l��false�D
			/// </summary>
			static bool				GDIDraw;
			/// <summary>
			///		�E�C���h�E���[�h�ŊJ�n���邩�ǂ����D�����l��true�D
			/// </summary>
			static bool				WindowMode;
			/// <summary>
			///		���ݒ��K�p����֐�
			/// </summary>
			static void				Accept();
			/// <summary>
			///		�W���̃t�H���g�����擾
			/// </summary>
			static Value::String	_GetDefaultFontName();
		};

		/// <summary>
		///		�V�X�e���֘A�̃N���X�DSingleton�D
		/// </summary>
		/// <remarks>
		///		<para>���̃N���X���ł́C�Q�[���̋N���ƏI���֘A�̏������s���܂��D</para>
		///		<para>ApcSetup�֐��͓Ǝ��Ɏ�������K�v������܂��D</para>
		/// </remarks>
		class __ApcSystem : public Template::__Singleton<__ApcSystem>
		{
			/// <summary>
			///		Singleton�N���X�͑S�Ẵ����o�ɃA�N�Z�X�\�ł��D
			/// </summary>
			friend class		Template::__Singleton<__ApcSystem>;
		public:
			/// <summary>
			///		Apocalypse�N���O�̃Z�b�g�A�b�v���s���֐��ł��D
			/// </summary>
			/// <remarks>
			///		���̊֐��̓��[�U�[���Ǝ��ɒ�`����K�v������܂��D
			/// </remarks>
			/// <example>
			///		�g�p��:
			///		<code>
			///		void ApocalypseSetUp()
			///		{
			///			// �����ݒ���s���D�ڍׂ�ApplicationConfig::���Q�Ƃ��Ă��������D
			///		}
			///		</code>
			/// </example>
			void				ApcSetUp() const;
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
