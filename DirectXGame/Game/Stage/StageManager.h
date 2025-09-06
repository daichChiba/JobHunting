#pragma once
#include "KamataEngine.h"
#include "stages/Stage.h"
#include "StageID.h"
class StageManager {
public:
	StageManager() = default;
	~StageManager() = default;

	void Initialize(int ereaNum_, int stageNum_, std::string stage_);

	void Update();

	void Draw(KamataEngine::Camera* camera_);


private:
	Stage* stages_;
};
