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
#include "../Game/Enemy/Normal/EnemyBase.h"
#include <DxLib.h>

namespace
{
	// オブジェクト配置データのファイルパス
	const std::string object_data_file_path = "Test";

	// 隕石に当たっている間にプレイヤーに与えるダメージ
	constexpr int meteor_damage = 2;

	// レーザーに当たっている間にプレイヤーに与えるダメージ
	constexpr int laser_damage = 1;

	// 敵に当たっている間にプレイヤーに与えるダメージ
	constexpr int enemy_damage = 1;
}

// コンストラクタ
Tutorial::Tutorial()
{
	// ステートマシンの設定
	m_stateMachine.AddState(State::START_ANIMATION, {}, [this]() { UpdateStartAnimation(); }, {});
	m_stateMachine.AddState(State::PLAY, {}, [this]() { UpdatePlay(); }, {});
	m_stateMachine.SetState(State::START_ANIMATION);

	// オブジェクト配置データ読み込み
	auto& dataReader = DataReaderFromUnity::GetInstance();
	dataReader.LoadUnityGameObjectData(object_data_file_path.c_str());

	// インスタンスの作成
	m_pPlayer = std::make_shared<Player>();
	m_pLaserManager = std::make_shared<LaserManager>(m_pPlayer);
	m_pEnemyManager = std::make_shared<EnemyManager>(m_pPlayer, m_pLaserManager);
	m_pPlanetManager = std::make_shared<PlanetManager>();
	m_pCamera = std::make_shared<Camera>(m_pPlayer->GetPos());
	m_pSkyDome = std::make_shared<SkyDome>(m_pCamera->GetPos());
	m_pMeteorManager = std::make_shared<MeteorManager>();
	m_pScreenShaker= std::make_shared<ScreenShaker>(m_pCamera);

	// UIのインスタンスの作成
	m_pDamageFlash = std::make_shared<DamageFlash>();
	UIManager::GetInstance().AddUI("DamageFlash", m_pDamageFlash, 3, { 0, 0 });

	// ウェーブデータの読み込み
	m_pEnemyManager->LoadWaveFileData("Test");
}

// デストラクタ
Tutorial::~Tutorial()
{
}

// 更新
void Tutorial::Update()
{
	// 更新
	m_stateMachine.Update();	// ステートマシン
	m_pScreenShaker->Update();	// 画面揺れ
	Effekseer3DEffectManager::GetInstance().Update();	// エフェクト
	UIManager::GetInstance().Update();	// UI
}

// スタート演出の更新
void Tutorial::UpdateStartAnimation()
{
	// 更新
	m_pPlayer->UpdateStart(m_pCamera->GetPos());	// プレイヤー
	m_pCamera->UpdateStart(m_pPlayer->GetPos());	// カメラ
	m_pSkyDome->Update(m_pCamera->GetPos());		// スカイドーム
	m_pPlanetManager->UpdateStart(m_pPlayer->GetMoveVec());	// 惑星

	// スタート演出が終わったらプレイ中に遷移
	if (m_pPlayer->GetIsStartAnimation() &&
		m_pCamera->GetIsStartAnimation())
	{
		m_stateMachine.SetState(State::PLAY);
	}
}

// プレイ中の更新
void Tutorial::UpdatePlay()
{
	static bool isWaveStart = false;
	if(!isWaveStart)
	{
		m_pEnemyManager->StartWave();
		isWaveStart = true;
	}

	// 更新
	m_pPlayer->Update(m_pCamera->GetCameraHorizon());	// プレイヤー
	m_pCamera->Update(m_pPlayer->GetPos());				// カメラ
	m_pEnemyManager->Update();							// 敵
	m_pLaserManager->Update();							// レーザー
	m_pSkyDome->Update(m_pCamera->GetPos());			// スカイドーム
	m_pPlanetManager->Update();							// 惑星
	m_pMeteorManager->Update(m_pCamera->GetPos());		// 隕石
	m_pDamageFlash->Update();							// ダメージフラッシュ

	// 隕石の生成
	m_pMeteorManager->CreateMeteor(120, m_pPlayer->GetPos());

	// 当たり判定
	Collision();
}

// 描画
void Tutorial::Draw()
{
	// 画面揺れの前処理
	m_pScreenShaker->PreDraw();

	// 画面をクリア
	ClearDrawScreen();

	// 描画
	m_pSkyDome->Draw();			// スカイドーム
	m_pPlanetManager->Draw();	// 惑星
	m_pMeteorManager->Draw();	// 隕石
	m_pEnemyManager->Draw();	// 敵
	m_pPlayer->Draw();			// プレイヤー
	m_pLaserManager->Draw();	// レーザー
	Effekseer3DEffectManager::GetInstance().Draw();	// エフェクト
	UIManager::GetInstance().Draw();	// UI

	// 画面揺れ描画
	m_pScreenShaker->Draw();
}

