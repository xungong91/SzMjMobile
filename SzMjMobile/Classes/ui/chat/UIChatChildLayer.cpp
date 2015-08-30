//  UIChatChildLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/30

#include "UIChatChildLayer.h"
#include "CocosHelper.h"
#include "XHelper.h"

UIChatChildLayer::UIChatChildLayer()
{
}

UIChatChildLayer::~UIChatChildLayer()
{
}

bool UIChatChildLayer::init()
{
    if(!Widget::init())
        return false;
    
    InitUI();
    
    return true;
}

//初始化UI
void UIChatChildLayer::InitUI()
{
    //不设置大小，listView里面添加了不在正确位置显示
    this->setContentSize(Size(1080, 250));
    
    //头像
    mAvatar = ImageView::create("chat/Chat_Head_1.png");
    mAvatar->setAnchorPoint(Vec2(0, 0));
    //mAvatar->setPosition(Vec2(20, 10));
    addChild(mAvatar);
    
    //文本背景
    mContentBg = Scale9Sprite::create(Rect(71, 16, 1, 1), "chat/Chat_TalkBg_0.png");//16, 83, 1, 1
    //mContentBg->setContentSize(Size(300, 250));
    mContentBg->setAnchorPoint(Vec2(0, 0));
    //mContentBg->setPosition(Vec2(200, 0));
    addChild(mContentBg);
    
    //文本
    mContent = ui::RichText::create();
    addChild(mContent);
    
    //SetString(1, "fghvvghfffffffffffffffffffffff虎妞迷宫 i 个 i 哦个 i 哦赶紧提哦狗 i");
}

//设置文本
void UIChatChildLayer::SetString(int viewSeatID, const string str)
{
    //添加文本
    ui::RichElementText *mElement = ui::RichElementText::create(0, Color3B(0, 0, 0), 255, str, "", 48);
    mContent->pushBackElement(mElement);
    
    //获得文本的大小
    mContent->formatText(); //没有这一句，下面获取大小为0
    Size size = mContent->getVirtualRendererSize();
    int bgWidth = 0, bgHeight = 0;
    //如果换行，则背景宽度和高度加的要少一些
    if(size.width > 800)
    {
        size = CocosHelper::changeRichTextSize(mContent, 800);
        bgWidth = size.width + 50;
        bgHeight = size.height + 20;
    }
    else
    {
        bgWidth = size.width + 90;
        bgHeight = size.height + 100;
    }
    /*
    if(bgHeight < 250)
    {
        mContentBg->setContentSize(Size(bgWidth, bgHeight));//250
        mContent->setPosition(Vec2(size.width*0.5+270, size.height*0.5 +(mContentBg->getContentSize().height-size.height)*0.5));
    }
    else
    {
        mContentBg->setContentSize(Size(bgWidth, bgHeight));
        //mContent->setPosition(Vec2(size.width*0.5+270, size.height*0.5 + 10));
        mContent->setPosition(Vec2(size.width*0.5+270, size.height*0.5 +(mContentBg->getContentSize().height-size.height)*0.5));
    }
    */
    
    if(viewSeatID == 1)
    {
        mContentBg->initWithFile(Rect(16, 16, 1, 1), "chat/Chat_TalkBg_1.png");
        mContentBg->setAnchorPoint(Vec2(0, 0));
    }
    mContentBg->setContentSize(Size(bgWidth, bgHeight));
    UpdatePos(viewSeatID);
    
    //如果高度超过该类的最大高度250，则重新设置大小(不设置大小，listView里面添加了不在正确位置显示)
    Size contentBgSize = mContentBg->getContentSize();
    if(contentBgSize.height > 250)
        this->setContentSize(contentBgSize);
}

//刷新坐标
void UIChatChildLayer::UpdatePos(int viewSeatID)
{
    //左边说话的人
    if(viewSeatID == 0)
    {
        mAvatar->setPosition(Vec2(20, 0));
        mContentBg->setPosition(Vec2(200, 0));
        mContent->setPosition(Vec2(mContent->getContentSize().width*0.5 + mContentBg->getPosition().x + 70,
                                   mContent->getContentSize().height*0.5 +(mContentBg->getContentSize().height-mContent->getContentSize().height)*0.5));
    }
    else if(viewSeatID == 1) //右边说话的人
    {
        mAvatar->setPosition(Vec2(860, 0));
        mContentBg->setPosition(Vec2(1080 - 200 - mContentBg->getContentSize().width, 0));
        mContent->setPosition(Vec2(mContent->getContentSize().width*0.5 + mContentBg->getPosition().x + 20,
                                   mContent->getContentSize().height*0.5 +(mContentBg->getContentSize().height-mContent->getContentSize().height)*0.5));
    }
}