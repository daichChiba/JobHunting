#define NOMINMAX
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
	kGroundSearchHeight = fileAccessor_->Read(fileMain, "kGroundSearchHeight", float());
	kAttenuationLanding = fileAccessor_->Read(fileMain, "kAttenuationLanding", float());

	// 後で消す
	worldTransform_.rotation_ = fileAccessor_->ReadVector3(fileMain, "rotation", Vector3());

	mapChipData_ = std::unique_ptr<MapChip>(new MapChip(mapchip));
	SetUpPos();
}
void Player::Update() {


	if (isMove) {
		if (Input::GetInstance()->PushKey(DIK_R)) {
			isAlive_ = false;
		}

		InputMove();
		UpdateVelocity();

		CollisionMapInfo collisionMapInfo = {};
		collisionMapInfo.move = velocity_;
		collisionMapInfo.landing = false;
		collisionMapInfo.hitWall = false;
		collisionMapInfo.ceiling = false;
		CheckMapCollision(collisionMapInfo);
		worldTransform_.translation_ += collisionMapInfo.move;

		info_ = collisionMapInfo;

		// 天井接触による落下開始
		if (collisionMapInfo.ceiling) {
			velocity_.y = 0;
		}
		// 壁接触による減速
		if (collisionMapInfo.hitWall) {
			velocity_.x *= (1.0f - speedX);
		}

		// onGroundの更新
		UpdateOnGround(collisionMapInfo);
	}

	worldTransform_.UpdateMatrix();
}
void Player::Draw(const Camera& camera) {
	if (isAlive_) {
		model_->Draw(worldTransform_, camera);
	}
}
void Player::Delete() {
	delete model_;
	model_ = nullptr;
}
void Player::DrawImGui() {
	// このまま記入しても大丈夫
#ifdef _DEBUG

	ImGui::Text("PlayerTest");
	ImGui::Checkbox("collisionMapInfo.ceiling", &info_.ceiling);
	ImGui::Checkbox("collisionMapInfo.landing", &info_.landing);
	ImGui::Checkbox("collisionMapInfo.hitwall", &info_.hitWall);
	ImGui::DragFloat3("size", &size_.x);
	if (ImGui::Button("save")) {
		fileAccessor_->WriteVector3(fileMain, "size", size_);
		fileAccessor_->Save();
	}

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

			if (moveKey.moveKey_ == MoveKeys::Up) {
				velocity_.y += kJumpAcceleration / 60.0f;
			}
		}
	}
}

void Player::SetUpPos() {
	// worldTransform_.translation_ = mapChip.GetPlayerPos();
	pos_ = mapChipData_->GetObjectPos(MapChipID::PlayerStart);
	worldTransform_.translation_ = pos_;
}

void Player::UpdateOnGround(const CollisionMapInfo& info) {
	//
	if (onGround_) {
		// 　ジャンプ開始
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		} else {
			Vector3 newPos = worldTransform_.translation_ + info.move;
			bool ground = false;

			// 右下点の判定
			Vector3 rightBottomPos = CornerPos(newPos, Corner::kRightBottom);
			if (mapChipData_->GetMapChipID(rightBottomPos + Vector3(0, -kGroundSearchHeight, 0)) == MapChipID::kBlock) {
				ground = true;
			}
			// 左下点の判定
			Vector3 leftBottomPos = CornerPos(newPos, Corner::kLeftBottom);
			if (mapChipData_->GetMapChipID(leftBottomPos + Vector3(0, -kGroundSearchHeight, 0)) == MapChipID::kBlock) {
				ground = true;
			}

			if (!ground) {
				onGround_ = false;
			}
		}
	} else {
		if (info.landing) {
			velocity_.x *= (1.0f - kAttenuationLanding);
			velocity_.y = 0.0f;
			onGround_ = true;
		}
	}
}
//
KamataEngine::Vector3 Player::CornerPos(const KamataEngine::Vector3& center, Corner corner) {
	Vector3 offsetTable[] = {
	    {+size_.x / 2.0f, -size_.y / 2.0f, 0}, // kRightBottom
	    {-size_.x / 2.0f, -size_.y / 2.0f, 0}, // kLeftBottom
	    {+size_.x / 2.0f, +size_.y / 2.0f, 0}, // kRightTop
	    {-size_.x / 2.0f, +size_.y / 2.0f, 0}  // kLeftTop
	};
	return center + offsetTable[static_cast<uint32_t>(corner)];
}
//
void Player::CheckMapCollision(CollisionMapInfo& info) {
	//
	CheckMapCollisionUp(info);
	CheckMapCollisionDown(info);
	CheckMapCollisionRight(info);
	CheckMapCollisionLeft(info);
}

