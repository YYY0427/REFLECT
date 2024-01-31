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
	virtual void Stop(Vector3 pos) {};

	// ����
	virtual void Reflect(Vector3 pos) {};

	// ���˂��ꂽ��Ԃ��猳�ɖ߂�
	virtual void UndoReflect() {};

	// ���[�U�[������
	void Delete();

	// �Q�b�^�[
	int GetModelHandle() const;				// ���f���n���h��
	int GetReflectLaserKey() const;			// ���˃��[�U�[�̃L�[
	Vector3 GetPos() const;					// �ʒu���
	Vector3 GetEndPos() const;				// �I���ʒu
	virtual Vector3 GetDirection() const;	// �����x�N�g��
	bool IsEnabled() const;					// ���݃t���O
	bool IsReflect() const;					// ���˃t���O

	// �Z�b�^�[
	void SetPos(Vector3 pos);			// �ʒu���
	void SetReflectLaserKey(int key);	// ���˃��[�U�[�̃L�[

protected:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;

	// �ʒu���
	Vector3 m_pos;

	// �J�n�ʒu
	Vector3 m_startPos;

	// �I���ʒu
	Vector3 m_endPos;

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

	// ���˃��[�U�[�̃L�[
	int m_reflectLaserKey;	
};

