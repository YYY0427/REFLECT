#include "Player.h"
#include "Shield.h"
#include "../Util/InputState.h"
#include "../Model.h"
#include "../Effekseer3DEffectManager.h"
#include "../Util/Range.h"
#include "../Application.h"
#include "../Math/Matrix.h"
#include "../Math/MathUtil.h"
#include "../Math/Vector2.h"
#include "../UI/Gauge.h"
#include "../UI/UIManager.h"
#include <string>
#include <algorithm>

namespace
{
	// �v���C���[���f���̃t�@�C���̃p�X
	const std::string model_file_path = "Data/Model/Player.mv1";

	// �v���C���[�̈ړ���
	const Vector3 player_vec_up = { 0, 1, 0 };
	const Vector3 player_vec_down = { 0, -1, 0 };
	const Vector3 player_vec_right = { -1, 0, 0 };
	const Vector3 player_vec_left = { 1, 0, 0 };

	// �v���C���[�̒ʏ�ړ����x
	constexpr float move_normal_speed = 1.5f;

	// �v���C���[��Z���ړ����x
	constexpr float move_z_speed = 0.5f;

	// �v���C���[�̓����蔻��̔��a
	constexpr float model_collision_radius = 30.0f;

	// ���G���Ԃ̃t���[����
	constexpr int ultimate_frames = 120;

	// �ő�HP
	constexpr int max_hp = 300;

	// ���t���[���O�܂ňʒu����ۑ����邩
	constexpr int log_frame = 10;

	// �v���C���[�̉���
	constexpr float player_width = 50.0f;

	// �v���C���[�̏c��
	constexpr float player_height = 50.0f;

	// �v���C���[��HP�o�[�̃t�@�C���p�X
	const std::string hp_bar_file_path = "Data/Image/HPBar.png";

	// �v���C���[��HP�o�[�̔w�i�摜�̃t�@�C���p�X
	const std::string hp_bar_back_file_path = "Data/Image/StatusBase.png";

	// �v���C���[��HP�o�[�̈ʒu
	const Vector2 hp_bar_pos = { 200, 550 };

	// �v���C���[��HP�o�[�̃T�C�Y
	const Vector2 hp_bar_size = { 300, 13 };

}

//  �R���X�g���N�^
Player::Player(UnityGameObject data) :
	m_pos(data.pos),
	m_rot(data.rot),
	m_scale(data.scale),
	m_moveVec(0, 0, 0),
	m_hp(max_hp),
	m_ultimateTimer(0),
	m_isInputLeftStick(false),
	m_moveSpeed(move_normal_speed),
	m_playerDeadEffectHandle(-1),
	m_isPlayerDeadEffect(false)
{
	// �v���C���[���f���̃C���X�^���X�̐���
	m_pModel = std::make_shared<Model>(model_file_path.c_str());

	// �V�[���h�̃C���X�^���X�̐���
	m_pShield = std::make_shared<Shield>(*this);

	// ���f���̊g�嗦�̐ݒ�
	m_pModel->SetScale(m_scale);

	// ��]���̐ݒ�
	m_pModel->SetRot(m_rot);

	// �ʒu���̐ݒ�
	m_pModel->SetPos(m_pos);

	// �A�j���[�V�����Ɠ����蔻��̍X�V
	m_pModel->Update();

	// HP�o�[�̃C���X�^���X�̐���
	m_pHPbar = std::make_shared<Gauge>(
		hp_bar_file_path,
		hp_bar_back_file_path,
		"",
		max_hp,
		hp_bar_pos,
		hp_bar_size,
		true, 
		3.0f,
		false,
		0.0f);

	// UI�̓o�^
	UIManager::GetInstance().AddUI("HPBar", m_pHPbar, 0, { 0, 1 });

	// �u�[�X�g�G�t�F�N�g�̍Đ�
//	Effekseer3DEffectManager::GetInstance().PlayEffectLoopAndFollow(boostEffectHandle_, EffectID::player_boost, &pos_, boostEffectScale_, boostEffectSpeed_, { rot_.x, 0.0f, 0.0f });
}

//  �f�X�g���N�^
Player::~Player()
{
}

