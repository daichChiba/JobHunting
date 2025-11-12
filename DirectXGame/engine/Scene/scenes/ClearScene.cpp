#include "ClearScene.h"
using namespace KamataEngine;

ClearScene::ClearScene() {}

ClearScene::~ClearScene() {}

void ClearScene::Initialize() {
	backScreenTh_ = TextureManager::Load("Titel/backScreen.png");
	backScreenSpite = Sprite::Create(backScreenTh_, {640.0f, 360.0f});
	backScreenSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));

	pushToSpaceTh_ = TextureManager::Load("Titel/PushToSpace.png");
	pushToSpaceSpite = Sprite::Create(pushToSpaceTh_, {640.0f, 550.0f});
	pushToSpaceSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));
	clearTh_ = TextureManager::Load("Clear/GameClear.png");
	clearSpite = Sprite::Create(clearTh_, {640.0f, 100.0f});
	clearSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));
}

void ClearScene::Update() {
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

void ClearScene::Draw() {
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

	clearSpite->Draw();

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void ClearScene::Delete() { delete fade_; }

void ClearScene::DrawImGui() {}

SceneID ClearScene::NextScene() const {
	//
	return nextScene_;
}
