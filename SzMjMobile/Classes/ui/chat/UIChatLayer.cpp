//  UIChatLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#include "UIChatLayer.h"

bool UIChatLayer::init()
{
    if(!UIBaseTopLayer::init())
        return false;
    
    InitUI();
    
    return true;
}

void UIChatLayer::InitUI()
{
}