#pragma once
#include "../Math/Vector3.h"
#include "../Editor/DataReaderFromUnity.h"
#include <memory>

// �v���g�^�C�v�錾
class Model;

// 覐΂̎��
enum class MeteorType
{
	SMALL,
	NORMAL
};

/// <summary>
/// 覐΃N���X
/// </summary>
class Meteor
{
public:
	// �R���X�g���N�^
	Meteor(MeteorType type,Vector3 playerPos);

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

	// �Q�b�^�[
	bool IsEnabled() const;		// ���݃t���O�̎擾
	int GetModelHandle() const;	// ���f���̃n���h���̎擾
	MeteorType GetType() const;	// 覐΂̎�ނ̎擾

private:
	// �|�C���^
	std::unique_ptr<Model> m_pModel;

	// 覐΂̎��
	MeteorType m_type;

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

	// ���݃t���O
	bool m_isEnabled;
};