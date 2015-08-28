//
//  UIIncomeModelLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIIncomeModelLayer.h"

bool UIIncomeModelLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_incomeModel.csb", this);
    
    return true;
}

void UIIncomeModelLayer::setTitle(const string &title)
{
    Text *text = Text::create();
    text->setString(title);
    text->setFontSize(50);
    text->setColor(Color3B::WHITE);
    text->setPosition(Point(540, 1790));
    this->addChild(text, 2);
}