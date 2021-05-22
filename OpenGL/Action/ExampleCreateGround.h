#pragma once
#include "GameObject.h"

// LoadTiledMap���瓾����������Ground�𐶐�����GameObject�N���X
class ExampleCreateGround : public GameObject
{
public:
	// �R���X�g���N�^
	ExampleCreateGround(Vector3 _objectpos, Vector3 objectSize, Tag _Tag);
	// �f�X�g���N�^
	~ExampleCreateGround();

	// �I�u�W�F�N�g�̍X�V����
	void UpdateGameObject(float _deltaTime)override;

private:

	Vector3 pos;
	//Mesh�ւ̃|�C���^
	class Mesh* mesh;
	// MeshComponent�ւ̃|�C���^
	class MeshComponent* meshComponent;
	// BoxCollider�ւ̃|�C���^
	class BoxCollider* boxCollider;

	// �����蔻�菈��
	void OnCollision(const GameObject& _hitObject);
};