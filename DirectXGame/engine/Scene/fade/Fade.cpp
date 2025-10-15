#include "Fade.h"
using namespace KamataEngine;
Fade::Fade() {}

Fade::~Fade() {}

void Fade::Initialize() {
	//
	sprite_ = Sprite::Create(0, Vector2{});
	sprite_->SetSize(Vector2(1280, 720));
	sprite_->SetColor(Vector4(0, 0, 0, 1));
}
void Fade::Update() {
	// フェード状態による分岐
	switch (fadeID_) {
	case FadeID::None:

		break;
	case FadeID::FadeIn:

		// 1フレーム分の秒数をカウントダウン
		counter_ += speed / frameTime;
		// フェード継続時間に達したら打ち止め
		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		// 0.0fから1.0fの間で、経過時間がフェード継続時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, 1.0f - std::clamp(counter_ / duration_, 0.0f, 1.0f)));
		break;
	case FadeID::FadeOut:
		// 1フレーム分の秒数をカウントアップ
		counter_ += speed / frameTime;
		// フェード継続時間に達したら打ち止め
		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		// 0.0fから1.0fの間で、経過時間がフェード継続時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp(counter_ / duration_, 0.0f, 1.0f)));
		break;

	}


}
void Fade::Draw() {
	if (fadeID_==FadeID::None) {
		return;
	}

	//
	sprite_->Draw();

}

void Fade::Start(FadeID fadeId_, float duration) {
	//
	fadeID_ = fadeId_;
	duration_ = duration;
	counter_ = initilizeCounter;
}

void Fade::Stop() {
	fadeID_ = FadeID::None; }

bool Fade::IsFinished() const {
	//フェード状態による分岐
	switch (fadeID_) {

	case FadeID::FadeIn:
	case FadeID::FadeOut:
		if (counter_ >= duration_) {
			return true;
		} else {
			return false;
		}
	}
	return true;
}
