#include "PlayerManager.h"
#include "application/base/GameScene.h"
using namespace KamataEngine;

void PlayerManager::Initialize(MapChip* mapChip) {
	//
	player_.Initialize(mapChip);
	clone_.Initialize(mapChip);
}
void PlayerManager::Update(XINPUT_STATE xinput, XINPUT_STATE preXinput) {
	// ここで切り替え処理や両方のUpdateを呼ぶ

	if (Input::GetInstance()->ReleseKey(DIK_SPACE) || (xinput.Gamepad.wButtons & XINPUT_GAMEPAD_B && !preXinput.Gamepad.wButtons)) {
		isCloneActive_ = !isCloneActive_;

		////動作フラグの更新
		// player_.SetIsMove(!isCloneActive_);
		// clone_.SetIsMove(isCloneActive_);
	}
	if (gameScene_->GetIsStart() == false) {
		// 動作フラグの更新
		player_.SetIsMove(!isCloneActive_);
		clone_.SetIsMove(isCloneActive_);
	}

	player_.SetXinput(xinput);
	player_.Update();
	clone_.SetXinput(xinput);
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
#ifdef _DEBUG

	ImGui::Begin("PlayerManager");
	ImGui::Checkbox("isCloneActive", &isCloneActive_);
	ImGui::End();
#endif // _DEBUG


	player_.DrawImGui();
	clone_.DrawImGui();
}

void PlayerManager::SetObjectManager(ObjectManager* objectManager) {
	player_.SetObjectManager(objectManager);
	clone_.SetObjectManager(objectManager);
}