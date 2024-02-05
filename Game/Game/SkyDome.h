#pragma once
#include <memory>
#include "../Math/Vector3.h"

// �v���g�^�C�v�錾
class Model;

/// <summary>
/// �X�J�C�h�[���N���X
/// </summary>
class SkyDome
{
public:
	// �R���X�g���N�^
	SkyDome(Vector3 cameraPos);

	// �f�X�g���N�^
	~SkyDome();

	// �X�V
	void Update(Vector3 cameraPos);

	// �`��
	void Draw();

	// �Z�b�^�[
	void SetPos(Vector3 pos);

private:
	// �|�C���^
	std::unique_ptr<Model> m_pModel;

	// �ʒu���
	Vector3 m_pos;
};