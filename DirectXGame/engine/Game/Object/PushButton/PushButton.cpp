#include "PushButton.h"
#include "engine/Game/MapChip/MapChip.h"

using namespace KamataEngine;

PushButton::PushButton() {
	//
}

PushButton::~PushButton() {
	//
}

void PushButton::Initilize(MapChip* mapChip_) {
	isPushButton = false;

	model_[0] = Model::CreateFromOBJ("PushButton", true);
	model_[1] = Model::CreateFromOBJ("PressButton", true);

	
	//
	worldTransform_.Initialize();
	worldTransform_.translation_ = mapChip_->GetObjectPos(MapChipID::Button);

}

void PushButton::Update() {
	worldTransform_.UpdateMatrix();
	//
}
void PushButton::Draw(Camera& camera_) {

	if (isPushButton) {
		model_[1]->Draw(worldTransform_, camera_);
	} else {
		model_[0]->Draw(worldTransform_, camera_);
	}
	//
}

void PushButton::DrawImGui() {
	//
	ImGui::Begin("PushButton");
	ImGui::Text("test");
	ImGui::Checkbox("isPushButton", &isPushButton);
	ImGui::End();
}
void PushButton::Delete() {
	//

	delete model_[0];
	delete model_[1];
}

Vector3 PushButton::GetWorldPos() {
	//
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB PushButton::GetAABB() {
	//
	Vector3 worldPos = GetWorldPos();

	AABB aabb;

	aabb.min = {worldPos.x - size_.x / 2.0f, worldPos.y - size_.y / 2.0f, worldPos.z - size_.x / 2.0f};
	aabb.max = {worldPos.x + size_.x / 2.0f, worldPos.y + size_.y / 2.0f, worldPos.z + size_.x / 2.0f};

	return aabb;
}

void PushButton::OnCollision(const Player* player) {
	//
	(void)player;
	isPushButton = true;
}

