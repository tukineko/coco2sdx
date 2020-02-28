#include "Game05Layer.h"
#include "SimpleAudioEngine.h"

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

    //スターウォーズ風
    _text = Sprite::create("text.png");
    _text->setRotation3D(cocos2d::Vertex3F(-80.0, 0.0, 0.0));
    //_text->setPosition(Vec2(winSizeCenterW, 0 - text->getContentSize().height / 2));
    _text->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(_text);
    
    this->scheduleUpdate();

    return true;
}

void Game05Layer::update(float dt) {
   
    _text->setPositionZ(_text->getPositionZ() - _speed);
}

#include "TitleLayer.h"
void Game05Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}