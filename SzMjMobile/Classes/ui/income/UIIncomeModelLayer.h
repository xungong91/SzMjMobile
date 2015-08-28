//
//  UIIncomeModelLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#ifndef __SzMjMobile__UIIncomeModelLayer__
#define __SzMjMobile__UIIncomeModelLayer__

#include "UIBaseTopLayer.h"

class UIIncomeModelLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIIncomeModelLayer);
    bool init();
    
    void setTitle(const string &title);
private:
    ImageView *Image_main;
    vector<Node*> mTaskLayers;
    
    void setTask();
    void runTaskAction();
};

#endif /* defined(__SzMjMobile__UIIncomeModelLayer__) */
