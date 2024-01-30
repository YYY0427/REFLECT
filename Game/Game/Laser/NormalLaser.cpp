#include "NormalLaser.h"
#include "../Enemy/EnemyBase.h"
#include "../Player.h"
#include "../../Math/Vector2.h"
#include "../../Application.h"
#include "../../Effect/Effekseer3DEffectManager.h"
#include "../../Model.h"
#include "../../MyDebug/DebugText.h"
#include <DxLib.h>
#include <random>
#include <algorithm>

namespace
{
	// ���f��
	const Vector3 init_model_direction = { 1.0f, 0.0f, 0.0f };	// ��������
	const Vector3 laser_model_scale = { 0.1f, 0.1f, 0.1f };		// �g�嗦

	// �G�t�F�N�g
	const Vector3 init_laser_effect_direction = { 0.0f, 0.0f, -1.0f };	// ��������
	const Vector3 laser_effect_scale = { 24.0f, 24.0f, 24.0f };		// �g�嗦
	constexpr float laser_effect_play_speed = 1.0f;		// �Đ����x
	constexpr int init_laser_effect_charge_frame = 140;	// ���X�̃`���[�W�t���[��
	constexpr float laser_effect_z_length = 300.0f;		// Z���̒���

	// �t���[��
	constexpr int laser_end_frame_no = 0;	// ���[�U�[�̒[�̃t���[���ԍ�

	// �ړI�n�ɓ��B�������ǂ����̔���
	// �����臒l�i�K�؂Ȓl�ɒ�������K�v�j
	constexpr float distance_threshold = 5.0f;

	// �J������Near��0�AFar��1�Ƃ����Ƃ���Z���W
	constexpr float near_far_z_pos = 0.0f;

	// ���˒��ɃV�[���h�ɉ��t���[���������Ă��Ȃ������甽�˂��������邩
	constexpr int reflect_collision_shield_frame = 5;

	// �v���C���[��Ǐ]���Ȃ��ꍇ�̌������ʒu
	const Vector2 window_size = 
		{ static_cast<float>(Application::GetInstance().GetWindowSize().width), 
		static_cast<float>(Application::GetInstance().GetWindowSize().height )};
	const Vector2 goal_pos[] = 
	{
		{ 0 - 300, 0 - 300 },
		{ window_size.x + 300, 0 - 300 },
		{ 0 - 300, window_size.y + 300 },
		{ window_size.x + 300, window_size.y + 300 },
		{ window_size.x / 2, window_size.y / 2 },
	};
}

