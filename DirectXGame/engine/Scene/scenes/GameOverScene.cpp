#include "GameOverScene.h"
using namespace KamataEngine;

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() {}

void GameOverScene::Initialize() {
	backScreenTh_ = TextureManager::Load("GameOver/backScreen.png");
	backScreenSpite = Sprite::Create(backScreenTh_, {640.0f, 360.0f});
	backScreenSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));

	titelTh_ = TextureManager::Load("GameOver/GameOver.png");
	titelSpite = Sprite::Create(titelTh_, {640.0, 100.0});
	titelSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));
	pushToSpaceTh_ = TextureManager::Load("GameOver/PushToSpace.png");
	pushToSpaceSpite = Sprite::Create(pushToSpaceTh_, {640.0f, 550.0f});
	pushToSpaceSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));
}

void GameOverScene::Update() {
	if (input_->GetInstance()->ReleseKey(DIK_SPACE)) {
		fade_->Start(FadeID::FadeOut, 1);
		isStart = false;
	}
	buttonCount++;

	if (!isStart) {
		if (fade_->IsFinished() == true) {
			isFinish = true;
			nextScene_ = SceneID::Title;
		}
	}
	fade_->Update();
}

void GameOverScene::Draw() {
	// 背景スプライト描画前処理
	Sprite::PreDraw();

	backScreenSpite->Draw();

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

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	titelSpite->Draw();

	if (buttonCount % kCountFrame_ >= kDrawCount_) {
		pushToSpaceSpite->Draw();
	}

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameOverScene::Delete() {
	//
	delete fade_;
}

void GameOverScene::DrawImGui() {
#ifdef _DEBUG

	ImGui::Begin("GameOverScene");
	ImGui::Text("Test");
	ImGui::End();
#endif // _DEBUG
}

SceneID GameOverScene::NextScene() const {
	//
	return nextScene_;
}
