#include "BossMatrix.h"
#include "../../../Model.h"
#include "../../../UI/Gauge.h"
#include "../../../UI/StringUI.h"
#include "../../../UI/UIManager.h"
#include "../../../Math/MathUtil.h"
#include "../../../Application.h"
#include "../../Laser/LaserManager.h"
#include "../../Player.h"
#include "../../../Effect/Effekseer3DEffectManager.h"
#include <random>
#include <algorithm>

// TODO : HP�������ȉ��ɂȂ����瓧���ɂȂ�(���[�U�[�̔��ˏꏊ�̓����_���ɂ���)

namespace
{
	// �ʒu
	const Vector3 init_pos = { 0.0f, 300.0f, 5000.0f };				// �����ʒu
	const Vector3 goal_init_pos = { 0.0f, 300.0f, 2000.0f };		// �o�ꎞ�̈ʒu

	// ���f��
	const Vector3 model_rot = { MathUtil::ToRadian(20), DX_PI_F, 0.0f};
	const Vector3 model_scale = { 2.0f , 2.0f, 2.0f };			// �g�嗦
	const Vector3 init_model_direction = { 0.0f, 0.0f, -1.0f };	// �����̌���

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
	constexpr float move_speed = 10.0f;			// �ړ����x
	constexpr float distance_threshold = 10.0f; // �ړI�n�ɓ��B�������ǂ�������臒l
	const Vector3 move_pos[] =					// �ړ���̍��W
	{
		goal_init_pos,
		{ 930, 300, 800 },
		{ 930, -300, 800 },
		{ -930, 300, 800 },
		{ -930, -300, 800 },
	};

	// ���S
	constexpr float died_swing_width = 5.0f;	// ���S���̉��h��̑傫��
	constexpr float died_swing_speed = 1.0f;	// ���S���̉��h��̑���
	constexpr int died_continue_frame = 60 * 5;	// ���S���̉��o�̌p������

	// HP
	auto& screenSize = Application::GetInstance().GetWindowSize();
	constexpr int max_hp = 1000;		// �ő�HP
	const Vector2 hp_gauge_pos = { screenSize.width / 2.0f, 0.0f + 100.0f};	// HP�Q�[�W�̈ʒu
	const Vector2 hp_gauge_size = { 500, 20 };										// HP�Q�[�W�̃T�C�Y
	const std::string hp_gauge_img_file_path = "Data/Image/HP.png";				// HP�Q�[�W�̉摜�t�@�C���p�X
	const std::string hp_gauge_back_img_file_path = "Data/Image/HPBack.png";	// HP�Q�[�W�̔w�i�摜�t�@�C���p�X
	const std::string hp_gauge_frame_img_file_path = "Data/Image/HPFrame.png";	// HP�Q�[�W�̘g�摜�t�@�C���p�X

	// �{�X�̖��O
	const std::string boss_name_key = "BossMatrixName";	// �{�X�̖��O�L�[
	const Vector2 boss_name_pos = { hp_gauge_pos.x, hp_gauge_pos.y - 50.0f };	// �{�X�̖��O�̈ʒu

	// �����蔻��̔��a
	constexpr float collision_radius = 250.0f;

	// �t���[��
	constexpr int next_attack_state_frame = 60 * 5;			// ���̍U���X�e�[�g�Ɉڂ�܂ł̃t���[��
	constexpr int stop_normal_laser_attack_frame = 60 * 20;	// �ʏ탌�[�U�[�U���̃t���[��
	constexpr int die_idle_frame = 60 * 3;					// ���S���̑ҋ@�t���[��
	constexpr int die_shake_frame = 60 * 5;					// ���S���̗h���t���[��
	constexpr int die_effect_interval_frame = 20;			// ���S���̃G�t�F�N�g�̍Đ��Ԋu
}

