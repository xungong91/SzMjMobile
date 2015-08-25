//
//  UIBaseTopLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIBaseTopLayer.h"
#include "UIMainLayer.h"

UIBaseTopLayer::UIBaseTopLayer()
{
}

UIBaseTopLayer::~UIBaseTopLayer()
{
}

bool UIBaseTopLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mTopLayout = CSLoader::createNode("res/CCS_topWidget.csb");
    mTopLayout->setPosition(Point(0, 1720));
    this->addChild(mTopLayout, 1);
    
    CocosHelper::getWidgetByName(mTopLayout, "BtnReturn")->addTouchEventListener
    ([](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->popLayer();
         }
     });
    
    return true;
}