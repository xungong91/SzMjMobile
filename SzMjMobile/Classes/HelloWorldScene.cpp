#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ShareHelper.h"
#include "MetroMainLayer.h"
#include "UIMainLayer.h"
#include "CrashHelper.h"
#include "UIMediaSelectLayer.h"
#include "XHelper.h"
#include "CocosHelper.h"

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
    scene->setAnchorPoint(Point(0.5, 0));
//    scene->setScaleY(1.025f);
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
    auto winSize = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create("HelloWorld.png");
    bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
    
    this->addChild(bg);
    
    Label *text = Label::create();
    text->setPosition(Point(winSize.width / 2, winSize.height * 9 / 10));
    this->addChild(text);
    
    auto itme1 = MenuItemFont::create("微信登录", [text](Ref *sender)
                          {
                              CCLOG("touchItem1");
                              ShareHelper::singleton()->sendAuth(ShareType::weixin, [text](bool b, const string &id)
                                                                 {
                                                                     if (b)
                                                                     {
                                                                         text->setString(id);
                                                                     }
                                                                     else
                                                                     {
                                                                         text->setString("登录失败");
                                                                     }
                                                                 });
                          });
    itme1->setPosition(Point(100, 50));
    
    auto item2 = MenuItemFont::create("发送微信", [](Ref* sender)
                                      {
                                          string fileName;
                                          stringstream ss;
                                          ss<<"screenshot_share.png";
                                          ss>>fileName;
                                          
                                          utils::captureScreen
                                          (
                                           [](bool succeed, const std::string& outputFile)
                                           {
                                               if (succeed)
                                               {
                                                   ShareHelper::singleton()->onShareLink(ShareType::weixin, outputFile);
                                               }
                                           }, fileName);
                                          
                                          CCLOG("touchItem2");
                                      });
    item2->setPosition(Point(100, 100));
    
    auto item3 = MenuItemFont::create("metro风格", [this](Ref *sender)
                                      {
                                          Director::getInstance()->getRunningScene()->removeChild(this);
                                          Director::getInstance()->getRunningScene()->addChild(MetroMainLayer::create());
                                      });
    item3->setPosition(Point(100, 150));
    
    auto item4 = MenuItemFont::create("UI界面", [this](Ref *sender)
                                      {
                                          Director::getInstance()->getRunningScene()->removeChild(this);
                                          Director::getInstance()->getRunningScene()->addChild(UIMainLayer::create());
                                      });
    item4->setPosition(Point(100, 200));
    
    auto item5 = MenuItemFont::create("崩溃按钮", [this](Ref *sender)
                                      {
                                          CrashHelper::singleton()->throwError();
                                      });
    item5->setPosition(Point(100, 250));
    
    auto item6 = MenuItemFont::create("选择多媒体界面", [this](Ref *sender)
                                      {
                                          this->addChild(UIMediaSelectLayer::create());
                                      });
    item6->setPosition(Point(100, 300));
    
    RichText *test = RichText::create();
    
    RichElementText* re1 = RichElementText::create(1, Color3B::YELLOW, 255, "asdfasdfsadfasdfasdfasdfasdfas工地是否广东省分公司的法国大使馆发的损公肥私的分公司的史蒂夫根深蒂固", "fonts/arial.ttf", 20);
    test->pushBackElement(re1);
    test->setPosition(getPointHalf(getSizeWin()));
    this->addChild(test);
    
    auto item7 = MenuItemFont::create("测试按钮", [this, test](Ref *sender)
                                      {
                                          CocosHelper::changeRichTextSize(test, 200);
                                      });
    item7->setPosition(Point(100, 350));
    
    
    auto menu = Menu::create(itme1, item2, item3, item4, item5, item6, item7, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    

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
