#pragma once
#include "../../Math/Vector3.h"
#include "EnemyManager.h"
#include "../../StateMachine.h"
#include <memory>

// �v���g�^�C�v�錾
class Model;
class Player;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase
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
	void OnDamage(int damage, Vector3 pos);

	// �Q�b�^�[
	Vector3 GetPos() const;		// �ʒu���
	bool IsEnabled() const;		// ���݃t���O

protected:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Player> m_pPlayer;

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