//
//  MetroMainLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/13.
//
//

#ifndef __SzMjMobile__MetroMainLayer__
#define __SzMjMobile__MetroMainLayer__

#include "BaseLayer.h"
#include "MetroTouchManage.h"
#include "MetroSpriteManage.h"

class MetroMainLayer : public BaseLayer
{
public:
    MetroMainLayer();
    ~MetroMainLayer();
    CREATE_FUNC(MetroMainLayer);
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
private:
    MetroSpriteManage *mMetroSpriteManage;
    MetroTouchManage *mMetroTouchManage;
    
    Layer *mMoveLayer;
    Point mMoveLayerPoint;
    Point mMoveLayerVector;
    
    void setTouch();
    void update(float dt) override;
    
    void testAddChild();
    
};

#endif /* defined(__SzMjMobile__MetroMainLayer__) */
