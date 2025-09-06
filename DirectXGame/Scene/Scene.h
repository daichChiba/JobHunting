#pragma once
#include "KamataEngine.h"
#include "Scene/manager/SceneID.h"
class Scene {
public:
	virtual ~Scene() = default;

	/// <summary>
	/// Sceneクラスのセットアップ
	/// </summary>
	void SetUp();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// 削除
	/// </summary>
	virtual void Delete();
	/// <summary>
	/// ImGui描画
	/// </summary>
	virtual void DrawImGui();

	// 追加：終了したら次に遷移するシーンID
	virtual SceneID NextScene() const = 0;

	// シーン終了
	bool IsFinish() { return isFinish; }

	// setter
	void SetEreaNum(int num) { ereaNum = num; }
	void SetStageNum(int num) { stageNum = num; }
	void SetStage(std::string str) { stage = str; }

	// getter
	int GetEreaNum() { return ereaNum; }
	int GetStageNum() { return stageNum; }
	std::string GetStage() { return stage; }

private:
protected:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// stageの数値と文字列
	int ereaNum = 1;
	int stageNum = 1;
	std::string stage = "Tutorial";

	bool isFinish;
};
