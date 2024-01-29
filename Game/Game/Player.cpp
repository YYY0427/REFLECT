#include "Player.h"
#include "Shield.h"
#include "../Util/InputState.h"
#include "../Model.h"
#include "../Effect/Effekseer3DEffectManager.h"
#include "../Util/Range.h"
#include "../Application.h"
#include "../Math/Matrix.h"
#include "../Math/MathUtil.h"
#include "../Math/Vector2.h"
#include "../UI/Gauge.h"
#include "../UI/StatusBack.h"
#include "../UI/ImageUI.h"
#include "../UI/UIManager.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../MyDebug/DebugText.h"
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
	constexpr float move_z_speed = 1.5f;

	// �v���C���[�̓����蔻��̔��a
	constexpr float model_collision_radius = 50.0f;

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

	// �v���C���[��HP�����̃t�@�C���p�X
	const std::string hp_string_file_path = "Data/Image/Life.png";

	// �v���C���[��HP�����̈ʒu
	const Vector2 hp_string_pos = { 70, 560 };

	// �v���C���[��HP�����̊g�嗦
	const Vector2 hp_string_scale = { 0.8f, 0.8f };

	// �v���C���[��HP�o�[�̈ʒu
	const Vector2 hp_bar_pos = { 215, 600 };

	// �v���C���[��HP�o�[�̃T�C�Y
	const Vector2 hp_bar_size = { 300, 13 };

	// �Q�[���̃X�^�[�g���o�̈ړ����x
	constexpr float start_move_speed = 25.0f;

	// �u�[�X�g�G�t�F�N�g�̊g�嗦
	const Vector3 boost_effect_scale = { 30.0f, 30.0f, 30.0f };

	// �u�[�X�g�G�t�F�N�g�̃X�s�[�h
	constexpr float boost_effect_speed = 1.0f;
}

//  �R���X�g���N�^
Player::Player() :
	m_moveVec(0, 0, 0),
	m_hp(max_hp),
	m_ultimateTimer(0),
	m_isInputLeftStick(false),
	m_moveSpeed(move_normal_speed),
	m_playerDeadEffectHandle(-1),
	m_isPlayerDeadEffect(false),
	m_isStartAnimation(false),
	m_slowValue(1.0f),
	m_windEffectHandle(-1),
	m_opacity(1.0f)
{
	// �f�[�^�̓ǂݍ���
	auto& data = DataReaderFromUnity::GetInstance().GetData("Player");
	m_pos = data.front().pos;
	m_rot = data.front().rot;
	m_scale = data.front().scale;

	// �v���C���[���f���̃C���X�^���X�̐���
	m_pModel = std::make_shared<Model>(model_file_path.c_str());

	// ���f���̐ݒ�
	m_pModel->SetOpacity(m_opacity);// �s�����x
	m_pModel->SetScale(m_scale);	// �g�嗦
	m_pModel->SetRot(m_rot);		// ��]
	m_pModel->SetPos(m_pos);		// �ʒu
	m_pModel->Update();				// �X�V

	// �u�[�X�g�G�t�F�N�g�̍Đ�
	Effekseer3DEffectManager::GetInstance().PlayEffectLoop(
		m_boostEffectHandle, 
		EffectID::player_boost, 
		{ m_pos.x, m_pos.y + 30.0f, m_pos.z },
		boost_effect_scale,
		boost_effect_speed,
		{ m_rot.x, 0.0f, 0.0f });

	//// ���G�t�F�N�g�̍Đ�
	//Effekseer3DEffectManager::GetInstance().PlayEffectLoopAndFollow(
	//	m_windEffectHandle,
	//	EffectID::wind,
	//	&m_pos,
	//	{ 100.0f, 100.0f, 100.0f },
	//	1.0f,
	//	{ 0.0f, -DX_PI_F / 2, 0.0f });
}

//  �f�X�g���N�^
Player::~Player()
{
}

// �X�^�[�g���o�̍X�V
void Player::UpdateStart(Vector3 cameraPos)
{
	// Z�������Ɉړ�
	m_moveVec.z = (start_move_speed * m_slowValue);
	m_pos.z += m_moveVec.z;

	if (m_pos.z > cameraPos.z + 200)
	{
		// �X�^�[�g���o���������t���O�𗧂Ă�
		m_isStartAnimation = true;
	}

	// �v���C���[���X����
	m_rot.x = -MathUtil::ToRadian(25.0f);

	// �G�t�F�N�g�̐ݒ�
	auto& effectManager = Effekseer3DEffectManager::GetInstance();
	effectManager.SetEffectPos(m_boostEffectHandle, { m_pos.x, m_pos.y, m_pos.z - 30.0f });
	effectManager.SetEffectRot(m_boostEffectHandle, { m_rot.x + DX_PI_F, m_rot.y, -m_rot.z });
	effectManager.SetEffectScale(m_boostEffectHandle, boost_effect_scale);
	effectManager.SetEffectSpeed(m_boostEffectHandle, boost_effect_speed * m_slowValue);

	// ���f���̐ݒ�
	m_pModel->SetPos(m_pos);	// �ʒu
	m_pModel->SetRot(m_rot);	// ��]
	m_pModel->Update();			// �X�V
}

