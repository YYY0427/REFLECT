#include "BossMatrix.h"
#include "../../../Model.h"
#include "../../../UI/Gauge.h"
#include "../../../UI/StringUI.h"
#include "../../../UI/UIManager.h"
#include "../../../Math/MathUtil.h"
#include "../../../Application.h"
#include "../../Laser/LaserManager.h"
#include "../../Laser/LaserBase.h"
#include "../../Player.h"
#include "../../../Effect/Effekseer3DEffectManager.h"
#include "../../../Effect/Flash.h"
#include "../../../Effect/Triangle.h"
#include "../../../Effect/ScreenShaker.h"
#include "../../../Util/InputState.h"
#include "../../../MyDebug/DebugText.h"
#include "../../../Score/Score.h"
#include "../../../ModelHandleManager.h"
#include <random>
#include <algorithm>
#include <cmath>

// TODO : HP�������ȉ��ɂȂ����瓧���ɂȂ�(���[�U�[�̔��ˏꏊ�̓����_���ɂ���)
// TODO : HP�������ȉ��ɂȂ�����v���C���[�̃V�[���h�̉�]���t�ɂ���

namespace
{
	// �X�N���[���T�C�Y
	auto& screenSize = Application::GetInstance().GetWindowSize();

	// �ʒu
	const Vector3 init_pos = { 0.0f, 300.0f, 5000.0f };				// �����ʒu(���[���h���W)
	const Vector3 goal_init_pos = { 0.0f, 300.0f, 1500.0f };		// �o�ꎞ�̈ʒu(���[���h���W)
	const Vector3 normal_pos = { 640, 360, 1300 };					// �ʏ펞�̈ʒu(�X�N���[�����W)

	// ���f��
	const Vector3 model_rot = { MathUtil::ToRadian(20), DX_PI_F, 0.0f}; // ��]�� 
	const Vector3 model_scale = { 2.0f , 2.0f, 2.0f };					// �g�嗦
	const Vector3 init_model_direction = { 0.0f, 0.0f, -1.0f };			// �����̌���

	// �A�j���[�V�����ԍ�
	constexpr int idle_anim_no = 0;				// �ҋ@
	constexpr int move_anim_no = 2;				// �ړ�
	constexpr int laser_fire_anim_no = 3;		// ���[�U�[����

	// ���f���̃}�e���A���ԍ�
	constexpr int body_material_no = 0;			// �{��
	constexpr int lense_material_no = 1;		// �����Y
	constexpr int eye_material_no = 2;			// ��
	constexpr int laser_material_no = 3;		// ���[�U�[

	// �t���[���ԍ�
	constexpr int normal_laser_fire_frame = 2;	// �ʏ탌�[�U�[����

	// �ړ�
	constexpr float entry_move_speed = 10.0f;	// �o�ꎞ�̈ړ����x
	constexpr float move_speed = 20.0f;			// �ړ����x
	constexpr float distance_threshold = 10.0f; // �ړI�n�ɓ��B�������ǂ�������臒l
	const Vector3 move_pos[] =					// �ړ���̍��W
	{
		{ screenSize. width / 2.0f, screenSize.height / 2.0f, 1600 },
		{ 0 + 200, 0 + 200, 1600 },
		{ screenSize. width - 200.0f, 0 + 200, 1600 },
		{ 0 + 200, screenSize.height - 200.0f, 1600 },
		{ screenSize.width - 200.0f, screenSize.height - 200.0f, 1600 }
	};

	// HP
	constexpr int max_hp = 1000;												// �ő�HP
	const Vector2 hp_gauge_pos = { screenSize.width / 2.0f, 0.0f + 100.0f};		// HP�Q�[�W�̈ʒu
	const Vector2 hp_gauge_size = { 500, 20 };									// HP�Q�[�W�̃T�C�Y
	const std::string hp_gauge_img_file_path = "Data/Image/HP.png";				// HP�Q�[�W�̉摜�t�@�C���p�X
	const std::string hp_gauge_back_img_file_path = "Data/Image/HPBack.png";	// HP�Q�[�W�̔w�i�摜�t�@�C���p�X
	const std::string hp_gauge_frame_img_file_path = "Data/Image/HPFrame.png";	// HP�Q�[�W�̘g�摜�t�@�C���p�X

	// �{�X�̖��O
	const std::string boss_name_key = "BossMatrixName";	// �{�X�̖��O�L�[
	const Vector2 boss_name_pos = { hp_gauge_pos.x, hp_gauge_pos.y - 50.0f };	// �{�X�̖��O�̈ʒu

