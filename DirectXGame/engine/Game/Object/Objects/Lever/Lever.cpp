#include "Lever.h"
#include "engine/Game/MapChip/MapChip.h"
#include "Game/Player/Player.h"
#include "Game/Player/PlayerManager.h"
#include "ect/MathUtilityForText.h"

using namespace KamataEngine;
Lever::Lever() {
	//
}

Lever::~Lever() {
	//
}

void Lever::Initialize(const KamataEngine::Vector3 pos) {
	//

	model_[0] = Model::CreateFromOBJ("LeverRight", true);
	model_[1] = Model::CreateFromOBJ("LeverLeft", true);

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void Lever::Update() {
	//
	worldTransform_.UpdateMatrix();
}

void Lever::Draw(Camera& camera_) {
	//
	if (isLever) {
		model_[1]->Draw(worldTransform_, camera_);
	} else {
		model_[0]->Draw(worldTransform_, camera_);
	}
}

void Lever::DrawImGui(const std::string& label) {
	//
	label;
#ifdef _DEBUG
	if (ImGui::TreeNode(label.c_str())) {
		ImGui::Text("test");
		ImGui::Checkbox("isLever", &isLever);
		ImGui::TreePop();
	}
#endif // _DEBUG
}

void Lever::Delete() {
	//
	delete model_[0];
	delete model_[1];
}

Vector3 Lever::GetWorldPos() {
	//
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Lever::GetAABB() {
	//
	Vector3 worldPos = GetWorldPos();

	AABB aabb;

	aabb.min = {worldPos.x - size_.x / 2.0f, worldPos.y - size_.y / 2.0f, worldPos.z - size_.x / 2.0f};
	aabb.max = {worldPos.x + size_.x / 2.0f, worldPos.y + size_.y / 2.0f, worldPos.z + size_.x / 2.0f};

	return aabb;
}

void Lever::CheckCollision(PlayerManager* playerManager) {
	//
	playerManager;
}

//void Lever::OnCollision(const Player* player, const PlayerClone* clone) {
//	(void)player;
//	(void)clone;
//	isLever = true;
//}