#pragma once
#include "StageBase.h"
#include "../StateMachine.h"
#include <string>
#include <memory>

// プロトタイプ宣言
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

/// <summary>
/// チュートリアルステージクラス
/// </summary>
class Tutorial final : public StageBase
{
public:
	// コンストラクタ
	Tutorial(SceneManager& manager);

	// デストラクタ
	~Tutorial();

	// 開始
	void EntarResult();

	// 更新
	void Update() override final;
	void UpdateStartAnimation();
	void UpdatePlay();
	void UpdateGameClear();
	void UpdateGameOver();
	void UpdateResult();

	// 描画
	void Draw() override final;

	// 当たり判定
	void Collision();

private:
	// 状態
	enum class State
	{
		START_ANIMATION,	// スタート演出
		PLAY,				// プレイ中
		GAME_CLEAR,			// ゲームクリア
		GAME_OVER,			// ゲームオーバー
		RESULT,				// リザルト
		NUM					// 状態の数
	};

private:
	// ステートマシン
	StateMachine<State> m_stateMachine;

	// ポインタ
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
};