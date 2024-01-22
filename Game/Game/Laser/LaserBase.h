#pragma once
#include <memory>
#include "../../Math/Vector3.h"

// �v���g�^�C�v�錾
class Model;

/// <summary>
/// ���[�U�[�̊��N���X
/// </summary>
class LaserBase
{
public:
	// �R���X�g���N�^
	LaserBase();
	
	// �f�X�g���N�^
	virtual ~LaserBase();
	
	// �X�V
	virtual void Update() = 0;
	
	// �`��
	virtual void Draw() = 0;

	// ���[�U�[���~�߂�
	virtual void Stop(Vector3 pos);

	// �Q�b�^�[
	int GetModelHandle() const;	// ���f���n���h��
	bool IsEnabled() const;	// ���݃t���O
	bool IsReflect() const;	// ���˃t���O

protected:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;

	// �ʒu���
	Vector3 m_pos;

	// ��]���
	Vector3 m_rot;

	// �g�嗦
	Vector3 m_scale;

	// ���x
	float m_speed;		

	// �s�����x
	float m_opacity;	

	// ���݃t���O
	bool m_isEnabled;

	// ���˃t���O
	bool m_isReflect;
};

