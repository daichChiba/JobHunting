#include "Player.h"
#include "../MapChip/MapChip.h"

using namespace KamataEngine;
using namespace FileJson;
using namespace MathUtility;

Player::Player() {}
Player::~Player() {}
void Player::Initialize(MapChip mapchip) {
	// model_->StaticInitialize();
	// model_ = Model::CreateFromOBJ("Player", true);

	fileAccessor_ = new FileAccessor(filePath);

	Model* model = nullptr;
	model = Model::CreateFromOBJ("Player", true);
	model_ = model;

	worldTransform_.Initialize();

	// worldTransform_.translation_ = pos_;

	worldTransform_.scale_ = fileAccessor_->ReadVector3(fileMain, "scale", Vector3());
	speedX = fileAccessor_->Read(fileMain, "speedX", float());
	size_ = fileAccessor_->ReadVector3(fileMain, "size", Vector3());
	kBlank = fileAccessor_->Read(fileMain, "kBlank", float());
	kDeceleration = fileAccessor_->Read(fileMain, "kDeceleration", float());
	kLimitXSpeed = fileAccessor_->Read(fileMain, "kLimitXSpeed", float());
	kJumpAcceleration = fileAccessor_->Read(fileMain, "kJumpAcceleration", float());

	// 後で消す
	worldTransform_.rotation_ = fileAccessor_->ReadVector3(fileMain, "rotation", Vector3());

	mapchipData_ = std::unique_ptr<MapChip>(new MapChip(mapchip));
	SetUpPos();
}
void Player::Update() {
	if (isMove) {
		InputMove();
	}

	worldTransform_.UpdateMatrix();
}
void Player::Draw(const Camera& camera) { model_->Draw(worldTransform_, camera); }
void Player::Delete() {
	delete model_;
	model_ = nullptr;
}
void Player::DrawImGui() {
	// このまま記入しても大丈夫
#ifdef _DEBUG

	ImGui::Text("PlayerTest");
#endif // _DEBUG
}

void Player::InputMove() {
	worldTransform_.translation_ = pos_;
	moveKey.isMove = false;

	if (Input::GetInstance()->PushKey(DIK_D)) {
		moveKey.moveKey_ = MoveKeys::Right;
		moveKey.isMove = true;
	} else if (Input::GetInstance()->PushKey(DIK_A)) {
		moveKey.moveKey_ = MoveKeys::Left;
		moveKey.isMove = true;
	}
	if (Input::GetInstance()->PushKey(DIK_W)) {
		moveKey.moveKey_ = MoveKeys::Up;
		moveKey.isMove = true;
	} else if (Input::GetInstance()->PushKey(DIK_S)) {
		moveKey.moveKey_ = MoveKeys::Down;
		moveKey.isMove = true;
	}
}

void Player::UpdateVelocity() {
	if (onGround_) {
		if (moveKey.isMove) {
			if (moveKey.moveKey_ == MoveKeys::Right) {
				velocity_.x += speedX;
			} else if (moveKey.moveKey_ == MoveKeys::Left) {
				velocity_.x -= speedX;
			} else {
				velocity_.x *= (1.0f - kDeceleration);
			}
			velocity_.x = std::clamp(velocity_.x, -kLimitXSpeed, kLimitXSpeed);

			if (std::abs(velocity_.x) <= 0.01f) {
				velocity_.x = 0.0f;
			}

			if (moveKey.moveKey_==MoveKeys::Up) {
				velocity_.y += kJumpAcceleration / 60.0f;
			}
		}
	}
}

void Player::SetUpPos() {
	// worldTransform_.translation_ = mapChip.GetPlayerPos();
	pos_ = mapchipData_->GetObjectPos(MapChipID::PlayerStart);
	worldTransform_.translation_ = pos_;
}

// void Player::UpdateOnGround(const CollisionMapInfo& info) {
//	//
// }
//
// KamataEngine::Vector3 Player::CornerPos(const KamataEngine::Vector3& center, Corner corner) {
//	//
//	return KamataEngine::Vector3();
// }
//
// void Player::CheckMapCollision(CollisionMapInfo& info) {
//	//
// }
//
// void Player::CheckMapCollisionUp(CollisionMapInfo& info) {
//	//
// }
//
// void Player::CheckmapCollisionDown(CollisionMapInfo& info) {
//	//
// }
//
// void Player::CheckMapCollisionRight(CollisionMapInfo& info) {
//	//
// }
//
// void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
//	//
// }
