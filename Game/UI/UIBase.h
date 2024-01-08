#pragma once
#include "../Math/Vector2.h"

/// <summary>
/// UI�̊��N���X
/// </summary>
class UIBase
{
public:
	// �R���X�g���N�^
	UIBase();

	// �f�X�g���N�^
	virtual ~UIBase();

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

	// UI�̊i�[
	void Store(Vector2 vec);

	// UI���L�����ǂ���
	bool IsEnabled() const;

protected:
	// UI�̍��W
	Vector2 m_pos;

	// UI���L�����ǂ���
	bool m_isEnabled;
};