#include "TutorialUI.h"
#include "../Util/DrawFunctions.h"
#include "../Application.h"
#include "../String/MessageManager.h"
#include <DxLib.h>

namespace
{
	// �摜�t�@�C���p�X
	const std::string xbox_stick_l_up = "Data/Image/xbox_stick_l_up.png";
	const std::string xbox_stick_l_down = "Data/Image/xbox_stick_l_down.png";
	const std::string xbox_stick_l_left = "Data/Image/xbox_stick_l_left.png";
	const std::string xbox_stick_l_right = "Data/Image/xbox_stick_l_right.png";

	// �A���t�@�l�̑������x
	constexpr int alpha_speed = 5;
}

// �R���X�g���N�^
TutorialUI::TutorialUI() :
	m_state(TutorialState::MOVE)
{
	// ������
	m_changeImageFrame = 120;

	// ��ʃT�C�Y�̎擾
	auto& screenSize = Application::GetInstance().GetWindowSize();

	// �摜�̃��[�h
	m_tutorialDataMap[TutorialState::MOVE].imgHandle.push_back(my::MyLoadGraph(xbox_stick_l_up.c_str()));
	m_tutorialDataMap[TutorialState::MOVE].imgHandle.push_back(my::MyLoadGraph(xbox_stick_l_down.c_str()));
	m_tutorialDataMap[TutorialState::MOVE].imgHandle.push_back(my::MyLoadGraph(xbox_stick_l_left.c_str()));
	m_tutorialDataMap[TutorialState::MOVE].imgHandle.push_back(my::MyLoadGraph(xbox_stick_l_right.c_str()));
	m_tutorialDataMap[TutorialState::MOVE].imgGoalPos = { screenSize.width / 2 + 150.0f, screenSize.height - 150.0f };
	m_tutorialDataMap[TutorialState::MOVE].messageId = "TutorialMove";
}

// �f�X�g���N�^
TutorialUI::~TutorialUI()
{
	// �摜�̉��
	for (auto& img : m_tutorialDataMap)
	{
		for (auto& img : img.second.imgHandle)
		{
			DeleteGraph(img);
		}
	}
}

// �X�V
void TutorialUI::Update()
{
	for (auto& data : m_tutorialDataMap)
	{
		// ��Ԃ��I�����Ă���ꍇ
		if (data.second.isEnd)
		{
			// �����x������
			data.second.imgAlpha -= alpha_speed;

			// ���X�ɏ�Ɉړ�
			data.second.imgPos.y -= 1.0f;
		}
		// ��Ԃ��J�n���Ă���ꍇ
		else if (data.first == m_state && data.second.isStart)
		{
			// �����x�𑝉�
			data.second.imgAlpha += alpha_speed;
			data.second.imgAlpha = (std::min)(data.second.imgAlpha, 255);
			/*data.second.textAlpha += alpha_speed;
			data.second.textAlpha = (std::min)(data.second.textAlpha, 255);*/

			// ���X�ɏ�Ɉړ�
			data.second.imgPos.y -= 1.0f;
			data.second.imgPos.y = (std::max)(data.second.imgPos.y, data.second.imgGoalPos.y);

			// ����̃t���[�����Ƃɉ摜��؂�ւ�
			m_changeImageFrame.Update(1);
			if (m_changeImageFrame.IsTimeOut())
			{
				// �摜��2���ȉ��̏ꍇ�͓����x��0�ɂ���
				if (data.second.imgHandle.size() >= 2)
				{
				//	data.second.imgAlpha = 0;
				}
				// ������
				m_changeImageFrame.Reset();

				// �摜�̐؂�ւ�
				data.second.imgIndex = (data.second.imgIndex + 1) % data.second.imgHandle.size();
			}
		}
	}
}

// �`��
void TutorialUI::Draw()
{
	// �����x�̐ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_tutorialDataMap[m_state].imgAlpha);

	// �摜�̕`��
	DrawRotaGraph(m_tutorialDataMap[m_state].imgPos.x, m_tutorialDataMap[m_state].imgPos.y, 
				  1.0, 0.0,	
				  m_tutorialDataMap[m_state].imgHandle[m_tutorialDataMap[m_state].imgIndex], TRUE);

	// �e�L�X�g�̕`��
	MessageManager::GetInstance().DrawStringCenter(m_tutorialDataMap[m_state].messageId, 
				  m_tutorialDataMap[m_state].imgPos.x + 130.0f, m_tutorialDataMap[m_state].imgPos.y, 0xffffff);
	
	// �����x�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// ��Ԃ̐ݒ�
void TutorialUI::StartState(TutorialState state)
{
	m_state = state;
	m_tutorialDataMap[m_state].isStart = true;
	m_tutorialDataMap[m_state].isEnd = false;
	m_tutorialDataMap[m_state].imgPos = 
		{ m_tutorialDataMap[m_state].imgGoalPos.x, m_tutorialDataMap[m_state].imgGoalPos.y + 20.0f };
}

// ���݂̏�Ԃ��I��
void TutorialUI::EndState()
{
	m_tutorialDataMap[m_state].isEnd = true;
}

// ��Ԃ̎擾
TutorialState TutorialUI::GetState() const
{
	return m_state;
}

// ��Ԃ��I�����Ă��邩
bool TutorialUI::IsEndState(TutorialState state)
{
	return m_tutorialDataMap[state].isEnd;
}