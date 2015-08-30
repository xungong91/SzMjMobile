//  UITaskInfoLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#include "UITaskInfoLayer.h"
#include "UIMainLayer.h"
#include "UIChatMainLayer.h"

bool UITaskInfoLayer::init()
{
    if (!UIBaseTopLayer::init())
        return false;
    
    InitUI();
    
    return true;
}

//初始化UI
void UITaskInfoLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_task_info.csb", this);
    
    //聊天按钮
    Button *btnTalk = (Button*)CocosHelper::getNodeByName(mLayout, "BtnTalk");
    btnTalk->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIChatMainLayer::create());
         }
     }
    );
}