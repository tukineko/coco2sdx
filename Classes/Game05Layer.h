#ifndef __Game05Layer_H__
#define __Game05Layer_H__

#include "Config.h"

USING_NS_CC;

class Game05Layer : public Layer
{
protected:
    Sprite* _gauge;
    float _gaugeCnt = 1;
    float _gaugeCntM = 1;
    float _gaugeSpeed = 0.5;
    float _py = 0;

    Label* _text;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game05Layer);
    void update(float dt);
    
    void viewGauge();

    void backTitleCallback();
};

#endif // __Game05Layer_H__
