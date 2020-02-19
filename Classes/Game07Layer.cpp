#pragma execution_character_set("utf-8")
#include "Game07Layer.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* Game07Layer::createScene()
{
    Scene* scene = Scene::create();
    Game07Layer* layer = Game07Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game07Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    //タイトルに戻る
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 24);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game07Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 100, 30));
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    //カード配列をシャッフル
    std::random_device get_rand_dev;
    std::mt19937 get_rand_mt(get_rand_dev()); // seedに乱数を指定
    std::shuffle(_cardAry.begin(), _cardAry.end(), get_rand_mt);

    /*for (int i = 0; i < _cardAry.size(); i++) {
        CCLOG("%d", _cardAry[i]);
    }*/

    //カードの表示
    int tagId = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 4; y++) {
            auto card = Sprite::create("card.png");
            card->setPosition(Vec2(150 + 160 * x, winSizeH - 150 - 160 * y));
            this->addChild(card, 1, tagId);
            _cards.pushBack(card);
            tagId++;
        }
    }

    //タッチイベント
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game07Layer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//タッチした時に呼び出される関数
bool Game07Layer::onTouchBegan(Touch* touch, Event* event) {
    auto location = touch->getLocation();
    if (_isAnime == false) {
        for (int i = 0; i < (int)_cards.size(); i++) {
            auto card = _cards.at(i);
            Rect cardRect = this->getRect(card);

            if (cardRect.containsPoint(location)) {
                int id = card->getTag();
                if (_card_boolAry[id] == false) {
                    this->clickCard(id);
                }
            }
        }
    }

    return true;
}

//ノードのRECTを返す
Rect Game07Layer::getRect(Node* node)
{
    Point point = node->getPosition();
    int width = node->getContentSize().width;
    int height = node->getContentSize().height;
    return Rect(point.x - (width / 2), point.y - (height / 2), width, height);
}

//カードをクリック
void Game07Layer::clickCard(int tagId) {
    CCLOG("カードタッチの内部は：%d", _cardAry[tagId]);
    
    //選択したカードのマークを表示
    auto sprite = (Sprite*)this->getChildByTag(tagId);
    sprite->setTexture(getCardImageFileName(_cardAry[tagId]));
    _card_boolAry[tagId] = true;

    //一枚目の選択か？
    if (_isFirst) {
        _card1 = sprite;
        _card1Id = _cardAry[tagId];
        _isFirst = false;
    }
    else {
        if (_card1Id == _cardAry[tagId]) {
            if (this->checkCards()) {
                auto text = Sprite::create("txt_gameover.png");
                text->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
                this->addChild(text, 10);
            }
        }
        else {
            _isAnime = true;
            this->missAnime();
        }

        _isFirst = true;
    }
}

const char* Game07Layer::getCardImageFileName(int num)
{
    switch (num) {
    case 0:
        return "puzzle1.png";

    case 1:
        return "puzzle2.png";

    case 2:
        return "puzzle3.png";

    case 3:
        return "puzzle4.png";

    case 4:
        return "puzzle5.png";

    case 5:
        return "puzzle6.png";

    default:
        return "";
    }
}

//失敗時のアニメーション
void Game07Layer::missAnime() {
    
    for (int i = 0; i < (int)_cards.size(); i++) {
        _card_boolAry[i] = false;
        auto card = _cards.at(i);
        card->runAction(
            Sequence::create(
                MoveBy::create(0.1f, Vec2(10, 0)),
                MoveBy::create(0.1f, Vec2(-10, 0)),
                MoveBy::create(0.1f, Vec2(10, 0)),
                MoveBy::create(0.1f, Vec2(-10, 0)),
                MoveBy::create(0.1f, Vec2(10, 0)),
                MoveBy::create(0.1f, Vec2(-10, 0)),
                CallFunc::create([card, this]() {
                    //すべてのカード表示を表に
                    card->setTexture("card.png");
                    _isAnime = false;
                    }),
                nullptr)
        );
    }
}

//すべてのカードのフラグをチェック
bool Game07Layer::checkCards() {

    int num = 0;
    for (int i = 0; i < (int)_card_boolAry.size(); i++) {
        if (_card_boolAry[i] == true) {
            num++;
        }
    }

    if (num == 12) {
        return true;
    }
    else {
        return false;
    }
}

#include "TitleLayer.h"
void Game07Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}