#pragma once
#include"GameObject.h"

// Player�𐶐�����GameObject�N���X
class Player :
	public GameObject
{
public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();
	// �v���C���[�X�V����
	void UpdateGameObject(float _deltaTime)override;
	// �v���C���[���͏���
	void GameObjectInput(const InputState& _keyState)override;

private:
	// SkeletalMeshComponent�ւ̃|�C���^
	class SkeletalMeshComponent* skeltalMeshComponent;
};