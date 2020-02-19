#include "Game01Layer.h"
#include "SimpleAudioEngine.h"
#include <iomanip>

Scene* Game01Layer::createScene()
{
    Scene* scene = Scene::create();
    Game01Layer* layer = Game01Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game01Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------Game01Layer::init()----------------");
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game01Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 130, 50));
    labelItem01->setColor(Color3B::BLUE);
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    //スコア画像はBatchNodeで処理
    _scoreBatchNode = SpriteBatchNode::create("number.png");
    this->addChild(_scoreBatchNode);

    //背景
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    this->addChild(bg, 0);

    //初期表示
    this->initDisp();

    //スコア表示
    this->viewScore();


    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game01Layer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game01Layer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game01Layer::initDisp() {
    /*for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            kBlock blockType = (kBlock)(rand() % 4);
            DropSprite* block = DropSprite::create(10000, blockType, kStatusNormal);
            block->setPosition(Vec2(200 + x * 150, 200 + y * 150));
            this->addChild(block, 0, 10000);


        }
    }*/
}

void Game01Layer::viewScore() {
    //scoreの名前がついているノードをすべて削除
    this->enumerateChildren("score", [](Node* node) -> bool {
        auto action = RemoveSelf::create();
        node->runAction(action);
        return false;
        });
    
    //文字列に変換、10桁0で埋める
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(10) << _score;
    std::string score = oss.str().c_str();
    int lang = score.length();
    int numberRect = 64;

    for (int i = 0; i < lang; i++) {
        auto number = Sprite::createWithTexture(_scoreBatchNode->getTexture(), Rect(0, 0, numberRect, numberRect));
        number->setPosition(Vec2((winSizeCenterW - 300) + numberRect * i, winSizeH - 100));
        char c = score[i];
        int num = c - '0';
        number->setTextureRect(Rect(numberRect * num, 0, numberRect, numberRect));
        this->addChild(number, 10, "score");
    }
}

//タッチした時に呼び出される関数
bool Game01Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    _score++;
    this->viewScore();

    return true;
}

//タッチを離した時に呼び出される関数  
void Game01Layer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto location = touch->getLocation();
}

#include "TitleLayer.h"
void Game01Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}

DropSprite::DropSprite()
{
}

DropSprite::~DropSprite()
{
}

DropSprite* DropSprite::create(int _tag, kBlock _type, kStatus _status)
{
    DropSprite* pRet = new DropSprite();

    if (pRet && pRet->init(_tag, _type, _status))
    {
        return pRet;

    }
    else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool DropSprite::init(int _tag, kBlock _type, kStatus _status)
{
    if (!Sprite::initWithFile(getDropImageFileName(_type)))
    {
        return false;
    }

    tag = _tag;
    type = _type;
    status = _status;

    return true;
}

const char* DropSprite::getDropImageFileName(kBlock _type)
{
    switch (_type) {
    case kBlockRed:
        return "puzzle1.png";

    case kBlockBlue:
        return "puzzle2.png";

    case kBlockYellow:
        return "puzzle4.png";

    case kBlockGreen:
        return "puzzle3.png";

    default:
        return "";
    }
}