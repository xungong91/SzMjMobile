//  TaskMetroChildManager.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/25

#include "TaskMetroChildManager.h"
#include "TaskMetroChild.h"
#include "MetroTextSprite.h"
#include "MetroVideoSprite.h"
#include "MetroNullSprite.h"

const int gRowCount = 3;        //最多3行
const int gColumnCount = 3;  //最多3列
const int gWidth = 350;
const int gHeight = 350;
const Point gStartPoint = Point(20, 1040);

TaskMetroChildManager::TaskMetroChildManager()
: mMetroNullSprite(nullptr)
{
    createMetroList();
}

TaskMetroChildManager::~TaskMetroChildManager()
{
}

void TaskMetroChildManager::createMetroList()
{
    vector<Color4B> colors =
    {
        Color4B(240, 148, 0, 255),
        Color4B(194, 57, 22, 255),
        Color4B(60, 119, 128, 255),
        Color4B(0, 157, 170, 255),
        Color4B(190, 33, 62, 255),
        Color4B(148, 200, 73, 255),
        Color4B(145, 0, 155, 255)
    };
    
    vector<TaskMetroInfoStruct> lists;
    
    //图片2x2
    for (int i = 0; i < 13; ++i)
    {
        TaskMetroInfoStruct temp =
        {
            MetroSpriteStyle::widget2x2,
            MetroSpriteType::image,
            colors[CCRANDOM_0_1() * colors.size()],
            ""
        };
        lists.push_back(temp);
    }
    
    for (int i=0; i < lists.size(); i++)
    {
        auto it = lists.at(i);
        
        BaseMetroSprite *sprite;
        if (it.type == MetroSpriteType::text)
        {
            sprite = MetroTextSprite::create();
        }
        else if (it.type == MetroSpriteType::image)
        {
            sprite = TaskMetroChild::create();
            ((TaskMetroChild*)sprite)->LoadImages(i);
        }
        else if (it.type == MetroSpriteType::video)
        {
            sprite = MetroVideoSprite::create();
        }
        sprite->setStyle(it.style);
        //sprite->setBgColor(it.color);
        sprite->setMetorName(it.title);
        sprite->retain();
        mMetroList.push_back(sprite);
    }
}

void TaskMetroChildManager::setMetro(Layer *node)
{
    mMoveLayer = node;
    vector<int> maps(mMetroList.size() * 3, 0);
    
    int index = 0;
    for (auto it : mMetroList)
    {
        int holdIndex = getHoldIndex(index, it->getStyle(), maps);
        
        setIsHold(holdIndex, it->getStyle(), maps);
        
        SetChildPosition(holdIndex, it);
        node->addChild(it);
        it->release();
        
        ++index;
    }
    
    UpdateMaxSize();
}

void TaskMetroChildManager::runTaskAction()
{
    
}

void TaskMetroChildManager::resetUpdata()
{
    vector<int> maps(mMetroList.size() * 3, 0);
    
    int index = 0;
    for (auto it : mMetroList)
    {
        int holdIndex = getHoldIndex(index, it->getStyle(), maps);
        
        setIsHold(holdIndex, it->getStyle(), maps);
        
        SetChildPosition(holdIndex, it);
        
        ++index;
    }
    
    UpdateMaxSize();
}

void TaskMetroChildManager::setChangeUpdataStart(Point p, BaseMetroSprite *sprite)
{
    //选中sprite后保存，移出mMetroList，插入空白sprite
    //调整sprite位置
    //结束时候移除空白sprite sprite归位
    mMetroNullSpriteIndex = 0;
    if (mMetroNullSprite)
    {
        mMetroNullSprite->release();
    }
    
    mMetroNullSprite = MetroNullSprite::create();
    mMetroNullSprite->setPosition(sprite->getPosition());
    mMetroNullSprite->setStyle(sprite->getStyle());
    sprite->getParent()->addChild(mMetroNullSprite);
    
    for (int i = 0; i < mMetroList.size(); ++i)
    {
        if (mMetroList[i] == sprite)
        {
            mMetroList[i] = mMetroNullSprite;
            mMetroNullSpriteIndex = i;
        }
    }
}

void TaskMetroChildManager::setChangeUpdata(Point p, BaseMetroSprite *sprite)
{
    //根据point得到index
    int i(0), index(-1);
    for (auto it : mMetroList)
    {
        if (it->getBoundingBox().containsPoint(p))
        {
            index = i;
        }
        ++i;
    }
    
    if (index != -1 && mMetroNullSpriteIndex != index)
    {
        auto temp = mMetroList[index];
        mMetroList[index] = mMetroList[mMetroNullSpriteIndex];
        mMetroList[mMetroNullSpriteIndex] = temp;
        mMetroNullSpriteIndex = index;
        
        resetUpdata();
    }
}

void TaskMetroChildManager::setChangeUpdataEnd(Point p, BaseMetroSprite *sprite)
{
    if (mMetroNullSprite)
    {
        mMetroList[mMetroNullSpriteIndex] = sprite;
        sprite->getParent()->removeChild(mMetroNullSprite);
        mMetroNullSprite = nullptr;
        
        resetUpdata();
    }
}

int TaskMetroChildManager::getHoldIndex(int index, MetroSpriteStyle style, vector<int> &maps)
{
    int rint = index;
    while (getIsHold(rint, style, maps))
    {
        ++rint;
    }
    return rint;
}

bool TaskMetroChildManager::getIsHold(int index, MetroSpriteStyle style, vector<int> &maps)
{
    bool isHold = false;
    
    if (maps[index] == 1)
    {
        isHold = true;
    }
    else if (style == MetroSpriteStyle::widget4x2 && maps[index + gRowCount] == 1)
    {
        isHold = true;
    }
    
    return isHold;
}

void TaskMetroChildManager::setIsHold(int index, MetroSpriteStyle style, vector<int> &maps)
{
    maps[index] = 1;
    if (style == MetroSpriteStyle::widget4x2)
    {
        maps[index + gRowCount] = 1;
    }
}

//设置每个元素的位置
void TaskMetroChildManager::SetChildPosition(int holdIndex, Node *sprite)
{
#if METRO_ORIENTATION_HOR
    //竖版
    Point p(holdIndex % gColumnCount * gWidth, holdIndex / gColumnCount * gHeight);
    p = Point(p.x, -p.y);
    p += gStartPoint;
    sprite->setPosition(p);
#else
    //横版
    Point p(holdIndex / gRowCount * gWidth, holdIndex % gRowCount * gHeight);
    p = Point(p.x, ((gRowCount - 1) * gHeight) - p.y);
    p += gStartPoint;
    sprite->setPosition(p);
#endif
}

//刷新大小
void TaskMetroChildManager::UpdateMaxSize()
{
#if METRO_ORIENTATION_HOR   
    //竖版
    float maxHeight = 0;
    for (auto it : mMetroList)
    {
        float height = it->getPosition().y + it->getContentSize().height;
        if (height > maxHeight)
        {
            maxHeight = height;
        }
    }
    mMoveLayer->setContentSize(Size(0, maxHeight));
#else
    //横版
    float maxWidth = 0;
    for (auto it : mMetroList)
    {
        float width = it->getPosition().x + it->getContentSize().width;
        if (width > maxWidth)
        {
            maxWidth = width;
        }
    }
    mMoveLayer->setContentSize(Size(maxWidth, 0));
#endif
}















