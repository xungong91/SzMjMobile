//
//  CTestDrawLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/7/5.
//
//

#ifndef __SzMjMobile__CTestDrawLayer__
#define __SzMjMobile__CTestDrawLayer__

#include "cocos2d.h"

USING_NS_CC;

class CTestDrawLayer : public Layer
{
public:
    CREATE_FUNC(CTestDrawLayer);
    bool init();
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    void onEnter() override;
private:
    cocos2d::CustomCommand _customCommand;
    
    void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
};

#endif /* defined(__SzMjMobile__CTestDrawLayer__) */
