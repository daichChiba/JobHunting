#include "SceneManager.h"

void SceneManager::ChangeScene(SceneID nextScene) {
	// 既存シーンのリソース削除
	if (currentScene_) {
		currentScene_->Delete();
		currentScene_.reset();
	}
	// 新しいシーンを生成
	switch (nextScene) {
	case SceneID::Title:
		currentScene_ = std::make_unique<TitleScene>();
		SetInformation();
		break;
	case SceneID::Game:
		currentScene_ = std::make_unique<GameScene>();
		SetInformation();
		break;
	case SceneID::Reset:
		currentScene_ = std::make_unique<ResetScene>();
		SetInformation();
		break;

	case SceneID::Demo:
		currentScene_ = std::make_unique<DemoScene>();
		SetInformation();
		break;

	case SceneID::Over:
		currentScene_ = std::make_unique<GameOverScene>();
		SetInformation();
		break;
	}

	currentSceneID_ = nextScene;

	// セットアップ
	if (currentScene_) {
		currentScene_->SetUp();
	}
}

void SceneManager::Update() {
	currentScene_->Update();

	// シーン終了が指示されたら、ゲーム <-> リセットを交互に切替
	if (currentScene_->IsFinish()) {
		SceneID next = currentScene_->NextScene();
		GetInformation();
		ChangeScene(next);
	}
}
void SceneManager::Draw() {
	if (currentScene_) {
		currentScene_->Draw();
	}
}
void SceneManager::DrawImGui() {
	if (currentScene_) {
		currentScene_->DrawImGui();
	}
}

void SceneManager::SetInformation() {
	currentScene_->SetFilePath(filePath);
	currentScene_->SetErea(erea);
	currentScene_->SetStage(stage);
	currentScene_->SetTitelFilePath(titelFilePath);
}

void SceneManager::GetInformation() {
	currentScene_->GetFilePath();
	currentScene_->GetErea();
	currentScene_->GetStage();
	currentScene_->GetTitelFilePath();
}
