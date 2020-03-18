#ifndef __Game05Layer_H__
#define __Game05Layer_H__

#include "Config.h"

USING_NS_CC;

class Game05Layer : public Layer
{
protected:
    enum class mainZOderList {
        BG = 0,
        GAUGE,
        TEXT,
    };

    enum class GameState {
        DEFAULT = 0,
        GAME,
        RESULT,
    };
    
    enum class GaugeState {
        STOP = 0,
        MOVING
    };

    GameState _game_state;
    Sprite* _gauge;
    float _gaugeCnt = 0;
    float _gaugeTime = 0;
    GaugeState _gaugeState;

    Sprite* _tapstart;

    Label* _text;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game05Layer);
    bool onTouchBegan(Touch* touch, Event* event);
    void update(float dt);
    
    void TapStart();
    void TapStop();
    void viewGauge();
    float GaugeCalc(float t);
    void TapAnime(float dt);

    void backTitleCallback();
};

#endif // __Game05Layer_H__
