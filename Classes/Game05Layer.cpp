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
    

    return false;
}

void Game05Layer::update(float dt) {

    _gaugeTime += dt;
    
    if (_gaugeState == GaugeState::MOVING) {
        _gaugeCnt = this->GaugeCalc(_gaugeTime);
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
    this->removeChildByName("tap");
    this->scheduleOnce(schedule_selector(Game05Layer::TapAnime), 0);
}

void Game05Layer::TapAnime(float dt) {
    //CCLOG("%f", dt);


    float elapsedTime = 0.0f;
    float time = 10.0f;
    while (elapsedTime < time)
    {
        float rate = elapsedTime / time;
        CCLOG("%f", _gaugeCnt * rate);
        // テキストの更新
        //scoreText.text = (befor + (after - befor) * rate).ToString("f0");

        elapsedTime += dt;
        // 0.01秒待つ
        //yield return new WaitForSeconds(0.01f);
    }
}

#include "TitleLayer.h"
void Game05Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}