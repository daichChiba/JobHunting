#pragma once
#include "../LoadJsonFile/FileJson.h"
#include <KamataEngine.h>
class Player;
class MapChip;
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

	/// <summary>
	/// ゲームシーンのカメラのゲッター
	/// </summary>
	/// <returns>カメラの情報を取得します。カメラの情報がない場合はnullを返す場合もあります。</returns>
	KamataEngine::Camera* GetCamera() { return camera_; }
	/// <summary>
	/// カメラの動きを管理するisMove_のsetter
	/// </summary>
	/// <param name="動くかどうか"></param>
	void SetIsMove(bool isMove_) { isMove = isMove_; }
	/// <summary>
	/// カメラの設置位置の種類を設定
	/// </summary>
	/// <param name="num">カメラ設置位置の種類</param>
	void SetCamera_PosType(int num) { camera_posType = num; }
	/// <summary>
	/// カメラの設置位置の最大数の取得
	/// </summary>
	/// <returns>カメラの設置位置の最大数を返します。</returns>
	int GetcameraTypeMax() { return cameraTypeMax; }
	/// <summary>
	/// カメラの位置タイプを取得
	/// </summary>
	/// <returns>現在のカメラの位置タイプを返します。</returns>
	int GetCamera_PosType() { return camera_posType; }
	/// <summary>
	/// カメラの次の移動位置
	/// </summary>
	void CameraNextPos();
	/// <summary>
	/// カメラの位置を設定
	/// </summary>
	void SetCameraPos();
	/// <summary>
	/// Playerの情報を取得する
	/// </summary>
	/// <param name="player">プレイヤーの情報</param>
	void SetPlayer(Player* player) { player_ = player; }
	/// <summary>
	/// mapChipの情報を取得する
	/// </summary>
	/// <param name="mapChip">mapChipの情報</param>
	void SetMapChip(MapChip* mapchip) { mapChip_ = mapchip; }

	/// <summary>
	/// リアクションの動作がすべて終わっているかどうかの情報を取得する
	/// </summary>
	/// <returns>リアクションの動作がすべて終わっていたらtrueを返し、終わっていなかったらfalseを返す</returns>
	bool GetIsReactionEnd() { return isReactionEnd; }

private:
	/// <summary>
	/// ゲームクリアしたときのカメラの動き
	/// </summary>
	void SetClearCamera();

	/// <summary>
	/// リアクションする際のカメラの動き
	/// </summary>
	void SetReactionCamera();

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

	int ReactionTimer;
	static inline const int kReactionTimer = 60;

	bool isReactionEnd = false;

	int endReaction;
	static inline const int kEndReaction = 60;

	// KamataEngine::Vector3

	Player* player_;

	//bool isAllReaction = false;


	bool isReactionStart = false;

	bool isReaction = false;

	MapChip* mapChip_;
};
