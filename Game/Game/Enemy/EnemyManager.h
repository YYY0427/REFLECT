#pragma once
#include <memory>
#include <list>

// �v���g�^�C�v�錾
class EnemyBase;
class BossEnemyBase;

/// <summary>
/// �G�̊Ǘ��N���X
/// </summary>
class EnemyManager
{
public:
	// �R���X�g���N�^
	EnemyManager();

	// �f�X�g���N�^
	~EnemyManager();

	// �X�V
	void Update();

	// �`��
	void Draw();

private:
	// �G�̃��X�g
	std::list<std::shared_ptr<EnemyBase>> m_pEnemyList;

	// �{�X�G
	std::shared_ptr<BossEnemyBase> m_pBossEnemy;
};