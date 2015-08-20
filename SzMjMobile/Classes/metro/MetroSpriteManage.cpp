//
//  MetroSpriteManage.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/14.
//
//

#include "MetroSpriteManage.h"
#include "MetroTextSprite.h"
#include "MetroImageSprite.h"
#include "MetroVideoSprite.h"
#include "MetroNullSprite.h"

const int gRowCount = 3;
const int gWidth = 200;
const int gHeight = 200;
const Point gStartPoint = Point(40, 20);

MetroSpriteManage::MetroSpriteManage()
: mMetroNullSprite(nullptr)
{
    createMetroList();
}

MetroSpriteManage::~MetroSpriteManage()
{
    
}

void MetroSpriteManage::createMetroList()
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
    
    vector<string> titles =
    {
        "日历",
        "邮件",
        "Edge",
        "Cortana",
        "天气",
        "QQ",
        "应用商店",
        "图片"
    };
    
    vector<MetroInfoStruct> lists;
    
    //普通2x2
    for (int i = 0; i < 15; ++i)
    {
        MetroInfoStruct temp =
        {
            MetroSpriteStyle::widget2x2,
            MetroSpriteType::text,
            colors[CCRANDOM_0_1() * colors.size()],
            titles[CCRANDOM_0_1() * titles.size()]
        };
        lists.push_back(temp);
    }
    
    //图片2x2
    for (int i = 0; i < 2; ++i)
    {
        MetroInfoStruct temp =
        {
            MetroSpriteStyle::widget2x2,
            MetroSpriteType::image,
            colors[CCRANDOM_0_1() * colors.size()],
            "视频"
        };
        lists.push_back(temp);
    }
    
    //视频
    for (int i = 0; i < 2; ++i)
    {
        MetroInfoStruct temp =
        {
            MetroSpriteStyle::widget4x2,
            MetroSpriteType::video,
            colors[CCRANDOM_0_1() * colors.size()],
            titles[CCRANDOM_0_1() * titles.size()]
        };
        lists.push_back(temp);
    }
    
    //普通4x2
    for (int i = 0; i < 5; ++i)
    {
        MetroInfoStruct temp =
        {
            MetroSpriteStyle::widget4x2,
            MetroSpriteType::text,
            colors[CCRANDOM_0_1() * colors.size()],
            titles[CCRANDOM_0_1() * titles.size()]
        };
        lists.push_back(temp);
    }
    
    //随机打乱
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(lists.begin(), lists.end(), g);
    
    for (auto it : lists)
    {
        BaseMetroSprite *sprite;
        if (it.type == MetroSpriteType::text)
        {
            sprite = MetroTextSprite::create();
        }
        else if (it.type == MetroSpriteType::image)
        {
            sprite = MetroImageSprite::create();
        }
        else if (it.type == MetroSpriteType::video)
        {
            sprite = MetroVideoSprite::create();
        }
        sprite->setStyle(it.style);
        sprite->setBgColor(it.color);
        sprite->setMetorName(it.title);
        sprite->retain();
        mMetroList.push_back(sprite);
    }
}

void MetroSpriteManage::setMetro(Layer *node)
{
    mMoveLayer = node;
    vector<int> maps(mMetroList.size() * 3, 0);
    
    int index = 0;
    for (auto it : mMetroList)
    {
        int holdIndex = getHoldIndex(index, it->getStyle(), maps);
        
        setIsHold(holdIndex, it->getStyle(), maps);
        
        setMetroSpritePoint(holdIndex, it);
        node->addChild(it);
        it->release();
        
        ++index;
    }
    
    setMaxWidth();
}

void MetroSpriteManage::resetUpdata()
{
    vector<int> maps(mMetroList.size() * 3, 0);
    
    int index = 0;
    for (auto it : mMetroList)
    {
        int holdIndex = getHoldIndex(index, it->getStyle(), maps);
        
        setIsHold(holdIndex, it->getStyle(), maps);
        
        setMetroSpritePoint(holdIndex, it);
        
        ++index;
    }
    
    setMaxWidth();
}

void MetroSpriteManage::setChangeUpdataStart(Point p, BaseMetroSprite *sprite)
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

void MetroSpriteManage::setChangeUpdata(Point p, BaseMetroSprite *sprite)
{
    //更具point得到index
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

void MetroSpriteManage::setChangeUpdataEnd(Point p, BaseMetroSprite *sprite)
{
    if (mMetroNullSprite)
    {
        mMetroList[mMetroNullSpriteIndex] = sprite;
        sprite->getParent()->removeChild(mMetroNullSprite);
        mMetroNullSprite = nullptr;
        
        resetUpdata();
    }
}

int MetroSpriteManage::getHoldIndex(int index, MetroSpriteStyle style, vector<int> &maps)
{
    int rint = index;
    while (getIsHold(rint, style, maps))
    {
        ++rint;
    }
    return rint;
}

bool MetroSpriteManage::getIsHold(int index, MetroSpriteStyle style, vector<int> &maps)
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

void MetroSpriteManage::setIsHold(int index, MetroSpriteStyle style, vector<int> &maps)
{
    maps[index] = 1;
    if (style == MetroSpriteStyle::widget4x2)
    {
        maps[index + gRowCount] = 1;
    }
}

void MetroSpriteManage::setMetroSpritePoint(int holdIndex, Node *sprite)
{
#if METRO_ORIENTATION_HOR
    Point p(holdIndex / gRowCount * gWidth, holdIndex % gRowCount * gHeight);
    p = Point(p.x, ((gRowCount - 1) * gHeight) - p.y);
    p += gStartPoint;
    sprite->setPosition(p);
#else
    Point p(holdIndex / gRowCount * gWidth, holdIndex % gRowCount * gHeight);
    p = Point(p.x, ((gRowCount - 1) * gHeight) - p.y);
    p += gStartPoint;
    sprite->setPosition(p);
#endif
}

void MetroSpriteManage::setMaxWidth()
{
#if METRO_ORIENTATION_HOR
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
#else
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














