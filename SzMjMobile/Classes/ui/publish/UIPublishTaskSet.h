//  UIPublishTaskSet.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#ifndef _UIPublishTaskSet_h_
#define _UIPublishTaskSet_h_

#include "UIBaseTopLayer.h"

class UIPublishTaskSet : public UIBaseTopLayer
{
public:
    CREATE_FUNC(UIPublishTaskSet);
    bool init();
    
private:
    void InitUI();
    
    void AddImage(string imagePath);
    
    void Open();
    void Close();
    void UpdateList(float dt);
    
    void CallbackBtn1(Ref *sender, Widget::TouchEventType type);
    void CallbackBtn2(Ref *sender, Widget::TouchEventType type);
    void CallbackBtnJiaJian(Ref *sender, Widget::TouchEventType type);
    
private:
    //添加照片
    ImageView *mImage;
    
    //价格文本
    Text *mPriceLabel;
    int mPrice = 1000;
    Button *mBtnJia;
    Button *mBtnJian;
    
    Button *mBtnTask;
    Button *mBtnAddress;
    Button *mBtnPerson;
    Button *mBtnCommerce;
    Button *mBtnWuChang;
    Button *mBtnHanKou;
    Button *mBtnHanYang;
    
    ListView *mListView;
    Widget *mPanel;
    Widget *mPanelMove;
    Widget *mBase;
    Widget *mTask;
    Widget *mAddress;
};

#endif
