#include "LoadAssetMap.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"

// コンストラクタ
LoadAssetMap::LoadAssetMap()
	// mesh生成
	: mesh(new Mesh())
	// meshComponent生成
	, meshComponent(new MeshComponent(this))
{
	printf("LoadAssetMap コンストラクタ\n");
}

// デストラクタ
LoadAssetMap::~LoadAssetMap()
{
	printf("LoadAssetMap デストラクタ\n");
}

// Meshの更新処理
void LoadAssetMap::UpdateGameObject(float _deltaTime)
{

}

// Meshを読み込めたか
void LoadAssetMap::LoadMesh(const char* _gpmeshFileName)
{
	// アセットのメッシュを取得
	mesh = RENDERER->GetMesh(_gpmeshFileName);

	// Meshを読み込めたか
	if (!mesh)
	{
		// ログ表示
		printf("Mesh読み込み失敗 : %s\n", _gpmeshFileName);
		return;
	}

	// ログ表示
	printf("Mesh読み込み成功 : %s\n", _gpmeshFileName);

	// MeshCompornentにMeshをセット(ここで描画処理は終わり)
	meshComponent->SetMesh(mesh);

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