#pragma once
#include "Game/Object/IGameObject.h"

/// <summary>
/// Goalの状況を取得し、ゲーム内に反映させるクラス
/// プレイヤーや分身がゴールしたかなど総合的に扱う
/// </summary>
class Goal : public IGameObject {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	Goal();
	/// <summary>
	///
	/// </summary>
	~Goal() override = default;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const KamataEngine::Vector3 pos) override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(KamataEngine::Camera& camera_) override;
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui(const std::string& label) override;
	/// <summary>
	/// ワールド座標の位置を取得
	/// </summary>
	/// <returns>ワールド座標を取得しVector3型で値を返します</returns>
	KamataEngine::Vector3 GetWorldPos() override;
	/// <summary>
	/// AABBを取得
	/// </summary>
	/// <returns>ゴールのAABBを返します。</returns>
	AABB GetAABB() override;

	void CheckCollision(PlayerManager* playerManager) override;

private:
	// KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	// MapChip* mapChipData_;

	// KamataEngine::Vector2 size_{0.5f, 1.0f};
};
