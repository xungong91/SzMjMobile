//
//  UIMediaLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/19.
//
//

#include "UIMediaLayer.h"
#include "XHelper.h"
#include "UIMediaVideoLayer.h"

UIMediaLayer::UIMediaLayer()
: mPageIndex(-1)
{
    
}

UIMediaLayer::~UIMediaLayer()
{
    
}

bool UIMediaLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_media.csb", this);
    
    PageView_media = static_cast<PageView*>(CocosHelper::getNodeByName(mLayout, "PageView_media"));
    PageView_media->removeAllPages();
    
    
    PageView_media->addEventListener([this](Ref* sender, PageView::EventType type)
                                          {
                                              onPageChange();
                                          });
    
    CocosHelper::getWidgetByName(mLayout, "Text_quit")->addTouchEventListener([this](Ref *sender, Widget::TouchEventType type)
                                                                              {
                                                                                  if (type == Widget::TouchEventType::ENDED)
                                                                                  {
                                                                                      this->getParent()->removeChild(this);
                                                                                  }
                                                                              });
    
    return true;
}

void UIMediaLayer::setMediaInfo(const vector<UIImageStruct> &medias)
{
    mMedias = medias;
    
    Size pageSize(1080, 1920);
    for (int i = 0; i < mMedias.size(); ++i)
    {
        UIImageStruct media = mMedias[i];
        
        Layout *layer = Layout::create();
        layer->setContentSize(pageSize);
        PageView_media->addPage(layer);
        
        if (media.type == UIMediaType::image)
        {
            ImageView *image = ImageView::create();
            image->loadTexture(media.file);
            image->setPosition(getPointHalf(pageSize));
            layer->addChild(image);
            mPageChilds.push_back(image);
            
            Size size = image->getContentSize();
            float scale;
            if (size.width / size.height > pageSize.width / pageSize.height)
            {
                scale = pageSize.width / size.width;
            }
            else
            {
                scale = pageSize.height / size.height;
            }
            
            image->setScale(scale);
        }
        else
        {
            UIMediaVideoLayer *play = UIMediaVideoLayer::create();
            play->setVideoFile(media.file);
            layer->addChild(play);
            
            Size size = play->getContentSize();
            float scale;
            if (size.width / size.height > pageSize.width / pageSize.height)
            {
                scale = pageSize.width / size.width;
            }
            else
            {
                scale = pageSize.height / size.height;
            }
            size = Size(size.width * scale, size.height * scale);
            play->setContentSize(size);
            play->setPosition(getPointHalf(pageSize) - getPointHalf(size));
        }
    }
    onPageChange();
}

void UIMediaLayer::stopAllVideo()
{
    return;
    for(auto it : mPageChilds)
    {
        if (typeid(*it) == typeid(VideoPlayer))
        {
            static_cast<VideoPlayer*>(it)->stop();
        }
    }
}

void UIMediaLayer::onPageChange()
{
    int temp = PageView_media->getCurPageIndex();
    if (temp == mPageIndex)
    {
        return;
    }
    else
    {
        mPageIndex = temp;
    }
    
    stopAllVideo();
    
    Text *Text_page = static_cast<Text*>(CocosHelper::getNodeByName(mLayout, "Text_page"));
    Text_page->setString(__String::createWithFormat("%zd/%zd", PageView_media->getCurPageIndex() + 1, PageView_media->getPages().size())->getCString());
}






















