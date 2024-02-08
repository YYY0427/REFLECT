#pragma once
#include "../Math/Vector2.h"
#include "../Util/Timer.h"
#include <map>
#include <string>
#include <vector>

// チュートリアルの状態
enum class TutorialState
{
	MOVE,		// 移動
	SHIELD,		// シールド
	REFLECT,	// 反射
	CUBE,		// キューブ
	DAMAGE,		// ダメージ
};

/// <summary>
/// チュートリアルUI
/// </summary>
class TutorialUI
{
public:
	// コンストラクタ
	TutorialUI();

	// デストラクタ
	~TutorialUI();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 状態の設定
	void StartState(TutorialState state);

	// 現在の状態を終了
	void EndState();

	// 状態の取得
	TutorialState GetState() const;
	bool IsEndState(TutorialState state);

private:
	// チュートリアルのデータ
	struct TutorialData
	{
		// スタートしたか
		bool isStart = false;

		// 終了したか
		bool isEnd = false;

		// 画像ハンドル
		std::vector<int> imgHandle;
		int imgIndex = 0;

		// 位置
		Vector2 imgPos;
		Vector2 imgGoalPos;

		// テキスト
		std::string text;

		// アルファ値
		int imgAlpha = 0;
		int textAlpha = 0;
	};

private:
	// チュートリアルの状態
	TutorialState m_state;

	// チュートリアルの画像
	std::map<TutorialState, TutorialData> m_tutorialDataMap;

	// 画像を切り替えるフレーム数
	Timer<int> m_changeImageFrame;
};