#pragma once
#include "../Math/Vector3.h"

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	// �R���X�g���N�^
	Camera(Vector3 playerPos);

	// �f�X�g���N�^
	~Camera();

	// �X�V
	void Update(Vector3 playerPos);				// �ʏ펞�̍X�V
	void GameClearUpdate(Vector3 playerPos);	// �Q�[���N���A���̍X�V
	void GameOverUpdate(Vector3 playerPos);		// �Q�[���I�[�o�[���̍X�V

	// �J�����̐ݒ�	
	void CameraSet();		

	// �J�����̍��W���擾
	Vector3 GetPos() const;

	// �J�����̐����������擾
	float GetCameraHorizon() const;

private:
	// �J�����̍��W
	Vector3 m_pos;

	// �J�����̒����_
	Vector3 m_target;

	// ����p
	float m_perspective;

	// �J�����̐�������
	float m_cameraVertical;

	// �J�����̐�������
	float m_cameraHorizon;	
};