#ifndef __Game12Layer_H__
#define __Game12Layer_H__

#include "Config.h"

USING_NS_CC;

class Game12Layer : public Layer
{
protected:
    
    bool _hit1Flag = false;
    bool _hit2Flag = false;
    bool _hit3Flag = false;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game12Layer);
    bool onTouchBegan(Touch* touch, Event* event);

    void checkPos(Vec2 pos);

    void backTitleCallback();
};

#endif // __Game12Layer_H__
