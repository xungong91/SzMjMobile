//
//  UIMainLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#ifndef __SzMjMobile__UIMainLayer__
#define __SzMjMobile__UIMainLayer__

#include "BaseMetroSprite.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "UIModelMainLayer.h"
#include "UIPublishMainLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class UIMainLayer : public Layer
{
public:
    static UIMainLayer *gUIMainLayer;
    
    UIMainLayer();
    ~UIMainLayer();
    CREATE_FUNC(UIMainLayer);
    bool init();

    void intoMain();
private:
    Node *mLayout;
    Node *mCurrentLayer;
    Node *mLastLayer;
    Widget *Panel_tools;
    UIModelMainLayer *mUIModelMainLayer;
    UIPublishMainLayer *mUIPublishMainLayer;
    vector<UIBaseCenterLayer*> mLayers;
    
    void changeAction(UIBaseCenterLayer *sender);
    void intoModelLayer();
    void intoPublishLayer();
};

#endif /* defined(__SzMjMobile__UIMainLayer__) */
