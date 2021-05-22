#include "Player.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "MainCameraObject.h"

// �R���X�g���N�^
Player::Player()
	// skeltalMeshComponent����
	: skeltalMeshComponent(new SkeletalMeshComponent(this))
{
	// Player��Tag��ݒ�
	tag = Tag::Player;
	// Player�̑傫����ݒ�
	SetScale(1.0f);
	// Player�̏����ʒu��ݒ�
	SetPosition(Vector3(0, 0, 0));

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	//skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Player.gpmesh"));

	printf("Player �R���X�g���N�^\n");
}

// �f�X�g���N�^
Player::~Player()
{
	printf("Player �R���X�g���N�^\n");
}

// �v���C���[�X�V����
void Player::UpdateGameObject(float _deltaTime)
{
	//Vector3(1000, 500, 1500)��������������position���ɂ₩�ɒǐՂ���B
	mainCamera->SetViewMatrixLerpObject(Vector3(1000, 500, 1500), position);
}

// �v���C���[���͏���
void Player::GameObjectInput(const InputState& _keyState)
{
}
