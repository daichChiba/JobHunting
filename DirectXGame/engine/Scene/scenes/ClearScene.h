#pragma once
#include "Scene/Scene.h"
class ClearScene : public Scene {
public:
	/// <summary>
	///
	/// </summary>
	ClearScene();
	/// <summary>
	///
	/// </summary>
	~ClearScene();
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
	uint32_t backScreenTh_;
	uint32_t pushToSpaceTh_;
	uint32_t clearTh_;

	KamataEngine::Sprite* backScreenSpite;
	KamataEngine::Sprite* pushToSpaceSpite;
	KamataEngine::Sprite* clearSpite;

	int buttonCount = 0;
	// 表示させる際の上限
	const int kDrawCount_ = 30;
	// 一秒あたりのフレーム数
	const int kCountFrame_ = 60;

	SceneID nextScene_;
};
