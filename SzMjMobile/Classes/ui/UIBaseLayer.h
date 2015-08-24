//
//  UIBaseLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#ifndef __SzMjMobile__UIBaseLayer__
#define __SzMjMobile__UIBaseLayer__

#include "BaseMetroSprite.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "CocosHelper.h"
#include <string>
#include <vector>
#include <functional>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace std;

class UIBaseLayer : public Layer
{
public:
    UIBaseLayer();
    virtual ~UIBaseLayer();
    CREATE_FUNC(UIBaseLayer);
    bool init();
    
    //设置panel按钮
    void addPanelTouch(Layout *panel, function<void ()> func);
protected:
    Node *mLayout;
};

#endif /* defined(__SzMjMobile__UIBaseLayer__) */
