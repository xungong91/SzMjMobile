//
//  UIManageModelLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#ifndef __SzMjMobile__UIManageModelLayer__
#define __SzMjMobile__UIManageModelLayer__

#include "UIBaseCenterLayer.h"
#include <functional>

using namespace cocos2d::ui;

class UIManageModelLayer : public UIBaseCenterLayer
{
public:
    CREATE_FUNC(UIManageModelLayer);
    bool init();
    
    void setEditTouch(function<void ()> func)
    {
        mEditTouchFunc = func;
    }
    
private:
    function<void ()> mEditTouchFunc;
    
    void onModelTouch(Ref *sender, Widget::TouchEventType type);
};

#endif /* defined(__SzMjMobile__UIManageModelLayer__) */
