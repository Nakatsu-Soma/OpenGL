#pragma once

/*
 @file PhysicsWorld.h
 @brief 生成されたColliderComponentへのアドレスを所持し、
		衝突判定を行いColliderComponentに衝突したことを伝えるクラス
 */

#include <vector>
#include "Math.h"
#include "Collision.h"
#include "GameObject.h"

class ColliderComponent;
class BoxCollider;
#define PHYSICS PhysicsWorld::GetInstance()

typedef std::function<void(GameObject&)> onCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> onCollisionMap;

/*
@file PhysicsWorld.h
@brief ColliderComponentを管理し衝突を行うクラス
*/
class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physics; }
	static void CreateInstance();
	static void DeleteInstance();

	//当たり判定
	void HitCheck();
	void HitCheck(BoxCollider* _box);

	//AABBの追加と削除
	void AddBox(BoxCollider* _box, onCollisionFunc _func);
	void RemoveBox(BoxCollider* _box);
private:
	PhysicsWorld();
	~PhysicsWorld() {};
	static PhysicsWorld* physics;

	//生成されたColliderComponent全てのアドレスを記憶
	std::vector<BoxCollider*> boxes;
	std::vector<BoxCollider*> playerBoxes;
	std::vector<BoxCollider*> wallBoxes;
	std::vector<BoxCollider*> groundBoxes;

	onCollisionMap collisionFunction;
};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