// �X�V
void Player::Update(float cameraHorizon)
{
	auto& effectManager = Effekseer3DEffectManager::GetInstance();

	// ���X�e�B�b�N�̓��͏��̎擾
	int up = InputState::IsPadStick(PadLR::LEFT, PadStickInputType::UP);
	int down = InputState::IsPadStick(PadLR::LEFT, PadStickInputType::DOWN);
	int left = InputState::IsPadStick(PadLR::LEFT, PadStickInputType::LEFT);
	int right = InputState::IsPadStick(PadLR::LEFT, PadStickInputType::RIGHT);

	// �J�����̉�]�ɍ��킹�Ĉړ��x�N�g�����쐬
	Vector3 moveUp = Vector3::Transform(player_vec_up, Matrix::GetRotationY(cameraHorizon));
	Vector3 moveDown = Vector3::Transform(player_vec_down, Matrix::GetRotationY(cameraHorizon));
	Vector3 moveRight = Vector3::Transform(player_vec_right, Matrix::GetRotationY(cameraHorizon));
	Vector3 moveLeft = Vector3::Transform(player_vec_left, Matrix::GetRotationY(cameraHorizon));

	// �ړ����̏�����
	m_isInputLeftStick = false;
	m_moveVec = { 0, 0, 0 };
	Vector3 moveVecX = { 0, 0, 0 };
	Vector3 moveVecY{ 0, 0, 0 };

	// �X�e�B�b�N�����͂���Ă�����ړ��x�N�g���ɃX�e�B�b�N���X���Ă�������̃x�N�g������
	// �X�e�B�b�N�̌X�����킢�ɂ���ăx�N�g�����傫���Ȃ�
	if (up > 0)
	{
		moveVecY = moveUp * up;
		m_isInputLeftStick = true;
	}
	if (left > 0)
	{
		moveVecX = moveLeft * left;
		m_isInputLeftStick = true;
	}
	if (down > 0)
	{
		moveVecY = moveDown * down;
		m_isInputLeftStick = true;
	}
	if (right > 0)
	{
		moveVecX = moveRight * right;
		m_isInputLeftStick = true;
	}

	// �X�e�B�b�N�����͂���Ă���ꍇ�݈̂ړ�
	if (m_isInputLeftStick)
	{
		// �v���C���[���猩��x������z�����̃x�N�g���𑫂��Ĉړ��x�N�g�����쐬����
		m_moveVec = moveVecY + moveVecX;

		// �v���C���[�̃X�s�[�h���|����
		m_moveVec *= m_moveSpeed;

		// �쐬�����ړ��x�N�g���ō��W�̈ړ�
		Vector3 tempPos = m_pos + m_moveVec;

		// ���[���h���W���X�N���[�����W�ɕϊ�
		Vector3 screenPos = Vector3::FromDxLibVector3(
			ConvWorldPosToScreenPos(tempPos.ToDxLibVector3()));

		// ��ʊO�ɏo�Ȃ��悤�ɂ���
		Size size = Application::GetInstance().GetWindowSize();
		if (screenPos.x > size.width - player_width)
		{
			screenPos.x = size.width - player_width;

			Vector3 worldPos = Vector3::FromDxLibVector3(
				ConvScreenPosToWorldPos(screenPos.ToDxLibVector3()));
			m_pos.x = worldPos.x;
			m_pos.y = worldPos.y;
		}
		else if (screenPos.x < 0 + player_width)
		{
			screenPos.x = 0 + player_width;

			Vector3 worldPos = Vector3::FromDxLibVector3(
				ConvScreenPosToWorldPos(screenPos.ToDxLibVector3()));
			m_pos.x = worldPos.x;
			m_pos.y = worldPos.y;
		}
		else if (screenPos.y > size.height - player_height)
		{
			screenPos.y = size.height - player_height;

			Vector3 worldPos = Vector3::FromDxLibVector3(
				ConvScreenPosToWorldPos(screenPos.ToDxLibVector3()));
			m_pos.x = worldPos.x;
			m_pos.y = worldPos.y;
		}
		else if (screenPos.y < 0 + player_height)
		{
			screenPos.y = 0 + player_height;

			Vector3 worldPos = Vector3::FromDxLibVector3(
				ConvScreenPosToWorldPos(screenPos.ToDxLibVector3()));
			m_pos.x = worldPos.x;
			m_pos.y = worldPos.y;
		}
		else
		{
			m_pos = tempPos;
		}
	}

	// ���Z�������Ɉړ�
	m_pos.z += move_z_speed;

	// ���O�ɒǉ�
	m_posLogTable.push_front(m_pos);

	// �ۑ��\�Ȑ��𒴂��Ă����疖���������
	if (m_posLogTable.size() > log_frame)
	{
		m_posLogTable.pop_back();
	}

	// ���G���Ԃ̃^�C�}�[�̍X�V
	// 0�ȉ��ɂ͂Ȃ�Ȃ�
	m_ultimateTimer = (std::max)(--m_ultimateTimer, 0);

	// �ړ��x�N�g���̑傫������v���C���[�̌X������Z�o
	// X����]�͐i��ł���悤�Ɍ�����悤�ɏ��30�x�𑫂�
	float rotX = MathUtil::ToRadian(30.0f);
	m_rot = { rotX + m_moveVec.z * 0.01f, 0.0f, -m_moveVec.x * 0.01f };

	// �G�t�F�N�g�̐ݒ�
	/*effectManager.SetEffectRot(boostEffectHandle_, { rot_.x + DX_PI_F, rot_.y, -rot_.z });
	effectManager.SetEffectScale(boostEffectHandle_, boostEffectScale_);
	effectManager.SetEffectSpeed(boostEffectHandle_, boostEffectSpeed_);*/

	// �ʒu���W�̐ݒ�
	m_pModel->SetPos(m_pos);

	// �����Ă�������̐ݒ�
	m_pModel->SetRot(m_rot);

	// �A�j���[�V������i�߂�
	m_pModel->Update();

	// �V�[���h�̍X�V
	m_pShield->Update();
}

