#include "GameScene.h"

using namespace KamataEngine;
GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	camera_ = new Camera();
	camera_->Initialize();
	camera_->farZ = 1000.0f;
	mapChip_.Initialize(filePath, erea, stage);
	player_.Initialize(mapChip_);
}

void GameScene::Update() {
	camera_->UpdateMatrix();
	player_.Update();

	mapChip_.Update();

	if (input_->GetInstance()->PushKey(DIK_RETURN)) {
		isFinish = true;
		nextScene_ = SceneID::Title;
	}
}

void GameScene::Draw() {

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_.Draw(*camera_);

	mapChip_.MapDraw(*camera_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Delete() { player_.Delete(); }

void GameScene::DrawImGui() {
#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);
	player_.DrawImGui();
	mapChip_.DrawImGui();
	ImGui::End();
#endif // _DEBUG

}

SceneID GameScene::NextScene() const { return nextScene_; }
