#include "TestComponent.h"
#include "GameObject.h"

TestComponent::TestComponent(GameObject* _owner, int _updateOrder):
	Component(_owner,_updateOrder)
{

}

TestComponent::~TestComponent()
{
}

void TestComponent::Update(float _deltaTime)
{
	//親GameObjectの座標に元の座標からx方向に-10した座標を足す
	owner->SetPosition(owner->GetPosition() + Vector3(-10, 0, 0));
}
