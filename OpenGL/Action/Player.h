#pragma once
#include"GameObject.h"

// Playerを生成するGameObjectクラス
class Player :
	public GameObject
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();
	// プレイヤー更新処理
	void UpdateGameObject(float _deltaTime)override;
	// プレイヤー入力処理
	void GameObjectInput(const InputState& _keyState)override;

private:
	// SkeletalMeshComponentへのポインタ
	class SkeletalMeshComponent* skeltalMeshComponent;
};