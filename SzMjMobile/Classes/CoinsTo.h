//
//  CoinsBy.h
//  SzMjMobile
//
//  Created by gongxun on 15/4/28.
//
//

#ifndef __SzMjMobile__CoinsBy__
#define __SzMjMobile__CoinsBy__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;
using namespace std;

class CC_DLL CoinsTo : public ActionInterval
{
public:
    static CoinsTo* create(float duration, const string &num, Text *text);
    CoinsTo() {}
    ~CoinsTo() {}
    
    virtual void update(float time) override;
    bool initWithDuration(float duration, const string &num, Text *text);
    
protected:
    int mNum;
    int mStartNum;
    Text *mText;
};

#endif /* defined(__SzMjMobile__CoinsBy__) */
