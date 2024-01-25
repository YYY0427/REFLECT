#pragma once
#include "../Math/Vector2.h"

/// <summary>
/// ��ʂ��t���b�V������N���X
/// </summary>
class Flash
{
public:
	// �R���X�g���N�^
	Flash(int enableFrame);

	// �f�X�g���N�^
	~Flash();

	// �X�V
	void Update(unsigned int color);

	// �`��
	void Draw();

	// �I���������ǂ���
	bool IsEnd() const;

private:
	// �ʒu
	Vector2 m_pos;

	// �J���[
	unsigned int m_color;

	// �A���t�@�l
	int m_alpha;

	// ���a
	float m_radius;

	// ������܂ł̃t���[����
	int m_enableFrame;
};