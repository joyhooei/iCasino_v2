//
//  GameServer.cpp
//  iCasino_v2
//
//  Created by AlexDao on 5/13/14.
//
//

#include "GameServer.h"

#include "Bitswarm/BitSwarmEvent.h"
#include "Util/EventDispatcher.h"
#include "Requests/LoginRequest.h"
#include "Requests/LogoutRequest.h"

#include "Requests/JoinRoomRequest.h"
#include "Requests/CreateRoomRequest.h"
#include "Requests/RoomSettings.h"
#include "Requests/PublicMessageRequest.h"
#include "Requests/ExtensionRequest.h"
#include "Requests/SetUserVariablesRequest.h"

#include "Entities/Variables/SFSUserVariable.h"

template<> GameServer* SingLeton<GameServer>::mSingleton = 0;
GameServer* GameServer::getSingletonPtr(void)
{
	return mSingleton;
}
GameServer& GameServer::getSingleton(void)
{
	assert( mSingleton );  return ( *mSingleton );
}

GameServer::GameServer(  )
{
	mSmartFox = boost::shared_ptr<Sfs2X::SmartFox>();
	mCallBack.clear();
	mCallBackIndex = 0;
}

void GameServer::addListeners( PlayerCallBack * callBack )
{
	if ( callBack == NULL )
		return;
    
	PlayerCallBackMapIter iTer = mCallBack.begin();
    
	for ( ; iTer != mCallBack.end() ; iTer ++ )
	{
		//if callback already exist, return
		if ( iTer->second == callBack )
			return;
	}
    
	mCallBack.insert(PlayerCallBackMapPair(mCallBackIndex++,callBack));
}
void GameServer::removeListeners( PlayerCallBack * callBack ){
    if ( callBack == NULL )
		return;
	CCLOG("GameServer::removeListeners() - BEGIN");
	PlayerCallBackMapIter iTer = mCallBack.begin();
    
	for ( ; iTer != mCallBack.end() ; iTer ++ )
	{
		//if callback already exist, return
		if ( iTer->second == callBack ){
			mCallBack.erase(iTer);
			CCLOG("GameServer::removeListeners() - EXECUTE");
			return;
        }
	}

}

void GameServer::initServer( )
{
	// Initialize Smart Fox
	mSmartFox = boost::shared_ptr<Sfs2X::SmartFox>(new Sfs2X::SmartFox(true));
	mSmartFox->ThreadSafeMode(true);
    mSmartFox->Debug(true);
	// Add event listeners
    mSmartFox->AddEventListener(SFSEvent::CONNECTION, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxConnection, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::CONNECTION_LOST, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxConnectionLost, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::SFS_SOCKET_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxSocketError, (unsigned long long)this)));
    
	mSmartFox->AddEventListener(SFSEvent::LOGIN, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxLogin, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::LOGIN_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxLoginError, (unsigned long long)this)));
    mSmartFox->AddEventListener(SFSEvent::LOGOUT, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxLogout, (unsigned long long)this)));
	
	mSmartFox->AddEventListener(SFSEvent::ROOM_JOIN, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxRoomJoin, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::ROOM_JOIN_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxRoomJoinError, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::ROOM_CREATION_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxRoomCreationError, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::ROOM_ADD, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxRoomAdd, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::ROOM_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxRoomVariableUpdate, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::ROOM_PASSWORD_STATE_CHANGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxRoomPasswordStateChange, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::ROOM_PASSWORD_STATE_CHANGE_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxRoomPasswordStateChangeError, (unsigned long long)this)));
    
	mSmartFox->AddEventListener(SFSEvent::PUBLIC_MESSAGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxPublicMessage, (unsigned long long)this)));
    
	mSmartFox->AddEventListener(SFSEvent::USER_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxUserVariableUpdate, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::USER_COUNT_CHANGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxUserCountChange, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::USER_ENTER_ROOM, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxUserEnterRoom, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::USER_EXIT_ROOM, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxUserExitRoom, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::SPECTATOR_TO_PLAYER_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxSpectatorToPlayerError, (unsigned long long)this)));
	mSmartFox->AddEventListener(SFSEvent::PLAYER_TO_SPECTATOR_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxPlayerToSpectatorError, (unsigned long long)this)));
    
	mSmartFox->AddEventListener(SFSEvent::INVITATION, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnSmartFoxInvitation, (unsigned long long)this)));
    
	mSmartFox->AddEventListener(SFSEvent::EXTENSION_RESPONSE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(GameServer::OnExtensionResponse, (unsigned long long)this)));
    
    /*
     //load config file, and connect
     #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
     std::string fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("sfs-config.xml");
     std::string * filename = new std::string(fullPath);
     cocos2d::CCLog("%s",fullPath.c_str());
     #else
     std::string* filename = new std::string(".\\sfs-config.xml");
     #endif
     
     mSmartFox->LoadConfig(filename, true);
     delete filename;
     filename = NULL;
     */
}

//connect
void GameServer::connectToServer( const char * strIP, const char * strPort )
{
    CCLOG("connectToServer with IP: %s", strIP);
	double port = atof(strPort);
	if( mSmartFox ){
		mSmartFox->RemoveAllEventListeners();
		mSmartFox.reset();
	}
	initServer();
	mSmartFox->Connect(strIP,(long int)port);
}

void GameServer::updateEvent( )
{
	//handle the message manually
	mSmartFox->ProcessEvents();
}
/*
 All events
 */
