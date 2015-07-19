//
//  CTestDrawLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/7/5.
//
//

#include "CTestDrawLayer.h"

bool CTestDrawLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->addChild(LayerColor::create(Color4B(0, 0, 0, 255)), -1);
    
    auto draw = DrawNode::create();
    this->addChild(draw, 10);
    //draw a solid polygon
    Vec2 vertices3[] = {Vec2(60,160), Vec2(70,190), Vec2(100,190), Vec2(90,160)};
    draw->drawSolidPoly( vertices3, 4, Color4F(1,1,0,1) );
    
    //draw a solid rectangle
    draw->drawSolidRect(Vec2(10,10), Vec2(400,500), Color4F(1,1,0,0.5f));
    return true;
}

void CTestDrawLayer::onEnter()
{
    Layer::onEnter();
    
    auto myListener = EventListenerTouchOneByOne::create();
    myListener->setSwallowTouches(true);
    myListener->onTouchBegan = [=](Touch* touch,Event* event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
}

void CTestDrawLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(CTestDrawLayer::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void CTestDrawLayer::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated)
{
    //利用Stack缓存
    Director *director = Director::getInstance();
    //CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    CHECK_GL_ERROR_DEBUG();
    
    //画边框
    DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
    glLineWidth(10);
    Vec2 vertices[] = {Vec2(100, 100), Vec2(300, 100), Vec2(300, 300), Vec2(100, 300)};
    DrawPrimitives::drawPoly(vertices, 4, true);
    
    CHECK_GL_ERROR_DEBUG();
    
    //绘制停止，释放
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}