//=============================================================================
//	@file	PhysicsWorld.cpp
//	@brief	当たり判定を行う
//=============================================================================

#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "BoxCollider.h"
#include "GameObject.h"
#include "ColliderComponent.h"

PhysicsWorld* PhysicsWorld::physics = nullptr;

PhysicsWorld::PhysicsWorld()
{
}

void PhysicsWorld::CreateInstance()
{
	if (physics == nullptr)
	{
		physics = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}

void PhysicsWorld::HitCheck()
{
	//SphereAndSphere();
 //   BoxAndBox();
 //   SphereAndBox();
}

void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_box->GetBoxTag() == ColliderComponent::PlayerTag)
	{
	
		for (auto itr : groundBoxes)
		{
			//自分自身とは当たり判定を行わない
			if (itr == _box)
			{
				continue;
			}
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}

			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->refreshWorldTransform();
		
			}
		}

		for (auto itr : wallBoxes)
		{
			//自分自身とは当たり判定を行わない
			if (itr == _box)
			{
				continue;
			}
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}

			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->refreshWorldTransform();

			}
		}
	}
}



void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{
	ColliderComponent::PhysicsTag objTag = _box->GetBoxTag();

	switch (objTag)
	{
	case ColliderComponent::PlayerTag:
		// playerBoxesに情報を格納
		playerBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
		break;

	case ColliderComponent::GroundTag:
		// groundBoxesに情報を格納
		groundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
		break;

	case ColliderComponent::WallTag:
		// wallBoxesに情報を格納
		wallBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
		break;

	default:
		break;
	}
}

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{
	if (_box->GetBoxTag() == ColliderComponent::PlayerTag)
	{
		auto iter = std::find(playerBoxes.begin(), playerBoxes.end(), _box);
		if (iter != playerBoxes.end())
		{
			std::iter_swap(iter, playerBoxes.end() - 1);
			playerBoxes.pop_back();
		}
		collisionFunction.erase(_box);
	}
	if (_box->GetBoxTag() == ColliderComponent::WallTag)
	{
		auto iter = std::find(wallBoxes.begin(), wallBoxes.end(), _box);
		if (iter != wallBoxes.end())
		{
			std::iter_swap(iter, wallBoxes.end() - 1);
			wallBoxes.pop_back();
		}
		collisionFunction.erase(_box);
	}
	if (_box->GetBoxTag() == ColliderComponent::GroundTag)
	{
		auto iter = std::find(groundBoxes.begin(), groundBoxes.end(), _box);
		if (iter != groundBoxes.end())
		{
			std::iter_swap(iter, groundBoxes.end() - 1);
			groundBoxes.pop_back();
		}
		collisionFunction.erase(_box);
	}
	
	auto iter = std::find(boxes.begin(), boxes.end(), _box);
	if (iter != boxes.end())
	{
		std::iter_swap(iter, boxes.end() - 1);
		boxes.pop_back();
	}
    collisionFunction.erase(_box);
}


//void PhysicsWorld::SphereAndSphere()
//{
//	for (size_t i = 0; i < spheres.size(); i++)
//	{
//		if (spheres[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = i + 1; j < spheres.size(); j++)
//		{
//			if (spheres[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(spheres[i]->GetWorldSphere(), spheres[j]->GetWorldSphere());
//
//			if (hit)
//			{
//				SphereCollider* sphereA = spheres[i];
//				SphereCollider* sphereB = spheres[j];
//
//				//sphereA->GetOwner()->OnCollision(*(sphereB->GetOwner()));
//				//sphereB->GetOwner()->OnCollision(*(sphereA->GetOwner()));
//			}
//		}
//	}
//}
//
//void PhysicsWorld::BoxAndBox()
//{
//	for (size_t i = 0; i < boxes.size(); i++)
//	{
//		if (boxes[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = i + 1; j < boxes.size(); j++)
//		{
//			if (boxes[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(boxes[i]->GetWorldBox(), boxes[j]->GetWorldBox());
//
//			if (hit)
//			{
//				BoxCollider* boxA = boxes[i];
//				BoxCollider* boxB = boxes[j];
//
//				//boxA->GetOwner()->OnCollision(*(boxB->GetOwner()));
//				//boxB->GetOwner()->OnCollision(*(boxA->GetOwner()));
//			}
//		}
//	}
//}
//
//void PhysicsWorld::SphereAndBox()
//{
//
//
//	for (size_t i = 0; i < spheres.size(); i++)
//	{
//		if (spheres[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = 0; j < boxes.size(); j++)
//		{
//			if (boxes[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(spheres[i]->GetWorldSphere(), boxes[j]->GetWorldBox());
//
//			if (hit)
//			{
//				//spheres[i]->GetOwner()->OnCollision(*(boxes[j]->GetOwner()));
//				//boxes[j]->GetOwner()->OnCollision(*(spheres[i]->GetOwner()));
//			}
//		}
//	}
//}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}
