#pragma once
#include "Component.h"

//¶‚ÉˆÚ“®‚µ‘±‚¯‚éGameObject‚Ì•â•ƒNƒ‰ƒX
class TestComponent :
	public Component
{
public:
	TestComponent(GameObject* _owner, int _updateOrder = 100);
	~TestComponent();

	void Update(float _deltaTime)override;
};

