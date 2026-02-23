#include "PausePage.h"

void PausePage::AddButton(const MenuButton& btn) {
	// ボタンをリストに追加
	items_.push_back(btn);
}

void PausePage::Update(bool isMoveUp, bool isMoveDown, bool isDecide) {
	// 上ボタンを押されたときの処理
	if (isMoveUp) {
		cursor_--;
		if (cursor_ < 0) {
			cursor_ = GetMax();
		}
	}
	// 上ボタンを押されたときの処理
	if (isMoveDown) {
		cursor_++;
		if (cursor_ > GetMax()) {
			cursor_ = 0;
		}
	}
	// 決定ボタンを押されたときの処理
	if (isDecide && items_[cursor_].onSelect) {
		items_[cursor_].onSelect();
	}
}

void PausePage::Draw(int cursor) const {
	for (int i = 0; i < static_cast<int>(items_.size()); i++) {
		// ボタン選択時の明度の変更の処理
		float alpha = 1.0f;
		if (items_.size() > 1) {
			if (i == cursor) {
				alpha = 1.0;
			} else {
				alpha = 0.5f;
			}
		}
		// 描画の処理
		items_[i].sprite->SetColor({1.0f, 1.0f, 1.0f, alpha});
		items_[i].sprite->Draw();
	}
}
