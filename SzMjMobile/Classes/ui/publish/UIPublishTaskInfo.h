//  UIPublishTaskInfo.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/28

#ifndef _UIPublishTaskInfo_h_
#define _UIPublishTaskInfo_h_

#include "UIBaseTopLayer.h"

class UIPublishTaskInfo : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIPublishTaskInfo);
    bool init();
    
private:
    void InitUI();
    
    void AddImage(string imagePath);
    
private:
    //添加头像
    ImageView *mImageAvatar;
    ClippingNode *mAvatarClipping;
};

#endif
