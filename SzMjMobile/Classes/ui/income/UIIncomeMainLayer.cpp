//
//  UIIncomeMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIIncomeMainLayer.h"
#include "UIIncomeModelLayer.h"
#include "UIMainLayer.h"
#include "UIIncomePickLayer.h"
#include "UIWidgetSearchLayer.h"

bool UIIncomeMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_income.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Image_0")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             auto temp = UIIncomeModelLayer::create();
             temp->setTitle("Eva小公举");
             UIMainLayer::gUIMainLayer->pushLayer(temp);
         }
     }
     );
    CocosHelper::getWidgetByName(mLayout, "Image_1")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             auto temp = UIIncomeModelLayer::create();
             temp->setTitle("奈奈");
             UIMainLayer::gUIMainLayer->pushLayer(temp);
         }
     }
     );
    CocosHelper::getWidgetByName(mLayout, "Image_2")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             auto temp = UIIncomeModelLayer::create();
             temp->setTitle("娃娃");
             UIMainLayer::gUIMainLayer->pushLayer(temp);
         }
     }
     );
    
    CocosHelper::getWidgetByName(mLayout, "Button_pick")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIIncomePickLayer::create());
         }
     }
     );
    
    auto mUIWidgetSearchLayer = UIWidgetSearchLayer::create();
    mUIWidgetSearchLayer->setPosition(Point(0, 1575));
    this->addChild(mUIWidgetSearchLayer);
    mUIWidgetSearchLayer->setVisible(false);
    vector<string> modelNicks = {"Eva小公举", "奈奈", "娃娃"};
    mUIWidgetSearchLayer->setHandldAction([modelNicks](string text)
                                          {
                                              if (find(modelNicks.begin(), modelNicks.end(), text) != modelNicks.end())
                                              {
                                                  auto temp = UIIncomeModelLayer::create();
                                                  temp->setTitle("text");
                                                  UIMainLayer::gUIMainLayer->pushLayer(temp);
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