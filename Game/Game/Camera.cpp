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
	constexpr float camera_perspective = 90.0f;

	// �`�拗��(near, far)
	constexpr float near_distance = 50.0f;
	constexpr float far_distance = 25000.0f;

	// �v���C���[����̃J�����܂ł̋���
	constexpr float camera_distance = 400.0f;

	// �Q�[���N���A���̃J�����̉�]���x
	constexpr float camera_rotate_speed = 0.03f;

	// �J�����̈ړ����x
	constexpr float camera_move_speed = 3.0f;
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

	// ���G�t�F�N�g�̍Đ�
	Effekseer3DEffectManager::GetInstance().PlayEffectLoop(
		m_windEffectHandle,
		EffectID::wind,
		m_pos,
		{ 100.0f, 100.0f, 100.0f },
		1.0f,
		{ 0.0f, -DX_PI_F / 2, 0.0f });

	// �J�����̐ݒ�
	SetCamera();
}

// �f�X�g���N�^
Camera::~Camera()
{
}

// �X�V
void Camera::Update(Vector3 playerPos)
{
#if false
	// TODO : �J�������^�[�Q�b�g�ς��Ɛ؂�ւ�����Ⴄ�̂ŁA�X���[�Y�ɐ؂�ւ��悤�ɂ���
	// ����̊p�x�ȏ�Ȃ�⊮������
	
	// �v���C���[�̈ʒu�����ɏ����J�����̒����_�����炷
	Vector3 tempTarget = m_target;

	m_target.x = playerPos.x * 0.2f;
	m_target.y = playerPos.y * 0.2f;

	// �����_�����̊p�x�ȏ�ɂ͉�]�����Ȃ�
	Vector3 centerPos = { 0, 0, playerPos.z };
	Vector3 targetPos = m_target - m_pos;
	float angle = MathUtil::ToDegree(centerPos.Angle(targetPos));
	if (angle >= 15.0f)
	{
		DebugText::Log("15�x��������");
		m_target = tempTarget;
	}
#else
	// �v���C���[�̈ʒu�����Ƃ͋t�ɏ����J�����̒����_�����炷
	m_target.x = -playerPos.x * 0.2f;
	m_target.y = -playerPos.y * 0.2f;
#endif

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

	Effekseer3DEffectManager::GetInstance().SetEffectPos(m_windEffectHandle, {m_pos.x, m_pos.y, m_pos.z - 400.0f });

	// �J�����̐ݒ�
	SetCamera();
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
		}
	}

	Effekseer3DEffectManager::GetInstance().SetEffectPos(m_windEffectHandle, { m_pos.x, m_pos.y, m_pos.z - 400.0f });

	// �J�����̐ݒ�
	SetCamera();
}

// �Q�[���N���A���̍X�V
void Camera::GameClearUpdate(Vector3 playerPos)
{
}

// �Q�[���I�[�o�[���̍X�V
void Camera::GameOverUpdate(Vector3 playerPos)
{
	// �J�����̐��������̉�]
	m_cameraHorizon -= camera_rotate_speed * m_slowValue;
	m_cameraHorizon = (std::max)(m_cameraHorizon, MathUtil::ToRadian(30));

	// ��̒����𐂒������ɉ�]�������Ƃ��̐������̒���
	float verticalLength = camera_distance * cosf(m_cameraVertical);

	// ����
	float horizonLength = camera_distance * sinf(m_cameraVertical);

	// �J�������W�̐ݒ�
	// xz���W�͐��������̒������i�߂��Ƃ���
	m_pos.x = playerPos.x + verticalLength * sinf(m_cameraHorizon);
	m_pos.z = playerPos.z + verticalLength * cosf(m_cameraHorizon);

	// �x���W�͐������������
	m_pos.y = playerPos.y + horizonLength;

	// �J�����̒����_�̐ݒ�
	m_target = playerPos;

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
bool Camera::GetIsStartAnimation() const
{
	return m_isStartAnimation;
}

// �X���[�̒l�̐ݒ�
void Camera::SetSlowValue(float slowValue)
{
	m_slowValue = slowValue;
}