#pragma execution_character_set("utf-8")
#include "Game13Layer.h"
#include "SimpleAudioEngine.h"

Scene* Game13Layer::createScene()
{
    Scene* scene = Scene::create();
    Game13Layer* layer = Game13Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game13Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game13Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 130, 50));
    labelItem01->setColor(Color3B::BLUE);
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    //グリッドを引く
    //CommonUtile::drawGrid(this, Color4F::BLUE, 100, 1.0f);

    _blockBatchNode = SpriteBatchNode::create("game13/block.png");
    this->addChild(_blockBatchNode);

    this->initDisp();

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game13Layer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


//タッチした時に呼び出される関数
bool Game13Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    
    return this->touchBlock(location);
}

//タッチを離した時に呼び出される関数  
void Game13Layer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

}

//タッチしながら移動中に呼び出される関数
void Game13Layer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void Game13Layer::initDisp() {
    
    for (int y = 0; y < _stage.size(); y++) {
        for (int x = 0; x < _stage.at(0).size(); x++) {
            CCLOG("%d", _stage.at(y).at(x));
            auto sp = Sprite::createWithTexture(_blockBatchNode->getTexture(), Rect(0, 0, 100, 100));
            sp->setPosition(Vec2((winSizeCenterW - 200) + 100 * x, (winSizeCenterH + 100) - 100 * y));
            sp->setTextureRect(Rect(100 * _stage.at(y).at(x), 0, 100, 100));
            sp->setTag(_stage.at(y).at(x));
            this->addChild(sp);
            _blockList.pushBack(sp);
        }
    }
}

bool Game13Layer::touchBlock(Vec2 pos) {

    for (auto block : _blockList) {
        if (block->getBoundingBox().containsPoint(pos)) {
            CCLOG("%f, %f", block->getPosition().x, block->getPosition().y);
            CCLOG("%d", block->getTag());

            return true;
        }
    }

    return false;
}

#include "TitleLayer.h"
void Game13Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}

