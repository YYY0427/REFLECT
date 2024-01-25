#pragma once
#include "BossEnemyBase.h"
#include "../Normal/EnemyBase.h"
#include <vector>

// �v���g�^�C�v�錾
class LaserManager;
class Gauge;
class StringUI;

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
	// �J�n
	void EntarStopNormalLaserAttack();	// �ʏ탌�[�U�[�U��

	// �X�V
	void UpdateEntry();		// �o�ꎞ�̍X�V
	void UpdateIdle();		// �ҋ@���̍X�V
	void UpdateDie();		// ���S���̍X�V
	void UpdateMoveNormalLaserAttack();	// �ړ����Ȃ���ʏ탌�[�U�[�U��
	void UpdateMoveHomingLaserAttack();	// �ړ����Ȃ���z�[�~���O���[�U�[�U��
	void UpdateStopNormalLaserAttack();	// �ʏ탌�[�U�[�U��
	void UpdateStopHomingLaserAttack();	// �z�[�~���O���[�U�[�U��
	void UpdateCubeLaserAttack();		// �L���[�u���[�U�[�U��

	// �U���X�e�[�g�̏������V���b�t��
	void ShuffleAttackState();

	// �U���X�e�[�g�̐ݒ�
	void SetAttackState();

private:
	// �X�e�[�g
	enum class State
	{
		ENTRY,		// �o��
		IDLE,		// �ҋ@
		BARIER,		// �o���A
		DIE,		// ���S

		// �U��
		MOVE_NORMAL_LASER_ATTACK,	// �ړ����Ȃ���ʏ탌�[�U�[�U��
		MOVE_HOMING_LASER_ATTACK,	// �ړ����Ȃ���z�[�~���O���[�U�[�U��
		STOP_NORMAL_LASER_ATTACK,	// �ʏ탌�[�U�[�U��
		STOP_HOMING_LASER_ATTACK,	// �z�[�~���O���[�U�[�U��
		CUBE_LASER_ATTACK,			// �L���[�u���[�U�[�U��
	};

private:
	// �X�e�[�g�}�V��
	StateMachine<State> m_stateMachine;

	// �|�C���^
	std::shared_ptr<Gauge> m_pHpGauge;
	std::shared_ptr<StringUI> m_pBossName;
	std::shared_ptr<LaserManager> m_pLaserManager;

	// �ړ�
	std::vector<Vector3> m_movePointTable;	// �ړ��|�C���g�e�[�u��
	int m_movePointIndex;					// �ړ��|�C���g�̃C���f�b�N�X
	Vector3 m_goalPos;						// �ڕW���W
	bool m_isGoal;							// �ڕW���W�ɓ��B������
	bool m_isMoveEnd;						// �ړ����I��������

	// �U���X�e�[�g
	std::vector<State> m_attackStateTable;	//	�U���X�e�[�g�e�[�u��
	int m_attackStateIndex;					// �U���X�e�[�g�̃C���f�b�N�X

	// �ҋ@
	int m_idleFrame;						// �ҋ@�t���[��
};