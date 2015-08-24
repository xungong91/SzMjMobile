//
//  UIMediaLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/19.
//
//

#ifndef __SzMjMobile__UIMediaLayer__
#define __SzMjMobile__UIMediaLayer__

#include "UIBaseLayer.h"
#include "UIInfoManage.h"

class UIMediaLayer : public UIBaseLayer
{
public:
    UIMediaLayer();
    ~UIMediaLayer();
    CREATE_FUNC(UIMediaLayer);
    bool init();
    
    void setMediaInfo(const vector<UIImageStruct> &medias);
    
private:
    vector<UIImageStruct> mMedias;
    PageView *PageView_media;
    vector<Widget*> mPageChilds;
    int mPageIndex;
    
    void stopAllVideo();
    void onPageChange();
};

#endif /* defined(__SzMjMobile__UIMediaLayer__) */
