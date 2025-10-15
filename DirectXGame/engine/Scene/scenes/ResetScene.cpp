#include "ResetScene.h"

ResetScene::ResetScene() {}

ResetScene::~ResetScene() {}

void ResetScene::Initialize() {}

void ResetScene::Update() {
	if (input_->GetInstance()->ReleseKey(DIK_SPACE)) {
		isFinish = true;
		nextScene_ = SceneID::Game;
	}
}

void ResetScene::Draw() {}

void ResetScene::Delete() {}

void ResetScene::DrawImGui() {
#ifdef _DEBUG

	ImGui::Begin("ResetScene");
	ImGui::Text("Test");
	ImGui::End();
#endif // _DEBUG
}

SceneID ResetScene::NextScene() const { return nextScene_; }
