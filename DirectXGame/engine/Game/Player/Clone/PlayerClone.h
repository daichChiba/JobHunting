#pragma once
#include "ect/AABB.h"
#include "engine/Game/LoadJsonFile/FileJson.h"
#include <KamataEngine.h>
class MapChip;
class Goal;
class ObjectManager;

/// <summary>
/// プレイヤーのクローンに関する状態を取り扱うクラス
/// プレイヤーのクローンの情報を単一的に扱う。
/// </summary>
class PlayerClone {
public:
	enum class LRDirection {
		kRight,
		kLeft,
	};

	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};

	enum Corner {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerClone();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerClone();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(MapChip* mapchip);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera_">カメラの情報を入力する</param>
	void Draw(const KamataEngine::Camera& camera_);
	/// <summary>
	/// 情報を削除する
	/// </summary>
	void Delete();
	/// <summary>
	/// ImGuiを描画する
	/// </summary>
	void DrawImGui();

	void SetIsMove(bool isMove_) { isMove = isMove_; }
	bool GetIsMove() { return isMove; }

	const KamataEngine::WorldTransform& worldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	void SetMapChip(MapChip* mapchip_) { mapChipData_ = mapchip_; }

	KamataEngine::Vector3 GetWorldPos();

	AABB GetAABB();

	void OnCollision(const Goal* goal_);

	bool GetIsGoal() { return isGoal_; }
	bool GetIsClear() { return isClear_; }

	bool GetOnGround() { return onGround_; }

	KamataEngine::Vector3 GetPlayerPos() { return worldTransform_.translation_; }

	bool GetIsRotateGoal() { return isRotateGoal; }

	void SetObjectManager(ObjectManager* objectManager) { objectManager_ = objectManager; }

	void SetXinput(XINPUT_STATE xinput) { xinput_ = xinput; }

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void InputMove();

	/// <summary>
	///
	/// </summary>
	/// <param name="center"></param>
	/// <param name="corner"></param>
	/// <returns></returns>
	KamataEngine::Vector3 CornerPos(const KamataEngine::Vector3& center, Corner corner);

	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);

	void CheckMapCollisionHit(CollisionMapInfo& info);
	void CellingSwitch(CollisionMapInfo& info);

	// std::unique_ptr<MapChip> Set(new MapChip());

	void GoalPlayerMove();

private:
	const std::string filePath = "Resources/Json/Player.json";
	std::string fileMain = "Player";

	FileJson::FileAccessor* fileAccessor_ = nullptr;

	KamataEngine::Vector3 pos_;
	KamataEngine::Vector3 size_;
	// 当たり判定の余白
	float kBlank;
	float kAcceleration;
	float kLimitXSpeed;
	float kAttenuation;
	float kJumpAcceleration;
	float kGravityAcceleration;
	float kLimitFallSpeed;
	float kAttennuationShift;
	float kAttennuationLanding;
	float kGoalRotatoMove;

	// 速度
	KamataEngine::Vector3 velocity_;

	KamataEngine::Vector3 goalRotationLimit;

	bool isMove = false;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;

	CollisionMapInfo info_;

	MapChip* mapChipData_;
	ObjectManager* objectManager_;
	LRDirection lrDirection_ = LRDirection::kRight;

	bool onGround_ = true;
	bool isGoal_ = false;
	bool isClear_ = false;
	bool isRotateGoal = false;

	KamataEngine::ObjectColor* objectColor_;

	KamataEngine::Vector4 translucentColor;

	XINPUT_STATE xinput_;
};
