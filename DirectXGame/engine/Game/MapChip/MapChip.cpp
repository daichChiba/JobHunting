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

KamataEngine::Vector3 MapChip::GetObjectPos(const MapChipID id_) {
	Vector3 playerPos = {};
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		mapChipData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (mapChipData_.data[y][x] == id_) {

				playerPos = {BlockSize.x * 1.0f * x, BlockSize.y * 1.0f * (csvData_.size() - 1 - y), 0};
			}
		}
	}
	return playerPos;
}

MapChipID MapChip::GetMapChipID(const KamataEngine::Vector3 pos) {
	//
	MapChipIndex index = GetMapChipIndex(pos);
	if (index.y < 0 || index.y >= static_cast<int>(mapChipData_.data.size()) || index.x < 0 || index.x >= static_cast<int>(mapChipData_.data[0].size())) {
		return MapChipID::kBlank;
	}
	return mapChipData_.data[index.y][index.x];
}

MapChipID MapChip::GetMapChipID(const MapChipIndex& index) {
	//
	return mapChipData_.data[index.y][index.x];
}

MapChip::Rect MapChip::GetMapRect(const Vector3 pos) {
	//
	MapChipIndex index = GetMapChipIndex(pos);
	Rect rect;
	rect.top = index.y * BlockSize.y;
	rect.bottom = rect.top + BlockSize.y;
	rect.left = index.x * BlockSize.x;
	rect.right = rect.left + BlockSize.x;
	return rect;
}

MapChip::MapChipIndex MapChip::GetMapChipIndex(const Vector3& pos) {
	MapChipIndex index;
	index.x = static_cast<int>(pos.x / BlockSize.x);
	index.y = GetMaxMapSize().y - 1 - static_cast<int>(pos.y / BlockSize.y);
	index.x = std::clamp<int>(index.x, 0, static_cast<int>(mapChipData_.data[0].size()) - 1);
	index.y = std::clamp<int>(index.y, 0, static_cast<int>(mapChipData_.data.size()) - 1);
	return index;
}

IntVector2 MapChip::GetMaxMapSize() {
	return IntVector2(
		static_cast<int>(mapChipData_.data[0].size()),
		static_cast<int>(mapChipData_.data.size())
	);
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