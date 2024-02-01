#include "TestScene.h"
#include "../Application.h"
#include "../Transitor/TileTransitor.h"
#include "../Transitor/FadeTransitor.h"
#include "../Transitor/IrisTransitor.h"
#include "../Transitor/WipeTransitor.h"
#include "../Transitor/PushTransitor.h"
#include "../Transitor/StripTransitor.h"
#include "../UI/Warning.h"
#include "DxLib.h"

namespace
{
	constexpr int kStretchWindowWidth = 640;
	constexpr int kStretchWindowHeight = 180;
}

// コンストラクタ
TestScene::TestScene(SceneManager& manager) :
	SceneBase(manager)
{
	// 画面切り替え演出の設定
	m_pTransitor = std::make_unique<StripTransitor>();
	m_pTransitor->Start();

	// 警告UIの設定
	m_pWarning = std::make_unique<Warning>(200);
}

// デストラクタ
TestScene::~TestScene()
{
}

// 更新
void TestScene::Update()
{
	// 画面切り替え演出の更新
	m_pTransitor->Update();

	// 警告UIの更新
	m_pWarning->Update();
}

// 描画
void TestScene::Draw()
{
	// 画面をクリア
	ClearDrawScreen();

	// 背景の描画
	const auto& size = Application::GetInstance().GetWindowSize();
	DrawBox(0, 0, size.width, size.height, 0x000000, true);

	// 警告UIの描画
	m_pWarning->Draw();

	// 画面切り替え演出の描画
	m_pTransitor->Draw();
}
