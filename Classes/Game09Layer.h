#ifndef __Game09Layer_H__
#define __Game09Layer_H__

#include "Config.h"

USING_NS_CC;

enum class kChara {
    CHARA01 = 0,
    CHARA02,
    CHARA03,
};

class Chara : public Sprite
{
protected:
    //タイプによって読み込む画像を変更
    const char* getImageFileName(kChara _type);
    
public:
    CC_SYNTHESIZE(bool, state, State);

    Chara();
    ~Chara();
    virtual bool init(kChara _type);
    static Chara* create(kChara _type);
};

class Game09Layer : public Layer
{
protected:
    Chara* _chara01;
    Sprite* _chara01_hit;
    Sprite* _chara01_msg;
    Chara* _chara02;
    Sprite* _chara02_hit;
    Sprite* _chara02_msg;
    Chara* _chara03;
    Sprite* _chara03_hit;
    Sprite* _chara03_msg;
    Node* _currentNode;

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
