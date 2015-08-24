//
//  MetroVideoSprite.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "MetroVideoSprite.h"

bool MetroVideoSprite::init()
{
    if (!BaseMetroSprite::init())
    {
        return false;
    }
    
    mIsPlay = false;
    
    mVideoPlayer = VideoPlayer::create();
    mVideoPlayer->setPosition(Point(0, 0));
    mVideoPlayer->setAnchorPoint(Point(0, 0));
    mClippingNode->addChild(mVideoPlayer);
    mVideoPlayer->addEventListener
    ([](Ref* sender, VideoPlayer::EventType eventType)
     {
     });
    
    return true;
}

void MetroVideoSprite::setStyle(MetroSpriteStyle style)
{
    BaseMetroSprite::setStyle(style);
    mVideoPlayer->setContentSize(this->getContentSize());
}

void MetroVideoSprite::onSelect()
{
    
}

void MetroVideoSprite::onSelectLeave()
{
    if (!mIsPlay)
    {
        mVideoPlayer->setFileName("Metro/qqvideo.mp4");
        mVideoPlayer->play();
    }
    else
    {
        mVideoPlayer->stop();
    }
    
    mIsPlay = !mIsPlay;
}