//  UITaskInfoLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#ifndef _UITaskInfoLayer_h_
#define _UITaskInfoLayer_h_

#include "UIBaseTopLayer.h"

class UITaskInfoLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UITaskInfoLayer);
    bool init();
    
private:
    void InitUI();
};

#endif
