﻿#ifndef __Game13Layer_H__
#define __Game13Layer_H__

#include "Config.h"

USING_NS_CC;

class Game13Layer : public Layer
{
protected:
    SpriteBatchNode* _blockBatchNode;
    Vector<Sprite*> _blockList;
    std::vector<std::vector<int>> _stage = {
        {1, 1, 0, 1},
        {0, 1, 1, 1},
        {0, 1, 1, 0}
    };

    Sprite* _currentBlock;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game13Layer);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);

    void initDisp();
    bool touchBlock(Vec2 pos);
    void nextBlock(Vec2 pos);
    void drawLine(Vec2 pos1, Vec2 pos2);
    bool nextBlockCheck();

    void backTitleCallback();
};

#endif // __Game13Layer_H__
