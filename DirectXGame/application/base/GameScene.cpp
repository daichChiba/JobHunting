#include "GameScene.h"
#include "ect/MathUtilityForText.h"

using namespace KamataEngine;
using namespace MathUtility;
using namespace FileJson;
GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	fileAccessor_ = new FileAccessor(filePath_);

	guidePos_ = fileAccessor_->Read("Guide", "pos", Vector2());

	guideTh_ = TextureManager::Load("Guide/Guide.png");
	guideSprite_ = Sprite::Create(guideTh_, guidePos_);
	guideSprite_->SetAnchorPoint({0.5f, 0.5f});
	guideSize_ = fileAccessor_->Read("Guide", "size", Vector2());
	guideSprite_->SetSize(guideSize_);

	f1ButtonPos_ = fileAccessor_->Read("F1", "pos", Vector2());
	f1ButtonTh_ = TextureManager::Load("Guide/F1Button.png");
	f1ButtonSprite_ = Sprite::Create(f1ButtonTh_, f1ButtonPos_);
	f1ButtonSprite_->SetAnchorPoint({0.5f, 0.5f});
	f1ButtonSize_ = fileAccessor_->Read("F1", "size", Vector2());
	f1ButtonSprite_->SetSize(f1ButtonSize_);

	mapChip_.Initialize(filePath, erea, stage);
	playerManager_.Initialize(&mapChip_);
	camera_ = new GameCamera();
	camera_->SetPlayer(playerManager_.GetPlayer());
	camera_->Initialize();

	objectManager_ = new ObjectManager();
	objectManager_->Initilize(&mapChip_);

	playerManager_.SetObjectManager(objectManager_);

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
	preXinput_ = xinput_;
	XInputGetState(0, &xinput_);
	input_->SetJoystickDeadZone(0, 1, 1);
	
	camera_->SetMapChip(&mapChip_);
	camera_->SetObjectManager(objectManager_);
	camera_->Update();
	playerManager_.Update(xinput_,preXinput_);
	mapChip_.Update();
	objectManager_->UpDate();

	mapChip_.SetIsBlockReaction(camera_->GetIsReactionEnd());

	if (Input::GetInstance()->ReleseKey(DIK_F1)||(xinput_.Gamepad.wButtons&XINPUT_GAMEPAD_START&&preXinput_.Gamepad.wButtons==0)) {
		isGuide = !isGuide;
	}

	if (playerManager_.GetPlayer()->GetIsRotateGoal()) {
		isFadeStart = true;
	}
	guideSprite_->SetPosition(guidePos_);
	guideSprite_->SetSize(guideSize_);
	f1ButtonSprite_->SetPosition(f1ButtonPos_);
	f1ButtonSprite_->SetSize(f1ButtonSize_);

	if (isStart) {
		startCount_--;
		playerManager_.GetPlayer()->SetIsMove(false);
		if (startCount_ % 60 == 0) {
			if (camera_->GetCamera_PosType() < camera_->GetcameraTypeMax()) {
				count_++;
				camera_->SetIsMove(true);
				camera_->SetCamera_PosType(camera_->GetCamera_PosType() + 1);
				camera_->CameraNextPos();
			} else {
				isStart = false;
				playerManager_.GetPlayer()->SetIsMove(true);
			}
		}
	} else {

		gameCount_++;
		if (gameCount_ > 60) {
			if (!isFadeStart) {
				fade_->Start(FadeID::FadeOut, 1);
			}
		}
		if (isFadeStart) {
			if (fade_->IsFinished()) {
				isFinish = true;
				if (playerManager_.GetPlayer()->GetIsGoal()) {
					nextScene_ = SceneID::Clear;
				} else {
					nextScene_ = SceneID::Title;
				}
			}
		}
	}

	objectManager_->CheckAllCollisions(playerManager_.GetPlayer(), playerManager_.GetClone());

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

	playerManager_.Draw(*camera_->GetCamera());
	objectManager_->Draw(*camera_->GetCamera());

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

	if (isGuide) {
		guideSprite_->Draw();
	}
	f1ButtonSprite_->Draw();
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Delete() {
	objectManager_->Delete();
	delete fade_;
}

void GameScene::DrawImGui() {
#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);

	ImGui::DragInt("CameraCount", &count_);
	ImGui::Checkbox("isStart", &isStart);

	ImGui::DragFloat2("guidePos", &guidePos_.x);
	ImGui::DragFloat2("guideSize", &guideSize_.x);
	ImGui::DragFloat2("f1ButtonPos", &f1ButtonPos_.x);
	ImGui::DragFloat2("f1ButtonSize", &f1ButtonSize_.x);

	if (ImGui::Button("save")) {
		fileAccessor_->Write("Guide", "pos", guidePos_);
		fileAccessor_->Write("Guide", "size", guideSize_);
		fileAccessor_->Write("F1", "pos", f1ButtonPos_);
		fileAccessor_->Write("F1", "size", f1ButtonSize_);
		fileAccessor_->Save();
	}
	ImGui::End();
	camera_->ImGuiDraw();
	playerManager_.DrawImGui();
	objectManager_->DrawImGui();

#endif // _DEBUG
}

SceneID GameScene::NextScene() const { return nextScene_; }
