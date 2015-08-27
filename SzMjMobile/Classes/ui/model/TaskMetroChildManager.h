//  TaskMetroChildManager.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/25

#ifndef _TaskMetroChildManager_h_
#define _TaskMetroChildManager_h_

#include "cocos2d.h"
#include "BaseMetroSprite.h"
#include <list>
#include <vector>

USING_NS_CC;
using namespace std;

#define METRO_ORIENTATION_HOR 1

struct TaskMetroInfoStruct
{
    MetroSpriteStyle style;
    MetroSpriteType type;
    Color4B color;
    string title;
};

class TaskMetroChildManager
{
public:
    TaskMetroChildManager();
    virtual ~TaskMetroChildManager();
    
    void setMetro(Layer *node);
    //重新排列
    void resetUpdata();
    //插入
    BaseMetroSprite *mMetroNullSprite;
    int mMetroNullSpriteIndex;
    void setChangeUpdataStart(Point p, BaseMetroSprite *sprite);
    void setChangeUpdata(Point p, BaseMetroSprite *sprite);
    void setChangeUpdataEnd(Point p, BaseMetroSprite *sprite);
    
    void runTaskAction();
private:
    void createMetroList();
    
    //设置每个元素的位置
    void SetChildPosition(int holdIndex, Node *sprite);
    //刷新大小
    void UpdateMaxSize();
    
    int getHoldIndex(int index, MetroSpriteStyle style, vector<int> &maps);
    bool getIsHold(int index, MetroSpriteStyle style, vector<int> &maps);
    void setIsHold(int index, MetroSpriteStyle style, vector<int> &maps);
    
private:
    //最大宽度
    Layer *mMoveLayer;
    
    vector<BaseMetroSprite*> mMetroList;
};

#endif
