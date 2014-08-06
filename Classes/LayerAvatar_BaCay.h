//
//  LayerAvatar_BaCay.h
//  iCasino_v2
//
//  Created by DauA on 6/26/14.
//  4 avatar for game
//
// 
//

#ifndef __iCasino_v2___LayerAvatar_BaCay___
#define __iCasino_v2___LayerAvatar_BaCay___

#include <iostream>
#include "cocos2d.h"
#include "_Avatar_.h"

using namespace cocos2d;
using namespace std;

class LayerBaCayAvatar : public CCLayer
{
public:
	~LayerBaCayAvatar();
	virtual void onExit();
	virtual bool init();
	CREATE_FUNC(LayerBaCayAvatar);

	void setIcon (int pos, char *url);
	void setFlag (int pos, bool isShow);
	void setName (int pos, string name);
	void setMoney(int pos, string money);
	void setMoney(int pos, int money);
	void setReady(int pos, bool isReady);
	void setVisibleLayerInvite(int pos, bool isShow);

	void resetAll();
	void setPosChuong(int pos);

	void setUnReadyAllUser();
	void resetGame();

	void setListUserForBaCay(string listUser);

	Avatar* getUserByPos(int pos);
    UIButton *btn_xem;

	int getPosByName(string name);
	string getNameByPos(int pos);
	//

	void updateUsers();

	void runTimer(int posUser);
	void stopAllTimer();
    void vaoBanChoi(CCObject* obj, TouchEventType type);
    void meIsSpec();
    void specToPlayer();
private:
	string myName;
	string listUser;
	UIImageView *chuong;
    
	boost::shared_ptr<User> myself;
};

#endif