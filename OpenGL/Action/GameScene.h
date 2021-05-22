#pragma once
#include "Game.h"
#include "SceneBase.h"

class GameScene : public SceneBase
{
public:
	// �R���X�g���N�^
	GameScene();
	// �f�X�g���N�^
	~GameScene();

	// �X�V����
	SceneBase* update();
	// �`�揈��
	void draw();

private:

	// TiledMapCreater�ւ̃|�C���^
	class LoadTiledMap* loadTiledMap;
	// LoadAsset�ւ̃|�C���^
	class LoadAssetMap* loadAssetMap;
};