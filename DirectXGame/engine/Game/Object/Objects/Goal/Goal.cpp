#include "Goal.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Player/Player.h"
#include "Game/Player/PlayerManager.h"
#include "ect/MathUtilityForText.h"

using namespace KamataEngine;
using namespace MathUtility;
Goal::Goal() {}
//Goal::~Goal() {}

void Goal::Initialize(const KamataEngine::Vector3& pos) {
	model_ = Model::CreateFromOBJ("Portal", true);

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = Vector3(0.5f, 0.5f, 1.0f);
}
void Goal::Update() {
	//

	worldTransform_.UpdateMatrix();
}
void Goal::Draw(Camera& camera_) {
	//
	model_->Draw(worldTransform_, camera_);
}
void Goal::Delete() {
	//
	delete model_;
	model_ = nullptr;
}
void Goal::DrawImGui(const std::string& label) {
	//
#ifdef _DEBUG
	(void)label;
	AABB aabb = GetAABB();
	ImGui::Begin("Goal");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::DragFloat3("max", &aabb.max.x);
	ImGui::DragFloat3("min", &aabb.min.x);
	ImGui::End();

#endif // _DEBUG
}

Vector3 Goal::GetWorldPos() {
	//
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Goal::GetAABB() {
	//
	Vector3 worldPos = GetWorldPos();

	AABB aabb;

	aabb.min = {worldPos.x - size_.x / 2.0f, worldPos.y - size_.y / 2.0f, worldPos.z - size_.x / 2.0f};
	aabb.max = {worldPos.x + size_.x / 2.0f, worldPos.y + size_.y / 2.0f, worldPos.z + size_.x / 2.0f};

	return aabb;
}

void Goal::CheckCollision(PlayerManager* playerManager) {
	// 元のObjectManager::CheckGoalCollisionのロジックをこちらに移動
	bool hitPlayer = IsCollision(GetAABB(), playerManager->GetPlayer()->GetAABB());
	bool hitClone = IsCollision(GetAABB(), playerManager->GetClone()->GetAABB());

	if (hitPlayer && hitClone) {
		if (playerManager->GetIsCloneActive() == true) {
			playerManager->SetIsCloneActive(false);
		}
		// 両方接触しているのでゴール成功
		playerManager->GetPlayer()->OnCollision(this);
	}
}
