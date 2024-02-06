#include "SkyDome.h"
#include "../Model.h"
#include "../ModelHandleManager.h"
#include <string>

namespace
{
	// モデルの拡大率
	const Vector3 model_scale = { 100, 100, 100 };
}

// コンストラクタ
SkyDome::SkyDome(Vector3 pos) :
	m_pos(pos)
{
	// モデルのインスタンスの作成
	m_pModel = std::make_unique<Model>(ModelHandleManager::GetInstance().GetHandle(ModelType::SKYDOME));

	// モデルの位置を設定
	m_pModel->SetPos(m_pos);

	// モデルの回転を設定
	m_pModel->SetRot({ 0, 0, 0 });

	// モデルの拡大率を設定
	m_pModel->SetScale(model_scale);
}

// デストラクタ
SkyDome::~SkyDome()
{
}

// 更新
void SkyDome::Update(Vector3 pos)
{
	m_pos = pos;
	m_pModel->SetPos(m_pos);
}

// 描画
void SkyDome::Draw()
{
	m_pModel->Draw();
}