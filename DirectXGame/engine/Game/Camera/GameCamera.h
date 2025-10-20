#pragma once
#include "../LoadJsonFile/FileJson.h"
#include <KamataEngine.h>
class GameCamera {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCamera();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCamera();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void ImGuiDraw();

	KamataEngine::Camera* GetCamera() { return camera_; }

private:
	KamataEngine::Camera* camera_;

	const std::string filePath = "Resources/Json/GameCamera.json";
	std::string fileMain = "GameCamera";

	FileJson::FileAccessor* fileAccessor_ = nullptr;
};
