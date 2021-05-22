#pragma once
#include "GameObject.h"

// LoadTiledMapから得た情報を元にGroundを生成するGameObjectクラス
class ExampleCreateGround : public GameObject
{
public:
	// コンストラクタ
	ExampleCreateGround(Vector3 _objectpos, Vector3 objectSize, Tag _Tag);
	// デストラクタ
	~ExampleCreateGround();

	// オブジェクトの更新処理
	void UpdateGameObject(float _deltaTime)override;

private:

	Vector3 pos;
	//Meshへのポインタ
	class Mesh* mesh;
	// MeshComponentへのポインタ
	class MeshComponent* meshComponent;
	// BoxColliderへのポインタ
	class BoxCollider* boxCollider;

	// 当たり判定処理
	void OnCollision(const GameObject& _hitObject);
};