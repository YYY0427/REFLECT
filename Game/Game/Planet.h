#pragma once
#include "../Math/Vector3.h"
#include "../Editor/DataReaderFromUnity.h"
#include <memory>

// �v���g�^�C�v�錾
class Model;

/// <summary>
/// �f���N���X
/// </summary>
class Planet
{
public:
	// �R���X�g���N�^
	Planet(int modelHandle, UnityGameObject data);

	// �f�X�g���N�^
	~Planet();

	// �X�V
	void UpdateStart(Vector3 playerVec);
	void Update();

	// �`��
	void Draw();

private:
	// �|�C���^
	std::unique_ptr<Model> m_pModel;

	// �ʒu���
	Vector3 m_pos;

	// ��]���
	Vector3 m_rot;

	// �g�嗦
	Vector3 m_scale;

	// ��]�x�N�g��
	Vector3 m_rotVec;
};