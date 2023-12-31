#include "GameScene.h"
#include "../Editor/DataReaderFromUnity.h"
#include "DxLib.h"

// �R���X�g���N�^
GameScene::GameScene(SceneManager& manager, std::string fileName) :
	SceneBase(manager)
{
	// �I�u�W�F�N�g�z�u�f�[�^�ǂݍ���
	auto dataReader = std::make_unique<DataReaderFromUnity>();
	dataReader->LoadUnityGameObjectData(fileName);
}

// �f�X�g���N�^
GameScene::~GameScene()
{
}

// �X�V
void GameScene::Update()
{
}

// �`��
void GameScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// �e�X�g�`��
	DrawString(0, 0, "test", 0xffffff);
}
