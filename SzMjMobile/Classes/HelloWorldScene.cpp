#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CoinsTo.h"
#include "CTestDrawLayer.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;
using namespace std;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

int gStep = 1;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Menu *menu = Menu::create();
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    Text *text = Text::create();
    text->setFontSize(40);
    text->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
    text->setString("100");
    this->addChild(text);
    
    addTestSprite();
    MenuItem *item1 = MenuItemFont::create("点我啊", [text](Ref *sender)
                                           {
                                               text->stopAllActions();
                                               CoinsTo *coinsTo = CoinsTo::create(3.0f, "1000", text);
                                               text->runAction(Sequence::create(coinsTo, NULL));
                                           });
    item1->setPosition(Point(480, 500));
    
    
    MenuItem *item2 = MenuItemFont::create("创建", [this](Ref *sender)
                                           {
                                               this->addChild(CTestDrawLayer::create(), 1);
                                           });
    item2->setPosition(Point(480, 400));
    
    
    
    menu->addChild(item1);
    menu->addChild(item2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::addTestSprite()
{
    mTestSprite = Sprite::create("CloseNormal.png");
    mTestSprite->setPosition(Point(200, 200));
    this->addChild(mTestSprite);
}

void HelloWorld::removeTestSprite()
{
    if (mTestSprite)
    {
        this->removeChild(mTestSprite);
        mTestSprite = nullptr;
    }
}
