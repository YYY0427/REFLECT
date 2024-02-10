#include "TutorialUI.h"
#include "../Util/DrawFunctions.h"
#include "../Application.h"
#include "../String/MessageManager.h"
#include "../Util/Easing.h"
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

	// �`���[�g���A���p��UI���E���Ɏc���̂��ǂ����̃t���O
	// �܂��������̂���false
	constexpr bool is_tutorial_ui_hold_test = false;
}

// �R���X�g���N�^
TutorialUI::TutorialUI() :
	m_state(TutorialState::MOVE)
{
	// ������
	m_changeImageFrame = 120;

	// ��ʃT�C�Y�̎擾
	auto& screenSize = Application::GetInstance().GetWindowSize();

	// �f�[�^�̐ݒ�
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
			// �`���[�g���A���p��UI���E���Ɏc���̂��ǂ����̃t���O�������Ă���ꍇ
			if (is_tutorial_ui_hold_test)
			{
				// �g�嗦������
				data.second.scale -= 0.01f;
				data.second.scale = (std::max)(data.second.scale, 0.6f);

				// �ړI�n�̐ݒ�
				auto& screenSize = Application::GetInstance().GetWindowSize();
				Vector2 goalPos = { static_cast<float>(screenSize.width) - 200.0f, 
									static_cast<float>(screenSize.height - 30.0f) };

				// �I�����Ă����Ԃ̐����J�E���g
				int count = 0;
				for (auto& data : m_tutorialDataMap)
				{
					if (data.second.isEnd)
					{
						count++;
					}
				}
				// �J�E���g�̐��ɂ���ĖړI�n��ύX
				goalPos.y -= 30.0f * count;

				// �ړI�n�փC�[�W���O���g�p���Ĉړ�
				data.second.easing++;
				data.second.imgPos.x = Easing::EaseOutCubic(data.second.easing, 300, goalPos.x, data.second.imgPos.x);
				data.second.imgPos.y = Easing::EaseOutCubic(data.second.easing, 300, goalPos.y, data.second.imgPos.y);
			}
			else
			{
				// �����x������
				data.second.imgAlpha -= alpha_speed;

				// ���X�ɏ�Ɉړ�
				data.second.imgPos.y -= 1.0f;
			}
		}
		// ��Ԃ��J�n���Ă���ꍇ
		else if (data.first == m_state && data.second.isStart)
		{
			// �����x�𑝉�
			data.second.imgAlpha += alpha_speed;
			data.second.imgAlpha = (std::min)(data.second.imgAlpha, 255);

			// ���X�ɏ�Ɉړ�
			data.second.imgPos.y -= 1.0f;
			data.second.imgPos.y = (std::max)(data.second.imgPos.y, data.second.imgGoalPos.y);

			// ����̃t���[�����Ƃɉ摜��؂�ւ�
			m_changeImageFrame.Update(1);
			if (m_changeImageFrame.IsTimeOut())
			{
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
	// �`���[�g���A���p��UI���E���Ɏc���̂��ǂ����̃t���O�������Ă���ꍇ
	if (is_tutorial_ui_hold_test)
	{
		for (auto& data : m_tutorialDataMap)
		{
			// ��Ԃ��X�^�[�g���Ă��Ȃ��ꍇ�͕`�悵�Ȃ�	
			if (!data.second.isStart) return;

			// ��������
			SetDrawScreen(data.second.messageTextImgHandle);
			ClearDrawScreen();
			auto& screenSize = Application::GetInstance().GetWindowSize();
			MessageManager::GetInstance().DrawStringCenter(data.second.messageId,
				screenSize.width / 2.0f, screenSize.height / 2.0f, 0xffffff);
			SetDrawScreen(DX_SCREEN_BACK);

			// �����x�̐ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, data.second.imgAlpha);

			// ���b�Z�[�W�摜�̕`��
			DrawRotaGraph(data.second.imgPos.x + 130.0f, data.second.imgPos.y,
				data.second.scale, 0.0f, data.second.messageTextImgHandle, true);

			// �摜�̕`��
			DrawRotaGraph(data.second.imgPos.x, data.second.imgPos.y,
				data.second.scale, 0.0,
				data.second.imgHandle[data.second.imgIndex], TRUE);

			// �����x�����ɖ߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else
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
}

// ��Ԃ̐ݒ�
void TutorialUI::StartState(TutorialState state)
{
	// ��Ԃ̐ݒ�
	m_state = state;
	m_tutorialDataMap[m_state].isStart = true;
	m_tutorialDataMap[m_state].isEnd = false;

	// �ʒu�̐ݒ�
	m_tutorialDataMap[m_state].imgPos = 
		{ m_tutorialDataMap[m_state].imgGoalPos.x, m_tutorialDataMap[m_state].imgGoalPos.y + 20.0f };

	// �`���[�g���A���p��UI���E���Ɏc���̂��ǂ����̃t���O�������Ă���ꍇ
	if (is_tutorial_ui_hold_test)
	{
		// ���b�Z�[�W�摜�p�̃X�N���[���̍쐬
		MessageManager& message = MessageManager::GetInstance();
		m_tutorialDataMap[m_state].messageTextImgHandle =
			MakeScreen(message.GetMessageWidth(m_tutorialDataMap[m_state].messageId),
				message.GetMessageHeight(m_tutorialDataMap[m_state].messageId));
	}
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