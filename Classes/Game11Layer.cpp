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

    this->scheduleUpdate();

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game11Layer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game11Layer::update(float dt) {
    // 全豆に対して落下を判定する
    for (auto mame : _mames) {
        this->fallMame(mame);
    }

    this->checkSpawn();
}

void Game11Layer::initDisp() {
    //ボタンを表示
    _btn01 = Sprite::create("game11/btn01.png");
    _btn01->setPosition(Vec2(winSizeCenterW + 200, 200));
    this->addChild(_btn01);

    _btn02 = Sprite::create("game11/btn02.png");
    _btn02->setPosition(Vec2(winSizeCenterW + 450, 200));
    this->addChild(_btn02);

    //ステージノードを作成
    this->setStage(Node::create());
    _stage->setPosition(Vec2(250, 250));
    this->addChild(_stage);

    //豆を表示
    for (int i = 0; i < 5; i++) {
        auto mame = Mame::create();
        mame->setMamePosition(Vec2(0, i));
        this->addMame(mame);
    }
}

void Game11Layer::addMame(Mame* mame) {
    //豆リストに豆を追加
    _mames.pushBack(mame);
    //_stageノードに豆を追加
    _stage->addChild(mame);
    //位置を調整する
    mame->adjustPosition();   
}

void Game11Layer::deleteMame(Mame::mameType mame_type) {
    auto mame = this->getMameAt(Vec2(0, 0));
    if (!mame) return;

    //豆タイプと一致していなかたら何もしない
    if (mame->getMameType() != mame_type) return;

    // 状態を消去中にする
    mame->setState(Mame::State::DISAPEARING);

    if (mame_type == Mame::mameType::OK) {
        // 削除アニメーションを追加する
        mame->runAction(
            Sequence::create(
                FadeOut::create(0.3f),
                CallFuncN::create([this](Node* node) {
            // クッキー一覧から削除する
            auto mame = dynamic_cast<Mame*>(node);
            _mames.eraseObject(mame);
        }),
                RemoveSelf::create(),
            NULL));
    }
    else {
        // 削除アニメーションを追加する
        mame->runAction(
            Sequence::create(
                Spawn::create(
                    MoveBy::create(0.3f, Vec2(300, 0)),
                    FadeOut::create(0.3f),
                    nullptr
                ),
                CallFuncN::create([this](Node* node) {
            // クッキー一覧から削除する
            auto mame = dynamic_cast<Mame*>(node);
            _mames.eraseObject(mame);
        }),
                RemoveSelf::create(),
            NULL));
    }
    
}

Mame* Game11Layer::getMameAt(const Vec2& position){
    for (auto& mame : _mames) {
        if (position.equals(mame->getMamePosition())) {
            return mame;
        }
    }
    return nullptr;
}

bool Game11Layer::fallMame(Mame* mame)
{
    auto position = mame->getMamePosition();
    // すでに一番下にあったときや、停止中じゃないとき、落ちない
    if (position.y == 0 || !mame->isStatic()) {
        return false;
    }
    
    // 1つ下のグリッド座標を取り出す
    auto downPosition = Vec2(position.x, position.y - 1);
    // 1つ下を取り出す
    auto down = this->getMameAt(Vec2(position.x, position.y - 1));
    // 1つ下がなかったとき、落ちる
    if (down == nullptr) {
        // 落下アニメーション時間
        const auto duration = 0.05;
        // 落下距離
        auto distance = -Mame::getSize();
        // 状態を落下中にする
        mame->setState(Mame::State::FALLING);
        // 落下アニメーションの実行
        mame->runAction(Sequence::create(MoveBy::create(duration, Vec2(0, distance)),
            CallFuncN::create([this, downPosition](Node* node) {
            // 落下アニメーション終了後
            auto mame = dynamic_cast<Mame*>(node);
            // 豆を動かす
            this->moveMame(mame, downPosition);
            mame->setState(Mame::State::STATIC);
            // さらに落ちないか再度落下判定を行う
            this->fallMame(mame);
        }),
            NULL));
        return true;
    }
    return false;
}

void Game11Layer::moveMame(Mame* mame, const Vec2& mamePosition)
{
    mame->setMamePosition(mamePosition);
    mame->adjustPosition();
}

Vector<Mame*> Game11Layer::checkSpawn()
{
    // 出現したクッキーの一覧
    Vector<Mame*> mames;
    // 一番上をチェック
    auto mame = this->getMameAt(Vec2(0, 4));
    if (!mame) { // もし豆がなければ
        // 豆を追加する
        auto mame = Mame::create();
        mame->setMamePosition(Vec2(0, 4));
        this->addMame(mame);
    }
    return std::move(mames);
}

void Game11Layer::ClickBtn01() {
    _btn01_state = true;
    auto ac = Sequence::create(
        EaseElasticOut::create(ScaleTo::create(0.3f, 1.1f)),
        ScaleTo::create(0, 1.0f),
        CallFunc::create([&]() {
            _btn01_state = false;
        }),
        nullptr
    );
    _btn01->runAction(ac);
    this->deleteMame(Mame::mameType::NG);
}

void Game11Layer::ClickBtn02() {
    _btn02_state = true;
    auto ac = Sequence::create(
        EaseElasticOut::create(ScaleTo::create(0.3f, 1.1f)),
        ScaleTo::create(0, 1.0f),
        CallFunc::create([&]() {
            _btn02_state = false;
        }),
        nullptr
        );
    _btn02->runAction(ac);
    this->deleteMame(Mame::mameType::OK);
}

//タッチした時に呼び出される関数
bool Game11Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    if (_btn01->getBoundingBox().containsPoint(location) && !_btn01_state) {
        CCLOG("btn01 click");
        this->ClickBtn01();
    }

    if (_btn02->getBoundingBox().containsPoint(location) && !_btn02_state) {
        CCLOG("btn02 click");
        this->ClickBtn02();
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
Mame::Mame():_state(State::STATIC)
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
