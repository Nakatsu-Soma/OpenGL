#include "TestScene.h"
#include "Renderer.h"
#include "TestObject.h"
#include "MapCreate.h"

TestScene::TestScene()
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	/*
	テストモデルの生成　解放はこのオブジェクトの継承元が自動でオブジェクト全体を管理しているクラスに追加されそのクラスで行われる
	①TestObjectが生成される
	②基底クラス内でGameObjectManager内のコンテナに追加される
	③GameObjectManagerが解放される時に全てのゲームオブジェクトが解放される
	*/
	// new TestObject();

	mapCreate = new MapCreate();

	// マップのjsonファイルが読み込まれているか
	if (!mapCreate->OpenFile())
	{
		// 地面作成
		mapCreate->CreateGround();
	}

	printf("TestScene コンストラクタ\n");
}

TestScene::~TestScene()
{
	printf("TestScene デストラクタ\n");
}
