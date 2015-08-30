//  UIChatChildLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/30

#ifndef _UIChatChildLayer_h_
#define _UIChatChildLayer_h_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include <string>

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

class UIChatChildLayer : public Widget
{
public:
    CREATE_FUNC(UIChatChildLayer);
    UIChatChildLayer();
    virtual ~UIChatChildLayer();
    virtual bool init();
    
public:
    void SetString(int viewSeatID, const string str);
    
private:
    void InitUI();
    
    void UpdatePos(int viewSeatID);
    
private:
    ImageView *mAvatar;
    Scale9Sprite *mContentBg;
    ui::RichText *mContent;
};

#endif
