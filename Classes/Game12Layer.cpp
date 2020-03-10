#pragma execution_character_set("utf-8")
#include "Game12Layer.h"
#include "SimpleAudioEngine.h"

Scene* Game12Layer::createScene()
{
    Scene* scene = Scene::create();
    Game12Layer* layer = Game12Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game12Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game12Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 130, 50));
    labelItem01->setColor(Color3B::BLUE);
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    //グリッドを引く
    //CommonUtile::drawGrid(this, Color4F::BLUE, 100, 1.0f);

    //ベース
    auto base = Sprite::create("game12/base.png");
    base->setPosition(Vec2(winSizeCenterW, winSizeCenterH - 50));
    this->addChild(base);

    auto base2 = Sprite::create("game12/base2.png");
    base2->setPosition(Vec2(winSizeCenterW, winSizeH - 70));
    this->addChild(base2);

    //間違いのヒットサークル
    auto hit1 = DrawNode::create();
    // 中心座標、半径、角度、頂点数、中心に向かう線を描画するか、倍率x、倍率y
    hit1->drawCircle(Vec2::ZERO, 50, 45, 360, false, 1, 1, Color4F::BLUE);
    hit1->setPosition(Vec2(880, 490));
    this->addChild(hit1);

    auto hit2 = DrawNode::create();
    hit2->drawCircle(Vec2::ZERO, 50, 45, 360, false, 1, 1, Color4F::BLUE);
    hit2->setPosition(Vec2(960, 320));
    this->addChild(hit2);

    auto hit3 = DrawNode::create();
    hit3->drawCircle(Vec2::ZERO, 50, 45, 360, false, 1, 1, Color4F::BLUE);
    hit3->setPosition(Vec2(1100, 300));
    this->addChild(hit3);

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game12Layer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


//タッチした時に呼び出される関数
bool Game12Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    //判定
    this->checkPos(location);


    return false;
}

void Game12Layer::checkPos(Vec2 pos) {
    /*auto check = Sprite::create("game12/check.png");
    check->setPosition(pos);
    this->addChild(check);
    check->runAction(
        Sequence::create(
            FadeOut::create(0.5f),
            FadeIn::create(0.5f),
            FadeOut::create(0.5f),
            FadeIn::create(0.5f),
            CallFunc::create([&]() {
                
            }),
            nullptr
            )
    );*/

    
    float radius = 50.0f;
    if (Vec2(880, 490).getDistance(pos) < radius) {
        CCLOG("hit1");
    }
}



#include "TitleLayer.h"
void Game12Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}

