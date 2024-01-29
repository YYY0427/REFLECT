#include "Application.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Effect/Effekseer3DEffectManager.h"
#include "SaveData.h"
#include "Scene/SceneManager.h"
#include "Scene/DebugScene.h"
#include "Scene/TitleScene.h"
#include "SoundManager.h"
#include "StringManager.h"
#include "Util/InputState.h"
#include "MyDebug/DebugText.h"
#include <string>
#include <memory>

namespace
{
    // ��ʃT�C�Y
    constexpr int window_width = 1280;	
    constexpr int window_height = 720;	
	/*constexpr int window_width = 1600;
	constexpr int window_height = 900;*/

    // �E�B���h�E�^�C�g��
    const std::string window_title = "REFLECT";

	// �J���[�r�b�g��
	constexpr int color_depth = 32;

	// ���̂P���[�g���ɑ�������l
	constexpr int one_meter = 100;

	// fps
	constexpr int fps = 60;
}

// �R���X�g���N�^
Application::Application() :
	m_screenSize{ window_width, window_height },
	m_isExit(false)
{
}

// Application�N���X�̃C���X�^���X���擾
Application& Application::GetInstance()
{
	// �������g�̐ÓI�I�u�W�F�N�g���쐬
	static Application instance;

	// �쐬�����I�u�W�F�N�g�̎Q�Ƃ�Ԃ�
	return instance;
}

// ������
bool Application::Init()
{
	// �Z�[�u�f�[�^�̓ǂݍ���
	auto& saveData = SaveData::GetInstance();
	saveData.Load();

	// Window���[�h�ݒ�
	ChangeWindowMode(saveData.GetSaveData().windowMode);

	// Window���ݒ�
	SetMainWindowText(window_title.c_str());

	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(window_width, window_height, color_depth);

	// �Q�[�����ɃE�B���h�E���[�h��؂�ւ��Ă��O���t�B�b�N�n���h�������Z�b�g���Ȃ�
	SetChangeScreenModeGraphicsSystemResetFlag(TRUE);

	// �ق��̃E�B���h�E��I�����Ă��Ă������悤�ɂ���
	SetAlwaysRunFlag(TRUE);

	// �E�B���h�E�̃T�C�Y��ύX�\�ɂ���
	SetWindowSizeChangeEnableFlag(TRUE);

	// DirectX11���g�p
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �P���[�g���ɑ�������l��ݒ肷��
	Set3DSoundOneMetre(one_meter);

	// XAudio��L����
	SetEnableXAudioFlag(TRUE);

	// ����������L����
	SetWaitVSyncFlag(TRUE);

	// 3D�ł̕`�揈���̃T�|�[�g
	SetUseLarge3DPositionSupport(TRUE);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// �񓯊��ǂݍ��ݐݒ�ɕύX
//	SetUseASyncLoadFlag(TRUE);

	// csv�t�@�C���ɉ����ăT�E���h�����[�h
	auto& soundManager = SoundManager::GetInstance();
	soundManager.LoadAndStoreSoundFileData();

	// csv�t�@�C���ɉ����ĕ���������[�h
	auto& stringManager = StringManager::GetInstance();
	stringManager.LoadAndStoreStringFileData();

	// Effekseer�̏�����
	auto& effectManager = Effekseer3DEffectManager::GetInstance();
	effectManager.Init();

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ�
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Z�o�b�t�@��L����
	SetUseZBufferFlag(TRUE);

	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(TRUE);

	// �|���S���̗��ʂ�`�悵�Ȃ�
	SetUseBackCulling(TRUE);

	// ���̓^�C�v�̏�����
	InputState::Init();

	// �f�o�b�O�e�L�X�g�̏�����
	DebugText::Init();

	// �_�u���o�b�t�@���[�h
	// ����ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

// �Q�[�����[�v
void Application::Run()
{
	// �ŏ��̃V�[����ݒ�
	SceneManager sceneManager;
#ifdef _DEBUG
	sceneManager.ChangeScene(std::make_shared<DebugScene>(sceneManager));
#else
	sceneManager.ChangeScene(std::make_shared<TitleScene>(sceneManager));
#endif

	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// Window���[�h�ݒ�
		auto& saveData = SaveData::GetInstance();
		ChangeWindowMode(saveData.GetSaveData().windowMode);

		// �f�o�b�O�e�L�X�g�̃N���A
		DebugText::Clear();

		// ���͂̍X�V
		InputState::Update();

		// �V�[���̍X�V
		sceneManager.Update();

		// �V�[���̕`��
		sceneManager.Draw();

		// ��ʂ̍X�V
		ScreenFlip();

#ifdef _DEBUG
		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
#endif

		// �Q�[���I���t���O�������Ă�����I��
		if(m_isExit) break;

		// fps���Œ�
		while (GetNowHiPerformanceCount() - time < (static_cast<long long>((1000 / fps)) * 1000))
		{

		}
	}
	// �I������
	End();
}

// �I������
void Application::End()
{
	// �T�E���h�����ׂĎ~�߂�
	auto& soundManager = SoundManager::GetInstance();
	soundManager.StopAllSound();

	// Effekseer�̏I������
	auto& effectManager = Effekseer3DEffectManager::GetInstance();
	effectManager.End();

	// StringManager�̏I������
	auto& stringManager = StringManager::GetInstance();
	stringManager.End();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();
}

// �E�B���h�E�T�C�Y�̎擾
const Size& Application::GetWindowSize() const
{
	return m_screenSize;
}

// fps���擾
int Application::GetFps() const
{
	return fps;
}

// �I��
void Application::Exit()
{
	m_isExit = true;
}