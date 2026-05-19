#pragma once
#include "KamataEngine.h"
#include "Scene/manager/SceneID.h"
#include "fade/Fade.h"

/// <summary>
/// 全てのシーンに関する基本情報を取り扱うクラス。
/// シーンに関する情報を統合的に扱う
/// </summary>
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

	/// <summary>
	/// 終了したら次に遷移するシーンID
	/// </summary>
	/// <returns>次のシーンのSceneIDを返す</returns>
	virtual SceneID NextScene() const = 0;


	// シーン終了
	bool IsFinish() { return isFinish; }

	void SetFilePath(std::string filePath_) { filePath = filePath_; }
	void SetErea(std::string erea_) { erea = erea_; }
	void SetStage(std::string stage_) { stage = stage_; }

	std::string GetFilePath() { return filePath; }
	std::string GetErea() { return erea; }
	std::string GetStage() { return stage; }

private:
protected:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	XINPUT_VIBRATION xVibration_;

	std::string filePath = "";
	std::string erea = "";
	std::string stage = "";


	Fade* fade_ = nullptr;

	bool isStart = false;

	bool isFinish;

	bool isCleck ;
};
