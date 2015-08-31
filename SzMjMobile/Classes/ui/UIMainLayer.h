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
#include "UIIncomeMainLayer.h"
#include "UIGrabMainLayer.h"
#include "UIManageMainLayer.h"
#include "UIBaseTopLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class UIMainLayer : public Layer
{
public:
    static UIMainLayer *gUIMainLayer;
    
    CREATE_FUNC(UIMainLayer);
    UIMainLayer();
    virtual ~UIMainLayer();
    virtual bool init();

public:
    void intoMain();
    
    void pushLayer(Node *layer);
    void popLayer();
    
    void intoModelLayer();
    void intoPublishLayer();
    void intoIncomeLayer();
    void intoGrabLayer();
    void intoManageLayer();
    
private:
    void changeAction(UIBaseCenterLayer *sender);
    void removeAllChiLayer();
    
    void CallbackMenu(Ref *sender, Widget::TouchEventType type);
    
private:
    //所有的layer
    vector<Node*> mChildLayers;
    Layer *mChildLayer;
    //main的layer
    Layer *mMainLayer;
    Node *mLayout;
    //当前选择的layer
    Node *mCurrentLayer;
    
    Widget *Panel_tools;
    Button *mBtnModel, *mBtnPublish, *mBtnProfit, *mBtnGrab, *mBtnUpdate;
    
    UIModelMainLayer *mUIModelMainLayer;
    UIPublishMainLayer *mUIPublishMainLayer;
    UIIncomeMainLayer *mUIIncomeMainLayer;
    UIGrabMainLayer *mUIGrabMainLayer;
    UIManageMainLayer *mUIManageMainLayer;
    vector<UIBaseCenterLayer*> mLayers;
    
    //监听按键
    EventListenerKeyboard *mListenerkeyPad;
    void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
};

#endif /* defined(__SzMjMobile__UIMainLayer__) */
