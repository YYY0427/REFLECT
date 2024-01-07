#include "Camera.h"
#include "../Math/MathUtil.h"
#include <DxLib.h>

namespace
{
	// �J�����̎���p
	constexpr float camera_perspective = 90.0f;

	// �`�拗��(near, far)
	constexpr float near_distance = 5.0f;
	constexpr float far_distance = 20000.0f;

	// �v���C���[����̃J�����܂ł̋���
	constexpr float camera_distance = 200.0f;

	// �Q�[���N���A���̃J�����̉�]���x
	constexpr float camera_rotate_speed = 0.03f;
}

// �R���X�g���N�^
Camera::Camera(UnityGameObject data) :
	m_pos(data.pos),
	m_target(data.rot),
	m_perspective(camera_perspective),
	m_cameraVertical(0.0f),
	m_cameraHorizon(DX_PI_F)
{
	// �J�����̐ݒ�
	CameraSet();
}

// �f�X�g���N�^
Camera::~Camera()
{
}

// �X�V
void Camera::Update()
{
}

// �Q�[���N���A���̍X�V
void Camera::GameClearUpdate(Vector3 playerPos)
{
}

// �Q�[���I�[�o�[���̍X�V
void Camera::GameOverUpdate(Vector3 playerPos)
{
	// �J�����̐��������̉�]
	m_cameraHorizon -= camera_rotate_speed;
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
	CameraSet();
}

// �J�����̐ݒ�
void Camera::CameraSet()
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

float Camera::GetCameraHorizon() const
{
	return m_cameraHorizon;
}
