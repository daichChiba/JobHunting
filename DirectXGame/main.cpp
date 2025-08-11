#include "Scene/scenes/GameScene.h"
#include "Scene/scenes/ResetScene.h"
#include <KamataEngine.h>
#include <Windows.h>
#include <map>

enum class SelectScene {
	Reset,
	Game,
};

Scene* scene = nullptr;

void SceneChange(SelectScene& scene_);

using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	Initialize(L"LE3D_16_チバ_ダイチ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	scene = new GameScene;
	scene->SetUp();

	SelectScene sceneSelect = SelectScene::Game;

#pragma region 汎用機能初期化
	// ImGuiManagerインスタンスの取得
	ImGuiManager* imguiManager_ = ImGuiManager::GetInstance();
#pragma endregion
	// メインループ
	while (true) {
		// エンジンの更新
		if (Update()) {
			break;
		}

		if (Input::GetInstance()->PushKey(DIK_ESCAPE)) {
			break;
		}

		// シーンの更新
		scene->Update();

		// ImGui受付開始
		imguiManager_->Begin();

		scene->DrawImGui();

		// ImGui受付開始
		imguiManager_->End();

		// 描画開始
		dxCommon->PreDraw();

		// ここに描画処理を記述する

		// シーンの描画
		scene->Draw();
		// ImGui描画
		imguiManager_->Draw();



		// 描画終了
		dxCommon->PostDraw();

		if (scene->IsFinish()) {
			SceneChange(sceneSelect);
		}
	}
	// シーンのリソースを削除
	scene->Delete();

	delete scene;
	// ゲームシーンの解放
	scene = nullptr;

	// エンジンの終了処理
	Finalize();

	return 0;
}

void SceneChange(SelectScene& scene_) {
	// シーンを切り替える順番
	std::map<SelectScene, SelectScene> selectScene{
	    {SelectScene::Reset, SelectScene::Game },
	    {SelectScene::Game,  SelectScene::Reset},
	};
	// シーンの切り替え
	scene_ = selectScene[scene_];
	// シーンのリソースを削除
	scene->Delete();
	delete scene;
	// シーンに該当する関数を生成
	std::map<SelectScene, Scene*> sceneNext{
	    {SelectScene::Reset, new ResetScene()},
        {SelectScene::Game,  new GameScene() }
    };
	// シーンを生成する
	scene = sceneNext[scene_];
	scene->SetUp();
}
