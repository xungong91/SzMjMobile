//
//  UIManageModelLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIManageModelLayer.h"
#include "UIManageModelEditLayer.h"
#include "UIMainLayer.h"

bool UIManageModelLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    mEditTouchFunc = nullptr;
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_manageModel.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Button_manage")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
    {
        if (type == Widget::TouchEventType::ENDED)
        {
            if (mEditTouchFunc)
            {
                mEditTouchFunc();
            }
        }
    });
    
    for (int i = 0; i < 2; ++i)
    {
        CocosHelper::getWidgetByName(mLayout, __String::createWithFormat("Image_model%d", i)->getCString())->addTouchEventListener(CC_CALLBACK_2(UIManageModelLayer::onModelTouch, this));
    }
    
    return true;
}

void UIManageModelLayer::onModelTouch(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        UIMainLayer::gUIMainLayer->pushLayer(UIManageModelEditLayer::create());
    }
}