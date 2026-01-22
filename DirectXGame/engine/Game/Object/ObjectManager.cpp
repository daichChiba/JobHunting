#include "ObjectManager.h"
#include "Game/Player/Clone/PlayerClone.h"
#include "engine/Game/MapChip/MapChip.h"
#include "engine/Game/Player/Player.h"
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

std::vector<Vector3> leverPos = mapchip->GetAllObjectPositions(MapChipID::Lever);
	for (const auto& pos : leverPos) {
		// newで生成してunique_ptrに持たせる
		auto newLever = std::make_unique<Lever>();
		newLever->Initilize(pos);
		levers_.push_back(std::move(newLever));
	}
	std::vector<Vector3> buttonPos = mapchip->GetAllObjectPositions(MapChipID::Button);
	for (const auto& pos : buttonPos) {
		auto newButton = std::make_unique<PushButton>();
		newButton->Initilize(pos);
		pushButtons_.push_back(std::move(newButton));
	}
	std::vector<Vector3> GoalPos = mapchip->GetAllObjectPositions(MapChipID::kGoal);
	for (const auto& pos : GoalPos) {
		auto newGoal = std::make_unique<Goal>();
		newGoal->Initialize(pos);
		goals_.push_back(std::move(newGoal));
	}
}

void ObjectManager::UpDate() {
	//
	for (auto& goal : goals_) {
		goal->Update();
	}
	for (auto& pushButton : pushButtons_) {
		pushButton->Update();
	}
	for (auto& lever : levers_) {
		lever->Update();
	}
}

void ObjectManager::Draw(KamataEngine::Camera& camera) {
	//

	for (auto& goal : goals_) {
		goal->Draw(camera);
	}
	for (auto& pushButton : pushButtons_) {
		pushButton->Draw(camera);
	}
	for (auto& lever : levers_) {
		lever->Draw(camera);
	}
}

void ObjectManager::DrawImGui() {

	for (auto& lever : levers_) {
		lever->DrawImGui();
	}
}

void ObjectManager::Delete() {
	for (auto& goal : goals_) {
		goal->Delete();
	}
	goals_.clear();
	for (auto& pushButton : pushButtons_) {
		pushButton->Delete();
	}
	pushButtons_.clear();
	for (auto& lever : levers_) {
		lever->Delete();
	}
	levers_.clear();
}

void ObjectManager::CheckAllCollisions(Player* player, PlayerClone* playerClone) {


	CheckLeverCollision(player, playerClone);
	CheckButtonCollision(player, playerClone);
	CheckGoalCollision(player, playerClone);
}

void ObjectManager::CheckLeverCollision(Player* player, PlayerClone* playerClone) {
	//

	int activeLeverCount = 0;
	bool playerHitAny = false;
	bool cloneHitAny = false;

	// 全レバーをチェック
	for (auto& lever : levers_) {
		bool hitPlayer = IsCollision(lever->GetAABB(), player->GetAABB());
		bool hitClone = IsCollision(lever->GetAABB(), playerClone->GetAABB());

		// 個別のレバーの接触状態を更新（アニメーション等のため）
		if (!isAllLeverCollision) {
			if (hitPlayer || hitClone) {
				lever->OnCollision(player, playerClone); // 接触時の処理
				activeLeverCount++;
			} else {
				lever->SetIsLever(false);
				activeLeverCount--;
			}
		}

		if (hitPlayer) {
			playerHitAny = true;
		}
		if (hitClone) {
			cloneHitAny = true;
		}
	}

	// 条件: プレイヤーとクローンがそれぞれレバーに触れている
	if (playerHitAny && cloneHitAny && activeLeverCount >= 2) {
		// 全体のギミック解除処理
		isAllLeverCollision = true;
	}

}

void ObjectManager::CheckButtonCollision(Player* player, PlayerClone* playerClone) {
	for (auto& button : pushButtons_) {
		bool hitPlayer = IsCollision(button->GetAABB(), player->GetAABB());
		bool hitClone = IsCollision(button->GetAABB(), playerClone->GetAABB());

		if (hitPlayer || hitClone) {
			button->OnCollision(player, playerClone); // ONにする
			isPushButton = true;
		} else {
			button->SetInPushButton(false); // 離れたらOFFにする処理が必要なら
			isPushButton = false;
		}
	}
}

void ObjectManager::CheckGoalCollision(Player* player, PlayerClone* playerClone) {
	// 複数のゴールがあるならループ、1つなら直接参照
	for (auto& goal : goals_) {
		bool hitPlayer = IsCollision(goal->GetAABB(), player->GetAABB());
		bool hitClone = IsCollision(goal->GetAABB(), playerClone->GetAABB());

		if (hitPlayer && hitClone) {
			// 両方接触しているのでゴール成功
			player->OnCollision(goal.get()); // プレイヤーのゴールフラグを立てる
		}
	}
}
