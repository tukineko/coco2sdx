#include "Game09Layer.h"
#include "SimpleAudioEngine.h"

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

    //背景
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    this->addChild(bg, 0);

    //シルエット背景
    auto base_kage = Sprite::create("game09/base_kage.png");
    base_kage->setPosition(Vec2(winSizeCenterW - 300, winSizeCenterH));
    this->addChild(base_kage, 1);

    //キャラ1の描写
    _chara01 = Chara::create(kChara::CHARA01);
    _chara01->setPosition(Vec2(winSizeW - 300, winSizeCenterH + 150));
    this->addChild(_chara01, 3, 1);

    //キャラ1の当たり判定
    _chara01_hit = Sprite::create();
    _chara01_hit->setOpacity(0);
    _chara01_hit->setTextureRect(Rect(0, 0, 100, 124));
    _chara01_hit->setPosition(Vec2(215, 375));
    this->addChild(_chara01_hit, 2);

    //キャラ1のセリフ
    _chara01_msg = Sprite::create("game09/chara01_msg.png");
    _chara01_msg->setPosition(Vec2(160, 413));
    _chara01_msg->setVisible(false);
    this->addChild(_chara01_msg, 4);

    //キャラ2の描画
    _chara02 = Chara::create(kChara::CHARA02);
    _chara02->setPosition(Vec2(winSizeW - 300, winSizeCenterH));
    this->addChild(_chara02, 3, 2);
    //キャラ2の当たり判定
    _chara02_hit = Sprite::create();
    _chara02_hit->setOpacity(0);
    //_chara02_hit->setColor(Color3B::BLUE);
    _chara02_hit->setTextureRect(Rect(0, 0, 94, 124));
    _chara02_hit->setPosition(Vec2(353, 378));
    this->addChild(_chara02_hit, 2);
    //キャラ2のセリフ
    _chara02_msg = Sprite::create("game09/chara02_msg.png");
    _chara02_msg->setPosition(Vec2(430, 413));
    _chara02_msg->setVisible(false);
    this->addChild(_chara02_msg, 4);

    //キャラ3の描画
    _chara03 = Chara::create(kChara::CHARA03);
    _chara03->setPosition(Vec2(winSizeW - 300, winSizeCenterH - 150));
    this->addChild(_chara03, 3, 3);
    //キャラ3の当たり判定
    _chara03_hit = Sprite::create();
    _chara03_hit->setOpacity(0);
    //_chara03_hit->setColor(Color3B::BLUE);
    _chara03_hit->setTextureRect(Rect(0, 0, 114, 124));
    _chara03_hit->setPosition(Vec2(575, 378));
    this->addChild(_chara03_hit, 2);
    //キャラ3のセリフ
    _chara03_msg = Sprite::create("game09/chara03_msg.png");
    _chara03_msg->setPosition(Vec2(510, 413));
    _chara03_msg->setVisible(false);
    this->addChild(_chara03_msg, 4);

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game09Layer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game09Layer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game09Layer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//タッチした時に呼び出される関数
bool Game09Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    if (_chara01->getBoundingBox().containsPoint(location) && _chara01->getState() == false) {
        _currentNode = _chara01;
        CCLOG("touch");
        return true;
    }

    if (_chara02->getBoundingBox().containsPoint(location) && _chara02->getState() == false) {
        _currentNode = _chara02;
        return true;
    }

    if (_chara03->getBoundingBox().containsPoint(location) && _chara03->getState() == false) {
        _currentNode = _chara03;
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

    if (_chara01_hit->getBoundingBox().containsPoint(location) && _currentNode->getTag() == 1) {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.2f, Vec2(215, 375)),
                nullptr)
        );
        _chara01_msg->setVisible(true);
        _chara01->setState(true);
    }
    else if(_currentNode->getTag() == 1) {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.6f, Vec2(winSizeW - 300, winSizeCenterH + 150)),
                nullptr)
        );
        _chara01->setState(false);
    }

    if (_chara02_hit->getBoundingBox().containsPoint(location) && _currentNode->getTag() == 2) {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.2f, Vec2(357, 380)),
                nullptr)
        );
        _chara02_msg->setVisible(true);
        _chara02->setState(true);
    }
    else if(_currentNode->getTag() == 2) {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.6f, Vec2(winSizeW - 300, winSizeCenterH)),
                nullptr)
        );
        _chara02->setState(false);
    }

    if (_chara03_hit->getBoundingBox().containsPoint(location) && _currentNode->getTag() == 3) {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.2f, Vec2(560, 373)),
                nullptr)
        );
        _chara03_msg->setVisible(true);
        _chara03->setState(true);
    }
    else if (_currentNode->getTag() == 3) {
        _currentNode->runAction(
            Sequence::create(
                MoveTo::create(0.6f, Vec2(winSizeW - 300, winSizeCenterH - 150)),
                nullptr)
        );
        _chara03->setState(false);
    }
}

#include "TitleLayer.h"
void Game09Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}

/***********************************************
*キャラクタークラス
***********************************************/
//コンストラクター
//作成されるときに起こる処理
//:以降で数値の初期化をすることが出来る
Chara::Chara()
{
}

//デストラクター
//このクラスが終わるときに起こる処理
Chara::~Chara()
{
}

Chara* Chara::create(kChara _type)
{
    Chara* ret = new Chara();

    if (ret && ret->init(_type))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool Chara::init(kChara _type)
{
    if (!Sprite::initWithFile(getImageFileName(_type))) return false;

    state = false;

    return true;
}

const char* Chara::getImageFileName(kChara _type)
{
    switch (_type) {
    case kChara::CHARA01:
        return "game09/chara01.png";

    case kChara::CHARA02:
        return "game09/chara02.png";

    case kChara::CHARA03:
        return "game09/chara03.png";

    default:
        return "";
    }
}
