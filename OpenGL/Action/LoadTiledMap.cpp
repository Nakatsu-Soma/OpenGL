#include "LoadTiledMap.h"
#include "ExampleCreateGround.h"

// コンストラクタ
LoadTiledMap::LoadTiledMap()
	: GameObject()
{
	// ブロックの個数初期化
	sizeX = 0;
	sizeY = 0;
	sizeZ = 0;
	// ブロックサイズ初期化
	blockSize = 100;

	printf("LoadTiledMap コンストラクタ\n");
}

// デストラクタ
LoadTiledMap::~LoadTiledMap()
{
	printf("LoadTiledMap デストラクタ\n");
}

// Jsonファイルが存在すればマップデータ配列にJsonファイルの情報を渡す
bool LoadTiledMap::OpenFile()
{
	// Jsonファイルが存在するか
	if (!readTiledJson(groundMapData, "Assets/MapBlock/sample.json", "Ground"))
	{
		// ログ表示
		printf("Jsonファイル読み込み失敗\n");
		return true;
	}

	// ログ表示
	printf("Jsonファイル読み込み成功\n");

	// ブロックの個数初期化
	sizeX = groundMapData[0].size();
	sizeY = groundMapData[0].size();
	sizeZ = groundMapData.size();

	return false;
}

// 地面生成(壁なら壁を生成する関数を作る)
void LoadTiledMap::CreateGround()
{
	// ブロックの個数分ループを回す
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			// 取得した数値をnameに渡す
			const unsigned int name = groundMapData[(int)iz][(int)ix];
			// ポジション設定
			Vector3 objectPos = Vector3(blockSize * ix, 0, -blockSize * iz);
			// サイズ指定
			Vector3 objectSize = Vector3(0.5f, 0.5f, 0.5f);

			 // 貰った数値をもとにタグを付ける
			switch (name)
			{
			case(1):
				// ここでブロックを生成するクラスnewする(呼ぶ)
				#pragma region new ClassName(pos, size, tag)
				new class ExampleCreateGround(objectPos, objectSize, Tag::Ground);
				#pragma endregion
				break;
			}
		}
	}
}

// タイルデータ読み込み
bool LoadTiledMap::readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc,fileName))
	{
		return false;
	}

	//開いたdocumentのtypeはmapか？
	if (!IsExistMemberAndValue(doc,"type","map"))
	{
		return false;
	}

	//開いたdocumentにlayerはあるか？
	if (!IsExistArrayName(doc,"layers"))
	{
		return false;
	}
	//layer数を取得
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer名から該当layerの添え字を調べる
	std::string layerNameString(layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", layerName);
		return false;
	}

	//レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//ユーザー配列確保　行方向、列方向の順番にサイズ確保
	mapData.resize(height);
	for (auto&mapIter:mapData)
	{
		mapIter.resize(width);
	}

	//ユーザー配列（2次元）にデータをコピー
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//なぜかIDが+1ずれているので補正する
			mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

/*
@fn	layerNameのレイヤーを検索し、そのインデックス値を返す
@param よくわからん
@param 要素数を見つけたいレイヤー
@param ↑のレイヤー名
*/
int LoadTiledMap::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName)
{
	int layerSize = layer.Size();
	int i;
	std::string layerNameString(layerName);
	for ( i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = layer[i]["name"].GetString();
		printf("%s\n", currentLayerName.c_str());
		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}
	return i;
}