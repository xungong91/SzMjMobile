//  UIChatMainLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#ifndef _UIChatMainLayer_h_
#define _UIChatMainLayer_h_

#include "UIBaseTopLayer.h"

class UIChatMainLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIChatMainLayer);
    virtual bool init();
    
private:
    void InitUI();
};

#endif
