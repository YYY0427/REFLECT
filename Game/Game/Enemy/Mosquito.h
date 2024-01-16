#pragma once
#include "EnemyBase.h"
#include "../../Util/Timer.h"
#include "../../Game/Laser/LaserManager.h"

/// <summary>
/// �G���G�N���X
/// </summary>
class Mosquito final : public EnemyBase
{
public:
	// �R���X�g���N�^
	Mosquito(int modelHandle, EnemyData data, std::shared_ptr<Player> pPlayer, std::shared_ptr<LaserManager> pLaserManager);

	// �f�X�g���N�^
	~Mosquito();

	// ������
	void EntarMove();	// �ړ�

	// �X�V
	void Update() override final;
	void UpdateIdle();		// �ҋ@
	void UpdateMove();		// �ړ�
	void UpdateAttack();	// �U��
	void UpdateDead();		// ���S

	// �`��
	void Draw() override final;

private:
	// ���
	enum class State
	{
		IDLE,		// �ҋ@
		MOVE,		// �ړ�
		ATTACK,		// �U��
		DEAD,		// ���S
	};

private:
	// ��ԃ}�V��
	StateMachine<State> m_state;

	// �ҋ@���ԃt���[��
	int m_idleFrame;		

	// ���[�U�[
	LaserType m_laserType;		// ���[�U�[�̎��
	int m_laserFireIdleFrame;	// ���[�U�[���˂܂ł̑ҋ@����
	int m_laserFireFrame;		// ���[�U�[���ˎ���
	float m_laserSpeed;			// ���[�U�[�̑��x
};

