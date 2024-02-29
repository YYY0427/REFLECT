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
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	LaserBase();
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~LaserBase();
	
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;
	
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ���[�U�[���~�߂�
	/// </summary>
	/// <param name="pos">���[�U�[���~�߂�ʒu</param>
	virtual void Stop(const Vector3& pos) {};

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="pos">���˂���ʒu</param>
	virtual void Reflect(const Vector3& pos) {};

	/// <summary>
	/// ���˂����ɖ߂�
	/// </summary>
	virtual void UndoReflect() {};

	/// <summary>
	/// ���[�U�[������
	/// </summary>
	void Delete();


	//// �Q�b�^�[ ////

	/// <summary>
	/// ���f���n���h�����擾
	/// </summary>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle() const;			

	/// <summary>
	/// ���˃��[�U�[�̃L�[���擾
	/// </summary>
	/// <returns>���˃��[�U�[�̃L�[</returns>
	int GetReflectLaserKey() const;			

	/// <summary>
	/// �ʒu�����擾
	/// </summary>
	/// <returns>�ʒu���</returns>
	const Vector3& GetPos() const;	

	/// <summary>
	/// ���[�U�[�̏I�[�ʒu���擾
	/// </summary>
	/// <returns>���[�U�[�̏I�[�ʒu</returns>
	const Vector3& GetEndPos() const;		

	/// <summary>
	/// �����x�N�g�����擾
	/// </summary>
	/// <returns>�����x�N�g��</returns>
	virtual Vector3 GetDirection() const;

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

