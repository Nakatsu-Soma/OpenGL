#pragma once

/*
 @file PhysicsWorld.h
 @brief �������ꂽColliderComponent�ւ̃A�h���X���������A
		�Փ˔�����s��ColliderComponent�ɏՓ˂������Ƃ�`����N���X
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
@brief ColliderComponent���Ǘ����Փ˂��s���N���X
*/
class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physics; }
	static void CreateInstance();
	static void DeleteInstance();

	//�����蔻��
	void HitCheck();
	void HitCheck(BoxCollider* _box);

	//AABB�̒ǉ��ƍ폜
	void AddBox(BoxCollider* _box, onCollisionFunc _func);
	void RemoveBox(BoxCollider* _box);
private:
	PhysicsWorld();
	~PhysicsWorld() {};
	static PhysicsWorld* physics;

	//�������ꂽColliderComponent�S�ẴA�h���X���L��
	std::vector<BoxCollider*> boxes;
	std::vector<BoxCollider*> playerBoxes;
	std::vector<BoxCollider*> wallBoxes;
	std::vector<BoxCollider*> groundBoxes;

	onCollisionMap collisionFunction;
};

/*
@fn �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
@param _movableBox �ړ�����
@param _fixedBox �ړ����Ȃ�����
@param _calcFixVec �ړ����̂̕␳�����x�N�g��
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
