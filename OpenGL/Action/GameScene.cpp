#include "GameScene.h"
#include "Renderer.h"
#include "Player.h"
#include "LoadTiledMap.h"
#include "LoadAssetMap.h"

GameScene::GameScene()
	// tiledMapCreater����
	: loadTiledMap(new LoadTiledMap())
	// loadAssetMap����
	, loadAssetMap(new LoadAssetMap())
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �}�b�v��json�t�@�C�����ǂݍ��܂�Ă��邩
	if (!loadTiledMap->OpenFile())
	{
		// �n�ʍ쐬
		loadTiledMap->CreateGround();
	}

	// �}�b�v��Mesh�ǂݍ���
	loadAssetMap->LoadMesh("Assets/MapAsset/TestMesh.gpmesh");

	// Player����
	new class Player();

	printf("GameScene �R���X�g���N�^\n");
}

GameScene::~GameScene()
{
	printf("GameScene �f�X�g���N�^\n");
}

SceneBase* GameScene::update()
{
	return nullptr;
}

void GameScene::draw()
{
}
