//
//  _Avatar_inGame_.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/15/14.
//  4 avatar for game
//
// // parent->this===>setListUserBy...->formatAndStore->updateUsers.
//

#ifndef __iCasino_v2___Avatar_inGame___
#define __iCasino_v2___Avatar_inGame___

#include <iostream>

#include "cocos2d.h"
//
#include "AllData.h"
#include "_Avatar_.h"

using namespace cocos2d;

class LayerAvatarInGame : public CCLayer
{
public:
	~LayerAvatarInGame();
	virtual void onExit();
    virtual bool init();
    CREATE_FUNC(LayerAvatarInGame);
    
    void setIcon (int pos, char *url);
    void setFlag (int pos, bool isShow);
    void setName (int pos, string name);
    void setMoney(int pos, string money);
	void setMoney(int pos, int money);
	void setMoney(int pos, double money);
    void setReady(int pos, bool isReady);
	void setVisibleLayerInvite(int pos, bool isShow);
    
    void resetAll();
    void setPosChuong(int pos);
    
    void setUnReadyAllUser();
    void resetGame();
    
    void setListUserByPhom(string listUser);
    void setListUserByTienLen(string listUser);
    //
    void formatAndStore(const char &c1, const char &c2);
    
    Avatar* getUserByPos(int pos);
    
    int getIndexInArrByName(string name);
	int getIndexInArrByAccountID(string aI);
    //
    int getPosByName(string name);
	int getPosByAccountID(string aI);
    string getNameByPos(int pos);
	string getAccountIDByPos(int pos);
    //
    void updateUsers();
    
    // Time
    void runTimer(int posUser);
    void stopAllTimer();
    
private:
	enum NAME_GAME {
		PHOM = 1,
		TIEN_LEN
	};

	int typeGame;
	bool isGuess;
	string myName;
	string myAI;
    string listUser;
    
    // mảng chứa
    vector<string> arrName;
    vector<string> arrFlag;
    vector<string> arrURL;
	vector<string> arrAI;
	vector<int> arrMoney;
	vector<double> arrMoneyDouble;
    UIImageView *chuong;
};

#endif /* defined(__iCasino_v2___Avatar_inGame___) */
