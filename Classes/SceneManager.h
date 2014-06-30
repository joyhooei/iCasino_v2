//
//  SceneManager.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/14/14.
//

#ifndef __iCasino_v2__SceneManager__
#define __iCasino_v2__SceneManager__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SmartFox.h"
#include "Core/BaseEvent.h"
#include "GameServer.h"
#include "SingLeton.h"

#include "Requests/LoginRequest.h"

#include "NotificationCallBack.h"
#include "AllData.h"

#include "LayerLogin.h"
#include "LayerMain.h"
#include "LayerPlayGame.h"
#include "LayerPlayGameTLMN.h"
#include "LayerPlayGameTLMB.h"
#include "LayerPlayGamePhom.h"

#include "BaCayNormal.h"
#include "BaCayChuong.h"
#include "Lieng.h"
#include "XiTo.h"
#include "LayerChanGame.h"

#include "LayerNotification.h"
#include "LayerLoading.h"
#include "TomCuaCa.h"

#include "LayerChatWindow.h"
//----------------
using namespace Sfs2X;
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

enum eLayerTags
{
	tag_LayerLogin,
	tag_LayerMain,
	tag_LayerGaming,
	tag_LayerNotification,
	tag_LayerLoading
};

enum eLayerZOrders
{
	zorder_LayerLogin=0,
	zorder_LayerMain,
	zorder_LayerGaming,
	zorder_layerLoading,
	zorder_LayerNotification = 1000
};

enum typeShowHideLayer
{
	None,
	fromLeft,
	fromRight,
	toLeft,
	toRight
};

class SceneManager : public CCLayer, public SingLeton<SceneManager>, public PlayerCallBack
{
private:
	// layers
	LayerPlayGame *mLayerPlayGame;

	LayerLogin *layerLogin;
	LayerMain *layerMain;
	LayerNotification* layerNotification;
	LayerLoading *layerLoading;

	LayerPlayGameTLMN *mGameTLMN;
	LayerPlayGameTLMB *mGameTLMB;
	LayerPlayGamePhom *mGamePhom;
	BaCayNormal *mBaCayNormal;
	BaCayChuong *mBaCayChuong;
	Lieng *mGameLieng;
	XiTo *mGameXiTo;
	LayerChanGame *mGameChan;

	LayerChatWindow* mLayerChatWindow;

	TomCuaCa *mGameTomCuaCa;

	CCSize SIZE_SCREEN;

	CCBReader * ccbReader;
	CCNodeLoaderLibrary * ccNodeLoaderLibrary;

	CCSprite *background;
	CCSprite *background_Chan;

	eLayerTags mCurrentLayerTag;
public:
	
	SceneManager();
	virtual ~SceneManager(){};

	static SceneManager& getSingleton(void);
	static SceneManager* getSingletonPtr(void);

	CCNodeLoaderLibrary* getNodeLoaderLibrary(){
		return ccNodeLoaderLibrary;
	}

	LayerLogin* getLayerLogin(){
		return layerLogin;
	}

	eLayerTags getCurrentLayerTag(){
		return mCurrentLayerTag;
	}

	LayerChatWindow* getLayerChatWindow(){
		return mLayerChatWindow;
	}
	bool showLayerChatWindow();
	bool hideLayerChatWindow();

	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(SceneManager);

	static CCScene* createScene();

	bool showLayer(CCLayer *pLayer);
	bool hideLayer(CCLayer *pLayer);

	bool showNotification();
	bool hideNotification();


	void showLoading();
	void hideLoading();

	void disconnectFromServer();
	// switch layers
	void gotoLogin();
	void gotoMain();
	void gotoGameByTag(int typeGame);

	void releaseCurrentLayerGame();

	// exit
	void exitScene();

	// getLayers
	// inline LayerLogin  *getLayerLogin()   { return mLayerLogin; }
	// inline LayerMain   *getLayerMain() { return mLayerMain; }
	inline LayerPlayGamePhom *getLayerGamePhom() { return mGamePhom; };
	inline LayerNotification* getLayerNotification() { return layerNotification; };
	inline LayerPlayGameTLMN *getLayerGameTLMN() { return mGameTLMN; };
	//update schedule, for update the server manually
	void updateEvent( float dt );
	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxDisconnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxSocketError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	// get, set
	//string getMyID();
	string getMyName();
	void setBackgroundScreen(bool _state);
};

#endif /* defined(__iCasino_v2__SceneManager__) */
