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
	// �R���X�g���N�^
	CubeLaser(int modelHandle, Vector3 firePos, std::shared_ptr<Player> pPlayer);

	// �f�X�g���N�^
	~CubeLaser();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// �|�C���^
	std::shared_ptr<Player> m_pPlayer;	// �v���C���[

	// �ړ��x�N�g��
	Vector3 m_moveVec;

	// �I�����̃X�P�[��
	Vector3 m_endScale;
};