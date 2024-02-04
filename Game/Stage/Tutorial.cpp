#include "Tutorial.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../UI/UIManager.h"
#include "../UI/DamageFlash.h"
#include "../Effect/ScreenShaker.h"
#include "../Effect/Effekseer3DEffectManager.h"
#include "../Game/Player.h"
#include "../Game/Camera.h"
#include "../Game/SkyDome.h"
#include "../Game/Shield.h"
#include "../Game/MeteorManager.h"
#include "../Game/PlanetManager.h"
#include "../Game/Laser/LaserManager.h"
#include "../Game/Laser/LaserBase.h"
#include "../Game/Enemy/EnemyManager.h"
#include "../Game/Enemy/EnemyBase.h"
#include "../Score/Score.h"
#include "../String/MessageManager.h"
#include <DxLib.h>

namespace
{
	// �I�u�W�F�N�g�z�u�f�[�^�̃t�@�C���p�X
	const std::string object_data_file_path = "Test";

	// �_���[�W
	constexpr int meteor_damage = 2; // 覐΂ɓ������Ă���ԂɃv���C���[�ɗ^����_���[�W
	constexpr int laser_damage = 1;  // ���[�U�[�ɓ������Ă���ԂɃv���C���[�ɗ^����_���[�W
	constexpr int enemy_damage = 1;  // �G�ɓ������Ă���ԂɃv���C���[�ɗ^����_���[�W
	constexpr int boss_reflect_laser_damage = 2; // ���˃��[�U�[�ɓ������Ă���ԂɃ{�X�ɗ^����_���[�W
}

// �R���X�g���N�^
Tutorial::Tutorial(SceneManager& manager) :
	StageBase(manager)
{
	// �X�e�[�g�}�V���̐ݒ�
	m_stateMachine.AddState(State::START_ANIMATION, {}, [this]() { UpdateStartAnimation(); }, {});
	m_stateMachine.AddState(State::PLAY, {}, [this]() { UpdatePlay(); }, {});
	m_stateMachine.AddState(State::GAME_CLEAR, {}, [this]() { UpdateGameClear(); }, {});
	m_stateMachine.AddState(State::RESULT, {}, [this]() { UpdateResult(); }, {});
	m_stateMachine.SetState(State::START_ANIMATION);

	// �I�u�W�F�N�g�z�u�f�[�^�ǂݍ���
	auto& dataReader = DataReaderFromUnity::GetInstance();
	dataReader.LoadUnityGameObjectData(object_data_file_path.c_str());

	// �X�R�A�̃C���X�^���X����
	auto& score = Score::GetInstance();

	// �C���X�^���X�̍쐬
	m_pPlayer = std::make_shared<Player>(object_data_file_path);
	m_pLaserManager = std::make_shared<LaserManager>(m_pPlayer);
	m_pPlanetManager = std::make_shared<PlanetManager>(object_data_file_path);
	m_pCamera = std::make_shared<Camera>(m_pPlayer->GetPos());
	m_pSkyDome = std::make_shared<SkyDome>(m_pCamera->GetPos());
	m_pMeteorManager = std::make_shared<MeteorManager>(object_data_file_path);
	m_pScreenShaker= std::make_shared<ScreenShaker>(m_pCamera);
	m_pEnemyManager = std::make_shared<EnemyManager>(m_pPlayer, m_pLaserManager, m_pScreenShaker);

	// UI�̃C���X�^���X�̍쐬
	m_pDamageFlash = std::make_shared<DamageFlash>();
	UIManager::GetInstance().AddUI("DamageFlash", m_pDamageFlash, 3, { 0, 0 });

	// �E�F�[�u�f�[�^�̓ǂݍ���
	m_pEnemyManager->LoadWaveFileData("Test");
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
	Effekseer3DEffectManager::GetInstance().Update();	// �G�t�F�N�g
	UIManager::GetInstance().Update();					// UI
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
	static bool isWaveStart = false;
	if(!isWaveStart)
	{
		m_pEnemyManager->StartWave();
		isWaveStart = true;
	}

	// �X�V
	m_pPlayer->Update(m_pCamera->GetCameraHorizon());	// �v���C���[
	m_pCamera->UpdatePlay(m_pPlayer->GetPos());				// �J����
	m_pEnemyManager->Update();							// �G
	m_pLaserManager->Update();							// ���[�U�[
	m_pSkyDome->Update(m_pCamera->GetPos());			// �X�J�C�h�[��
	m_pPlanetManager->Update();							// �f��
	m_pMeteorManager->Update(m_pCamera->GetPos());		// 覐�
	m_pDamageFlash->Update();							// �_���[�W�t���b�V��
	m_pScreenShaker->Update();							// ��ʗh��

	// 覐΂̐���
//	m_pMeteorManager->CreateMeteor(120, m_pPlayer->GetPos());

	// �����蔻��
	Collision();

	// �{�X�����񂾂�Q�[���N���A�ɑJ��
	if (m_pEnemyManager->IsDeadBoss())
	{
		m_stateMachine.SetState(State::GAME_CLEAR);
	}
}

