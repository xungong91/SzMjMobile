//
//  UIGrabInfoLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIGrabInfoLayer.h"

bool UIGrabInfoLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_grabInfo.csb", this);
    
    mSelects.assign(7, false);
    
    Text_select = static_cast<Text*>(CocosHelper::getNodeByName(mLayout, "Text_select"));
    
    for (int i = 0; i < 7; ++i)
    {
        ImageView *view = static_cast<ImageView*>(CocosHelper::getNodeByName(mLayout, __String::createWithFormat("Image_model%d", i)->getCString()));
        view->setTag(i);
        view->addTouchEventListener(CC_CALLBACK_2(UIGrabInfoLayer::onImageTouch, this));
        mImages.push_back(view);
    }
    
    setSelectInfo();
    
    return true;
}

void UIGrabInfoLayer::setSelectInfo()
{
    int selectCount(0);
    for (int i = 0; i < mImages.size(); ++i)
    {
        mImages[i]->getChildByName("Image_select")->setVisible(mSelects[i]);
        
        if (mSelects[i])
        {
            ++selectCount;
        }
    }
    Text_select->setString(__String::createWithFormat("%d/7", selectCount)->getCString());
}

void UIGrabInfoLayer::onImageTouch(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto image = static_cast<ImageView*>(sender);
        mSelects[image->getTag()] = !mSelects[image->getTag()];
        setSelectInfo();
    }
}