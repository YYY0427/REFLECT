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
	constexpr float opacity_speed = 0.005f;

	// �s�����x�̍ő�l
	constexpr float max_opacity = 1.0f;

	// 1�t���[���ɉ�]����p�x
	const float max_delta_rot = 1.0f;  // �ő�
	const float min_delta_rot = 0.1f;  // �ŏ�

	// ���[�U�[�̊g�嗦
	constexpr float max_scale = 20.0f;	// �ő�
	constexpr float min_scale = 10.0f;	// �ŏ�
}

// �R���X�g���N�^
CubeLaser::CubeLaser(const Vector3& firePos, 
				     const float laserSpeed, 
					 const std::shared_ptr<Player>& pPlayer)
{
	// ������
	m_pos     = firePos;
	m_pPlayer = pPlayer;
	m_opacity = 0.0f;	
	m_moveVec = (m_pPlayer->GetPos() - m_pos).Normalized() * laserSpeed;

	// 1�t���[���ɉ�]����ʂ������_���Ŏ擾
	m_deltaRot.x = MathUtil::ToRadian(MathUtil::GetRandFloat(min_delta_rot, max_delta_rot));
	m_deltaRot.y = MathUtil::ToRadian(MathUtil::GetRandFloat(min_delta_rot, max_delta_rot));
	m_deltaRot.z = MathUtil::ToRadian(MathUtil::GetRandFloat(min_delta_rot, max_delta_rot));

	// �ő�g�嗦�������_���Ŏ擾
	m_maxScale.x = MathUtil::ToRadian(MathUtil::GetRandFloat(min_scale, max_scale));
	m_maxScale.y = MathUtil::ToRadian(MathUtil::GetRandFloat(min_scale, max_scale));
	m_maxScale.z = MathUtil::ToRadian(MathUtil::GetRandFloat(min_scale, max_scale));

	// ���f���ݒ�
	m_pModel = std::make_unique<Model>(ModelHandleManager::GetInstance().GetHandle("CubeLaser"));
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
	m_opacity = (std::min)(m_opacity + opacity_speed, max_opacity);

	// �ړ�
	m_pos.z += m_pPlayer->GetMoveVec().z;
	m_pos   += m_moveVec;

	// �g��
	m_scale += scale_speed;

	// �g�嗦�̐���
	m_scale.x = (std::min)(m_scale.x, m_maxScale.x);
	m_scale.y = (std::min)(m_scale.y, m_maxScale.y);
	m_scale.z = (std::min)(m_scale.z, m_maxScale.z);

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
