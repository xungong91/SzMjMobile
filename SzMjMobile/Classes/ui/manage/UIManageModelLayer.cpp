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
#include "UIWidgetSearchLayer.h"

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
    
    auto mUIWidgetSearchLayer = UIWidgetSearchLayer::create();
    mUIWidgetSearchLayer->setPosition(Point(0, 1575));
    this->addChild(mUIWidgetSearchLayer);
    mUIWidgetSearchLayer->setVisible(false);
    vector<string> modelNicks = {"任性的小伊伊", "娃娃"};
    mUIWidgetSearchLayer->setHandldAction([modelNicks](string text)
                                          {
                                              if (find(modelNicks.begin(), modelNicks.end(), text) != modelNicks.end())
                                              {
                                                  UIMainLayer::gUIMainLayer->pushLayer(UIManageModelEditLayer::create());
                                              }
                                          });
    
    CocosHelper::getWidgetByName(mLayout, "Button_Search")->addTouchEventListener
    (
     [mUIWidgetSearchLayer](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             mUIWidgetSearchLayer->setVisible(!mUIWidgetSearchLayer->isVisible());
         }
     }
     );
    
    return true;
}

void UIManageModelLayer::onModelTouch(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        UIMainLayer::gUIMainLayer->pushLayer(UIManageModelEditLayer::create());
    }
}