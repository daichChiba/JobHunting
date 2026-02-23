#pragma once
#include "KamataEngine.h"
#include <functional>
#include <string>
#include <vector>

enum class PauseID {
	kReturnGame,
	kGuide,
	kTitel,
	kRestart,
	kGuideImage,
};

struct MenuButton {
	PauseID type;
	std::string jsonKey;
	uint32_t textureHandle = 0;
	KamataEngine::Sprite* sprite;
	KamataEngine::Vector2 pos;
	KamataEngine::Vector2 size;
	std::function<void()> onSelect;
};

class PausePage {
public:
	/// <summary>
	/// メニューにボタンを追加する
	/// </summary>
	/// <param name="btn">追加するメニューボタンをここに記入</param>
	void AddButton(const MenuButton& btn);
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="isMoveUp">カーソルが上に移動する場合はtrue,移動しない場合はfalse</param>
	/// <param name="isMoveDown">カーソルが下に移動する場合はtrue,移動しない場合はfalse</param>
	/// <param name="isDecide">決定ボタンが押された場合はtrue,押されていない場合はfalse</param>
	void Update(bool isMoveUp, bool isMoveDown, bool isDecide);
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="cursor">カーソルの位置</param>
	void Draw(int cursor) const;
	/// <summary>
	/// カーソル位置を取得
	/// </summary>
	/// <returns>現在のカーソル位置</returns>
	int GetCursor() const { return cursor_; }
	/// <summary>
	/// ボタン数に基づいて最大インデックスを取得
	/// </summary>
	/// <returns>最大のインデックス（ボタン数 - 1）。</returns>
	int GetMax() const { return static_cast<int>(items_.size()) - 1; }
	/// <summary>
	/// カーソルを初期位置にリセットする
	/// </summary>
	void ResetCursor() { cursor_ = 0; }
	/// <summary>
	/// 指定されたメニューボタンを取得
	/// </summary>
	/// <param name="index">取得するボタンの数値</param>
	/// <returns>指定された数値にあるMenuButton</returns>
	MenuButton& GetButton(int index) { return items_[index];}
	/// <summary>
	/// ボタンの数を取得
	/// </summary>
	/// <returns>ボタンの総数</returns>
	int GetButtonCount() const { return static_cast<int>(items_.size()); }

private:
	std::vector<MenuButton> items_;
	int cursor_ = 0;
};
