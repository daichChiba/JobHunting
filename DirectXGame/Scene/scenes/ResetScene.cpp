#include "ResetScene.h"

ResetScene::ResetScene() {

}

ResetScene::~ResetScene() {

}

void ResetScene::Initialize() {

}

void ResetScene::Update() {
	if (input_->GetInstance()->PushKey(DIK_SPACE)) {
		isFinish = true;
		nextScene_ = SceneID::Game;
	}
}

void ResetScene::Draw() {

}

void ResetScene::Delete() {

}

void ResetScene::DrawImGui() {
	ImGui::Begin("ResetScene");
	ImGui::Text("Test");
	ImGui::End();
}

SceneID ResetScene::NextScene() const {
	return nextScene_;
}
