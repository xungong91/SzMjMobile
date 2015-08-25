//
//  BaseMetroSprite.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/13.
//
//

#ifndef __SzMjMobile__BaseMetroSprite__
#define __SzMjMobile__BaseMetroSprite__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

enum class MetroSpriteStyle
{
    widget1x1,
    widget2x2,
    widget4x2
};

enum class MetroSpriteType
{
    text,
    image,
    video
};

inline Size getSizeForStyle(MetroSpriteStyle style)
{
    Size rSize(0, 0);
    switch (style)
    {
        case MetroSpriteStyle::widget1x1:
            rSize = Size(90, 90);
            break;
        case MetroSpriteStyle::widget2x2:
            rSize = Size(341, 340);
            break;
        case MetroSpriteStyle::widget4x2:
            rSize = Size(390, 190);
            break;
        default:
            break;
    }
    return rSize;
}

class MetroSpriteColor : public LayerColor
{
public:
    static MetroSpriteColor *create();
    bool init();
    void setLayerColor(const Color4B& color, GLfloat width, GLfloat height);
};

class BaseMetroSprite : public Sprite
{
public:
    BaseMetroSprite();
    virtual ~BaseMetroSprite();
    CREATE_FUNC(BaseMetroSprite);
    bool init() override;
    
    virtual void setStyle(MetroSpriteStyle style);
    virtual void setBgColor(Color4B color4b);
    
    virtual void setMetorName(const string &name);
    
    virtual void onSelect();
    virtual void onSelectLeave();
    
    MetroSpriteStyle getStyle() { return mStyle; }
protected:
    //背景色
    MetroSpriteColor *mBgColor;
    
    //风格
    MetroSpriteStyle mStyle;
    
    //名称
    Label *mNameLabel;
    
    //遮罩 防止内容超过边界
    ClippingNode *mClippingNode;
};

#endif /* defined(__SzMjMobile__BaseMetroSprite__) */
