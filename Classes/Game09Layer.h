#ifndef __Game09Layer_H__
#define __Game09Layer_H__

#include "Config.h"

USING_NS_CC;

class Game09Layer : public Layer
{
protected:
    Sprite* _chara01;
    Sprite* _chara01_hit;
    Sprite* _chara01_msg;
    Sprite* _chara02;
    Sprite* _chara03;
    Node* _currentNode;

    bool _chara01_state;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game09Layer);
    
    
    void update(float frame);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    void backTitleCallback();
};

#endif // __Game09Layer_H__
