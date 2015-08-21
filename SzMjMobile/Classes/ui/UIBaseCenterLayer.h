//
//  UIBaseCenterLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#ifndef __SzMjMobile__UIBaseCenterLayer__
#define __SzMjMobile__UIBaseCenterLayer__

#include "UIBaseLayer.h"

class UIBaseCenterLayer : public NodeGrid
{
public:
    UIBaseCenterLayer();
    virtual ~UIBaseCenterLayer();
    CREATE_FUNC(UIBaseCenterLayer);
    bool init();
    
protected:
    Node *mLayout;
};

#endif /* defined(__SzMjMobile__UIBaseCenterLayer__) */
