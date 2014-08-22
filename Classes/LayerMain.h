//
//  LayerMain.h
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#ifndef demo_LayerMain_h
#define demo_LayerMain_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SingLeton.h"
#include "GameServer.h"
#include "ImageDownloader.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerMain
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public SingLeton<LayerMain>
, public PlayerCallBack
{
private:
    enum tag_CurrentView{
		tag_LayerDefault = -1,
        tag_UserInfo=0,
        tag_Money=1,
        tag_Mail=2,
        tag_Friends=3,
        tag_Service=4,
        tag_ChooseGame=5,
        tag_ChonBanChoi=6,
        tag_Rank = 7,
        tag_ChatRoom = 8,
        tag_Guide = 9,
        tag_Shop = 10,
		tag_EmailDetails,
		tag_ComposeEmail
    };
    CCLabelTTF* lblName;
    CCLabelTTF* lblAMF;
    CCLabelTTF* lblAM;
    CCLabelTTF* lblCountOfMails;
    
    CCNode* nodeAvatar;
    
    //CCSprite* img_avatar;
    
    tag_CurrentView currViewTag;
    
    CCBReader * ccbReader;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary;
    
    CCNode* currNodeView;

	ImageDownloader* imageDownloader;
public:
    LayerMain();
    virtual ~LayerMain();
    
    static LayerMain& getSingleton(void);
	static LayerMain* getSingletonPtr(void);

	void keyBackClicked();
    
	void setCurrentViewTagDefault(){
		currViewTag = tag_LayerDefault;
	}
    void loadAllMyDatas();
    
    void closeOldView();
    void removeOldView();
    //
    void gotoServices();
    void gotoChooseGame();
    void gotoChonBanChoi(int gID);
    void gotoUserInfo();

    void gotoMoney();
	void gotoTransferMoney(string toUser);

    void gotoMail();
	void gotoMailDetails(int idMsg, string fromUser, string toUser, string date, string contents);
	void gotoComposeMail(string toUser="", string title="", string contents = "");

    void gotoFriends();
    void gotoGuide();
    void gotoChat();
    void gotoShop();
    void gotoRank();
    
    void logoutAndExit();

	void autoJoinGameWithID(int gID, int rID);
    
    CREATE_FUNC(LayerMain);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
    // selector callbacks
    void onButtonUserInfo(CCObject* pSender);
    void onButtonMoney(CCObject* pSender);
    void onButtonMail(CCObject* pSender);
    void onButtonFriends(CCObject* pSender);
    void onButtonSettings(CCObject* pSender);
    void onButtonBack(CCObject* pSender);
    //HTTPCLIENT
//     void downLoadImage(string url, string fileName);
//     void onImageDownLoaded(CCHttpClient* pSender, CCHttpResponse* pResponse);
//     void loadDefaultImage();
    //Server
    void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerMainLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerMainLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerMain);
};

#endif
