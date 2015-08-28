//
//  UIIncomeModelLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIIncomeModelLayer.h"
#include "UIWidgetTaskLayer.h"

bool UIIncomeModelLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_incomeModel.csb", this);
    
    Image_main = static_cast<ImageView*>(CocosHelper::getNodeByName(mLayout, "Image_main"));
    
    setTask();
    runTaskAction();
    return true;
}

void UIIncomeModelLayer::setTitle(const string &title)
{
    Text *text = Text::create();
    text->setString(title);
    text->setFontSize(50);
    text->setColor(Color3B::WHITE);
    text->setPosition(Point(540, 1790));
    this->addChild(text, 2);
}

void UIIncomeModelLayer::setTask()
{
    vector<string> imageFiles =
    {
        "taskList/Task_1_1.png",
        "taskList/Task_0_1.png",
        "taskList/Task_2_1.png",
        
        "taskList/Task_3_1.png",
        "taskList/Task_6_1.png",
        "taskList/Task_5_1.png",
        
        "taskList/Task_4_1.png",
        "taskList/Task_0_1.png",
        "taskList/Task_7_1.png"
    };
    
    vector<float> ys =
    {
        1006.0f,
        523.0f,
        40.0f,
    };
    
    vector<float> xs=
    {
        5.0f,
        365.0f,
        725.0f,
    };
    
    
    for (int i = 0; i < 9; ++i)
    {
        string img1 = __String::createWithFormat("income/task_inconme%d.png", i % 3)->getCString();
        Point p(xs[i % 3], ys[i / 3]);
        
        UIWidgetTaskLayer *temp = UIWidgetTaskLayer::create();
        temp->setImage(img1, imageFiles[i]);
        temp->setPosition(p);
        Image_main->addChild(temp);
        
        mTaskLayers.push_back(temp);
    }
}

void UIIncomeModelLayer::runTaskAction()
{
    int index = CCRANDOM_0_1() * mTaskLayers.size();
    static_cast<UIWidgetTaskLayer*>(mTaskLayers[index])->setHandldAction([this]()
                                                                         {
                                                                             runTaskAction();
                                                                         });
}





