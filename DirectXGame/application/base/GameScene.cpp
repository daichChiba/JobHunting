#include "GameScene.h"

using namespace KamataEngine;
using namespace FileJson;
GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	camera_ = new GameCamera();
	camera_->Initialize();
	mapChip_.Initialize(filePath, erea, stage);
	player_.Initialize(mapChip_);

	fileAccessor_ = mapChip_.GetFileAccessor();

	for (int i = 0; i < 3; i++) {
		countTh_[i] = TextureManager::Load(std::string("Count/count_") + std::to_string(3 - i) + std::string(".png"));
		countSprite_[i] = Sprite::Create(countTh_[i], Vector2(640.0f, 360.0f));
		countSprite_[i]->SetAnchorPoint({0.5f, 0.5f});
	}
	countTh_[3] = TextureManager::Load("Count/start.png");
	countSprite_[3] = Sprite::Create(countTh_[3], Vector2(640.0f, 360.0f));
	countSprite_[3]->SetAnchorPoint({0.5f, 0.5f});

	startCount_ = 240;
	isStart = true;
	gameCount_ = 0;

	isFadeStart = false;
}

void GameScene::Update() {

	camera_->Update();
	player_.Update();

	mapChip_.Update();

	if (isStart) {
		startCount_--;
		player_.SetIsMove(false);
		if (startCount_ % 60 == 0) {
			if (camera_->GetCamera_PosType() < camera_->GetcameraTypeMax()) {
				count_++;
				camera_->SetIsMove(true);
				camera_->SetCamera_PosType(camera_->GetCamera_PosType() + 1);
				camera_->CameraNextPos();
			} else {
				// if (count_>=3) {
				// }
				isStart = false;
			}
		}
	} else {
		// startCount_ = 240;
		// camera_->SetCamera_PosType(0);
		// camera_->CameraNextPos();
		// camera_->SetCameraPos();
		// count_ = 0;
		// isStart = true;
		player_.SetIsMove(true);
		gameCount_++;
		if (gameCount_ > 60) {
			if (!isFadeStart) {
				fade_->Start(FadeID::FadeOut, 1);
			}
			if (!player_.GetIsAlive()) {
				isFadeStart = true;
			}
		}
		if (isFadeStart) {
			if (fade_->IsFinished()) {
				isFinish = true;
				nextScene_ = SceneID::Over;
			}
		}
	}

	// if (input_->GetInstance()->PushKey(DIK_RETURN)) {
	//	isFinish = true;
	//	nextScene_ = SceneID::Title;
	// }

	fade_->Update();
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

	player_.Draw(*camera_->GetCamera());

	mapChip_.MapDraw(*camera_->GetCamera());
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	if (isStart) {
		countSprite_[count_]->Draw();
	}

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Delete() {
	player_.Delete();
	delete fade_;
}

void GameScene::DrawImGui() {
#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);
	player_.DrawImGui();

	ImGui::DragInt("CameraCount", &count_);
	ImGui::Checkbox("isStart", &isStart);
	if (ImGui::Button("restart")) {
		startCount_ = 240;
		camera_->SetCamera_PosType(0);
		camera_->CameraNextPos();
		camera_->SetCameraPos();
		count_ = 0;
		isStart = true;
	}
	ImGui::End();
	camera_->ImGuiDraw();
	mapChip_.DrawImGui();
#endif // _DEBUG
}

SceneID GameScene::NextScene() const { return nextScene_; }
