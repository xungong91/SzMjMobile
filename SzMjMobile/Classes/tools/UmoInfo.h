//
//  UmoInfo.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#ifndef __SzMjMobile__UmoInfo__
#define __SzMjMobile__UmoInfo__

#include "SingletonBase.h"

class UmoInfo : public SingletonBase<UmoInfo>
{
public:
    void showMsg();
};

#endif /* defined(__SzMjMobile__UmoInfo__) */
