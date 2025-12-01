#pragma once
#include "Game/Camera/GameCamera.h"
#include "Game/MapChip/MapChip.h"
//#include "Game/Object/Goal/Goal.h"
#include "Game/Player/Player.h"
#include "Scene/Scene.h"
#include "Game/Manager/ObjectManager.h"
/// <summary>
/// ゲームシーンに関する状況を取得し、シーンに反映させるクラス。
/// 
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
	//void CheckAllCollisions(Player* player);

private:
	//プレイヤー
	Player player_;
	//オブジェクト
	//Goal goal_;
	ObjectManager* objectManager_ = nullptr;

	MapChip mapChip_;
	GameCamera* camera_;
	//シーン
	SceneID nextScene_;
private:

	int startCount_;
	int count_;
	bool isStart;

	int gameCount_;

	bool isFadeStart;

	uint32_t countTh_[4];
	KamataEngine::Sprite* countSprite_[4];
};
