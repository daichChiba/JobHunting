#include "PauseMenu.h"

using namespace KamataEngine;
using namespace FileJson;

void PauseMenu::Initilize() {
	fileAccessor_ = new FileAccessor(filePath_);

	// 背景の初期化
	backScreenPos_ = fileAccessor_->Read("pauseBackScreen", "pos", Vector2());
	backScreenSize_ = fileAccessor_->Read("pauseBackScreen", "size", KamataEngine::Vector2());
	backScreenColor_ = fileAccessor_->Read("pauseBackScreen", "Color", KamataEngine::Vector4());
	backScreenTh_ = TextureManager::Load("white1x1.dds");
	backScreenSprite_ = Sprite::Create(backScreenTh_, backScreenPos_);
	backScreenSprite_->SetAnchorPoint({0.5f, 0.5f});
	backScreenSprite_->SetSize(backScreenSize_);
	backScreenSprite_->SetColor(backScreenColor_);

	// メインページの初期化
	if (mainPage_ == nullptr) {
		mainPage_ = new PausePage();
	}
}

void PauseMenu::Update(const XINPUT_STATE& xinput, const XINPUT_STATE& preXinput) {
	// ポーズ開閉入力
	bool openTriggered = Input::GetInstance()->ReleseKey(DIK_ESCAPE) || (xinput.Gamepad.wButtons & XINPUT_GAMEPAD_START && preXinput.Gamepad.wButtons == 0);

	// ポーズボタンが押された場合
	if (openTriggered) {
		if (!IsOpen() && mainPage_ != nullptr) {
			mainPage_->ResetCursor();
			PushPage(mainPage_);
		} else if (IsOpen()) {
			PopPage();
		}
		return;
	}

	// ページがない場合は閉じる
	if (!IsOpen()) {
		return;
	}

	bool isMoveUp = false;
	bool isMoveDown = false;

	// コントローラーのスティックでの入力処理
	if (xinput.Gamepad.sThumbLY > 20000) {
		if (isLStickPushed_ == false) {
			isMoveUp = true;
			isLStickPushed_ = true;
		}
	} else if (xinput.Gamepad.sThumbLY < -20000) {
		if (isLStickPushed_ == false) {
			isMoveDown = true;
			isLStickPushed_ = true;
		}
	} else {
		isLStickPushed_ = false;
	}
	// コントローラーのボタンとキーボードでの入力処理
	if (Input::GetInstance()->ReleseKey(DIK_W) || (xinput.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && !preXinput.Gamepad.wButtons)) {
		isMoveUp = true;
	}
	if (Input::GetInstance()->ReleseKey(DIK_S) || (xinput.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && !preXinput.Gamepad.wButtons)) {
		isMoveDown = true;
	}
	// 決定ボタンの処理
	bool isDecide = (Input::GetInstance()->ReleseKey(DIK_SPACE) || (xinput.Gamepad.wButtons & XINPUT_GAMEPAD_A && !preXinput.Gamepad.wButtons));

	// 現在のページに入力状況を委譲
	if (!pageStack_.empty()) {
		pageStack_.back()->Update(isMoveUp, isMoveDown, isDecide);
	}

	// Bボタンで前のページに戻る
	bool isBack = (xinput.Gamepad.wButtons & XINPUT_GAMEPAD_B && !preXinput.Gamepad.wButtons);
	if (isBack) {
		PopPage();
	}
}

void PauseMenu::Draw() {
	// 背景描画
	backScreenSprite_->Draw();

	if (!pageStack_.empty()) {
		int cursor = pageStack_.back()->GetCursor();
		pageStack_.back()->Draw(cursor);
	}
}

void PauseMenu::Delete() {
	// メモリ開放
	delete fileAccessor_;
	if (mainPage_ != nullptr) {
		delete mainPage_;
		mainPage_ = nullptr;
	}
}

void PauseMenu::DrawImGui() {
	//
#ifdef _DEBUG
	if (!IsOpen()) {
		return;
	}
	ImGui::Begin("PauseMenu");
	ImGui::Text("Pause Menu Settings");
	ImGui::Separator();

	//背景の調整
	if (ImGui::CollapsingHeader("BackScreen")) {
		ImGui::DragFloat2("BackScreen Pos", &backScreenPos_.x);
		ImGui::DragFloat2("BackScreen Size", &backScreenSize_.x);
		ImGui::DragFloat4("BackScreen Color", &backScreenColor_.x);

		//リアルタイム反映
		backScreenSprite_->SetPosition(backScreenPos_);
		backScreenSprite_->SetSize(backScreenSize_);
		backScreenSprite_->SetColor(backScreenColor_);
	}
	//現在開いているページの調整
	PausePage* currentPage = pageStack_.back();
	if (currentPage != nullptr) {
		if (ImGui::CollapsingHeader("Current Page Buttons")) {
			for (int i = 0; i < currentPage->GetButtonCount() ; i++) {
				MenuButton& btn = currentPage->GetButton(i);

				//ボタンのJsonキーをラベルにして区別する
				if (ImGui::TreeNode(btn.jsonKey.c_str())) {
					ImGui::DragFloat2("Pos", &btn.pos.x);
					ImGui::DragFloat2("Size", &btn.size.x);

					// リアルタイム反映
					btn.sprite->SetPosition(btn.pos);
					btn.sprite->SetSize(btn.size);

					ImGui::TreePop();
				}
			}
		}

		//Jsonファイルに保存
		if (ImGui::Button("Save to Json")) {
			//背景の保存
			fileAccessor_->Write("pauseBackScreen", "pos", backScreenPos_);
			fileAccessor_->Write("pauseBackScreen", "size", backScreenSize_);
			fileAccessor_->Write("pauseBackScreen", "Color", backScreenColor_);

			//現在のページのボタンを保存
			if (currentPage != nullptr) {
				for (int i = 0; i < currentPage->GetButtonCount(); i++) {
					MenuButton& btn = currentPage->GetButton(i);
					fileAccessor_->Write(btn.jsonKey, "pos", btn.pos);
					fileAccessor_->Write(btn.jsonKey, "size", btn.size);
				}
			}

			//jsonファイルに書き出し
			fileAccessor_->Save();
		}

	}

	ImGui::End();
#endif // _DEBUG
}

void PauseMenu::PushPage(PausePage* page) {
	// ページの階層を追加
	pageStack_.push_back(page);
}

void PauseMenu::PopPage() {
	// ページを閉じる
	if (!pageStack_.empty()) {
		pageStack_.pop_back();
	}
}

void PauseMenu::RegisterButton(PauseID id, ButtonCreator creator) {
	// ボタンのファクトリーを登録
	buttonFactory_[id] = creator;
}

void PauseMenu::SetAction(PauseID id, std::function<void()> action) {
	//
	actionMap_[id] = action;
}

PausePage* PauseMenu::BuilldPage(const std::vector<PauseID>& order) {
	PausePage* page = new PausePage();

	for (auto id : order) {
		// ファクトリーからUIを生成
		auto factoryIt = buttonFactory_.find(id);
		if (factoryIt == buttonFactory_.end()) {
			assert(false && "Button not registered in factory");
			continue;
		}
		MenuButton btn = factoryIt->second(fileAccessor_);

		// アクションを注入
		auto actionIt = actionMap_.find(id);
		if (actionIt != actionMap_.end()) {
			btn.onSelect = actionIt->second;
		}

		page->AddButton(btn);
	}
	return page;
}
