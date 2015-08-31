//
//  UIInfoManage.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/18.
//
//

#ifndef __SzMjMobile__UIInfoManage__
#define __SzMjMobile__UIInfoManage__

#include "BaseMetroSprite.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

enum class UIMediaType
{
    image,
    video
};

struct UIImageStruct
{
    UIMediaType type;
    string file;
};

class UIInfoManage
{
public:
    static UIInfoManage *singleton();
    
    void setShowPwd(Button *button, EditBox *textFied);
    bool mIsShowPwd;
    string mPhoneNum;
private:
    
    static UIInfoManage *mUIInfoManage;
    UIInfoManage();
    ~UIInfoManage();
    class CGarbo
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (UIInfoManage::mUIInfoManage)
            {
                delete UIInfoManage::mUIInfoManage;
            }
        }
    };
    static CGarbo mGarbo;
};

#endif /* defined(__SzMjMobile__UIInfoManage__) */
