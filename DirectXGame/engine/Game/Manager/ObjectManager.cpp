#include "ObjectManager.h"
#include "engine/Game/MapChip/MapChip.h"
#include "engine/Game/Player/Player.h"
#include "engine/ect/MathUtilityForText.h"

ObjectManager::ObjectManager() {
	//
}

ObjectManager::~ObjectManager() {
	//
}

void ObjectManager::Initilize(MapChip* mapchip) {
	//
	mapChipData_ = mapchip;
	goal_.Initialize(mapchip);
	pushButton_.Initilize(mapchip);
	lever_.Initilize(mapchip);
}

void ObjectManager::UpDate() {
	//
	goal_.Update();
	pushButton_.Update();
	lever_.Update();
}

void ObjectManager::Draw(KamataEngine::Camera& camera) {
	//

	goal_.Draw(camera);
	pushButton_.Draw(camera);
	lever_.Draw(camera);
}

void ObjectManager::DrawImGui() {
	//goal_.DrawImGui();
	//pushButton_.DrawImGui();
	lever_.DrawImGui();
}

void ObjectManager::Delete() {
	goal_.Delete();
	pushButton_.Delete();
	lever_.Delete();
}

void ObjectManager::CheckAllCollisions(Player* player) {
	//
	AABB playerAABB = player->GetAABB();

	if (IsCollision(playerAABB, goal_.GetAABB())) {
		player->OnCollision(&goal_);
	}

	if (IsCollision(playerAABB,pushButton_.GetAABB())) {
		pushButton_.OnCollision(player);
	} else {
		pushButton_.SetInPushButton(false);
	}

	if (IsCollision(playerAABB,lever_.GetAABB())) {
		lever_.OnCollision(player);
	}
}