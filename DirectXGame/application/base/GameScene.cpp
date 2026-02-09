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

	guideTh_ = TextureManager::Load("Guide/Guide.dds");
	guideSprite_ = Sprite::Create(guideTh_, guidePos_);
	guideSprite_->SetAnchorPoint({0.5f, 0.5f});
	guideSize_ = fileAccessor_->Read("Guide", "size", Vector2());
	guideSprite_->SetSize(guideSize_);

	guideIconPos_ = fileAccessor_->Read("GuideIcon", "pos", Vector2());
	guideIconTh_ = TextureManager::Load("Guide/GuideIcon.dds");
	guideIconSprite_ = Sprite::Create(guideIconTh_, guideIconPos_);
	guideIconSprite_->SetAnchorPoint({0.5f, 0.5f});
	guideIconSize_ = fileAccessor_->Read("GuideIcon", "size", Vector2());
	guideIconSprite_->SetSize(guideIconSize_);

	pauseBackScreenPos_ = fileAccessor_->Read("pauseBackScreen", "pos", Vector2());
	pauseBackScreenTh_ = TextureManager::Load("white1x1.dds");
	pauseBackScreenSprite_ = Sprite::Create(pauseBackScreenTh_, pauseBackScreenPos_);
	pauseBackScreenSprite_->SetAnchorPoint({0.5f, 0.5f});
	pauseBackScreenSize_ = fileAccessor_->Read("pauseBackScreen", "size", Vector2());
	pauseBackScreenSprite_->SetSize(pauseBackScreenSize_);
	pauseBackScreenColor_ = fileAccessor_->Read("pauseBackScreen", "Color", Vector4());
	pauseBackScreenSprite_->SetColor(pauseBackScreenColor_);

	gameButtonPos_ = fileAccessor_->Read("ReturnGameButton", "pos", Vector2());
	returnGameButtonTh_ = TextureManager::Load("Pause/ReturnGame.dds");
	returnGameButtonSprite_ = Sprite::Create(returnGameButtonTh_, gameButtonPos_);
	returnGameButtonSprite_->SetAnchorPoint({0.5f, 0.5f});
	gameButtonSize_ = fileAccessor_->Read("ReturnGameButton", "size", Vector2());
	returnGameButtonSprite_->SetSize(gameButtonSize_);

	guideButtonPos_ = fileAccessor_->Read("GuideButton", "pos", Vector2());
	guideButtonTh_ = TextureManager::Load("Pause/GameGuideButton.dds");
	guideButtonSprite_ = Sprite::Create(guideButtonTh_, guideButtonPos_);
	guideButtonSprite_->SetAnchorPoint({0.5f, 0.5f});
	guideButtonSize_ = fileAccessor_->Read("GuideButton", "size", Vector2());
	guideButtonSprite_->SetSize(guideButtonSize_);

	titelButtonPos_ = fileAccessor_->Read("TitelButton", "pos", Vector2());
	titelButtonTh_ = TextureManager::Load("Pause/TitelButton.dds");
	titelButtonSprite_ = Sprite::Create(titelButtonTh_, titelButtonPos_);
	titelButtonSprite_->SetAnchorPoint({0.5f, 0.5f});
	titelButtonSize_ = fileAccessor_->Read("TitelButton", "size", Vector2());
	titelButtonSprite_->SetSize(titelButtonPos_);

	mapChip_.Initialize(filePath, erea, stage);
	playerManager_.Initialize(&mapChip_);
	camera_ = new GameCamera();
	camera_->SetPlayerManager(&playerManager_);
	camera_->Initialize();

	objectManager_ = new ObjectManager();
	objectManager_->Initilize(&mapChip_);

	playerManager_.SetObjectManager(objectManager_);

	for (int i = 0; i < 3; i++) {
		countTh_[i] = TextureManager::Load(std::string("Count/count_") + std::to_string(3 - i) + std::string(".dds"));
		countSprite_[i] = Sprite::Create(countTh_[i], Vector2(640.0f, 360.0f));
		countSprite_[i]->SetAnchorPoint({0.5f, 0.5f});
	}
	countTh_[3] = TextureManager::Load("Count/start.dds");
	countSprite_[3] = Sprite::Create(countTh_[3], Vector2(640.0f, 360.0f));
	countSprite_[3]->SetAnchorPoint({0.5f, 0.5f});

	pauseCursorMin = fileAccessor_->Read("Pause", "PauseCursorMin", int());
	pauseCursorMax = fileAccessor_->Read("Pause", "PauseCursorMax", int());

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
	mapChip_.Update();
	if (Input::GetInstance()->ReleseKey(DIK_ESCAPE) || (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_START && preXinput_.Gamepad.wButtons == 0)) {
		isPause_ = true;
		pauseCursor_ = 0;
	}

	guideSprite_->SetPosition(guidePos_);
	guideSprite_->SetSize(guideSize_);
	guideIconSprite_->SetPosition(guideIconPos_);
	guideIconSprite_->SetSize(guideIconSize_);
	pauseBackScreenSprite_->SetPosition(pauseBackScreenPos_);
	pauseBackScreenSprite_->SetSize(pauseBackScreenSize_);
	pauseBackScreenSprite_->SetColor(pauseBackScreenColor_);
	returnGameButtonSprite_->SetPosition(gameButtonPos_);
	returnGameButtonSprite_->SetSize(gameButtonSize_);
	guideButtonSprite_->SetPosition(guideButtonPos_);
	guideButtonSprite_->SetSize(guideButtonSize_);
	titelButtonSprite_->SetPosition(titelButtonPos_);
	titelButtonSprite_->SetSize(titelButtonSize_);

	playerManager_.SetGameScene(this);

	if (isPause_) {
		bool isMoveUp = false;
		bool isMoveDown = false;
		if (xinput_.Gamepad.sThumbLY > 20000) {
			if (isLStickPushed_ == false) {
				isMoveUp = true;
				isLStickPushed_ = true;
			}
		} else if (xinput_.Gamepad.sThumbLY < -20000) {
			if (isLStickPushed_ == false) {
				isMoveDown = true;
				isLStickPushed_ = true;
			}
		} else {
			isLStickPushed_ = false;
		}

		if (Input::GetInstance()->ReleseKey(DIK_W) || (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && !preXinput_.Gamepad.wButtons)) {
			isMoveUp = true;
		}
		if (Input::GetInstance()->ReleseKey(DIK_S) || (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && !preXinput_.Gamepad.wButtons)) {
			isMoveDown = true;
		}
		if (isMoveUp) {
			pauseCursor_--;
			if (pauseCursor_ < pauseCursorMin) {
				pauseCursor_ = pauseCursorMax;
			}
		}
		if (isMoveDown) {
			pauseCursor_++;
			if (pauseCursor_ > pauseCursorMax) {
				pauseCursor_ = pauseCursorMin;
			}
		}


		if (Input::GetInstance()->ReleseKey(DIK_SPACE) || (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_A && !preXinput_.Gamepad.wButtons)) {
			if (pauseCursor_ == 0) {
				isPause_ = false;
			}
			if (pauseCursor_ == 1) {
				isGuide = !isGuide;
			}
			if (pauseCursor_ == 2) {
				nextScene_ = SceneID::Title;
				isFinish = true;
			}
		}

	} else {
		playerManager_.Update(xinput_, preXinput_);
		objectManager_->UpDate();

		mapChip_.SetIsBlockReaction(camera_->GetIsReactionEnd());

		if (playerManager_.GetPlayer()->GetIsRotateGoal()) {
			isFadeStart = true;
		}

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
		objectManager_->CheckAllCollisions(&playerManager_);
		fade_->Update();
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

	guideIconSprite_->Draw();
	if (isPause_) {
		pauseBackScreenSprite_->Draw();
		returnGameButtonSprite_->Draw();
		guideButtonSprite_->Draw();
		titelButtonSprite_->Draw();

		if (pauseCursor_ == 0) {
			returnGameButtonSprite_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			returnGameButtonSprite_->SetColor({1.0f, 1.0f, 1.0f, 0.5f});
		}
		if (pauseCursor_ == 1) {
			guideButtonSprite_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			guideButtonSprite_->SetColor({1.0f, 1.0f, 1.0f, 0.5f});
		}
		if (pauseCursor_ == 2) {
			titelButtonSprite_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			titelButtonSprite_->SetColor({1.0f, 1.0f, 1.0f, 0.5f});
		}

	} else {
		if (isStart) {
			countSprite_[count_]->Draw();
		}

		fade_->Draw();
	}

	if (isGuide) {
		guideSprite_->Draw();
	}

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
	ImGui::DragFloat2("guideIconPos", &guideIconPos_.x);
	ImGui::DragFloat2("guideIconSize", &guideIconSize_.x);
	ImGui::Checkbox("isPause", &isPause_);
	ImGui::DragFloat2("pauseBackScreenPos", &pauseBackScreenPos_.x);
	ImGui::DragFloat2("pauseBackScreenSize", &pauseBackScreenSize_.x);
	ImGui::DragFloat4("pauseBackScreenColor", &pauseBackScreenColor_.x);
	ImGui::DragFloat2("gameButtonPos_", &gameButtonPos_.x);
	ImGui::DragFloat2("gameButtonSize_", &gameButtonSize_.x);
	ImGui::DragFloat2("guideButtonPos_", &guideButtonPos_.x);
	ImGui::DragFloat2("guideButtonSize_", &guideButtonSize_.x);
	ImGui::DragFloat2("titelButtonPos_", &titelButtonPos_.x);
	ImGui::DragFloat2("titelButtonSize_", &titelButtonSize_.x);

	if (ImGui::Button("save")) {
		fileAccessor_->Write("Guide", "pos", guidePos_);
		fileAccessor_->Write("Guide", "size", guideSize_);
		fileAccessor_->Write("GuideIcon", "pos", guideIconPos_);
		fileAccessor_->Write("GuideIcon", "size", guideIconSize_);
		fileAccessor_->Write("pauseBackScreen", "pos", pauseBackScreenPos_);
		fileAccessor_->Write("pauseBackScreen", "size", pauseBackScreenSize_);
		fileAccessor_->Write("pauseBackScreen", "Color", pauseBackScreenColor_);
		fileAccessor_->Write("ReturnGameButton", "pos", gameButtonPos_);
		fileAccessor_->Write("ReturnGameButton", "size", gameButtonSize_);
		fileAccessor_->Write("GuideButton", "pos", guideButtonPos_);
		fileAccessor_->Write("GuideButton", "size", guideButtonSize_);
		fileAccessor_->Write("TitelButton", "pos", titelButtonPos_);
		fileAccessor_->Write("TitelButton", "size", titelButtonSize_);
		fileAccessor_->Save();
	}
	ImGui::End();
	camera_->ImGuiDraw();
	playerManager_.DrawImGui();
	objectManager_->DrawImGui();

#endif // _DEBUG
}

SceneID GameScene::NextScene() const { return nextScene_; }
