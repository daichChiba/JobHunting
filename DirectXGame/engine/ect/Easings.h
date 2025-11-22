#pragma once
#include "KamataEngine.h"
/// <summary>
/// イージングに関するnamespace
/// イージングに関する関数をここで扱う
/// </summary>
namespace Easings {
/// <summary>
/// イーズイン
/// </summary>
/// <param name="t">入力値</param>
/// <returns>四次イーズイン補間の結果を表す</returns>
float EaselnQuart(float t);
/// <summary>
/// 指定した時刻におけるイーズイン
/// </summary>
/// <param name="t">現在の時刻または進行量。通常は補間の経過時間や正規化された進行値を指定します（例: 0 から time の範囲）。</param>
/// <param name="time">イーズイン補間の総時間または継続時間。補間の完了時刻を示します。</param>
/// <returns>イーズイン補間を適用した結果の値（float）。入力 t に基づく変換済みの進行度合いを返します。</returns>
float EaseInTime(float t, float time);

// EaseInTime の引数を変更

/// <summary>
/// 開始位置から目標位置へイーズイン（Ease-In）曲線で補間し、指定した現在時刻における位置を返します。
/// </summary>
/// <param name="startPos">補間を開始する位置。</param>
/// <param name="targetPos">補間の終了位置</param>
/// <param name="currentTime">経過時間または補間開始からの現在時刻（通常は0からdurationまでの範囲）。</param>
/// <param name="duration">補間に要する総時間（通常は正の値）。</param>
/// <returns>指定した時刻に基づくイーズイン補間後の位置</returns>
KamataEngine::Vector3 EaseInTime(const KamataEngine::Vector3& startPos, const KamataEngine::Vector3& targetPos, float currentTime, float duration);

//    // 追加：EaseInQuad関数
// float EaseInQuad(float t);

// 追加：加速度イージング用

/// <summary>
/// 加速度イーズイン
/// </summary>
/// <param name="startVelocity">補間の開始点となる速度ベクトル（初期速度）。</param>
/// <param name="maxVelocity">補間の目標となる最大速度ベクトル（目標速度）。</param>
/// <param name="currentTime">経過時間（秒）。通常は 0 から duration の範囲で指定し、その時点の補間結果を求めるために使用します。</param>
/// <param name="duration">補間に要する総時間（秒）。currentTime がこの値に達するまで加速が続きます。</param>
/// <returns>currentTime におけるイーズイン補間結果の速度ベクトル（startVelocity から maxVelocity へ移行した値）。</returns>
KamataEngine::Vector3 EaseInAcceleration(const KamataEngine::Vector3& startVelocity, const KamataEngine::Vector3& maxVelocity, float currentTime, float duration);
} // namespace Easings