	// �����蔻��̔��a
	constexpr float collision_radius = 250.0f;

	// �o�ꎞ�ɕs�����x�������鑬�x
	constexpr float entry_opacity_speed = 0.005f;

	// �t���[��
	constexpr int next_attack_state_frame = 60 * 5;			// ���̍U���X�e�[�g�Ɉڂ�܂ł̃t���[��
	constexpr int stop_normal_laser_attack_frame = 60 * 20;	// �ʏ탌�[�U�[�U���̃t���[��
	constexpr int move_normal_laser_attack_frame = 60 * 20;	// �ړ����Ȃ���ʏ탌�[�U�[�U���̃t���[��
	constexpr int cube_laser_attack_frame = 60 * 10;		// �L���[�u���[�U�[�U���̃t���[��
	constexpr int cube_laser_interval_frame = 60 * 2;		// �L���[�u���[�U�[�U���̊Ԋu�t���[��
	constexpr int die_idle_frame = 60 * 3;					// ���S���̑ҋ@�t���[��
	constexpr int die_draw_stop_frame = 60 * 7;				// ���S���̕`���~�t���[��
}

// �R���X�g���N�^
BossMatrix::BossMatrix(std::shared_ptr<Player> pPlayer, std::shared_ptr<LaserManager> pLaserManager, std::shared_ptr<ScreenShaker> pScreenShaker) :
	m_attackStateIndex(0),
	m_isMoveEnd(false),
	m_idleFrame(0),
	m_laserKey(-1),
	m_laserFrame(0),
	m_damageEffectHandle(-1),
	m_dieIdleFrame(die_idle_frame),
	m_pScreenShaker(pScreenShaker),
	m_dieEffectHandle(-1),
	m_dieDrawStopFrame(die_draw_stop_frame),
	m_movePointIndex(0),
	m_isGoal(false),
	m_cubeLaserIntervalFrame(cube_laser_interval_frame)
{
	// ������
	m_pPlayer = pPlayer;
	m_pLaserManager = pLaserManager;
	m_pos = m_pPlayer->GetPos() + init_pos;
	m_rot = model_rot;
	m_opacity = 0.0f;
	m_hp = max_hp;
	m_moveSpeed = move_speed;
	m_collisionRadius = collision_radius * model_scale.x;
	for (auto& point : move_pos)
	{
		m_movePointTable.push_back(point);
	}

	// �X�e�[�g�}�V���̐ݒ�
	m_stateMachine.AddState(State::ENTRY, {}, [this]() {UpdateEntry(); }, {});
	m_stateMachine.AddState(State::IDLE, {}, [this]() {UpdateIdle(); }, {});
	m_stateMachine.AddState(State::DIE, [this]() {EntarDie(); }, [this]() {UpdateDie(); }, {});
	m_stateMachine.AddState(State::MOVE_HOMING_LASER_ATTACK, [this]() {EntarMoveHormingLaserAttack(); }, [this]() {UpdateMoveHomingLaserAttack(); }, {});
	m_stateMachine.AddState(State::CUBE_LASER_ATTACK, [this]() {EntarCubeLaserAttack(); }, [this]() {UpdateCubeLaserAttack(); }, {});
	m_stateMachine.SetState(State::ENTRY);

	// �U���X�e�[�g�̒ǉ�
	m_attackStateTable.push_back(State::MOVE_HOMING_LASER_ATTACK);
	m_attackStateTable.push_back(State::CUBE_LASER_ATTACK);
	ShuffleAttackState();

	// HP�Q�[�W�̐ݒ�
	m_pHpGauge = std::make_shared<Gauge>(
		hp_gauge_img_file_path, hp_gauge_back_img_file_path, hp_gauge_frame_img_file_path, max_hp, 
		hp_gauge_pos, hp_gauge_size, true, 2, true, 3);
	UIManager::GetInstance().AddUI("BossHPGauge", m_pHpGauge, 2, { 0, -1 });

	// �{�X���O�̐ݒ�
	m_pBossName = std::make_shared<StringUI>(boss_name_key);
	m_pBossName->SetPos(boss_name_pos);
	UIManager::GetInstance().AddUI("BossName", m_pBossName, 2, { 0, -1 });

	// ���f���ݒ�
	m_pModel = std::make_shared<Model>(ModelHandleManager::GetInstance().GetHandle(ModelType::MATRIX));	// �C���X�^���X����
	m_pModel->SetUseCollision(true);					// �����蔻��ݒ�
	m_pModel->SetOpacity(m_opacity);					// �s�����x	
	m_pModel->SetScale(model_scale);					// �g�嗦
	m_pModel->SetRot(m_rot);							// ����
	m_pModel->SetPos(m_pos);							// �ʒu
	m_pModel->Update();									// �����蔻��̍X�V
}

