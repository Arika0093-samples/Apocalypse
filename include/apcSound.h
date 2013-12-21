// --------------------------------------------------------
//	apcSound.h
// --------------------------------------------------------
//	���֘A�̃N���X���L�ڂ���D
// --------------------------------------------------------
//	��x�����ǂݍ���
#pragma once

// --------------------------------------------------------
//	���O��Ԃ��g�p(Apocalypse::Sound)
// --------------------------------------------------------
namespace Apocalypse
{
	namespace Sound
	{
		/// <summary>
		///		�����Đ����邽�߂̊e�퍀�ڂ��܂Ƃ߂��N���X�D
		/// </summary>
		/// <remarks>
		///		���̃N���X���g�p���邱�Ƃ�SE�i���ʉ��j��BGM�Ɨ����ɑΉ��ł��܂��D
		/// </remarks>
		/// <example>
		///		�g�p��:
		///		<code>
		///		ApcSound* Bgm = new ApcSound("BGM.wav");
		///		Bgm->Play();	// �Đ�����
		///		</code>
		/// </example>
		class SoundObject : virtual public Base::__ApcBase
		{
		public:
			/// <summary>
			///		ApcSound�N���X�̃R���X�g���N�^�D
			/// </summary>
			/// <remarks>
			///		�����Ƀt�@�C�������w�肷�邱�Ƃł��̃t�@�C�����Đ�����p�ӂ��s���܂��D
			/// </remarks>
			/// <param name="FilePath">
			///		�Đ�����Ώۂ̃t�@�C�����D
			///	</param>
								SoundObject(Base::String FilePath);
			/// <summary>
			///		�Đ����̉��ʂ��w�肷��D
			/// </summary>
			/// <remarks>
			///		0�i�����j�`255�i�ő�j�܂ł̊ԂŎw�肵�܂��D
			/// </remarks>
			UINT				Volume;
			/// <summary>
			///		�Đ����̃p�����w�肷��D
			/// </summary>
			/// <remarks>
			///		-10000�i���������j�`10000�i�E�������j�̊ԂŎw�肵�܂��D
			/// </remarks>
			int					Pan;
			/// <summary>
			///		�Đ������擾����֐��D
			/// </summary>
			bool				IsPlaying();
			/// <summary>
			///		�Đ����s���֐��D
			/// </summary>
			/// <remarks>
			///		�����̃T�E���h�n���h�������ɍĐ����s���܂��D
			///		��~����ۂ� Stop() �֐����g�p���܂��D
			/// </remarks>
			void				Play();
			/// <summary>
			///		�Đ���~���s���֐��D
			/// </summary>
			/// <remarks>
			///		���݉����Đ����Ă���ꍇ��~���܂��D
			/// </remarks>
			void				Stop();
		private:
			/// <summary>
			///		���f�[�^��ێ�����n���h���D
	/// </summary>
			int					_Handle;
		};
	}
}