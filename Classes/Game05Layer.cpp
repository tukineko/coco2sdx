#pragma execution_character_set("utf-8")
#include "Game05Layer.h"
#include "SimpleAudioEngine.h"

#define PI 3.14159265358979323846

USING_NS_CC;

Scene* Game05Layer::createScene()
{
    Scene* scene = Scene::create();
    Game05Layer* layer = Game05Layer::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Game05Layer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------Game05Layer::init()----------------");
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game05Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 100, 30));
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    //初期化
    _game_state = GameState::DEFAULT;
    _gaugeState = GaugeState::STOP;
    
    //スコア画像はBatchNodeで処理
    _pointBatchNode = SpriteBatchNode::create("common/number.png");
    this->addChild(_pointBatchNode);

    //ゲージ
    auto gauge_bg = Sprite::create("game05/gauge_bg.png");
    gauge_bg->setPosition(Vec2(winSizeCenterW - 50 - 16, 150 - 15));
    gauge_bg->setAnchorPoint(Point::ZERO);
    this->addChild(gauge_bg, (int)mainZOderList::GAUGE);
    _gauge = Sprite::create("game05/gauge.png");
    _gauge->setPosition(Vec2(winSizeCenterW - 50, 150));
    _gauge->setAnchorPoint(Point::ZERO);
    this->addChild(_gauge, (int)mainZOderList::GAUGE);
    this->viewGauge();
    
    //タップでスタート
    _tapstart = Sprite::create("game05/tapstart.png");
    _tapstart->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(_tapstart, (int)mainZOderList::TEXT);
    _tapstart->runAction(
        RepeatForever::create(
            Sequence::create(
                DelayTime::create(0.4f),
                FadeOut::create(0.2f),
                FadeIn::create(0.2f),
                nullptr
            )
        )
    );

    //ポイント表示
    _textPoint = Label::createWithSystemFont("", "Arial", 300);
    _textPoint->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    _textPoint->setColor(Color3B(0, 0, 255));
    _textPoint->enableOutline(Color4B::WHITE, 20);
    _textPoint->setVisible(false);
    this->addChild(_textPoint, (int)mainZOderList::POINT);

    //デバック用ゲージ
    _text = Label::createWithSystemFont("デバック用ゲージ数値", "Arial", 48);
    _text->setPosition(Vec2(250, winSizeH - 100));
    this->addChild(_text, (int)mainZOderList::TEXT);

    this->scheduleUpdate();
    
    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game05Layer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//タッチした時に呼び出される関数
bool Game05Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    if (_gaugeState == GaugeState::STOP && _game_state == GameState::DEFAULT) {
        this->TapStart();
    }
    else if(_gaugeState == GaugeState::MOVING && _game_state == GameState::GAME) {
        this->TapStop();
    }
    else if (_game_state == GameState::RESULT) {
        this->TapReset();
    }
    

    return false;
}

void Game05Layer::update(float dt) {

    _gaugeTime += dt;
    
    if (_gaugeState == GaugeState::MOVING) {
        //_gaugeCnt = this->GaugeCalc(_gaugeTime);
        this->GaugeCalc2(_gaugeTime);
        _text->setString(std::to_string(_gaugeCnt));
        //CCLOG("%f", _gaugeCnt);
        this->viewGauge();
    }
}

void Game05Layer::viewGauge() {
    _gauge->setTextureRect(Rect(0, 500 - (500 * (int)std::round(_gaugeCnt) / 100), _gauge->getContentSize().width, 500 * (int)std::round(_gaugeCnt) / 100));

}

float Game05Layer::GaugeCalc(float t) {
    return (-0.5 * (cos(PI * t) - 1)) * 100;
}

