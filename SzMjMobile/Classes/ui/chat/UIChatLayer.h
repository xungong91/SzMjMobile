//  UIChatLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#ifndef _UIChatLayer_h_
#define _UIChatLayer_h_

#include "UIBaseTopLayer.h"

class UIChatLayer : public UIBaseTopLayer, public EditBoxDelegate
{
public:
    CREATE_FUNC(UIChatLayer);
    virtual bool init();
    
    virtual void editBoxEditingDidBegin(EditBox* editBox);
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(EditBox* editBox);
    
private:
    void InitUI();
    
    void CallbackBtnSend(Ref *sender, Widget::TouchEventType type);
    
private:
    //输入文本框
    ui::EditBox *mInput;
    
    Button *mBtnFace;
    Button *mBtnSend;
    
    ListView *mList;
};

#endif
