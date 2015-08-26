//  UIInput.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#include "UIInput.h"

void UIInput::SetScale9Sprite(const Size& size, const std::string& pNormal9SpriteBg)
{
    _backgroundSprite->initWithFile(pNormal9SpriteBg, Rect(0, 0, size.width, size.height));
}