// �X�V
void Player::Update(float cameraHorizon)
{
	if (!m_pBackUI)
	{
		// �v���C���[UI�̔w�i�摜�̃C���X�^���X�̐���
		m_pBackUI = std::make_shared<StatusBack>();

		// UI�̓o�^
		UIManager::GetInstance().AddUI("PlayerStatusBack", m_pBackUI, 0, { 2, 1 });
	}

	// �X�^�[�g���o�����Ă��Ȃ��ꍇ
	if (!m_pBackUI->GetIsStartAnimation())
	{
		// �X�^�[�g���o
		m_pBackUI->UpdateStartAnimation();
	}
	// �X�^�[�g���o���I��������񂾂�
	else if(!m_pShield && !m_pHPbar)
	{
		// �V�[���h�̃C���X�^���X�̐���
		m_pShield = std::make_shared<Shield>(*this);

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

		// HP�����̃C���X�^���X�̐���
		auto pHpString = std::make_shared<ImageUI>(hp_string_file_path);
		pHpString->SetPos(hp_string_pos);
		pHpString->SetScale(hp_string_scale);

		// UI�̓o�^
		UIManager::GetInstance().AddUI("HPBar", m_pHPbar, 0, { 0, 1 });
		UIManager::GetInstance().AddUI("HPString", pHpString, 0, { 0, 1 });
	}

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
		m_moveVec *= (m_moveSpeed * m_slowValue);

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
	m_moveVec.z = (move_z_speed * m_slowValue);
	m_pos.z += m_moveVec.z;

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
	// X����]�͐i��ł���悤�Ɍ�����悤�X����
	float rotX = MathUtil::ToRadian(25.0f);
	m_rot = { rotX + m_moveVec.z * 0.01f, 0.0f, -m_moveVec.x * 0.01f };

	// �s�����x�����ɖ߂�
	m_opacity = 1.0f;

	// �G�t�F�N�g�̐ݒ�
	effectManager.SetEffectPos(m_boostEffectHandle, { m_pos.x, m_pos.y, m_pos.z - 30.0f });
	effectManager.SetEffectRot(m_boostEffectHandle, { m_rot.x + DX_PI_F, m_rot.y, -m_rot.z });
	effectManager.SetEffectScale(m_boostEffectHandle, boost_effect_scale);
	effectManager.SetEffectSpeed(m_boostEffectHandle, boost_effect_speed * m_slowValue);

	// ���f���̐ݒ�
	m_pModel->SetOpacity(m_opacity);	// �s�����x
	m_pModel->SetPos(m_pos);			// �ʒu
	m_pModel->SetRot(m_rot);			// ��]
	m_pModel->Update();					// �X�V

	// �V�[���h������ꍇ
	if (m_pShield)
	{
		// �V�[���h�̍X�V
		m_pShield->Update();
	}
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

#ifdef _DEBUG
		// �v���C���[�̓����蔻��̕`��
		DrawSphere3D(m_pos.ToDxLibVector3(), model_collision_radius, 8, 0xff0000, 0xff0000, false);

		// �v���C���[�̈ʒu���̕`��
		DebugText::Log("�v���C���[ ���W", { m_pos.x, m_pos.y, m_pos.z});
#endif 
	}
}

// �V�[���h�̕`��
void Player::DrawShield()
{
	// �V�[���h������ꍇ
	// �v���C���[������ł���ꍇ�͕`�悵�Ȃ�
	if (m_pShield && !m_isPlayerDeadEffect)
	{
		// �V�[���h�̕`��
		m_pShield->Draw();
	}
}

// �_���[�W����
void Player::OnDamage(int damage)
{
	// HP�����炷
	// 0�ȉ��ɂ͂Ȃ�Ȃ�
	m_hp = (std::max)(m_hp - damage, 0);

	// HP�o�[�̒l�̐ݒ�
	m_pHPbar->SetValue(m_hp);
}

// �V�[���h�����˂������̏���
void Player::OnReflect()
{
	//// ���[�U�[�������₷���悤�ɕs�����x��������
	m_opacity = 0.1f;
	m_pModel->SetOpacity(m_opacity);	
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

// �ړ��x�N�g���̎擾
Vector3 Player::GetMoveVec() const
{
	return m_moveVec;
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

 // �X�^�[�g���o���������t���O�̎擾
bool Player::GetIsStartAnimation() const
{
	return m_isStartAnimation;
}

// �X���[�̒l�̐ݒ�
void Player::SetSlowValue(float slowValue)
{
	m_slowValue = slowValue;
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