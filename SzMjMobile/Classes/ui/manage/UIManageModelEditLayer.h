//
//  UIManageModelEditLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#ifndef __SzMjMobile__UIManageModelEditLayer__
#define __SzMjMobile__UIManageModelEditLayer__

#include "UIBaseTopLayer.h"
#include <vector>

using namespace std;

class UIManageModelEditLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIManageModelEditLayer);
    bool init();
    
    void onEnter();
    void onExit();
    
private:
    Widget *Panel_model;
    Text *Text_pageCount;
    Point mTouchBeganPoint;
    Point mPanelModelStartPoint;
    EventListenerTouchOneByOne *mEventListenerChange;
    
    void onPanelModelEnd();
    
    //选择视频和图片
    vector<Widget*> mPanelMedias;
    void onPanelMediasImageTouch(Ref *sender, Widget::TouchEventType type);
    void onPanelMediasVideoTouch(Ref *sender, Widget::TouchEventType type);
    void onPanelMediasCloseTouch(Ref *sender, Widget::TouchEventType type);
};

#endif /* defined(__SzMjMobile__UIManageModelEditLayer__) */
