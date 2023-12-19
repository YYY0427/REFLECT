#pragma once
#include "SceneBase.h"

/// <summary>
/// デバッグシーン
/// このシーンから全てのシーンに遷移できる
/// </summary>
class DebugScene : public SceneBase
{
public:
	 /// </summary>
	 /// コンストラクタ
	 /// </summary>
	 /// <param name="manager">シーンマネージャーの参照</param>
	 DebugScene(SceneManager& manager);
	 
	 // デストラクタ
	 ~DebugScene();
	 
	 // 更新
	 void Update() override;
	 
	 // 描画
	 void Draw() override;
};