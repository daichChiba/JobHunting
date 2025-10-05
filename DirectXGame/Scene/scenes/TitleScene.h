#pragma once
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
	SceneID nextScene_;

	uint32_t backScreenTh_;
	uint32_t titelTh_;
	uint32_t pushToSpaceTh_;

	KamataEngine::Sprite* backScreenSpite;
	KamataEngine::Sprite* titelSpite;
	KamataEngine::Sprite* pushToSpaceSpite;

	
};
