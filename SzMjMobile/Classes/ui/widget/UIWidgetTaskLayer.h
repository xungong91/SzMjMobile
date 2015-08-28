//
//  UIWidgetTaskLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#ifndef __SzMjMobile__UIWidgetTaskLayer__
#define __SzMjMobile__UIWidgetTaskLayer__

#include "UIBaseLayer.h"

class UIWidgetTaskLayer : public UIBaseLayer
{
public:
    CREATE_FUNC(UIWidgetTaskLayer);
    bool init();
    
    void setImage(const string &img1, const string &img2);
};

#endif /* defined(__SzMjMobile__UIWidgetTaskLayer__) */
