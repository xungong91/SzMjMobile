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
    child11->imageRun();
    child11->setPosition(Vec2(10, 10));
    child11->setStyle(temp.style);
    child11->setMetorName(temp.title);
    model1Panel->addChild(child11);
    
    UIPublishMetroChild *child12 = UIPublishMetroChild::create();
    child12->LoadImages(1);
    child12->setPosition(Vec2(500, 100));
    model1Panel->addChild(child12);
    
    UIPublishMetroChild *child13 = UIPublishMetroChild::create();
    child13->LoadImages(2);
    child13->setPosition(Vec2(900, 100));
    model1Panel->addChild(child13);
    
    //初始化第一个玩家的Metro
    Layout *model2Panel = (Layout*)CocosHelper::getNodeByName(mLayout, "PublishListPanel2");
}