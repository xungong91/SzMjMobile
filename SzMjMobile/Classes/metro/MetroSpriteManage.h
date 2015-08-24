//
//  MetroSpriteManage.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/14.
//
//

#ifndef __SzMjMobile__MetroSpriteManage__
#define __SzMjMobile__MetroSpriteManage__

#include "cocos2d.h"
#include "BaseMetroSprite.h"
#include <list>
#include <vector>

USING_NS_CC;
using namespace std;

#define METRO_ORIENTATION_HOR 0

struct MetroInfoStruct
{
    MetroSpriteStyle style;
    MetroSpriteType type;
    Color4B color;
    string title;
};

class MetroSpriteManage
{
public:
    MetroSpriteManage();
    ~MetroSpriteManage();
    
    void setMetro(Layer *node);
    //重新排列
    void resetUpdata();
    //插入
    BaseMetroSprite *mMetroNullSprite;
    int mMetroNullSpriteIndex;
    void setChangeUpdataStart(Point p, BaseMetroSprite *sprite);
    void setChangeUpdata(Point p, BaseMetroSprite *sprite);
    void setChangeUpdataEnd(Point p, BaseMetroSprite *sprite);
    
    void setMaxWidth();
private:
    //最大宽度
    Layer *mMoveLayer;
    
    vector<BaseMetroSprite*> mMetroList;
    
    void createMetroList();
    
    int getHoldIndex(int index, MetroSpriteStyle style, vector<int> &maps);
    bool getIsHold(int index, MetroSpriteStyle style, vector<int> &maps);
    void setIsHold(int index, MetroSpriteStyle style, vector<int> &maps);
    void setMetroSpritePoint(int holdIndex, Node *sprite);
};

#endif /* defined(__SzMjMobile__MetroSpriteManage__) */
