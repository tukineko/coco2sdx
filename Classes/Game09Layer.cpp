#include "Game09Layer.h"
#include "SimpleAudioEngine.h"
#include <iomanip>

Scene* Game09Layer::createScene()
{
    Scene* scene = Scene::create();
    Game09Layer* layer = Game09Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game09Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------Game09Layer::init()----------------");
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game09Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 130, 50));
    labelItem01->setColor(Color3B::BLUE);
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    //グリッド線
    /*auto render = RenderTexture::create(winSizeW, winSizeH);
    render->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(render, 999);

    render->begin();
    auto line = DrawNode::create();
    line->retain();
    for (int x = 0; x < 10; x++) {
        line->drawSegment(Vec2(100 * x, 0), Vec2(100 * x, winSizeH), 1.0f, Color4F::RED);
        line->Node::visit();
    }
    for (int y = 0; y < 7; y++) {
        line->drawSegment(Vec2(0, 100 * y), Vec2(winSizeW, 100 * y), 1.0f, Color4F::RED);
        line->Node::visit();
    }
    render->end();*/

    //初期状態
    _chara01_state = false;

    //背景
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    this->addChild(bg, 0);

    //ベース確認
    /*auto base = Sprite::create("game09/base.png");
    base->setPosition(Vec2(winSizeCenterW - 300, winSizeCenterH));
    this->addChild(base, 2);*/

    //シルエット背景
    auto base_kage = Sprite::create("game09/base_kage.png");
    base_kage->setPosition(Vec2(winSizeCenterW - 300, winSizeCenterH));
    this->addChild(base_kage, 1);

    //キャラの描写
    _chara01 = Sprite::create("game09/chara01.png");
    _chara01->setPosition(Vec2(winSizeW - 300, winSizeCenterH + 150));
    this->addChild(_chara01, 3, "chara01");

    _chara01_hit = Sprite::create();
    //chara1_hit->setColor(Color3B::BLUE);
    _chara01_hit->setTextureRect(Rect(0, 0, 100, 124));
    _chara01_hit->setPosition(Vec2(215, 375));
    this->addChild(_chara01_hit, 0);

    _chara01_msg = Sprite::create("game09/chara01_msg.png");
    _chara01_msg->setPosition(Vec2(160, 413));
    _chara01_msg->setVisible(false);
    this->addChild(_chara01_msg, 4);


    _chara02 = Sprite::create("game09/chara02.png");
    _chara02->setPosition(Vec2(winSizeW - 300, winSizeCenterH));
    this->addChild(_chara02, 3, "chara02");

    _chara03 = Sprite::create("game09/chara03.png");
    _chara03->setPosition(Vec2(winSizeW - 300, winSizeCenterH - 150));
    this->addChild(_chara03, 3, "chara03");

    this->scheduleUpdate();

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game09Layer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game09Layer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game09Layer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game09Layer::update(float flame) {
    
    

}

//タッチした時に呼び出される関数
bool Game09Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    if (_chara01->getBoundingBox().containsPoint(location) && _chara01_state == false) {
        _currentNode = _chara01;
        CCLOG("touch");
        return true;
    }

    return false;
}

//タッチしながら移動中に呼び出される関数
void Game09Layer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();
    Vec2 preLocation = touch->getPreviousLocation();
    _currentNode->setPosition(Vec2(_currentNode->getPosition().x + location.x - preLocation.x, _currentNode->getPosition().y + location.y - preLocation.y));
}

//タッチを離した時に呼び出される関数  
void Game09Layer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    if (_chara01_hit->getBoundingBox().containsPoint(location)) {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.2f, Vec2(215, 375)),
                nullptr)
        );
        _chara01_msg->setVisible(true);
        _chara01_state = true;
    }
    else {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.6f, Vec2(winSizeW - 300, winSizeCenterH + 150)),
                nullptr)
        );
        _chara01_state = false;
    }
}

#include "TitleLayer.h"
void Game09Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}
