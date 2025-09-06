#pragma once
#include "Scene/scenes/GameScene.h"
#include "Scene/scenes/ResetScene.h"
#include "Scene/manager/SceneID.h"
#include <KamataEngine.h>
class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	/// <summary>
	/// シーン切り替え（現在のシーンを破棄して新しいシーンを生成）
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeScene(SceneID nextScene);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui();


private:
	std::unique_ptr<Scene> currentScene_;
	SceneID currentSceneID_;
};
