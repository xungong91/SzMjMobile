//  UIPublishTaskSet.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#ifndef _UIPublishTaskSet_h_
#define _UIPublishTaskSet_h_

#include "UIBaseTopLayer.h"

class UIPublishTaskSet : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIPublishTaskSet);
    bool init();
    
private:
    void InitUI();
    
private:
    //添加照片
    ImageView *mImageAvatar;
};

#endif
