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
	fileAccessor_ = new FileAccessor(filePath);

	// 初期化
	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = fileAccessor_->ReadVector3(fileMain, "Pos0", Vector3());
	camera_->farZ = 1000.0f;
}
void GameCamera::Update() {
	// 更新
	camera_->UpdateMatrix();
}

void GameCamera::ImGuiDraw() {
#ifdef _DEBUG
	const char* listBox_[] = {"1stPos", "2ndPos", "3rdPos"};
	static int listBox_num = 1;
	ImGui::ListBox("CameraPos", &listBox_num, listBox_, IM_ARRAYSIZE(listBox_), 3);
	if (ImGui::Button("save")) {
		//if (listBox_num == 1) {
		//	fileAccessor_->WriteVector3(fileMain, "1stPos", camera_->translation_);
		//}
		fileAccessor_->WriteVector3(fileMain, std::string("Pos") + std::to_string(listBox_num), camera_->translation_);
		fileAccessor_->Save();
	};
	if (ImGui::Button("set")) {
		if (listBox_num) {
			camera_->translation_ = fileAccessor_->ReadVector3(fileMain, std::string("Pos") + std::to_string(listBox_num), Vector3());
		}
	}
	ImGui::DragFloat3("pos", &camera_->translation_.x, 0.01f);
	ImGui::SliderFloat3("pos", &camera_->translation_.x, -50.0f, 50.0f);
	ImGui::End();

#endif // _DEBUG
}
