//
//  UIManageMainLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#ifndef __SzMjMobile__UIManageMainLayer__
#define __SzMjMobile__UIManageMainLayer__

#include "UIBaseCenterLayer.h"
#include "UIManageModelLayer.h"
#include "UIManageEditlLayer.h"

using namespace cocos2d::ui;

class UIManageMainLayer : public UIBaseCenterLayer
{
public:
    CREATE_FUNC(UIManageMainLayer);
    bool init();
    
private:
    UIManageModelLayer *mUIManageModelLayer;
    UIManageEditlLayer *mUIManageEditlLayer;
};

#endif /* defined(__SzMjMobile__UIManageMainLayer__) */
