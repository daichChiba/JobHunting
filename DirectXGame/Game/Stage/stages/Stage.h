#pragma once
#include "../StageID.h"
#include "Game/LoadJsonFile/FileJson.h"

struct StageData {
	std::vector<std::vector<StageID>> data;
};

class Stage {
public:
	void Initialize(int ereaNum_, int stageNum_, std::string stage_);

	void Update();

	void Draw(KamataEngine::Camera* camera_);

private:
	StageData stageData_;

	// csvデータ
	std::vector<std::vector<int>> csvData_;

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;

	// モデル
	KamataEngine::Model* BlockModel_;

	// ワールドトランスフォーム
	std::vector<std::vector<WorldTransform>> worldTransform_;
};
