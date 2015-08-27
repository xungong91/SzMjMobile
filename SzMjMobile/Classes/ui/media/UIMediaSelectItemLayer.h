//
//  UIMediaSelectItemLayer.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/19.
//
//

#ifndef __SzMjMobile__UIMediaSelectItemLayer__
#define __SzMjMobile__UIMediaSelectItemLayer__

#include "UIBaseLayer.h"
#include "UIInfoManage.h"

class UIMediaSelectItemLayer : public UIBaseLayer
{
public:
    UIMediaSelectItemLayer();
    ~UIMediaSelectItemLayer();
    CREATE_FUNC(UIMediaSelectItemLayer);
    bool init();
    void setResInfo(const string &file, UIMediaType type);
    
    void onSelect();
    void onSelectLeave();
    
    void selectThis();
    
    UIImageStruct getType();
    //string GetFilePath() {return mFile;};
    
    bool mIsSelect;
private:
    UIMediaType mType;
    string mFile;
    
    Sprite *mSelectSprite;
};

#endif /* defined(__SzMjMobile__UIMediaSelectItemLayer__) */
