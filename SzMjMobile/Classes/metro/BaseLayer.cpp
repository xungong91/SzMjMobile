//
//  BaseLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/13.
//
//

#include "BaseLayer.h"

BaseLayer::BaseLayer()
{
    
}

BaseLayer::~BaseLayer()
{
    
}

bool BaseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}