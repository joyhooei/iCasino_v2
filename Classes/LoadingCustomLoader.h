//
//  LoadingCustomLoader.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LoadingCustomLoader_h
#define demo_LoadingCustomLoader_h


#include "cocos2d.h"

using namespace cocos2d;

class LoadingCustomLoader : public cocos2d::extension::CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoadingCustomLoader, loader);
protected:
    virtual CCControlSlider * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
		CCControlSlider* slider = CCControlSlider::create(CCSprite::createWithSpriteFrameName("assest/frame_scroll.png")
			, CCSprite::createWithSpriteFrameName("assest/light_scroll.png")
			, CCSprite::createWithSpriteFrameName("assest/button_scroll.png") );
        slider->setMaximumValue(1000);
        slider->setMinimumValue(100);
        CCLOG("Im here");
        //slider->setPosition(pParent->getPo);
        //slider->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerDMK::valueChanged), CCControlEventValueChanged);
        
        return slider;
    }
};

#endif
