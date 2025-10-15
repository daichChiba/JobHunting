#pragma once
#include "KamataEngine.h"
#include "Scene/manager/SceneID.h"
#include "fade/Fade.h"
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

	void SetFilePath(std::string filePath_) { filePath = filePath_; }
	void SetErea(std::string erea_) { erea = erea_; }
	void SetStage(std::string stage_) { stage = stage_; }
	void SetTitelFilePath(std::string filePath_) { titelFilePath_ = filePath_; }

	std::string GetFilePath() { return filePath; }
	std::string GetErea() { return erea; }
	std::string GetStage() { return stage; }
	std::string GetTitelFilePath() { return titelFilePath_; }

private:
protected:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	std::string filePath = "";
	std::string erea = "";
	std::string stage = "";

	std::string titelFilePath_ = "";

	Fade* fade_ = nullptr;

	bool isStart = false;

	bool isFinish;
};
