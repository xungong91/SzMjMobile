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
    
    void CallbackBtnTask(Ref *sender, Widget::TouchEventType type);
    
private:
    //添加照片
    ImageView *mImage;
    
    Button *mBtnTask;
    Button *mBtnAddress;
    Button *mBtnPerson;
    Button *mBtnCommerce;
    Button *mBtnWuChang;
    Button *mBtnHanKou;
    Button *mBtnHanYang;
    
    ListView *mListView;
    Widget *mPanel;
    Widget *mBase;
    Widget *mTask;
    Widget *mAddress;
};

#endif
