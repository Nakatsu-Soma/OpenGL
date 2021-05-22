#pragma once
#include "GameObject.h"

class SkeletalMeshComponent;

/*
モデルデータを読み込んでアニメーションを行ってくれるクラス
補助クラスで左に移動し続けキーボードのAを押すと右に移動するテストGameObjectクラス
*/
class TestObject :
    public GameObject
{
public:
    TestObject();
    ~TestObject();
    void UpdateGameObject(float _deltaTime)override;
    void GameObjectInput(const InputState& _keyState)override;

private:
    //3Dモデルの描画を行うクラスclass
    SkeletalMeshComponent* skeltalMeshComponent;
};