#pragma once
#include "../../Game/LoadJsonFile/FileJson.h"
#include "../Scene.h"
class TitleScene : public Scene {
public:
	TitleScene();
	~TitleScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Delete() override;
	void DrawImGui() override;
	SceneID NextScene() const override;

private:
	KamataEngine::Vector2 ChangeToVector2(std::string stringPos);

private:
	SceneID nextScene_;

	uint32_t backScreenTh_;
	uint32_t titelTh_;
	uint32_t pushToSpaceTh_;

	KamataEngine::Sprite* backScreenSpite;
	KamataEngine::Sprite* titelSpite;
	KamataEngine::Sprite* pushToSpaceSpite;

	KamataEngine::Vector2 backScreenPos;
	KamataEngine::Vector2 titelPos;
	KamataEngine::Vector2 pushToSpacePos;
	KamataEngine::Vector2 stopTitelPos;

	FileJson::FileAccessor* fileAccessor_;
	// std::string file = "../../Resources/Json/Titel.json";
	std::string fileMain = "title";

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
};
