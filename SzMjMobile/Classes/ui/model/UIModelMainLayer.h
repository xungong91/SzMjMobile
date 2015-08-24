//
//  UIModelMainLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#ifndef __SzMjMobile__UIModelMainLayer__
#define __SzMjMobile__UIModelMainLayer__

#include "UIBaseCenterLayer.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class UIModelMainLayer : public UIBaseCenterLayer
{
public:
    CREATE_FUNC(UIModelMainLayer);
    bool init();
    
private:
    //初始化UI界面
    void InitUI();
    
    //按钮事件
    void CallbackBtnClick(Ref *sender, Widget::TouchEventType type);
    
private:
    Button *mBtnModelList;     //模特列表按钮
    Button *mBtnTaskList;       //任务列表按钮
    
    Layer *mLayerModelList;  //模特列表
    Layer *mLayerTaskList;    //任务列表
};

#endif /* defined(__SzMjMobile__UIModelMainLayer__) */
