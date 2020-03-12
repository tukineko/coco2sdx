#pragma execution_character_set("utf-8")

#include "TitleLayer.h"
#include "SimpleAudioEngine.h"

#define PI 3.14159265358979323846

USING_NS_CC;

enum class mainZOderList{
    BG = 0,
    CHARA,
    TITLE,
    MENU
};

Scene* TitleLayer::createScene()
{
    Scene* scene = Scene::create();
    TitleLayer* layer = TitleLayer::create();
    scene->addChild(layer);
    return scene;
}

bool TitleLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------TitleLayer::init()----------------");

    //グリッドを引く
    //CommonUtile::drawGrid(this, Color4F::BLUE, 100, 1.0f);

    //背景
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    this->addChild(bg, (int)mainZOderList::BG);

    //タイトル
    auto title = Sprite::create("title/logo.png");
    title->setPosition(Vec2(winSizeCenterW, winSizeH - 150));
    title->setOpacity(0);
    this->addChild(title, (int)mainZOderList::TITLE);
    title->runAction(EaseOut::create(FadeIn::create(1.0f), 1.0f));
    
    //メニューボタン（テキスト）
    int fontsize = 36;
    int leftPos = 100;
    int rightPos = 700;

    auto labelBtnLabel1 = Label::createWithSystemFont("タップしたら得点が増えるだけ", "Arial", fontsize);
    auto mItem1 = MenuItemLabel::create(labelBtnLabel1, CC_CALLBACK_0(TitleLayer::nextSceneCallback, this));
    mItem1->setPosition(Vec2(leftPos, winSizeH - 350));
    mItem1->setAnchorPoint(Point::ZERO);
    mItem1->setColor(Color3B::BLUE);

    auto labelBtnLabel2 = Label::createWithSystemFont("羽つきゲームっぽいもの", "Arial", fontsize);
    auto mItem2 = MenuItemLabel::create(labelBtnLabel2, CC_CALLBACK_0(TitleLayer::nextSceneCallback2, this));
    mItem2->setPosition(Vec2(leftPos, winSizeH - 400));
    mItem2->setAnchorPoint(Point::ZERO);
    mItem2->setColor(Color3B::BLUE);

    auto labelBtnLabel3 = Label::createWithSystemFont("物理エンジンで物体を落とすだけ", "Arial", fontsize);
    auto mItem3 = MenuItemLabel::create(labelBtnLabel3, CC_CALLBACK_0(TitleLayer::nextSceneCallback3, this));
    mItem3->setPosition(Vec2(leftPos, winSizeH - 450));
    mItem3->setAnchorPoint(Point::ZERO);
    mItem3->setColor(Color3B::BLUE);

    auto labelBtnLabel4 = Label::createWithSystemFont("指でぐるぐる回すだけ", "Arial", fontsize);
    auto mItem4 = MenuItemLabel::create(labelBtnLabel4, CC_CALLBACK_0(TitleLayer::nextSceneCallback4, this));
    mItem4->setPosition(Vec2(leftPos, winSizeH - 500));
    mItem4->setAnchorPoint(Point::ZERO);
    mItem4->setColor(Color3B::BLUE);

    auto labelBtnLabel5 = Label::createWithSystemFont("ゲージ", "Arial", fontsize);
    auto mItem5 = MenuItemLabel::create(labelBtnLabel5, CC_CALLBACK_0(TitleLayer::nextSceneCallback5, this));
    mItem5->setPosition(Vec2(leftPos, winSizeH - 550));
    mItem5->setAnchorPoint(Point::ZERO);
    mItem5->setColor(Color3B::BLUE);

    auto labelBtnLabel6 = Label::createWithSystemFont("物理エンジンで引っ張って飛ばす", "Arial", fontsize);
    auto mItem6 = MenuItemLabel::create(labelBtnLabel6, CC_CALLBACK_0(TitleLayer::nextSceneCallback6, this));
    mItem6->setPosition(Vec2(leftPos, winSizeH - 600));
    mItem6->setAnchorPoint(Point::ZERO);
    mItem6->setColor(Color3B::BLUE);

    auto labelBtnLabel7 = Label::createWithSystemFont("真剣衰弱っぽいもの", "Arial", fontsize);
    auto mItem7 = MenuItemLabel::create(labelBtnLabel7, CC_CALLBACK_0(TitleLayer::nextSceneCallback7, this));
    mItem7->setPosition(Vec2(leftPos, winSizeH - 650));
    mItem7->setAnchorPoint(Point::ZERO);
    mItem7->setColor(Color3B::BLUE);

    auto labelBtnLabel8 = Label::createWithSystemFont("自機操作のキャッチ", "Arial", fontsize);
    auto mItem8 = MenuItemLabel::create(labelBtnLabel8, CC_CALLBACK_0(TitleLayer::nextSceneCallback8, this));
    mItem8->setPosition(Vec2(leftPos, winSizeH - 700));
    mItem8->setAnchorPoint(Point::ZERO);
    mItem8->setColor(Color3B::BLUE);

    auto labelBtnLabel9 = Label::createWithSystemFont("ビジュアルパズルっぽいもの", "Arial", fontsize);
    auto mItem9 = MenuItemLabel::create(labelBtnLabel9, CC_CALLBACK_0(TitleLayer::nextSceneCallback9, this));
    mItem9->setPosition(Vec2(rightPos, winSizeH - 350));
    mItem9->setAnchorPoint(Point::ZERO);
    mItem9->setColor(Color3B::BLUE);

    auto labelBtnLabel10 = Label::createWithSystemFont("演出etc", "Arial", fontsize);
    auto mItem10 = MenuItemLabel::create(labelBtnLabel10, CC_CALLBACK_0(TitleLayer::nextSceneCallback10, this));
    mItem10->setPosition(Vec2(rightPos, winSizeH - 400));
    mItem10->setAnchorPoint(Point::ZERO);
    mItem10->setColor(Color3B::BLUE);

    auto labelBtnLabel11 = Label::createWithSystemFont("大豆でなにか", "Arial", fontsize);
    auto mItem11 = MenuItemLabel::create(labelBtnLabel11, CC_CALLBACK_0(TitleLayer::nextSceneCallback11, this));
    mItem11->setPosition(Vec2(rightPos, winSizeH - 450));
    mItem11->setAnchorPoint(Point::ZERO);
    mItem11->setColor(Color3B::BLUE);

    auto labelBtnLabel12 = Label::createWithSystemFont("間違い探し", "Arial", fontsize);
    auto mItem12 = MenuItemLabel::create(labelBtnLabel12, CC_CALLBACK_0(TitleLayer::nextSceneCallback12, this));
    mItem12->setPosition(Vec2(rightPos, winSizeH - 500));
    mItem12->setAnchorPoint(Point::ZERO);
    mItem12->setColor(Color3B::BLUE);

    auto labelBtnLabel13 = Label::createWithSystemFont("なぞりゲー", "Arial", fontsize);
    auto mItem13 = MenuItemLabel::create(labelBtnLabel13, CC_CALLBACK_0(TitleLayer::nextSceneCallback13, this));
    mItem13->setPosition(Vec2(rightPos, winSizeH - 550));
    mItem13->setAnchorPoint(Point::ZERO);
    mItem13->setColor(Color3B::BLUE);

    //メニューを作成
    auto menu = Menu::create(mItem1, mItem2, mItem3, mItem4, mItem5, mItem6, mItem7, mItem8, mItem9, mItem10, mItem11, mItem12, mItem13, NULL);
    menu->setPosition(Point::ZERO);
    menu->setOpacity(0);
    this->addChild(menu, (int)mainZOderList::MENU);
    menu->runAction(
        Sequence::create(
            DelayTime::create(1.2f),
            Spawn::create(
                FadeIn::create(0.5f),
                MoveBy::create(0.5f, Vec2(0, 10)),
                nullptr
            ),
            nullptr
        )   
    );

    //キャラクター
    _chara = Sprite::create("title/player.png");
    _chara->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    _chara->setFlippedX(true);
    this->addChild(_chara, (int)mainZOderList::CHARA);
    
    this->scheduleUpdate();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(TitleLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(TitleLayer::onTouchMoved, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
#include "Game01Layer.h"
void TitleLayer::nextSceneCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game01Layer::createScene(), Color3B::WHITE));
}

