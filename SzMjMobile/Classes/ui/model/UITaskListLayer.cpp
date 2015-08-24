//  UITaskListLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/24

#include "UITaskListLayer.h"

UITaskListLayer::UITaskListLayer()
{
}

UITaskListLayer::~UITaskListLayer()
{
}

bool UITaskListLayer::init()
{
    if(!UIBaseCenterLayer::init())
        return false;

    InitUI();
    
    return true;
}

//初始化UI
void UITaskListLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_model_list.csb", this);
}