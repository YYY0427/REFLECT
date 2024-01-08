#include "TestScene.h"
#include "../Application.h"
#include "../Transitor/TileTransitor.h"
#include "../Transitor/FadeTransitor.h"
#include "../Transitor/IrisTransitor.h"
#include "../Transitor/WipeTransitor.h"
#include "../Transitor/PushTransitor.h"
#include "../Transitor/StripTransitor.h"
#include "DxLib.h"

// �R���X�g���N�^
TestScene::TestScene(SceneManager& manager) :
	SceneBase(manager)
{
	// ��ʐ؂�ւ����o�̐ݒ�
	m_pTransitor = std::make_unique<StripTransitor>();
	m_pTransitor->Start();
}

// �f�X�g���N�^
TestScene::~TestScene()
{
}

// �X�V
void TestScene::Update()
{
	// ��ʐ؂�ւ����o�̍X�V
	m_pTransitor->Update();
}

// �`��
void TestScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// �w�i�̕`��
	const auto& size = Application::GetInstance().GetWindowSize();
	DrawBox(0, 0, size.width, size.height, 0xffffff, true);

	// ��ʐ؂�ւ����o�̕`��
	m_pTransitor->Draw();
}
