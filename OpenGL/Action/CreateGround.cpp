#include "CreateGround.h"
#include "MainCameraObject.h"

// コンストラクタ
CreateGround::CreateGround()
{
}

// デストラクタ
CreateGround::~CreateGround()
{
}

// オブジェクトの更新処理
void CreateGround::UpdateGameObject(float _deltaTime)
{
	//Vector3(-250, 200, 0)離した距離からpositionを緩やかに追跡する。
	mainCamera->SetViewMatrixLerpObject(Vector3(-250, 200, 0), position);
}
