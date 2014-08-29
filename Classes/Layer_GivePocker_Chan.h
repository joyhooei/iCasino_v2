#ifndef __LAYER_GIVECARD_CHAN__
#define __LAYER_GIVECARD_CHAN__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;


class Layer_GivePocker_Chan : public cocos2d::CCLayer, public PlayerCallBack
{
public:
	CCSize *s;
	virtual bool init();  
	void onExit();
	~Layer_GivePocker_Chan();

	static cocos2d::CCScene* scene();

	void initAllCards();
	void addVirtualCard(UIImageView *img);
	void test(CCNode* sender, void* data);

	void startGivePocker();

	void moveRandomIsNotPlayerBocCai(string cards);
	void sendRequsetBocNoc();

	UIImageView* create5Cards(float posX, float posY, int mTag);

	void moveCard4User(string cards, string user);

	void givePocker(int Pos);
	void giveToPosition(float toX, float toY, int pos);
	void delayTimeturn2();
	void delayTimeEnd();

	void setIntervalBocNoc();
	void updateTimer(float dt);

	void NocTouch(CCObject *pSender,TouchEventType type);
	void BocNoc(CCObject *pSender,TouchEventType type);

	void setIsPlayerBocCai(bool isFlag);
	void setPlayerBocCai(string player);

	string findTypeCard(string number,string suite);

	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	void moveCardsToPosition();

	int getPosUserByName(string uid,string _list_user);
	void setListusers(string listusers);

	string getNamePlayer(string uid);

	vector<int> sortArrayTag(vector<int> _arr, int position);
	void chiaBai(vector<int> toPos, vector<int> allTag);
	void finishGive(UIImageView *img, int tpos);

	void killLayer();

	CREATE_FUNC(Layer_GivePocker_Chan);
private:

	bool isPlayerBocCai;
	string playerBocCai;
	string listusers;

	string playerStart;

	vector<int> arrTag;

	UILayer *uLayer;
	UIImageView *noc;
	UIImageView *noc2;

	UILabelBMFont *timer;
	float _startTimmer;

	CCArray *P_NOC;

	UIImageView *B1;
	UIImageView *B2;
	UIImageView *B3;
	UIImageView *B4;
	UIImageView *B5;
	UIImageView *B6;
	UIImageView *B7;
	UIImageView *B8;
	UIImageView *B9;
	UIImageView *B10;

	bool flag_ChonNoc;
	bool flagBocCai;
	int countLeft;
	int countRight;

	int index_Noc;
	int index_Choose;

	float c1_leftX;
	float c1_leftY;

	float c2_leftX;
	float c2_leftY;

	float c3_leftX;
	float c3_leftY;

	float c4_leftX;
	float c4_leftY;

	float c5_leftX;
	float c5_leftY;

	float c1_rightX;
	float c1_rightY;

	float c2_rightX;
	float c2_rightY;

	float c3_rightX;
	float c3_rightY;

	float c4_rightX;
	float c4_rightY;

	float c5_rightX;
	float c5_rightY;
};


#endif // __LAYER_GIVECARD_CHAN__
