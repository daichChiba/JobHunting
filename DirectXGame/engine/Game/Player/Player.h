#pragma once
#include "KamataEngine.h"
class MapChip;
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
	void Draw(KamataEngine::Camera& camera);
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui();

	void SetIsMove(bool isMove_) { isMove = isMove_; }

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	void SetUpPos(MapChip mapChip);

	KamataEngine::Vector3 pos_;
	const float playerSpeed = 0.1f;

	bool isMove = true;

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
};
