//
//  UIWidgetTaskLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIWidgetTaskLayer.h"
#include "UITaskInfoLayer.h"
#include "UIMainLayer.h"

bool UIWidgetTaskLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_WIDGET_Task.csb", this);
    Image_1 = static_cast<ImageView*>(CocosHelper::getNodeByName(mLayout, "Image_1"));
    Image_2 = static_cast<ImageView*>(CocosHelper::getNodeByName(mLayout, "Image_2"));
    
    mActionIndex = 0;
    
//    this->addChild(Menu::create(MenuItemImage::create("taskList/Task_0_0.png", "taskList/Task_0_0.png",
//                                                      [](Ref *sender)
//                                                      {
//                                                          UIMainLayer::gUIMainLayer->pushLayer(UITaskInfoLayer::create());
//                                                      }), NULL));
    return true;
}

void UIWidgetTaskLayer::setImage(const string &img1, const string &img2)
{
    CocosHelper::loadTexture(Image_1, img1);
    CocosHelper::loadTexture(Image_2, img2);
}

void UIWidgetTaskLayer::setHandldAction(function<void ()> func)
{
    Image_1->stopAllActions();
    Image_2->stopAllActions();
    
    auto it = DelayTime::create(CCRANDOM_0_1());
    
    if (mActionIndex == 0)
    {
        Image_1->runAction(Sequence::create(MoveTo::create(0.3f, Point(0, -350)), it, CallFunc::create(func), NULL));
        Image_2->runAction(Sequence::create(MoveTo::create(0.3f, Point(0, 0)), NULL));
        mActionIndex = 1;
    }
    else
    {
        Image_1->runAction(Sequence::create(MoveTo::create(0.3f, Point(0, 0)), it, CallFunc::create(func), NULL));
        Image_2->runAction(Sequence::create(MoveTo::create(0.3f, Point(0, 350)), NULL));
        mActionIndex = 0;
    }
}