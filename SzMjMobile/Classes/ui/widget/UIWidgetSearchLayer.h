//
//  UIWidgetSearchLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/30.
//
//

#ifndef __SzMjMobile__UIWidgetSearchLayer__
#define __SzMjMobile__UIWidgetSearchLayer__

#include "UIBaseLayer.h"
#include <functional>

using namespace std;

class UIWidgetSearchLayer : public Layer, public ui::EditBoxDelegate
{
public:
    CREATE_FUNC(UIWidgetSearchLayer);
    bool init();
    
    void setHandldAction(function<void (string text)> func) {mDidEndFunc = func;}
    
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    
    void setVisible(bool isVisble) override;
private:
    Node *mLayout;
    function<void (string text)> mDidEndFunc;
    
    EditBox *mSearchEdit;
};

#endif /* defined(__SzMjMobile__UIWidgetSearchLayer__) */
