#define NOMINMAX
#include "Player.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Object/Objects/Goal/Goal.h"
#include "Game/Object/Objects/Lever/Lever.h"
#include "Game/Object/Manager/ObjectManager.h"
#include "Game/Object/Objects/PushButton/PushButton.h"
#include "GameScene.h"
#include <algorithm>

using namespace KamataEngine;
using namespace FileJson;
using namespace MathUtility;

Player::Player() {}
Player::~Player() {}

void Player::Initialize(MapChip* mapchip) {
	fileAccessor_ = new FileAccessor(filePath);

	mapChipData_ = mapchip;

	Model* model = nullptr;
	model = Model::CreateFromOBJ("Player", true);
	model_ = model;

	objectColor_ = new ObjectColor();
	objectColor_->Initialize();
	objectColor_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});

	worldTransform_.Initialize();
	worldTransform_.translation_ = mapChipData_->GetObjectPos(MapChipID::PlayerStart);
	worldTransform_.scale_ = fileAccessor_->Read(fileMain, "scale", Vector3());
	size_ = fileAccessor_->Read(fileMain, "size", Vector3());
	kAcceleration = fileAccessor_->Read(fileMain, "kAcceleration", float());
	kLimitXSpeed = fileAccessor_->Read(fileMain, "kLimitXSpeed", float());
	kAttenuation = fileAccessor_->Read(fileMain, "kAttenuation", float());
	kJumpAcceleration = fileAccessor_->Read(fileMain, "kJumpAcceleration", float());
	kGravityAcceleration = fileAccessor_->Read(fileMain, "kGravityAcceleration", float());
	kLimitFallSpeed = fileAccessor_->Read(fileMain, "kLimitFallSpeed", float());
	kBlank = fileAccessor_->Read(fileMain, "kBlank", float());
	kAttennuationShift = fileAccessor_->Read(fileMain, "kAttennuationShift", float());
	kAttennuationLanding = fileAccessor_->Read(fileMain, "kAttennuationLanding", float());
	kGoalRotatoMove = fileAccessor_->Read(fileMain, "kGoalRotatoMove", float());
	goalRotationLimit = fileAccessor_->Read(fileMain, "goalRotationLimit", Vector3());
	translucentColor = fileAccessor_->Read(fileMain, "translucentColor", Vector4());
	kGoalVibration = fileAccessor_->Read(fileMain, "kGoalVibration", int());
	// 後で消す
	worldTransform_.rotation_ = fileAccessor_->Read(fileMain, "rotation", Vector3());
}
void Player::Update() {

	XInputSetState(0, &xVibration_);
	xVibration_.wLeftMotorSpeed = static_cast<unsigned short>(leftVibration);
	xVibration_.wRightMotorSpeed = static_cast<unsigned short>(rightVibration);

	if (isMove) {
		if (!isGoal_) {
			InputMove();
		}
		objectColor_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
	} else {
		objectColor_->SetColor(translucentColor);
	}
	CollisionMapInfo collisionMapInfo;

	if (!isMove) {
		velocity_ = Vector3Zero();
		collisionMapInfo.ceiling = false;
		collisionMapInfo.hitWall = false;
		collisionMapInfo.landing = false;
		return;
	}

	collisionMapInfo.move = velocity_;

	CheckMapCollision(collisionMapInfo);

	CheckMapCollisionHit(collisionMapInfo);
	CellingSwitch(collisionMapInfo);

	if (isGoal_) {
		GoalPlayerMove();
	}

	worldTransform_.UpdateMatrix();
}
void Player::Draw(const Camera& camera) {
	//
	model_->Draw(worldTransform_, camera, objectColor_);
}

void Player::Delete() {
	delete model_;
	model_ = nullptr;
	xVibration_.wLeftMotorSpeed = 0;
}
void Player::DrawImGui() {
	// このまま記入しても大丈夫
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::Text("PlayerTest");
	ImGui::Checkbox("collisionMapInfo.ceiling", &info_.ceiling);
	ImGui::Checkbox("collisionMapInfo.landing", &info_.landing);
	ImGui::Checkbox("collisionMapInfo.hitwall", &info_.hitWall);
	ImGui::Checkbox("onGround", &onGround_);
	ImGui::Checkbox("isGoal", &isGoal_);
	ImGui::Checkbox("isMove", &isMove);
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("size", &size_.x, 0.0f, 2.0f);
	ImGui::DragFloat3("velocity", &velocity_.x);
	ImGui::DragFloat("kBlank", &kBlank);
	ImGui::DragFloat("kGoalRotatoMove", &kGoalRotatoMove);
	ImGui::DragFloat3("goalRotationLimit", &goalRotationLimit.x);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation_.x);
	ImGui::SliderInt("leftVibration", &leftVibration, 0, 65535);
	ImGui::SliderInt("rightVibration", &rightVibration, 0, 65535);
	ImGui::DragFloat4("translucentColor", &translucentColor.x);
	ImGui::SliderFloat4("translucentColor", &translucentColor.x, 0.0f, 1.0f);
	ImGui::SliderInt("kGoalVibration", &kGoalVibration, 0, 65535);
	if (ImGui::Button("save")) {
		fileAccessor_->Write(fileMain, "size", size_);
		fileAccessor_->Write(fileMain, "kBlank", kBlank);
		fileAccessor_->Write(fileMain, "kGoalRotatoMove", kGoalRotatoMove);
		fileAccessor_->Write(fileMain, "goalRotationLimit", goalRotationLimit);
		fileAccessor_->Write(fileMain, "translucentColor", translucentColor);
		fileAccessor_->Write(fileMain, "kGoalVibration", kGoalVibration);
		fileAccessor_->Save();
	}
	ImGui::End();

