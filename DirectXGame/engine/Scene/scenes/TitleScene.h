#pragma once
#include "../../Game/LoadJsonFile/FileJson.h"
#include "../Scene.h"
/// <summary>
/// タイトルシーンに関する状況を取得しシーンに反映させるクラス
/// シーンクラスを基底クラスにタイトルシーンを扱う
/// </summary>
class TitleScene : public Scene {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	TitleScene();
	/// <summary>
	///
	/// </summary>
	~TitleScene();
	/// <summary>
	///
	/// </summary>
	void Initialize() override;
	/// <summary>
	///
	/// </summary>
	void Update() override;
	/// <summary>
	///
	/// </summary>
	void Draw() override;
	/// <summary>
	///
	/// </summary>
	void Delete() override;
	/// <summary>
	///
	/// </summary>
	void DrawImGui() override;
	/// <summary>
	/// 次に表示するシーンを示すSceneIDを返す
	/// </summary>
	/// <returns>次のシーンを識別するSceneIDを返す。</returns>
	SceneID NextScene() const override;

private:
private:
	SceneID nextScene_;

	uint32_t backScreenTh_;
	uint32_t titelTh_;
	//uint32_t pushToSpaceTh_;

	KamataEngine::Sprite* backScreenSpite;
	//KamataEngine::Sprite* titelSpite;
	//KamataEngine::Sprite* pushToSpaceSpite;

	KamataEngine::Model* titleModel;
	KamataEngine::Model* pushSpaceModel;

	KamataEngine::Vector2 backScreenPos;
	KamataEngine::Vector3 titelPos;
	KamataEngine::Vector3 pushToSpacePos;
	KamataEngine::Vector2 stopTitelPos;

	FileJson::FileAccessor* fileAccessor_;
	std::string file = "Resources/Json/Titel.json";
	std::string fileMain = "title";

	KamataEngine::WorldTransform worldTransform_[2];

	KamataEngine::Camera camera_;

	bool isJump = false;

	bool isMove = true;

	int jumpCount = 0;

	int buttonCount = 0;
	// 表示させる際の上限
	const int kDrawCount_ = 30;
	// 一秒あたりのフレーム数
	const int kCountFrame_ = 60;

	const int kJumpCount = 60;
	const int kResetCount = 0;
	float resetSpeed;

	float speed;

	float fadeTime_ = 1.0f;

	// タイトルシーン開始直後の誤入力を防ぐためのタイマー
	// 0より大きい間は入力を受け付けない
	int inputWaitTimer_ = 0;

	// タイトルシーンが有効（入力を受け付け可能）かどうか
	// trueになったらボタン判定を開始する
	bool canAcceptInput_ = false;
};
