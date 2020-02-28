#ifndef __Game03Layer_H__
#define __Game03Layer_H__

#include "Config.h"

USING_NS_CC;

enum class kTagList {
    FLOOR = 0,
    BLOCK,
    OUTLINE,
};

class Game03Layer : public Layer
{
protected:
    SpriteBatchNode* _scoreBatchNode;

    int _game_state = 0;
    int _score = 0;
public:
    static Scene* createScene();
    CREATE_FUNC(Game03Layer);
    virtual bool init();

    bool onContactBegin(PhysicsContact& contact);

    void initDisp();
    void viewScore();
    void addObject(Node* parent, Vec2 point);
    void GameOver();

    Sprite* addNewCircleAtPosition(Node* parent, Point p, bool dynamic, const char* fileName);
    Sprite* addNewBoxAtPosition(Node* parent, Point p, bool dynamic, const char* fileName);

    bool onTouchBegan(Touch* touch, Event* event);

    void backTitleCallback();
};

#endif // __Game03Layer_H__
