#include "PlayerClone.h"
using namespace KamataEngine;

PlayerClone::PlayerClone() {}

PlayerClone::~PlayerClone() {}

void PlayerClone::Initialize() {
	//
	model_ = Model::CreateFromOBJ("Player", true);

	worldTransform_.Initialize();
}

void PlayerClone::Update() {
	//
	worldTransform_.UpdateMatrix();
}

void PlayerClone::Draw(Camera& camera_) {
	//
	model_->Draw(worldTransform_, camera_);
}

void PlayerClone::Delete() {
	//
}

void PlayerClone::DrawImGui() {
	//
#ifdef _DEBUG

	ImGui::Begin("PlayerClone");
	ImGui::Text("test");
	ImGui::End();
#endif // _DEBUG

}
