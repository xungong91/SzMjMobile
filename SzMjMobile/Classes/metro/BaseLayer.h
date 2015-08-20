//
//  BaseLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/13.
//
//

#ifndef __SzMjMobile__BaseLayer__
#define __SzMjMobile__BaseLayer__

#include "cocos2d.h"

USING_NS_CC;

class BaseLayer : public Layer
{
public:
    BaseLayer();
    virtual ~BaseLayer();
    CREATE_FUNC(BaseLayer);
    bool init() override;
};

#endif /* defined(__SzMjMobile__BaseLayer__) */
