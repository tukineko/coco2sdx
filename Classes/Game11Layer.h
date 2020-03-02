#ifndef __Game11Layer_H__
#define __Game11Layer_H__

#include "Config.h"

USING_NS_CC;

class Mame : public Sprite {
protected:
public:
    enum class mameType {
        OK = 0,
        NG
    };

    Mame();
    ~Mame();
    virtual bool init();
    CREATE_FUNC(Mame);



    CC_SYNTHESIZE_READONLY(mameType, _mameType, MameType);

};

class Game11Layer : public Layer
{
protected:
    Sprite* _btn01;
    bool _btn01_state = false;
    Sprite* _btn02;
    bool _btn02_state = false;

    Vector<Mame*> _mameList;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game11Layer);
    
    void initDisp();
    void addMame();
    void ClickBtn01();
    

    bool onTouchBegan(Touch* touch, Event* event);
    void backTitleCallback();
};

#endif // __Game11Layer_H__
