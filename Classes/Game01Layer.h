#ifndef __Game01Layer_H__
#define __Game01Layer_H__

#include "Config.h"

USING_NS_CC;

enum kBlock {
    kBlockRed,
    kBlockBlue,
    kBlockYellow,
    kBlockGreen
};

enum kStatus {
    kStatusNormal,
    kStatusMarked,
    kStatusSwept
};

class Game01Layer : public Layer
{
protected:
    SpriteBatchNode* _scoreBatchNode;
    int _score = 0;
    int _board[3][3];

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game01Layer);
    
    void initDisp();
    void viewScore();

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    void backTitleCallback();
};

class DropSprite : public Sprite
{
protected:
    const char* getDropImageFileName(kBlock _type);
public:
    CC_SYNTHESIZE(int, tag, Tag);
    CC_SYNTHESIZE(kBlock, type, Type);
    CC_SYNTHESIZE(kStatus, status, Status);

    DropSprite();
    virtual ~DropSprite();
    virtual bool init(int _tag, kBlock _type, kStatus _status);
    static DropSprite* create(int _tag, kBlock _type, kStatus _status);
};

#endif // __Game01Layer_H__
