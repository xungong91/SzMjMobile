//  TaskMetroChild.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/25

#ifndef _TaskMetroChild_h_
#define _TaskMetroChild_h_

#include "BaseMetroSprite.h"

class TaskMetroChild : public BaseMetroSprite
{
public:
    CREATE_FUNC(TaskMetroChild);
    bool init();
    
public:
    void LoadImages(int name);
    
    void setStyle(MetroSpriteStyle style) override;
    
    void onSelect() override;
    void onSelectLeave() override;
    
    //播放动画
    float setHanldRunAction();
protected:
    Sprite *mImage;
    string mName;
    Sprite *mNormal0, *mNormal1, *mSelect;
    int mShowIndex;
    
    void imageRun();
};

#endif
