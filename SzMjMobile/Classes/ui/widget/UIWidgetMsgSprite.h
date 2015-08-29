//
//  UIWidgetMsgSprite.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#ifndef __SzMjMobile__UIWidgetMsgSprite__
#define __SzMjMobile__UIWidgetMsgSprite__

#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace std;

class UIWidgetMsgSprite : public ui::Scale9Sprite
{
public:
    static void setMsg(const string &msg);
    static UIWidgetMsgSprite *getRichCB();
public:
    UIWidgetMsgSprite();
    ~UIWidgetMsgSprite();
    CREATE_FUNC(UIWidgetMsgSprite);
    bool init();
    void setSize();
    
    Label *mLabel;
    
};

#endif /* defined(__SzMjMobile__UIWidgetMsgSprite__) */
