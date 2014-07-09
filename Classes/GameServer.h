//
//  GameServer.h
//  iCasino_v2
//
//  Created by AlexDao on 5/13/14.
//
//

#ifndef iCasino_v2_GameServer_h
#define iCasino_v2_GameServer_h

#include "SingLeton.h"

#include "SmartFox.h"
#include "Core/BaseEvent.h"

#include "cocos2d.h"

using namespace Sfs2X;

enum eEventTags
{
    tag_EventConnection,
    tag_EventConnectionLost,
	tag_EventDisconnected,
	tag_EventSocketError,
    //
    tag_EventLogin,
    tag_EventLoginError,
    tag_EventLogout0,
    //
    tag_EventRoomJoin,
    tag_EventRoomJoinError,
    tag_EventCreationError,
    tag_EventRoomAdd,
    tag_EventRoomVariableUpdate,
    tag_EventRoomPasswordStateChange,
    tag_EventRoomPasswordStateChangeError,
    //
    tag_EventPublicMessage,
    tag_EventUserVariableUpdate,
    tag_EventUserCountChange,
    tag_EventUserEnterRoom,
    tag_EventUserExitRoom,
    tag_EventSpectatorToPlayerError,
    tag_EventPlayerToSpectatorError,
    tag_EventInvitation,
    //
    tag_EventExtensionResponse,
};

//the callback from the server
class PlayerCallBack
{
public:
    virtual void OnSmartFoxConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxDisconnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxSocketError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
    
	virtual void OnSmartFoxLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
    
    virtual void OnSmartFoxLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	
	virtual void OnSmartFoxRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxRoomJoinError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxRoomAdd(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxRoomVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxRoomPasswordStateChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxRoomPasswordStateChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
    
	virtual void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
    
	virtual void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxUserCountChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxUserEnterRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxSpectatorToPlayerError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
	virtual void OnSmartFoxPlayerToSpectatorError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
    
	virtual void OnSmartFoxInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
    
	virtual void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){};
};


typedef std::map< int , PlayerCallBack * > PlayerCallBackMap;
typedef std::map< int , PlayerCallBack * >::iterator PlayerCallBackMapIter;
typedef std::pair< int , PlayerCallBack * > PlayerCallBackMapPair;

//the GameServer control the sfs2x message
class GameServer : public SingLeton<GameServer>
{
public:
	GameServer( );
    
	virtual ~GameServer(){};
    
	static GameServer& getSingleton(void);
	static GameServer* getSingletonPtr(void);
    
	// add listeners
	void addListeners( PlayerCallBack * callBack );
	void removeListeners( PlayerCallBack * callBack );
    
	//init the server, and set ThreadSafeMode to true
	void initServer( );
    
	//update the server manually
	void updateEvent( );
    
	//get the smartfox
	boost::shared_ptr<Sfs2X::SmartFox> getSmartFox(){ return mSmartFox;};
    
	//connect
	void connectToServer( const char * strIP, const char * strPort );
	//smartfox callback
	static void OnSmartFoxConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxDisconnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxSocketError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    
	static void OnSmartFoxLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    static void OnSmartFoxLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	
	static void OnSmartFoxRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxRoomJoinError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxRoomAdd(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxRoomVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxRoomPasswordStateChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxRoomPasswordStateChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    
	static void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    
	static void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxUserCountChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxUserEnterRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxSpectatorToPlayerError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void OnSmartFoxPlayerToSpectatorError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    
	static void OnSmartFoxInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    
	static void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	//Log
	static void OnDebugMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) ;
    
public: //4 notify
    void OnSmartFoxNtf(eEventTags tag, unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
private:
	boost::shared_ptr<Sfs2X::SmartFox> mSmartFox;
    
	PlayerCallBackMap mCallBack;
	int mCallBackIndex;
};

#endif
