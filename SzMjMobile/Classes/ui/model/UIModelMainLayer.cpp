//
//  UIModelMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIModelMainLayer.h"
#include "UIMainLayer.h"
#include "UIModelListLayer.h"
#include "UITaskListLayer.h"

bool UIModelMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
        return false;
    
    InitUI();
    
    return true;
}

//初始化UI界面
void UIModelMainLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_model.csb", this);
    
    mBtnModelList = (Button*)CocosHelper::getNodeByName(mLayout, "Button_ModelList");
    mBtnModelList->loadTextures("model/ModelList_1.png", "model/ModelList_1.png");
    mBtnModelList->addTouchEventListener(CC_CALLBACK_2(UIModelMainLayer::CallbackBtnClick, this));
    mBtnModelList->setPressedActionEnabled(false);
    
    mBtnTaskList = (Button*)CocosHelper::getNodeByName(mLayout, "Button_TaskList");
    mBtnTaskList->loadTextures("model/TaskList_0.png", "model/TaskList_1.png");
    mBtnTaskList->addTouchEventListener(CC_CALLBACK_2(UIModelMainLayer::CallbackBtnClick, this));
    mBtnTaskList->setPressedActionEnabled(true);
    
    mLayerModelList = (Layer*)UIModelListLayer::create();
    mLayerModelList->setVisible(true);
    addChild(mLayerModelList);
    
    mLayerTaskList = (Layer*)UITaskListLayer::create();
    mLayerTaskList->setVisible(false);
    addChild(mLayerTaskList);
    
    /*
    CocosHelper::getWidgetByName(mLayout, "Image_1")->addTouchEventListener
    ([](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIModelListLayer::create());
         }
     });
     */
}

//按钮事件
void UIModelMainLayer::CallbackBtnClick(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        if(sender == mBtnModelList)
        {
            mBtnModelList->loadTextures("model/ModelList_1.png", "model/ModelList_1.png");
            mBtnModelList->setPressedActionEnabled(false);
            
            mBtnTaskList->loadTextures("model/TaskList_0.png", "model/TaskList_1.png");
            mBtnTaskList->setPressedActionEnabled(true);
            
            mLayerModelList->setVisible(true);
            mLayerTaskList->setVisible(false);
        }
        else if(sender == mBtnTaskList)
        {
            mBtnModelList->loadTextures("model/ModelList_0.png", "model/ModelList_1.png");
            mBtnModelList->setPressedActionEnabled(true);
            
            mBtnTaskList->loadTextures("model/TaskList_1.png", "model/TaskList_1.png");
            mBtnTaskList->setPressedActionEnabled(false);
            
            mLayerModelList->setVisible(false);
            mLayerTaskList->setVisible(true);
        }
    }
}



