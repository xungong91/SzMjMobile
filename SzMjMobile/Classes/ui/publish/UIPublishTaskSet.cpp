//  UIPublishTaskSet.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#include "UIPublishTaskSet.h"
#include "UIMediaSelectLayer.h"

bool UIPublishTaskSet::init()
{
    if(!UIBaseTopLayer::init())
        return false;

    InitUI();
    
    return true;
}

//初始化UI
void UIPublishTaskSet::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_publish_taskSet.csb", this);
    
    //模特照片
    Layout *modelImagePanel = (Layout*)CocosHelper::getNodeByName(mLayout, "Panel_image");
    
    mImage = ImageView::create();
    //mImage->loadTexture("publish/Publish_UploadImage.png");
    mImage->setPosition(Vec2(1080*0.5, 594*0.5));
    modelImagePanel->addChild(mImage);
    
    //添加模特照片按钮及响应事件
    Button *btnAdd = (Button*)CocosHelper::getNodeByName(mLayout, "Button_upload");
    btnAdd->addTouchEventListener
    (
     [this](Ref *sender, Widget::TouchEventType type)
     {
         if(type == Widget::TouchEventType::ENDED)
         {
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
    );
    
    //动画处的按钮
    mBtnTask = (Button*)CocosHelper::getNodeByName(mLayout, "Button_1");
    mBtnTask->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtnTask, this));
    mBtnAddress = (Button*)CocosHelper::getNodeByName(mLayout, "Button_2");
    mBtnPerson = (Button*)CocosHelper::getNodeByName(mLayout, "Button_3");
    mBtnCommerce = (Button*)CocosHelper::getNodeByName(mLayout, "Button_4");
    mBtnWuChang = (Button*)CocosHelper::getNodeByName(mLayout, "Button_5");
    mBtnHanKou = (Button*)CocosHelper::getNodeByName(mLayout, "Button_6");
    mBtnHanYang = (Button*)CocosHelper::getNodeByName(mLayout, "Button_7");
    
    //列表动画
    mListView = static_cast<ListView*>(CocosHelper::getNodeByName(mLayout, "ListView_main"));
    mPanel = CocosHelper::getWidgetByName(mLayout, "Panel_renWuDiDian");
    mBase = CocosHelper::getWidgetByName(mLayout, "Image_base");
    mTask = CocosHelper::getWidgetByName(mLayout, "Image_renWu");
    mTask->setScaleY(0);
    mAddress = CocosHelper::getWidgetByName(mLayout, "Image_diDian");
    mAddress->setScaleY(0);
    
    this->schedule(CC_CALLBACK_1(UIPublishTaskSet::UpdateList, this), "updateList");
}

//添加照片
void UIPublishTaskSet::AddImage(string imagePath)
{
    if(imagePath == "")
        return;
    
    mImage->loadTexture(imagePath);
    mImage->setScale(1080 / mImage->getContentSize().width, 594 / mImage->getContentSize().height);
}

//展开动画
void UIPublishTaskSet::Open()
{
    mTask->stopAllActions();
    mTask->runAction(Sequence::create(ScaleTo::create(0.3, 1, 1), NULL));
}

//收起动画
void UIPublishTaskSet::Close()
{
    mTask->stopAllActions();
    mTask->runAction(Sequence::create(ScaleTo::create(0.3, 1, 0), NULL));
}

void UIPublishTaskSet::UpdateList(float dt)
{
    float height = 135 * mTask->getScaleY();
    mPanel->setContentSize(Size(1080, 135 + height));
    mBase->setPosition(Point(0, height));
    mListView->refreshView();
}

//任务按钮事件
void UIPublishTaskSet::CallbackBtnTask(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        Open();
    }
}