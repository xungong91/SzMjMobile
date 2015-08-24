//
//  UIMediaVideoLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/20.
//
//

#include "UIMediaVideoLayer.h"
#include "XHelper.h"

UIMediaVideoLayer::UIMediaVideoLayer()
: mImage(nullptr)
{
    
}

bool UIMediaVideoLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    mPlayMenu = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [this](Ref *sender)
                                      {
                                          Director::getInstance()->getRunningScene()->addChild(UIPlayVideoLayer::create(mVideoFile), 10);
                                      });
    mPlayMenu->setScale(4.0f);
    
    auto menu = Menu::create(mPlayMenu, NULL);
    menu->setPosition(Point::ZERO);
    menu->setAnchorPoint(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void UIMediaVideoLayer::setVideoFile(const string &file)
{
    mVideoFile = file;
    
    string imageFile = file.substr(0, file.find(".")) + ".jpg";
    
    mImage = Sprite::create(imageFile);
    mImage->setAnchorPoint(Point::ZERO);
    this->addChild(mImage);

    Layer::setContentSize(mImage->getContentSize());
}

void UIMediaVideoLayer::setContentSize(const Size& contentSize)
{
    Layer::setContentSize(contentSize);
    if (!mImage)
    {
        return;
    }
    
    mPlayMenu->setPosition(getPointHalf(contentSize));
    
    
    auto size = mImage->getContentSize();
    mImage->setScale(contentSize.width / size.width, contentSize.height / size.height);
}

//---------------
//UIPlayVideoLayer
//---------------

UIPlayVideoLayer *UIPlayVideoLayer::create(const string &file)
{
    UIPlayVideoLayer *pRet = new(std::nothrow) UIPlayVideoLayer();
    if (pRet && pRet->init(file))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool UIPlayVideoLayer::init(const string &file)
{
    if (!Layer::init())
    {
        return false;
    }
    this->addChild(LayerColor::create(Color4B(0, 0, 0, 255)));
    
    VideoPlayer *mVideoPlayer = VideoPlayer::create();
    mVideoPlayer->setPosition(Point(0, 0));
    mVideoPlayer->setAnchorPoint(Point(0, 0));
    mVideoPlayer->setFileName(file);
    mVideoPlayer->setKeepAspectRatioEnabled(true);
    mVideoPlayer->setContentSize(getSizeWin());
    mVideoPlayer->play();
    this->addChild(mVideoPlayer);

    
    auto mEventListenerMove = EventListenerTouchOneByOne::create();
    mEventListenerMove->onTouchBegan = [this](Touch* touch, Event  *event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mEventListenerMove, this);
    
    auto mPlayMenu = MenuItemFont::create("返回", [this](Ref* sender)
                                          {
                                              this->getParent()->removeChild(this);
                                          });
    mPlayMenu->setFontSize(80);
    mPlayMenu->setPosition(100, 1820);
    
    auto menu = Menu::create(mPlayMenu, NULL);
    menu->setPosition(Point::ZERO);
    menu->setAnchorPoint(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}





















