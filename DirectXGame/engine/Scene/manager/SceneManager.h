#pragma once
#include "GameScene.h"
#include "Scene/scenes/ResetScene.h"
#include "Scene/scenes/TitleScene.h"
#include "Scene/manager/SceneID.h"
#include "Scene/scenes/DemoScene.h"
#include "Scene/scenes/clearScene.h"
#include <KamataEngine.h>

using SceneCreator = std::function<std::unique_ptr<Scene>()>;
/// <summary>
/// 全てのシーンの情報を管理するクラス
/// シーンに関する情報を統合的に管理し扱う
/// </summary>
class SceneManager {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	SceneManager() ;
	/// <summary>
	/// 
	/// </summary>
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
	void SetInformation();

	void GetInformation();

	std::map<SceneID, SceneCreator> sceneFactory_;

	std::unique_ptr<Scene> currentScene_;
	SceneID currentSceneID_;



	std::string filePath = "Resources/Json/Stage.json";
	std::string erea = "stage_1";
	std::string stage = "1_3";

	std::string titelFilePath = "Resources/Json/Titel.json";
};
