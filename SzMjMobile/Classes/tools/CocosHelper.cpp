#include "CocosHelper.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

using namespace ui;
using namespace cocostudio;

CocosHelper * CocosHelper::mCocosHelper = NULL;

CocosHelper::CGarbo CocosHelper::Garbo;

CocosHelper::CocosHelper()
{
	//setGameScale();
	mMaxSize = Size(1080, 1920);  // <3:2 = 960 720
}

CocosHelper::~CocosHelper()
{
	mCocosHelper = NULL;
}

CocosHelper * CocosHelper::singleton()
{
	if (mCocosHelper == NULL)
	{
		mCocosHelper = new CocosHelper();
	}
	return mCocosHelper;
}

float CocosHelper::GetGameScale()
{
	return mGameScale;
}

cocos2d::Size CocosHelper::getCurrentSize()
{
	return mCurrentSize;
}

void CocosHelper::setGameScale()
{
	Size resolutionSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	mGameScale = ((frameSize.height*resolutionSize.width)/(resolutionSize.height*frameSize.width));

//	CLogHelper::singleton()->Log(CCString::createWithFormat("∆¡ƒªµƒÀı∑≈±»¿˝Œ™£∫ %f", mGameScale)->getCString());
}

void CocosHelper::setDesignResolution( GLView* EGLView )
{
//    Size currentSize = CCDirector::getInstance()->getWinSize();
//    float wight ,height;
//    if (currentSize.width/currentSize.height >= mMaxSize.width/mMaxSize.height)
//    {
////        wight = currentSize.width/currentSize.height *mMaxSize.height;
////        height = mMaxSize.height;
////        mCurrentSize = Size(wight, mMaxSize.height);
//        
//        wight = mMaxSize.width;
//        height = currentSize.height/currentSize.width *mMaxSize.width;
//        mCurrentSize = Size(wight, height);
//    }
//    else
//    {
//        wight = mMaxSize.width;
//        height = currentSize.height / currentSize.width * mMaxSize.width;
//        mCurrentSize = Size(wight, height);
//    }
//    EGLView->setDesignResolutionSize(mCurrentSize.width, mCurrentSize.height, ResolutionPolicy::EXACT_FIT);
//    
//    mGameScale = 1;
    
    mCurrentSize = mMaxSize;
    EGLView->setDesignResolutionSize(mCurrentSize.width, mCurrentSize.height, ResolutionPolicy::EXACT_FIT);
}

Node* CocosHelper::getScaleLayout( const string &file, Node *root, int zOlder)
{
    auto node = CSLoader::createNode(file.c_str());
    root->addChild(node, zOlder);
    
    auto *panel = CocosHelper::getNodeByName(node, "Layer");
    if (panel)
    {
        panel->setContentSize(mCurrentSize);
        Helper::doLayout(panel);
    }
    
    return node;
}

float CocosHelper::getScaleForType( float w, EnumRelativeType type )
{
	float reseltF;
	switch (type)
	{
	case EnumRelativeType::right:
		reseltF = getScaleRight(w);
		break;
	case EnumRelativeType::left:
		reseltF = getScaleLeft(w);
		break;
	case EnumRelativeType::center:
		reseltF = getScaleCenter(w);
		break;
	default:
		break;
	}
	return reseltF;
}

float CocosHelper::getScaleCenter( float w )
{
	return mCurrentSize.width/2 - (mMaxSize.width/2 - w);
}

float CocosHelper::getScaleLeft( float w )
{
	return w;
}

float CocosHelper::getScaleRight( float w )
{
	return mCurrentSize.width - (mMaxSize.width - w);
}

float CocosHelper::getScaleVCenter(float h)
{
    return mCurrentSize.height/2 - (mMaxSize.height/2 - h);
}

float CocosHelper::getScaleTop(float h)
{
    return mCurrentSize.height - (mMaxSize.height - h);
}

float CocosHelper::getScaleBottom(float h)
{
    return h;
}

