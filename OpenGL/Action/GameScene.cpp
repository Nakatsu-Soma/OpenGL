#include "GameScene.h"
#include "Renderer.h"
#include "Player.h"
#include "LoadTiledMap.h"
#include "LoadAssetMap.h"

GameScene::GameScene()
	// tiledMapCreater生成
	: loadTiledMap(new LoadTiledMap())
	// loadAssetMap生成
	, loadAssetMap(new LoadAssetMap())
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// マップのjsonファイルが読み込まれているか
	if (!loadTiledMap->OpenFile())
	{
		// 地面作成
		loadTiledMap->CreateGround();
	}

	// マップのMesh読み込み
	loadAssetMap->LoadMesh("Assets/MapAsset/TestMesh.gpmesh");

	// Player生成
	new class Player();

	printf("GameScene コンストラクタ\n");
}

GameScene::~GameScene()
{
	printf("GameScene デストラクタ\n");
}

SceneBase* GameScene::update()
{
	return nullptr;
}

void GameScene::draw()
{
}
