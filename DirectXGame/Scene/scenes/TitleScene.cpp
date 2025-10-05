#include "TitleScene.h"

using namespace KamataEngine;
TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {
	backScreenTh_ = TextureManager::Load("Titel/backScreen.png");
	backScreenSpite = Sprite::Create(backScreenTh_, Vector2(0.0f, 0.0f));
	titelTh_ = TextureManager::Load("Titel/titel.png");
	titelSpite = Sprite::Create(titelTh_, Vector2(0.0f, 0.0f));
	pushToSpaceTh_ = TextureManager::Load("Titel/PushToSpace.png");
	pushToSpaceSpite = Sprite::Create(pushToSpaceTh_, Vector2(0.0f, 0.0f));
}

void TitleScene::Update() {
	if (input_->GetInstance()->ReleseKey(DIK_SPACE)) {
		isFinish = true;
		nextScene_ = SceneID::Reset;
	}
}

void TitleScene::Draw() {
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

	pushToSpaceSpite->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitleScene::Delete() {}

void TitleScene::DrawImGui() {
	ImGui::Begin("TitelScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);

	ImGui::End();
}

SceneID TitleScene::NextScene() const { return nextScene_; }
