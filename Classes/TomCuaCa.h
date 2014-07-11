//
//  TomCuaCa.h
//  iCasino_v2
//
//  Created by Tuan on 5/20/14.
//
//

#ifndef __iCasino_v2__TomCuaCa__
#define __iCasino_v2__TomCuaCa__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "AllData.h"
#include "_Avatar_inTomCuaCa.h"
#include "FrameBet.h"
#include "_Number_inGame_.h"
#include "_Chat_inGame_.h"
#include "ImageDownloader.h"

//ket qua
#define _kqNai 100
#define _kqRuou 95.8 
#define _kqGa 91.75 
#define _kqCa 87.45
#define _kqCua 83.27
#define _kqTom 79.2

//button Tag
#define t_ready 10000
#define t_unReady 10001

//-game-
#define t_tom 20001
#define t_cua 20002
#define t_ca 20003
#define t_ga 20004
#define t_ruou 20005
#define t_nai 20006

using namespace cocos2d;
using namespace cocos2d::ui;
//using namespace Sfs2X;

class TomCuaCa : public CCLayer, public PlayerCallBack{
private:
	float _count;
	boost::shared_ptr<string> _id_me;
	string _list_user;
	//Các button trong game

	UILayer *uLayer;
	UIButton *btnReady;
	UIButton *btnUnReady;
	UIButton *btnTom;
	UIButton *btnCua;
	UIButton *btnCa;
	UIButton *btnGa;
	UIButton *btnRuou;
	UIButton *btnNai;
	UIScrollView *scroll1;
	UIScrollView *scroll2;
	UIScrollView *scroll3;
	UILoadingBar *loading;
	AvatarInTomCuaCa* lAvatar;
	LayerChatInGame *layerChat;
	int _tienBet;
	int _time;
	string kq1;
	string kq2;
	string kq3;
	boost::shared_ptr<string> kq;
public:
	FrameBet* betTom;
	FrameBet* betCua;
	FrameBet* betCa;
	FrameBet* betGa;
	FrameBet* betRuou;
	FrameBet* betNai;

	ImageDownloader* imagedownloader4Red;
	ImageDownloader* imagedownloader4Black;

	TomCuaCa();
	~TomCuaCa();
	CREATE_FUNC(TomCuaCa);
	bool init();


	void createBackgrounds();
	void createAvatars();
	void createButtons();

	virtual void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	vector<string> TCCsplit(string &S,const char &str);
	void updateUser(string list);
	string find_ChuPhong(string listUser);


	void whenUserReady(string uid);
	void whenUserUnready(string uid);
	void whenGameStart();
	void whenResuiltGame(string rg);
	void whenGameEnd();
	int getPosUserByName(string uid,string _list_user);

	void clickBtn(CCObject* obj, TouchEventType type);


	int convertResponseToInt(string inString);
	string convertResponseToString(int inInt);
	float convertResult(string rs);
	virtual void update(float dt);
	void clickBet(int _tag);
	void bet(int aid, string tienBet);
	void setTimer(float dt);
	void hienKetQua();
	void hienOketqua();
	virtual void onExit();
};

#endif /* defined(__iCasino_v2__TomCuaCa__) */
