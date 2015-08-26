//  UITaskInfoLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#include "UITaskInfoLayer.h"

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
}