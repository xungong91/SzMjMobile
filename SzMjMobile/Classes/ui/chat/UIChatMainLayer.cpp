//  UIChatMainLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#include "UIChatMainLayer.h"
#include "UIMainLayer.h"
#include "UIChatLayer.h"

bool UIChatMainLayer::init()
{
    if(!UIBaseTopLayer::init())
        return false;

    InitUI();
    
    return true;
}

//初始化UI
void UIChatMainLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_chat.csb", this);
    
    //给第一个添加事件
    Button *btnChat01 = (Button*)CocosHelper::getNodeByName(mLayout, "Button_4");
    btnChat01->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIChatLayer::create());
         }
     }
    );
}