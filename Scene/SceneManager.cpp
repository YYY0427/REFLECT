#include "SceneManager.h"
#include "SceneBase.h"

// �R���X�g���N�^
SceneManager::SceneManager()
{
}

// �f�X�g���N�^
SceneManager::~SceneManager()
{
}

// �X�V
void SceneManager::Update()
{
	//�����̂ݎ��s
	m_scenes.back()->Update();
}

// �`��
void SceneManager::Draw()
{
	//�擪���珇�ɕ`��(�Ō�ɐς񂾂��̂��Ō�ɕ`�悳���)
	for (auto& scene : m_scenes) 
	{
		scene->Draw();
	}
}

// �V�[���̐؂�ւ�
void SceneManager::ChangeScene(std::shared_ptr<SceneBase> nextScene)
{
	//���X�g������ۂ����������ւ���̂ł͂Ȃ�
	if (m_scenes.empty())
	{
		//�����ɒǉ�����
		m_scenes.push_back(nextScene);
	}
	else 
	{
		//���ɂP�ȏ゠�����疖���̂��̂����ւ���
		m_scenes.back() = nextScene;
	}
}

// ���݂̃V�[���̏�ɃV�[����ς�(�|�[�Y)
void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
{
	m_scenes.push_back(scene);
}

// ��ԏ�̃V�[�����폜
void SceneManager::PopScene()
{
	m_scenes.pop_back();
}