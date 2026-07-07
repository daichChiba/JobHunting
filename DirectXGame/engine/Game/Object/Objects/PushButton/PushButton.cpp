#include "PushButton.h"
#include "engine/Game/MapChip/MapChip.h"
#include "Game/Player/Player.h"
#include "Game/Player/PlayerManager.h"
#include "ect/MathUtilityForText.h"

using namespace KamataEngine;

PushButton::PushButton() {
	//
}

PushButton::~PushButton() {
	//
}

void PushButton::Initialize(const KamataEngine::Vector3 pos) {

	model_[0] = Model::CreateFromOBJ("PushButton", true);
	model_[1] = Model::CreateFromOBJ("PressButton", true);

	//
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
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

void PushButton::DrawImGui(const std::string& label) {
	//
	label;
#ifdef _DEBUG

	if (ImGui::TreeNode(label.c_str())) {
		ImGui::Text("test");
		ImGui::Checkbox("isPushButton", &isPushButton);
		ImGui::TreePop();
	}

#endif // _DEBUG
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

void PushButton::CheckCollision(PlayerManager* playerManager) {
	// 元のObjectManager::CheckButtonCollisionの個別ロジックをカプセル化
	bool hitPlayer = IsCollision(GetAABB(), playerManager->GetPlayer()->GetAABB());
	bool hitClone = IsCollision(GetAABB(), playerManager->GetClone()->GetAABB());

	if (hitPlayer || hitClone) {
		isPushButton = true; // ボタンON
	} else {
		isPushButton = false; // 離れたらOFF
	}
}

//void PushButton::OnCollision(const Player* player, const PlayerClone* clone) {
//	//
//	(void)player;
//	(void)clone;
//
//	isPushButton = true;
//}
