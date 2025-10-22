#include "GameCamera.h"
#include "engine/ect/Easings.h"
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
	targetPos_ = fileAccessor_->ReadVector3(fileMain, "Pos1", Vector3());
	// 初期化
	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = fileAccessor_->ReadVector3(fileMain, "Pos0", Vector3());
	camera_->farZ = fileAccessor_->Read(fileMain, "farZ", float());
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

	// 更新
	camera_->UpdateMatrix();
}

void GameCamera::ImGuiDraw() {
#ifdef _DEBUG
	const char* listBox_[] = {"1stPos", "2ndPos", "3rdPos"};
	ImGui::Begin("GameCamera");
	// ImGui::ListBox("CameraPos", &listBox_num, listBox_, IM_ARRAYSIZE(listBox_), 3);
	ImGui::Combo("cameraPos", &camera_posType, listBox_, IM_ARRAYSIZE(listBox_), cameraTypeMax);
	if (ImGui::Button("save")) {
		// if (listBox_num == 1) {
		//	fileAccessor_->WriteVector3(fileMain, "1stPos", camera_->translation_);
		// }
		fileAccessor_->WriteVector3(fileMain, std::string("Pos") + std::to_string(camera_posType), camera_->translation_);
		fileAccessor_->Save();
	};
	if (ImGui::Button("set")) {
		camera_->translation_ = fileAccessor_->ReadVector3(fileMain, std::string("Pos") + std::to_string(camera_posType), Vector3());
	}
	if (ImGui::Button("Move")) {
		isMove = true;
		startPos_ = camera_->translation_;
		if (camera_posType < cameraTypeMax) {
			camera_posType += 1;
			targetPos_ = fileAccessor_->ReadVector3(fileMain, std::string("Pos") + std::to_string(camera_posType), Vector3());
		}
	}
	ImGui::DragFloat3("pos", &camera_->translation_.x, 0.01f);
	ImGui::SliderFloat3("pos", &camera_->translation_.x, -50.0f, 50.0f);
	ImGui::DragInt("listBox_", &camera_posType);
	ImGui::End();

#endif // _DEBUG
}

void GameCamera::CameraNextPos() {
	startPos_ = camera_->translation_;
	if (camera_posType < cameraTypeMax) {
		targetPos_ = fileAccessor_->ReadVector3(fileMain, std::string("Pos") + std::to_string(camera_posType), Vector3());
	}
}

void GameCamera::SetCameraPos() {
	camera_->translation_ = fileAccessor_->ReadVector3(fileMain, std::string("Pos")
		+ std::to_string(camera_posType), Vector3());
}
