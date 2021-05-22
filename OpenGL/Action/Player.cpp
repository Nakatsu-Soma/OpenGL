#include "Player.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "MainCameraObject.h"

// コンストラクタ
Player::Player()
	// skeltalMeshComponent生成
	: skeltalMeshComponent(new SkeletalMeshComponent(this))
{
	// PlayerにTagを設定
	tag = Tag::Player;
	// Playerの大きさを設定
	SetScale(1.0f);
	// Playerの初期位置を設定
	SetPosition(Vector3(0, 0, 0));

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	//skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Player.gpmesh"));

	printf("Player コンストラクタ\n");
}

// デストラクタ
Player::~Player()
{
	printf("Player コンストラクタ\n");
}

// プレイヤー更新処理
void Player::UpdateGameObject(float _deltaTime)
{
	//Vector3(1000, 500, 1500)離した距離からpositionを緩やかに追跡する。
	mainCamera->SetViewMatrixLerpObject(Vector3(1000, 500, 1500), position);
}

// プレイヤー入力処理
void Player::GameObjectInput(const InputState& _keyState)
{
}
