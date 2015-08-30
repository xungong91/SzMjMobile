//
//  UIManageModelEditLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIManageModelEditLayer.h"

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
     });
    
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
















