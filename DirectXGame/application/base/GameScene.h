#pragma once
#include "Game/Camera/GameCamera.h"
#include "Game/LoadJsonFile/FileJson.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Object/ObjectManager.h"
#include "Game/Player/PlayerManager.h"
#include "Scene/Scene.h"
#include "Game/Pause/PauseMenu.h"
#include <KamataEngine.h>


/// <summary>
/// ゲームシーンに関する状況を取得し、シーンに反映させるクラス。
/// </summary>
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
	/// <summary>
	/// 次に表示するシーンを示すSceneIDを返す
	/// </summary>
	/// <returns>次のシーンを識別するSceneIDを返す。</returns>
	SceneID NextScene() const override;

	/// <summary>
	/// ゲームが始まっているかどうかを示すisStartを返す
	/// </summary>
	/// <returns>始まっているのであればtrue,始まっていないのであればfalse</returns>
	bool GetIsStart() { return isStart; }

private:

private:
	// プレイヤー
	PlayerManager playerManager_;

	// オブジェクト
	ObjectManager* objectManager_ = nullptr;

	MapChip mapChip_;
	GameCamera* camera_;
	// シーン
	SceneID nextScene_;

	PauseMenu pauseMenu_;

private:


	FileJson::FileAccessor* fileAccessor_ = nullptr;

	const std::string filePath_ = "Resources/Json/GameScene.json";

	int startCount_;
	int count_;
	bool isStart;

	int gameCount_;

	bool isFadeStart;


	uint32_t countTh_[4];
	KamataEngine::Sprite* countSprite_[4];

	KamataEngine::Vector2 guideIconPos_;
	KamataEngine::Vector2 guideIconSize_;


	uint32_t guideIconTh_;
	KamataEngine::Sprite* guideIconSprite_;

};
