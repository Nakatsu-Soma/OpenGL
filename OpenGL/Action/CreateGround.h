#pragma once
#include "GameObject.h"

// �n�ʐ���
class CreateGround : public GameObject
{
public:
	// �R���X�g���N�^
	CreateGround();
	// �f�X�g���N�^
	~CreateGround();

	// �I�u�W�F�N�g�̍X�V����
	void UpdateGameObject(float _deltaTime)override;
};