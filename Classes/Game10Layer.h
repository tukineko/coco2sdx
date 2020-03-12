#ifndef __Game10Layer_H__
#define __Game10Layer_H__

#include "Config.h"

USING_NS_CC;

class Game10Layer : public Layer
{
protected:
    Layer* _currentLayer;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game10Layer);

    void effect01();
    void effect02();

    void backTitleCallback();
};

#endif // __Game10Layer_H__
