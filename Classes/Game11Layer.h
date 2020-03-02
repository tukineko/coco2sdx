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

    CC_SYNTHESIZE_READONLY_PASS_BY_REF(Vec2, _mamePosition, MamePosition);
    CC_SYNTHESIZE_READONLY(mameType, _mameType, MameType);

};


class Game11Layer : public Layer
{
protected:
    Sprite* _btn01;
    bool _btn01_state = false;
    Sprite* _btn02;
    bool _btn02_state = false;

    Vector<Mame*> _mameList;


public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game11Layer);
    
    void initDisp();
    void ClickBtn01();
    
    void addMame(Mame* mame);


    //豆を設置するノード
    CC_SYNTHESIZE_RETAIN(Node*, _stage, Stage);

    bool onTouchBegan(Touch* touch, Event* event);
    void backTitleCallback();
};

#endif // __Game11Layer_H__