void Game05Layer::GaugeCalc2(float t) {    
    //CCLOG("%f", -100 * (cos(PI * t) - 100));

    /*float calc;
    if (_gaugeCnt >= 80) {
        calc = 5;
    }
    else if (35 < _gaugeCnt && _gaugeCnt < 80) {
        calc = 4;
    }
    else {
        calc = 3;
    }

    if (_gaugePlus) {
        _gaugeCnt += calc;
        if (_gaugeCnt >= 100) {
            _gaugeCnt = 100;
            _gaugePlus = false;
        }
    }
    else {
        _gaugeCnt -= calc;
        if (_gaugeCnt <= 0) {
            _gaugeCnt = 0;
            _gaugePlus = true; 
        }
    }*/

    //_gaugeCnt = (0.5 * (1 + sin(PI * (t - 0.5)))) * 100;
    //_gaugeCnt = 1 - sqrt(1 - t);
    //_gaugeCnt = t * t;

    //CCLOG("%f", (cos(PI * t) - 1));

    CCLOG("%f", t);
    _gaugeCnt = t * t * t;
    //CCLOG("%f", _gaugeCnt);
    
        
}

void Game05Layer::TapStart()
{
    _tapstart->setVisible(false);
    _gaugeTime = 0;
    _gaugeCnt = 0;
    _gaugeState = GaugeState::MOVING;
    _game_state = GameState::GAME;

    //タイミングよくタップしてね
    auto tap = Sprite::create("game05/tap.png");
    tap->setPosition(Vec2(winSizeCenterW, 70));
    this->addChild(tap, (int)mainZOderList::TEXT, "tap");
    tap->runAction(
        RepeatForever::create(
            Sequence::create(
                DelayTime::create(0.4f),
                FadeOut::create(0.2f),
                FadeIn::create(0.2f),
                nullptr
            )
        )
    );
}

void Game05Layer::TapStop() {
    _gaugeState = GaugeState::STOP;
    _game_state = GameState::RESULT;
    this->removeChildByName("tap");
    _calcPoint = _gaugeCnt / 10;
    _startPoint = 0;
    _endPoint = _gaugeCnt;
    _textPoint->setVisible(true);
    this->schedule(schedule_selector(Game05Layer::PointAnime), 0.05, 10, 0);
}

void Game05Layer::TapReset() {
    _game_state = GameState::DEFAULT;
    _gaugeCnt = 0;
    _textPoint->setVisible(false);
    _tapstart->setVisible(true);
    this->viewGauge();
    
}

void Game05Layer::PointAnime(float dt) {

    _startPoint += _calcPoint;
    if (_endPoint < _startPoint) {
        _startPoint = _endPoint;
    }

    GLubyte r = 0;
    GLubyte g = 0;
    GLubyte b = 0;
    if (_startPoint < 12.5) {
        r = 0;
        g = 0;
        b = 255;
    }else if(12.5 <= _startPoint && _startPoint < 37.5) {
        r = 0;
        g = 255;
        b = 255;
    }else if(37.5 <= _startPoint && _startPoint < 62.5) {
        r = 0;
        g = 255;
        b = 0;
    }else if (62.5 <= _startPoint && _startPoint < 87.5) {
        r = 255;
        g = 255;
        b = 0;
    }else{
        r = 255;
        g = 0;
        b = 0;
    }

    _textPoint->setColor(Color3B(r, g, b));
    _textPoint->setString(std::to_string((int)std::round(_startPoint)));

    //scoreの名前がついているノードをすべて削除
    /*this->enumerateChildren("point", [](Node* node) -> bool {
        auto action = RemoveSelf::create();
        node->runAction(action);
        return false;
    });

    std::string score = std::to_string((int)_startPoint);

    int lang = score.length();
    int numberRect = 64;

    for (int i = 0; i < lang; i++) {
        auto number = Sprite::createWithTexture(_pointBatchNode->getTexture(), Rect(0, 0, numberRect, numberRect));
        number->setPosition(Vec2((winSizeCenterW - 300) + numberRect * i, winSizeCenterH - 50));
        char c = score[i];
        int num = c - '0';
        number->setTextureRect(Rect(numberRect * num, 0, numberRect, numberRect));
        this->addChild(number, (int)mainZOderList::SCORE, "point");
    }*/

}

#include "TitleLayer.h"
void Game05Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}