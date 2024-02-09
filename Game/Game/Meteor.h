#pragma once
#include "../Math/Vector3.h"
#include "../Editor/DataReaderFromUnity.h"
#include <memory>

// �v���g�^�C�v�錾
class Model;

/// <summary>
/// 覐΃N���X
/// </summary>
class Meteor
{
public:
	// �R���X�g���N�^
	Meteor(Vector3 playerPos);

	// �R���X�g���N�^
	// ���̃R���X�g���N�^��Unity����̃f�[�^���󂯎��
	Meteor(UnityGameObject data);

	// �f�X�g���N�^
	~Meteor();

	// �X�V
	void Update(Vector3 cameraPos);
	void UpdateStart(Vector3 playerPos);

	// �`��
	void Draw();

	// �X���[�̒l�̐ݒ�
	void SetSlowValue(float slowValue);

	// ���݃t���O�̎擾
	bool IsEnabled() const;

	// ���f���n���h���̎擾
	int GetModelHandle() const;

private:
	// �|�C���^
	std::unique_ptr<Model> m_pModel;

	// �ʒu���
	Vector3 m_pos;

	// ��]�p�x
	Vector3 m_rot;

	// �g�嗦
	Vector3 m_scale;

	// �ړ��x�N�g��
	Vector3 m_moveVec;

	// ��]�x�N�g��
	Vector3 m_rotVec;

	// �X���[�̒l
	float m_slowValue;

	// ���݃t���O
	bool m_isEnabled;
};