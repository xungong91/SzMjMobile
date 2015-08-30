//  UIChatMainLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#include "UIChatMainLayer.h"

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
}