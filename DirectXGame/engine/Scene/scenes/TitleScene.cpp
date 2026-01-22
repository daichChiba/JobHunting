#include "TitleScene.h"

using namespace KamataEngine;
using namespace FileJson;
TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {

	fileAccessor_ = new FileAccessor(file);
	speed = fileAccessor_->Read(fileMain, "speed", float());
	
	resetSpeed = speed;
	backScreenPos = fileAccessor_->Read(fileMain, "backScreenPos", Vector2());
	titelPos = fileAccessor_->Read(fileMain, "titelPos", Vector2());
	pushToSpacePos = fileAccessor_->Read(fileMain, "pushToSpacePos", Vector2());
	stopTitelPos = fileAccessor_->Read(fileMain, "stopTitelPos", Vector2());

	backScreenTh_ = TextureManager::Load("Titel/backScreen.png");
	backScreenSpite = Sprite::Create(backScreenTh_, backScreenPos);
	backScreenSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));

	titelTh_ = TextureManager::Load("Titel/titel.png");
	titelSpite = Sprite::Create(titelTh_, titelPos);
	titelSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));

	pushToSpaceTh_ = TextureManager::Load("Titel/PushToSpace.png");
	pushToSpaceSpite = Sprite::Create(pushToSpaceTh_, pushToSpacePos);
	pushToSpaceSpite->SetAnchorPoint(Vector2(0.5f, 0.5f));
}

void TitleScene::Update() {
	preXinput_ = xinput_;
	XInputGetState(0, &xinput_);

	if (input_->GetInstance()->ReleseKey(DIK_SPACE)||xinput_.Gamepad.wButtons&XINPUT_GAMEPAD_A) {
		if (!isCleck) {
			isCleck = true;
			fade_->Start(FadeID::FadeOut, 1);
			isStart = false;
		}
	}

	if (!isStart) {
		if (fade_->IsFinished() == true) {
			isFinish = true;
			nextScene_ = SceneID::Demo;
		}
	}

	titelSpite->SetPosition(titelPos);
	backScreenSpite->SetPosition(backScreenPos);
	pushToSpaceSpite->SetPosition(pushToSpacePos);
	buttonCount++;
	if (isMove) {
		if (!isJump) {
			if (titelPos.y < stopTitelPos.y) {
				titelPos.y += speed;
				speed += speed;
			} else {
				isJump = true;
				speed = resetSpeed;
			}
		}

		if (isJump) {
			if (jumpCount < kJumpCount) {
				jumpCount++;
				titelPos.y -= speed;
			} else {
				isJump = false;
				jumpCount = kResetCount;
				speed = resetSpeed;
			}
		}
	}

	fade_->Update();
}

void TitleScene::Draw() {
	// 背景スプライト描画前処理
	Sprite::PreDraw();

	backScreenSpite->Draw();

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

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	titelSpite->Draw();

	if (buttonCount % kCountFrame_ >= kDrawCount_) {
		pushToSpaceSpite->Draw();
	}

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitleScene::Delete() { delete fade_; }

void TitleScene::DrawImGui() {
#ifdef _DEBUG

	ImGui::Begin("TitelScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);
	if (ImGui::Button("save")) {
		fileAccessor_->Write(fileMain, "backScreenPos", Vector3(backScreenPos.x, backScreenPos.y, 0.0f));
		fileAccessor_->Write(fileMain, "titelPos", Vector3(titelPos.x, titelPos.y, 0.0f));
		fileAccessor_->Write(fileMain, "pushToSpacePos", Vector3(pushToSpacePos.x, pushToSpacePos.y, 0.0f));
		fileAccessor_->Write(fileMain, "stopTitelPos", Vector3(stopTitelPos.x, stopTitelPos.y, 0.0f));
		fileAccessor_->Write(fileMain, std::to_string(speed) /*"speed"*/, speed);
		fileAccessor_->Save();
	}
	ImGui::Checkbox("isMove", &isMove);
	// ImGui::Checkbox("isJump", &isJump);
	ImGui::DragFloat2("backScreenPos", &backScreenPos.x);
	ImGui::DragFloat2("titelPos", &titelPos.x);
	ImGui::DragFloat2("pushToSpacePos", &pushToSpacePos.x);
	ImGui::DragFloat2("stopTitelPos", &stopTitelPos.x);
	ImGui::DragFloat("Speed", &speed);
	ImGui::End();
#endif // _DEBUG
}

SceneID TitleScene::NextScene() const { return nextScene_; }


