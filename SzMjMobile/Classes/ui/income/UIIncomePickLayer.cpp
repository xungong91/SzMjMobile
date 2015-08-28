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
    
    ListView_main = static_cast<ListView*>(CocosHelper::getNodeByName(mLayout, "ListView_main"));
    Panel_help = CocosHelper::getWidgetByName(mLayout, "Panel_help");
    Image_help = CocosHelper::getWidgetByName(mLayout, "Image_help");
    Image_1 = CocosHelper::getWidgetByName(mLayout, "Image_1");
    
    Image_help->setScaleY(0);
    
    auto openFunc = [this]()
    {
        Panel_help->setContentSize(Size(1080, 840));
        Image_help->setScaleY(1);
        Image_1->setPosition(Point(0, 590));
        ListView_main->refreshView();
    };
    
    auto closeFunc = [this]()
    {
        Panel_help->setContentSize(Size(1080, 250));
        Image_help->setScaleY(0);
        Image_1->setPosition(Point(0, 0));
        ListView_main->refreshView();
    };
    
    Button *Button_help = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_help"));
    Button_help->addTouchEventListener
    (
     [Button_help, openFunc, closeFunc](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             static bool gIsOpenHelp = false;
             if (gIsOpenHelp)
             {
                 Button_help->loadTextureNormal("income/btn_qianbao1.png");
                 Button_help->loadTexturePressed("income/btn_qianbao1.png");
                 closeFunc();
             }
             else
             {
                 Button_help->loadTextureNormal("income/btn_qianbao2.png");
                 Button_help->loadTexturePressed("income/btn_qianbao2.png");
                 openFunc();
             }
             gIsOpenHelp = !gIsOpenHelp;
         }
     }
     );
    
    addTask();
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
        string img1 = __String::createWithFormat("income/task_inconme%d.png", i % 3)->getCString();
        
        UIWidgetTaskLayer *temp = UIWidgetTaskLayer::create();
        temp->setImage(img1, imageFiles[i]);
        temp->setPosition(Point(xs[i % 3], 145));
        Image_help->addChild(temp);
        
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

















