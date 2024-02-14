#pragma once
#include <memory>
#include "../Scene/SceneBase.h"

// �v���g�^�C�v�錾
class UIManager;
class Player;
class Camera;
class SkyDome;
class MeteorManager;
class DamageFlash;
class ScreenShaker;
class PlanetManager;
class LaserManager;
class EnemyManager;
class ResultWindow;
class Fade;

/// <summary>
/// �X�e�[�W���N���X
/// </summary>
class StageBase
{
public:
	// �R���X�g���N�^
	StageBase(SceneManager& manager);

	// �f�X�g���N�^
	virtual ~StageBase();

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw();

	// �����蔻��
	void Collision();

protected:
	// �V�[���}�l�[�W���[
	SceneManager& m_manager;

	// �|�C���^
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<SkyDome> m_pSkyDome;
	std::shared_ptr<MeteorManager> m_pMeteorManager;
	std::shared_ptr<DamageFlash> m_pDamageFlash;
	std::shared_ptr<ScreenShaker> m_pScreenShaker;
	std::shared_ptr<PlanetManager> m_pPlanetManager;
	std::shared_ptr<LaserManager> m_pLaserManager;
	std::shared_ptr<EnemyManager> m_pEnemyManager;
	std::shared_ptr<ResultWindow> m_pResultWindow;
	std::unique_ptr<Fade> m_pFade;

	// ���݂̃t���[��
	int m_currentFrame;

	// �E�F�[�u���X�^�[�g�������̃t���O
	bool m_isWaveStart;

	// ���C�g�n���h��
	int m_directionalLightHandle;

	// 覐΂��v���C���[�ɗ^����_���[�W
	int m_meteorDamage;
	// ���[�U�[���v���C���[�ɗ^����_���[�W
	int m_laserDamage;
	// �v���C���[�����˃��[�U�[�Ń{�X�G�ɗ^����_���[�W
	int m_playerToBossDamage;
	// �v���C���[�����˃��[�U�[�œG�ɗ^����_���[�W
	int m_playerToEnemyDamage;
	// �v���C���[�ƓG�������������̃v���C���[�ɗ^����_���[�W
	int m_enemyDamage;
};