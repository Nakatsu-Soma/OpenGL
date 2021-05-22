#ifndef __SCENE_H__
#define __SCENE_H__

#include "game.h"

// SceneBaseクラス
class SceneBase
{
public:
	SceneBase() {};
	virtual      ~SceneBase() {};

	virtual       SceneBase* update() = 0;    // シーンの更新処理（オーバーライド必須）
	virtual void  draw() = 0;                  // シーンの描画処理（オーバーライド必須）
};
#endif

#pragma region ifndef~endifとは
/*
これは再定義を防ぐもの。
後ろの 「__SCENE_H__」は記号定数と言い、これが定義されているかによって
重複定義の判別をする。#defineは記号定数を定義している。
参照：https://programgenjin.hatenablog.com/entry/2019/02/22/210141
*/
#pragma endregion