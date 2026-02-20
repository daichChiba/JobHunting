#pragma once
#include "../LoadJsonFile/FileJson.h"
#include "MapChipID.h"
#include <KamataEngine.h>
#include "engine/ect/IntVector2.h"

class PushButton;
class Lever;
class ObjectManager;

/// <summary>
/// マップチップに関する情報を取り扱うクラス
/// csvファイルなどの情報を総合的に扱う
/// </summary>
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

	/// <summary>
	/// 矩形の構造体
	/// </summary>
	struct Rect {
		float left;
		float top;
		float right;
		float bottom;
	};
	/// <summary>
	/// マップ上のチップ位置を表す構造体
	/// </summary>
	struct MapChipIndex {
		int x;
		int y;
	};
	/// <summary>
	/// マップチップのデータを保持する構造体
	/// </summary>
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
	/// 指定した位置にいるマップチップの種類を取得
	/// </summary>
	/// <param name="pos">マップ上の位置を入力。</param>
	/// <returns>指定の位置にいるMapChipの種類を返す</returns>
	MapChipID GetMapChipID(const KamataEngine::Vector3 pos);
	/// <summary>
	/// 指定したMapChipIndexに対してマップチップの種類を取得
	/// </summary>
	/// <param name="index">マップチップの位置を入力</param>
	/// <returns>指定の位置にいるMapChipの種類を返す</returns>
	MapChipID GetMapChipID(const MapChipIndex& index);
	/// <summary>
	/// マップ上の矩形を取得
	/// </summary>
	/// <param name="pos">基準となる位置ベクトル（Vector3）。この位置に対応するマップ矩形が返されます。</param>
	/// <returns>指定位置に対応するマップの矩形（Rect）。</returns>
	Rect GetMapRect(const Vector3 pos);
	/// <summary>
	/// マップチップ上のチップ位置を取得する
	/// </summary>
	/// <param name="pos">基準となる位置ベクトル</param>
	/// <returns>マップチップの位置(1,1)など</returns>
	MapChipIndex GetMapChipIndex(const Vector3& pos);
	/// <summary>
	/// MapChipの最大の大きさ
	/// </summary>
	/// <returns>MapChipの範囲(大きさ)</returns>
	IntVector2 GetMaxMapSize();
	/// <summary>
	/// マップの位置
	/// </summary>
	/// <param name="index_">マップチップの位置を入力</param>
	/// <returns>対応する各点の座標</returns>
	Rect GetRectByIndex(MapChipIndex index_);
	/// <summary>
	/// マップチップのワールド座標の取得
	/// </summary>
	/// <param name="index_">マップチップの位置を入力</param>
	/// <returns>ワールド座標</returns>
	KamataEngine::Vector3 GetMapChipPosByIndex(MapChipIndex index_);

	/// <summary>
	/// マップチップの位置の取得
	/// </summary>
	/// <param name="pos">ワールド座標を入力</param>
	/// <returns>マップチップの位置</returns>
	MapChipIndex GetMapChipIndexSetByPosition(const KamataEngine::Vector3 pos);

	/// <summary>
	/// Jsonファイルを操作するためのアクセッサの取得
	/// </summary>
	/// <returns>FileAccessorのポインタ</returns>
	FileJson::FileAccessor* GetFileAccessor() { return fileAccessor_; }

	///// <summary>
	///// プッシュボタンオブジェクトを登録
	///// </summary>
	///// <param name="pushButton">プッシュボタンオブジェクト</param>
	//void SetPushButton(PushButton* pushButton) { pushButton_ = pushButton; } 
	///// <summary>
	///// レバーオブジェクトを登録
	///// </summary>
	///// <param name="lever">レバーオブジェクト</param>
	//void SetLever(Lever* lever) { lever_ = lever; }

	/// <summary>
	/// オブジェクトマネージャーを設定します。
	/// </summary>
	/// <param name="objectManager">設定するオブジェクトマネージャー</param>
	void SetObjectManager(ObjectManager* objectManager) { objectManager_ = objectManager; }

	/// <summary>
	/// ブロックのリアクションが終わったかどうかを設定する
	/// </summary>
	/// <param name="isBlockReactionEnd_">リアクションが終わっていたらtrue,終わっていなかったらfalse</param>
	void SetIsBlockReaction(bool isBlockReactionEnd_) { isBlockReactionEnd = isBlockReactionEnd_; }

	/// <summary>
	/// 指定したMapChipIDに該当するオブジェクトのワールド座標を取得
	/// </summary>
	/// <param name="id">検索対象のMapChipID</param>
	/// <returns>座標のリスト</returns>
	std::vector<KamataEngine::Vector3> GetAllObjectPositions(MapChipID id);

private:
	/// <summary>
	/// マップを生成する
	/// </summary>
	void MapCreate();
	/// <summary>
	/// モデルを生成する
	/// </summary>
	void SetModel();

private:
private:
	FileJson::FileAccessor* fileAccessor_;
	std::vector<std::vector<int>> csvData_;
	std::string directory = "";
	MapChipData mapChipData_;

	std::string erea_ = "";

	std::string common = "Common";

	KamataEngine::Vector3 BlockSize;

	// ワールドトランスフォーム
	std::vector<std::vector<WorldTransform*>> worldTransform_;

	//PushButton* pushButton_;
	//Lever* lever_;

	ObjectManager* objectManager_;

	bool isBlockReactionEnd;
};