#include "LoadAssetMap.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"

// �R���X�g���N�^
LoadAssetMap::LoadAssetMap()
	// mesh����
	: mesh(new Mesh())
	// meshComponent����
	, meshComponent(new MeshComponent(this))
{
	printf("LoadAssetMap �R���X�g���N�^\n");
}

// �f�X�g���N�^
LoadAssetMap::~LoadAssetMap()
{
	printf("LoadAssetMap �f�X�g���N�^\n");
}

// Mesh�̍X�V����
void LoadAssetMap::UpdateGameObject(float _deltaTime)
{

}

// Mesh��ǂݍ��߂���
void LoadAssetMap::LoadMesh(const char* _gpmeshFileName)
{
	// �A�Z�b�g�̃��b�V�����擾
	mesh = RENDERER->GetMesh(_gpmeshFileName);

	// Mesh��ǂݍ��߂���
	if (!mesh)
	{
		// ���O�\��
		printf("Mesh�ǂݍ��ݎ��s : %s\n", _gpmeshFileName);
		return;
	}

	// ���O�\��
	printf("Mesh�ǂݍ��ݐ��� : %s\n", _gpmeshFileName);

	// MeshCompornent��Mesh���Z�b�g(�����ŕ`�揈���͏I���)
	meshComponent->SetMesh(mesh);

	//Z����90�x��]������
	float radian = Math::ToRadians(90);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	//X����-90�x��]������
	radian = Math::ToRadians(-90);
	rot = this->GetRotation();
	inc = Quaternion(Vector3::UnitX, radian);
	target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}