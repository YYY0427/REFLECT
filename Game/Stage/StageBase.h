#pragma once

/// <summary>
/// �X�e�[�W���N���X
/// </summary>
class StageBase
{
public:
	// �R���X�g���N�^
	StageBase();

	// �f�X�g���N�^
	virtual ~StageBase();

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

protected:
};