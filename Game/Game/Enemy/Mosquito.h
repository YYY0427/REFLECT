#pragma once
#include "EnemyBase.h"

/// <summary>
/// �G���G�N���X
/// </summary>
class Mosquito final : public EnemyBase
{
public:
	// �R���X�g���N�^
	Mosquito(int modelHandle, EnemyData data, std::shared_ptr<Player> m_pPlayer);

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
};

