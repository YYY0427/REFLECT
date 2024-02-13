#include "Camera.h"
#include "../Math/MathUtil.h"
#include "../Effect/Effekseer3DEffectManager.h"
#include "../MyDebug/DebugText.h"
#include <DxLib.h>
#include <algorithm>
#include <cassert>

namespace
{
	// �J�����̎���p
	constexpr float camera_perspective = 70.0f;

	// �`�拗��(near, far)
	constexpr float near_distance = 5.0f;
	constexpr float far_distance = 50000.0f;

	// �v���C���[����̃J�����܂ł̋���
	constexpr float camera_distance = 400.0f;

	// �Q�[���N���A���̃J�����̉�]���x
	constexpr float camera_rotate_speed = 0.03f;

	// �J�����̈ړ����x
	constexpr float camera_move_speed = 7.5f;

	// �J�����̈ړ������͈�
	const Vector2 camera_move_limit = { 150.0f, 100.0f };
}

// �R���X�g���N�^
Camera::Camera(Vector3 pos, Vector3 target) :
	m_pos(pos),
	m_target(target),
	m_perspective(camera_perspective),
	m_cameraVertical(0.0f),
	m_cameraHorizon(DX_PI_F),
	m_isStartAnimation(false),
	m_hermiteValue(0.0f),
	m_lerpValue(0.0f),
	m_slowValue(1.0f)
{
}

// �R���X�g���N�^
Camera::Camera(Vector3 playerPos) :
	m_pos({ playerPos.x + 500, playerPos.y + 100, playerPos.z + 2000}),
	m_target(playerPos),
	m_perspective(camera_perspective),
	m_cameraVertical(0.0f),
	m_cameraHorizon(DX_PI_F),
	m_isStartAnimation(false),
	m_hermiteValue(0.0f),
	m_lerpValue(0.0f),
	m_slowValue(1.0f)
{
	// �J�����̐ݒ�
	SetCamera();
}

// �f�X�g���N�^
Camera::~Camera()
{
}

// �X�V
void Camera::Update(Vector3 pos, Vector3 target)
{
	// �J�����̍��W�ƒ����_�̍X�V
	m_pos = pos;
	m_target = target;

	// �J�����̐ݒ�
	SetCamera();
}

// �v���C���̍X�V
void Camera::UpdatePlay(Vector3 playerPos, Vector3 playerVec)
{
	// �J�������v���C���[�̃x�N�g���ɍ��킹�ď����ړ�
	if (std::fabs(m_pos.x) <= camera_move_limit.x) 
	{
		m_pos.x += -playerVec.x * 0.3f;
	}
	if (std::fabs(m_pos.y) <= camera_move_limit.y) 
	{
		m_pos.y += -playerVec.y * 0.3f;
	}

	// �J�����̈ړ�����
	m_pos.x = std::clamp(m_pos.x, -camera_move_limit.x, camera_move_limit.x);
	m_pos.y = std::clamp(m_pos.y, -camera_move_limit.y, camera_move_limit.y);

	// �J�����ƃv���C���[�̍���
	Vector3 direction = playerPos - m_pos;

	// Y���AX���𖳎�
	direction.y = 0.0f;
	direction.x = 0.0f;

	// �J�����ƃv���C���[�̋��������ȏ㗣��Ă�����
	if (direction.Length() > camera_distance)
	{
		// �J�����ƒ����_�̈ړ�
		direction.Normalize();
		m_pos += (direction * camera_move_speed * m_slowValue);
		m_target += (direction * camera_move_speed * m_slowValue);
	}

	// �J�����̐ݒ�
	SetCamera();

	DebugText::Log("CameraPos", { m_pos.x, m_pos.y, m_pos.z });
	DebugText::Log("CameraTarget", { m_target.x, m_target.y, m_target.z });
}

// �X�^�[�g���o���̍X�V
void Camera::UpdateStart(Vector3 playerPos)
{
	// �����_�̍X�V
	m_target = playerPos;

	// �v���C���[�̈ʒu���J�����̈ʒu���O�ɗ�����
	if (playerPos.z > m_pos.z + 200)
	{
		// �G���~�[�g�Ȑ��̒l�𑝂₷
		m_hermiteValue += 0.005f * m_slowValue;

		// �J�����̈ʒu���G���~�[�g�Ȑ��ňړ�������
		m_pos = Vector3::Hermite
			(
				m_pos,
				{ -1.0f, 0.0f, -1.0f },
				{ playerPos.x, playerPos.y + 50, playerPos.z - camera_distance },
				{ 1.0f, 0.0f, 1.0f },
				m_hermiteValue
			);

		// �G���~�[�g�Ȑ��̒l��1.0f�𒴂�����
		if (m_hermiteValue >= 1.0f)
		{
			// �X�^�[�g���o���������t���O�𗧂Ă�
			m_isStartAnimation = true;
			m_hermiteValue = 0.0f;
		}
	}

	// �J�����̐ݒ�
	SetCamera();
}

// �Q�[���N���A���̍X�V
bool Camera::UpdateGameClear(Vector3 playerPos)
{
	// �J�����̃^�[�Q�b�g���v���C���[�̈ʒu�ɏ��X�ɕύX
	m_lerpValue += 0.001f * m_slowValue;
	m_target = Vector3::Lerp(m_target, playerPos, m_lerpValue);

	// �J�����̈ʒu���G���~�[�g�Ȑ��ňړ�������
	m_hermiteValue += 0.002f * m_slowValue;
	Vector3 targetPos = { playerPos.x + 200.0f, playerPos.y + 50, playerPos.z + 200.0f };
	m_pos = Vector3::Hermite
	(
		m_pos,
		{ 1.0f, 0.0f, 1.0f },
		targetPos, 
		{ -1.0f, 0.0f, -1.0f },
		m_hermiteValue
	);

	// �ڕW�ʒu�ɓ��B������
	if (targetPos.Distance(m_pos) < 50.0f &&  m_target.Distance(playerPos) < 100.0f)
	{
		return true;
	}

	// �J�����̐ݒ�
	SetCamera();

	return false;
}

// �Q�[���I�[�o�[���̍X�V
void Camera::UpdateGameOver(Vector3 playerPos)
{
	// �J�����̃^�[�Q�b�g���v���C���[�̈ʒu�ɏ��X�ɕύX
	m_lerpValue += 0.001f * m_slowValue;
	m_target = Vector3::Lerp(m_target, playerPos, m_lerpValue);

	// �J�����̐ݒ�
	SetCamera();
}

// �J�����̐ݒ�
void Camera::SetCamera()
{
	// �J��������ǂꂾ�����ꂽ�Ƃ���( Near )����A �ǂ��܂�( Far )�̂��̂�`�悷�邩��ݒ�
	SetCameraNearFar(near_distance, far_distance);

	// �J�����̎���p��ݒ�(���W�A��)
	SetupCamera_Perspective(MathUtil::ToRadian(m_perspective));

	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTargetAndUpVec(
		m_pos.ToDxLibVector3(),
		m_target.ToDxLibVector3(),
		VGet(0, 1, 0));
}

// �J�����̈ʒu�̎擾
Vector3 Camera::GetPos() const
{
	return m_pos;
}

// �J�����̐����������擾
float Camera::GetCameraHorizon() const
{
	return m_cameraHorizon;
}

// �X�^�[�g���o���������t���O�̎擾
bool Camera::IsStartAnimation() const
{
	return m_isStartAnimation;
}

// �X���[�̒l�̐ݒ�
void Camera::SetSlowValue(float slowValue)
{
	m_slowValue = slowValue;
}