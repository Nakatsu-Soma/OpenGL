#pragma once
#include"GameObject.h"

// �A�Z�b�g����}�b�v��ǂݍ��ރN���X
class LoadAssetMap : public GameObject
{
public:
	// �R���X�g���N�^
	LoadAssetMap();
	// �f�X�g���N�^
	~LoadAssetMap();

	// Mesh�̍X�V����
	void UpdateGameObject(float _deltaTime)override;

	// Mesh���ǂݍ��߂���
	void LoadMesh(const char* _gpmeshFileName);

private:

	//Mesh�ւ̃|�C���^
	class Mesh* mesh;
	// MeshComponent�ւ̃|�C���^
	class MeshComponent* meshComponent;
};