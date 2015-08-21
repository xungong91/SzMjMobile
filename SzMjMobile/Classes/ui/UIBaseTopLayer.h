//
//  UIBaseTopLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#ifndef __SzMjMobile__UIBaseTopLayer__
#define __SzMjMobile__UIBaseTopLayer__

#include "UIBaseLayer.h"

class UIBaseTopLayer : public UIBaseLayer
{
public:
    UIBaseTopLayer();
    virtual ~UIBaseTopLayer();
    CREATE_FUNC(UIBaseTopLayer);
    bool init();
    
protected:
    Node *mTopLayout;
};

#endif /* defined(__SzMjMobile__UIBaseTopLayer__) */
