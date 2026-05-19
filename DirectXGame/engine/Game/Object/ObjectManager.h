#pragma once
#include "Game/Object/Goal/Goal.h"
#include "Game/Object/Lever/Lever.h"
#include "Game/Object/PushButton/PushButton.h"
#include "KamataEngine.h"

class MapChip;
class Player;
class PlayerClone;
class PlayerManager;

/// <summary>
/// オブジェクトに関する情報を管理するクラス
/// オブジェクトに関する描画や出力を総合的に扱う
/// </summary>
class ObjectManager {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	ObjectManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectManager();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="mapchip">MapChipの情報を入力</param>
	void Initilize(MapChip* mapchip);
	/// <summary>
	/// 更新
	/// </summary>
	void UpDate();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">Cameraの情報を入力</param>
	void Draw(KamataEngine::Camera& camera);
	/// <summary>
	/// ImGuiを描画する
	/// </summary>
	void DrawImGui();
	/// <summary>
	/// リソースの削除
	/// </summary>
	void Delete();
	/// <summary>
	/// 全てのオブジェクトの当たり判定を取得する
	/// </summary>
	/// <param name="player">プレイヤーの情報を入力</param>
	/// <param name="playerClone">プレイヤークローンの情報を入力</param>
	void CheckAllCollisions(PlayerManager* playerManager);
	/// <summary>
	/// 全てのレバーの衝突が完了したかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsAllLever() { return isAllLeverCollision; }
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool GetIsPushButton() { return isPushButton; }

private:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="player"></param>
	/// <param name="playerClone"></param>
	void CheckLeverCollision(PlayerManager* playerManager);
	/// <summary>
	///
	/// </summary>
	/// <param name="player"></param>
	/// <param name="playerClone"></param>
	void CheckButtonCollision(PlayerManager* playerManager);
	/// <summary>
	///
	/// </summary>
	/// <param name="player"></param>
	/// <param name="playerClone"></param>
	void CheckGoalCollision(PlayerManager* playerManager);

private:
	MapChip* mapChipData_;
	std::vector<std::unique_ptr<Goal>> goals_;
	std::vector<std::unique_ptr<PushButton>> pushButtons_;
	std::vector<std::unique_ptr<Lever>> levers_;
	//Player* player_;
	//PlayerClone* playerClone_;

	PlayerManager* playerManager_;

	bool isAllLeverCollision = false;
	bool isPushButton;
};
