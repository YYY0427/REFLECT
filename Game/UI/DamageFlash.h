#pragma once
#include "UIBase.h"

/// <summary>
/// �_���[�W���󂯂��Ƃ��̃t���b�V��
/// </summary>
class DamageFlash : public UIBase
{
public:
	// �R���X�g���N�^
	DamageFlash();

	// �f�X�g���N�^
	~DamageFlash();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

	// ���o�J�n
	void Start(int frame, int alpha, unsigned int color);

private:
	// �t���[����
	int m_frame;

	// �A���t�@�l
	int m_alpha;

	// �F
	unsigned int m_color;

	// �����x�̕ω���
	float m_speed;
};