#include "Game02Layer.h"
void TitleLayer::nextSceneCallback2() {
    Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, Game02Layer::createScene()));
}

#include "Game03Layer.h"
void TitleLayer::nextSceneCallback3() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game03Layer::createScene(), Color3B::WHITE));
}

#include "Game04Layer.h"
void TitleLayer::nextSceneCallback4() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game04Layer::createScene(), Color3B::WHITE));
}

#include "Game05Layer.h"
void TitleLayer::nextSceneCallback5() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game05Layer::createScene(), Color3B::WHITE));
}

#include "Game06Layer.h"
void TitleLayer::nextSceneCallback6() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game06Layer::createScene(), Color3B::WHITE));
}

#include "Game07Layer.h"
void TitleLayer::nextSceneCallback7() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game07Layer::createScene(), Color3B::WHITE));
}

#include "Game08Layer.h"
void TitleLayer::nextSceneCallback8() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game08Layer::createScene(), Color3B::WHITE));
}

#include "Game09Layer.h"
void TitleLayer::nextSceneCallback9() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game09Layer::createScene(), Color3B::WHITE));
}

#include "Game10Layer.h"
void TitleLayer::nextSceneCallback10() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game10Layer::createScene(), Color3B::WHITE));
}

#include "Game11Layer.h"
void TitleLayer::nextSceneCallback11() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game11Layer::createScene(), Color3B::WHITE));
}

