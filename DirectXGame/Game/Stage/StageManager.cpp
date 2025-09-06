#include "StageManager.h"

using namespace KamataEngine;

void StageManager::Initialize(int ereaNum_, int stageNum_, std::string stage_) {
	stages_ = new Stage();
	stages_->Initialize(ereaNum_, stageNum_, stage_);
 }

void StageManager::Update() {
	stages_->Update();
}

void StageManager::Draw(KamataEngine::Camera* camera_) {
	stages_->Draw(camera_);
}
