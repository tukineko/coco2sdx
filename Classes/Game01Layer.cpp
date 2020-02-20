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

    //�X�R�A�摜��BatchNode�ŏ���
    _scoreBatchNode = SpriteBatchNode::create("number.png");
    this->addChild(_scoreBatchNode);

    //�����\��
    this->initDisp();

    //���Ԋu�ŃG�l�~�[�̏o��
    schedule(schedule_selector(Game01Layer::spawnEnemy), 0.5f);

    //�^�b�`�C�x���g�̐ݒ�
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game01Layer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game01Layer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Game01Layer::initDisp() {
    //�w�i
    auto bg = LayerColor::create(Color4B::WHITE, winSizeW, winSizeH);
    this->addChild(bg, 0);
    
    //�X�R�A�\��
    this->viewScore();

}

//�X�R�A��\������
void Game01Layer::viewScore() {
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

    //�o�����Ă���2�b��ɏ���
    enemy->runAction(
        Sequence::create(
            DelayTime::create(1.0f),
            FadeOut::create(0.5f),
            RemoveSelf::create(),
            nullptr
        )
    );
}

//�^�b�`�������ɌĂяo�����֐�
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

            //�X�R�A���X�V
            _score += _EnemyScore[enemyId];
            this->viewScore();
        }
    }

    return true;
}

//�^�b�`�𗣂������ɌĂяo�����֐�  
void Game01Layer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto location = touch->getLocation();
}

//�m�[�h��RECT��Ԃ�
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
*�G�l�~�[�N���X
***********************************************/
//�R���X�g���N�^�[
//�쐬�����Ƃ��ɋN���鏈��
//:�ȍ~�Ő��l�̏����������邱�Ƃ��o����
Enemy::Enemy()
{
}

//�f�X�g���N�^�[
//���̃N���X���I���Ƃ��ɋN���鏈��
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
