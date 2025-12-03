#pragma once
#include "ect/AABB.h"
#include <KamataEngine.h>
class MapChip;
class Player;
/// <summary>
/// Goalの状況を取得し、ゲーム内に反映させるクラス
/// プレイヤーや分身がゴールしたかなど総合的に扱う
/// </summary>
class Goal {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	Goal();
	/// <summary>
	/// 
	/// </summary>
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
	/// <summary>
	/// ワールド座標の位置を取得
	/// </summary>
	/// <returns>ワールド座標を取得しVector3型で値を返します</returns>
	KamataEngine::Vector3 GetWorldPos();
	/// <summary>
	/// AABBを取得
	/// </summary>
	/// <returns>ゴールのAABBを返します。</returns>
	AABB GetAABB();


private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	MapChip* mapChipData_;

	KamataEngine::Vector2 size_{0.5f, 1.0f};
};