// 当たり判定
void Tutorial::Collision()
{
	// プレイヤーと隕石の当たり判定
	for (auto& meteor : m_pMeteorManager->GetMeteor())
	{
		// 球とメッシュの当たり判定
		MV1_COLL_RESULT_POLY_DIM result{};
		result = MV1CollCheck_Sphere(				
			meteor->GetModelHandle(), 
			-1, 
			m_pPlayer->GetPos().ToDxLibVector3(),
			m_pPlayer->GetCollsionRadius());

		// 当たっていたら
		if (result.HitNum > 0)
		{
			// プレイヤーのダメージ処理
			m_pPlayer->OnDamage(meteor_damage);

			// ダメージフラッシュの演出
			m_pDamageFlash->Start(60, 50, 0xff0000);

			// 画面揺れの演出
			m_pScreenShaker->StartShake({ meteor_damage * 10.0f, meteor_damage * 10.0f}, 30);
		}
		// 当たり判定情報の後始末
		MV1CollResultPolyDimTerminate(result);
	}

	// プレイヤーと敵のレーザーの当たり判定
	for (auto& laser : m_pLaserManager->GetLaserList())
	{
		// 球とメッシュの当たり判定
		MV1_COLL_RESULT_POLY_DIM result{};
		result = MV1CollCheck_Sphere(
			laser.pLaser->GetModelHandle(),
			-1,
			m_pPlayer->GetPos().ToDxLibVector3(),
			m_pPlayer->GetCollsionRadius());

		// 当たっていたら
		if (result.HitNum > 0)
		{
			// プレイヤーのダメージ処理
			m_pPlayer->OnDamage(laser_damage);

			// ダメージフラッシュの演出
			m_pDamageFlash->Start(60, 50, 0xff0000);

			// 画面揺れの演出
			m_pScreenShaker->StartShake({ laser_damage * 10.0f, laser_damage * 10.0f }, 30);
		}
		// 当たり判定情報の後始末
		MV1CollResultPolyDimTerminate(result);
	}

	// プレイヤーと敵の当たり判定
	for (auto& enemy : m_pEnemyManager->GetEnemyList())
	{
		float distance = (enemy->GetPos() - m_pPlayer->GetPos()).Length();
		if (distance < enemy->GetCollisionRadius() + m_pPlayer->GetCollsionRadius())
		{
			// プレイヤーのダメージ処理
			m_pPlayer->OnDamage(enemy_damage);

			// ダメージフラッシュの演出
			m_pDamageFlash->Start(60, 50, 0xff0000);

			// 画面揺れの演出
			m_pScreenShaker->StartShake({ enemy_damage * 10.0f, enemy_damage * 10.0f }, 30);
		}
	}

	// シールドと敵レーザーの当たり判定
	for (auto& laser : m_pLaserManager->GetLaserList())
	{
		// シールドがなければ判定しない
		if (!m_pPlayer->GetShield()->IsShield()) continue;

		// レーザーの種類が反射レーザーなら判定しない
		if (laser.type == LaserType::REFLECT)	continue;

		// シールドの頂点の座標を取得
		Vector3 shieldLeftTopPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[0].pos);
		Vector3 shieldRightTopPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[1].pos);
		Vector3 shieldLeftBottomPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[2].pos);
		Vector3 shieldRightBottomPos = Vector3::FromDxLibVector3(m_pPlayer->GetShield()->GetVertex()[3].pos);

		// シールドは2つのポリゴンからできてるので2つのポリゴンともチェック
		MV1_COLL_RESULT_POLY_DIM result = MV1CollCheck_Triangle(
			laser.pLaser->GetModelHandle(), -1, shieldLeftTopPos.ToDxLibVector3(), shieldRightTopPos.ToDxLibVector3(), shieldLeftBottomPos.ToDxLibVector3());
		MV1_COLL_RESULT_POLY_DIM result2 = MV1CollCheck_Triangle(
			laser.pLaser->GetModelHandle(), -1, shieldRightBottomPos.ToDxLibVector3(), shieldLeftBottomPos.ToDxLibVector3(), shieldRightTopPos.ToDxLibVector3());

		// どっちかのポリゴンが当たっていたら
		if (result.HitNum > 0 || result2.HitNum > 0)
		{
			// レーザーの当たった位置をおおまかに取得
			Vector3 hitPos{};
			if (result.HitNum > 0)
			{
				hitPos = (Vector3::FromDxLibVector3(result.Dim->Position[0]) + 
						  Vector3::FromDxLibVector3(result.Dim->Position[1]) +
						  Vector3::FromDxLibVector3(result.Dim->Position[2])) / 3;
			}
			else
			{
				hitPos = (Vector3::FromDxLibVector3(result2.Dim->Position[0]) +
						  Vector3::FromDxLibVector3(result2.Dim->Position[1]) +
						  Vector3::FromDxLibVector3(result2.Dim->Position[2])) / 3;
			}
			// 敵のレーザーを止める
			laser.pLaser->Stop(hitPos);
		}
	}
}
