#pragma once
#include "KamataEngine.h"
#include "ect/AABB.h"

class PlayerManager;

class IGameObject {
public:
	IGameObject() = default;
	virtual ~IGameObject() = default; // 仮想デストラクタ
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos"></param>
	virtual void Initialize(const KamataEngine::Vector3 pos);
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera_">カメラの値</param>
	virtual void Draw(KamataEngine::Camera& camera_);
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	/// <param name="label">クラスごとのラベル</param>
	virtual void DrawImGui(const std::string& label);
	/// <summary>
	/// 当たったかどうか確認する
	/// </summary>
	/// <param name="playerManager">プレイヤーの情報を取得する</param>
	virtual void CheckCollision(PlayerManager* playerManager);
	/// <summary>
	/// ワールド座標を参照する
	/// </summary>
	/// <returns>ワールド座標を返す</returns>
	virtual KamataEngine::Vector3 GetWorldPos();
	/// <summary>
	/// AABBを参照する
	/// </summary>
	/// <returns>AABBを返す</returns>
	virtual AABB GetAABB();

protected:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Vector2 size_{1.0f, 1.0f};
};
