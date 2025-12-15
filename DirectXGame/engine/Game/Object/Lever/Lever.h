#pragma once
#include "KamataEngine.h"
#include "ect/AABB.h"

class MapChip;
class Player;

class Lever {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	Lever();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Lever();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initilize(MapChip* mapChip_);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera_">カメラ情報を入力</param>
	void Draw(KamataEngine::Camera& camera_);
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();
	/// <summary>
	/// リソースの削除
	/// </summary>
	void Delete();

	bool GetIsLever() const { return isLever; }

	bool GetIsColision() const { return isColision; }

	void SetIsColision(bool isColision_) { isColision = isColision_; }

	KamataEngine::Vector3 GetWorldPos();

	AABB GetAABB();

	void OnCollision(const Player* player);

private:
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_[2] = {nullptr};

	bool isLever = false;
	bool isColision = false;

	KamataEngine::Vector2 size_{1.0f, 1.0f};
};
