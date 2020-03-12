#include "Game04Layer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Game04Layer::createScene()
{
    Scene* scene = Scene::create();
    Game04Layer* layer = Game04Layer::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Game04Layer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------Game04Layer::init()----------------");
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game04Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 100, 30));
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    _moveNode = Sprite::create("game04/yubi.png");
    _moveNode->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(_moveNode);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game04Layer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game04Layer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game04Layer::onTouchMoved, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//タッチした時に呼び出される関数
bool Game04Layer::onTouchBegan(Touch* touch, Event* event) {
    auto location = touch->getLocation();

    return true;
}

//タッチを離した時に呼び出される関数  
void Game04Layer::onTouchEnded(Touch* touch, Event* event) {
    

    
}

//タッチしながら移動中に呼び出される関数
void Game04Layer::onTouchMoved(Touch* touch, Event* event) {
    Vec2 location = touch->getLocation();
    Vec2 preLocation = touch->getPreviousLocation();

    auto diff = _moveNode->getPosition() - location;
    auto diff2 = _moveNode->getPosition() - preLocation;
    auto angle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
    auto angle2 = CC_RADIANS_TO_DEGREES(atan2(diff2.x, diff2.y));
    //CCLOG("%f", (angle - angle2));
    _moveNode->setRotation(_moveNode->getRotation() + (angle - angle2));
    CCLOG("%f", _moveNode->getRotation());
}

#include "TitleLayer.h"
void Game04Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}