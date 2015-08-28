//  UIPublishMetroChild.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/28

#ifndef _UIPublishMetroChild_h_
#define _UIPublishMetroChild_h_

#include "BaseMetroSprite.h"
#include <functional>

using namespace std;

class UIPublishMetroChild : public BaseMetroSprite
{
public:
    CREATE_FUNC(UIPublishMetroChild);
    bool init();
    
public:
    void LoadImages(int name);
    
    void setStyle(MetroSpriteStyle style) override;
    
    void onSelect() override;
    void onSelectLeave(bool isMove) override;
    
    //播放动画
    float setHanldRunAction(function<void ()> func);
    
    void imageRun();
    
protected:
    Sprite *mImage;
    string mName;
    Sprite *mNormal0, *mNormal1, *mSelect;
    int mShowIndex;
};

#endif
