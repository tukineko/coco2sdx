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

    
    //ゲージ
    _gauge = Sprite::create("game05/gauge.png");
    _gauge->setPosition(Vec2(winSizeCenterW, 100));
    _gauge->setAnchorPoint(Point::ZERO);
    this->addChild(_gauge);
    
    _text = Label::createWithSystemFont("aaa", "Arial", 48);
    _text->setPosition(Vec2(300, 200));
    this->addChild(_text);

    this->scheduleUpdate();
    
    return true;
}

void Game05Layer::update(float dt) {
    _text->setString(std::to_string(_gaugeCnt));


    if (65 <= _gaugeCnt) {
        _gaugeSpeed = 2.0;
    }
    else if (30 <= _gaugeCnt && _gaugeCnt < 65) {
        _gaugeSpeed = 1.0;
    }
    else {
        _gaugeSpeed = 0.5;
    }

    if (_gaugeCnt <= 0 || 100 <= _gaugeCnt) {
        _gaugeCntM *= -1;
    }
    _gaugeCnt += _gaugeCntM * _gaugeSpeed;
    CCLOG("_gaugeCnt:%f", _gaugeCnt);


    viewGauge();
}

void Game05Layer::viewGauge() {
    _gauge->setTextureRect(Rect(0, 500 - (500 * _gaugeCnt / 100), _gauge->getContentSize().width, 500 * _gaugeCnt / 100));

}

#include "TitleLayer.h"
void Game05Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}