//  UITaskListLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/24

#ifndef _UITaskListLayer_h_
#define _UITaskListLayer_h_

#include "UIBaseCenterLayer.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class UITaskListLayer : public UIBaseCenterLayer
{
public:
    CREATE_FUNC(UITaskListLayer);
    UITaskListLayer();
    virtual ~UITaskListLayer();
    virtual bool init();
    
private:
    //初始化UI
    void InitUI();
};

#endif
