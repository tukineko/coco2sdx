#include "Game03Layer.h"
#include "SimpleAudioEngine.h"
#include <iomanip>

USING_NS_CC;

enum class mainZOderList {
    BG = 0,
    BOX,
    FLOOR,
    GAMEOVER,
    SCORE,
    MENU,
};

Scene* Game03Layer::createScene()
{
    auto scene = Scene::createWithPhysics();  //物理エンジンのシーンの作成
    auto layer = Game03Layer::create();
    scene->addChild(layer);

    //gravityを変更（現実の場合0,-980）
    PhysicsWorld* world = scene->getPhysicsWorld();
    world->setGravity(Vec2(0, -980));

    return scene;
}


// on "init" you need to initialize your instance
bool Game03Layer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game03Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 100, 30));
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, (int)mainZOderList::MENU);

    //スコア画像はBatchNodeで処理
    _scoreBatchNode = SpriteBatchNode::create("number.png");
    this->addChild(_scoreBatchNode);

    // 物理衝突リスナー
    auto phlistener = EventListenerPhysicsContact::create();
    phlistener->onContactBegin = CC_CALLBACK_1(Game03Layer::onContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(phlistener, this);

    //初期表示
    this->initDisp();

    //タッチイベント
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game03Layer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game03Layer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game03Layer::onTouchMoved, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game03Layer::initDisp()
{
    //ボックス
    /*auto boxL = Sprite::create();
    boxL->setTextureRect(Rect(0, 0, 30, 400));
    boxL->setPhysicsBody(PhysicsBody::createBox(boxL->getContentSize()));
    boxL->getPhysicsBody()->setDynamic(false);
    boxL->setPosition(Vec2(winSizeCenterW - 400, 300));
    this->addChild(boxL, (int)mainZOderList::BOX);*/

    auto boxB = Sprite::create();
    boxB->setTextureRect(Rect(0, 0, 800, 30));
    auto pboxB = PhysicsBody::createBox(boxB->getContentSize());
    boxB->setPhysicsBody(pboxB);
    boxB->getPhysicsBody()->setDynamic(false);
    boxB->setPosition(Vec2(winSizeCenterW, 100));
    this->addChild(boxB, (int)mainZOderList::BOX);

    /*auto boxR = Sprite::create();
    boxR->setTextureRect(Rect(0, 0, 30, 400));
    boxR->setPhysicsBody(PhysicsBody::createBox(boxR->getContentSize()));
    boxR->getPhysicsBody()->setDynamic(false);
    boxR->setPosition(Vec2(winSizeCenterW + 400, 300));
    this->addChild(boxR, (int)mainZOderList::BOX);*/

    //画面外の地面
    auto floor = Sprite::create();
    floor->setTextureRect(Rect(0, 0, winSizeW, 30));
    auto floor_body = PhysicsBody::createBox(floor->getContentSize());
    floor_body->setContactTestBitmask(1);
    floor->setPhysicsBody(floor_body);
    floor->getPhysicsBody()->setDynamic(false);
    floor->setPosition(Vec2(winSizeCenterW, -100));
    this->addChild(floor, (int)mainZOderList::BOX, (int)kTagList::OUTLINE);

    //スコア表示
    this->viewScore();

}

//オブジェクトを落とす
void Game03Layer::addObject(Node* parent, Vec2 point) {
    auto sprite = Sprite::create("btnOn.png");
    auto body = PhysicsBody::createBox(sprite->getContentSize());
    body->setContactTestBitmask(1);
    sprite->setPhysicsBody(body);
    sprite->getPhysicsBody()->setDynamic(true);
    sprite->setPosition(point);
    this->addChild(sprite, (int)mainZOderList::BOX, (int)kTagList::BLOCK);
}

bool Game03Layer::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    log("Tags nodeA: %d, nodeB: %d", nodeA->getTag(), nodeB->getTag());
    if (_game_state == 0) {
        // 画面外とブロックがあたったとき
        if (2 == nodeA->getTag() || 2 == nodeB->getTag()) {
            this->GameOver();
            return false;
        }
    }

    return true;
}

void Game03Layer::GameOver() {
    _game_state = 1;
    auto gameover = Sprite::create("txt_gameover.png");
    gameover->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(gameover, (int)mainZOderList::GAMEOVER);

    // 作成したパーティクルのプロパティリストを読み込み
    auto particle = ParticleSystemQuad::create("particle_texture/explosion01.plist");
    particle->resetSystem();
    particle->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    particle->setAutoRemoveOnFinish(true);
    this->addChild(particle, (int)mainZOderList::GAMEOVER);
}

//スコアを表示する
void Game03Layer::viewScore() {
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
        number->setPosition(Vec2((winSizeCenterW - 300) + numberRect * i, winSizeH - 50));
        char c = score[i];
        int num = c - '0';
        number->setTextureRect(Rect(numberRect * num, 0, numberRect, numberRect));
        this->addChild(number, (int)mainZOderList::SCORE, "score");
    }
}

// 丸(物理エンジン)を作成
Sprite* Game03Layer::addNewCircleAtPosition(Node* parent, Point p, bool dynamic, const char* fileName) {
    CCLOG("-------addNewCircleAtPosition--------");
    Sprite* sprite = Sprite::create(fileName);
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.density = 1.0f; // 密度
    material.restitution = 1.0f; // 反発係数
    material.friction = 0.4f; // 摩擦係数
    sprite->setPhysicsBody(PhysicsBody::createCircle((sprite->getContentSize().width / 2 - 1), material));
    sprite->getPhysicsBody()->setDynamic(dynamic);
    sprite->setPosition(p);
    parent->addChild(sprite, 10);
    return sprite;
}

// 四角(物理エンジン)を作成
Sprite* Game03Layer::addNewBoxAtPosition(Node* parent, Point p, bool dynamic, const char* fileName) {
    Sprite* sprite = Sprite::create(fileName);
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.density = 1.0f; // 密度
    material.restitution = 0.7f; // 反発係数
    material.friction = 0.0f; // 摩擦係数
    sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getContentSize(), material));
    sprite->getPhysicsBody()->setDynamic(dynamic);
    sprite->setPosition(p);
    parent->addChild(sprite, 10);
    return sprite;
}

//タッチした時に呼び出される関数
bool Game03Layer::onTouchBegan(Touch* touch, Event* event) {
    auto location = touch->getLocation();
    
    if (_game_state == 0) {
        this->addObject(this, location);
        _score++;
        this->viewScore();
    }

    /*int rand = random(0, 5);
    switch (rand) {
        case 0:
            this->addNewCircleAtPosition(this, Point(location), true, "puzzle1.png");
            break;

        case 1:
            this->addNewCircleAtPosition(this, Point(location), true, "puzzle2.png");
            break;

        case 2:
            this->addNewCircleAtPosition(this, Point(location), true, "puzzle3.png");
            break;

        case 3:
            this->addNewCircleAtPosition(this, Point(location), true, "puzzle4.png");
            break;

        case 4:
            this->addNewCircleAtPosition(this, Point(location), true, "puzzle5.png");
            break;

        case 5:
            this->addNewCircleAtPosition(this, Point(location), true, "puzzle6.png");
            break;

        default:
            break;
    }*/

    return true;
}

#include "TitleLayer.h"
void Game03Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}