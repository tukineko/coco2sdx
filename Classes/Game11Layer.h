#ifndef __Game11Layer_H__
#define __Game11Layer_H__

#include "Config.h"

USING_NS_CC;

const int MAME_SIZE = 100;

class Mame : public Sprite {
protected:
public:
    enum class mameType {
        OK = 0,
        NG,
        COUNT
    };

    enum class State {
        /// 停止中
        STATIC = 0,
        /// 出現中
        APPEARING,
        /// 落下中
        FALLING,
        /// 入れ替え中
        SWAPPING,
        /// 消去中
        DISAPEARING
    };

    Mame();
    ~Mame();
    virtual bool init();
    CREATE_FUNC(Mame);

    static int getSize() {
        return MAME_SIZE;
    }

    /** ステージ上の座標をグリッド上の位置に変換します
     *  @param stagePosition ステージ上の座標
     *  @return グリッド上の位置
     */
    static Vec2 convertToGridSpace(const Vec2& stagePosition);

    /** グリッド上の位置をステージ上の座標に変換します
     *  @param gridPosition グリッド上の位置
     *  @return ステージ上の座標
     */
    static Vec2 convertToStageSpace(const Vec2& gridPosition);

    /** 豆のグリッド上の位置を指定します
    * @param position x, y位置を含んだ二次元ベクトル
    */
    void setMamePosition(const Vec2& position);
    
    /** 豆の位置を、現在のグリッド上の位置に合わせて調整します
     */
    void adjustPosition();

    /** 豆が停止状態かどうかを返します
     *  @return 停止状態かどうか
     */
    bool isStatic() {
        return _state == State::STATIC;
    }

    CC_SYNTHESIZE(State, _state, State);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(Vec2, _mamePosition, MamePosition);
    CC_SYNTHESIZE_READONLY(mameType, _mameType, MameType);

};

typedef cocos2d::Vector<Mame*> MameVector;

class Game11Layer : public Layer
{
protected:
    Sprite* _btn01;
    bool _btn01_state = false;
    Sprite* _btn02;
    bool _btn02_state = false;


public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game11Layer);
    
    void initDisp();
    void ClickBtn01();
    void ClickBtn02();
    
    void addMame(Mame* mame);
    void deleteMame(Mame::mameType mame_type);

    void update(float dt);

    /** グリッド上の特定位置にある豆を取り出します
    *   何もなかった場合はnullptrを返します
     *  @param position グリッド上の豆位置
     *  @return その位置にあるCookie、またはnullptr
    */
    Mame* getMameAt(const Vec2& position);

    /** 渡された豆が落ちるかどうかを判定し、落ちる場合は落下させます
     *  @param mame チェックする豆
     *  @return 落ちたかどうか
     */
    bool fallMame(Mame* mame);

    /** クッキーをグリッド上の指定した位置に動かします
     *  @param cookie 動かすブロック
     *  @param cookiePosition 動かすグリッド上の座標
     */
    void moveMame(Mame* mame, const Vec2& mamePosition);

    /** ステージをチェックして出現できる場所に豆を出現させ、出現した豆の一覧を返します
     *  出現しなかった場合、空のベクターを返します
     *  @return 出現したクッキーの一覧
     */
    Vector<Mame*> checkSpawn();

    CC_SYNTHESIZE_PASS_BY_REF(MameVector, _mames, Mames);
    //豆を設置するノード
    CC_SYNTHESIZE_RETAIN(Node*, _stage, Stage);

    bool onTouchBegan(Touch* touch, Event* event);
    void backTitleCallback();
};

#endif // __Game11Layer_H__
