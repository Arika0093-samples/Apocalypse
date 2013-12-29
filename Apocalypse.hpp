// ----------------------------------------------------
//	Apocalypse.hpp
//						Copyright (C) 2013-2014 Arika.
// ----------------------------------------------------
//	Apocalypse�̑S�@�\���g�p����̂�include����w�b�_�[�ł��D
//	�g�p���̎�Ԃ����炷���߂ɁC
//	�@�E�S�t�@�C����include
//	�@�E�S���O��Ԃ�W����using
//	�@�E��������define�}�N�����`
//	�@�Elib�������œǂݍ���
//	��4���s���Ă��܂��D
//	�C�ɂȂ�l�͎����Ōʂ�include���Ă��������D
// ----------------------------------------------------
//	read once
#pragma once

// ----------------------------------------------------
//	�ǂݍ��ݎ��̐ݒ�
// ----------------------------------------------------
//	�ݒ��L���ɂ���ɂ́C�擪�̃R�����g�A�E�g���O���ĉ������D
//	#define NOTUSING_DEFINEMACRO	// �}�N�����g�p���܂���
//	#define NOTUSING_NAMESPACE		// ���O��Ԃ�using���܂���
//	#define NOTLOADING_LIB			// .lib��ǂݍ��݂܂���

// ----------------------------------------------------
//	Include(��`�֘A)
// ----------------------------------------------------
//	�}�N����`
#include "include/apxMacro.hpp"
// ----------------------------------------------------
//	���N���X(���O���: Apocalypse::Base)
#include "include/apcClassBase.hpp"
// ----------------------------------------------------
//	�e���v���[�g�N���X(���O���: Apocalypse::Template)
#include "include/apxTemplate.hpp"
// ----------------------------------------------------
//	�w���v�t�@�C���쐬�p�w�b�_�[
#include "include/apxDoxygen.hpp"

// ----------------------------------------------------
//	Include(�N���X�֘A)
// ----------------------------------------------------
//	�C�x���g�N���X(���O���: Apocalypse::Event)
#include "include/apcEvent.hpp"
// ----------------------------------------------------
//	�v�f�Ǘ��N���X(���O���: Apocalypse::Collection)
#include "include/apcCollection.hpp"
// ----------------------------------------------------
//	���͊Ǘ��N���X(���O���: Apocalypse::Input)
#include "include/apcInput.hpp"
// ----------------------------------------------------
//	�V�[�P���X�N���X(���O���: Apocalypse::Sequence)
#include "include/apcSequence.hpp"
// ----------------------------------------------------
//	�`��N���X(���O���: Apocalypse::Draw)
#include "include/apcDrawing.hpp"
// ----------------------------------------------------
//	�����N���X(���O���: Apocalypse::Sound)
//#include "include/apcSound.hpp"
// ----------------------------------------------------
//	�����N���X(���O���: Apocalypse::Expression)
//#include "include/apcExpression.hpp"
// ----------------------------------------------------
//	�V�X�e���Ǘ��N���X(���O���: Apocalypse::System)
#include "include/apcSystem.hpp"
// ----------------------------------------------------
//	UI�`��/�Ǘ��N���X(���O���: Apocalypse::UI)
//#include "include/apcInterface.hpp"

// ----------------------------------------------------
//	lib�t�@�C���ǂݍ���
// ----------------------------------------------------
//	NOTLOADING_LIB����`����Ă���ꍇ����œǂݍ��݂܂���D 
#ifndef NOTLOADING_LIB
	#ifndef _WIN64
		#ifndef _DEBUG
			#pragma comment(lib, "lib/Apocalypse.lib")
		#else
			#pragma comment(lib, "lib/Apocalypse_d.lib")
		#endif
	#else
		#ifndef _DEBUG
			#pragma comment(lib, "lib/Apocalypse_x64.lib")
		#else
			#pragma comment(lib, "lib/Apocalypse_x64_d.lib")
		#endif
	#endif
#endif

// ----------------------------------------------------
//	���O��Ԃ��g�p����
// ----------------------------------------------------
//	NOTUSING_NAMESPACE����`����Ă���ꍇ�����using���܂���
#ifndef NOTUSING_NAMESPACE
	using namespace Apocalypse;
	using namespace Apocalypse::Base;
	using namespace Apocalypse::System;
	using namespace Apocalypse::Sequence;
	using namespace Apocalypse::Draw;
	using namespace Apocalypse::Event;
	using namespace Apocalypse::Collection;
	using namespace Apocalypse::Input;
	//using namespace Apocalypse::Expression;
	//using namespace Apocalypse::Sound;
	//using namespace Apocalypse::UI;
#endif
