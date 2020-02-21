#include "Game08Layer.h"
#include "SimpleAudioEngine.h"
#include <iomanip>

Scene* Game08Layer::createScene()
{
    Scene* scene = Scene::create();
    Game08Layer* layer = Game08Layer::create();
    scene->addChild(layer);
    return scene;
}

bool Game08Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------Game08Layer::init()----------------");
    
    auto labelBtnLabel01 = Label::createWithSystemFont("Back to Title", "Arial", 36);
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01, CC_CALLBACK_0(Game08Layer::backTitleCallback, this));
    labelItem01->setPosition(Vec2(winSizeW - 130, 50));
    labelItem01->setColor(Color3B::BLUE);
    auto menu = Menu::create(labelItem01, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);

    //�X�R�A�摜��BatchNode�ŏ���
    _scoreBatchNode = SpriteBatchNode::create("number.png");
    this->addChild(_scoreBatchNode);

    //�����l
    _isPlayerMove = false;
    _isPlayerMuki = 0;
    _score = 0;

    //�����\��
    this->initDisp();


    this->scheduleUpdate();

    //�^�b�`�C�x���g�̐ݒ�
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game08Layer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game08Layer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game08Layer::initDisp() {
    //�w�i
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    this->addChild(bg, 0);

    //�n��
    auto floor = Sprite::create("floor.png");
    floor->setPosition(Vec2(winSizeCenterW, 30));
    this->addChild(floor);
    
    //�X�R�A�\��
    this->viewScore();

    //���@�\��
    this->drawPlayer();
}

//�X�R�A��\������
void Game08Layer::viewScore() {
    //score�̖��O�����Ă���m�[�h�����ׂč폜
    this->enumerateChildren("score", [](Node* node) -> bool {
        auto action = RemoveSelf::create();
        node->runAction(action);
        return false;
        });
    
    //������ɕϊ��A10��0�Ŗ��߂�
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
        this->addChild(number, 10, "score");
    }
}

//���@�Ƒ���{�^���̕\��
void Game08Layer::drawPlayer() {
    //���@�̕\��
    _player = Sprite::create("player.png");
    _player->setPosition(Vec2(winSizeCenterW, 150));
    this->addChild(_player, 1);

    //����{�^��
    _btnL = Sprite::create("btnL.png");
    _btnL->setPosition(Vec2(100, winSizeCenterH));
    this->addChild(_btnL, 10);

    _btnR = Sprite::create("btnR.png");
    _btnR->setPosition(Vec2(winSizeW - 100, winSizeCenterH));
    this->addChild(_btnR, 10);

}

void Game08Layer::update(float flame) {
    
    //�[�ɍs���Ă��Ȃ����
    /*if (_player->getPositionX() > 110
        && _player->getPositionX() < winSizeW - 110
        && _isPlayerMove) {*/
    if(_isPlayerMove){

        if (_isPlayerMuki == 0) {
            _player->setPosition(Vec2(this->_player->getPositionX() - 250 * flame, _player->getPositionY()));
        }
        else {
            _player->setPosition(Vec2(this->_player->getPositionX() + 250 * flame, _player->getPositionY()));
        }
        
    }

}

//�^�b�`�������ɌĂяo�����֐�
bool Game08Layer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 location = touch->getLocation();

    if (_btnL->getBoundingBox().containsPoint(location)) {
        _isPlayerMove = true;
        _isPlayerMuki = 0;
        _player->setFlippedX(false);
        CCLOG("left btn");
    }

    if (_btnR->getBoundingBox().containsPoint(location)) {
        _isPlayerMove = true;
        _isPlayerMuki = 1;
        _player->setFlippedX(true);
        CCLOG("right btn");
    }

    return true;
}

//�^�b�`�𗣂������ɌĂяo�����֐�  
void Game08Layer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto location = touch->getLocation();
    _isPlayerMove = false;
}

//�m�[�h��RECT��Ԃ�
Rect Game08Layer::getRect(Node* node)
{
    Point point = node->getPosition();
    int width = node->getContentSize().width;
    int height = node->getContentSize().height;
    return Rect(point.x - (width / 2), point.y - (height / 2), width, height);
}

#include "TitleLayer.h"
void Game08Layer::backTitleCallback() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::createScene(), Color3B::WHITE));
}
