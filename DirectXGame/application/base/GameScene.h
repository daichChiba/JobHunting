#pragma once
#include "Game/Camera/GameCamera.h"
#include "Game/LoadJsonFile/FileJson.h"
#include "Game/MapChip/MapChip.h"
// #include "Game/Object/Goal/Goal.h"
// #include "Game/Player/Player.h"
// #include "Game/Player/Clone/PlayerClone.h"
#include "Game/Object/ObjectManager.h"
#include "Game/Player/PlayerManager.h"
#include "Scene/Scene.h"
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

private:
	FileJson::FileAccessor* fileAccessor_ = nullptr;

	const std::string filePath_ = "Resources/Json/GameScene.json";

	int startCount_;
	int count_;
	bool isStart;

	int gameCount_;

	bool isFadeStart;

	bool isGuide = false;

	bool isPause_ = false;

	uint32_t countTh_[4];
	KamataEngine::Sprite* countSprite_[4];

	KamataEngine::Vector2 guidePos_;
	KamataEngine::Vector2 guideSize_;
	KamataEngine::Vector2 guideIconPos_;
	KamataEngine::Vector2 guideIconSize_;
	KamataEngine::Vector2 pauseBackScreenPos_;
	KamataEngine::Vector2 pauseBackScreenSize_;
	KamataEngine::Vector4 pauseBackScreenColor_;
	KamataEngine::Vector2 gameButtonPos_;
	KamataEngine::Vector2 gameButtonSize_;
	KamataEngine::Vector2 guideButtonPos_;
	KamataEngine::Vector2 guideButtonSize_;
	KamataEngine::Vector2 titelButtonPos_;
	KamataEngine::Vector2 titelButtonSize_;


	uint32_t guideTh_;
	KamataEngine::Sprite* guideSprite_;
	uint32_t guideIconTh_;
	KamataEngine::Sprite* guideIconSprite_;

	uint32_t pauseBackScreenTh_;
	KamataEngine::Sprite* pauseBackScreenSprite_;

	uint32_t returnGameButtonTh_;
	KamataEngine::Sprite* returnGameButtonSprite_;
	uint32_t guideButtonTh_;
	KamataEngine::Sprite* guideButtonSprite_;
	uint32_t titelButtonTh_;
	KamataEngine::Sprite* titelButtonSprite_;


	int pauseCursor_ = 0;
	int pauseCursorMin;
	int pauseCursorMax;

	// enum class Pause {
	//	ReturnGame,
	//	Guide,
	//	Titel
	// };
	// Pause PauseID = Pause::ReturnGame;
};
