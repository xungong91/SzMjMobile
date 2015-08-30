//
//  UIPublishMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIPublishMainLayer.h"
#include "UIPublishMetroChild.h"
#include "MetroSpriteManage.h"
#include "UIMainLayer.h"
#include "UIChatMainLayer.h"

bool UIPublishMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
        return false;
    
    InitUI();
    
    return true;
}

//初始化UI
void UIPublishMainLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_publish.csb", this);
    
    //初始化第一个玩家的Metro
    Layout *model1Panel = (Layout*)CocosHelper::getNodeByName(mLayout, "PublishListPanel1");
    
    MetroInfoStruct temp =
    {
        MetroSpriteStyle::widget2x2,
        MetroSpriteType::image,
        Color4B(240, 148, 0, 255),
        ""
    };
    
    UIPublishMetroChild *child11 = UIPublishMetroChild::create();
    child11->LoadImages(0);
    child11->setPosition(Vec2(15, 10));
    child11->setStyle(temp.style);
    model1Panel->addChild(child11);
    
    UIPublishMetroChild *child12 = UIPublishMetroChild::create();
    child12->LoadImages(1);
    child12->setPosition(Vec2(370, 10));
    child12->setStyle(temp.style);
    model1Panel->addChild(child12);
    
    UIPublishMetroChild *child13 = UIPublishMetroChild::create();
    child13->LoadImages(2);
    child13->setPosition(Vec2(725, 10));
    child13->setStyle(temp.style);
    model1Panel->addChild(child13);
    
    //初始化第一个玩家的Metro
    Layout *model2Panel = (Layout*)CocosHelper::getNodeByName(mLayout, "PublishListPanel2");
    
    UIPublishMetroChild *child21 = UIPublishMetroChild::create();
    child21->LoadImages(2);
    child21->setPosition(Vec2(15, 10));
    child21->setStyle(temp.style);
    model2Panel->addChild(child21);
    
    UIPublishMetroChild *child22 = UIPublishMetroChild::create();
    child22->LoadImages(3);
    child22->setPosition(Vec2(370, 10));
    child22->setStyle(temp.style);
    model2Panel->addChild(child22);
    
    UIPublishMetroChild *child23 = UIPublishMetroChild::create();
    child23->LoadImages(4);
    child23->setPosition(Vec2(725, 10));
    child23->setStyle(temp.style);
    model2Panel->addChild(child23);
    
    //聊天按钮
    Button *btnTalk = (Button*)CocosHelper::getNodeByName(mLayout, "BtnTalk");
    btnTalk->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIChatMainLayer::create());
         }
     }
    );
}