// �f�X�g���N�^
BossMatrix::~BossMatrix()
{
}

// �X�V
void BossMatrix::Update()
{
#ifdef _DEBUG
	// �f�o�b�O�p
	if (InputState::IsTriggered(InputType::BOSS_DETH_DEBUG))
	{
		m_hp = 0;
		OnDamage(0, m_pos);
	}
#endif

	// HP�Q�[�W�̍X�V
	m_pHpGauge->Update();	

	// Z���W�̍X�V
	m_pos.z += m_pPlayer->GetMoveVec().z;

	// �X�e�[�g�}�V���̍X�V
	m_stateMachine.Update();

	// ���f���ݒ�
	m_pModel->RestoreAllMaterialDifColor();	// �f�B�t���[�Y�J���[�����ɖ߂�
	m_pModel->SetOpacity(m_opacity);		// �s�����x
	m_pModel->SetRot(m_rot);				// ����
	m_pModel->SetPos(m_pos);				// �ʒu
	m_pModel->Update();						// ���f���̓����蔻��A�A�j���[�V�����̍X�V
}

// �`��
void BossMatrix::Draw()
{
	// ���݃t���O�������Ă��Ȃ�������`�悵�Ȃ�
	if (m_isEnabled)
	{
		DebugText::Log("BossMatrixPos", { m_pos.x, m_pos.y, m_pos.z});

		// ���f���̕`��
		m_pModel->Draw();

#ifdef _DEBUG
		// �����蔻��̕`��
		DrawSphere3D(m_pos.ToDxLibVector3(), m_collisionRadius, 16, 0xff0000, 0xff0000, false);
#endif
	}
}

// �_���[�W����
void BossMatrix::OnDamage(int damage, Vector3 pos)
{
	// HP�����炷
	m_hp -= damage;
	m_pHpGauge->SetValue(m_hp);

	// �_���[�W�G�t�F�N�g�̍Đ�
	Effekseer3DEffectManager::GetInstance().PlayEffect(
		m_damageEffectHandle,
		EffectID::player_attack_hit_effect,
		pos,
		{ 100.0f, 100.0f, 100.0f }
	);

	// HP��0�ȉ��ɂȂ����玀�S
	if (m_hp <= 0)
	{
		// �X�e�[�g�����S�ɕύX
		m_stateMachine.SetState(State::DIE);
	}
	else
	{
		// �S�Ẵ}�e���A���̃f�B�t���[�Y�J���[�𔽓]
		m_pModel->InversAllMaterialDifColor();
	}
}

// ���S���o�̊J�n
void BossMatrix::EntarDie()
{
	// ���[�U�[���폜
	m_pLaserManager->DeleteAllLaser();

	// �A�j���[�V�����̒�~
	m_pModel->StopAnim();

	// ��ʗh��J�n
	m_pScreenShaker->StartShake({ 100.0f, 0.0f }, 60);
}

// �ړ����Ȃ���z�[�~���O���[�U�[�U���̊J�n
void BossMatrix::EntarMoveHormingLaserAttack()
{
	// �t���[���̏�����
	m_laserFrame = move_normal_laser_attack_frame;

	// �ʏ탌�[�U�[���˗p�̃A�j���[�V�����ɕύX
	m_pModel->ChangeAnimation(laser_fire_anim_no, true, false, 8);

	// ���[�U�[�̐���
	m_laserKey = m_pLaserManager->AddLaser(LaserType::NORMAL, shared_from_this(), 140, 10000, 5.0f, true);

	// �ړ��̏�����
	InitMove();
}

// �L���[�u���[�U�[�U���̊J�n
void BossMatrix::EntarCubeLaserAttack()
{
	// �t���[���̏�����
	m_laserFrame = cube_laser_attack_frame;

	// �L���[�u���[�U�[���˗p�̃A�j���[�V�����ɕύX
	m_pModel->ChangeAnimation(laser_fire_anim_no, true, false, 8);
}

