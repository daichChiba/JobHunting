#include "SceneManager.h"

SceneManager::SceneManager() {
		// シーンファクトリにすべてのシーンの生成ロジックを登録
		sceneFactory_[SceneID::Title] = []() { return std::make_unique<TitleScene>(); };
		sceneFactory_[SceneID::Game] = []() { return std::make_unique<GameScene>(); };
		sceneFactory_[SceneID::Reset] = []() { return std::make_unique<ResetScene>(); };
		sceneFactory_[SceneID::Demo] = []() { return std::make_unique<DemoScene>(); };
		sceneFactory_[SceneID::Clear] = []() { return std::make_unique<ClearScene>(); };
}

void SceneManager::ChangeScene(SceneID nextScene) {
	if (sceneFactory_.find(nextScene)==sceneFactory_.end()) {
		assert(!"Unknown SceneID provided to ChangeScene");
	}

	// 既存シーンのリソース削除
	if (currentScene_) {
		currentScene_->Delete();
		currentScene_.reset();
	}

	//if (nextScene==SceneID::Title) {
	//	currentScene_ = std::make_unique<TitleScene>();
	//	SetInformation();
	//}
	//// 新しいシーンを生成
	//switch (nextScene) {
	//case SceneID::Title:
	//	currentScene_ = std::make_unique<TitleScene>();
	//	SetInformation();
	//	break;
	//case SceneID::Game:
	//	currentScene_ = std::make_unique<GameScene>();
	//	SetInformation();
	//	break;
	//case SceneID::Reset:
	//	currentScene_ = std::make_unique<ResetScene>();
	//	SetInformation();
	//	break;

	//case SceneID::Demo:
	//	currentScene_ = std::make_unique<DemoScene>();
	//	SetInformation();
	//	break;
	//case SceneID::Clear:
	//	currentScene_ = std::make_unique<ClearScene>();
	//	
	//	break;
	//}

	//新しいシーンをファクトリから生成
	//マップから登録済みの生成関数を取得し、実行する
	currentScene_ = sceneFactory_[nextScene]();

	//シーン生成後に共通で呼び出される処理
	SetInformation();

	currentSceneID_ = nextScene;

	// セットアップ
	if (currentScene_) {
		currentScene_->SetUp();
	}
}

void SceneManager::Update() {
	currentScene_->Update();

	// シーン終了が指示されたら、任意の次のシーンを生成する
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
