#include "Meteor.h"
#include "../Model.h"
#include "../Application.h"
#include "../Math/Vector2.h"
#include "../Math/MathUtil.h"
#include <DxLib.h>

namespace
{
	// ���f���̊g�嗦
	constexpr int meteor_max_scale = 500;	// �ő�g�嗦
	constexpr int meteor_min_scale = 100;	// �ŏ��g�嗦

	// �ړ����x
	constexpr float meteor_move_speed = 100.0f;
}

// �R���X�g���N�^
// �����_���ɐ����A�v���C���[�̕����Ɉړ�
Meteor::Meteor(int modelHandle, Vector3 playerPos) :
	m_rot({ 0, 0, 0 }),
	m_slowValue(1.0f),
	m_isEnabled(true)
{
	// ���f���̃C���X�^���X�̍쐬
	m_pModel = std::make_unique<Model>(modelHandle);

	// ��ʓ��Ƀ����_���ɐ���
	Vector3 screenPos{};
	screenPos.x = GetRand(static_cast<int>(Application::GetInstance().GetWindowSize().width));
	screenPos.y = GetRand(static_cast<int>(Application::GetInstance().GetWindowSize().height));
	screenPos.z = 1.0f;
	m_pos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos(screenPos.ToDxLibVector3()));

	// 覐΂̊g�嗦�������_���ɐݒ�
	float scale = GetRand(meteor_max_scale - meteor_min_scale) + meteor_min_scale;
	m_scale = { scale, scale, scale };

	// 1�t���[���ɉ�]����ʂ�0�x����`1�x�̊Ԃ���擾
	m_rotVec.x = MathUtil::ToRadian(GetRand(10) * 0.1f);
	m_rotVec.y = MathUtil::ToRadian(GetRand(10) * 0.1f);
	m_rotVec.z = MathUtil::ToRadian(GetRand(10) * 0.1f);
	
	// �ړ��x�N�g��
	Vector3 distance = playerPos - m_pos;
	distance.Normalize();
	distance *= meteor_move_speed;
	m_moveVec = distance;

	// ���f���̐ݒ�
	m_pModel->SetPos(m_pos);			// �ʒu
	m_pModel->SetRot(m_rot);			// ��]
	m_pModel->SetScale(m_scale);		// �g�嗦
	m_pModel->SetUseCollision(true);	// �����蔻����g�p����
	m_pModel->Update();					// �X�V
}

// �R���X�g���N�^
// �z�u�f�[�^�ʂ�ɐ����A�ړ����Ȃ�
Meteor::Meteor(int modelHandle, UnityGameObject data):
	m_pos(data.pos),
	m_rot(data.rot),
	m_scale(data.scale),
	m_slowValue(1.0f),
	m_isEnabled(true),
	m_moveVec({ 0, 0, 0 }),
	m_rotVec({ 0, 0, 0 })
{
	// ���f���̐ݒ�
	m_pModel->SetPos(m_pos);			// �ʒu
	m_pModel->SetRot(m_rot);			// ��]
	m_pModel->SetScale(m_scale);		// �g�嗦
	m_pModel->SetUseCollision(true);	// �����蔻����g�p����
	m_pModel->Update();					// �X�V
}

// �f�X�g���N�^
Meteor::~Meteor()
{
}

// �X�V
void Meteor::Update(Vector3 cameraPos)
{
	// �J���������ɍs������
	if (cameraPos.z > m_pos.z)
	{
		// ����
		m_isEnabled = false;
	}

	// �ړ�
	m_pos += (m_moveVec * m_slowValue);

	// ��]
	m_rot += (m_rotVec * m_slowValue);

	// ���f���̈ʒu��ݒ�
	m_pModel->SetPos(m_pos);
	
	// ���f���̉�]��ݒ�
	m_pModel->SetRot(m_rot);

	// ���f���̍X�V
	m_pModel->Update();
}

// �`��
void Meteor::Draw()
{
	// ���C�e�B���O���g�p���Ȃ�
	SetUseLighting(false);
	m_pModel->Draw();
	SetUseLighting(true);
}

// �X���[�̒l�̐ݒ�
void Meteor::SetSlowValue(float slowValue)
{
	m_slowValue = slowValue;
}

// ���݃t���O�̎擾
bool Meteor::IsEnabled() const
{
	return m_isEnabled;
}

// ���f���̃n���h���̎擾
int Meteor::GetModelHandle() const
{
	return m_pModel->GetModelHandle();
}
