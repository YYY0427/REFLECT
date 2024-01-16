#include "NormalLaser.h"
#include "../Enemy/Normal/EnemyBase.h"
#include "../Player.h"
#include "../../Math/Vector2.h"
#include "../../Application.h"
#include "../../Effect/Effekseer3DEffectManager.h"
#include "../../Model.h"
#include <DxLib.h>
#include <random>
#include <algorithm>

namespace
{
	// ���f��
	const Vector3 init_model_direction = { 1.0f, 0.0f, 0.0f };	// ��������
	const Vector3 laser_model_scale = { 0.1f, 0.1f, 0.1f };		// �g�嗦

	// �G�t�F�N�g
	const Vector3 laser_effect_direction = { 0.0f, 0.0f, -1.0f };	// ��������
	const Vector3 laser_effect_scale = { 24.0f, 24.0f, 24.0f };		// �g�嗦
	constexpr int laser_effect_play_speed = 1.5f;		// �Đ����x
	constexpr int laser_effect_total_play_frame = 100;	// �Đ��t���[����
	constexpr int laser_effect_charge_frame = 150;		// �`���[�W�t���[��

	// �ړI�n�ɓ��B�������ǂ����̔���
	// �����臒l�i�K�؂Ȓl�ɒ�������K�v�j
	constexpr float distance_thres_hold = 0.1f;

	// �v���C���[��Ǐ]���Ȃ��ꍇ�̌������ʒu
	const Vector2 window_size = { static_cast<float>(Application::GetInstance().GetWindowSize().width) , static_cast<float>(Application::GetInstance().GetWindowSize().height )};
	const Vector2 goal_pos[] = 
	{
		{ 0 + 100, 0 + 100 },
		{ window_size.x - 100, 0 + 100 },
		{ 0 + 100, window_size.y - 100 },
		{ window_size.x - 100, window_size.y - 100 },
		{ window_size.x / 2, window_size.y / 2 },
	};
}

// �R���X�g���N�^
NormalLaser::NormalLaser(int modelHandle, std::shared_ptr<EnemyBase> pEnemy, std::shared_ptr<Player> pPlayer, int laserFireFrame, float laserSpeed, bool isPlayerFollowing) :
	m_pEnemy(pEnemy),
	m_pPlayer(pPlayer),
	m_laserFireFrame(laserFireFrame),
	m_isPlayerFollowing(isPlayerFollowing),
	m_normalFireMovePointIndex(0)
{
	// ������
	m_pos = m_pEnemy->GetLaserFirePos();
	m_scale = laser_model_scale;
	m_speed = laserSpeed;

	// �G�t�F�N�g�̃`���[�W���ԃt���[���ƃG�t�F�N�g�̍Đ����x����`���[�W���Ԃ����t���[���Ȃ̂����߂�
	m_chargeEffectTimer = laser_effect_charge_frame / laser_effect_play_speed;

	// �v���C���[��Ǐ]����ꍇ	
	if (m_isPlayerFollowing)
	{
		// �v���C���[�̈ʒu��ړI�n�ɐݒ�
		m_moveVec = (m_pPlayer->GetPos() - m_pos).Normalized() * laserSpeed;
	}
	// �v���C���[��Ǐ]���Ȃ��ꍇ
	else
	{
		// ���[�U�[�̖ړI�n�����X�g�ɒǉ�
		for (auto& movePoint : goal_pos)
		{
			m_normalFireMovePointList.push_back(movePoint);
		}

		// �����_���ŖړI�n��ݒ�(�z��̒��g���V���b�t��)
		std::random_device seed;
		std::mt19937 engine(seed());
		std::shuffle(m_normalFireMovePointList.begin(), m_normalFireMovePointList.end(), engine);
		Vector2 screenPos = m_normalFireMovePointList.front();
		m_normalFireGoalPos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos({ screenPos.x,screenPos.y, 0.0f }));

		// ���[�U�[�̈ړ��x�N�g����ݒ�
		m_moveVec = (m_normalFireGoalPos - m_pos).Normalized() * laserSpeed;
	}

	// �x�N�g�������̉�]�s����쐬
	m_rotMtx = Matrix::GetRotationMatrix(init_model_direction, m_moveVec);

	// �x�N�g�������̉�]�s�񂩂�I�C���[�p���o��
	Matrix effectRotMtx = Matrix::GetRotationMatrix(laser_effect_direction, m_moveVec);
	Vector3 effectRot = effectRotMtx.ToEulerAngle();

	// �G�t�F�N�g�̍Đ�
	Effekseer3DEffectManager::GetInstance().PlayEffectFollow(
		m_laserEffectHandle,
		EffectID::infinity_laser,
		&m_pos,
		laser_effect_scale,
		laser_effect_play_speed,
		effectRot);

	// ��Ԃ̒ǉ�
	m_stateMachine.AddState(State::CHARGE, {}, [this]() { UpdateCharge(); }, {});
	m_stateMachine.AddState(State::FIRE_PLYER_FOLLOWING, {}, [this]() { UpdateFirePlayerFollowing(); }, {});
	m_stateMachine.AddState(State::NORMAL_FIRE, {}, [this]() { UpdateNormalFire(); }, {});
	m_stateMachine.SetState(State::CHARGE);

	// �����蔻��Ɏg�p���郂�f���̐ݒ�
	m_pModel = std::make_unique<Model>(modelHandle);	// �C���X�^���X����
	m_pModel->SetUseCollision(true);					// �����蔻��ݒ�
	m_pModel->SetScale(m_scale);	// �g�嗦
	m_pModel->SetRotMtx(m_rotMtx);	// ��]�s��
	m_pModel->SetPos(m_pos);		// �ʒu
	m_pModel->SetOpacity(m_opacity);// �s�����x
	m_pModel->Update();				// �����蔻��̍X�V
}

