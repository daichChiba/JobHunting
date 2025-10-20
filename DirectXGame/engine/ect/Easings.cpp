#define NOMINMIN
#include "Easings.h"
#include <cmath>
using namespace KamataEngine;

using namespace MathUtility;
namespace Easings {
float EaselnQuart(float t) { return t * t * t * t; }

float EaseInTime(float t, float time) { return (t / time); }

// EaseInTime の実装を変更
Vector3 EaseInTime(const Vector3& startPos, const Vector3& targetPos, float currentTime, float duration) {
	if (duration <= 0.1f) {
		return targetPos; // durationが0以下の場合は目標位置を返す
	}
	float t = currentTime / duration;
	t = (std::min)(t, 1.0f); // 0~1 の範囲にクランプ
	t = t * t;               // EaseIn効果を適用

	// 線形補間（lerp）を使って計算
	return Vector3(startPos.x + (targetPos.x - startPos.x) * t, startPos.y + (targetPos.y - startPos.y) * t, startPos.z + (targetPos.z - startPos.z) * t);
}

// 加速度イージング関数
Vector3 EaseInAcceleration(const Vector3& startVelocity, const Vector3& maxVelocity, float currentTime, float duration) {
	if (duration <= 0.1f) {
		return maxVelocity; // durationが0以下の場合は最大速度を返す
	}

	float t = currentTime / duration;
	t = (std::min)(t, 1.0f); // 0~1 の範囲にクランプ

	float easedT = EaselnQuart(t); // EaseInQuadを適用

	// 加速度を適用した速度を計算
	return startVelocity + (maxVelocity - startVelocity) * easedT;
}

} // namespace Easings