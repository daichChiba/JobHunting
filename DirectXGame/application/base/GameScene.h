#pragma once
#include "Scene/Scene.h"
#include "Game/Player/Player.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Camera/GameCamera.h"

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

	MapChip mapChip_;

private:
	GameCamera* camera_;
};
