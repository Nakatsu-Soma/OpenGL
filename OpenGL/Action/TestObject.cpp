#include "TestObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"
#include <string>
#include "Renderer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "InputSystem.h"
#include "TestComponent.h"

TestObject::TestObject() :
	GameObject()
{
	//GameObjectメンバ変数の初期化
	tag = Tag::Other;
	SetScale(1.0f);
	SetPosition(Vector3(0, 0, 0));

	//更新の度に左に移動するコンポーネントを生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	new TestComponent(this);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Skelton_King/skeleton_king_king.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Skelton_King/skeleton_king_king.gpskel"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = RENDERER->GetAnimation("Assets/Model/Skelton_King/KingRun.gpanim");
	//anim変数を速度0.5fで再生
	skeltalMeshComponent->PlayAnimation(anim, 0.5f);

	//Z軸を90度回転させる
	float radian = Math::ToRadians(90);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	//X軸を-90度回転させる
	radian = Math::ToRadians(-90);
	rot = this->GetRotation();
	inc = Quaternion(Vector3::UnitX, radian);
	target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

TestObject::~TestObject()
{
}

void TestObject::UpdateGameObject(float _deltaTime)
{
	//Vector3(0, 180, -400)離した距離からpositionを緩やかに追跡する。
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 140, -400), position);
}

void TestObject::GameObjectInput(const InputState& _keyState)
{
	//キーボードAが入力されたらxを足す
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		SetPosition(position + Vector3(20, 0, 0));
	}
}
