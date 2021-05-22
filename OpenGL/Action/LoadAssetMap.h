#pragma once
#include"GameObject.h"

// アセットからマップを読み込むクラス
class LoadAssetMap : public GameObject
{
public:
	// コンストラクタ
	LoadAssetMap();
	// デストラクタ
	~LoadAssetMap();

	// Meshの更新処理
	void UpdateGameObject(float _deltaTime)override;

	// Meshが読み込めたか
	void LoadMesh(const char* _gpmeshFileName);

private:

	//Meshへのポインタ
	class Mesh* mesh;
	// MeshComponentへのポインタ
	class MeshComponent* meshComponent;
};