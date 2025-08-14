#pragma once
#include "KamataEngine.h"

class Player;
class GameSceneManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();

private:
	Player* player_;

private:
	KamataEngine::Camera* camera_;


};
