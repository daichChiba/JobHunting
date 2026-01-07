#include "GameCamera.h"
#include "engine/Game/MapChip/MapChip.h"
#include "engine/Game/Object/Lever/Lever.h"
#include "engine/Game/Object/PushButton/PushButton.h"
#include "engine/Game/Player/Player.h"
#include "engine/ect/Easings.h"
#include "Game/Object/ObjectManager.h"

using namespace KamataEngine;
using namespace FileJson;

GameCamera::GameCamera() {
	//
}

GameCamera::~GameCamera() {
	//
}

void GameCamera::Initialize() {

	isMove = false;

	fileAccessor_ = new FileAccessor(filePath);
	camera_posType = fileAccessor_->Read(fileMain, "camera_posType", int());
	targetPos_ = fileAccessor_->Read(fileMain, "Pos1", Vector3());
	startCameraPos_ = Vector3(player_->GetPlayerPos().x, player_->GetPlayerPos().y, player_->GetPlayerPos().z - 6.0f);
	// 初期化
	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = startCameraPos_ /*fileAccessor_->ReadVector3(fileMain, "Pos0", Vector3())*/;
	camera_->farZ = fileAccessor_->Read(fileMain, "farZ", float());
	fileAccessor_->Write(fileMain, "Pos0", startCameraPos_);
	fileAccessor_->Save();
}
void GameCamera::Update() {
	if (isMove) {
		float duration = static_cast<float>(kMoveTimer) / 60.0f;
		if (currentTime < duration) {
			Vector3 newPos = Easings::EaseInTime(startPos_, targetPos_, currentTime, duration);
			camera_->translation_ = newPos;
			currentTime += 1.0f / 60.0f; // 1フレームごとに時間を進める(60fpsを想定)
		} else {
			isMove = false;
			currentTime = 0.0f;
		}
	}
	SetReactionCamera();

	SetClearCamera();

	// 更新
	camera_->UpdateMatrix();
}

void GameCamera::ImGuiDraw() {
#ifdef _DEBUG
	const char* listBox_[] = {"1stPos", "2ndPos", "3rdPos"};
	ImGui::Begin("GameCamera");
	ImGui::Combo("cameraPos", &camera_posType, listBox_, IM_ARRAYSIZE(listBox_), cameraTypeMax);
	if (ImGui::Button("save")) {

		fileAccessor_->Write(fileMain, std::string("Pos") + std::to_string(camera_posType), camera_->translation_);
		fileAccessor_->Save();
	};
	if (ImGui::Button("set")) {
		camera_->translation_ = fileAccessor_->Read(fileMain, std::string("Pos") + std::to_string(camera_posType), Vector3());
	}
	if (ImGui::Button("Move")) {
		isMove = true;
		startPos_ = camera_->translation_;
		if (camera_posType < cameraTypeMax) {
			camera_posType += 1;
			targetPos_ = fileAccessor_->Read(fileMain, std::string("Pos") + std::to_string(camera_posType), Vector3());
		}
	}
	ImGui::DragFloat3("pos", &camera_->translation_.x, 0.01f);
	ImGui::SliderFloat3("pos", &camera_->translation_.x, -50.0f, 50.0f);
	ImGui::DragInt("listBox_", &camera_posType);
	//ImGui::Checkbox("isAllReaction", &isAllReaction);
	ImGui::End();

#endif // _DEBUG
}

void GameCamera::CameraNextPos() {
	startPos_ = camera_->translation_;
	if (camera_posType < cameraTypeMax) {
		targetPos_ = fileAccessor_->Read(fileMain, std::string("Pos") + std::to_string(camera_posType), Vector3());
	}
}

void GameCamera::SetCameraPos() { camera_->translation_ = fileAccessor_->Read(fileMain, std::string("Pos") + std::to_string(camera_posType), Vector3()); }

void GameCamera::SetClearCamera() {
	//
	startPos_ = camera_->translation_;

	if (player_->GetIsGoal()) {
		float duration = static_cast<float>(kMoveTimer) / 60.0f;
		if (currentTime < duration) {
			Vector3 newPos = Easings::EaseInTime(startPos_, targetPos_, currentTime, duration);
			camera_->translation_ = newPos;
			currentTime += 1.0f / 60.0f; // 1フレームごとに時間を進める(60fpsを想定)
		} else {
			currentTime = 0.0f;
		}
		targetPos_ = Vector3(player_->GetPlayerPos().x, player_->GetPlayerPos().y, player_->GetPlayerPos().z - 6.0f);
	}
}

void GameCamera::SetReactionCamera() {
	if (player_->GetIsGoal() == false) {
		startPos_ = camera_->translation_;

		if (objectManager_->GetIsAllLever()) {
			if (isReactionStart == false) {
				player_->SetIsMove(false);
			}
			isReactionStart = true;
		}

		if (isReactionStart) {
			if (isReaction == false) {
				float duration = static_cast<float>(kMoveTimer) / 60.0f;
				if (currentTime < duration) {
					Vector3 newPos = Easings::EaseInTime(startPos_, targetPos_, currentTime, duration);
					camera_->translation_ = newPos;
					currentTime += 1.0f / 60.0f; // 1フレームごとに時間を進める(60fpsを想定)
				} else {
					currentTime = 0.0f;
					isReaction = true;
				}
				targetPos_ = Vector3(mapChip_->GetObjectPos(MapChipID::kGoal).x, mapChip_->GetObjectPos(MapChipID::kGoal).y, mapChip_->GetObjectPos(MapChipID::kGoal).z - 6.0f);
			} else {
				if (isReactionEnd == false) {
					if (ReactionTimer < kReactionTimer) {
						ReactionTimer++;
					} else {
						isReactionEnd = true;
					}
				} else {
					if (endReaction < kEndReaction) {
						endReaction++;
					} else {
						float duration = static_cast<float>(kMoveTimer) / 60.0f;
						if (currentTime < duration) {
							Vector3 newPos = Easings::EaseInTime(startPos_, targetPos_, currentTime, duration);
							camera_->translation_ = newPos;
							currentTime += 1.0f / 60.0f; // 1フレームごとに時間を進める(60fpsを想定)
						} else {
							currentTime = 0.0f;
							player_->SetIsMove(true);

						}
						targetPos_ = fileAccessor_->Read(fileMain, std::string("Pos") + std::to_string(2), Vector3());
					}
				}
			}
		}
	}
}
