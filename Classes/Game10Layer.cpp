#pragma execution_character_set("utf-8")
#include "Game10Layer.h"
#include "SimpleAudioEngine.h"

Scene* Game10Layer::createScene()
{
    Scene* scene = Scene::create();
    Game10Layer* layer = Game10Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game10Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game10Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 130, 50));
    labelItem01->setColor(Color3B::BLUE);
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    _currentLayer = Layer::create();
    this->addChild(_currentLayer);

    //背景
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    _currentLayer->addChild(bg);

    //メニューボタン（テキスト）
    int fontsize = 36;
    int leftPos = 50;

    auto labelBtnLabel1 = Label::createWithSystemFont("演出1", "Arial", fontsize);
    auto mItem1 = MenuItemLabel::create(labelBtnLabel1, [=](Ref* sender) {
        this->effect01();
    });
    mItem1->setPosition(Vec2(leftPos, winSizeH - 50));
    mItem1->setAnchorPoint(Point::ZERO);
    mItem1->setColor(Color3B::BLUE);

    auto labelBtnLabel2 = Label::createWithSystemFont("演出2", "Arial", fontsize);
    auto mItem2 = MenuItemLabel::create(labelBtnLabel2, [=](Ref* sender) {
        this->effect02();
    });
    mItem2->setPosition(Vec2(leftPos, winSizeH - 100));
    mItem2->setAnchorPoint(Point::ZERO);
    mItem2->setColor(Color3B::BLUE);

    auto menu_text = Menu::create(mItem1, mItem2, NULL);
    menu_text->setPosition(Point::ZERO);
    this->addChild(menu_text, 10);

    return true;
}

void Game10Layer::effect01() {
    //演出
    auto bg = Sprite::create("game10/bg.png");
    bg->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    bg->setScale(2.5f);
    this->addChild(bg, 5);
    auto ac = RepeatForever::create(
        RotateBy::create(10.0f, 360.0f)
    );
    bg->runAction(ac);
}

void Game10Layer::effect02() {
    //スターウォーズ風
    auto sp = Sprite::create("game10/text.png");
    sp->setRotation3D(cocos2d::Vertex3F(-80.0, 0.0, 0.0));
    sp->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(sp);

    
    //_text->setPositionZ(_text->getPositionZ() - _speed);
}

#include "TitleLayer.h"
void Game10Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}