//  UIAddModelLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#ifndef _UIModelAddLayer_h_
#define _UIModelAddLayer_h_

#include "UIBaseTopLayer.h"

class UIModelAddLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIModelAddLayer);
    virtual bool init();
    
public:
    //添加照片
    void AddImage(string imagePath);
    
private:
    void InitUI();
    
    //标签按钮响应事件
    void CallbackBiaoQianBtn(Ref *sender, Widget::TouchEventType type);
    //任务按钮响应事件
    void CallbackTaskBtn(Ref *sender, Widget::TouchEventType type);
    //添加多媒体按钮响应事件
    void CallbackAvatarBtn(Ref *sender, Widget::TouchEventType type);
    void CallbackImageBtn(Ref *sender, Widget::TouchEventType type);
    void CallbackVideoBtn(Ref *sender, Widget::TouchEventType type);
    
private:
    //标签按钮
    Button *mBtnQingChun;
    Button *mBtnQiaoLi;
    Button *mBtnYouYa;
    Button *mBtnWenYi;
    Button *mBtnGaoGui;

    //任务按钮
    Button *mBtnPerson;
    Button *mBtnCommerce;
    
    //添加多媒体按钮
    int mState;
    ImageView *mImageAvatar;
    ClippingNode *mAvatarClipping;
    Button *mBtnAvatar;
    ImageView *mBtnImage;
    ImageView *mBtnVideo;
};

#endif
