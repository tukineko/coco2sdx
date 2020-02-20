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

    //初期表示
    this->initDisp();

    //一定間隔でエネミーの出現
    schedule(schedule_selector(Game01Layer::spawnEnemy), 0.5f);

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game01Layer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game01Layer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game01Layer::initDisp() {
    //背景
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    this->addChild(bg, 0);
    
    //スコア表示
    this->viewScore();

}

//スコアを表示する
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

void Game01Layer::spawnEnemy(float frame) {
    kEnemyType type = (kEnemyType)(rand() % 3);
    auto enemy = Enemy::create(type);
    int px = rand() % (int)winSizeW;
    int py = rand() % (int)winSizeH;
    enemy->setPosition(Vec2(px, py));
    this->addChild(enemy, 5);
    this->_enemys.pushBack(enemy);

    //出現してから2秒後に消滅
    enemy->runAction(
        Sequence::create(
            DelayTime::create(1.0f),
            FadeOut::create(0.5f),
            RemoveSelf::create(),
            nullptr
        )
    );
}

//タッチした時に呼び出される関数
bool Game01Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    Vec2 location = touch->getLocation();

    for (int i = 0; i < this->_enemys.size(); i++) {
        auto enemy = this->_enemys.at(i);

        Rect enemyRect = this->getRect(enemy);

        if (enemyRect.containsPoint(location)) {
            CCLOG("HIT! %d:%d", i, (int)enemy->getType());
            int enemyId = (int)enemy->getType();

            enemy->removeFromParent();
            this->_enemys.erase(i);
            i--;

            //スコアを更新
            _score += _EnemyScore[enemyId];
            this->viewScore();
        }
    }

    return true;
}

//タッチを離した時に呼び出される関数  
void Game01Layer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto location = touch->getLocation();
}

//ノードのRECTを返す
Rect Game01Layer::getRect(Node* node)
{
    Point point = node->getPosition();
    int width = node->getContentSize().width;
    int height = node->getContentSize().height;
    return Rect(point.x - (width / 2), point.y - (height / 2), width, height);
}

#include "TitleLayer.h"
void Game01Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}

/***********************************************
*エネミークラス
***********************************************/
//コンストラクター
//作成されるときに起こる処理
//:以降で数値の初期化をすることが出来る
Enemy::Enemy()
{
}

//デストラクター
//このクラスが終わるときに起こる処理
Enemy::~Enemy()
{
}

Enemy* Enemy::create(kEnemyType _type)
{
    auto sp = new Enemy();
    sp->init(_type);
    sp->autorelease();
    return sp;

    /*Enemy* ret = new Enemy();

    if (ret && ret->init(_type))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }*/
}

bool Enemy::init(kEnemyType _type)
{
    if (!Sprite::initWithFile(getImageFileName(_type))) return false;

    type = _type;

    return true;
}

const char* Enemy::getImageFileName(kEnemyType _type)
{
    switch (_type) {
    case Red:
        return "puzzle1.png";

    case Blue:
        return "puzzle2.png";

    case Green:
        return "puzzle3.png";

    default:
        return "";
    }
}
