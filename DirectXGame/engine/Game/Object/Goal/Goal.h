#pragma once
#include "ect/AABB.h"
#include <KamataEngine.h>
class MapChip;
class Player;

class Goal {
public:
	Goal();
	~Goal();
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
	void Draw(const KamataEngine::Camera& camera);
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui();

	KamataEngine::Vector3 GetWorldPos();

	AABB GetAABB();


private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	MapChip* mapChipData_;

	KamataEngine::Vector2 size_{1.0f, 1.0f};
};
