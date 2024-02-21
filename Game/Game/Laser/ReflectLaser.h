#pragma once
#include "LaserBase.h"
#include "../Shield.h"

// �v���g�^�C�v�錾
class EnemyManager;

/// <summary>
/// ���˃��[�U�[
/// </summary>
class ReflectLaser : public LaserBase
{
public:
	// �R���X�g���N�^
	ReflectLaser(const std::shared_ptr<EnemyManager>& pEnemyManager, 
				 const std::shared_ptr<Shield>& pShield, 
				 const std::shared_ptr<LaserBase>& pLaser, 
				 const Vector3& firePos);

	// �f�X�g���N�^
	~ReflectLaser();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// �|�C���^
	std::shared_ptr<Shield> m_pShield;		// �V�[���h�̃|�C���^
	std::shared_ptr<LaserBase> m_pLaser;	// ���[�U�[�̃|�C���^
	std::shared_ptr<EnemyManager> m_pEnemyManager;	// �G�̃|�C���^

	// ���[�U�[�G�t�F�N�g�̃n���h��
	int m_laserEffectHandle;	

	Vector3 m_directionPos;
};
