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
	if (sceneFactory_.find(nextScene) == sceneFactory_.end()) {
		assert(!"Unknown SceneID provided to ChangeScene");
	}

	// 既存シーンのリソース削除
	if (currentScene_) {
		currentScene_->Delete();
		currentScene_.reset();
	}

	// 新しいシーンをファクトリから生成
	// マップから登録済みの生成関数を取得し、実行する
	currentScene_ = sceneFactory_[nextScene]();

	// シーン生成後に共通で呼び出される処理
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

	if (reloadRequested_) {
		ChangeScene(currentSceneID_);
		GetInformation();
		reloadRequested_ = false;
	}
}
void SceneManager::Draw() {
	if (currentScene_) {
		currentScene_->Draw();
	}
}
void SceneManager::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("SceneManager");


	/// シーン遷移機能
	ImGui::SeparatorText("Scene Change");
	
	//
	const char* sceneNames[] = {
	    "Title", "Reset", "Game", "Demo", "Clear",
	};
	static int currentSceneIndex = 0;
	//コンボボックスでシーンを切り替える
	ImGui::Combo("Next Scene", &currentSceneIndex, sceneNames, IM_ARRAYSIZE(sceneNames));
	//
	if (ImGui::Button("Change Scene")) {
		ChangeScene(static_cast<SceneID>(currentSceneIndex));
	}

	//ステージ選択機能
	ImGui::SeparatorText("Stage Select");

	// ■ エリア (erea) の選択
	const char* areaList[] = {"stage"};
	static int currentAreaIndex = 0;

	if (ImGui::Combo("Area", &currentAreaIndex, areaList, IM_ARRAYSIZE(areaList))) {
		// 選択が変わったらSceneManagerの変数を更新
		erea = areaList[currentAreaIndex];
	}

	// ■ ステージ (stage) の選択
	const char* stageList[] = {"1", "2", "3", "4", "5", "6"}; 
	static int currentStageIndex = 0;

	if (ImGui::Combo("Stage", &currentStageIndex, stageList, IM_ARRAYSIZE(stageList))) {
		// 選択が変わったらSceneManagerの変数を更新
		stage = stageList[currentStageIndex];
	}


	if (ImGui::Button("ReLoad/Apply Stage")) {
		reloadRequested_ = true;
	}
	ImGui::End();
#endif // _DEBUG

	if (currentScene_) {
		currentScene_->DrawImGui();
	}
}

void SceneManager::SetInformation() {
	currentScene_->SetFilePath(filePath);
	currentScene_->SetErea(erea);
	currentScene_->SetStage(stage);
}

void SceneManager::GetInformation() {
	currentScene_->GetFilePath();
	currentScene_->GetErea();
	currentScene_->GetStage();
}
