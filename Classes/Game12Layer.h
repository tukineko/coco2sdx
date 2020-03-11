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

    bool _moving = false;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game12Layer);
    bool onTouchBegan(Touch* touch, Event* event);

    void TouchAnime(Vec2 pos);
    void Check(Vec2 pos);
    void hitOn(Vec2 pos);
    void doAnimeOK();
    void doAnimeMiss();
    

    void backTitleCallback();
};

#endif // __Game12Layer_H__