// �o�ꎞ�̍X�V
void BossMatrix::UpdateEntry()
{
	// �s�����x���グ��
	m_opacity += entry_opacity_speed;
	m_opacity = (std::min)(m_opacity, 1.0f);
	m_pModel->SetOpacity(m_opacity);

	// �ړ�
	if (!m_isMoveEnd)
	{
		// �x�N�g���̎擾
		Vector3 goalPos = { goal_init_pos.x, goal_init_pos.y, goal_init_pos.z + m_pPlayer->GetPos().z };
		Vector3 moveVec = (goalPos - m_pos).Normalized() * entry_move_speed;

		// �ړ�
		m_pos += moveVec;

		// �ړI�n�ɓ��B������ 
		if (m_pos.Distance(goalPos) < distance_threshold)
		{
			m_isMoveEnd = true;
		}
	}
	
	// �s�����x��1.0f�𒴂�����
	// HP�Q�[�W�̓o�ꉉ�o���I��������
	// �ړI�n�ɓ���������
	if (m_opacity >= 1.0f && 
		m_pHpGauge->IsEndBurst() &&
		m_isMoveEnd)
	{
		// ������
		m_isMoveEnd = false;

		// �X�e�[�g��ҋ@�ɕύX
		m_stateMachine.SetState(State::IDLE);
	}
}

// �ҋ@���̍X�V
void BossMatrix::UpdateIdle()
{
	// �ҋ@�A�j���[�V�����ɕύX
	m_pModel->ChangeAnimation(idle_anim_no, true, false, 8);

	// �ҋ@
	if (m_idleFrame++ > next_attack_state_frame)
	{
		// ������
		m_idleFrame = 0;

		// �U���X�e�[�g�̐ݒ�
		SetAttackState();
	}
}

// ���S���̍X�V
void BossMatrix::UpdateDie()
{
	// ����̃t���[�����o�߂����牉�o�J�n
	if (m_dieIdleFrame-- <= 0)
	{
		// UI���i�[
		UIManager::GetInstance().Store();

		// �܂��G�t�F�N�g���Đ�����Ă��Ȃ�������
		if (m_dieEffectHandle == -1)
		{
			// �X�R�A�̉��Z
			Score::GetInstance().AddScore(ScoreType::BOSS);

			// �G�t�F�N�g�̍Đ�
			Effekseer3DEffectManager::GetInstance().PlayEffect(
				m_dieEffectHandle,
				EffectID::enemy_boss_die,
				m_pos,
				{ 100.0f, 100.0f, 100.0f });
		}
		// �G�t�F�N�g�̍Đ����J�n���Ă���A���t���[���o�߂�����
		else if (m_dieDrawStopFrame-- <= 0)
		{
			// �����Ȃ�����
			m_opacity = 0.0f;

			// �G�t�F�N�g�̍Đ����I��������
			if (!Effekseer3DEffectManager::GetInstance().IsPlayingEffect(m_dieEffectHandle))
			{
				// ���݃t���O��������
				m_isEnabled = false;
			}
		}
		// �G�t�F�N�g�̈ʒu�̍X�V
		Effekseer3DEffectManager::GetInstance().SetEffectPos(m_dieEffectHandle, { m_pos.x, m_pos.y, m_pos.z - 300.0f });
	}
}

// �ړ����Ȃ���z�[�~���O���[�U�[�U��
void BossMatrix::UpdateMoveHomingLaserAttack()
{
	// ���[�U�[�̔��ˈʒu�̍X�V
	Vector3 pos = Vector3::FromDxLibVector3(
		MV1GetFramePosition(m_pModel->GetModelHandle(), normal_laser_fire_frame));
	m_laserFirePos = { pos.x, pos.y, pos.z - 200.0f };

	// ���[�U�[�̕����Ɍ�����悤�ɂ���
	Vector3 directionVec = m_pLaserManager->GetLaserData(m_laserKey).pLaser->GetDirection();
	Matrix rotMtx = Matrix::GetRotationMatrix(init_model_direction, directionVec);
	m_rot = { rotMtx.ToEulerAngle().x * -1, rotMtx.ToEulerAngle().y + DX_PI_F, rotMtx.ToEulerAngle().z * -1 };

	// �t���[�����o�߂�����
	if (m_laserFrame-- <= 0)
	{
		// �����ʒu�ֈړ�
		MoveInitPos();

		// �ړ����I��������
		if (m_isMoveEnd)
		{
			// �X�e�[�g��ҋ@�ɕύX
			m_stateMachine.SetState(State::IDLE);

			// ���[�U�[�̍폜
			m_pLaserManager->DeleteLaser(m_laserKey);
		}
	}
	else
	{
		// �ړ�
		Move();
	}
}

