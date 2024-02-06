#pragma once
#include "SceneBase.h"
#include "../Math/Vector2.h"
#include <string>

/// <summary>
/// ���U���g���
/// </summary>
class ResultScene : public SceneBase
{
public:
	// �R���X�g���N�^
	ResultScene(SceneManager& manager, std::string stageName);

	// �f�X�g���N�^
	~ResultScene();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// �E�B���h�E�̈ʒu
	Vector2 m_windowPos;

	// �X�e�[�W��
	std::string m_stageName;
};