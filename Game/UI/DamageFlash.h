#pragma once
#include "UIBase.h"

/// <summary>
/// �_���[�W���󂯂��Ƃ��̃t���b�V��
/// </summary>
class DamageFlash : public UIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DamageFlash();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DamageFlash();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override final;

	/// <summary>
	/// ���o�J�n
	/// </summary>
	/// <param name="frame">�t���b�V���̃t���[����</param>
	/// <param name="alpha">�t���b�V���̓����x</param>
	/// <param name="color">�t���b�V���̐F</param>
	void Start(const int frame, const int alpha, const unsigned int color);

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