void Player::GameOverUpdate()
{
	// UI���i�[
	UIManager::GetInstance().Store();

	// �^�C�}�[�̍X�V
	m_waitTimer.Update(1);

	// �^�C�}�[���������Ԃ𒴂��Ă��ăG�t�F�N�g���Đ����Ă��Ȃ��ꍇ
	// �G�t�F�N�g���Đ�����
	if (m_waitTimer.IsTimeOut() && !m_isPlayerDeadEffect)
	{
		// �Đ��t���O�𗧂Ă�
		m_isPlayerDeadEffect = true;

		// �Đ����Ă���G�t�F�N�g���폜
		auto& effectManager = Effekseer3DEffectManager::GetInstance();
		effectManager.DeleteEffect(m_boostEffectHandle);

		// �v���C���[���S�G�t�F�N�g�̍Đ�
		effectManager.PlayEffectFollow(
			m_playerDeadEffectHandle, 
			EffectID::player_dead, 
			&m_pos, 
			{ 50.0f, 50.0f, 50.0f }, 0.5f);
	}
	// �^�C�}�[���������Ԉȓ��̏ꍇ�͈ړ�
	else if (!m_waitTimer.IsTimeOut())
	{
		// �ړ��x�N�g���쐬
		m_moveVec = { 0.0f, -0.1f, 1.0f };
		m_moveVec = m_moveVec.Normalized();
		m_moveVec *= 2.0f;

		// �쐬�����ړ��x�N�g���ō��W�̈ړ�
		m_pos = m_pos + m_moveVec;
	}

	// �ʒu���W�̐ݒ�
	m_pModel->SetPos(m_pos);

	// �����Ă�������̐ݒ�
	m_pModel->SetRot({ m_moveVec.Length(), 0.0f, m_moveVec.Length() });

	// �A�j���[�V�����Ɠ����蔻��̍X�V
	m_pModel->Update();
}

// �`��
void Player::Draw()
{
	// ����ł��Ȃ��ꍇ
	if (!m_isPlayerDeadEffect)
	{
		// �v���C���[���f���̕`��
		m_pModel->Draw();

		// �V�[���h�̕`��
		m_pShield->Draw();

		// �v���C���[�̓����蔻��̕`��
#ifdef _DEBUG
		DrawSphere3D(m_pos.ToDxLibVector3(), model_collision_radius, 8, 0xff0000, 0xff0000, false);
#endif 
	}
}

// �_���[�W����
void Player::OnDamage()
{
	// HP�����炷
	// 0�ȉ��ɂ͂Ȃ�Ȃ�
	m_hp = (std::max)(--m_hp, 0);

	// HP�o�[�̒l�̐ݒ�
	m_pHPbar->SetValue(m_hp);
}

// �v���C���[�������Ă��邩
bool Player::IsLive() const
{
	return (m_hp > 0) ? true : false;
}

// �ʒu���̎擾
Vector3 Player::GetPos() const
{
	return m_pos;
}

// �v���C���[�̓����蔻��̔��a�̎擾
float Player::GetCollsionRadius() const
{
	return model_collision_radius;
}

// �v���C���[���f���̃n���h���̎擾
int Player::GetModelHandle() const
{
	return m_pModel->GetModelHandle();
}

// �V�[���h�̃C���X�^���X�̎擾
std::shared_ptr<Shield> Player::GetShield() const
{
	return m_pShield;
}

// ���߂�ꂽ�t���[���̐������ʒu����ۑ�����e�[�u���̎擾
std::deque<Vector3> Player::GetPosLogTable() const
{
	return m_posLogTable;
}