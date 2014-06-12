//
//  SliderCustomLoader.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_SliderCustomLoader_h
#define demo_SliderCustomLoader_h

#include "cocos2d.h"

using namespace cocos2d;

class SliderCustomLoader : public cocos2d::extension::CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SliderCustomLoader, loader);
protected:
    virtual CCControlSlider * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCControlSlider* slider = CCControlSlider::create("frame_scroll.png", "light_scroll.png", "button_scroll.png");
        return slider;
    }
};

#endif
