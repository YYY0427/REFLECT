#pragma once
#include "BossEnemyBase.h"

// �v���g�^�C�v�錾
class LaserManager;

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
};