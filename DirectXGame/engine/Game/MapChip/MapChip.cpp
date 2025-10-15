#include "MapChip.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <xmemory>

using namespace KamataEngine;
using namespace FileJson;
MapChip::MapChip() {}
MapChip::~MapChip() {}
void MapChip::Initialize(std::string file, std::string erea, std::string stage) {
	directory = file;
	fileAccessor_ = new FileAccessor(file);
	erea_ = erea;
	csvData_ = fileAccessor_->ReadCsvData(erea, stage);
	BlockSize = fileAccessor_->ReadVector3(erea, "BlockSize", Vector3());
	MapCreate();
	SetModel();
}
void MapChip::Update() {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		mapChipData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			worldTransform_[y][x]->UpdateMatrix();
		}
	}
}

void MapChip::Draw() {}

void MapChip::MapDraw(Camera& camera) {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		mapChipData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (mapChipData_.data[y][x] == MapChipID::kBlock) {
				mapChipData_.model->Draw(*worldTransform_[y][x], camera);
			}
		}
	}
}

void MapChip::DrawImGui() {
#ifdef _DEBUG

	ImGui::DragFloat3("BlockSize", &BlockSize.x);
	fileAccessor_->WriteVector3(erea_, "BlockSize", BlockSize);
	fileAccessor_->Save();
#endif // _DEBUG

}

KamataEngine::Vector3 MapChip::GetPlayerPos() {
	Vector3 playerPos;
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		mapChipData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (mapChipData_.data[y][x] == MapChipID::PlayerStart) {

				playerPos = {1.0f * x, 1.0f * (csvData_.size() - 1 - y), 0};
			}
		}
	}
	return playerPos;
}

void MapChip::MapCreate() {
	// worldTransform をステージサイズにリサイズ
	worldTransform_.resize(csvData_.size());
	mapChipData_.data.resize(csvData_.size());
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		worldTransform_[y].resize(csvData_[y].size());
		mapChipData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (!worldTransform_[y][x]) {
				worldTransform_[y][x] = new WorldTransform();
			}
			if (csvData_[y][x] == 0) {
				mapChipData_.data[y][x] = MapChipID::kBlank;
			} else {
				mapChipData_.data[y][x] = static_cast<MapChipID>(csvData_[y][x]);
			}
			Vector3 BlockPos = {1.0f * x, 1.0f * (csvData_.size() - 1 - y), 0};

			worldTransform_[y][x]->translation_ = BlockPos;
			worldTransform_[y][x]->Initialize();
		}
	}
}

void MapChip::SetModel() {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		mapChipData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (mapChipData_.data[y][x] == MapChipID::kBlock) {
				mapChipData_.model = Model::CreateFromOBJ("block");
			}
		}
	}
}
