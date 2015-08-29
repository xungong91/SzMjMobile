//  UIPublishTaskInfo.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/28

#include "UIPublishTaskInfo.h"
#include "UIMediaSelectLayer.h"
#include "UIMainLayer.h"

bool UIPublishTaskInfo::init()
{
    if(!UIBaseTopLayer::init())
        return false;

    InitUI();
    
    return true;
}

//初始化UI
void UIPublishTaskInfo::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_publish_taskInfo.csb", this);
    
    //两个删除按钮
    ImageView *image1 = (ImageView*)CocosHelper::getNodeByName(mLayout, "Image_5");
    Text *text1 = (Text*)CocosHelper::getNodeByName(mLayout, "Text_4");
    Button *btnClose1 = (Button*)CocosHelper::getNodeByName(mLayout, "BtnClose1");
    btnClose1->addTouchEventListener
    (
     [image1, text1, btnClose1](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
             image1->setVisible(false);
             text1->setVisible(false);
             btnClose1->setVisible(false);
         }
     }
    );
    
    ImageView *image2 = (ImageView*)CocosHelper::getNodeByName(mLayout, "Image_6");
    Text *text2 = (Text*)CocosHelper::getNodeByName(mLayout, "Text_5");
    Button *btnClose2 = (Button*)CocosHelper::getNodeByName(mLayout, "BtnClose2");
    btnClose2->addTouchEventListener
    (
     [image2, text2, btnClose2](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
             image2->setVisible(false);
             text2->setVisible(false);
             btnClose2->setVisible(false);
         }
     }
     );
    
    //添加头像按钮
    Button *btnAdd = (Button*)CocosHelper::getNodeByName(mLayout, "Button_Add");
    btnAdd->addTouchEventListener
    (
     [this](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
              //this->addChild(UIMediaSelectLayer::create());
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
             //UIMainLayer::gUIMainLayer->pushLayer(select);
         }
     }
    );
    
    //模特头像
    mImageAvatar = ImageView::create();
    
    Layout *modelAvatarPanel = (Layout*)CocosHelper::getNodeByName(mLayout, "Panel_ShenHe");
    
    //模特头像的遮罩
    mAvatarClipping = ClippingNode::create();
    mAvatarClipping->setPosition(189, 309);
    DrawNode *shap = DrawNode::create();
    shap->drawSolidRect(Point(0, 0), Point(344, 340), Color4F(0, 0, 0, 0));
    shap->setPosition(Vec2(-344*0.5, -170));
    mAvatarClipping->setStencil(shap);
    mAvatarClipping->setInverted(false);
    modelAvatarPanel->addChild(mAvatarClipping);
    //mAvatarClipping->addChild(ImageView::create("taskList/Task_0_2.png"));
    mAvatarClipping->addChild(mImageAvatar);
}

//添加照片
void UIPublishTaskInfo::AddImage(string imagePath)
{
    if(imagePath == "")
        return;
    
    mImageAvatar->loadTexture(imagePath);
    mImageAvatar->setScale(344 / mImageAvatar->getContentSize().width, 340 / mImageAvatar->getContentSize().height);
}