#pragma once
#include "../Math/Vector2.h"
#include "../Util/Timer.h"
#include <map>
#include <string>
#include <vector>

// �`���[�g���A���̏��
enum class TutorialState
{
	MOVE,		// �ړ�
	SHIELD,		// �V�[���h
	REFLECT,	// ����
	REFLECT2,	// ����2
	CUBE,		// �L���[�u
	CUBE2,		// �L���[�u2
	PLAY,		// �v���C
	DAMAGE,		// �_���[�W
};

/// <summary>
/// �`���[�g���A��UI
/// </summary>
class TutorialUI
{
public:
	// �R���X�g���N�^
	TutorialUI();

	// �f�X�g���N�^
	~TutorialUI();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// ��Ԃ̐ݒ�
	void StartState(TutorialState state);

	// ���݂̏�Ԃ��I��
	void EndState();

	// ��Ԃ̎擾
	TutorialState GetState() const;
	bool IsEndState(TutorialState state);

private:
	// �`���[�g���A���̃f�[�^
	struct TutorialData
	{
		// �X�^�[�g������
		bool isStart = false;

		// �I��������
		bool isEnd = false;

		// �摜�n���h��
		std::vector<std::vector<int>> imgHandle;
		std::vector<int> imgIndex;
		int messageTextImgHandle;

		// �ʒu
		Vector2 imgPos;
		Vector2 goalPos;

		// ���b�Z�[�WID
		std::string messageId;

		// �A���t�@�l
		int imgAlpha = 0;

		// �g�嗦
		float scale = 1.0f;

		// �C�[�W���O
		float easing = 0.0f;

		// �`��t���[��
		int drawFrame = 0;
	};

private:
	// �`���[�g���A���̏��
	TutorialState m_state;

	// �`���[�g���A���̉摜
	std::map<TutorialState, TutorialData> m_tutorialDataMap;

	// �摜��؂�ւ���t���[����
	Timer<int> m_changeImageFrame;
};