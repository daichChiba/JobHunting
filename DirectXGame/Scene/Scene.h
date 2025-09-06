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

private:

protected:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	

	bool isFinish;
};
