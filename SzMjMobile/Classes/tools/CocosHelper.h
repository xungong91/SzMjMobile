#ifndef _C_COCOS_HELPER_H_
#define _C_COCOS_HELPER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include <string>

using namespace std;
USING_NS_CC;
using namespace ui;

enum class EnumRelativeType
{
	right = 0,
	left,
	center
};

enum class EnumVRelativeType
{
    top = 0,
    vCenter,
    bottom
};

class CocosHelper
{
public:
	static CocosHelper *singleton();
	float GetGameScale();
    void setDesignResolution( GLView* EGLView );
    Node* getScaleLayout(const string &file, Node *root, int zOlder = 0);
	float getScaleForType(float w, EnumRelativeType type);
	float getScaleCenter(float w);
	float getScaleLeft(float w);
    float getScaleRight(float w);
    float getScaleVCenter(float h);
    float getScaleTop(float h);
    float getScaleBottom(float h);
    
	Point getScaledCenter(Point p);
	Size getCurrentSize();
	Size getMaxSize();
    
    //获取指定UI
    static Node* getNodeByName(Node *root, const string &name);
    static Node* getNodeByTag(Node *root, const int &tag);
    static ui::Widget *getWidgetByName(Node *root, const string &name);
    
    //载入图片 重置imageview大小
    static Size loadTexture(ui::ImageView *image, const string &file);
    static Size loadTexturePlist(ui::ImageView *image, const string &file);
    
    //现实所有UI子树名称
    static void showNodeNames(Node *root);
    
    //动态改变RichText的Size
    static Size changeRichTextSize(cocos2d::ui::RichText *rich, float w);
    
    //设置带万金币显示 beishu 10000就是缩到1w 100000就是缩到10w
    static void setWanCoins(const int &coins, bool isAdd, const int beishu, cocos2d::ui::TextAtlas *textAtlas);
    
private:
    Size mMaxSize;          //设计尺寸
    Size mCurrentSize;
    float mGameScale;
    void setGameScale();
    
    
    static CocosHelper *mCocosHelper;
    CocosHelper();
	~CocosHelper();
	class CGarbo
	{  
	public:  
		~CGarbo()  
		{  
			if (CocosHelper::mCocosHelper)  
				delete CocosHelper::mCocosHelper;  
		}  
	};  
	static CGarbo Garbo;
};
#endif