#include "Game12Layer.h"
void TitleLayer::nextSceneCallback12() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game12Layer::createScene(), Color3B::WHITE));
}

#include "Game13Layer.h"
void TitleLayer::nextSceneCallback13() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Game13Layer::createScene(), Color3B::WHITE));
}

//タッチした時に呼び出される関数
bool TitleLayer::onTouchBegan(Touch* touch, Event* event) {
    auto location = touch->getLocation();

    // 作成したパーティクルのプロパティリストを読み込み
    auto particle = ParticleSystemQuad::create("particle_texture/particle_texture.plist");
    particle->resetSystem();
    // パーティクルを表示する場所の設定
    particle->setPosition(location);
    //パーティクルのメモリーリーク回避（★重要）
    particle->setAutoRemoveOnFinish(true);
    // パーティクルを配置
    this->addChild(particle, 100);
    

    return true;
}

//タッチを離した時に呼び出される関数  
void TitleLayer::onTouchEnded(Touch* touch, Event* event) {



}

//タッチしながら移動中に呼び出される関数
void TitleLayer::onTouchMoved(Touch* touch, Event* event) {
    auto location = touch->getLocation();

    // 作成したパーティクルのプロパティリストを読み込み
    auto particle = ParticleSystemQuad::create("particle_texture/particle_texture.plist");
    particle->resetSystem();
    // パーティクルを表示する場所の設定
    particle->setPosition(location);
    //パーティクルのメモリーリーク回避（★重要）
    particle->setAutoRemoveOnFinish(true);
    // パーティクルを配置
    this->addChild(particle, 100);
}

void TitleLayer::update(float dt) {
    
    //キャラクターの動き
    _py += dt;
    auto cPosX = _chara->getPositionX() + _px;
    auto cPosY = _chara->getPositionY() + sin(PI * 1.5 * _py);
    _chara->setPosition(Vec2(cPosX, cPosY));
    if (cPosX < 103 || cPosX > winSizeW -103) {
        this->ChangeCharaDirection();
    }
    
}

void TitleLayer::ChangeCharaDirection() {
    _px = -_px;
    if (_px > 0) {
        _chara->setFlippedX(true);
    }
    else {
        _chara->setFlippedX(false);
    }
}