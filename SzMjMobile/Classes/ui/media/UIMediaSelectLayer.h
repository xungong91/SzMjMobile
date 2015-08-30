//
//  UIMediaSelectLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/19.
//
//

#ifndef __SzMjMobile__UIMediaSelectLayer__
#define __SzMjMobile__UIMediaSelectLayer__

#include "UIBaseLayer.h"
#include "UIInfoManage.h"
#include "UIMediaSelectItemLayer.h"
#include <functional>

class UIMediaSelectLayer : public UIBaseLayer
{
public:
    UIMediaSelectLayer();
    ~UIMediaSelectLayer();
    CREATE_FUNC(UIMediaSelectLayer);
    bool init();
    void onEnter();
    void onExit();
    
    void setSelectCallFunc(function<void (vector<UIImageStruct> files)> func);
private:
    Layer *mMoveLayer;
    Point mTouchStartPoint;
    Point mMoveLayerStartPoint;
    UIMediaSelectItemLayer *mSelectMediaItem;
    function<void (vector<UIImageStruct> files)> mSelectCallFunc;
    //选中用的
    Point mTouchSelectPoint;
    bool mIsSelect;
    vector<UIMediaSelectItemLayer*> mSelectSprites;
    EventListenerTouchOneByOne *mEventListenerMove;
    
    void onSelectBegan(Point p);
    void onSelectMove(Point p);
    void onSelectEnd(Point p);
    void onTouchEnd();
    void setOkButtonStatas();
    
    bool getSpriteForPoint(Point p, UIMediaSelectItemLayer *&sprite);
};

#endif /* defined(__SzMjMobile__UIMediaSelectLayer__) */
