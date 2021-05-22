#include "LoadTiledMap.h"
#include "ExampleCreateGround.h"

// �R���X�g���N�^
LoadTiledMap::LoadTiledMap()
	: GameObject()
{
	// �u���b�N�̌�������
	sizeX = 0;
	sizeY = 0;
	sizeZ = 0;
	// �u���b�N�T�C�Y������
	blockSize = 100;

	printf("LoadTiledMap �R���X�g���N�^\n");
}

// �f�X�g���N�^
LoadTiledMap::~LoadTiledMap()
{
	printf("LoadTiledMap �f�X�g���N�^\n");
}

// Json�t�@�C�������݂���΃}�b�v�f�[�^�z���Json�t�@�C���̏���n��
bool LoadTiledMap::OpenFile()
{
	// Json�t�@�C�������݂��邩
	if (!readTiledJson(groundMapData, "Assets/MapBlock/sample.json", "Ground"))
	{
		// ���O�\��
		printf("Json�t�@�C���ǂݍ��ݎ��s\n");
		return true;
	}

	// ���O�\��
	printf("Json�t�@�C���ǂݍ��ݐ���\n");

	// �u���b�N�̌�������
	sizeX = groundMapData[0].size();
	sizeY = groundMapData[0].size();
	sizeZ = groundMapData.size();

	return false;
}

// �n�ʐ���(�ǂȂ�ǂ𐶐�����֐������)
void LoadTiledMap::CreateGround()
{
	// �u���b�N�̌������[�v����
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			// �擾�������l��name�ɓn��
			const unsigned int name = groundMapData[(int)iz][(int)ix];
			// �|�W�V�����ݒ�
			Vector3 objectPos = Vector3(blockSize * ix, 0, -blockSize * iz);
			// �T�C�Y�w��
			Vector3 objectSize = Vector3(0.5f, 0.5f, 0.5f);

			 // ��������l�����ƂɃ^�O��t����
			switch (name)
			{
			case(1):
				// �����Ńu���b�N�𐶐�����N���Xnew����(�Ă�)
				#pragma region new ClassName(pos, size, tag)
				new class ExampleCreateGround(objectPos, objectSize, Tag::Ground);
				#pragma endregion
				break;
			}
		}
	}
}

// �^�C���f�[�^�ǂݍ���
bool LoadTiledMap::readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc,fileName))
	{
		return false;
	}

	//�J����document��type��map���H
	if (!IsExistMemberAndValue(doc,"type","map"))
	{
		return false;
	}

	//�J����document��layer�͂��邩�H
	if (!IsExistArrayName(doc,"layers"))
	{
		return false;
	}
	//layer�����擾
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer������Y��layer�̓Y�����𒲂ׂ�
	std::string layerNameString(layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", layerName);
		return false;
	}

	//���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//���[�U�[�z��m�ہ@�s�����A������̏��ԂɃT�C�Y�m��
	mapData.resize(height);
	for (auto&mapIter:mapData)
	{
		mapIter.resize(width);
	}

	//���[�U�[�z��i2�����j�Ƀf�[�^���R�s�[
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//�Ȃ���ID��+1����Ă���̂ŕ␳����
			mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

/*
@fn	layerName�̃��C���[���������A���̃C���f�b�N�X�l��Ԃ�
@param �悭�킩���
@param �v�f���������������C���[
@param ���̃��C���[��
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