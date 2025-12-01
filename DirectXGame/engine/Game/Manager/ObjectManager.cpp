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
}

void ObjectManager::UpDate() {
	//
	goal_.Update();
	
}

void ObjectManager::Draw(KamataEngine::Camera& camera) {
	//

	goal_.Draw(camera);
}

void ObjectManager::DrawImGui() {
	goal_.DrawImGui();
}

void ObjectManager::Delete() {
	goal_.Delete();
}

void ObjectManager::CheckAllCollisions(Player* player) {
	//
	AABB playerAABB = player->GetAABB();

	if (IsCollision(playerAABB, goal_.GetAABB())) {
		player->OnCollision(&goal_);
	}
}