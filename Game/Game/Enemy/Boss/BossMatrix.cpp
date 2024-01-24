#include "BossMatrix.h"
#include "../../../Model.h"
#include "../../../UI/Gauge.h"
#include "../../../UI/UIManager.h"
#include "../../../Math/MathUtil.h"
#include "../../../Application.h"
#include <random>
#include <algorithm>

namespace
{
	// �ʒu
	const Vector3 init_pos = { 0.0f, 300.0f, 1100.0f };			// �����ʒu
	const Vector3 goal_init_pos = { 0.0f, 300.0f, 800.0f };		// �o�ꎞ�̈ʒu

	// ���f��
	const Vector3 model_rot = { MathUtil::ToRadian(20), DX_PI_F, 0.0f};
	const Vector3 model_scale = { 1.0f , 1.0f, 1.0f };			// �g�嗦
	const Vector3 init_model_direction = { 0.0f, 0.0f, -1.0f };	// �����̌���

	// �A�j���[�V�����ԍ�
	constexpr int idle_anim_no = 0;						// �ҋ@
	constexpr int normal_laser_fire_anim_no = 1;		// �ړ�
	constexpr int cube_laser_fire_anim_no = 2;			// ���[�U�[����

	// ���f���̃}�e���A���ԍ�
	constexpr int body_material_no = 0;			// �{��
	constexpr int lense_material_no = 1;		// �����Y
	constexpr int eye_material_no = 2;			// ��
	constexpr int laser_material_no = 3;		// ���[�U�[

	// �ړ�
	constexpr float move_speed = 10.0f;			// �ړ����x
	constexpr float move_error_range = 10.0f;	// �ړ��덷�͈�
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
	const Vector2 hp_gauge_pos = { screenSize.width / 2, screenSize.height - 300};	// HP�Q�[�W�̈ʒu
	const Vector2 hp_gauge_size = { 500, 50 };										// HP�Q�[�W�̃T�C�Y
	const std::string hp_gauge_img_file_path = "Data/Image/HP.png";				// HP�Q�[�W�̉摜�t�@�C���p�X
	const std::string hp_gauge_back_img_file_path = "Data/Image/HPBack.png";	// HP�Q�[�W�̔w�i�摜�t�@�C���p�X
	const std::string hp_gauge_frame_img_file_path = "Data/Image/HPFrame.png";	// HP�Q�[�W�̘g�摜�t�@�C���p�X

	// �����蔻��̔��a
	constexpr float collision_radius = 250.0f;
}

// �R���X�g���N�^
BossMatrix::BossMatrix(int modelHandle, std::shared_ptr<Player> pPlayer, std::shared_ptr<LaserManager> pLaserManager) :
	m_attackStateIndex(0)
{
	// ������
	m_pPlayer = pPlayer;
	m_pLaserManager = pLaserManager;
	m_pos = init_pos;
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
	m_stateMachine.AddState(State::MOVE, {}, [this]() {UpdateMove(); }, {});
	m_stateMachine.AddState(State::DIE, {}, [this]() {UpdateDie(); }, {});
	m_stateMachine.AddState(State::MOVE_NORMAL_LASER_ATTACK, {}, [this]() {UpdateMoveNormalLaserAttack(); }, {});
	m_stateMachine.AddState(State::MOVE_HOMING_LASER_ATTACK, {}, [this]() {UpdateMoveHomingLaserAttack(); }, {});
	m_stateMachine.AddState(State::CUBE_LASER_ATTACK, {}, [this]() {UpdateCubeLaserAttack(); }, {});
	m_stateMachine.SetState(State::ENTRY);

	// �U���X�e�[�g�̒ǉ�
	m_attackStateTable.push_back(State::MOVE_NORMAL_LASER_ATTACK);
	m_attackStateTable.push_back(State::MOVE_HOMING_LASER_ATTACK);
	m_attackStateTable.push_back(State::CUBE_LASER_ATTACK);

	// HP�Q�[�W�̐ݒ�
	m_pHpGauge = std::make_unique<Gauge>(
		hp_gauge_img_file_path, hp_gauge_back_img_file_path, hp_gauge_frame_img_file_path, max_hp, 
		hp_gauge_pos, hp_gauge_size, true, max_hp / 100, true, 3);

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
	m_stateMachine.Update();
}

// �`��
void BossMatrix::Draw()
{
	// ���f���̕`��
	m_pModel->Draw();
}

// �U���X�e�[�g�̏������V���b�t��
void BossMatrix::ShuffleAttackState()
{
	std::random_device seed;
	std::mt19937 engine(seed());
	std::shuffle(m_attackStateTable.begin(), m_attackStateTable.end(), engine);
}
