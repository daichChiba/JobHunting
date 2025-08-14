#include "GameScene.h"

using namespace KamataEngine;
GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	gameSceneManager_.Initialize();
}

void GameScene::Update() {
	gameSceneManager_.Update();

	if (input_->GetInstance()->PushKey(DIK_RETURN)) {
		isFinish = true;
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

	gameSceneManager_.Draw();

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

void GameScene::Delete() { 
	gameSceneManager_.Initialize();
}

void GameScene::DrawImGui() {
	ImGui::Begin("GameScene");
	 ImGui::Text("Test");
	 ImGui::Checkbox("isFinished", &isFinish);
	 gameSceneManager_.DrawImGui();
	ImGui::End();
}
