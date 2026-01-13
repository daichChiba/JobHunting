#pragma once
#include "Game/Object/Goal/Goal.h"
#include "Game/Object/Lever/Lever.h"
#include "Game/Object/PushButton/PushButton.h"
#include "KamataEngine.h"

class MapChip;
class Player;
class PlayerClone;
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
	~ObjectManager();

	void Initilize(MapChip* mapchip);
	void UpDate();
	void Draw(KamataEngine::Camera& camera);
	void DrawImGui();
	void Delete();

	void CheckAllCollisions(Player* player, PlayerClone* playerClone);

	std::vector<std::unique_ptr<PushButton>>& GetPushButtons() { return pushButtons_; }
	const std::vector<std::unique_ptr<PushButton>>& GetPushButtons() const { return pushButtons_; }
	std::vector<std::unique_ptr<Lever>>& GetLevers() { return levers_; }
	const std::vector<std::unique_ptr<Lever>>& GetLevers() const { return levers_; }

	bool GetIsAllLever() { return isAllLeverCollision; }

	bool GetIsPushButton() { return isPushButton; }

private:
	void CheckLeverCollision(Player* player, PlayerClone* playerClone);
	void CheckButtonCollision(Player* player, PlayerClone* playerClone);
	void CheckGoalCollision(Player* player, PlayerClone* playerClone);

private:
	MapChip* mapChipData_;
	std::vector<std::unique_ptr<Goal>> goals_;
	std::vector<std::unique_ptr<PushButton>> pushButtons_;
	std::vector<std::unique_ptr<Lever>> levers_;
	Player* player_;
	PlayerClone* playerClone_;

	bool isAllLeverCollision = false;
	bool isPushButton;
};
