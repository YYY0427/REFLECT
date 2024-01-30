#pragma once
#include "../../Math/Vector3.h"
#include "EnemyManager.h"
#include "../../StateMachine.h"
#include <memory>

// �v���g�^�C�v�錾
class Model;
class Player;
class LaserManager;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase : public std::enable_shared_from_this<EnemyBase>
{
public:
	// �R���X�g���N�^
	EnemyBase();

	// �f�X�g���N�^
	virtual ~EnemyBase();

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

	// �_���[�W����
	virtual void OnDamage(int damage, Vector3 pos);

	// ���S���o
	virtual void PerformDeathEffect() {};

	// �Q�b�^�[
	Vector3 GetPos() const;				// �ʒu���
	Vector3 GetLaserFirePos() const;	// ���[�U�[�̔��ˈʒu
	bool IsEnabled() const;				// ���݃t���O
	float GetCollisionRadius() const;	// �����蔻��̔��a

protected:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<LaserManager> m_pLaserManager;

	// �s���f�[�^���X�g
	std::vector<EnemyActionData> m_actionDataList;

	// �ʒu���
	Vector3 m_pos;

	// ��]���
	Vector3 m_rot;

	// �ړ��x�N�g��
	Vector3 m_moveVec;

	// �ړI�n
	Vector3 m_goalPos;

	// ���[�U�[�̔��ˈʒu
	Vector3 m_laserFirePos;

	// �傫��
	Vector3 m_scale;

	// �����蔻��̔��a
	float m_collisionRadius;	

	// �ړ����x
	float m_moveSpeed;

	// �s�����x
	float m_opacity;

	// �U����
	int m_attackPower;

	// HP
	int m_hp;		

	// ���݃t���O
	bool m_isEnabled;

	// ���݂̍s���f�[�^�̃C���f�b�N�X
	int m_movePointIndex;

	// ���S�G�t�F�N�g�n���h��
	int m_deadEffectHandle;

	// �ړI�n�ɓ��B�������t���O
	bool m_isGoal;
};