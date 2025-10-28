#include "Player.h"
#include "../MapChip/MapChip.h"

using namespace KamataEngine;
using namespace FileJson;
using namespace MathUtility;

Player::Player() {}
Player::~Player() {}
void Player::Initialize(MapChip mapchip) {
	//model_->StaticInitialize();
	//model_ = Model::CreateFromOBJ("Player", true);

	fileAccessor_ = new FileAccessor(filePath);


	Model* model = nullptr;
	model = Model::CreateFromOBJ("Player", true);
	model_ = model;

	worldTransform_.Initialize();

	//worldTransform_.translation_ = pos_;

	worldTransform_.scale_ = fileAccessor_->ReadVector3(fileMain, "scale", Vector3());
	playerSpeed = fileAccessor_->Read(fileMain, "speed", float());
	size_ = fileAccessor_->ReadVector3(fileMain, "size", Vector3());
	kBlank = fileAccessor_->Read(fileMain, "kBlank", float());

	// 後で消す
	worldTransform_.rotation_ = fileAccessor_->ReadVector3(fileMain, "rotation", Vector3());

	mapchipData_ = std::unique_ptr<MapChip>(new MapChip(mapchip));
	SetUpPos();
}
void Player::Update() {
	if(isMove){
		Move();
	}

	worldTransform_.UpdateMatrix();
}
void Player::Draw(const Camera& camera) {
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
	worldTransform_.translation_ = pos_;

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

void Player::SetUpPos() {
	//worldTransform_.translation_ = mapChip.GetPlayerPos();
	pos_ = mapchipData_->GetObjectPos(MapChipID::PlayerStart);
	worldTransform_.translation_ = pos_;
}

//void Player::UpdateOnGround(const CollisionMapInfo& info) {
//	//
//}
//
//KamataEngine::Vector3 Player::CornerPos(const KamataEngine::Vector3& center, Corner corner) {
//	//
//	return KamataEngine::Vector3();
//}
//
//void Player::CheckMapCollision(CollisionMapInfo& info) {
//	//
//}
//
//void Player::CheckMapCollisionUp(CollisionMapInfo& info) {
//	//
//}
//
//void Player::CheckmapCollisionDown(CollisionMapInfo& info) {
//	//
//}
//
//void Player::CheckMapCollisionRight(CollisionMapInfo& info) {
//	//
//}
//
//void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
//	//
//}
