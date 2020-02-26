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
    this->addChild(menu, (int)mainZOderList::TITLEBACK);

    //スコア画像はBatchNodeで処理
    _scoreBatchNode = SpriteBatchNode::create("number.png");
    this->addChild(_scoreBatchNode);

    //初期化
    _score = 0;
    _timer = 20.0f;
    _game_state = (int)GameState::DEFAULT;

    //初期表示
    this->initDisp();

    //一定間隔でエネミーの出現
    schedule(schedule_selector(Game01Layer::spawnEnemy), 0.4f);

    this->scheduleUpdate();

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
    this->addChild(bg, (int)mainZOderList::BG);
    
    //スコア表示
    this->viewScore();

    //制限時間を表示
    this->viewTimer();

    //ゲーム開始
    this->GameStart();
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
        number->setPosition(Vec2((winSizeCenterW - 300) + numberRect * i, winSizeH - 50));
        char c = score[i];
        int num = c - '0';
        number->setTextureRect(Rect(numberRect * num, 0, numberRect, numberRect));
        this->addChild(number, (int)mainZOderList::SCORE, "score");
    }
}

//制限時間を表示する
void Game01Layer::viewTimer() {
    //timerの名前がついているノードをすべて削除
    this->enumerateChildren("timer", [](Node* node) -> bool {
        auto action = RemoveSelf::create();
        node->runAction(action);
        return false;
    });

    std::string timer = StringUtils::toString((int)_timer);
    int lang = timer.length();
    int numberRect = 64;

    for (int i = 0; i < lang; i++) {
        auto number = Sprite::createWithTexture(_scoreBatchNode->getTexture(), Rect(0, 0, numberRect, numberRect));
        number->setPosition(Vec2(100 + numberRect * i, winSizeH - 50));
        char c = timer[i];
        int num = c - '0';
        number->setTextureRect(Rect(numberRect * num, 0, numberRect, numberRect));
        this->addChild(number, (int)mainZOderList::SCORE, "timer");
    }
}

void Game01Layer::update(float flame) {
    if (_game_state == (int)GameState::GAME) {
        _timer -= flame;
        this->viewTimer();
        if ((int)_timer <= 0) {
            _game_state = (int)GameState::TIMEUP;
            this->GameOver();
        }
    }
}

void Game01Layer::GameStart()
{
    auto count3 = Sprite::create("countdown3.png");
    count3->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    count3->setOpacity(0);
    this->addChild(count3);

    auto count2 = Sprite::create("countdown2.png");
    count2->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    count2->setOpacity(0);
    this->addChild(count2);

    auto count1 = Sprite::create("countdown1.png");
    count1->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    count1->setOpacity(0);
    this->addChild(count1);

    auto start = Sprite::create("txt_start.png");
    start->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    start->setOpacity(1);
    this->addChild(start);

    auto ac = Sequence::create(
        Spawn::create(
            EaseOut::create(MoveBy::create(0.3f, Vec2(0, 100)), 3),
            EaseOut::create(FadeIn::create(0.5f), 3),
            nullptr
        ),
        EaseOut::create(FadeOut::create(0.1f), 3),
        nullptr);

    auto ac2 = Sequence::create(
        FadeIn::create(0.0f),
        Spawn::create(
            EaseIn::create(ScaleTo::create(0.3f, 2.0f), 3),
            EaseIn::create(FadeOut::create(0.3f), 3),
            nullptr
        ),
        EaseOut::create(FadeOut::create(0.1f), 3),
        CallFunc::create([this]() {
            _game_state = (int)GameState::GAME;
    }),
        nullptr);

    count3->runAction(
        Sequence::create(
            DelayTime::create(0.5f),
            ac,
            TargetedAction::create(count2, Sequence::create(ac, RemoveSelf::create(), nullptr)),
            TargetedAction::create(count1, Sequence::create(ac, RemoveSelf::create(), nullptr)),
            TargetedAction::create(start, Sequence::create(ac2, RemoveSelf::create(), nullptr)),
            RemoveSelf::create(),
            nullptr)
    );
}

//敵の出現
void Game01Layer::spawnEnemy(float frame) {
    if (_game_state == (int)GameState::GAME) {
        kEnemyType type = (kEnemyType)(rand() % 3);
        auto enemy = Enemy::create(type);
        //cocos2dxのrandom関数を使う
        int px = random(75, (int)winSizeW - 75);
        int py = random(75, (int)winSizeH - 200);
        //CCLOG("%d:%d", px, py);
        enemy->setPosition(Vec2(px, py));
        this->addChild(enemy, (int)mainZOderList::ENEMY);
        this->_enemys.push_back(enemy);

        auto ac = Sequence::create(
                DelayTime::create(1.0f),
                FadeOut::create(0.5f),
                RemoveSelf::create(),
                CallFunc::create([=]() {
                    this->_enemys.erase(remove(this->_enemys.begin(), this->_enemys.end(), enemy), this->_enemys.end());
                    this->_enemys.shrink_to_fit();
                }),
                nullptr
                );
        ac->setTag(1);

        //出現してから1秒後に消滅
        enemy->runAction(ac);
    }
}

//タッチした時に呼び出される関数
bool Game01Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    Vec2 location = touch->getLocation();

    if (_game_state != (int)GameState::GAME) {
        return false;
    }

    for (int i = 0; i < (int)this->_enemys.size(); i++) {
        auto enemy = this->_enemys.at(i);

        Rect enemyRect = this->getRect(enemy);

        if (enemyRect.containsPoint(location)) {
            int enemy_point = enemy->getEnemyPoint();
            enemy->stopActionByTag(1);

            enemy->runAction(
                Sequence::create(
                    Spawn::create(
                        FadeOut::create(0.5f),
                        MoveBy::create(0.5f, Vec2(100, 0)),
                        nullptr
                    ),
                    RemoveSelf::create(),
                    nullptr)
            );

            this->_enemys.erase(this->_enemys.begin() + i);
            
            //スコアを更新
            _score += enemy_point;
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

void Game01Layer::GameOver() {
    auto gameover = Sprite::create("txt_gameover.png");
    gameover->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(gameover);
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
    Enemy* ret = new Enemy();

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

int Enemy::getEnemyPoint() {
    return _EnemyScore[type];
}
