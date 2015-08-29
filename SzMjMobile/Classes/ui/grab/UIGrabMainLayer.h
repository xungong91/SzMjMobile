//
//  UIGraboMainLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#ifndef __SzMjMobile__UIGraboMainLayer__
#define __SzMjMobile__UIGraboMainLayer__

#include "UIBaseCenterLayer.h"

using namespace cocos2d::ui;

class UIGrabMainLayer : public UIBaseCenterLayer
{
public:
    CREATE_FUNC(UIGrabMainLayer);
    bool init();
    
private:
    void onInfoTouch(Ref *sender, Widget::TouchEventType type);
    void onModelInfoTouch(Ref *sender, Widget::TouchEventType type);
};

#endif /* defined(__SzMjMobile__UIGraboMainLayer__) */
