//  UIChatLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#ifndef _UIChatLayer_h_
#define _UIChatLayer_h_

#include "UIBaseTopLayer.h"

class UIChatLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIChatLayer);
    virtual bool init();
    
private:
    void InitUI();
};

#endif
