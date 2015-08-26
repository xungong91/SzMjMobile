//  UIAddModelLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#ifndef _UIModelAddLayer_h_
#define _UIModelAddLayer_h_

#include "UIBaseTopLayer.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class UIModelAddLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIModelAddLayer);
    virtual bool init();
    
private:
    void InitUI();
    
    //标签按钮响应事件
    void CallbackBiaoQianBtn(Ref *sender, Widget::TouchEventType type);
    //任务按钮响应事件
    void CallbackTaskBtn(Ref *sender, Widget::TouchEventType type);
    
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
};

#endif
