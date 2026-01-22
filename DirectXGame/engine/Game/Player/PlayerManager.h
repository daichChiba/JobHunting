#pragma once
#include "Game/Player/Clone/PlayerClone.h"
#include "Game/Player/Player.h"

class PlayerManager {
public:
	void Initialize(MapChip* mapChip);
	void Update(XINPUT_STATE xinput, XINPUT_STATE preXinput);
	void Draw(const KamataEngine::Camera& camera);

	// ゲッター（当たり判定などで外部からアクセスするため）
	Player* GetPlayer() { return &player_; }
	PlayerClone* GetClone() { return &clone_; }

	void DrawImGui();

	// 操作状態の取得など
	bool IsControllingClone() const { return isCloneActive_; }

	void SetObjectManager(ObjectManager* objectManager);

private:
	Player player_;
	PlayerClone clone_;
	bool isCloneActive_ = false; // trueならクローン操作中

	// 切り替え入力検知用
	void CheckSwitchInput();
};
