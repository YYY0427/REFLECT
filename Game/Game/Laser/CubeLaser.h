#pragma once
#include "LaserBase.h"

// �v���g�^�C�v�錾
class Player;

/// <summary>
/// �L���[�u���[�U�[
/// </summary>
class CubeLaser : public LaserBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="firePos">���ˈʒu</param>
	/// <param name="laserSpeed">���[�U�[�̑���</param>
	/// <param name="pPlayer">�v���C���[�̃|�C���^</param>
	CubeLaser(const Vector3& firePos, 
			  const float laserSpeed, 
			  const std::shared_ptr<Player>& pPlayer);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CubeLaser();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override final;

private:
	// �v���C���[�̃|�C���^
	std::shared_ptr<Player> m_pPlayer;

	// �ړ��x�N�g��
	Vector3 m_moveVec;

	// �ő�X�P�[��
	Vector3 m_maxScale;

	// �I�����̃X�P�[��
	Vector3 m_endScale;

	// 1�t���[���ɉ�]�����
	Vector3 m_deltaRot;	
};