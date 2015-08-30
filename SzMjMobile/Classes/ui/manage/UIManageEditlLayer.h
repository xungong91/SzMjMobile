//
//  UIManageEditlLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#ifndef __SzMjMobile__UIManageEditlLayer__
#define __SzMjMobile__UIManageEditlLayer__

#include "UIBaseCenterLayer.h"
#include <vector>

using namespace std;
using namespace cocos2d::ui;

class UIManageEditlLayer : public UIBaseCenterLayer, public ui::EditBoxDelegate
{
public:
    CREATE_FUNC(UIManageEditlLayer);
    bool init();
    
    void setModelTouch(function<void ()> func)
    {
        mModelTouchFunc = func;
    }
    
    
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    
private:
    function<void ()> mModelTouchFunc;
    
    vector<string> mEditHolders;
    vector<ui::EditBox*> mEdits;
    vector<Layout*> mLayouts;
    static vector<string> mEditInputs;
    
    void onChange();
    void setInput();
};

#endif /* defined(__SzMjMobile__UIManageEditlLayer__) */
