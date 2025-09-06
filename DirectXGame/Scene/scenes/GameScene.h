#pragma once
#include "../Scene.h"
#include "Game/Player/Player.h"
#include "Game/Stage/StageManager.h"
#include "Game/Stage/StageID.h"

class GameScene : public Scene {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 削除
	/// </summary>
	void Delete() override;
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui() override;
	SceneID NextScene() const override;

private:
	Player player_;
	SceneID nextScene_;

	StageManager* stageManager_;

	int ereaNum = 1;
	int stageNum = 1;
	std::string stage = "Tutorial";

private:
	KamataEngine::Camera* camera_;
};
