#include "CommonUtile.h"

USING_NS_CC;

namespace CommonUtile {
    void drawGrid(cocos2d::Node* parent, cocos2d::Color4F color, int lineWidth, float lineSize)
    {
        auto render = RenderTexture::create(winSizeW, winSizeH);
        render->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
        parent->addChild(render, 999);

        render->begin();
        auto line = DrawNode::create();
        line->retain();
        for (int x = 0; x < 50; x++) {
            line->drawSegment(Vec2(lineWidth * x, 0), Vec2(lineWidth * x, winSizeH), lineSize, color);
            line->Node::visit();
        }
        for (int y = 0; y < 50; y++) {
            line->drawSegment(Vec2(0, lineWidth * y), Vec2(winSizeW, lineWidth * y), lineSize, color);
            line->Node::visit();
        }
        render->end();
    }
}

