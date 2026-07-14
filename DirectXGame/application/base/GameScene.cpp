#include "GameScene.h"
#include "ect/MathUtilityForText.h"

using namespace KamataEngine;
using namespace MathUtility;
using namespace FileJson;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	fileAccessor_ = new FileAccessor(filePath_);

	guideIconPos_ = fileAccessor_->Read("GuideIcon", "pos", Vector2());
	guideIconTh_ = TextureManager::Load("Guide/GuideIcon.dds");
	guideIconSprite_ = Sprite::Create(guideIconTh_, guideIconPos_);
	guideIconSprite_->SetAnchorPoint({0.5f, 0.5f});
	guideIconSize_ = fileAccessor_->Read("GuideIcon", "size", Vector2());
	guideIconSprite_->SetSize(guideIconSize_);

	mapChip_.Initialize(filePath, erea, stage);
	playerManager_.Initialize(&mapChip_);
	camera_ = new GameCamera();
	camera_->SetPlayerManager(&playerManager_);
	camera_->Initialize();

	objectManager_ = new ObjectManager();
	objectManager_->Initilize(&mapChip_);

	playerManager_.SetObjectManager(objectManager_);
	playerManager_.SetGameScene(this);

	mapChip_.SetObjectManager(objectManager_);

	for (int i = 0; i < 3; i++) {
		countTh_[i] = TextureManager::Load(std::string("Count/count_") + std::to_string(3 - i) + std::string(".dds"));
		countSprite_[i] = Sprite::Create(countTh_[i], Vector2(640.0f, 360.0f));
		countSprite_[i]->SetAnchorPoint({0.5f, 0.5f});
	}
	countTh_[3] = TextureManager::Load("Count/start.dds");
	countSprite_[3] = Sprite::Create(countTh_[3], Vector2(640.0f, 360.0f));
	countSprite_[3]->SetAnchorPoint({0.5f, 0.5f});

	startCount_ = 240;
	isStart = true;
	gameCount_ = 0;

	isFadeStart = false;

	pauseMenu_.Initilize();
	// ファクトリーの登録
	pauseMenu_.RegisterButton(PauseID::kReturnGame, [](FileJson::FileAccessor* fa) -> MenuButton {
		MenuButton btn;
		btn.jsonKey = "ReturnGameButton";
		btn.pos = fa->Read(btn.jsonKey, "pos", Vector2());
		btn.size = fa->Read(btn.jsonKey, "size", Vector2());
		btn.textureHandle = KamataEngine::TextureManager::Load("Pause/ReturnGame.dds");
		btn.sprite = KamataEngine::Sprite::Create(btn.textureHandle, btn.pos);
		btn.sprite->SetAnchorPoint({0.5f, 0.5f});
		btn.sprite->SetSize(btn.size);
		return btn;
	});
	pauseMenu_.RegisterButton(PauseID::kGuide, [](FileJson::FileAccessor* fa) -> MenuButton {
		MenuButton btn;
		btn.jsonKey = "GuideButton";
		btn.pos = fa->Read(btn.jsonKey, "pos", Vector2());
		btn.size = fa->Read(btn.jsonKey, "size", Vector2());
		btn.textureHandle = KamataEngine::TextureManager::Load("Pause/GameGuideButton.dds");
		btn.sprite = KamataEngine::Sprite::Create(btn.textureHandle, btn.pos);
		btn.sprite->SetAnchorPoint({0.5f, 0.5f});
		btn.sprite->SetSize(btn.size);
		return btn;
	});
	pauseMenu_.RegisterButton(PauseID::kTitel, [](FileJson::FileAccessor* fa) -> MenuButton {
		MenuButton btn;
		btn.jsonKey = "TitelButton";
		btn.pos = fa->Read(btn.jsonKey, "pos", Vector2());
		btn.size = fa->Read(btn.jsonKey, "size", Vector2());
		btn.textureHandle = KamataEngine::TextureManager::Load("Pause/TitelButton.dds");
		btn.sprite = KamataEngine::Sprite::Create(btn.textureHandle, btn.pos);
		btn.sprite->SetAnchorPoint({0.5f, 0.5f});
		btn.sprite->SetSize(btn.size);
		return btn;
	});
	pauseMenu_.RegisterButton(PauseID::kRestart, [](FileJson::FileAccessor* fa) -> MenuButton {
		MenuButton btn;
		btn.jsonKey = "RestartButton";
		btn.pos = fa->Read(btn.jsonKey, "pos", Vector2());
		btn.size = fa->Read(btn.jsonKey, "size", Vector2());
		btn.textureHandle = KamataEngine::TextureManager::Load("Pause/RestartButton.dds");
		btn.sprite = KamataEngine::Sprite::Create(btn.textureHandle, btn.pos);
		btn.sprite->SetAnchorPoint({0.5f, 0.5f});
		btn.sprite->SetSize(btn.size);
		return btn;
	});
	pauseMenu_.RegisterButton(PauseID::kGuideImage, [](FileJson::FileAccessor* fa) -> MenuButton {
		MenuButton btn;
		btn.jsonKey = "Guide";
		btn.pos = fa->Read(btn.jsonKey, "pos", Vector2(640.0f, 360.0f));
		btn.size = fa->Read(btn.jsonKey, "size", Vector2(1280.0f, 720.0f));
		btn.textureHandle = KamataEngine::TextureManager::Load("Guide/Guide.dds");
		btn.sprite = KamataEngine::Sprite::Create(btn.textureHandle, btn.pos);
		btn.sprite->SetAnchorPoint({0.5f, 0.5f});
		btn.sprite->SetSize(btn.size);
		return btn;
	});

	// ガイド専用ページ
	PausePage* guidePage_ = pauseMenu_.BuilldPage({PauseID::kGuideImage});

	// メインページを作成
	PausePage* mainPage = pauseMenu_.BuilldPage({PauseID::kReturnGame, PauseID::kGuide, PauseID::kTitel, PauseID::kRestart});

	// ポーズ時のアクションを注入
	pauseMenu_.SetAction(PauseID::kReturnGame, [this]() { pauseMenu_.PopPage(); });
	pauseMenu_.SetAction(PauseID::kGuide, [this, guidePage_]() { pauseMenu_.PushPage(guidePage_); });
	pauseMenu_.SetAction(PauseID::kTitel, [this]() {
		nextScene_ = SceneID::Title;
		isFinish = true;
	});
	pauseMenu_.SetAction(PauseID::kRestart, [this]() {
		nextScene_ = SceneID::Game;
		isFinish = true;
	});

	mainPage = pauseMenu_.BuilldPage({
		PauseID::kReturnGame,
		PauseID::kGuide,
		PauseID::kTitel,
		PauseID::kRestart
	});

	// PauseMenu内部で所持
	pauseMenu_.SetMainPage(mainPage);
}

