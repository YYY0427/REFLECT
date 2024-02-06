#pragma once
#include "../EnemyBase.h"

/// <summary>
/// ��̃{�X�N���X
/// </summary>
class BossMosquito final : public EnemyBase
{
public:
	// �R���X�g���N�^
	BossMosquito(std::shared_ptr<Player> pPlayer, std::shared_ptr<LaserManager> pLaserManager);

	// �f�X�g���N�^
	~BossMosquito();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
};