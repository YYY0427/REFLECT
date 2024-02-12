#include "TestScene.h"
#include "../Application.h"
#include "../Transitor/TileTransitor.h"
#include "../Transitor/FadeTransitor.h"
#include "../Transitor/IrisTransitor.h"
#include "../Transitor/WipeTransitor.h"
#include "../Transitor/PushTransitor.h"
#include "../Transitor/StripTransitor.h"
#include "../UI/Warning.h"
#include "../Util/FileUtil.h"
#include "../UI/ResultWindow.h"
#include "DxLib.h"

namespace
{
	const std::string file_extension = ".bmp";
}

// �R���X�g���N�^
TestScene::TestScene(SceneManager& manager) :
	SceneBase(manager)
{
	// ��ʐ؂�ւ����o�̐ݒ�
	m_pTransitor = std::make_unique<StripTransitor>();
	m_pTransitor->Start();

	m_pResultWindow = std::make_unique<ResultWindow>();

	// �x��UI�̐ݒ�
//	m_pWarning = std::make_unique<Warning>(200);

	// �t�@�C�����̈ꊇ�ǂݍ���
//	m_fileNames = FileUtil::LoadFileNames("Data/Test", file_extension);
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

	m_pResultWindow->Update();

	// �x��UI�̍X�V
//	m_pWarning->Update();
}

// �`��
void TestScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// �w�i�̕`��
	const auto& size = Application::GetInstance().GetWindowSize();
	DrawBox(0, 0, size.width, size.height, 0x000000, true);

	m_pResultWindow->Draw();

	// �x��UI�̕`��
//	m_pWarning->Draw();

	//int i = 0;
	//for (int i = 0; i < m_fileNames.size(); i++)
	//{
	//	// �g���q���폜
	//	m_fileNames[i] = m_fileNames[i].substr(0, m_fileNames[i].size() - file_extension.size());

	//	// �t�@�C�����̕`��
	//	DrawString(0, 50 + (i * 20), m_fileNames[i].c_str(), 0xffffff);
	//}

	// ��ʐ؂�ւ����o�̕`��
	m_pTransitor->Draw();
}
