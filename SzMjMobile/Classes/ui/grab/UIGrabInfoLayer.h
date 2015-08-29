//
//  UIGrabInfoLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#ifndef __SzMjMobile__UIGrabInfoLayer__
#define __SzMjMobile__UIGrabInfoLayer__

#include "UIBaseTopLayer.h"

class UIGrabInfoLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIGrabInfoLayer);
    bool init();
    
private:
    Text *Text_select;
    vector<bool> mSelects;
    vector<ImageView*> mImages;
    
    void setSelectInfo();
    void onImageTouch(Ref *sender, Widget::TouchEventType type);
};

#endif /* defined(__SzMjMobile__UIGrabInfoLayer__) */
