#pragma once
#include "KamataEngine.h"
class Lever {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	Lever();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Lever();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initilize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera_">カメラ情報を入力</param>
	//void Draw(KamataEngine::Camera& camera_);
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();
	/// <summary>
	/// リソースの削除
	/// </summary>
	void Delete();

private:
	KamataEngine::Model* model_ = nullptr;

};
