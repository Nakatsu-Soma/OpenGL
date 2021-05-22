#pragma once
#include "GameObject.h"

// 地面生成
class CreateGround : public GameObject
{
public:
	// コンストラクタ
	CreateGround();
	// デストラクタ
	~CreateGround();

	// オブジェクトの更新処理
	void UpdateGameObject(float _deltaTime)override;
};