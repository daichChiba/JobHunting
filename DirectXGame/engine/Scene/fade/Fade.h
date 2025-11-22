#pragma once
#include "FadeID.h"
#include <algorithm>
#include <KamataEngine.h>
/// <summary>
/// フェードの状況を取得して、ゲーム内に反映するクラス
/// フェードの入出力と描画を統合的に扱う
/// </summary>
class Fade {
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	Fade();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Fade();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 指定したフェードIDでフェードを開始します。
	/// </summary>
	/// <param name="fadeId_">開始するフェードのID。</param>
	/// <param name="duration">フェードの継続時間</param>
	void Start(FadeID fadeId_, float duration);

	/// <summary>
	/// フェードを停止します。
	/// </summary>
	void Stop();

	/// <summary>
	/// フェード終了判定
	/// </summary>
	/// <returns></returns>
	bool IsFinished() const;

private:
	//現在のフェードの状態
	FadeID fadeID_ = FadeID::None;
	// 
	KamataEngine::Sprite* sprite_ = nullptr;

	// フェードの持続時間
	float duration_ = 0.0f;

	// 経過時間カウンター
	float counter_ = 0.0f;
	// 経過時間の初期化
	const float initilizeCounter = 0.0f;
	// フェードのスピード
	float speed = 0.5f;
	// 一秒あたりのフレーム数
	const float frameTime = 60;
};