#endif // _DEBUG
}

KamataEngine::Vector3 Player::GetWorldPos() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Player::GetAABB() {
	Vector3 worldPos = GetWorldPos();

	AABB aabb;

	aabb.min = {worldPos.x - size_.x / 2.0f, worldPos.y - size_.y / 2.0f, worldPos.z - size_.x / 2.0f};
	aabb.max = {worldPos.x + size_.x / 2.0f, worldPos.y + size_.y / 2.0f, worldPos.z + size_.x / 2.0f};

	return aabb;
}

void Player::OnCollision(const Goal* goal_) {
	(void)goal_;

	if (onGround_) {
		isGoal_ = true;
	}
}

void Player::InputMove() {
	if (onGround_) {
		float moveDirX = 0.0f;

		// 左右移動
		if (Input::GetInstance()->PushKey(DIK_D)) {
			moveDirX += 1.0f;
		}

		if (Input::GetInstance()->PushKey(DIK_A)) {
			moveDirX -= 1.0f;
		}

		float lx = xinput_.Gamepad.sThumbLX / 32767.0f;
		const float kDeadZone = 0.2f;
		if (std::abs(lx) > kDeadZone) {
			moveDirX = lx;
		}

		// --- 最終的な速度計算（共通ロジック） ---
		if (std::abs(moveDirX) > 0.01f) {
			// 加速処理
			if (moveDirX > 0) {
				velocity_.x += kAcceleration;
			} else {
				velocity_.x -= kAcceleration;
			}
		} else {
			// 入力がないなら停止
			velocity_.x = 0.0f;
		}

		velocity_.x = std::clamp(velocity_.x, -kLimitXSpeed, kLimitXSpeed);

		if (Input::GetInstance()->PushKey(DIK_W) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			velocity_.y = kJumpAcceleration;
		}
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移行
			onGround_ = false;
		}

	} else {
		// 落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}
}

//
KamataEngine::Vector3 Player::CornerPos(const KamataEngine::Vector3& center, Corner corner) {
	Vector3 offsetTable[] = {
	    {+size_.x * 0.5f, -size_.y * 0.5f, 0}, // kRightBottom
	    {-size_.x * 0.5f, -size_.y * 0.5f, 0}, // kLeftBottom
	    {+size_.x * 0.5f, +size_.y * 0.5f, 0}, // kRightTop
	    {-size_.x * 0.5f, +size_.y * 0.5f, 0}  // kLeftTop
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
	if (info.move.y <= 0) {
		return;
	}

	std::array<Vector3, kNumCorner> NewPos;

	for (uint32_t i = 0; i < NewPos.size(); ++i) {
		NewPos[i] = CornerPos(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipID mapChipID_;
	bool hit = false;

	MapChip::MapChipIndex indexSet;
	indexSet = mapChipData_->GetMapChipIndexSetByPosition(NewPos[kLeftTop]);
	mapChipID_ = mapChipData_->GetMapChipID(indexSet);
	if (mapChipID_ == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (mapChipID_ == MapChipID::OpenBlock) {
			hit = true;
		}
	}

	indexSet = mapChipData_->GetMapChipIndexSetByPosition(NewPos[kRightTop]);
	mapChipID_ = mapChipData_->GetMapChipID(indexSet);
	if (mapChipID_ == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (mapChipID_ == MapChipID::OpenBlock) {
			hit = true;
		}
	}
	if (hit) {
		indexSet = mapChipData_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, +size_.y / 2.0f, 0));
		MapChip::Rect rect = mapChipData_->GetRectByIndex(indexSet);
		info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (size_.y / 2.0f + kBlank));
		// 天井に当たったことを記録する
		info.ceiling = true;
	}
}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) {
	if (info.move.y >= 0) {
		return;
	}

	std::array<Vector3, kNumCorner> newPos;

	for (uint32_t i = 0; i < newPos.size(); ++i) {
		newPos[i] = CornerPos(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipID MapChipID;
	bool hit = false;
	MapChip::MapChipIndex indexSet;
	indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kLeftBottom]);
	MapChipID = mapChipData_->GetMapChipID(indexSet);
	if (MapChipID == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (MapChipID == MapChipID::OpenBlock) {
			hit = true;
		}
	}
	indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kRightBottom]);
	MapChipID = mapChipData_->GetMapChipID(indexSet);
	if (MapChipID == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (MapChipID == MapChipID::OpenBlock) {
			hit = true;
		}
	}
	if (hit) {
		indexSet = mapChipData_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, +size_.y / 2.0f, 0));
		MapChip::Rect rect = mapChipData_->GetRectByIndex(indexSet);
		info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (size_.y / 2.0f + kBlank));
		info.landing = true;
	}
}

