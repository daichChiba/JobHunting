#include "Stage.h"

using namespace KamataEngine;
void Stage::Initialize(int ereaNum_, int stageNum_, std::string stage_) {
	BlockModel_ = Model::CreateFromOBJ("block");

	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Json/Stage.json");

	csvData_ = fileAccessor_->ReadCsvData(stage_, std::to_string(ereaNum_) + "_" + std::to_string(stageNum_));

	// worldTransform をステージサイズにリサイズ
	worldTransform_.resize(csvData_.size());
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		worldTransform_[y].resize(csvData_[y].size());
	}
	stageData_.data.resize(csvData_.size());

	// CSVからマップチップデータを読み込む
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		stageData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (csvData_[y][x] == 0) {
				stageData_.data[y][x] = StageID::kBlank;
			} else {
				stageData_.data[y][x] = static_cast<StageID>(csvData_[y][x]);
			}
			Vector3 BlockPos = {1.0f * x, 1.0f * y, 0};

			worldTransform_[y][x].translation_ = BlockPos;
			worldTransform_[y][x].Initialize();
		}
	}
}

void Stage::Update() {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			worldTransform_[y][x].UpdateMatrix();
		}
	}
}

void Stage::Draw(Camera* camera_) {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (stageData_.data[y][x] == StageID::kBlock) {
				BlockModel_->Draw(worldTransform_[y][x], *camera_);
			}
		}
	}
}