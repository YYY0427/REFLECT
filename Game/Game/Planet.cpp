#include "Planet.h"
#include "../Math/MathUtil.h"
#include "../Model.h"
#include <DxLib.h>

// �R���X�g���N�^
Planet::Planet(int modelHandle, UnityGameObject data) :
	m_pos(data.pos),
	m_rot(data.rot),
	m_scale(data.scale)
{
	// ���f���̃C���X�^���X�̍쐬
	m_pModel = std::make_unique<Model>(modelHandle);

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
void Planet::UpdateStart(Vector3 playerVec, Vector3 rotVec)
{
	// �v���C���[�Ɠ����x�N�g���ړ�
	m_pos += playerVec;

	// ��]
	m_rot += rotVec;

	// ���f���̐ݒ�
	m_pModel->SetPos(m_pos);	// �ʒu
	m_pModel->SetRot(m_rot);	// ��]
	m_pModel->Update();			// �X�V
}

// �X�V
void Planet::Update(Vector3 rotVec)
{
	// ��]
	m_rot += rotVec;

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