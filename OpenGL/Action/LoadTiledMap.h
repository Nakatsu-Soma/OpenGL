#pragma once
#include"GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

// Tiledからマップを読み込むクラス
class LoadTiledMap : public GameObject
{
public:
	// コンストラクタ
	LoadTiledMap();
	// デストラクタ
	~LoadTiledMap();

	// Jsonファイルが存在すればマップデータ配列にJsonファイルの情報を渡す
	bool OpenFile();

	// 地面生成
	void CreateGround();

private:
	// タイルデータ読み込み
	bool readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName);
	// layerNameのレイヤーを検索し、そのインデックス値を返す
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& layer,std::string& layerName);

	// マップデータ
	std::vector<std::vector<int>> groundMapData;

	// ブロックの個数
	int sizeX;
	int sizeY;
	int sizeZ;
	// ブロックサイズ
	float blockSize;
};