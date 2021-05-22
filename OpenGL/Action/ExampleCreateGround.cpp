#include "ExampleCreateGround.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "ColliderComponent.h"

ExampleCreateGround::ExampleCreateGround(Vector3 _objectPos, Vector3 _objectSize, Tag _Tag)
	// mesh����
	:mesh(new Mesh())
	// meshComponent����
	, meshComponent(new MeshComponent(this))
	// boxCollider����
	, boxCollider(new BoxCollider(this, ColliderComponent::PhysicsTag::GroundTag, GetOnCollisionFunc()))
{
	// Ground��tag��ݒ�
	tag = _Tag;
	// Ground�̑傫����ݒ�
	SetScale(_objectSize);
	// Ground�̈ʒu��ݒ�
	SetPosition(_objectPos);

	// �}�b�v��gpmesh�ǂݍ���
	mesh = RENDERER->GetMesh("Assets/MapBlock/Block.gpmesh");
	// ���O�\��
	printf("Block��gpmesh�ǂݍ��ݐ���");
	// meshComponent�ɃZ�b�g(�����ŕ`�揈���͏I���)
	meshComponent->SetMesh(mesh);

	// ���b�V���̑傫���擾
	AABB groundBox = mesh->GetAABB();
	// PhysicsWorld��Box��ǉ��������蔻��𔽉f
	boxCollider->SetObjectBox(groundBox);

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

	printf("CreateGround �R���X�g���N�^\n");
}

ExampleCreateGround::~ExampleCreateGround()
{
	printf("CreateGround �f�X�g���N�^\n");
}

// �I�u�W�F�N�g�̍X�V����
void ExampleCreateGround::UpdateGameObject(float _deltaTime)
{

}

// �����蔻�菈��
void ExampleCreateGround::OnCollision(const GameObject& _hitObject)
{
}
