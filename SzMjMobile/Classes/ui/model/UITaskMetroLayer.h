//  UITaskMetroLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/25

#ifndef _UITaskMetroLayer_h_
#define _UITaskMetroLayer_h_

#include "BaseLayer.h"
#include "MetroTouchManage.h"
#include "TaskMetroChildManager.h"

class UITaskMetroLayer : public BaseLayer
{
public:
    CREATE_FUNC(UITaskMetroLayer);
    UITaskMetroLayer();
    virtual ~UITaskMetroLayer();
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
private:
    void setTouch();
    void update(float dt) override;
    
    void testAddChild();
    
private:
    //MetroSpriteManage *mMetroSpriteManage;
    TaskMetroChildManager *mMetroChildManager;
    MetroTouchManage *mMetroTouchManage;
    
    Layer *mMoveLayer;
    Point mMoveLayerPoint;
    Point mMoveLayerVector;
};

#endif
