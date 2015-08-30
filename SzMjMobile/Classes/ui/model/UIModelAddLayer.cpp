//  UIAddModelLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#include "UIModelAddLayer.h"
#include "UISpecialInputLayer.h"
#include "UIMediaVideoLayer.h"
#include "UIMainLayer.h"

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
    
    //模特头像
    mImageAvatar = ImageView::create();
    
    Layout *modelAvatarPanel = (Layout*)CocosHelper::getNodeByName(mLayout, "PanelAvatar");
    
    //模特头像的遮罩
    mAvatarClipping = ClippingNode::create();
    mAvatarClipping->setAnchorPoint(Point(0, 0));
    mAvatarClipping->setPosition(220, 220);
    DrawNode *shap = DrawNode::create();
    //shap->drawSolidRect(Point(0, 0), Point(300, 300), Color4F(0, 0, 0, 0));
    //shap->drawDot(Vec2(150, 150), 150, Color4F(0, 0, 0, 0));
    shap->drawSolidCircle(Vec2(0, 0), 150, M_PI * 2, 50, 1.0, 1.0, Color4F(0, 0, 0, 0));
    //shap->setPosition(Point(-150, -150));
    shap->setAnchorPoint(Point(0, 0));
    mAvatarClipping->setStencil(shap);
    mAvatarClipping->setInverted(false);
    modelAvatarPanel->addChild(mAvatarClipping);
    //mAvatarClipping->addChild(ImageView::create("taskList/Task_0_2.png"));
    mAvatarClipping->addChild(mImageAvatar);
    
    //添加多媒体按钮
    mBtnAvatar = (Button*)CocosHelper::getNodeByName(mLayout, "Button_Add");
    mBtnAvatar->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackAvatarBtn, this));
    
    mBtnImage = (ImageView*)CocosHelper::getNodeByName(mLayout, "ModelImage");
    mBtnImage->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackImageBtn, this));
    
    mBtnVideo = (ImageView*)CocosHelper::getNodeByName(mLayout, "ModelVideo");
    mBtnVideo->addTouchEventListener(CC_CALLBACK_2(UIModelAddLayer::CallbackVideoBtn, this));
    
    //模特信息
    Layout *modelBaseInfo = (Layout*)CocosHelper::getNodeByName(mLayout, "PanelModelBaseInfo");
    
    UISpecialInputLayer *nickname = UISpecialInputLayer::create();
    nickname->InitUI("昵称", "请输入6-16位昵称", "昵称非法", ui::EditBox::InputMode::ANY, UISpecialInputLayer::InputType::ANY);
    nickname->setPosition(Vec2(268.5, 268 + 64));
    modelBaseInfo->addChild((Node*)nickname);
    
    UISpecialInputLayer *birthday = UISpecialInputLayer::create();
    birthday->InitUI("生日", "1993/01/03", "必须为8位数字", ui::EditBox::InputMode::NUMERIC, UISpecialInputLayer::InputType::BIRTHDAY);
    birthday->setPosition(Vec2(810, 268 + 64));
    modelBaseInfo->addChild((Node*)birthday);
    
    UISpecialInputLayer *height = UISpecialInputLayer::create();
    height->InitUI("身高", "170cm", "身高非法", ui::EditBox::InputMode::NUMERIC, UISpecialInputLayer::InputType::HEIGHT);
    height->setPosition(Vec2(268.5, 136 + 64));
    modelBaseInfo->addChild((Node*)height);
    
    UISpecialInputLayer *bhw = UISpecialInputLayer::create();
    bhw->InitUI("三围", "90B/70/90", "必须为6位数字", ui::EditBox::InputMode::NUMERIC, UISpecialInputLayer::InputType::BHW);
    bhw->setPosition(Vec2(810, 136 + 64));
    modelBaseInfo->addChild((Node*)bhw);
    
    UISpecialInputLayer *tel = UISpecialInputLayer::create();
    tel->InitUI("电话", "111-1111-1111", "必须为11位数字", ui::EditBox::InputMode::NUMERIC, UISpecialInputLayer::InputType::TEL);
    tel->setPosition(Vec2(1080 * 0.5, 130 * 0.5));
    modelBaseInfo->addChild((Node*)tel);
    
    //提交按钮
    Button *btnTiJiao = (Button*)CocosHelper::getNodeByName(mLayout, "Button_TiJiao");
    btnTiJiao->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->popLayer();
         }
     }
    );
}

//添加照片
void UIModelAddLayer::AddImage(string imagePath)
{
    if(imagePath == "")
        return;
    
    if(mState == 0)
    {
        mBtnImage->loadTexture(imagePath);
    }
    else if(mState == 1)
    {
        mBtnAvatar->setOpacity(0);//设置透明度
        
        mImageAvatar->loadTexture(imagePath);
        mImageAvatar->setScale(300 / mImageAvatar->getContentSize().width, 300 / mImageAvatar->getContentSize().height);
    }
}

//添加视频
void UIModelAddLayer::AddVideo(UIImageStruct imageStruct)
{
    if(imageStruct.file == "")
        return;
    
    Layout *videoPanel = (Layout*)CocosHelper::getNodeByName(mLayout, "PanelVideo");
    Size panelSize = videoPanel->getContentSize();
    
    UIMediaVideoLayer *videoLayer = UIMediaVideoLayer::create();
    videoLayer->setVideoFile(imageStruct.file);
    videoLayer->setContentSize(panelSize);
    
    videoPanel->addChild(videoLayer);
}

//添加头像
void UIModelAddLayer::CallbackAvatarBtn(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        mState = 1;//添加头像
        UIMediaSelectLayer *select =UIMediaSelectLayer::create();
        select->setSelectCallFunc
        (
         [this](vector<UIImageStruct> files)
         {
             for(int i=0; i<files.size(); i++)
             {
                 UIImageStruct temp = files.at(i);
                 this->AddImage(temp.file);
             }
         }
         );
    }
}

//添加照片
void UIModelAddLayer::CallbackImageBtn(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        mState = 0;//添加照片
        UIMediaSelectLayer *select =UIMediaSelectLayer::create();
        select->setSelectCallFunc
        (
         [this](vector<UIImageStruct> files)
         {
             for(int i=0; i<files.size(); i++)
             {
                 UIImageStruct temp = files.at(i);
                 this->AddImage(temp.file);
             }
         }
         );
    }
}

//添加视频
void UIModelAddLayer::CallbackVideoBtn(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        mState = 2;//添加视频
        UIMediaSelectLayer *select =UIMediaSelectLayer::create();
        select->setSelectCallFunc
        (
         [this](vector<UIImageStruct> files)
         {
             for(int i=0; i<files.size(); i++)
             {
                 UIImageStruct temp = files.at(i);
                 this->AddVideo(temp);
             }
         }
         );
    }
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
