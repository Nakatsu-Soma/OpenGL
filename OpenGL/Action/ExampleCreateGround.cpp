#include "ExampleCreateGround.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "ColliderComponent.h"

ExampleCreateGround::ExampleCreateGround(Vector3 _objectPos, Vector3 _objectSize, Tag _Tag)
	// mesh生成
	:mesh(new Mesh())
	// meshComponent生成
	, meshComponent(new MeshComponent(this))
	// boxCollider生成
	, boxCollider(new BoxCollider(this, ColliderComponent::PhysicsTag::GroundTag, GetOnCollisionFunc()))
{
	// Groundにtagを設定
	tag = _Tag;
	// Groundの大きさを設定
	SetScale(_objectSize);
	// Groundの位置を設定
	SetPosition(_objectPos);

	// マップのgpmesh読み込み
	mesh = RENDERER->GetMesh("Assets/MapBlock/Block.gpmesh");
	// ログ表示
	printf("Blockのgpmesh読み込み成功");
	// meshComponentにセット(ここで描画処理は終わり)
	meshComponent->SetMesh(mesh);

	// メッシュの大きさ取得
	AABB groundBox = mesh->GetAABB();
	// PhysicsWorldにBoxを追加し当たり判定を反映
	boxCollider->SetObjectBox(groundBox);

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

	printf("CreateGround コンストラクタ\n");
}

ExampleCreateGround::~ExampleCreateGround()
{
	printf("CreateGround デストラクタ\n");
}

// オブジェクトの更新処理
void ExampleCreateGround::UpdateGameObject(float _deltaTime)
{

}

// 当たり判定処理
void ExampleCreateGround::OnCollision(const GameObject& _hitObject)
{
}
