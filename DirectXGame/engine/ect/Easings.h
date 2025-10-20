#pragma once
#include"KamataEngine.h"
namespace Easings {
float EaselnQuart(float t);

float EaseInTime(float t, float time);

// EaseInTime の引数を変更
KamataEngine::Vector3 EaseInTime(const KamataEngine::Vector3& startPos, const KamataEngine::Vector3& targetPos, float currentTime, float duration);

//    // 追加：EaseInQuad関数
//float EaseInQuad(float t);

// 追加：加速度イージング用
KamataEngine::Vector3 EaseInAcceleration(const KamataEngine::Vector3& startVelocity, const KamataEngine::Vector3& maxVelocity, float currentTime, float duration);
}