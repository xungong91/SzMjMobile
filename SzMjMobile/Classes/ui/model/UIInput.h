//  UIInput.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#ifndef _UIInput_h_
#define _UIInput_h_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class UIInput : public ui::EditBox
{
public:
    void SetScale9Sprite(const Size& size, const std::string& pNormal9SpriteBg);
};

#endif
