#pragma once
#include "KamataEngine.h"
#include "ect/AABB.h"

class MapChip;
class Player;

/// <summary>
/// ステージ内のギミックの開閉を管理するクラス
/// </summary>
class PushButton {
public:
	/// <summary>
	/// インスタンス
	/// </summary>
	PushButton();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PushButton();
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
	/// <param name="camera_">GameCameraの情報を記入</param>
	void Draw(KamataEngine::Camera& camera_);
	/// <summary>
	/// ImGuiの表示
	/// </summary>
	void DrawImGui();
	/// <summary>
	/// リソースの削除
	/// </summary>
	void Delete();
	/// <summary>
	/// ボタンが押されたかどうか
	/// </summary>
	/// <returns>ボタンが押されたときはtrue、押されていない時はfalseを返します。</returns>
	bool IsPushButton() { return isPushButton; }
	/// <summary>
	/// ワールド座標の位置を取得
	/// </summary>
	/// <returns>ワールド座標を取得しVector3型で値を返します</returns>
	KamataEngine::Vector3 GetWorldPos();
	/// <summary>
	/// AABBの取得
	/// </summary>
	/// <returns>PushButtonのAABBを返します。</returns>
	AABB GetAABB();

	void OnCollision(const Player* player);

private:
	KamataEngine::Model* model_[2] = {nullptr};
	const std::string filePath = "Resources/Json/Stage.json";

	KamataEngine::WorldTransform worldTransform_;

	bool isPushButton;

	KamataEngine::Vector2 size_{1.0f, 1.0f};
};