// �f�X�g���N�^
NormalLaser::~NormalLaser()
{
	// �G�t�F�N�g�̍폜
	Effekseer3DEffectManager::GetInstance().DeleteEffect(m_laserEffectHandle);
}

// �X�V
void NormalLaser::Update()
{
	// �X�e�[�g���`���[�W��ԂłȂ��ꍇ
	if(m_stateMachine.GetCurrentState() != State::CHARGE)
	{
		// ���[�U�[�̔��˃t���[�������炷
		m_laserFireFrame--;

		// ���[�U�[�̔��˃t���[����0�ȉ��ɂȂ�����
		if (m_laserFireFrame <= 0)
		{
			// ���݃t���O��������
			m_isEnabled = false;
		}
	}
	
	// ��Ԃ̍X�V
	m_stateMachine.Update();

	// ��ɔ��ˌ��̈ʒu�ɍ��킹��
	m_pos = m_pEnemy->GetLaserFirePos();

	// �x�N�g�������̉�]�s����쐬
	m_rotMtx = Matrix::GetRotationMatrix(init_model_direction, m_moveVec);

	// �x�N�g�������̉�]�s�񂩂�I�C���[�p���o��
	Matrix effectRotMtx = Matrix::GetRotationMatrix(laser_effect_direction, m_moveVec);
	Vector3 effectRot = effectRotMtx.ToEulerAngle();

	// �G�t�F�N�g�̉�]����ݒ�
	Effekseer3DEffectManager::GetInstance().SetEffectRot(m_laserEffectHandle, effectRot);

	// ���f���̐ݒ�
	m_pModel->SetRotMtx(m_rotMtx);	// ��]�s��
	m_pModel->SetPos(m_pos);		// �ʒu
	m_pModel->SetOpacity(m_opacity);// �s�����x
	m_pModel->SetScale(m_scale);	// �g�嗦
	m_pModel->Update();				// �����蔻��̍X�V
}

// �`���[�W��Ԃ̍X�V
void NormalLaser::UpdateCharge()
{
	// �`���[�W���Ԃ̃^�C�}�[�̍X�V	
	m_chargeEffectTimer.Update(1);

	// �`���[�W���Ԃ��I�������
	if(m_chargeEffectTimer.IsTimeOut())
	{
		// ���f���̊g�嗦��ݒ�
		m_scale.x *= -10.0f;

		// �X�e�[�g�̕ύX
		if (m_isPlayerFollowing)
		{
			// �v���C���[��Ǐ]����ꍇ
			m_stateMachine.SetState(State::FIRE_PLYER_FOLLOWING);
		}
		else
		{
			// �v���C���[��Ǐ]���Ȃ��ꍇ
			m_stateMachine.SetState(State::NORMAL_FIRE);
		}
	}
}

// �ʏ픭�ˏ�Ԃ̍X�V
void NormalLaser::UpdateNormalFire()
{
	// �ړI�n�ɓ��B�������ǂ����̔���
	if (m_pos.Distance(m_normalFireGoalPos) < distance_thres_hold)
	{
		// �ړI�n�ɓ��B�����玟�̖ړI�n��ݒ�
		m_normalFireMovePointIndex++;

		// ���̖ړI�n�����X�g�̍Ō�܂œ��B������ŏ��ɖ߂�
		if (m_normalFireMovePointIndex >= m_normalFireMovePointList.size())
		{
			m_normalFireMovePointIndex = 0;

			// �n�_�̈ړ������̓���ւ�(�z��̒��g���V���b�t��)
			std::random_device seed;
			std::mt19937 engine(seed());
			std::shuffle(m_normalFireMovePointList.begin(), m_normalFireMovePointList.end(), engine);
		}

		// ���̖ړI�n��ݒ�
		Vector2 screenPos = m_normalFireMovePointList[m_normalFireMovePointIndex];
		m_normalFireGoalPos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos({ screenPos.x,screenPos.y, 0.0f }));

		// ���[�U�[�̈ړ��x�N�g����ݒ�
		m_moveVec = (m_normalFireGoalPos - m_pos).Normalized() * m_speed;
	}
}

// �v���C���[��Ǐ]���Ĕ��ˏ�Ԃ̍X�V
void NormalLaser::UpdateFirePlayerFollowing()
{
	// �v���C���[�̈ʒu��ړI�n�ɐݒ�
	m_moveVec = (m_pPlayer->GetPos() - m_pos).Normalized() * m_speed;
}

// �`��
void NormalLaser::Draw()
{
#ifdef _DEBUG
	// ���f���̕`��
	m_pModel->Draw();
#endif 
}