void GameServer::OnSmartFoxConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventConnection, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventConnectionLost, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxDisconnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventDisconnected, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxSocketError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventSocketError, ptrContext, ptrEvent );
}

void GameServer::OnSmartFoxLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventLogin, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventLoginError, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("GameServer::OnSmartFoxLogout");
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventLogout0, ptrContext, ptrEvent );
}

void GameServer::OnSmartFoxRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventRoomJoin, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxRoomJoinError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventRoomJoinError, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventCreationError, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxRoomAdd(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventRoomAdd, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxRoomVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventRoomVariableUpdate, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxRoomPasswordStateChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventRoomPasswordStateChange, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxRoomPasswordStateChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventRoomPasswordStateChangeError, ptrContext, ptrEvent );
}

void GameServer::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventPublicMessage, ptrContext, ptrEvent );
}

void GameServer::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventUserVariableUpdate, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxUserCountChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventUserCountChange, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxUserEnterRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventUserEnterRoom, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventUserExitRoom, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxSpectatorToPlayerError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventSpectatorToPlayerError, ptrContext, ptrEvent );
}
void GameServer::OnSmartFoxPlayerToSpectatorError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventPlayerToSpectatorError, ptrContext, ptrEvent );
}

void GameServer::OnSmartFoxInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    GameServer::getSingleton().OnSmartFoxNtf(tag_EventInvitation, ptrContext, ptrEvent );
}

void GameServer::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    if(strcmp("hbc", ptrNotifiedCmd->c_str())==0){
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        //sendRequest
        boost::shared_ptr<IRequest> request (new ExtensionRequest("ghbres",parameter));
        GameServer::getSingleton().getSmartFox()->Send(request);
        return;
    }

    GameServer::getSingleton().OnSmartFoxNtf(tag_EventExtensionResponse, ptrContext, ptrEvent );
}
/*
 Notify
 */

void GameServer::OnSmartFoxNtf(eEventTags tag, unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    PlayerCallBackMapIter iTer = mCallBack.begin();
	for ( ; iTer != mCallBack.end() ; iTer ++ ){
// 		if( iTer->second == 0x0e0e0e0e )
// 			continue;
		switch(tag)
		{
		case tag_EventConnection:
			iTer->second->OnSmartFoxConnection(ptrContext, ptrEvent);
			break;
		case tag_EventConnectionLost:
			iTer->second->OnSmartFoxConnectionLost(ptrContext, ptrEvent);
			break;
		case tag_EventDisconnected:
			iTer->second->OnSmartFoxDisconnection(ptrContext, ptrEvent);
			break;
		case tag_EventSocketError:
			iTer->second->OnSmartFoxSocketError(ptrContext, ptrEvent);
			break;
		case tag_EventLogin:
			iTer->second->OnSmartFoxLogin(ptrContext, ptrEvent);
			break;
		case tag_EventLoginError:
			iTer->second->OnSmartFoxLoginError(ptrContext, ptrEvent);
			break;
		case tag_EventLogout0:
			CCLOG("tag_EventLogout");
			iTer->second->OnSmartFoxLogout(ptrContext, ptrEvent);
			break;
		case tag_EventRoomJoin:
			iTer->second->OnSmartFoxRoomJoin(ptrContext, ptrEvent);
			break;
		case tag_EventRoomJoinError:
			iTer->second->OnSmartFoxRoomJoinError(ptrContext, ptrEvent);
			break;
		case tag_EventCreationError:
			iTer->second->OnSmartFoxRoomCreationError(ptrContext, ptrEvent);
			break;
		case tag_EventRoomAdd:
			iTer->second->OnSmartFoxRoomAdd(ptrContext, ptrEvent);
			break;
		case tag_EventRoomVariableUpdate:
			iTer->second->OnSmartFoxRoomVariableUpdate(ptrContext, ptrEvent);
			break;
		case tag_EventRoomPasswordStateChange:
			iTer->second->OnSmartFoxRoomPasswordStateChange(ptrContext, ptrEvent);
			break;
		case tag_EventRoomPasswordStateChangeError:
			iTer->second->OnSmartFoxRoomPasswordStateChangeError(ptrContext, ptrEvent);
			break;
		case tag_EventPublicMessage:
			iTer->second->OnSmartFoxPublicMessage(ptrContext, ptrEvent);
			break;
		case tag_EventUserVariableUpdate:
			iTer->second->OnSmartFoxUserVariableUpdate(ptrContext, ptrEvent);
			break;
		case tag_EventUserCountChange:
			iTer->second->OnSmartFoxUserCountChange(ptrContext, ptrEvent);
			break;
		case tag_EventUserEnterRoom:
			iTer->second->OnSmartFoxUserEnterRoom(ptrContext, ptrEvent);
			break;
		case tag_EventUserExitRoom:
			iTer->second->OnSmartFoxUserExitRoom(ptrContext, ptrEvent);
			break;
		case tag_EventSpectatorToPlayerError:
			iTer->second->OnSmartFoxSpectatorToPlayerError(ptrContext, ptrEvent);
			break;
		case tag_EventPlayerToSpectatorError:
			iTer->second->OnSmartFoxPlayerToSpectatorError(ptrContext, ptrEvent);
			break;
		case tag_EventInvitation:
			iTer->second->OnSmartFoxInvitation(ptrContext, ptrEvent);
			break;
		case tag_EventExtensionResponse:
			iTer->second->OnExtensionResponse(ptrContext, ptrEvent);
			break;
		};
		
    }
}
