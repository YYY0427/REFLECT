#pragma once
#include "EnemyBase.h"
#include "../../../Util/Timer.h"
#include "../../../Game/Laser/LaserManager.h"
#include <memory>

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

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

	// �Q�b�^�[
	Vector3 GetPos() const;				// ���W

private:
	// ������
	void EntarMove();	// �ړ�

	// �X�V
	void UpdateIdle();	// �ҋ@
	void UpdateMove();	// �ړ�
	void UpdateAttack();// �U��
	void UpdateDead();	// ���S

	// �S�[���̍��W
	void GetGoalPos();	

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

	// �s���f�[�^
	EnemyActionData m_actionData;	

	// ���[�U�[��Key
	int m_laserKey;
};

