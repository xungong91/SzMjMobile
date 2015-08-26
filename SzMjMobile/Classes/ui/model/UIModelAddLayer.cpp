//  UIAddModelLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#include "UIModelAddLayer.h"
#include "UISpecialInputLayer.h"

bool UIModelAddLayer::init()
{
    if(!UIBaseTopLayer::init())
        return false;
    
    InitUI();
    
    return true;
}

//初始化UI
void UIModelAddLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_model_add.csb", this);
    
    //标签按钮
    mBtnQingChun = (Button*)CocosHelper::getNodeByName(mLayout, "Button_QingChun");
    mBtnQingChun->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackBiaoQianBtn, this));
    
    mBtnQiaoLi = (Button*)CocosHelper::getNodeByName(mLayout, "Button_QiaoLi");
    mBtnQiaoLi->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackBiaoQianBtn, this));
    
    mBtnYouYa = (Button*)CocosHelper::getNodeByName(mLayout, "Button_YouYa");
    mBtnYouYa->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackBiaoQianBtn, this));
    
    mBtnWenYi = (Button*)CocosHelper::getNodeByName(mLayout, "Button_WenYiFan");
    mBtnWenYi->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackBiaoQianBtn, this));
    
    mBtnGaoGui = (Button*)CocosHelper::getNodeByName(mLayout, "Button_GaoGui");
    mBtnGaoGui->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackBiaoQianBtn, this));
    
    //任务按钮
    mBtnPerson  = (Button*)CocosHelper::getNodeByName(mLayout, "BtnPerson");
    mBtnPerson->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackTaskBtn, this));
    mBtnPerson->setPressedActionEnabled(false);
    
    mBtnCommerce  = (Button*)CocosHelper::getNodeByName(mLayout, "BtnCommerce");
    mBtnCommerce->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackTaskBtn, this));
    
    //模特信息
    Layout *modelBaseInfo = (Layout*)CocosHelper::getNodeByName(mLayout, "PanelModelBaseInfo");
    
    UISpecialInputLayer *nickname = UISpecialInputLayer::create();
    nickname->setPosition(Vec2(268.5, 268 + 64));
    modelBaseInfo->addChild((Node*)nickname);
    
    UISpecialInputLayer *birthday = UISpecialInputLayer::create();
    birthday->setPosition(Vec2(810, 268 + 64));
    modelBaseInfo->addChild((Node*)birthday);
    
    UISpecialInputLayer *height = UISpecialInputLayer::create();
    height->setPosition(Vec2(268.5, 136 + 64));
    modelBaseInfo->addChild((Node*)height);
    
    UISpecialInputLayer *bhw = UISpecialInputLayer::create();
    bhw->setPosition(Vec2(810, 136 + 64));
    modelBaseInfo->addChild((Node*)bhw);
    
    UISpecialInputLayer *tel = UISpecialInputLayer::create();
    tel->setPosition(Vec2(1080 * 0.5, 130 * 0.5));
    modelBaseInfo->addChild((Node*)tel);
}

//任务按钮的事件
void UIModelAddLayer::CallbackTaskBtn(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        mBtnPerson->loadTextures("addModel/SiRen_0.png", "addModel/SiRen_0.png");
        mBtnPerson->setPressedActionEnabled(true);
        
        mBtnCommerce->loadTextures("addModel/ShangWu_0.png", "addModel/ShangWu_0.png");
        mBtnCommerce->setPressedActionEnabled(true);
        
        if(sender == mBtnPerson)
        {
            mBtnPerson->loadTextures("addModel/SiRen_1.png", "addModel/SiRen_1.png");
            mBtnPerson->setPressedActionEnabled(false);
        }
        else if(sender == mBtnCommerce)
        {
            mBtnCommerce->loadTextures("addModel/ShangWu_1.png", "addModel/ShangWu_1.png");
            mBtnCommerce->setPressedActionEnabled(false);
        }
    }
}

//标签按钮的事件
void UIModelAddLayer::CallbackBiaoQianBtn(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        mBtnQingChun->loadTextures("addModel/AddModel_QingChun_0.png", "addModel/AddModel_QingChun_0.png");
        mBtnQingChun->setPressedActionEnabled(true);
        
        mBtnQiaoLi->loadTextures("addModel/AddModel_QiaoLi_0.png", "addModel/AddModel_QiaoLi_0.png");
        mBtnQiaoLi->setPressedActionEnabled(true);
        
        mBtnYouYa->loadTextures("addModel/AddModel_YouYa_0.png", "addModel/AddModel_YouYa_0.png");
        mBtnYouYa->setPressedActionEnabled(true);
        
        mBtnWenYi->loadTextures("addModel/AddModel_WenYiFan_0.png", "addModel/AddModel_WenYiFan_0.png");
        mBtnWenYi->setPressedActionEnabled(true);
        
        mBtnGaoGui->loadTextures("addModel/AddModel_GaoGui_0.png", "addModel/AddModel_GaoGui_0.png");
        mBtnGaoGui->setPressedActionEnabled(true);
        
        if(sender == mBtnQingChun)
        {
            mBtnQingChun->loadTextures("addModel/AddModel_QingChun_1.png", "addModel/AddModel_QingChun_1.png");
            mBtnQingChun->setPressedActionEnabled(false);
        }
        else if(sender == mBtnQiaoLi)
        {
            mBtnQiaoLi->loadTextures("addModel/AddModel_QiaoLi_1.png", "addModel/AddModel_QiaoLi_1.png");
            mBtnQiaoLi->setPressedActionEnabled(false);
        }
        else if(sender == mBtnYouYa)
        {
            mBtnYouYa->loadTextures("addModel/AddModel_YouYa_1.png", "addModel/AddModel_YouYa_1.png");
            mBtnYouYa->setPressedActionEnabled(false);
        }
        else if(sender == mBtnWenYi)
        {
            mBtnWenYi->loadTextures("addModel/AddModel_WenYiFan_1.png", "addModel/AddModel_WenYiFan_1.png");
            mBtnWenYi->setPressedActionEnabled(false);
        }
        else if(sender == mBtnGaoGui)
        {
            mBtnGaoGui->loadTextures("addModel/AddModel_GaoGui_1.png", "addModel/AddModel_GaoGui_1.png");
            mBtnGaoGui->setPressedActionEnabled(false);
        }
    }
}
