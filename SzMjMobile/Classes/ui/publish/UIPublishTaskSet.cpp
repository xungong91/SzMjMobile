//  UIPublishTaskSet.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#include "UIPublishTaskSet.h"
#include "UIMediaSelectLayer.h"

//0为初始状态（未按下），1为按下，2为已选择
static int mTastBtnState = 0;
static int mAddressBtnState = 0;

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
    
    //价格文本
    Layout *pricePanle = (Layout*)CocosHelper::getNodeByName(mLayout, "Panel_price");
    
    mPriceLabel = Text::create();
    mPriceLabel->setFontSize(48);
    mPriceLabel->setColor(Color3B(0, 0, 0));
    mPriceLabel->setString("预设底价为1000MB");
    mPriceLabel->setPosition(Vec2(1080*0.5, 100));
    pricePanle->addChild(mPriceLabel);
    
    mBtnJia = (Button*)CocosHelper::getNodeByName(mLayout, "Button_jia");
    mBtnJia->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtnJiaJian, this));
    mBtnJian = (Button*)CocosHelper::getNodeByName(mLayout, "Button_jian");
    mBtnJian->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtnJiaJian, this));
    
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
    mBtnTask->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtn1, this));
    mBtnAddress = (Button*)CocosHelper::getNodeByName(mLayout, "Button_2");
    mBtnAddress->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtn1, this));
    mBtnPerson = (Button*)CocosHelper::getNodeByName(mLayout, "Button_3");
    mBtnPerson->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtn2, this));
    mBtnCommerce = (Button*)CocosHelper::getNodeByName(mLayout, "Button_4");
    mBtnCommerce->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtn2, this));
    mBtnWuChang = (Button*)CocosHelper::getNodeByName(mLayout, "Button_5");
    mBtnWuChang->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtn2, this));
    mBtnHanKou = (Button*)CocosHelper::getNodeByName(mLayout, "Button_6");
    mBtnHanKou->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtn2, this));
    mBtnHanYang = (Button*)CocosHelper::getNodeByName(mLayout, "Button_7");
    mBtnHanYang->addTouchEventListener(CC_CALLBACK_2(UIPublishTaskSet::CallbackBtn2, this));
    
    //列表动画
    mListView = static_cast<ListView*>(CocosHelper::getNodeByName(mLayout, "ListView_main"));
    mPanel = CocosHelper::getWidgetByName(mLayout, "Panel_renWuDiDian");
    mPanelMove = CocosHelper::getWidgetByName(mLayout, "Panel_Move");
    mPanelMove->setScaleY(0);
    mBase = CocosHelper::getWidgetByName(mLayout, "Panel_base");
    mTask = CocosHelper::getWidgetByName(mLayout, "Image_renWu");
    mTask->setVisible(false);
    mAddress = CocosHelper::getWidgetByName(mLayout, "Image_diDian");
    mAddress->setVisible(false);
    
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
    mPanelMove->stopAllActions();
    mPanelMove->runAction(Sequence::create(ScaleTo::create(0.3, 1, 1), NULL));
}

//收起动画
void UIPublishTaskSet::Close()
{
    mPanelMove->stopAllActions();
    mPanelMove->runAction(Sequence::create(ScaleTo::create(0.3, 1, 0), NULL));
}

void UIPublishTaskSet::UpdateList(float dt)
{
    float height = 135 * mPanelMove->getScaleY();
    mPanel->setContentSize(Size(1080, 135 + height));
    mBase->setPosition(Point(0, height));
    mListView->refreshView();
}

//加减按钮事件
void UIPublishTaskSet::CallbackBtnJiaJian(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        if(sender == mBtnJia)
        {
            mPrice += 100;
        }
        else if(sender == mBtnJian)
        {
            if(mPrice>=100)
                mPrice -= 100;
        }
        string temp;
        stringstream ss;
        ss<<mPrice;
        ss>>temp;
        mPriceLabel->setString(temp + "MB");
    }
}

//2级按钮事件
void UIPublishTaskSet::CallbackBtn2(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        if(sender == mBtnPerson)
        {
            mTastBtnState = 2;
            mBtnTask->loadTextures("publish/Publish_Person.png", "publish/Publish_Person.png");
            mBtnTask->setPressedActionEnabled(true);
            
            Close();
        }
        else if(sender == mBtnCommerce)
        {
            mTastBtnState = 2;
            mBtnTask->loadTextures("publish/Publish_Commerce.png", "publish/Publish_Commerce.png");
            mBtnTask->setPressedActionEnabled(true);
            
            Close();
        }
        else if(sender == mBtnWuChang)
        {
            mAddressBtnState = 2;
            mBtnAddress->loadTextures("publish/Publish_WuChang.png", "publish/Publish_WuChang.png");
            mBtnAddress->setPressedActionEnabled(true);
            
            Close();
        }
        else if(sender == mBtnHanKou)
        {
            mAddressBtnState = 2;
            mBtnAddress->loadTextures("publish/Publish_HanKou.png", "publish/Publish_HanKou.png");
            mBtnAddress->setPressedActionEnabled(true);
            
            Close();
        }
        else if(sender == mBtnHanYang)
        {
            mAddressBtnState = 2;
            mBtnAddress->loadTextures("publish/Publish_HanYang.png", "publish/Publish_HanYang.png");
            mBtnAddress->setPressedActionEnabled(true);
            
            Close();
        }
    }
}

//1级按钮事件
void UIPublishTaskSet::CallbackBtn1(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        if(sender == mBtnTask)
        {
            mTastBtnState = 1;
            mTask->setVisible(true);
            mAddress->setVisible(false);
            mBtnTask->loadTextures("publish/Publish_Task_1.png", "publish/Publish_Task_1.png");
            mBtnTask->setPressedActionEnabled(false);
            
            //如果此时地点按钮也是按下状态，则弹起
            if(mAddressBtnState == 1)
            {
                mAddressBtnState = 0;
                mBtnAddress->loadTextures("publish/Publish_Address_0.png", "publish/Publish_Address_0.png");
                mBtnAddress->setPressedActionEnabled(true);
            }
            else
                Open();
        }
        else if(sender == mBtnAddress)
        {
            mAddressBtnState = 1;
            mTask->setVisible(false);
            mAddress->setVisible(true);
            mBtnAddress->loadTextures("publish/Publish_Address_1.png", "publish/Publish_Address_1.png");
            mBtnAddress->setPressedActionEnabled(false);
            
            //如果此时任务按钮也是按下状态，则弹起
            if(mTastBtnState == 1)
            {
                mTastBtnState = 0;
                mBtnTask->loadTextures("publish/Publish_Task_0.png", "publish/Publish_Task_0.png");
                mBtnTask->setPressedActionEnabled(true);
            }
            else
                Open();
        }
    }
}