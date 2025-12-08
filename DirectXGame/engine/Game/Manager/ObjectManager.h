#pragma once
#include "KamataEngine.h"
#include "Game/Object/Goal/Goal.h"
#include "Game/Object/PushButton/PushButton.h"


class MapChip;
class Player;
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

	void CheckAllCollisions(Player* player);

	PushButton& GetPushButton() { return pushButton_; }

private:
	MapChip* mapChipData_;
	Goal goal_;
	PushButton pushButton_;
	Player* player_;
};
