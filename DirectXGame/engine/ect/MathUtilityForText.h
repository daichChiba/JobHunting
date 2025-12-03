#pragma once
#include "../../engine/ect/AABB.h"
/// <summary>
/// 2つの軸整列境界ボックス (AABB) が衝突しているかを判定します。
/// </summary>
/// <param name="aabb1">比較する1つ目の軸整列境界ボックス（AABB）。</param>
/// <param name="aabb2">比較する2つ目の軸整列境界ボックス（AABB）。</param>
/// <returns>AABBが交差（衝突）していればtrue、していなければfalseを返します。</returns>
bool IsCollision(const AABB& aabb1, const AABB& aabb2);
