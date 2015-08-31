//
//  UILogin1Layer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#ifndef __SzMjMobile__UILogin1Layer__
#define __SzMjMobile__UILogin1Layer__

#include "UIBaseLayer.h"

class UserEditBox : public EditBox, public ui::EditBoxDelegate
{
public:
    static UserEditBox* create(const Size& size, Scale9Sprite* normalSprite);
    
    UserEditBox() : mDidEndFunc(nullptr)
    {
        
    }
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    
    void setDidEndFunc(function<void (string)> func) { mDidEndFunc = func; }
private:
    function<void (string)> mDidEndFunc;
};

class UILogin1Layer : public UIBaseLayer
{
public:
    CREATE_FUNC(UILogin1Layer);
    bool init();
};

#endif /* defined(__SzMjMobile__UILogin1Layer__) */