// �R���X�g���N�^
BossMatrix::BossMatrix(int modelHandle, std::shared_ptr<Player> pPlayer, std::shared_ptr<LaserManager> pLaserManager) :
	m_attackStateIndex(0),
	m_isMoveEnd(false),
	m_idleFrame(0),
	m_laserKey(-1),
	m_laserFrame(0),
	m_damageEffectHandle(-1),
	m_dieIdleFrame(die_idle_frame),
	m_dieShakeFrame(die_shake_frame),
	m_dieEffectIntervalFrame(die_effect_interval_frame)
{
	// ������
	m_pPlayer = pPlayer;
	m_pLaserManager = pLaserManager;
	m_pos = m_pPlayer->GetPos() + init_pos;
	m_rot = model_rot;
	m_opacity = 0.0f;
	m_hp = max_hp;
	m_collisionRadius = collision_radius * model_scale.x;
	for (auto& point : move_pos)
	{
		m_movePointTable.push_back(point);
	}

	// �X�e�[�g�}�V���̐ݒ�
	m_stateMachine.AddState(State::ENTRY, {}, [this]() {UpdateEntry(); }, {});
	m_stateMachine.AddState(State::IDLE, {}, [this]() {UpdateIdle(); }, {});
	m_stateMachine.AddState(State::DIE, {}, [this]() {UpdateDie(); }, {});
	m_stateMachine.AddState(State::MOVE_NORMAL_LASER_ATTACK, {}, [this]() {UpdateMoveNormalLaserAttack(); }, {});
	m_stateMachine.AddState(State::MOVE_HOMING_LASER_ATTACK, {}, [this]() {UpdateMoveHomingLaserAttack(); }, {});
	m_stateMachine.AddState(State::STOP_NORMAL_LASER_ATTACK, [this]() {EntarStopNormalLaserAttack(); }, [this]() {UpdateStopNormalLaserAttack(); }, {});
	m_stateMachine.AddState(State::CUBE_LASER_ATTACK, {}, [this]() {UpdateCubeLaserAttack(); }, {});
	m_stateMachine.SetState(State::ENTRY);

	// �U���X�e�[�g�̒ǉ�
//	m_attackStateTable.push_back(State::MOVE_NORMAL_LASER_ATTACK);
//	m_attackStateTable.push_back(State::MOVE_HOMING_LASER_ATTACK);
	m_attackStateTable.push_back(State::STOP_NORMAL_LASER_ATTACK);
//	m_attackStateTable.push_back(State::CUBE_LASER_ATTACK);
	ShuffleAttackState();

	// HP�Q�[�W�̐ݒ�
	m_pHpGauge = std::make_shared<Gauge>(
		hp_gauge_img_file_path, hp_gauge_back_img_file_path, hp_gauge_frame_img_file_path, max_hp, 
		hp_gauge_pos, hp_gauge_size, true, 2, true, 3);
	UIManager::GetInstance().AddUI("BossHPGauge", m_pHpGauge, 2, { 0, 1 });

	// �{�X���O�̐ݒ�
	m_pBossName = std::make_shared<StringUI>(boss_name_key);
	m_pBossName->SetPos(boss_name_pos);
	UIManager::GetInstance().AddUI("BossName", m_pBossName, 2, { 0, 1 });

	// ���f���ݒ�
	m_pModel = std::make_shared<Model>(modelHandle);	// �C���X�^���X����
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
	// HP�Q�[�W�̍X�V
	m_pHpGauge->Update();	

	// Z���W�̍X�V
	m_pos.z += m_pPlayer->GetMoveVec().z;

	// �X�e�[�g�}�V���̍X�V
	m_stateMachine.Update();

	// �v���C���[�����̉�]�s��̎擾
	Matrix rotMtx = Matrix::GetRotationMatrix(init_model_direction, (m_pPlayer->GetPos() - m_pos).Normalized());
	Vector3 rot = { rotMtx.ToEulerAngle().x * -1, rotMtx.ToEulerAngle().y + DX_PI_F, rotMtx.ToEulerAngle().z * -1 };

	// ���f���ݒ�
	m_pModel->RestoreAllMaterialDifColor();	// �f�B�t���[�Y�J���[�����ɖ߂�
	m_pModel->SetOpacity(m_opacity);	// �s�����x
	m_pModel->SetRot(rot);				// ����
	m_pModel->SetPos(m_pos);			// �ʒu
	m_pModel->Update();					// ���f���̓����蔻��A�A�j���[�V�����̍X�V
}

// �`��
void BossMatrix::Draw()
{
	// ���f���̕`��
	m_pModel->Draw();

#ifdef _DEBUG
	// �����蔻��̕`��
	DrawSphere3D(m_pos.ToDxLibVector3(), m_collisionRadius, 16, 0xff0000, 0xff0000, false);
#endif
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
		EffectID::enemy_boss_hit_effect,
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

// �ʏ탌�[�U�[�U���̊J�n
void BossMatrix::EntarStopNormalLaserAttack()
{
	// �t���[���̏�����
	m_laserFrame = stop_normal_laser_attack_frame;

	// �ʏ탌�[�U�[���˗p�̃A�j���[�V�����ɕύX
	m_pModel->ChangeAnimation(laser_fire_anim_no, true, false, 8);

	// ���[�U�[�̐���
	m_laserKey = m_pLaserManager->AddLaser(LaserType::NORMAL, shared_from_this(), 140, 10000, 2.0f, false);
}

// �o�ꎞ�̍X�V
void BossMatrix::UpdateEntry()
{
	// �s�����x���グ��
	m_opacity += 0.005f;
	m_opacity = (std::min)(m_opacity, 1.0f);
	m_pModel->SetOpacity(m_opacity);

	// �ړ�
	if (!m_isMoveEnd)
	{
		// �x�N�g���̎擾
		Vector3 moveVec = ((goal_init_pos + m_pPlayer->GetPos()) - m_pos).Normalized() * entry_move_speed;

		// �ړ�
		m_pos += moveVec;

		// �ړI�n�ɓ��B������ 
		if (m_pos.Distance(goal_init_pos + m_pPlayer->GetPos()) < distance_threshold)
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
	// ���[�U�[���폜
	m_pLaserManager->DeleteLaser(m_laserKey);

	// UI���i�[
	UIManager::GetInstance().Store();
}

// �ړ����Ȃ���ʏ탌�[�U�[�U��
void BossMatrix::UpdateMoveNormalLaserAttack()
{

}

// �ړ����Ȃ���z�[�~���O���[�U�[�U��
void BossMatrix::UpdateMoveHomingLaserAttack()
{
}

// �ʏ탌�[�U�[�U��
void BossMatrix::UpdateStopNormalLaserAttack()
{
	// ���[�U�[�̔��ˈʒu�̍X�V
	Vector3 pos = Vector3::FromDxLibVector3(
		MV1GetFramePosition(m_pModel->GetModelHandle(), normal_laser_fire_frame));
	m_laserFirePos = { pos.x, pos.y, pos.z - 200.0f };

	// �A�j���[�V�������I��������
	if (m_laserFrame-- <= 0)
	{
		// �X�e�[�g��ҋ@�ɕύX
		m_stateMachine.SetState(State::IDLE);

		// ���[�U�[�̍폜
		m_pLaserManager->DeleteLaser(m_laserKey);
	}
}

// �L���[�u���[�U�[�U��
void BossMatrix::UpdateCubeLaserAttack()
{
}

// �U���X�e�[�g�̏������V���b�t��
void BossMatrix::ShuffleAttackState()
{
	std::random_device seed;
	std::mt19937 engine(seed());
	std::shuffle(m_attackStateTable.begin(), m_attackStateTable.end(), engine);
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