void Player::CheckMapCollisionRight(CollisionMapInfo& info) {
	if (info.move.x <= 0) {
		return;
	}

	std::array<Vector3, kNumCorner> newPos;

	for (uint32_t i = 0; i < newPos.size(); ++i) {
		newPos[i] = CornerPos(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipID mapChipID_;
	bool hit = false;
	MapChip::MapChipIndex indexSet;
	indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kRightTop]);
	mapChipID_ = mapChipData_->GetMapChipID(indexSet);
	if (mapChipID_ == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (mapChipID_ == MapChipID::OpenBlock) {
			hit = true;
		}
	}
	indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kRightBottom]);
	mapChipID_ = mapChipData_->GetMapChipID(indexSet);
	if (mapChipID_ == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (mapChipID_ == MapChipID::OpenBlock) {
			hit = true;
		}
	}

	if (hit) {
		indexSet = mapChipData_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(+size_.x / 2.0f, 0, 0));
		MapChip::Rect rect = mapChipData_->GetRectByIndex(indexSet);
		info.move.x = std::max(0.0f, rect.right - worldTransform_.translation_.x - (size_.x / 2.0f + kBlank));
		info.ceiling = true;
	}
}

void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
	if (info.move.x >= 0) {
		return;
	}

	std::array<Vector3, kNumCorner> newPos;

	for (uint32_t i = 0; i < newPos.size(); ++i) {
		newPos[i] = CornerPos(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipID mapChipID_;
	bool hit = false;
	MapChip::MapChipIndex indexSet;
	indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kLeftTop]);
	mapChipID_ = mapChipData_->GetMapChipID(indexSet);
	if (mapChipID_ == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (mapChipID_ == MapChipID::OpenBlock) {
			hit = true;
		}
	}
	indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kLeftBottom]);
	mapChipID_ = mapChipData_->GetMapChipID(indexSet);
	if (mapChipID_ == MapChipID::kBlock) {
		hit = true;
	}
	if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
		if (mapChipID_ == MapChipID::OpenBlock) {
			hit = true;
		}
	}

	if (hit) {
		indexSet = mapChipData_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(+size_.x / 2.0f, 0, 0));
		MapChip::Rect rect = mapChipData_->GetRectByIndex(indexSet);
		info.move.x = std::max(0.0f, rect.right - worldTransform_.translation_.x - (size_.x / 2.0f + kBlank));
		info.ceiling = true;
	}
}

void Player::CheckMapCollisionHit(CollisionMapInfo& info) { worldTransform_.translation_ += info.move; }

void Player::CellingSwitch(CollisionMapInfo& info) {
	if (onGround_) {
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		} else {
			std::array<Vector3, kNumCorner> newPos;

			for (uint32_t i = 0; i < newPos.size(); ++i) {
				newPos[i] = CornerPos(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
			}

			MapChipID MapChipID;
			bool hit = false;
			MapChip::MapChipIndex indexSet;
			indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kLeftBottom] + Vector3(0, -kAttennuationShift, 0));
			MapChipID = mapChipData_->GetMapChipID(indexSet);
			if (MapChipID == MapChipID::kBlock) {
				hit = true;
			}
			if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
				if (MapChipID == MapChipID::OpenBlock) {
					hit = true;
				}
			}
			indexSet = mapChipData_->GetMapChipIndexSetByPosition(newPos[kRightBottom] + Vector3(0, -kAttennuationShift, 0));
			MapChipID = mapChipData_->GetMapChipID(indexSet);
			if (MapChipID == MapChipID::kBlock) {
				hit = true;
			}
			if (objectManager_->GetIsPushButton() == false && objectManager_->GetIsAllLever() == false) {
				if (MapChipID == MapChipID::OpenBlock) {
					hit = true;
				}
			}

			if (!hit) {
				onGround_ = false;
			}
		}
	} else {
		if (info.landing) {
			onGround_ = true;

			velocity_.x *= (1.0f - kAttennuationLanding);

			velocity_.y = 0.0f;
		}
	}
}

void Player::GoalPlayerMove() {
	//
	if (worldTransform_.rotation_.y <= goalRotationLimit.y) {
		worldTransform_.rotation_.y += kGoalRotatoMove;
		leftVibration = kGoalVibration;
	} else {
		isRotateGoal = true;
		leftVibration = 0;
	}
}
