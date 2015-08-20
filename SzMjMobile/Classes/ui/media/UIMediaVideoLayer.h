//
//  UIMediaVideoLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/20.
//
//

#ifndef __SzMjMobile__UIMediaVideoLayer__
#define __SzMjMobile__UIMediaVideoLayer__

#include "UIBaseLayer.h"
#include "UIInfoManage.h"
#include "ui/UIVideoPlayer.h"

using namespace experimental::ui;

class UIPlayVideoLayer : public Layer
{
public:
    static UIPlayVideoLayer *create(const string &file);
    bool init(const string &file);
};

class UIMediaVideoLayer : public Layer
{
public:
    UIMediaVideoLayer();
    CREATE_FUNC(UIMediaVideoLayer);
    bool init();
    
    void setVideoFile(const string &file);
    void setContentSize(const Size& contentSize) override;
private:
    string mVideoFile;
    Sprite *mImage;
    MenuItemImage *mPlayMenu;
};

#endif /* defined(__SzMjMobile__UIMediaVideoLayer__) */
