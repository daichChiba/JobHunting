#pragma once
#include "../LoadJsonFile/FileJson.h"
#include "MapChipID.h"
#include <KamataEngine.h>
#include "engine/ect/IntVector2.h"

class MapChip {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MapChip();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~MapChip();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="file"></param>
	void Initialize(std::string file, std::string erea, std::string stage);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// マップ描画
	/// </summary>
	/// <param name="camera"></param>
	void MapDraw(KamataEngine::Camera& camera);
	/// <summary>
	/// ImGui描画
	/// </summary>
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

	/// <summary>
	/// ブロックのサイズを取得します。
	/// </summary>
	/// <returns></returns>
	KamataEngine::Vector3 GetBlockSize() { return BlockSize; }
	/// <summary>
	/// オブジェクトのの現在位置を取得します。
	/// </summary>
	/// <returns></returns>
	KamataEngine::Vector3 GetObjectPos(const MapChipID id_);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	MapChipID GetMapChipID(const KamataEngine::Vector3 pos);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	MapChipID GetMapChipID(const MapChipIndex& index);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	Rect GetMapRect(const Vector3 pos);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	MapChipIndex GetMapChipIndex(const Vector3& pos);
	/// <summary>
	/// 
	/// </summary>
	/// <returns>MapChipの範囲(大きさ)</returns>
	IntVector2 GetMaxMapSize();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="index_"></param>
	/// <returns></returns>
	Rect GetRectByIndex(MapChipIndex index_);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="index_"></param>
	/// <returns></returns>
	KamataEngine::Vector3 GetMapChipPosByIndex(MapChipIndex index_);

	MapChipIndex GetMapChipIndexSetByPosition(const KamataEngine::Vector3 pos);

	FileJson::FileAccessor* GetFileAccessor() { return fileAccessor_; }

private:
	void MapCreate();
	void SetModel();

private:
private:
	FileJson::FileAccessor* fileAccessor_;
	std::vector<std::vector<int>> csvData_;
	std::string directory = "";
	MapChipData mapChipData_;

	std::string erea_ = "";

	KamataEngine::Vector3 BlockSize;

	// ワールドトランスフォーム
	std::vector<std::vector<WorldTransform*>> worldTransform_;
};