#include "SceneManager.h"

void SceneManager::ChangeScene(SceneID nextScene) {
	// 既存シーンのリソース削除
	if (currentScene_) {
		currentScene_->Delete();
		currentScene_.reset();
	}
	// 新しいシーンを生成
	switch (nextScene) {
	case SceneID::Game:
		currentScene_ = std::make_unique<GameScene>();
		SetInformation();

		break;
	case SceneID::Reset:
		currentScene_ = std::make_unique<ResetScene>();
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
	// stageの数値と文字列を引き継ぐ
	currentScene_->SetStageNum(stageNum);
	currentScene_->SetEreaNum(ereaNum);
	currentScene_->SetStage(stage);
}

void SceneManager::GetInformation() {
	stageNum = currentScene_->GetStageNum();
	ereaNum = currentScene_->GetEreaNum();
	stage = currentScene_->GetStage();
}
