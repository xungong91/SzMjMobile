//
//  UIWidgetTaskLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIWidgetTaskLayer.h"

bool UIWidgetTaskLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_WIDGET_Task.csb", this);
    
    return true;
}

void UIWidgetTaskLayer::setImage(const string &img1, const string &img2)
{
    static_cast<ImageView*>(CocosHelper::getNodeByName(mLayout, "Image_1"))->loadTexture(img1);
    static_cast<ImageView*>(CocosHelper::getNodeByName(mLayout, "Image_1"))->loadTexture(img2);
}