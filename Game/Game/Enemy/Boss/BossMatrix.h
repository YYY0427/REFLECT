#pragma once
#include "BossEnemyBase.h"
#include <vector>

// �v���g�^�C�v�錾
class LaserManager;
class Gauge;

/// <summary>
/// �{�X�G
/// �}�g���b�N�X
/// </summary>
class BossMatrix : public BossEnemyBase
{
public:
	// �R���X�g���N�^
	BossMatrix(int modelHandle, 
			   std::shared_ptr<Player> pPlayer, 
			   std::shared_ptr<LaserManager> pLaserManager);

	// �f�X�g���N�^
	~BossMatrix();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	void UpdateEntry();		// �o�ꎞ�̍X�V
	void UpdateIdle();		// �ҋ@���̍X�V
	void UpdateMove();		// �ړ����̍X�V
	void UpdateDie();		// ���S���̍X�V
	void UpdateMoveNormalLaserAttack();	// �ړ����Ȃ���ʏ탌�[�U�[�U��
	void UpdateMoveHomingLaserAttack();	// �ړ����Ȃ���z�[�~���O���[�U�[�U��
	void UpdateCubeLaserAttack();	// �L���[�u���[�U�[�U��

	// �U���X�e�[�g�̏������V���b�t��
	void ShuffleAttackState();

private:
	// �X�e�[�g
	enum class State
	{
		ENTRY,		// �o��
		IDLE,		// �ҋ@
		MOVE,		// �ړ�
		DIE,		// ���S

		// �U��
		MOVE_NORMAL_LASER_ATTACK,	// �ړ����Ȃ���ʏ탌�[�U�[�U��
		MOVE_HOMING_LASER_ATTACK,	// �ړ����Ȃ���z�[�~���O���[�U�[�U��
		CUBE_LASER_ATTACK,			// �L���[�u���[�U�[�U��
	};

private:
	// �X�e�[�g�}�V��
	StateMachine<State> m_stateMachine;

	// �|�C���^
	std::unique_ptr<Gauge> m_pHpGauge;

	// �ړ��|�C���g�e�[�u��
	std::vector<Vector3> m_movePointTable;

	// �U���X�e�[�g
	std::vector<State> m_attackStateTable;	//	�U���X�e�[�g�e�[�u��
	int m_attackStateIndex;					// �U���X�e�[�g�̃C���f�b�N�X
};