//
//  UIManageMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIManageMainLayer.h"

bool UIManageMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    
    mUIManageModelLayer = UIManageModelLayer::create();
    this->addChild(mUIManageModelLayer);
    mUIManageModelLayer->setEditTouch([this]()
                                      {
                                          mUIManageModelLayer->setVisible(false);
                                          mUIManageEditlLayer->setVisible(true);
                                      });
    
    mUIManageEditlLayer = UIManageEditlLayer::create();
    this->addChild(mUIManageEditlLayer);
    mUIManageEditlLayer->setModelTouch([this]()
                                      {
                                          mUIManageModelLayer->setVisible(true);
                                          mUIManageEditlLayer->setVisible(false);
                                      });
    
    
    
    mUIManageModelLayer->setVisible(true);
    mUIManageEditlLayer->setVisible(false);
    
    return true;
}