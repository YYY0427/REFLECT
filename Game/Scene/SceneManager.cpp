#include "SceneManager.h"
#include "SceneBase.h"
#include "../Application.h"

// �R���X�g���N�^
SceneManager::SceneManager() :
	m_updateTime(0),
	m_drawTime(0)
{
}

// �f�X�g���N�^
SceneManager::~SceneManager()
{
}

// �X�V
void SceneManager::Update()
{
	// �~���b�P�ʂ̐��x�����J�E���^�̌��݂̒l�𓾂�
	LONGLONG start = GetNowHiPerformanceCount();

	// ���X�g������ۂ������牽�����Ȃ�
	if (!m_scenes.empty())
	{
		// �擪�̂ݎ��s
		m_scenes.front()->Update();
	}

	// �X�V���Ԃ��v��
	m_updateTime = GetNowHiPerformanceCount() - start;
}

// �`��
void SceneManager::Draw()
{
	// �~���b�P�ʂ̐��x�����J�E���^�̌��݂̒l�𓾂�
	LONGLONG start = GetNowHiPerformanceCount();

	// �t���ɕ`��(�Ō�ɐς񂾂��̂��ŏ��ɕ`�悳���)
	for (auto rit = m_scenes.rbegin(); rit != m_scenes.rend(); rit++)
	{
		// �`��
		rit->get()->Draw();
	}

	// �`�掞�Ԃ��v��
	m_drawTime = GetNowHiPerformanceCount() - start;

	// fps�̎擾
	float fps = GetFPS();

	// ��ʃT�C�Y�̎擾
	Size size = Application::GetInstance().GetWindowSize();

#ifdef _DEBUG
	// 1�t���[���ɂ��������`�掞�Ԃ�\��
	float rate = static_cast<float>(m_updateTime + m_drawTime) / static_cast<long long>(1000000 / fps);
	int width = static_cast<int>(size.width * rate);
	DrawBox(16, size.height - 40, 32, size.height - 24, 0xff0000, true);
	DrawString(40, size.height - 40, "DrawTime", 0xffffff);
	DrawBox(0, size.height - 16, width, size.height, 0xff0000, true);

	// 1�t���[���ɂ��������X�V���Ԃ�\��
	rate = static_cast<float>(m_updateTime) / static_cast<long long>(1000000 / fps);
	width = static_cast<int>(size.width * rate);
	DrawBox(150, size.height - 40, 166, size.height - 24, 0x0000ff, true);
	DrawString(174, size.height - 40, "UpdateTime", 0xffffff);
	DrawBox(0, size.height - 16, width, size.height, 0x0000ff, true);

	// fps��`��
	DrawFormatString(300, size.height - 40, 0xffffff, "FPS : %f", fps);
#endif
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

// 
void SceneManager::ChangeAndClearScene(std::shared_ptr<SceneBase> nextScene)
{
	// �V�[���̑S�폜
	ClearScene();

	// �V�[���̐؂�ւ�
	ChangeScene(nextScene);
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

// �V�[���̑S�폜
void SceneManager::ClearScene()
{
	m_scenes.clear();
}