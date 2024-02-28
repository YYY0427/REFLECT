#pragma once
#include "../EnemyBase.h"

/// <summary>
/// ��̃{�X�N���X
/// </summary>
class BossMosquito final : public EnemyBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pPlayer">�v���C���[�̃|�C���^</param>
	/// <param name="pLaserManager">���[�U�[�̃}�l�[�W���[�̃|�C���^</param>
	BossMosquito(const std::shared_ptr<Player>& pPlayer, 
				 const std::shared_ptr<LaserManager>& pLaserManager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossMosquito();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override final;

private:
};