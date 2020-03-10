#ifndef __TitleLayer_H__
#define __TitleLayer_H__

#include "Config.h"

USING_NS_CC;

class TitleLayer : public Layer
{
protected:
    Sprite* _chara;
    float _count = 0;
    float _px = 2.5f;
    float _py = 0;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TitleLayer);

    void nextSceneCallback();
    void nextSceneCallback2();
    void nextSceneCallback3();
    void nextSceneCallback4();
    void nextSceneCallback5();
    void nextSceneCallback6();
    void nextSceneCallback7();
    void nextSceneCallback8();
    void nextSceneCallback9();
    void nextSceneCallback10();
    void nextSceneCallback11();
    void nextSceneCallback12();

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);

    void update(float dt);

    void ChangeCharaDirection();
};

#endif // __TitleLayer_H__
