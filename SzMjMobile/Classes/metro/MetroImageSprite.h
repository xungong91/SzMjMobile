//
//  MetroImageSprite.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/14.
//
//

#ifndef __SzMjMobile__MetroImageSprite__
#define __SzMjMobile__MetroImageSprite__

#include "BaseMetroSprite.h"

class MetroImageSprite : public BaseMetroSprite
{
public:
    CREATE_FUNC(MetroImageSprite);
    bool init();
    
    void loadImages();
    
    void setStyle(MetroSpriteStyle style) override;
    
    void onSelect() override;
    void onSelectLeave(bool isMove) override;
protected:
    Sprite *mImage;
    
    void imageRun();
};

#endif /* defined(__SzMjMobile__MetroImageSprite__) */
