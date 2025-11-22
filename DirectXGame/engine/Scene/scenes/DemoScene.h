#pragma once
#include "Scene/Scene.h"

/// <summary>
/// デモシーンに関する状況を取得しシーンに反映させるクラス
/// シーンクラスを基底クラスにデモシーンを扱う
/// ここではシーン切り替えやステージ選択などを実際にできるかこのクラスを使って確かめる
/// </summary>
class DemoScene : public Scene {
public:
	/// <summary>
	///
	/// </summary>
	DemoScene();
	/// <summary>
	///
	/// </summary>
	~DemoScene();
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

	KamataEngine::Sprite* backScreenSpite;
	KamataEngine::Sprite* pushToSpaceSpite;

	int buttonCount = 0;
	// 表示させる際の上限
	const int kDrawCount_ = 30;
	// 一秒あたりのフレーム数
	const int kCountFrame_ = 60;

	SceneID nextScene_;

};
