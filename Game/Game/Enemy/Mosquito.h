#pragma once
#include "EnemyBase.h"

/// <summary>
/// �G���G�N���X
/// </summary>
class Mosquito final : public EnemyBase
{
public:
	// �R���X�g���N�^
	Mosquito(int modelHandle);

	// �f�X�g���N�^
	~Mosquito();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
};

