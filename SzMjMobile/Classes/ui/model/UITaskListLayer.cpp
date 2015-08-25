//  UITaskListLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/24

#include "UITaskListLayer.h"
#include "UITaskMetroLayer.h"

UITaskListLayer::UITaskListLayer()
{
}

UITaskListLayer::~UITaskListLayer()
{
}

bool UITaskListLayer::init()
{
    if(!UIBaseCenterLayer::init())
        return false;

    InitUI();
    
    return true;
}

//初始化UI
void UITaskListLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_task_list.csb", this);
    
    Layout *panelTaskList = (Layout*)CocosHelper::getNodeByName(mLayout, "PanelTaskList");
    
    UITaskMetroLayer *taskMetro = UITaskMetroLayer::create();
    //taskMetro->setPosition(Vec2(0, 165));
    panelTaskList->addChild(taskMetro);
    //panelTaskList->setClippingEnabled(true);
}