#pragma once
#include "../EnemyBase.h"
#include <vector>

// �v���g�^�C�v�錾
class LaserManager;
class Gauge;
class StringUI;
class Flash;
class Triangle;
class ScreenShaker;

/// <summary>
/// �{�X�G
/// �}�g���b�N�X
/// </summary>
class BossMatrix : public EnemyBase
{
public:
	// �R���X�g���N�^
	BossMatrix(int modelHandle, 
			   std::shared_ptr<Player> pPlayer, 
			   std::shared_ptr<LaserManager> pLaserManager,
			   std::shared_ptr<ScreenShaker> pScreenShaker);

	// �f�X�g���N�^
	~BossMatrix();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

	// �_���[�W����
	void OnDamage(int damage, Vector3 pos) override final;

	// ���S���o
	void PerformDeathEffect() override final;

private:
	// �J�n
	void EntarStopNormalLaserAttack();	// �ʏ탌�[�U�[�U��
	void EntarMoveNormalLaserAttack();	// �ړ����Ȃ���ʏ탌�[�U�[�U��
	void EntarDie();					// ���S

	// �X�V
	void UpdateEntry();		// �o�ꎞ�̍X�V
	void UpdateIdle();		// �ҋ@���̍X�V
	void UpdateDie();		// ���S���̍X�V
	void UpdateMoveNormalLaserAttack();	// �ړ����Ȃ���ʏ탌�[�U�[�U��
	void UpdateMoveHomingLaserAttack();	// �ړ����Ȃ���z�[�~���O���[�U�[�U��
	void UpdateStopNormalLaserAttack();	// �ʏ탌�[�U�[�U��
	void UpdateCubeLaserAttack();		// �L���[�u���[�U�[�U��

	// �ړ�
	void InitMove();		// �ړ��̏�����
	void SetGoalPos();		// �ڕW���W�̐ݒ�
	void MoveInitPos();		// �����ʒu�Ɉړ�
	void Move();			// �ړ�

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
		CUBE_LASER_ATTACK,			// �L���[�u���[�U�[�U��
	};

private:
	// ���S���̃G�t�F�N�g�̃f�[�^
	struct DieEffectData
	{
		int effectHandle;
		Vector3 pos;
		Vector3 vec;
		float scale;
	};

private:
	// �X�e�[�g�}�V��
	StateMachine<State> m_stateMachine;

	// �|�C���^
	std::shared_ptr<Gauge> m_pHpGauge;
	std::shared_ptr<StringUI> m_pBossName;
	std::shared_ptr<LaserManager> m_pLaserManager;
	std::shared_ptr<ScreenShaker> m_pScreenShaker;
	std::unique_ptr<Flash> m_pFlash;
	std::unique_ptr<Triangle> m_pTriangle;

	// ���S���̃G�t�F�N�g�e�[�u��
	std::vector<DieEffectData> m_dieEffectTable;

	// �ړ�
	std::vector<Vector3> m_movePointTable;	// �ړ��|�C���g�e�[�u��
	int m_movePointIndex;					// �ړ��|�C���g�̃C���f�b�N�X
	Vector3 m_goalPos;						// �ڕW���W
	bool m_isGoal;							// �ڕW���W�ɓ��B������
	bool m_isMoveEnd;						// �ړ����I��������

	// �U���X�e�[�g
	std::vector<State> m_attackStateTable;	// �U���X�e�[�g�e�[�u��
	int m_attackStateIndex;					// �U���X�e�[�g�̃C���f�b�N�X

	// �t���[��
	int m_idleFrame;						// �ҋ@�t���[��
	int m_laserFrame;						// ���[�U�[���˃t���[��
	int m_dieIdleFrame;						// ���S���̑ҋ@�t���[��	
	int m_dieShakeFrame;					// ���S���̉��h�ꉉ�o���s���t���[��
	int m_dieEffectIntervalFrame;			// ���S���̃G�t�F�N�g�̔����Ԋu
	int m_dieDrawStopFrame;					// ���S���̕`����~�߂�t���[��

	// ���[�U�[��Key
	int m_laserKey;

	// �G�t�F�N�g�n���h��
	int m_damageEffectHandle;
	int m_dieEffectHandle;
};