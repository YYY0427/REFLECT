#include "CubeLaser.h"
#include "../../Model.h"
#include "../../Math/MathUtil.h"
#include "../Player.h"
#include "../../ModelHandleManager.h"
#include <DxLib.h>

namespace
{
	// �g�呬�x
	constexpr float scale_speed = 0.0002f;

	// �s�����x�̏㏸���x
	constexpr float opacity_speed = 0.01f;
}

// �R���X�g���N�^
CubeLaser::CubeLaser(Vector3 firePos, float laserSpeed, std::shared_ptr<Player> pPlayer)
{
	// ������
	m_pos = firePos;
	m_pPlayer = pPlayer;
	m_opacity = 0.0f;	
	m_moveVec = (m_pPlayer->GetPos() - m_pos).Normalized() * laserSpeed;

	// 1�t���[���ɉ�]����ʂ�0�x����`1�x�̊Ԃ���擾
	m_deltaRot = MathUtil::ToRadian(GetRand(100) / 100.0f);

	// ���f���ݒ�
	m_pModel = std::make_unique<Model>(ModelHandleManager::GetInstance().GetHandle(ModelType::CUBE_LASER));
	m_pModel->SetUseCollision(true);	// �����蔻����g�p����
	m_pModel->SetOpacity(m_opacity);	// �s�����x
	m_pModel->SetRot(m_rot);			// ��]���
	m_pModel->SetScale(m_scale);		// �g�嗦
	m_pModel->SetPos(m_pos);			// �ʒu���
	m_pModel->Update();					// �����蔻��̍X�V
}

// �f�X�g���N�^
CubeLaser::~CubeLaser()
{
}

// �X�V
void CubeLaser::Update()
{
	// �s�����x�����Z
	m_opacity = (std::min)(m_opacity + opacity_speed, 1.0f);

	// �ړ�
	m_pos += m_moveVec;

	// �g��
	m_scale += scale_speed;

	// ��]
	m_rot += m_deltaRot;

	// ���f���ݒ�
	m_pModel->SetOpacity(m_opacity);	// �s�����x
	m_pModel->SetRot(m_rot);			// ��]���
	m_pModel->SetScale(m_scale);		// �g�嗦
	m_pModel->SetPos(m_pos);			// �ʒu���
	m_pModel->Update();					// �����蔻��̍X�V
}

// �`��
void CubeLaser::Draw()
{
	// ���f���`��
	m_pModel->Draw();
}
