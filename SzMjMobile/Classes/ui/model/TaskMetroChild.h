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
    
protected:
    Sprite *mImage;
    
    string mName;
    
    void imageRun();
};

#endif
