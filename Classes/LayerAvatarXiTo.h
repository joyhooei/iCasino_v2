//
//  LayerAvatarXiTo.h
//  iCasinov2
//
//  Created by DauA on 5/28/14.
//
//

#ifndef __iCasinov2__LayerAvatarXiTo__
#define __iCasinov2__LayerAvatarXiTo__

#include "cocos2d.h"
#include "_Avatar_.h"
#include "_Number_.h"
using namespace cocos2d;


enum {
    user_me,
    user_rightBottom,
    user_rightTop,
    user_leftTop,
    user_leftBottom
};

class LayerAvatarXiTo : public CCLayer{
private:
    float widthAvatar;
	float heightAvatar;
    Avatar *me,*left_bottom,*left_top,*right_bottom,*right_top;
    
    float bt_card_me;
    float bt_card_bottom;
    float bt_card_top;
    
    float lf_card_me;
    float lf_card_left_bottom;
    float lf_card_left_top;
public:
    LayerAvatarXiTo();
    ~LayerAvatarXiTo();
    virtual bool init();
    CREATE_FUNC(LayerAvatarXiTo);
    void setIcon(int pos,const char *url);
    void setFlag(int pos, bool isShow);
    void setName(int pos,const char *name);
    void setMoney(int pos,const char *money);
    void resetAll();
    void stopAllTimer();
	void setUnReadyAllUser();
    
    void showNunberByPos(int pos, string numberString);
    Avatar* getUserByPos(int pos);
};

#endif /* defined(__iCasinov2__LayerAvatarXiTo__) */
