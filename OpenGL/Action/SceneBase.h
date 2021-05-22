#ifndef __SCENE_H__
#define __SCENE_H__

#include "game.h"

// SceneBase�N���X
class SceneBase
{
public:
	SceneBase() {};
	virtual      ~SceneBase() {};

	virtual       SceneBase* update() = 0;    // �V�[���̍X�V�����i�I�[�o�[���C�h�K�{�j
	virtual void  draw() = 0;                  // �V�[���̕`�揈���i�I�[�o�[���C�h�K�{�j
};
#endif

#pragma region ifndef~endif�Ƃ�
/*
����͍Ē�`��h�����́B
���� �u__SCENE_H__�v�͋L���萔�ƌ����A���ꂪ��`����Ă��邩�ɂ����
�d����`�̔��ʂ�����B#define�͋L���萔���`���Ă���B
�Q�ƁFhttps://programgenjin.hatenablog.com/entry/2019/02/22/210141
*/
#pragma endregion