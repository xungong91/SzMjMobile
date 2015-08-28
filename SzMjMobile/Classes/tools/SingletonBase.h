//
//  SingletonBase.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#ifndef __SzMjMobile__SingletonBase__
#define __SzMjMobile__SingletonBase__

template<typename T>
class SingletonBase
{
public:
    static T* getInstance()
    {
        return instance;
    }
private:
    static T* instance;
};
#endif /* defined(__SzMjMobile__SingletonBase__) */