void Player::CheckMapCollisionUp(CollisionMapInfo& info) {
	if (info.move.y <= 0.0f) {
		return;
	}

	Vector3 nextPos = worldTransform_.translation_ + info.move;
	bool hit = false;
	MapChip::MapChipIndex indexSet;
	MapChip::Rect rect{};

	// 右上と左上の角の位置
	Vector3 rightTopCorner = CornerPos(nextPos, Corner::kRightTop);
	Vector3 leftTopCorner = CornerPos(nextPos, Corner::kLeftTop);

	// 右上点の判定
	indexSet = mapChipData_->GetMapChipIndex(rightTopCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(rightTopCorner);
	}
	// 左上点の判定
	indexSet = mapChipData_->GetMapChipIndex(leftTopCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(leftTopCorner);
	}

	if (hit) {
		info.move.y = std::max(0.0f, (rect.bottom - (worldTransform_.translation_.y + size_.y / 2.0f + kBlank)));
		info.ceiling = true;
	}
}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) {
	//
	if (info.move.y >= 0) {
		return;
	}
	Vector3 nextPos = worldTransform_.translation_ + info.move;
	bool hit = false;
	MapChip::MapChipIndex indexSet;
	MapChip::Rect rect{};

	// 右下と左下の角の位置
	Vector3 rightBottomCorner = CornerPos(nextPos, Corner::kRightBottom);
	Vector3 leftBottomCorner = CornerPos(nextPos, Corner::kLeftBottom);

	// 右下点の判定
	indexSet = mapChipData_->GetMapChipIndex(rightBottomCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(rightBottomCorner);
	}
	// 左下点の判定
	indexSet = mapChipData_->GetMapChipIndex(leftBottomCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(leftBottomCorner);
	}

	if (hit) {
		info.move.y = std::min(0.0f, rect.top - (worldTransform_.translation_.y - size_.y / 2.0f - kBlank));
		info.landing = true;
	}
}

void Player::CheckMapCollisionRight(CollisionMapInfo& info) {
	if (info.move.x <= 0) {
		return;
	}

	Vector3 nextPos = worldTransform_.translation_ + info.move;
	bool hit = false;
	MapChip::MapChipIndex indexSet;
	MapChip::Rect rect{};

	// 右上と右下の角の位置
	Vector3 rightTopCorner = CornerPos(nextPos, Corner::kRightTop);
	Vector3 rightBottomCorner = CornerPos(nextPos, Corner::kRightBottom);

	// 右上点の判定
	indexSet = mapChipData_->GetMapChipIndex(rightTopCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(rightTopCorner);
	}
	// 右下点の判定
	indexSet = mapChipData_->GetMapChipIndex(rightBottomCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(rightBottomCorner);
	}

	if (hit) {
		info.move.x = std::min(0.0f, rect.left - (worldTransform_.translation_.x + size_.x / 2.0f + kBlank));
		info.hitWall = true;
	}
}

void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
	if (info.move.x >= 0) {
		return;
	}

	Vector3 nextPos = worldTransform_.translation_ + info.move;
	bool hit = false;
	MapChip::MapChipIndex indexSet;
	MapChip::Rect rect{};

	// 左上と左下の角の位置
	Vector3 leftTopCorner = CornerPos(nextPos, Corner::kLeftTop);
	Vector3 leftBottomCorner = CornerPos(nextPos, Corner::kLeftBottom);

	// 左上点の判定
	indexSet = mapChipData_->GetMapChipIndex(leftTopCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(leftTopCorner);
	}
	// 左下点の判定
	indexSet = mapChipData_->GetMapChipIndex(leftBottomCorner);
	if (mapChipData_->GetMapChipID(indexSet) == MapChipID::kBlock) {
		hit = true;
		rect = mapChipData_->GetMapRect(leftBottomCorner);
	}

	if (hit) {
		info.move.x = std::max(0.0f, rect.right - (worldTransform_.translation_.x - size_.x / 2.0f - kBlank));
		info.hitWall = true;
	}
}
