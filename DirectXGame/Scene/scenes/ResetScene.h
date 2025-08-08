#pragma once
#include "../Scene.h"

class ResetScene : public Scene {
public:
	/// <summary>
	///
	/// </summary>
	ResetScene();
	/// <summary>
	///
	/// </summary>
	~ResetScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 削除
	/// </summary>
	void Delete() override;
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui() override;

};
