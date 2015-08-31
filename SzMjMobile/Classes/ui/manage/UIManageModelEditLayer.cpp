//
//  UIManageModelEditLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIManageModelEditLayer.h"
#include "UIWidgetMsgSprite.h"
#include "UIMediaSelectLayer.h"

bool UIManageModelEditLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_manageModelEdit.csb", this);
    
    Panel_model = CocosHelper::getWidgetByName(mLayout, "Panel_model");
    Text_pageCount = static_cast<Text*>(CocosHelper::getNodeByName(mLayout, "Text_pageCount"));
    
    PageView *PageView_model = static_cast<PageView*>(CocosHelper::getNodeByName(mLayout, "PageView_model"));
    PageView_model->addEventListener
    (
     [PageView_model, this](Ref* sender, PageView::EventType type)
     {
         Text_pageCount->setString(__String::createWithFormat("%zd/%zd", PageView_model->getCurPageIndex() + 1, PageView_model->getPages().size())->getCString());
         if (Panel_model->getPosition().y != -500)
         {
             Panel_model->stopAllActions();
             Panel_model->runAction(Sequence::create(MoveTo::create(0.3f, Point(0, -500)), NULL));
         }
     });
    
    CocosHelper::getWidgetByName(mLayout, "Panel_media0")->addTouchEventListener
    ([](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             auto it = UIMediaSelectLayer::create();
             it->setSelectCallFunc
             ([sender](vector<UIImageStruct> files)
              {
                  ImageView *image = static_cast<ImageView*>(static_cast<Widget*>(sender)->getChildByName("Image"));
                  CocosHelper::loadTexture(image, files[0].file);
                  image->setScale(205 / image->getContentSize().width, 205 / image->getContentSize().height);
                  image->setVisible(true);
              });
         }
     });
    
    for (int i = 0; i < 6; ++i)
    {
        Widget *temp = CocosHelper::getWidgetByName(mLayout, __String::createWithFormat("Panel_media%d", i)->getCString());
        temp->addTouchEventListener(CC_CALLBACK_2(UIManageModelEditLayer::onPanelMediasImageTouch, this));
        
        CocosHelper::getWidgetByName(temp, "Button_close")->addTouchEventListener(CC_CALLBACK_2(UIManageModelEditLayer::onPanelMediasCloseTouch, this));
        mPanelMedias.push_back(temp);
    }
    
    return true;
}

void UIManageModelEditLayer::onEnter()
{
    UIBaseTopLayer::onEnter();
    
    mEventListenerChange = EventListenerTouchOneByOne::create();
    mEventListenerChange->onTouchBegan = [this](Touch* touch, Event  *event)
    {
        mTouchBeganPoint = touch->getLocation();
        if (Panel_model->getBoundingBox().containsPoint(mTouchBeganPoint))
        {
            mPanelModelStartPoint = Panel_model->getPosition();
            return true;
        }
        
        return false;
    };
    
    mEventListenerChange->onTouchMoved = [this](Touch* touch, Event  *event)
    {
        Point location = touch->getLocation();
        float y = location.y - mTouchBeganPoint.y + mPanelModelStartPoint.y;
        if (y > 0 || y < -500)
        {
            Panel_model->setPosition(Point(0, y > 0 ? 0 : -500));
            return;
        }
        
        Panel_model->setPosition(Point(0, y));
    };
    
    mEventListenerChange->onTouchEnded = [this](Touch* touch, Event  *event)
    {
        Point location = touch->getLocation();
        float y = location.y - mTouchBeganPoint.y + mPanelModelStartPoint.y;
        if (y > 0 || y < -500)
        {
            Panel_model->setPosition(Point(0, y > 0 ? 0 : -500));
            return;
        }
        
        Panel_model->setPosition(Point(0, y));
        onPanelModelEnd();
    };
    _eventDispatcher->addEventListenerWithFixedPriority(mEventListenerChange, -1);
}

void UIManageModelEditLayer::onExit()
{
    _eventDispatcher->removeEventListener(mEventListenerChange);
    UIBaseTopLayer::onExit();
}

void UIManageModelEditLayer::onPanelModelEnd()
{
    if (Panel_model->getPosition().y > 0)
    {
        Panel_model->stopAllActions();
        Panel_model->runAction(Sequence::create(MoveTo::create(0.3f, Point(0, 0)), NULL));
    }
    else if (Panel_model->getPosition().y < -500)
    {
        Panel_model->stopAllActions();
        Panel_model->runAction(Sequence::create(MoveTo::create(0.3f, Point(0, -500)), NULL));
    }
}

void UIManageModelEditLayer::onPanelMediasImageTouch(Ref *sender, Widget::TouchEventType type)
{
    if ( type == Widget::TouchEventType::ENDED)
    {
        Widget *temp = static_cast<Widget*>(sender);
        ImageView *image = static_cast<ImageView*>(temp->getChildByName("Image"));
        Widget *Button_close = static_cast<ImageView*>(temp->getChildByName("Button_close"));
        Text *text = static_cast<Text*>(temp->getChildByName("Text"));
        
        if (!image->isVisible())
        {
            auto it = UIMediaSelectLayer::create();
            it->setMaxSelectCount(1);
            it->setSelectCallFunc
            ([image, Button_close, text](vector<UIImageStruct> files)
             {
                 string fileName;
                 if (files.size() > 0)
                 {
                     if (files[0].type == UIMediaType::image)
                     {
                         fileName = files[0].file;
                     }
                     else if (files[0].type == UIMediaType::video)
                     {
                         fileName = files[0].file.substr(0, files[0].file.find(".")) + ".jpg";
                     }
                 }
                 else
                 {
                     return;
                 }
                 
                 CocosHelper::loadTexture(image, fileName);
                 image->setScale(200 / image->getContentSize().width, 200 / image->getContentSize().height);
                 image->setVisible(true);
                 
                 Button_close->setVisible(true);
                 text->setString("待审核");
                 text->setVisible(true);
                 text->setColor(Color3B(34, 34, 34));
             });
        }
    }
}

void UIManageModelEditLayer::onPanelMediasVideoTouch(Ref *sender, Widget::TouchEventType type)
{
    if ( type == Widget::TouchEventType::ENDED)
    {
        
    }
}

void UIManageModelEditLayer::onPanelMediasCloseTouch(Ref *sender, Widget::TouchEventType type)
{
    if ( type == Widget::TouchEventType::ENDED)
    {
        Widget *temp = static_cast<Widget*>(sender);
        CocosHelper::getWidgetByName(temp->getParent(), "Image")->setVisible(false);
        CocosHelper::getWidgetByName(temp->getParent(), "Text")->setVisible(false);
        temp->setVisible(false);
    }
}















