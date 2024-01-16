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
	// ���X�g������ۂ������牽�����Ȃ�
	if (!m_scenes.empty())
	{
		// �擪�̂ݎ��s
		m_scenes.front()->Update();
	}
}

// �`��
void SceneManager::Draw()
{
	// �t���ɕ`��(�Ō�ɐς񂾂��̂��ŏ��ɕ`�悳���)
	for (auto rit = m_scenes.rbegin(); rit != m_scenes.rend(); rit++)
	{
		rit->get()->Draw();
	}
}

// �V�[���̐؂�ւ�
void SceneManager::ChangeScene(std::shared_ptr<SceneBase> nextScene)
{
	// ���X�g������ۂ����������ւ���̂ł͂Ȃ�
	if (m_scenes.empty())
	{
		// �擪�ɒǉ�����
		m_scenes.push_front(nextScene);
	}
	else 
	{
		// ���ɂP�ȏ゠������擪�̂��̂����ւ���
		m_scenes.front() = nextScene;
	}
}

// ���݂̃V�[���̏�ɃV�[����ς�(�|�[�Y)
void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
{
	m_scenes.push_front(scene);
}

// ��ԏ�̃V�[�����폜
void SceneManager::PopScene()
{
	m_scenes.pop_front();
}