#pragma once
#include "KamataEngine.h"
#include "ect/AABB.h"

class MapChip;
class Player;
class PlayerClone;

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
	void Initilize(const KamataEngine::Vector3 pos);
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
	bool GetIsPushButton() { return isPushButton; }
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
	/// <summary>
	/// プレイヤーに当たった時の処理
	/// </summary>
	/// <param name="player">playerを入力しする</param>
	void OnCollision(const Player* player,const PlayerClone* clone);
	/// <summary>
	/// ボタンを切り替える
	/// </summary>
	/// <param name="pushButton_">ボタンを押したならtrue、押していないのであればfalseに設定する</param>
	void SetInPushButton(bool pushButton_) { isPushButton = pushButton_; }

private:
	KamataEngine::Model* model_[2] = {nullptr};
	const std::string filePath = "Resources/Json/Stage.json";

	KamataEngine::WorldTransform worldTransform_;

	bool isPushButton=false;

	KamataEngine::Vector2 size_{1.0f, 1.0f};
};
