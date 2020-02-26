#ifndef __Game08Layer_H__
#define __Game08Layer_H__

#include "Config.h"

USING_NS_CC;

class Game08Layer : public Layer
{
protected:
    SpriteBatchNode* _scoreBatchNode;
    int _score = 0;
    Sprite* _player;
    Sprite* _btnL;
    Sprite* _btnR;
    bool _isPlayerMove = false;
    int _isPlayerMuki = 0; //0は左向き
    
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game08Layer);
    
    void initDisp();
    void viewScore();
    void drawPlayer();
    Rect getRect(Node* node);

    void update(float frame);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    void backTitleCallback();
};

#endif // __Game08Layer_H__
