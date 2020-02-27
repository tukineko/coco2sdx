#ifndef __Game01Layer_H__
#define __Game01Layer_H__

#include "Config.h"

USING_NS_CC;

//ゲームの状態
enum class GameState {
    DEFAULT = 0,
    COUNTDOWN,
    GAME,
    TIMEUP,
    RESULT,
};

enum kEnemyType {
    Red,
    Blue,
    Green
};

class Enemy : public Sprite
{
protected:
    //タイプによって読み込む画像を変更
    const char* getImageFileName(kEnemyType _type);
    std::vector<int> _EnemyScore = { 100,300,500 };

public:
    //getterとsetterを同時に作成
    //このget~とset~で親からアクセスすることが出来る
    CC_SYNTHESIZE(kEnemyType, type, Type);

    Enemy();
    ~Enemy();
    virtual bool init(kEnemyType _type);
    static Enemy* create(kEnemyType _type);
    int getEnemyPoint();
};

class Game01Layer : public Layer
{
protected:
    SpriteBatchNode* _scoreBatchNode;
    std::vector<Enemy*> _enemys;
    int _game_state;
    int _score;
    float _timer;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game01Layer);
    
    void initDisp();
    void viewScore();
    void viewTimer();
    void GameStart();
    void GameOver();
    void spawnEnemy(float frame);
    Rect getRect(Node* node);

    void update(float frame);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    void backTitleCallback();
};

#endif // __Game01Layer_H__
