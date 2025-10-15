#include "Player.h"
#include "../MapChip/MapChip.h"

using namespace KamataEngine;

Player::Player() {}
Player::~Player() {}
void Player::Initialize(MapChip mapchip) {
	//model_->StaticInitialize();
	//model_ = Model::CreateFromOBJ("Player", true);
	Model* model = nullptr;
	model = Model::CreateFromOBJ("Player", true);
	model_ = model;

	worldTransform_.Initialize();
	SetUpPos(mapchip);
	//worldTransform_.translation_ = pos_;
	worldTransform_.rotation_.y = 1.0f;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
}
void Player::Update() {
	worldTransform_.translation_ = pos_;
	Move();
	worldTransform_.UpdateMatrix();
}
void Player::Draw(Camera& camera) {
	model_->Draw(worldTransform_, camera);
}
void Player::Delete() {
	delete model_;
	model_ = nullptr;
}
void Player::DrawImGui() {
	//このまま記入しても大丈夫
#ifdef _DEBUG


	ImGui::Text("PlayerTest");
#endif // _DEBUG
}

void Player::Move() {
	if (Input::GetInstance()->PushKey(DIK_D)) {
		pos_.x += playerSpeed;
	} else if (Input::GetInstance()->PushKey(DIK_A)) {
		pos_.x -= playerSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_W)) {
		pos_.y += playerSpeed;
	} else if (Input::GetInstance()->PushKey(DIK_S)) {
		pos_.y -= playerSpeed;
	}
}

void Player::SetUpPos(MapChip mapChip) {
	//worldTransform_.translation_ = mapChip.GetPlayerPos();
	pos_ = mapChip.GetPlayerPos();
}
