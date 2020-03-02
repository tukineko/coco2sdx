#pragma execution_character_set("utf-8")
#include "Game11Layer.h"
#include "SimpleAudioEngine.h"

Scene* Game11Layer::createScene()
{
    Scene* scene = Scene::create();
    Game11Layer* layer = Game11Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game11Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game11Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 130, 50));
    labelItem01->setColor(Color3B::BLUE);
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    this->initDisp();

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game11Layer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game11Layer::initDisp() {
    //ボタンを表示
    _btn01 = Sprite::create("game11/btn01.png");
    _btn01->setPosition(Vec2(winSizeCenterW + 200, 200));
    this->addChild(_btn01);

    _btn02 = Sprite::create("game11/btn02.png");
    _btn02->setPosition(Vec2(winSizeCenterW + 450, 200));
    this->addChild(_btn02);

    //豆を表示
    this->setStage(Node::create());
    for (int i = 0; i < 5; i++) {
        auto mame = Mame::create();
        mame->setMamePosition(Vec2(0, i));
        this->addChild(mame);
        this->addMame(mame);
    }

}

void Game11Layer::addMame(Mame* mame) {
    //豆リストに豆を追加
    _mameList.pushBack(mame);
    //_stageノードに豆を追加
    //_stage->addChild(mame);
    //位置を調整する
    mame->adjustPosition();
    
}

void Game11Layer::ClickBtn01() {
    _btn01_state = true;
    auto ac = Sequence::create(
        EaseElasticOut::create(ScaleTo::create(0.3, 1.1f)),
        ScaleTo::create(0, 1.0f),
        CallFunc::create([&]() {
            _btn01_state = false;
        }),
        nullptr
    );

    _btn01->runAction(ac);
}

//タッチした時に呼び出される関数
bool Game11Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    if (_btn01->getBoundingBox().containsPoint(location) && !_btn01_state) {
        CCLOG("btn01 click");
        this->ClickBtn01();
    }

    return false;
}

#include "TitleLayer.h"
void Game11Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}

/***********************************************
*豆クラス
***********************************************/
//コンストラクター
//作成されるときに起こる処理
//:以降で数値の初期化をすることが出来る
Mame::Mame()
{
}

//デストラクター
//このクラスが終わるときに起こる処理
Mame::~Mame()
{
}

bool Mame::init()
{
    // 乱数発生器の初期化
    std::random_device rdev;
    auto engine = std::mt19937(rdev());
    auto dist = std::uniform_int_distribution<>(0, (int)(Mame::mameType::COUNT) - 1);

    // 豆をランダムに1つ選ぶ
    auto mame = dist(engine);
    _mameType = static_cast<Mame::mameType>(mame);

    if (!Sprite::initWithFile("game11/mame.png", Rect(Mame::getSize() * mame, 0, Mame::getSize(), Mame::getSize()))) return false;

    return true;
}

Vec2 Mame::convertToStageSpace(const Vec2& gridPosition)
{
    return std::move((gridPosition + Vec2::ONE * 0.5) * Mame::getSize());
}

Vec2 Mame::convertToGridSpace(const Vec2& stagePosition)
{
    auto x = floor(stagePosition.x / Mame::getSize());
    auto y = floor(stagePosition.y / Mame::getSize());
    return std::move(Vec2(x, y));
}

void Mame::setMamePosition(const Vec2& position)
{
    _mamePosition = position;
}

void Mame::adjustPosition()
{
    auto position = _mamePosition;
    // _mamePositionを元にpositionを設定する
    this->setPosition(Mame::convertToStageSpace(position));
}