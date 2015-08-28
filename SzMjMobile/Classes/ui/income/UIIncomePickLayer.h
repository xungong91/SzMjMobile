//
//  UIIncomePickLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#ifndef __SzMjMobile__UIIncomePickLayer__
#define __SzMjMobile__UIIncomePickLayer__

#include "UIBaseTopLayer.h"

class UIIncomePickLayer : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIIncomePickLayer);
    bool init();
    
    void updateList(float dt);
private:
    ListView *ListView_main;
    Widget *Panel_help;
    Widget *Image_help;
    Widget *Image_1;
    vector<Node*> mTaskLayers;
    
    void addTask();
    void sethanldAction();
};

#endif /* defined(__SzMjMobile__UIIncomePickLayer__) */
