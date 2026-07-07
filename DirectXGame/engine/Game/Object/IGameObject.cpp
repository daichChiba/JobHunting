#include "IGameObject.h"

using namespace KamataEngine;

void IGameObject::Initialize(const KamataEngine::Vector3 pos) {
	//
	pos;
}

void IGameObject::Update() {
	//

}

void IGameObject::Draw(KamataEngine::Camera& camera_) {
	//
	camera_;
}

void IGameObject::DrawImGui(const std::string& label) {
	//
	label;
}

void IGameObject::CheckCollision(PlayerManager* playerManager) {
	//
	playerManager;
}

KamataEngine::Vector3 IGameObject::GetWorldPos() {
	//
	KamataEngine::Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

AABB IGameObject::GetAABB() {
	//
	KamataEngine::Vector3 worldPos = GetWorldPos();
	AABB aabb;
	aabb.min = {worldPos.x - size_.x / 2.0f, worldPos.y - size_.y / 2.0f, worldPos.z - size_.x / 2.0f};
	aabb.max = {worldPos.x + size_.x / 2.0f, worldPos.y + size_.y / 2.0f, worldPos.z + size_.x / 2.0f};
	return aabb;
}