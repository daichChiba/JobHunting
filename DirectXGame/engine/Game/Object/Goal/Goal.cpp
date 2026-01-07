#include "Goal.h"
#include "engine/Game/MapChip/MapChip.h"
#include "engine/Game/Player/Player.h"

using namespace KamataEngine;
using namespace MathUtility;
Goal::Goal() {}
Goal::~Goal() {}

void Goal::Initialize(const KamataEngine::Vector3 pos) {
	//


	Model* model = nullptr;
	model = Model::CreateFromOBJ("Portal", true);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = Vector3(0.5f, 0.5f, 1.0f);

	
}
void Goal::Update() {
	//

	worldTransform_.UpdateMatrix();
}
void Goal::Draw(const Camera& camera) {
	//
	model_->Draw(worldTransform_, camera);
}
void Goal::Delete() {
	//
	delete model_;
	model_ = nullptr;
}
void Goal::DrawImGui() {
	//
#ifdef _DEBUG
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


