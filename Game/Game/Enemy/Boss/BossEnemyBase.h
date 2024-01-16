#pragma once
#include "../../../Math/Vector3.h"
#include <memory>

// �v���g�^�C�v�錾
class Model;
class Player;
class LaserManager;

/// <summary>
/// �{�X�G�̊��N���X
/// </summary>
class BossEnemyBase
{
public:
	// �R���X�g���N�^
	BossEnemyBase();

	// �f�X�g���N�^
	virtual ~BossEnemyBase();

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
	std::shared_ptr<LaserManager> m_pLaserManager;

	// �ʒu���
	Vector3 m_pos;

	// ��]���
	Vector3 m_rot;

	// �ړ��x�N�g��
	Vector3 m_moveVec;

	// �s�����x
	float m_opacity;

	// HP
	int m_hp;

	// ���݃t���O
	bool m_isEnabled;

	// �_���[�W�G�t�F�N�g�̃n���h��
	int m_damageEffectHandle;
};