#include "Planet.h"
#include "../Math/MathUtil.h"
#include "../Model.h"
#include <DxLib.h>

namespace
{
	// 1�t���[���ɉ�]����ʂ̍ő�l
	constexpr float max_rot = 0.01f;

	// 1�t���[���ɉ�]����ʂ̍ŏ��l
	constexpr float min_rot = 0.0f;
}

// �R���X�g���N�^
Planet::Planet(int modelHandle, UnityGameObject data) :
	m_pos(data.pos),
	m_rot(data.rot),
	m_scale(data.scale)
{
	// ���f���̃C���X�^���X�̍쐬
	m_pModel = std::make_unique<Model>(modelHandle);

	// 1�t���[���ɉ�]����ʂ�0�x����`0.1�x�̊Ԃ���擾
	m_rotVec.x = MathUtil::ToRadian(GetRand(10) * (max_rot * 0.1f) + min_rot);
	m_rotVec.y = MathUtil::ToRadian(GetRand(10) * (max_rot * 0.1f) + min_rot);
	m_rotVec.z = MathUtil::ToRadian(GetRand(10) * (max_rot * 0.1f) + min_rot);

	// ���f���̐ݒ�
	m_pModel->SetPos(m_pos);			// �ʒu
	m_pModel->SetRot(m_rot);			// ��]
	m_pModel->SetScale(m_scale);		// �g�嗦
	m_pModel->Update();					// �X�V
}

// �f�X�g���N�^
Planet::~Planet()
{
}

// �X�^�[�g���̍X�V
void Planet::UpdateStart(Vector3 playerVec)
{
	// �v���C���[�Ɠ����x�N�g���ړ�
	m_pos += playerVec;

	// ��]
	m_rot += m_rotVec;

	// ���f���̐ݒ�
	m_pModel->SetPos(m_pos);	// �ʒu
	m_pModel->SetRot(m_rot);	// ��]
	m_pModel->Update();			// �X�V
}

// �X�V
void Planet::Update()
{
	// ��]
	m_rot += m_rotVec;

	// ���f���̐ݒ�
	m_pModel->SetRot(m_rot);	// ��]
	m_pModel->Update();			// �X�V
}

// �`��
void Planet::Draw()
{
	m_pModel->Draw();
}

// �Q�b�^�[
Vector3 Planet::GetPos() const
{
	return m_pos;
}