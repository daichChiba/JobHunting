#pragma once
#include "Game/Object/IGameObject.h"

class MapChip;
class Player;
class PlayerClone;
/// <summary>
/// Leverの状況を取得して、ゲーム内に反映させるクラス
/// プレイヤーや分身がゴールしたかなど総合的に扱う
/// </summary>
class Lever :public IGameObject {
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
	void Initialize(const KamataEngine::Vector3& pos) override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera_">カメラ情報を入力</param>
	void Draw(KamataEngine::Camera& camera_) override;
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	/// <param name="label">ボタンごとのラベルを記入する</param>
	void DrawImGui(const std::string& label) override;
	/// <summary>
	/// リソースの削除
	/// </summary>
	void Delete();

	/// <summary>
	/// レバーがオンになったかどうかの情報を取得する
	/// </summary>
	/// <returns>レバーがオンになっているときはtrue,なっていない時はfalse</returns>
	bool GetIsLever() const { return isLever; }

	/// <summary>
	/// レバーがオンになったかセットする
	/// </summary>
	/// <param name="isLever_">レバーのフラグを取得する</param>
	void SetIsLever(bool isLever_) { isLever = isLever_; }

	/// <summary>
	/// ワールド座標の位置を取得
	/// </summary>
	/// <returns>ワールド座標を取得しVector3型で値を返します</returns>
	KamataEngine::Vector3 GetWorldPos() override;

	/// <summary>
	/// AABBを取得
	/// </summary>
	/// <returns>レバーのAABBを返します。</returns>
	AABB GetAABB() override;

	///// <summary>
	///// 衝突判定
	///// </summary>
	///// <param name="player">Playerの情報を入力</param>
	///// <param name="clone">PlayerCloneの情報を入力</param>
	//void OnCollision(const Player* player, const PlayerClone* clone);

	void CheckCollision(PlayerManager* playerManager)override;

private:
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_[2] = {nullptr};

	bool isLever = false;

	KamataEngine::Vector2 size_{1.0f, 1.0f};
};
