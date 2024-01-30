#include "Triangle.h"
#include "../Math/MathUtil.h"
#include "../Application.h"
#include <cmath>
#include <DxLib.h>

namespace
{
	// �O�p�`�̐�
	constexpr int triangle_num = 4;

	// �O�p�`�̏����p�x
	constexpr float triangle_init_angle = 135.0f;

	// �O�p�`�̂Ȃ��p
	constexpr float triangle_angle = 10.0f;

	// �O�p�`�̐F��ω������鑬�x
	constexpr float color_speed = 2.0f;

	// �O�p�`�̍ŏI�I�ȐF
	const Vector3 end_triangle_color = { 255, 0, 0 };

	// �O�p�`�̐F��ω������鎞��(1.0 = m_frame)
	constexpr float change_color_time = 0.5f;
}

// �R���X�g���N�^
Triangle::Triangle(int frame) :
	m_frame(frame),
	m_intervalFrame(frame / (triangle_num + 1)),
	m_angle(triangle_init_angle),
	m_color(255, 255, 255)
{
}

// �f�X�g���N�^
Triangle::~Triangle()
{
}

// �X�V
void Triangle::Update(Vector3 bossEnemyPos)
{
	// �^�C�}�[�̍X�V
	m_frame.Update(1);
	m_intervalFrame.Update(1);

	// �O�p�`��`�悷��Ԋu�̃t���[���o�߂���
	// �O�p�`�̐����w�萔�ɒB���Ă��Ȃ��ꍇ�͒ǉ�
	if (m_intervalFrame.IsTimeOut() && m_triangleDataTable.size() < triangle_num)
	{
		// �^�C�}�[�̃��Z�b�g
		m_intervalFrame.Reset();

		// �O�p�`�̃f�[�^��ǉ�
		TriangleData triangleData;

		// �O�p�`�̈ʒu��ݒ�
		auto& screenSize = Application::GetInstance().GetWindowSize();
		Vector3 screenPos = Vector3::FromDxLibVector3(ConvWorldPosToScreenPos(bossEnemyPos.ToDxLibVector3()));
		triangleData.pos[0] = Vector2(screenPos.x, screenPos.y);

		triangleData.pos[1] = Vector2((0.5f * cosf(m_angle) + 0.5f) * screenSize.width, (0.5f * sinf(m_angle) + 0.5f) * screenSize.width);
		triangleData.pos[2] = Vector2((0.5f * cosf(m_angle + triangle_angle) + 0.5f) * screenSize.width, (0.5f * sinf(m_angle + triangle_angle) + 0.5f) * screenSize.width);
		/*triangleData.pos[1] = 
			Vector2(cosf(MathUtil::ToRadian(m_angle)) * screenSize.width,
			sinf(MathUtil::ToRadian(m_angle)) * screenSize.height);

		triangleData.pos[2] =
			Vector2(cosf(MathUtil::ToRadian(m_angle + triangle_angle)) * screenSize.width,
					sinf(MathUtil::ToRadian(m_angle + triangle_angle)) * screenSize.height);*/

		// �p�x�����Z
		m_angle += 90.0f;

		// �A���t�@�l��ݒ�
		triangleData.alpha = 255;

		// �O�p�`�̃f�[�^��ǉ�
		m_triangleDataTable.push_back(triangleData);
	}

	// �O�p�`�̃f�[�^���X�V
	for (auto& triangle : m_triangleDataTable)
	{
		// �`�J�`�J������
		triangle.alpha *= -1;

		// �O�p�`�̈ʒu��ݒ�
		Vector3 screenPos = Vector3::FromDxLibVector3(ConvWorldPosToScreenPos(bossEnemyPos.ToDxLibVector3()));
		triangle.pos[0] = Vector2(screenPos.x, screenPos.y);
	}

	// ����̎��ԂɂȂ�����O�p�`�̐F��ω�������
	if (m_frame.GetTime() >= m_frame.GetLimitTime() * change_color_time)
	{
		// �O�p�`�̐F��ω�������
		m_color -= color_speed;

		// �O�p�`�̐F�͍ŏI�I�ȐF�Ŏ~�߂�
		m_color.x = (std::max)(m_color.x, end_triangle_color.x);
		m_color.y = (std::max)(m_color.y, end_triangle_color.y);
		m_color.z = (std::max)(m_color.z, end_triangle_color.z);
	}
}

// �`��
void Triangle::Draw()
{
	// ���o���I����Ă�����`�悵�Ȃ�
	if (IsEnd()) return;

	for (auto& triangle : m_triangleDataTable)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, triangle.alpha);
		DrawTriangle(triangle.pos[0].x, triangle.pos[0].y, triangle.pos[1].x, triangle.pos[1].y, triangle.pos[2].x, triangle.pos[2].y, 
			GetColor(m_color.x, m_color.y, m_color.z), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// �I��������
bool Triangle::IsEnd() const
{
	return m_frame.IsTimeOut();
}
