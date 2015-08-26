//
//  UIModelListLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIModelListLayer.h"
#include "UIModelInfoLayer.h"
#include "UIModelAddLayer.h"
#include "UIMainLayer.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

bool UIModelListLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_model_list.csb", this);
    
    Button *btnModelAdd = (Button*)CocosHelper::getWidgetByName(mLayout, "Button_Add");
    btnModelAdd->addTouchEventListener
    ([btnModelAdd, this](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
             UIMainLayer::gUIMainLayer->pushLayer(UIModelAddLayer::create());
     }
    );
    
    ImageView *image0 = (ImageView*)CocosHelper::getWidgetByName(mLayout, "Image_0");
    image0-> addTouchEventListener
    ([image0, this](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::BEGAN)
             image0->loadTexture("model/Model_0_1.png");
         
         if(type == Widget::TouchEventType::CANCELED)
             image0->loadTexture("model/Model_0_0.png");
         
         if (type == Widget::TouchEventType::ENDED)
         {
             image0->loadTexture("model/Model_0_0.png");
             UIMainLayer::gUIMainLayer->pushLayer(UIModelInfoLayer::create());
         }
     });
    
    return true;
}