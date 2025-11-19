#pragma once
#include "KamataEngine.h"

class MapChip;

class ObjectManager {
public:
	ObjectManager();
	~ObjectManager();

	void Initilize(MapChip* mapchip);
	void UpDate();
	//void Draw(KamataEngine::Camera* camera);
	void DrawImGui();
	void Delete();

private:
	MapChip* mapChipData_;
};
