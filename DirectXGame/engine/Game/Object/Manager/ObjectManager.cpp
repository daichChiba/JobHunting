#include "ObjectManager.h"
#include "Game/Object/Objects/Goal/Goal.h"
#include "Game/Object/Objects/Lever/Lever.h"
#include "Game/Object/Objects/PushButton/PushButton.h"
#include "Game/Player/Clone/PlayerClone.h"
#include "engine/Game/MapChip/MapChip.h"
#include "engine/Game/Player/Player.h"
#include "engine/Game/Player/PlayerManager.h"
#include "engine/ect/MathUtilityForText.h"

using namespace KamataEngine;

ObjectManager::ObjectManager() {
	//
}

ObjectManager::~ObjectManager() {
	//
}

void ObjectManager::Initilize(MapChip* mapchip) {
	//
	mapChipData_ = mapchip;

	// 1. レバーの生成・登録
	std::vector<Vector3> leverPos = mapchip->GetAllObjectPositions(MapChipID::Lever);
	for (const auto& pos : leverPos) {
		auto newLever = std::make_unique<Lever>();
		newLever->Initialize(pos);
		objects_.push_back(std::move(newLever));
	}

	// 2. ボタンの生成・登録
	std::vector<Vector3> buttonPos = mapchip->GetAllObjectPositions(MapChipID::Button);
	for (const auto& pos : buttonPos) {
		auto newButton = std::make_unique<PushButton>();
		newButton->Initialize(pos);
		objects_.push_back(std::move(newButton));
	}

	// 3. ゴールの生成・登録
	std::vector<Vector3> goalPos = mapchip->GetAllObjectPositions(MapChipID::kGoal);
	for (const auto& pos : goalPos) {
		auto newGoal = std::make_unique<Goal>();
		newGoal->Initialize(pos);
		objects_.push_back(std::move(newGoal));
	}
}

void ObjectManager::UpDate() {
	//
	for (auto& obj : objects_) {
		obj->Update();
	}
}

void ObjectManager::Draw(KamataEngine::Camera& camera) {
	//

	for (auto& obj : objects_) {
		obj->Draw(camera);
	}
}

void ObjectManager::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("ObjectManager");

	int index = 0;
	for (auto& obj : objects_) {
		std::string label = "Object_" + std::to_string(index);
		obj->DrawImGui(label);
		index++;
	}

	ImGui::Checkbox("isPushButton", &isPushButton);
	ImGui::Checkbox("isAllLeverCollision", &isAllLeverCollision);
	ImGui::End();
#endif // _DEBUG
}

void ObjectManager::Delete() {
	objects_.clear();
}

void ObjectManager::CheckAllCollisions(PlayerManager* playerManager) {
	// 1. まず各オブジェクト個別の衝突判定を回す (GoalやButton自身の状態が更新される)
	bool anyButtonPushed = false;

	for (auto& obj : objects_) {
		obj->CheckCollision(playerManager);

		// 全体フラグ(isPushButton)の集計のため、PushButtonタイプのみ状態を取得する
		if (auto button = dynamic_cast<PushButton*>(obj.get())) {
			if (button->GetIsPushButton()) {
				anyButtonPushed = true;
			}
		}
	}
	isPushButton = anyButtonPushed;

	// 2. 複数オブジェクトの複合条件が必要なレバー判定を一括処理
	CheckLeverCollision(playerManager);
}

void ObjectManager::CheckLeverCollision(PlayerManager* playerManager) {
	int activeLeverCount = 0;
	bool playerHitAny = false;
	bool cloneHitAny = false;

	for (auto& obj : objects_) {
		// 基底クラスのポインタからLeverクラスであるかを安全に識別 (dynamic_cast)
		if (auto lever = dynamic_cast<Lever*>(obj.get())) {
			bool hitPlayer = IsCollision(lever->GetAABB(), playerManager->GetPlayer()->GetAABB());
			bool hitClone = IsCollision(lever->GetAABB(), playerManager->GetClone()->GetAABB());

			if (!isAllLeverCollision) {
				if (hitPlayer || hitClone) {
					lever->SetIsLever(true);
					activeLeverCount++;
				} else {
					lever->SetIsLever(false);
				}
			}

			if (hitPlayer)
				playerHitAny = true;
			if (hitClone)
				cloneHitAny = true;
		}
	}

	// 条件: プレイヤーとクローンがそれぞれ別のレバーに同時に触れている
	if (playerHitAny && cloneHitAny && activeLeverCount >= 2) {
		isAllLeverCollision = true;
	}
}