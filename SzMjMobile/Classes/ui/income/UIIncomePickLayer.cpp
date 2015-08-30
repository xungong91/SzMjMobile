//
//  UIIncomePickLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIIncomePickLayer.h"
#include "UIIncomePickRegLayer.h"
#include "UIMainLayer.h"
#include "UIWidgetTaskLayer.h"
#include "UITaskInfoLayer.h"
#include "UIWidgetMsgSprite.h"
#include "UIIncomeSubmitLayer.h"

bool UIIncomePickLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_incomePick.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Button_reg")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIIncomePickRegLayer::create());
         }
     }
     );
    
    CocosHelper::getWidgetByName(mLayout, "Button_tixian")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIIncomeSubmitLayer::create());
         }
     }
     );
    
    ListView_main = static_cast<ListView*>(CocosHelper::getNodeByName(mLayout, "ListView_main"));
    Panel_help = CocosHelper::getWidgetByName(mLayout, "Panel_help");
    Image_help = CocosHelper::getWidgetByName(mLayout, "Image_help");
    Image_1 = CocosHelper::getWidgetByName(mLayout, "Image_1");
    
    Image_help->setScaleY(0);
    
    auto openFunc = [this]()
    {
        Image_help->stopAllActions();
        Image_help->runAction(Sequence::create(ScaleTo::create(0.3, 1, 1), NULL));
    };
    
    auto closeFunc = [this]()
    {
        Image_help->stopAllActions();
        Image_help->runAction(Sequence::create(ScaleTo::create(0.3, 1, 0), NULL));
    };
    
    static bool gIsOpenHelp = false;
    gIsOpenHelp = false;
    
    Button *Button_help = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_help"));
    Button_help->addTouchEventListener
    (
     [Button_help, openFunc, closeFunc](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (!gIsOpenHelp)
             {
                 Button_help->loadTextureNormal("income/btn_qianbao2.png");
                 Button_help->loadTexturePressed("income/btn_qianbao2.png");
                 openFunc();
                 gIsOpenHelp = !gIsOpenHelp;
             }
         }
     }
     );
    
    static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_shouqi"))->addTouchEventListener
    (
     [Button_help, openFunc, closeFunc](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (gIsOpenHelp)
             {
                 Button_help->loadTextureNormal("income/btn_qianbao1.png");
                 Button_help->loadTexturePressed("income/btn_qianbao1.png");
                 closeFunc();
                 gIsOpenHelp = !gIsOpenHelp;
             }
         }
     }
     );
    
    static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_quanbu"))->addTouchEventListener
    (
     [Button_help, openFunc, closeFunc](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIWidgetMsgSprite::setMsg("没有更多内容");
         }
     }
     );
    
    addTask();
    
    this->schedule(CC_CALLBACK_1(UIIncomePickLayer::updateList, this), "updateList");
    
    return true;
}

void UIIncomePickLayer::addTask()
{
    vector<string> imageFiles =
    {
        "taskList/Task_1_1.png",
        "taskList/Task_0_1.png",
        "taskList/Task_2_1.png"
    };
    
    vector<float> xs=
    {
        5.0f,
        365.0f,
        725.0f,
    };
    
    for (int i = 0; i < 3; ++i)
    {
        auto panel = CocosHelper::getWidgetByName(Image_help, __String::createWithFormat("Panel_%d", i)->getCString());
        panel->addTouchEventListener(CC_CALLBACK_2(UIIncomePickLayer::onTaskTouch, this));
        
        string img1 = __String::createWithFormat("income/task_inconme%d.png", i % 3)->getCString();
        
        UIWidgetTaskLayer *temp = UIWidgetTaskLayer::create();
        temp->setImage(img1, imageFiles[i]);
        panel->addChild(temp);
        
        mTaskLayers.push_back(temp);
    }
    
    sethanldAction();
}

void UIIncomePickLayer::sethanldAction()
{
    int index = CCRANDOM_0_1() * mTaskLayers.size();
    static_cast<UIWidgetTaskLayer*>(mTaskLayers[index])->setHandldAction([this]()
                                                                         {
                                                                             sethanldAction();
                                                                         });
}

void UIIncomePickLayer::updateList(float dt)
{
    float height = 590 * Image_help->getScaleY();
    Panel_help->setContentSize(Size(1080, 250 + height));
    Image_1->setPosition(Point(0, height));
    ListView_main->refreshView();
}

void UIIncomePickLayer::onTaskTouch(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        UIMainLayer::gUIMainLayer->pushLayer(UITaskInfoLayer::create());
    }
}
















