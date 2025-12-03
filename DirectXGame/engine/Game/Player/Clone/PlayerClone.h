#pragma once
#include <KamataEngine.h>


class PlayerClone {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerClone();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerClone();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	///// <summary>
	/////	描画
	///// </summary>
	///// <param name="camera_">カメラの情報を入力する</param>
	//void Draw(KamataEngine::Camera& camera_);
	/// <summary>
	/// 情報を削除する
	/// </summary>
	void Delete();
	/// <summary>
	/// ImGuiを描画する
	/// </summary>
	void DrawImGui();

private:
	

};
