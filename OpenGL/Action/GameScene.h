#pragma once
#include "Game.h"
#include "SceneBase.h"

class GameScene : public SceneBase
{
public:
	// コンストラクタ
	GameScene();
	// デストラクタ
	~GameScene();

	// 更新処理
	SceneBase* update();
	// 描画処理
	void draw();

private:

	// TiledMapCreaterへのポインタ
	class LoadTiledMap* loadTiledMap;
	// LoadAssetへのポインタ
	class LoadAssetMap* loadAssetMap;
};