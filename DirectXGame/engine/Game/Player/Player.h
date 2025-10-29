#pragma once
#include "KamataEngine.h"
#include "engine/Game/LoadJsonFile/FileJson.h"
class MapChip;

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
enum class MoveKeys { Up, Down, Left, Right, Num };

struct Moves {
	MoveKeys moveKey_;
	bool isMove = false;
};

enum class Corner {
	kRightBottom,
	kLeftBottom,
	kRightTop,
	kLeftTop,

	kNumCorner
};

class Player {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(MapChip mapchip);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const KamataEngine::Camera& camera);
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui();

	void SetIsMove(bool isMove_) { isMove = isMove_; }

	const KamataEngine::WorldTransform& worldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }
	const KamataEngine::Vector3& GetPos() const { return worldTransform_.translation_; }


	bool GetIsAlive() { return isAlive_; }

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void InputMove();
	/// <summary>
	///
	/// </summary>
	void UpdateVelocity();
	/// <summary>
	///
	/// </summary>
	/// <param name="mapChip">mapChip</param>
	void SetUpPos();
	/// <summary>
	///
	/// </summary>
	/// <param name="info"></param>
	void UpdateOnGround(const CollisionMapInfo& info);
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

private:
	const std::string filePath = "Resources/Json/Player.json";
	std::string fileMain = "Player";

	FileJson::FileAccessor* fileAccessor_ = nullptr;

	KamataEngine::Vector3 pos_;
	KamataEngine::Vector3 size_;
	// 当たり判定の余白
	float kBlank;
	float speedX;

	float kDeceleration; // 横移動の減速速度
	float kLimitXSpeed; // 横移動の最大速度
	float kJumpAcceleration;//ジャンプ力

	float kGroundSearchHeight;
	float kAttenuationLanding;

	KamataEngine::Vector3 velocity_;

	bool isMove = true;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;

	CollisionMapInfo info_;

	std::unique_ptr<MapChip> mapChipData_;
	LRDirection lrDirection_ = LRDirection::kRight;

	bool onGround_;
	Moves moveKey;
	bool isAlive_ = true;
};