// �Q�[���N���A�̍X�V
void Tutorial::UpdateGameClear()
{
	m_stateMachine.SetState(State::RESULT);
}

// ���U���g�̍X�V
void Tutorial::UpdateResult()
{
	StageBase::UpdateResult("Tutorial", "UNKO");
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
	m_pLaserManager->Draw();	// ���[�U�[
	m_pPlayer->Draw();								// �v���C���[
	Effekseer3DEffectManager::GetInstance().Draw();	// �G�t�F�N�g
	m_pPlayer->DrawShield();						// �V�[���h
	UIManager::GetInstance().Draw();				// UI
	Score::GetInstance().DrawScore();				// �X�R�A

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

		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}

	// �V�[���h�ƓG���[�U�[�̓����蔻��
	for (auto& laser : m_pLaserManager->GetLaserList())
	{
		// ���[�U�[�̎�ނ����˃��[�U�[�Ȃ画�肵�Ȃ�
		if (laser.type == LaserType::REFLECT)	continue;

		if (!m_pPlayer->GetShield()->IsShield())
		{
			// ���[�U�[�����ɖ߂�
			laser.pLaser->UndoReflect();

			// �V�[���h���Ȃ���Δ��肵�Ȃ�
			continue;
		}

		// �V�[���h�̒��_�̍��W���擾
		Vector3 shieldLeftTopPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[0].pos);
		Vector3 shieldRightTopPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[1].pos);
		Vector3 shieldLeftBottomPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[2].pos);
		Vector3 shieldRightBottomPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[3].pos);

		// �V�[���h��2�̃|���S������ł��Ă�̂�2�̃|���S���Ƃ��`�F�b�N
		HITRESULT_LINE result = HitCheck_Line_Triangle(
			laser.pLaser->GetPos().ToDxLibVector3(), laser.pLaser->GetEndPos().ToDxLibVector3(),
			shieldLeftTopPos.ToDxLibVector3(), shieldRightTopPos.ToDxLibVector3(), shieldLeftBottomPos.ToDxLibVector3());

		HITRESULT_LINE result2 = HitCheck_Line_Triangle(
			laser.pLaser->GetPos().ToDxLibVector3(), laser.pLaser->GetEndPos().ToDxLibVector3(),
			shieldRightBottomPos.ToDxLibVector3(), shieldLeftBottomPos.ToDxLibVector3(), shieldRightTopPos.ToDxLibVector3());

		// �ǂ������̃|���S�����������Ă�����
		if (result.HitFlag || result2.HitFlag)
		{
			// ���˃��[�U�[�̔��ˈʒu���擾
			Vector3 firePos{};
			if(result.HitFlag)	firePos = Vector3::FromDxLibVector3(result.Position);
			else				firePos = Vector3::FromDxLibVector3(result2.Position);

			// �܂����˃��[�U�[���Ȃ���Δ��˃��[�U�[��ǉ�
			if (!laser.pLaser->IsReflect())
			{
				// ���˃��[�U�[��ǉ�
				int key = m_pLaserManager->AddReflectLaser(m_pPlayer->GetShield(), laser.pLaser, firePos);
				laser.pLaser->SetReflectLaserKey(key);
			}
			// ���ɔ��˃��[�U�[������Δ��˃��[�U�[�̈ʒu��ݒ�
			else
			{
				// ���˃��[�U�[�̈ʒu��ݒ�
				m_pLaserManager->SetLaserPosition(laser.pLaser->GetReflectLaserKey(), firePos);
			}

			// �G�̃��[�U�[���~�߂�
			laser.pLaser->Reflect(m_pPlayer->GetShield()->GetPos());

			// �v���C���[�̔��ˏ���
		//	m_pPlayer->OnReflect();
		}
	}

	// �v���C���[�ƓG�̃��[�U�[�̓����蔻��
	for (auto& laser : m_pLaserManager->GetLaserList())
	{
		// ���˒����[�U�[�Ȃ画�肵�Ȃ�
		if(laser.pLaser->IsReflect()) continue;	

		// ���[�U�[�̎�ނ����˃��[�U�[�Ȃ画�肵�Ȃ�
		if (laser.type == LaserType::REFLECT)	continue;

		// ���ƃ��b�V���̓����蔻��
		MV1_COLL_RESULT_POLY_DIM result{};
		result = MV1CollCheck_Sphere(
			laser.pLaser->GetModelHandle(),
			-1,
			m_pPlayer->GetPos().ToDxLibVector3(),
			m_pPlayer->GetCollsionRadius());

		// �������Ă�����
		if (result.HitNum > 0)
		{
			// �v���C���[�̃_���[�W����
			m_pPlayer->OnDamage(laser_damage);

			// �_���[�W�t���b�V���̉��o
			m_pDamageFlash->Start(60, 50, 0xff0000);

			// ��ʗh��̉��o
			m_pScreenShaker->StartShake({ laser_damage * 10.0f, laser_damage * 10.0f }, 30);

			// �������Ă������[�U�[���ʏ�̃��[�U�[�Ȃ�
			if (laser.type == LaserType::NORMAL)
			{
				// ���[�U�[���~�߂�
				laser.pLaser->Stop(m_pPlayer->GetPos());
			}
		}
		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}

	// ���˂������[�U�[�ƓG�̓����蔻��
	for (auto& laser : m_pLaserManager->GetLaserList())
	{
		// ���˒����[�U�[�łȂ���Δ��肵�Ȃ�
		if(laser.type != LaserType::REFLECT) continue;

		// �G���G
		for (auto& enemy : m_pEnemyManager->GetEnemyList())
		{
			// ���ƃ��b�V���̓����蔻��
			MV1_COLL_RESULT_POLY_DIM result{};
			result = MV1CollCheck_Sphere(
				laser.pLaser->GetModelHandle(),
				-1,
				enemy->GetPos().ToDxLibVector3(),
				enemy->GetCollisionRadius());

			// �������Ă�����
			if (result.HitNum > 0)
			{
				// �G�Ƀ_���[�W����
				enemy->OnDamage(1000, Vector3::FromDxLibVector3(result.Dim->HitPosition));
			}
			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
		}
		// �{�X
		if (m_pEnemyManager->GetBossEnemy())
		{
			MV1_COLL_RESULT_POLY_DIM result{};
			result = MV1CollCheck_Sphere(
				laser.pLaser->GetModelHandle(),
				-1,
				m_pEnemyManager->GetBossEnemy()->GetPos().ToDxLibVector3(),
				m_pEnemyManager->GetBossEnemy()->GetCollisionRadius());

			// �������Ă�����
			if (result.HitNum > 0)
			{
				// �{�X�Ƀ_���[�W����
				m_pEnemyManager->GetBossEnemy()->OnDamage(
					boss_reflect_laser_damage, Vector3::FromDxLibVector3(result.Dim->HitPosition));
			}
			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
		}
	}

	// �v���C���[�ƓG�̓����蔻��
	for (auto& enemy : m_pEnemyManager->GetEnemyList())
	{
		// ���Ƌ��̓����蔻��
		float distance = (enemy->GetPos() - m_pPlayer->GetPos()).Length();
		if (distance < enemy->GetCollisionRadius() + m_pPlayer->GetCollsionRadius())
		{
			// �v���C���[�̃_���[�W����
			m_pPlayer->OnDamage(enemy_damage);

			// �_���[�W�t���b�V���̉��o
			m_pDamageFlash->Start(60, 50, 0xff0000);

			// ��ʗh��̉��o
			m_pScreenShaker->StartShake({ enemy_damage * 10.0f, enemy_damage * 10.0f }, 30);
		}
	}
}
