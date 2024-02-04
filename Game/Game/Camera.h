#pragma once
#include "../Math/Vector3.h"

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	// �R���X�g���N�^
	Camera(Vector3 pos, Vector3 target);
	Camera(Vector3 playerPos);

	// �f�X�g���N�^
	~Camera();

	// �X�V
	void Update(Vector3 pos, Vector3 target);	// �ʏ펞�̍X�V
	void UpdatePlay(Vector3 playerPos);			// �v���C���̍X�V
	void UpdateStart(Vector3 playerPos);		// �X�^�[�g���o���̍X�V
	void GameClearUpdate(Vector3 playerPos);	// �Q�[���N���A���̍X�V
	void GameOverUpdate(Vector3 playerPos);		// �Q�[���I�[�o�[���̍X�V

	// �J�����̐ݒ�	
	void SetCamera();		

	// �J�����̍��W���擾
	Vector3 GetPos() const;

	// �J�����̐����������擾
	float GetCameraHorizon() const;

	// �X�^�[�g���o���������t���O�̎擾
	bool GetIsStartAnimation() const;

	// �X���[�̒l�̐ݒ�
	void SetSlowValue(float slowValue);

private:
	int m_windEffectHandle;

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

	// �G���~�[�g�Ȑ��̒l
	float m_hermiteValue;		

	// ���[�v�̒l
	float m_lerpValue;

	// �X���[�̒l
	float m_slowValue;			

	// �t���O
	bool m_isStartAnimation;	// �X�^�[�g���o��������
};