#include "Tutorial.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../UI/UIManager.h"
#include "../UI/DamageFlash.h"
#include "../Effect/ScreenShaker.h"
#include "../Effect/Effekseer3DEffectManager.h"
#include "../Game/Player.h"
#include "../Game/Camera.h"
#include "../Game/SkyDome.h"
#include "../Game/MeteorManager.h"
#include "../Game/PlanetManager.h"
#include "../Game/Laser/LaserManager.h"
#include "../Game/Enemy/EnemyManager.h"
#include <DxLib.h>

namespace
{
	// �I�u�W�F�N�g�z�u�f�[�^�̃t�@�C���p�X
	const std::string object_data_file_path = "Test";

	// 覐΂ɓ������Ă���ԂɃv���C���[�ɗ^����_���[�W
	constexpr int meteor_damage = 2;
}

// �R���X�g���N�^
Tutorial::Tutorial()
{
	// �X�e�[�g�}�V���̐ݒ�
	m_stateMachine.AddState(State::START_ANIMATION, {}, [this]() { UpdateStartAnimation(); }, {});
	m_stateMachine.AddState(State::PLAY, {}, [this]() { UpdatePlay(); }, {});
	m_stateMachine.SetState(State::START_ANIMATION);

	// �I�u�W�F�N�g�z�u�f�[�^�ǂݍ���
	auto& dataReader = DataReaderFromUnity::GetInstance();
	dataReader.LoadUnityGameObjectData(object_data_file_path.c_str());

	// �C���X�^���X�̍쐬
	m_pPlayer = std::make_shared<Player>();
	m_pLaserManager = std::make_shared<LaserManager>(m_pPlayer);
	m_pEnemyManager = std::make_shared<EnemyManager>(m_pPlayer, m_pLaserManager);
	m_pPlanetManager = std::make_shared<PlanetManager>();
	m_pCamera = std::make_shared<Camera>(m_pPlayer->GetPos());
	m_pSkyDome = std::make_shared<SkyDome>(m_pCamera->GetPos());
	m_pMeteorManager = std::make_shared<MeteorManager>();
	m_pScreenShaker= std::make_shared<ScreenShaker>(m_pCamera);

	// UI�̃C���X�^���X�̍쐬
	m_pDamageFlash = std::make_shared<DamageFlash>();
	UIManager::GetInstance().AddUI("DamageFlash", m_pDamageFlash, 3, { 0, 0 });
}

// �f�X�g���N�^
Tutorial::~Tutorial()
{
}

// �X�V
void Tutorial::Update()
{
	// �X�V
	m_stateMachine.Update();	// �X�e�[�g�}�V��
	m_pScreenShaker->Update();	// ��ʗh��
	Effekseer3DEffectManager::GetInstance().Update();	// �G�t�F�N�g
	UIManager::GetInstance().Update();	// UI
}

// �X�^�[�g���o�̍X�V
void Tutorial::UpdateStartAnimation()
{
	// �X�V
	m_pPlayer->UpdateStart(m_pCamera->GetPos());	// �v���C���[
	m_pCamera->UpdateStart(m_pPlayer->GetPos());	// �J����
	m_pSkyDome->Update(m_pCamera->GetPos());		// �X�J�C�h�[��
	m_pPlanetManager->UpdateStart(m_pPlayer->GetMoveVec());	// �f��

	// �X�^�[�g���o���I�������v���C���ɑJ��
	if (m_pPlayer->GetIsStartAnimation() &&
		m_pCamera->GetIsStartAnimation())
	{
		m_stateMachine.SetState(State::PLAY);
	}
}

// �v���C���̍X�V
void Tutorial::UpdatePlay()
{
	// �X�V
	m_pPlayer->Update(m_pCamera->GetCameraHorizon());	// �v���C���[
	m_pCamera->Update(m_pPlayer->GetPos());				// �J����
	m_pEnemyManager->Update();							// �G
	m_pLaserManager->Update();							// ���[�U�[
	m_pSkyDome->Update(m_pCamera->GetPos());			// �X�J�C�h�[��
	m_pPlanetManager->Update();							// �f��
	m_pMeteorManager->Update(m_pCamera->GetPos());		// 覐�
	m_pDamageFlash->Update();							// �_���[�W�t���b�V��

	// 覐΂̐���
	m_pMeteorManager->CreateMeteor(120, m_pPlayer->GetPos());

	// �����蔻��
	Collision();
}

// �`��
void Tutorial::Draw()
{
	// ��ʗh��̑O����
	m_pScreenShaker->PreDraw();

	// ��ʂ��N���A
	ClearDrawScreen();

	// �`��
	m_pSkyDome->Draw();			// �X�J�C�h�[��
	m_pPlanetManager->Draw();	// �f��
	m_pMeteorManager->Draw();	// 覐�
	m_pEnemyManager->Draw();	// �G
	m_pPlayer->Draw();			// �v���C���[
	m_pLaserManager->Draw();	// ���[�U�[
	Effekseer3DEffectManager::GetInstance().Draw();	// �G�t�F�N�g
	UIManager::GetInstance().Draw();	// UI

	// ��ʗh��`��
	m_pScreenShaker->Draw();
}

// �����蔻��
void Tutorial::Collision()
{
	// �v���C���[��覐΂̓����蔻��
	for (auto& meteor : m_pMeteorManager->GetMeteor())
	{
		// ���ƃ��b�V���̓����蔻��
		MV1_COLL_RESULT_POLY_DIM result{};
		result = MV1CollCheck_Sphere(				
			meteor->GetModelHandle(), 
			-1, 
			m_pPlayer->GetPos().ToDxLibVector3(),
			m_pPlayer->GetCollsionRadius());

		// �������Ă�����
		if (result.HitNum > 0)
		{
			// �v���C���[�̃_���[�W����
			m_pPlayer->OnDamage(meteor_damage);

			// �_���[�W�t���b�V���̉��o
			m_pDamageFlash->Start(60, 50, 0xff0000);

			// ��ʗh��̉��o
			m_pScreenShaker->StartShake({ meteor_damage * 10.0f, meteor_damage * 10.0f}, 30);
		}
	}
}
