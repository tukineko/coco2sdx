#ifndef __Game05Layer_H__
#define __Game05Layer_H__

#include "Config.h"

USING_NS_CC;

class Game05Layer : public Layer
{
protected:
    Sprite* _text;
    float _speed = 1.0f;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game05Layer);

    

    void backTitleCallback();
};

#endif // __Game05Layer_H__
