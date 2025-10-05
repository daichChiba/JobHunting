#pragma once
#include "../LoadJsonFile/FileJson.h"
#include "MapChipID.h"
#include <KamataEngine.h>

class MapChip {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="file"></param>
	void Initialize(std::string file, std::string erea, std::string stage);

	void Update();

	void Draw();

	void MapDraw(KamataEngine::Camera& camera);

	void DrawImGui();

	struct Rect {
		float left;
		float top;
		float right;
		float bottom;
	};
	struct MapChipIndex {
		int x;
		int y;
	};
	struct MapChipData {
		std::vector<std::vector<MapChipID>> data;
		KamataEngine::Model* model;
	};

	KamataEngine::Vector3 GetBlockSize() { return BlockSize; }
	KamataEngine::Vector3 GetPlayerPos();

private:
	void MapCreate();
	void SetModel();

private:
private:
	FileJson::FileAccessor* fileAccessor_;
	std::vector<std::vector<int>> csvData_;
	std::string directory = "";
	MapChipData mapChipData_;
	// std::unique_ptr<FileJson::FileAccessor> fileAccessor_;

	std::string erea_ = "";

	KamataEngine::Vector3 BlockSize;

	// ワールドトランスフォーム
	std::vector<std::vector<WorldTransform*>> worldTransform_;
};