// �R���X�g���N�^
NormalLaser::NormalLaser(int modelHandle, std::shared_ptr<EnemyBase> pEnemy, std::shared_ptr<Player> pPlayer, int laserChargeFrame, int laserFireFrame, float laserSpeed, bool isPlayerFollowing) :
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

	// �G�t�F�N�g�̃`���[�W�t���[����ݒ�
	m_chargeEffectFrame = laserChargeFrame;

	// �G�t�F�N�g�̃`���[�W�t���[������Đ����x���Z�o
	float effectSpeed = static_cast<float>(init_laser_effect_charge_frame) / static_cast<float>(m_chargeEffectFrame);

	// �v���C���[��Ǐ]���Ȃ��ꍇ
	if(!m_isPlayerFollowing)
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

		// �ړI�n��ݒ�
		Vector2 screenPos = m_normalFireMovePointList.front();
		m_normalFireGoalPos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos({ screenPos.x,screenPos.y, near_far_z_pos }));

	}
	// ���[�U�[�̌������W��ݒ�
	m_directionPos = m_pPlayer->GetPosLogTable().back();

	// �x�N�g�������̉�]�s����쐬
	m_rotMtx = Matrix::GetRotationMatrix(init_model_direction, (m_directionPos - m_pos).Normalized());

	// �x�N�g�������̉�]�s�񂩂�I�C���[�p���o��
	Matrix effectRotMtx = Matrix::GetRotationMatrix(init_laser_effect_direction, (m_directionPos - m_pos).Normalized());
	Vector3 effectRot = effectRotMtx.ToEulerAngle();

	// �G�t�F�N�g�̍Đ�
	Effekseer3DEffectManager::GetInstance().PlayEffectFollow(
		m_laserEffectHandle,
		EffectID::normal_laser,
		&m_pos,
		laser_effect_scale,
		effectSpeed,
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
	// ���ˌ��̓G������ł�����
	if (!m_pEnemy->IsEnabled())
	{
		// ���݃t���O��������
		m_isEnabled = false;
		return;
	}

	// �X�e�[�g���`���[�W��ԂłȂ��ꍇ
	if(m_stateMachine.GetCurrentState() != State::CHARGE)
	{
		// �G�t�F�N�g�̍Đ����x�̐ݒ�
		Effekseer3DEffectManager::GetInstance().SetEffectSpeed(m_laserEffectHandle, 1.0f);

		// ���[�U�[�̔��˃t���[����0�ȉ��ɂȂ�����
		if (m_laserFireFrame-- <= 0)
		{
			// ���݃t���O��������
			m_isEnabled = false;
		}
	}
	
	// ���[�U�[�����ˏ�ԂȂ�
	if (m_isReflect)
	{
		// �t���[�������Z
		// ���t���[���o�߂����甽�ˏ�Ԃ�����
		if (m_reflectFrame++ > reflect_collision_shield_frame)
		{
			// ���ˏ�Ԃ�����
			UndoReflect();
		}
	}
	
	// ��Ԃ̍X�V
	m_stateMachine.Update();

	// ��ɔ��ˌ��̈ʒu�ɍ��킹��
	m_pos = m_pEnemy->GetLaserFirePos();

	// ���[�U�[�̐�[�̍��W��ݒ�
	m_endPos = Vector3::FromDxLibVector3(
		MV1GetFramePosition(m_pModel->GetModelHandle(), laser_end_frame_no));

	// �x�N�g�������̉�]�s����쐬
	m_rotMtx = Matrix::GetRotationMatrix(init_model_direction, (m_directionPos - m_pos).Normalized());

	// �x�N�g�������̉�]�s�񂩂�I�C���[�p���o��
	Matrix effectRotMtx = Matrix::GetRotationMatrix(init_laser_effect_direction, (m_directionPos - m_pos).Normalized());
	Vector3 effectRot = effectRotMtx.ToEulerAngle();

	// �G�t�F�N�g�̉�]����ݒ�
	Effekseer3DEffectManager::GetInstance().SetEffectRot(m_laserEffectHandle, effectRot);

	// ���[�U�[�̔��˃t���O�������Ă��Ȃ��ꍇ
	if (!m_isReflect)
	{
		// �G�t�F�N�g�̊g�嗦��ݒ�
		Effekseer3DEffectManager::GetInstance().SetEffectScale(m_laserEffectHandle, laser_effect_scale);
	}

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
	// �`���[�W���Ԃ��I�������
	if(m_chargeEffectFrame-- <= 0)
	{
		// ���f���̊g�嗦��ݒ�
		m_scale.x = -1.0f;

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
	if (m_directionPos.Distance(m_normalFireGoalPos) < distance_threshold)
	{
		// �ړI�n�ɓ��B�����玟�̖ړI�n��ݒ�
		m_normalFireMovePointIndex++;

		// ���̖ړI�n�����X�g�̍Ō�܂œ��B������
		if (m_normalFireMovePointIndex >= m_normalFireMovePointList.size())
		{
			// �C���f�b�N�X��������
			m_normalFireMovePointIndex = 0;

			// �n�_�̈ړ������̓���ւ�(�z��̒��g���V���b�t��)
			std::random_device seed;
			std::mt19937 engine(seed());
			std::shuffle(m_normalFireMovePointList.begin(), m_normalFireMovePointList.end(), engine);
		}

		// ���̖ړI�n��ݒ�
		Vector2 screenPos = m_normalFireMovePointList[m_normalFireMovePointIndex];
		m_normalFireGoalPos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos({ screenPos.x,screenPos.y, near_far_z_pos }));
	}
	else
	{
		// �S�[���̍��W��ݒ�
		m_normalFireGoalPos = Vector3::FromDxLibVector3(
			ConvScreenPosToWorldPos(
				{ m_normalFireMovePointList[m_normalFireMovePointIndex].x,
				  m_normalFireMovePointList[m_normalFireMovePointIndex].y,
				  near_far_z_pos }));

		// �x�N�g����ݒ�
		m_directionVec = (m_normalFireGoalPos - m_directionPos).Normalized() * m_speed;

		// �x�N�g����NaN��������
		if (std::isnan(m_directionVec.x) || std::isnan(m_directionVec.y) || std::isnan(m_directionVec.z))
		{
			// 0�ɐݒ�
			m_directionVec = { 0.0f, 0.0f, 0.0f };
		}

		// ���W���X�V
		m_directionPos += m_directionVec;
	}
}

// �v���C���[��Ǐ]���Ĕ��ˏ�Ԃ̍X�V
void NormalLaser::UpdateFirePlayerFollowing()
{
	// �x�N�g����ݒ�
	m_directionVec = (m_pPlayer->GetPos() - m_directionPos).Normalized() * m_speed;

	// �x�N�g����NaN��������
	if (std::isnan(m_directionVec.x) || std::isnan(m_directionVec.y) || std::isnan(m_directionVec.z))
	{
		// 0�ɐݒ�
		m_directionVec = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�̍X�V
	m_directionPos += m_directionVec;
}

// �`��
void NormalLaser::Draw()
{
#ifdef _DEBUG
	// ���f���̕`��
	SetUseLighting(false);
//	m_pModel->Draw();
	SetUseLighting(true);

	DebugText::Log("���[�U�[�̌������W", { m_directionPos.x, m_directionPos.y, m_directionPos.z });
#endif 
}

// ���[�U�[���~�߂�
void NormalLaser::Stop(Vector3 pos)
{
	// ���[�U�[�̔��˃t���O�𗧂Ă�
	m_isReflect = true;

	// �V�[���h�ɓ��������̂ŏ�����
	m_reflectFrame = 0;

	// ���[�U�[�̔��˒n�_����V�[���h�܂ł̋������Z�o
	Vector3 vec = pos - m_pos;
	float length = vec.Length();

	// ���[�U�[�̃G�t�F�N�g���V�[���h�Ŏ~�܂��Ă�悤������悤�ɁA�G�t�F�N�g�̊g�嗦��ݒ�
	Effekseer3DEffectManager::GetInstance().SetEffectScale(
		m_laserEffectHandle, { laser_effect_scale.x, laser_effect_scale.y, length / laser_effect_z_length });

	// ���[�U�[�̓����蔻��p���f���𔽑Α��Ɍ�����
	m_pModel->SetScale(m_scale);
	m_pModel->Update();
}

// ���˂��ꂽ��Ԃ��猳�ɖ߂�
void NormalLaser::UndoReflect()
{
	// ������
	m_isReflect = false;
	m_reflectFrame = 0;
}

// �����x�N�g���̎擾
Vector3 NormalLaser::GetDirection() const
{
	return (m_directionPos - m_pos);
}