// �L���[�u���[�U�[�U��
void BossMatrix::UpdateCubeLaserAttack()
{
	// �t���[�����Ȃ�
	if (m_laserFrame-- >= 0)
	{
		// �t���[�����o�߂�����
		if (m_cubeLaserIntervalFrame-- <= 0)
		{
			// �t���[���̏�����
			m_cubeLaserIntervalFrame = cube_laser_interval_frame;

			// ���ˈʒu�̎擾
			Vector3 firePos = Vector3::FromDxLibVector3(
				MV1GetFramePosition(m_pModel->GetModelHandle(), normal_laser_fire_frame));

			// �L���[�u���[�U�[�̐���
			int key = m_pLaserManager->AddCubeLaser(firePos);
		}
	}
	else
	{
		// �X�e�[�g��ҋ@�ɕύX
		m_stateMachine.SetState(State::IDLE);
	}
}

// �U���X�e�[�g�̏������V���b�t��
void BossMatrix::ShuffleAttackState()
{
	std::random_device seed;
	std::mt19937 engine(seed());
	std::shuffle(m_attackStateTable.begin(), m_attackStateTable.end(), engine);
}

// �ړ�
void BossMatrix::Move()
{
	// �ړI�n�ɓ��B�������ǂ����̔���
	if (m_pos.Distance(m_goalPos) < distance_threshold && !m_isGoal)
	{
		// ���B�����ꍇ�A��񂵂��ʂ��Ăق����Ȃ��ׁA
		// �t���O�𗧂Ă�
		m_isGoal = true;

		// �ړI�n�ɓ��B�����玟�̖ړI�n��ݒ�
		m_movePointIndex++;

		// ���̖ړI�n�����X�g�̍Ō�܂œ��B������
		if (m_movePointIndex >= m_actionDataList.size())
		{
			// �ړ��̏�����
			InitMove();	
		}

		// �ړI�n�̐ݒ�
		SetGoalPos();
	}
	else
	{
		// �ړI�n�ƃx�N�g���̐ݒ�
		SetGoalPos();

		// �ړ�
		m_pos += m_moveVec;
	}
}

// �ړ��̏�����
void BossMatrix::InitMove()
{
	// ������
	m_movePointIndex = 0;
	m_isGoal = false;
	m_isMoveEnd = false;

	// �n�_�̈ړ������̓���ւ�(�z��̒��g���V���b�t��)
	std::random_device seed;
	std::mt19937 engine(seed());
	std::shuffle(m_movePointTable.begin(), m_movePointTable.end(), engine);

	// �ړI�n�̐ݒ�
	SetGoalPos();
}

// �ړI�n�̐ݒ�
void BossMatrix::SetGoalPos()
{
	// ���݂̈ړ��|�C���g�̃C�e���[�^�[�̎擾
	auto itr = m_movePointTable.begin();
	std::advance(itr, m_movePointIndex);

	// �ړI�n�̐ݒ�
	float z = (fabs(GetCameraPosition().z - m_pPlayer->GetPos().z) + itr->z) / GetCameraFar();
	m_goalPos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos_ZLinear({ itr->x, itr->y, z }));

	// �ړ��x�N�g���̐ݒ�
	m_moveVec = (m_goalPos - m_pos).Normalized() * m_moveSpeed;
}

// �U���X�e�[�g�̐ݒ�
void BossMatrix::SetAttackState()
{
	// �U���X�e�[�g�̐ݒ�
	m_stateMachine.SetState(m_attackStateTable[m_attackStateIndex]);

	// �U���X�e�[�g�̃C���f�b�N�X��i�߂�
	m_attackStateIndex++;

	// �U���X�e�[�g�̃C���f�b�N�X���U���X�e�[�g�̃T�C�Y�𒴂�����
	if (m_attackStateIndex >= m_attackStateTable.size())
	{
		// �U���X�e�[�g���V���b�t��
		ShuffleAttackState();

		// �U���X�e�[�g�̃C���f�b�N�X��������
		m_attackStateIndex = 0;
	}
}

// �����ʒu�ֈړ�
void BossMatrix::MoveInitPos()
{
	// �ړI�n�̐ݒ�
	float z = (fabs(GetCameraPosition().z - m_pPlayer->GetPos().z) + normal_pos.z) / GetCameraFar();
	m_goalPos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos_ZLinear({ normal_pos.x, normal_pos.y, z }));

	// �ړ��x�N�g���̐ݒ�
	m_moveVec = (m_goalPos - m_pos).Normalized() * m_moveSpeed;

	// �ړI�n�ɓ��B�������ǂ����̔���
	if (m_pos.Distance(m_goalPos) < distance_threshold)
	{
		// �ړ����I��������t���O�𗧂Ă�
		m_isMoveEnd = true;
	}
	else
	{
		// �ړ�
		m_pos += m_moveVec;
	}
}