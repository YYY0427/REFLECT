#pragma once
#include "LaserBase.h"
#include "../Shield.h"

/// <summary>
/// ���˃��[�U�[
/// </summary>
class ReflectLaser : public LaserBase
{
public:
	// �R���X�g���N�^
	ReflectLaser(int modelHandle, std::shared_ptr<Shield> pShield, std::shared_ptr<LaserBase> pLaser, Vector3 firePos);

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

	// ���[�U�[�G�t�F�N�g�̃n���h��
	int m_laserEffectHandle;	

	Vector3 m_directionVec;
};
