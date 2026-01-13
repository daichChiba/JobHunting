#include "PlayerManager.h"
using namespace KamataEngine;

void PlayerManager::Initialize(MapChip* mapChip) {
	//
	player_.Initialize(mapChip);
	clone_.Initialize(mapChip);
}
void PlayerManager::Update() {
	// ここで切り替え処理や両方のUpdateを呼ぶ

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		isCloneActive_ = !isCloneActive_;

		//動作フラグの更新
		player_.SetIsMove(!isCloneActive_);
		clone_.SetIsMove(isCloneActive_);
	}
	player_.Update();
	clone_.Update();
}

void PlayerManager::Draw(const Camera& camera) {
	//
	player_.Draw(camera);
	clone_.Draw(camera);
}

void PlayerManager::CheckSwitchInput() {
	//
}

void PlayerManager::DrawImGui() {
	player_.DrawImGui();
	clone_.DrawImGui();
}

void PlayerManager::SetObjectManager(ObjectManager* objectManager) {
	player_.SetObjectManager(objectManager);
	clone_.SetObjectManager(objectManager);
}