#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include "KamataEngine.h"
#include "PausePage.h"
#include <Xinput.h>
#include <functional>
#include <map>
#include <vector>

using ButtonCreator = std::function<MenuButton(FileJson::FileAccessor*)>;

class PauseMenu {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initilize();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="xinput">最新のコントローラーの状態</param>
	/// <param name="preXinput">前回のコントローラーの状態</param>
	void Update(const XINPUT_STATE& xinput, const XINPUT_STATE& preXinput);
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 開放処理
	/// </summary>
	void Delete();
	/// <summary>
	/// ImGui描画処理
	/// </summary>
	void DrawImGui();

	/// <summary>
	/// メニューの階層を増やす
	/// </summary>
	/// <param name="page">新しく追加するページ</param>
	void PushPage(PausePage* page);
	/// <summary>
	/// 今現在のページを閉じる
	/// </summary>
	void PopPage();

	/// <summary>
	/// Jsonデータからボタンを動的生成するためのファクトリーを登録
	/// </summary>
	/// <param name="id">管理用ID</param>
	/// <param name="creator">FileAccessorを受け取りMenuButtonを返す関数オブジェクト</param>
	void RegisterButton(PauseID id, ButtonCreator creator);
	/// <summary>
	/// メニューの動作を登録
	/// </summary>
	/// <param name="id">管理用ID</param>
	/// <param name="action">メニューの動作</param>
	void SetAction(PauseID id, std::function<void()> action);
	/// <summary>
	/// 指定されたID通りにページを生成する
	/// </summary>
	/// <param name="order">管理用IDのリスト</param>
	/// <returns>構築済みのPausePageインスタンス</returns>
	PausePage* BuilldPage(const std::vector<PauseID>& order);
	/// <summary>
	/// ポーズメニューが表示されているかどうか
	/// </summary>
	/// <returns>メニューが表示されている場合はtrue,されていない場合はfalse</returns>
	bool IsOpen() const { return !pageStack_.empty(); }

	/// <summary>
	/// メインページを設定
	/// </summary>
	/// <param name="page">メインページのインスタンス</param>
	void SetMainPage(PausePage* page) { mainPage_ = page; }

private:
	// ファイル関連
	const std::string filePath_ = "Resources/Json/PauseMenu.json";
	FileJson::FileAccessor* fileAccessor_ = nullptr;

	// ページ関連
	std::vector<PausePage*> pageStack_;
	std::map<PauseID, ButtonCreator> buttonFactory_;
	std::map<PauseID, std::function<void()>> actionMap_;

	// コントローラー関連
	bool isLStickPushed_ = false;

	// ポーズ時のページ背景
	uint32_t backScreenTh_ = 0;
	KamataEngine::Sprite* backScreenSprite_ = nullptr;
	KamataEngine::Vector2 backScreenPos_;
	KamataEngine::Vector2 backScreenSize_;
	KamataEngine::Vector4 backScreenColor_;

	PausePage* mainPage_ = nullptr;
};