void GameScene::Update() {
	preXinput_ = xinput_;
	XInputGetState(0, &xinput_);
	input_->SetJoystickDeadZone(0, 1, 1);

	camera_->SetMapChip(&mapChip_);
	camera_->SetObjectManager(objectManager_);
	camera_->Update();
	mapChip_.Update();

	if (!isStart) {
		pauseMenu_.Update(xinput_, preXinput_);
	}

	guideIconSprite_->SetPosition(guideIconPos_);
	guideIconSprite_->SetSize(guideIconSize_);

	if (!pauseMenu_.IsOpen()) {
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
	} else {
		playerManager_.StopRumble(xVibration_);
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
	if (pauseMenu_.IsOpen()) {

		pauseMenu_.Draw();

	} else {
		if (isStart) {
			countSprite_[count_]->Draw();
		}

		fade_->Draw();
	}

	// if (isGuide) {
	//	guideSprite_->Draw();
	// }

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Delete() {
	playerManager_.Delete();
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

	ImGui::DragFloat2("guideIconPos", &guideIconPos_.x);
	ImGui::DragFloat2("guideIconSize", &guideIconSize_.x);
	bool isOpen = pauseMenu_.IsOpen();
	ImGui::Checkbox("isOpen", &isOpen);

	if (ImGui::Button("Save GameScene Json")) {
		fileAccessor_->Write("GuideIcon", "pos", guideIconPos_);
		fileAccessor_->Write("GuideIcon", "size", guideIconSize_);
		fileAccessor_->Save();
	}
	ImGui::End();
	camera_->ImGuiDraw();
	playerManager_.DrawImGui();
	objectManager_->DrawImGui();
	pauseMenu_.DrawImGui();

#endif // _DEBUG
}

SceneID GameScene::NextScene() const { return nextScene_; }
