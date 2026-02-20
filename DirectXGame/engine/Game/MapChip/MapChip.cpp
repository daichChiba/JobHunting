#include "MapChip.h"
#include "Game/Object/ObjectManager.h"
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
	BlockSize = fileAccessor_->Read(common, "BlockSize", Vector3());
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

			if (isBlockReactionEnd == false) {
				if (objectManager_->GetIsPushButton() == false) {
					if (mapChipData_.data[y][x] == MapChipID ::OpenBlock) {
						mapChipData_.model->Draw(*worldTransform_[y][x], camera);
					}
				}
			}
		}
	}
}

void MapChip::DrawImGui() {
#ifdef _DEBUG

	ImGui::DragFloat3("BlockSize", &BlockSize.x);
	fileAccessor_->Write(erea_, "BlockSize", BlockSize);
	fileAccessor_->Save();
#endif // _DEBUG
}

KamataEngine::Vector3 MapChip::GetObjectPos(const MapChipID id_) {
	Vector3 Pos = {};
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		mapChipData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (mapChipData_.data[y][x] == id_) {

				Pos = {BlockSize.x * 1.0f * x, BlockSize.y * 1.0f * (csvData_.size() - 1 - y), 0};
			}
		}
	}
	return Pos;
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
	// 境界チェックを追加して範囲外なら kBlank を返す
	if (index.y < 0 || index.y >= static_cast<int>(mapChipData_.data.size()) || index.x < 0 || index.x >= static_cast<int>(mapChipData_.data[0].size())) {
		return MapChipID::kBlank;
	}
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
	return index;
}

IntVector2 MapChip::GetMaxMapSize() { return IntVector2(static_cast<int>(mapChipData_.data[0].size()), static_cast<int>(mapChipData_.data.size())); }

MapChip::Rect MapChip::GetRectByIndex(MapChipIndex index_) {
	Vector3 center = GetMapChipPosByIndex(index_);
	Rect rect;
	rect.left = center.x - BlockSize.x / 2.0f;
	rect.right = center.x + BlockSize.x / 2.0f;
	rect.bottom = center.y - BlockSize.y / 2.0f;
	rect.top = center.y + BlockSize.y / 2.0f;

	return rect;
}

KamataEngine::Vector3 MapChip::GetMapChipPosByIndex(MapChipIndex index_) { return Vector3(BlockSize.x * index_.x, BlockSize.y * (mapChipData_.data.size() - 1 - index_.y), 0); }

MapChip::MapChipIndex MapChip::GetMapChipIndexSetByPosition(const KamataEngine::Vector3 pos) {
	MapChipIndex indexSet = {};

	indexSet.x = static_cast<uint32_t>((pos.x + BlockSize.x / 2) / BlockSize.x);

	indexSet.y = GetMaxMapSize().y - 1 - static_cast<uint32_t>((pos.y + BlockSize.y / 2) / BlockSize.y);

	return indexSet;
}

std::vector<KamataEngine::Vector3> MapChip::GetAllObjectPositions(MapChipID id) {
	std::vector<KamataEngine::Vector3> positions;

	// マップの縦横サイズ分ループ
	for (int y = 0; y < GetMaxMapSize().y; y++) {
		for (int x = 0; x < GetMaxMapSize().x; x++) {
			// その場所のチップIDが一致したら
			if (GetMapChipID(MapChipIndex{x, y}) == id) {
				// そのブロックのワールド座標を計算してリストに追加
				// (GetMapChipPosByIndexなどが既に計算式を持っているはず)
				positions.push_back(GetMapChipPosByIndex({x, y}));
			}
		}
	}
	return positions;
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
			// BlockSize を使ってワールド座標を決定（以前は 1.0f 固定だった）
			Vector3 BlockPos = {BlockSize.x * static_cast<float>(x), BlockSize.y * static_cast<float>(csvData_.size() - 1 - y), 0.0f};

			worldTransform_[y][x]->Initialize();
			worldTransform_[y][x]->translation_ = BlockPos;
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