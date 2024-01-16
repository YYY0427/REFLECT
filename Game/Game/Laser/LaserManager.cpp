#include "LaserManager.h"
#include "LaserBase.h"
#include "NormalLaser.h"
#include "../../Util/DrawFunctions.h"
#include <cassert>
#include <string>

namespace
{
	// 通常レーザーのモデルファイルパス
	const std::string normal_laser_model_file_path = "Data/Model/Laser.mv1";	
} 

// コンストラクタ
LaserManager::LaserManager(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// モデルの読み込み
	m_modelHandleTable[LaserType::NORMAL] = my::MyLoadModel(normal_laser_model_file_path.c_str());
}

// デストラクタ
LaserManager::~LaserManager()
{
}

// 更新
void LaserManager::Update()
{
	// 不要になったレーザーの削除
	m_pLaserList.remove_if([](LaserData data) { return !data.pLaser->IsEnabled(); });

	// レーザーの更新
	for (auto& laser : m_pLaserList)
	{
		laser.pLaser->Update();
	}
}

// 描画
void LaserManager::Draw()
{
	for (auto& laser : m_pLaserList)
	{
		laser.pLaser->Draw();
	}
}

// レーザーの追加
void LaserManager::AddLaser(LaserType type, std::shared_ptr<EnemyBase> pEnemy, int laserFireFrame, float laserSpeed, bool isPlayerFollowing)
{
	LaserData laserData;
	laserData.type = type;

	// レーザーの種類によって処理を分岐
	switch (laserData.type)
	{
	case LaserType::NORMAL:
		laserData.pLaser = std::make_shared<NormalLaser>(
			m_modelHandleTable[LaserType::NORMAL],
			pEnemy, m_pPlayer, laserFireFrame, laserSpeed, isPlayerFollowing);
		break;
	default:
		assert(!"レーザーの種類がありません");
	}
}

// レーザーの取得	
const std::list<LaserData>& LaserManager::GetLaserList() const
{
	return m_pLaserList;
}