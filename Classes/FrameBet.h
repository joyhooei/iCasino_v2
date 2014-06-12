//
//  FrameBet.h
//  iCasinov2
//
//  Created by DauA on 5/26/14.
//
//

#ifndef __iCasinov2__FrameBet__
#define __iCasinov2__FrameBet__

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::ui;
class FrameBet : public CCLayer{
private:
    CCSprite *iconXu;
    UIImageView *frame;
    UILabel *money;
public:
    FrameBet();
    ~FrameBet();
    bool init();
    CREATE_FUNC(FrameBet);
    void setFrameSize(float toSize);
    void setValueBet(std::string value);
    float getKc_width();
};


#endif /* defined(__iCasinov2__FrameBet__) */
