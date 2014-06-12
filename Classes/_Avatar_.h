//
//  AvatarLayer.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/14/14.
//
//

#ifndef __iCasino_v2__AvatarLayer__
#define __iCasino_v2__AvatarLayer__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LayerPlayerInfo.h"
#include "LayerMoiChoi.h"

#include "_Chat_.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::extension;

class Avatar : public CCLayer
{
public:
    Avatar(bool isMe);
    
    CCSize getSizeThis();
    
    void onTouch(CCObject *pObject, TouchEventType pType);
    
	void hideLayerInvite();
	void showLayerInvite();
    void setVisibleLayerInvite(bool isShow);
    
    void setIcon(string url);
    void setFlag(bool isShow);
    void setName(string name);
    void setMoney(string money);
	void setMoney(int money);
    void setReady(bool isReady);
	void setAI(string ai);
	void setMeIsBoss( bool isBoss ); 
    
    void startTimer();
    void stopTimer();
    
    void callbackTimer(CCNode *pSender);
    string convertMoney(int money);

    // hoangdd
    void downLoadImage(string url, string fileName);
    void onImageDownLoaded(CCHttpClient* pSender, CCHttpResponse* pResponse);
    void loadDefaultImage();
    
private:
    enum {
        tagIcon = 0,
        tagInvite
    };
    
    bool isMe;
	bool meIsBoss;
	string aI;
	string nameString;
    CCSize sizeThis;
    CCSize sizeIcon;
    
    CCProgressTimer *timer;
    
    UILayer   *layerWidget;
    UILayer   *layerInvite;
    ImageView *bg;
    ImageView *icon, *flag;
    CCLabelTTF *name, *money;

	LayerPlayerInfo* layerPlayerInfo;
	LayerMoiChoi* layerMoiChoi;
};

#endif /* defined(__iCasino_v2__AvatarLayer__) */