cocos2d::Point CocosHelper::getScaledCenter( Point p )
{
	return (p + Point(mCurrentSize.width / 2, mCurrentSize.height / 2));
}

Size CocosHelper::getMaxSize()
{
	return mMaxSize;
}

Node* CocosHelper::getNodeByName(Node *root, const string &name)
{
    if (root->getName() == name)
    {
        return root;
    }
    
    Vector<Node*> &childs = root->getChildren();
    for (auto it = childs.begin(); it !=childs.end(); ++it)
    {
        if ((*it)->getName() == name)
        {
            return *it;
        }
        else
        {
            Node *node = getNodeByName(*it, name);
            if (node)
            {
                return node;
            }
        }
    }
    return nullptr;
}

Node* CocosHelper::getNodeByTag(Node *root, const int &tag)
{
    if (root->getTag() == tag)
    {
        return root;
    }
    
    Vector<Node*> &childs = root->getChildren();
    for (auto it = childs.begin(); it !=childs.end(); ++it)
    {
        if ((*it)->getTag() == tag)
        {
            return *it;
        }
        else
        {
            Node *node = getNodeByTag(*it, tag);
            if (node)
            {
                return node;
            }
        }
    }
    return nullptr;
}

ui::Widget *CocosHelper::getWidgetByName(Node *root, const string &name)
{
    return static_cast<Widget*>(getNodeByName(root, name));
}

void CocosHelper::showNodeNames(Node *root)
{
    Vector<Node*> &childs = root->getChildren();
    for (auto it = childs.begin(); it !=childs.end(); ++it)
    {
        showNodeNames(*it);
    }
}

Size CocosHelper::loadTexture(ImageView *image, const string &file)
{
    image->loadTexture(file);
    Size size = Director::getInstance()->getTextureCache()->getTextureForKey(file)->getContentSize();
    image->setContentSize(size);
    return size;
}

Size CocosHelper::loadTexturePlist(ui::ImageView *image, const string &file)
{
    image->loadTexture(file, TextureResType::PLIST);
    auto it = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
    Size size = it->getRect().size;
    image->setContentSize(size);
    return size;
}

Size CocosHelper::changeRichTextSize(RichText *rich, float w)
{
    Size sResult(0 ,0);
    
    rich->ignoreContentAdaptWithSize(true);
    rich->formatText();
    Size autoSize = rich->getVirtualRendererSize();
    int hCount = (int)(autoSize.width / w) + 1;
    sResult = Size(w, autoSize.height * hCount);
    
    rich->ignoreContentAdaptWithSize(false);
    rich->setContentSize(sResult);
    
    return sResult;
}

void CocosHelper::setWanCoins(const int &coins, bool isAdd, const int beishu, cocos2d::ui::TextAtlas *textAtlas)
{
    //去正负号
    int scoin = coins > 0 ? coins : -coins;
    //展示的
    char ccoin[30];
    if(scoin >= beishu)
    {
        sprintf(ccoin, "/%d", (scoin / 10000));
    }
    else
    {
        sprintf(ccoin, "/%d", scoin);
    }
    
    //显示加号
    if(isAdd)
    {
        textAtlas->setProperty(ccoin, "fonts/num_orange.png", 17, 17, "/");
    }
    else
    {
        textAtlas->setProperty(ccoin, "fonts/num_green.png", 17, 19, "/");
    }
    
    textAtlas->setString(ccoin);
    
    if(scoin >= beishu)
    {
        ImageView *Image_wan;
        if (textAtlas->getChildrenCount() != 0)
        {
            Image_wan = static_cast<ImageView*>(textAtlas->getChildren().back());
        }
        else
        {
            Image_wan = ImageView::create();
            textAtlas->addChild(Image_wan);
        }
        //显示万字
        Image_wan->setAnchorPoint(Point(0, 0));
        if(isAdd)
        {
            Image_wan->loadTexture("fonts/num_orange_wan.png");
        }
        else
        {
            Image_wan->loadTexture("fonts/num_green_wan.png");
        }
        Image_wan->setPosition(Point(textAtlas->getContentSize().width, 0));
    }
}












