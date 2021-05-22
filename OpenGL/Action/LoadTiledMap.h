#pragma once
#include"GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

// Tiled����}�b�v��ǂݍ��ރN���X
class LoadTiledMap : public GameObject
{
public:
	// �R���X�g���N�^
	LoadTiledMap();
	// �f�X�g���N�^
	~LoadTiledMap();

	// Json�t�@�C�������݂���΃}�b�v�f�[�^�z���Json�t�@�C���̏���n��
	bool OpenFile();

	// �n�ʐ���
	void CreateGround();

private:
	// �^�C���f�[�^�ǂݍ���
	bool readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName);
	// layerName�̃��C���[���������A���̃C���f�b�N�X�l��Ԃ�
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& layer,std::string& layerName);

	// �}�b�v�f�[�^
	std::vector<std::vector<int>> groundMapData;

	// �u���b�N�̌�
	int sizeX;
	int sizeY;
	int sizeZ;
	// �u���b�N�T�C�Y
	float blockSize;
};