//
//  UIManageEditlLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#ifndef __SzMjMobile__UIManageEditlLayer__
#define __SzMjMobile__UIManageEditlLayer__

#include "UIBaseCenterLayer.h"

using namespace cocos2d::ui;

class UIManageEditlLayer : public UIBaseCenterLayer
{
public:
    CREATE_FUNC(UIManageEditlLayer);
    bool init();
    
    void setModelTouch(function<void ()> func)
    {
        mModelTouchFunc = func;
    }
    
private:
    function<void ()> mModelTouchFunc;
};

#endif /* defined(__SzMjMobile__UIManageEditlLayer__) */
