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

		break;
	case SceneID::Reset:
		currentScene_ = std::make_unique<ResetScene>();
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
