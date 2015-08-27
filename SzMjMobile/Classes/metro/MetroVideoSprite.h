//
//  MetroVideoSprite.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#ifndef __SzMjMobile__MetroVideoSprite__
#define __SzMjMobile__MetroVideoSprite__

#include "BaseMetroSprite.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UIVideoPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace experimental::ui;

class MetroVideoSprite : public BaseMetroSprite
{
public:
    CREATE_FUNC(MetroVideoSprite);
    bool init();
    
    void setStyle(MetroSpriteStyle style) override;
    void onSelect() override;
    void onSelectLeave(bool isMove) override;
    
//    void
private:
    bool mIsPlay;
    VideoPlayer* mVideoPlayer;
};

#endif /* defined(__SzMjMobile__MetroVideoSprite__) */
