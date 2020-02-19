#ifndef __Game07Layer_H__
#define __Game07Layer_H__

#include "Config.h"

USING_NS_CC;

class Game07Layer : public Layer
{
private:
    
protected:
    std::vector<int> _cardAry = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
    std::vector<bool> _card_boolAry = { false, false, false, false, false, false, false, false, false, false, false, false };
    Vector<Sprite*> _cards;
    Sprite* _card1;
    int _card1Id;
    bool _isFirst = true;
    bool _isAnime = false;

    const char* getCardImageFileName(int num);
    
public:
    static Scene* createScene();
    CREATE_FUNC(Game07Layer);
    virtual bool init();

    bool onTouchBegan(Touch* touch, Event* event);
    Rect getRect(Node* node);

    void clickCard(int tagId);
    void missAnime();
    bool checkCards();

    void backTitleCallback();

};

#endif // __Game07Layer_H__
