#pragma once
#include "../LoadJsonFile/FileJson.h"
#include <KamataEngine.h>
class Player;
/// <summary>
/// GameScene時のカメラの情報(カメラの位置など)を取り扱うクラス
/// カメラに関する入出力を単一的に扱う
/// </summary>
class GameCamera {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCamera();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCamera();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void ImGuiDraw();

	KamataEngine::Camera* GetCamera() { return camera_; }

	void SetIsMove(bool isMove_) { isMove = isMove_; }

	void SetCamera_PosType(int num) { camera_posType = num; }

	int GetcameraTypeMax() { return cameraTypeMax; }
	int GetCamera_PosType() { return camera_posType; }

	void CameraNextPos();
	void SetCameraPos();

	void SetPlayer(Player* player) { player_ = player; }

private:
	void SetClearCamera();

private:
	KamataEngine::Camera* camera_;

	KamataEngine::Vector3 startCameraPos_;

	const std::string filePath = "Resources/Json/GameCamera.json";
	std::string fileMain = "GameCamera";

	FileJson::FileAccessor* fileAccessor_ = nullptr;

	// float count = 0.0f;
	// const float kCount = 60.0f;

	KamataEngine::Vector3 startPos_;
	KamataEngine::Vector3 targetPos_;
	//
	int camera_posType;

	// float target2camera;
	static inline const int kMoveTimer = 15;
	float currentTime; // 現在の経過時間
	const int cameraTypeMax = 3;
	bool isMove;

	// KamataEngine::Vector3

	Player* player_;
};
