//
//  UIIncomeSubmitLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/30.
//
//

#include "UIIncomeSubmitLayer.h"
#include "UIMainLayer.h"

bool UIIncomeSubmitLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_incomeSubmit.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Button_tixian")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->popLayer();
         }
     }
     );
    
    vector<string> layoutNames = {"Panel_edit0", "Panel_edit1", "Panel_edit2"};
    
    vector<string> mEditHolders = {"收款人姓名", "收款人卡号", "请输入银行"};
    
    for (int i = 0; i < 3; ++i)
    {
        Layout *layout = static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, layoutNames[i]));
        Size size = layout->getContentSize();
        EditBox *tempEdit = EditBox::create(size, Scale9Sprite::create("Transparent.png"));
        tempEdit->setPosition(Point::ZERO);
        tempEdit->setAnchorPoint(Point::ZERO);
        tempEdit->setFontSize(60);
        tempEdit->setFontColor(Color3B::BLACK);
        tempEdit->setPlaceHolder("");
        tempEdit->setPlaceholderFontColor(Color3B::WHITE);
        tempEdit->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        tempEdit->setTag(i);
        tempEdit->setInputMode(EditBox::InputMode::NUMERIC);
        tempEdit->setPlaceHolder(mEditHolders[i].c_str());
        
        layout->addChild(tempEdit);
    }
    
    return true;
}
