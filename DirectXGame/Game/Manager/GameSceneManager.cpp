#include "GameSceneManager.h"
#include "../Player/Player.h"


using namespace KamataEngine;
void GameSceneManager::Initialize() {
	camera_ = new Camera();
	camera_->Initialize();
	camera_->farZ = 1000.0f;
	player_ = new Player;
	player_->Initialize();
}
void GameSceneManager::Update() {
	camera_->UpdateMatrix();
	player_->Update();
}
void GameSceneManager::Draw() {
	player_->Draw(*camera_);
}
void GameSceneManager::DrawImGui() {
	player_->DrawImGui();
}
void GameSceneManager::Delete() {
	player_->Delete();
}