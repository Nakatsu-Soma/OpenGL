#include "CreateGround.h"
#include "MainCameraObject.h"

// �R���X�g���N�^
CreateGround::CreateGround()
{
}

// �f�X�g���N�^
CreateGround::~CreateGround()
{
}

// �I�u�W�F�N�g�̍X�V����
void CreateGround::UpdateGameObject(float _deltaTime)
{
	//Vector3(-250, 200, 0)��������������position���ɂ₩�ɒǐՂ���B
	mainCamera->SetViewMatrixLerpObject(Vector3(-250, 200, 0), position);
}
