#pragma once
#include "KamataEngine.h"

class MapChip;
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
	void Draw(KamataEngine::Camera* camera);
	void DrawImGui();
	void Delete();

private:
	MapChip* mapChipData_;
};
