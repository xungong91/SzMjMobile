//  UISpecialInputLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#ifndef _UISpecialInputLayer_h_
#define _UISpecialInputLayer_h_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UIInput.h"
#include <string>

USING_NS_CC;
using namespace ui;
using namespace std;

class UISpecialInputLayer : public Layer, public EditBoxDelegate
{
public:
    enum class InputType
    {
        ANY,
        BIRTHDAY,
        HEIGHT,
        BHW,
        TEL
    };
    
public:
    CREATE_FUNC(UISpecialInputLayer);
    UISpecialInputLayer();
    virtual ~UISpecialInputLayer();
    virtual bool init();
    
    virtual void editBoxEditingDidBegin(EditBox* editBox);
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(EditBox* editBox);
    
public:
    void InitUI(string titleStr, string placeHolderStr, ui::EditBox::InputMode inputMode, InputType inputType);
    
private:
    void SetString(string str);
    
private:
    ui::Text *mNullLabel;        //内容为空时的label
    ui::Text *mTitleLabel;       //有内容时的内容标题
    ui::Text *mContentLabel; //内容
    
    UIInput *mInput;
    
    string mTitleStr;
    string mPlaceHolderStr;
    string mStr;
    
    InputType mInputType;
};

#endif
