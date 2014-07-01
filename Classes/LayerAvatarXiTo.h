//
//  LayerAvatarXiTo.h
//  iCasinov2
//
//  Created by DauA on 5/28/14.
//
//

#ifndef __iCasinov2__LayerAvatarXiTo__
#define __iCasinov2__LayerAvatarXiTo__

#include <iostream>
#include "cocos2d.h"
#include "_Avatar_.h"
using namespace cocos2d;
using namespace std;

class LayerAvatarXiTo : public CCLayer{
public:
    LayerAvatarXiTo();
    ~LayerAvatarXiTo();
    virtual bool init();
    CREATE_FUNC(LayerAvatarXiTo);
    void setIcon(int pos,const char *url);
    void setFlag(int pos, bool isShow);
    void setName(int pos,const char *name);
    void setMoney(int pos,const char *money);

	void resetAvatar(Avatar* avatar);

    void resetAll();
    void stopAllTimer();
	void runTimer(int pos);

	void setUnReadyAllUser();
    
    void showNunberByPos(int pos, string numberString);
    Avatar* getUserByPos(int pos);

	void updateUser();

	void setListUserXiTo(string _listusers);
	void setMyName(string myname);

	int getPosByName(string pName);
};

#endif /* defined(__iCasinov2__LayerAvatarXiTo__) */
