#include "DemoScene.h"
using namespace KamataEngine;
DemoScene::DemoScene() {}

DemoScene::~DemoScene() {}

void DemoScene::Initialize() {

	backScreenTh_ = TextureManager::Load("Titel/backScreen.png");
	backScreenSpite = Sprite::Create(backScreenTh_, {640.0f, 360.0f});
	backScreenSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));

	pushToSpaceTh_ = TextureManager::Load("Titel/PushToSpace.png");
	pushToSpaceSpite = Sprite::Create(pushToSpaceTh_, {640.0f, 550.0f});
	pushToSpaceSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));
}

void DemoScene::Update() {
	preXinput_ = xinput_;
	XInputGetState(0, &xinput_);

	if (input_->GetInstance()->ReleseKey(DIK_SPACE) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		if (!isCleck) {
			isCleck = true;
			fade_->Start(FadeID::FadeOut, 1);
			isStart = false;
		}
	}
	buttonCount++;

	if (!isStart) {
		if (fade_->IsFinished() == true) {
			isFinish = true;
			nextScene_ = SceneID::Game;
		}
	}
	fade_->Update();
}

void DemoScene::Draw() {
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

	if (buttonCount % kCountFrame_ >= kDrawCount_) {
		pushToSpaceSpite->Draw();
	}

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void DemoScene::Delete() {
	//
	delete fade_;
}

void DemoScene::DrawImGui() {
	//
#ifdef _DEBUG

	ImGui::Begin("DemoScene");
	ImGui::Text("Test");
	ImGui::End();
#endif // _DEBUG
}

SceneID DemoScene::NextScene() const {
	//
	return nextScene_;
}
