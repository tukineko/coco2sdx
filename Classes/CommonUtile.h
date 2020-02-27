#ifndef __CommonUtile_H__
#define __CommonUtile_H__

#include "config.h"

namespace CommonUtile {
    //グリッド線を引く
    void drawGrid(cocos2d::Node* parent, cocos2d::Color4F color, int lineWidth, float lineSize);
}

#endif // __CommonUtile_H__
