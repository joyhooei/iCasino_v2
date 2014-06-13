//
//  LayerChonBanChoi.cpp
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#include "LayerChonBanChoi.h"
#include "SliderCustomLoader.h"
#include "TextFieldCustomLoader.h"
#include "LayerCreateRoom.h"
#include "mUtils.h"
#include "CustomTableViewCell.h"

#include "Requests/JoinRoomRequest.h"
#include "Requests/SetUserVariablesRequest.h"
#include "Entities/Variables/UserVariable.h"
#include "Entities/Variables/SFSUserVariable.h"
#include "Entities/Invitation/SFSInvitation.h"
#include "Entities/Invitation/Invitation.h"
#include "SceneManager.h"
#include "_Chat_.h"

#include <boost/make_shared.hpp>

using namespace cocos2d;
//using namespace CocosDenshion;


LayerChonBanChoi::LayerChonBanChoi()
{
    nodeTableRooms = NULL;
    tblRooms = NULL;
    
    nodeTableListRooms = NULL;
    tblListRooms = NULL;
    
    lblTitle = NULL;
    
    ccbReader = NULL;
    ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);
    V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, TextFieldCustom);
    // register loaders
    ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerCreateRoom",   LayerCreateRoomLoader::loader());
    //
	GameServer::getSingleton().addListeners(this);

	mRoomID4Invite = -1;
}

LayerChonBanChoi::~LayerChonBanChoi()
{
    GameServer::getSingleton().removeListeners(this);
}

void LayerChonBanChoi::setGameID(int gID){
    m_gID = gID;
    CCLOG("setGameID: gId: %d", gID);
    lblTitle->setString( CCString::createWithFormat("CHỌN BÀN - %s", mUtils::getGameNameUpperCaseByID(gID)->getCString())->getCString() );
    tblListRooms->reloadData();
	//
	boost::shared_ptr<vector<boost::shared_ptr<UserVariable>>> collectionUserVariable (new vector<boost::shared_ptr<UserVariable>>());
	boost::shared_ptr<SFSUserVariable> variable (new SFSUserVariable ("cvg", boost::make_shared<int>(gID), VARIABLETYPE_INT));
	collectionUserVariable->push_back(variable);	//
	boost::shared_ptr<IRequest> request (new SetUserVariablesRequest(collectionUserVariable)); 
	GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerChonBanChoi::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCreateRoom", LayerChonBanChoi::onButtonCreate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnRefresh", LayerChonBanChoi::onButtonRefresh);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChoiNgay", LayerChonBanChoi::onButtonChoiNgay);
    return NULL;
}

void LayerChonBanChoi::onButtonCreate(CCObject* pSender)
{
    CCLOG("onButtonUpdate ");
    //Check
    boost::shared_ptr<double> am, amf;
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    if( myself==NULL || myself->GetVariable("am")==NULL || myself->GetVariable("amf")==NULL ){
        return;
    }
    amf = myself->GetVariable("amf")->GetDoubleValue();
    if((*amf/4)<1000){
		CCLOG("Không đủ tiền tạo phòng!");
		Chat *toast = new Chat("Bạn không đủ tiền tạo phòng!!", -1);
		this->addChild(toast);
        return;
    }
    
    //
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerCreateRoom* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerCreateRoom *)ccbReader->readNodeGraphFromFile( "LayerCreateRoom.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    mLayer->setGameID(m_gID);
}

void LayerChonBanChoi::onButtonRefresh(CCObject* pSender)
{
    tblListRooms->reloadData();
}

void LayerChonBanChoi::onButtonChoiNgay(CCObject* pSender)
{
//     CCLOG("onButtonChoiNgay");
//     return;
    vector<long> lstRoomsID;
    boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup( CCString::createWithFormat("%d", m_gID)->getCString() );
    //
    boost::shared_ptr<double> amf;
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    amf = myself->GetVariable("amf")->GetDoubleValue();
    //
    CCLOG("rooms size %d", rooms->size());
    int i = 0;
    for( i = 0; i<rooms->size(); i++ ){
        boost::shared_ptr<Room> r = rooms->at(i);
        boost::shared_ptr<RoomVariable> rv = r->GetVariable("params");
        string s = *rv->GetStringValue();
        vector<string> lstV = mUtils::splitString( s, '@');
        double roomMoney = atof(lstV[0].c_str());
        if( *amf>roomMoney ){
            lstRoomsID.push_back( rooms->at(i)->Id() );
        }
    }
    if( lstRoomsID.size()==0 )
    {
        CCLOG("Khong co phong nao du tieu chuan");
        return;
    }
    //
    srand(time(NULL));
    int vt = rand() % lstRoomsID.size();
    CCLOG("vao phong id=%ld", lstRoomsID.at(vt));
    //Send request
    boost::shared_ptr<IRequest> request (new JoinRoomRequest(lstRoomsID.at(vt),""));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBMemberVariableAssigner interface
bool LayerChonBanChoi::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTableListRooms", CCNode *, nodeTableListRooms);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle", CCLabelTTF *, lblTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTableRooms", CCNode *, nodeTableRooms);
    return true;
}

void LayerChonBanChoi::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    //Init for table List Room
    tblListRooms = CCTableView::create(this, nodeTableListRooms->getContentSize());
    tblListRooms->setDirection(kCCScrollViewDirectionVertical);
    tblListRooms->setAnchorPoint(ccp(0, 0));
    tblListRooms->setPosition(ccp(0, 0));
    tblListRooms->setDelegate(this);
    tblListRooms->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblListRooms->setTag(tagListPlay);
    nodeTableListRooms->addChild(tblListRooms);
    //Init for table List Room
    tblRooms = CCTableView::create(this, nodeTableRooms->getContentSize());
    tblRooms->setDirection(kCCScrollViewDirectionVertical);
    tblRooms->setAnchorPoint(ccp(0, 0));
    tblRooms->setPosition(ccp(0, 0));
    tblRooms->setDelegate(this);
    tblRooms->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblRooms->setTag(tagListRoom);
    nodeTableRooms->addChild(tblRooms);
    tblRooms->reloadData();
    //
	boost::shared_ptr<vector<boost::shared_ptr<UserVariable>>> collectionUserVariable (new vector<boost::shared_ptr<UserVariable>>());
 	boost::shared_ptr<SFSUserVariable> variable (new SFSUserVariable ("pai", boost::make_shared<int>(1), VARIABLETYPE_INT));
 	collectionUserVariable->push_back(variable);	//
	boost::shared_ptr<IRequest> request (new SetUserVariablesRequest(collectionUserVariable)); 
	GameServer::getSingleton().getSmartFox()->Send(request);
    return;
}

void LayerChonBanChoi::tableCellHighlight(CCTableView* table, CCTableViewCell* cell){
     //CCLOG("tableCellHighlight: %d", cell->getObjectID());
}

void LayerChonBanChoi::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){
    //CCLOG("tableCellUnhighlight: %d", cell->getObjectID());
}

// hàm khi click vào 1 hành của table view
void LayerChonBanChoi::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d", cell->getObjectID());
    if(table->getTag()==tagListPlay){
        CCLOG("Roomid: %d",cell->getObjectID());
        boost::shared_ptr<Room> ro = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup(CCString::createWithFormat("%d", m_gID)->getCString())->at(cell->getObjectID());
        //GetRoomById(cell->getTag());
        if(ro==NULL){
			CCLOG("Roomid: %d NOT FOUND",cell->getObjectID());
			Chat *toast = new Chat("Phòng không tồn tại!!", -1);
			this->addChild(toast);
            return;
		}
		boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
        vector<string> rParams = mUtils::splitString( *ro->GetVariable("params")->GetStringValue(), '@' );
		if( atof(rParams.at(0).c_str()) > *myself->GetVariable("amf")->GetDoubleValue() ){
			Chat *toast = new Chat("Bạn không đủ tiền vào phòng!", -1);
			this->addChild(toast);
			return;
		}

        boost::shared_ptr<IRequest> request (new JoinRoomRequest(ro,""));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }else{
		//Uncheck other cell
// 		for( int i = 0; i<7; i++ ){
// 			CustomTableViewCell* cc = (CustomTableViewCell*)table->cellAtIndex(i);
// 			if( cc==NULL )
// 				continue;
// 			cc->setSelectedState(false);
// 		}
// 		CustomTableViewCell*c = (CustomTableViewCell*)cell;
// 		c->setSelectedState(true);
	}
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerChonBanChoi::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    if(table->getTag()==tagListPlay)
        return CCSizeMake(nodeTableListRooms->getContentSize().width, 40);
    //Rooms
//    if( idx==0 )
//        return CCSizeMake(nodeTableRooms->getContentSize().width, 0);
    return CCSizeMake(nodeTableRooms->getContentSize().width, 40);
}

CCNode* LayerChonBanChoi::createLabel4Cell(int tag, const char* text, CCSize size, CCPoint point){
    CCNode* node = CCNode::create();
    node->setContentSize(size);
    node->setAnchorPoint(CCPointZero);
    node->setPosition(point);
    node->setTag(tag);
    
    CCLabelTTF *label = CCLabelTTF::create(text, "Helvetica", 14);
    label->setAnchorPoint(ccp(0.5,0.5));
    label->setPosition(ccp( size.width/2, size.height/2 ));
    label->setTag(tag);
    
    node->addChild(label);
    
    return node;
}

CCLabelTTF* LayerChonBanChoi::getLabelFromTagID(CCTableViewCell *cell, int tag){
    CCNode* node = cell->getChildByTag(tag);
    if( node == NULL )
        return NULL;
    CCLabelTTF *lbl = (CCLabelTTF*)node->getChildByTag(tag);
    return lbl;
}

CCTableViewCell* LayerChonBanChoi::process4ListRooms(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    //CCLOG("cell: %d", idx);
    boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms
    = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup(CCString::createWithFormat("%d", m_gID)->getCString());
    
    boost::shared_ptr<RoomVariable> rv = rooms->at(idx)->GetVariable("params");
    
    if(!cell){
        cell = new CustomTableViewCell(CCSizeMake(nodeTableListRooms->getContentSize().width, 40));
        cell->autorelease();
        cell->setObjectID(rooms->at(idx)->Id());
        cell->setTag(rooms->at(idx)->Id());
        // Mã phòng
        cell->addChild(createLabel4Cell(tag_RoomID, boost::to_string(rooms->at(idx)->Id()).c_str(), CCSizeMake(100, 40), ccp(0, 0)));
        
        //người chơi
        CCString *songuoi = CCString::createWithFormat("%s/%s",boost::to_string(rooms->at(idx)->UserCount()).c_str(),boost::to_string(rooms->at(idx)->MaxUsers()).c_str());
        
        cell->addChild(createLabel4Cell(tag_Players, songuoi->getCString(), CCSizeMake(100, 40), ccp(101, 0)));
        
        cell->addChild(createLabel4Cell(tag_Bet, rv->GetStringValue()->c_str(), CCSizeMake(100, 40), ccp(202, 0)));
        
        cell->addChild(createLabel4Cell(-1, "Nhà chẳng có gì, có mỗi điều kiện", CCSizeMake(271, 40), ccp(302, 0)));
        
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(tblListRooms->getContentSize().width/2,0));
        line->setScaleX(tblListRooms->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else{
        CCLabelTTF *label1 = getLabelFromTagID(cell, tag_RoomID);
        if( label1!=NULL )
            label1->setString(boost::to_string(rooms->at(idx)->Id()).c_str());
        
        CCLabelTTF *label2 = getLabelFromTagID(cell, tag_Players);
        if( label2!=NULL ){
            CCString *songuoi = CCString::createWithFormat("%s/%s",boost::to_string(rooms->at(idx)->UserCount()).c_str(),boost::to_string(rooms->at(idx)->MaxUsers()).c_str());
            label2->setString(songuoi->getCString());
        }
        
        CCLabelTTF *label3 = getLabelFromTagID(cell, tag_Bet);
        if( label3!=NULL )
            label3->setString(rv->GetStringValue()->c_str());
    }
    return cell;
}
CCTableViewCell* LayerChonBanChoi::process4Rooms(cocos2d::extension::CCTableView *table, unsigned int idx){
    CustomTableViewCell *cell = (CustomTableViewCell *)table->dequeueCell();
   // CCLOG("cell: %lf %lf", tblRooms->getContentSize().width, tblRooms->getContentSize().height);
    CCString *soPhong = CCString::createWithFormat("Phòng %d", idx+1);
    if(!cell){
        cell = new CustomTableViewCell(CCSizeMake(nodeTableRooms->getContentSize().width, 40));
        cell->setObjectID(idx);
        cell->autorelease();
        cell->setTag(idx);
        cell->setSelectedState( idx==0 );
        //
        cell->addChild(createLabel4Cell(tag_RoomID, soPhong->getCString(), CCSizeMake(nodeTableRooms->getContentSize().width, 40), ccp(0, 0)));
        //
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(nodeTableRooms->getContentSize().width/2,0));
        line->setScaleX(nodeTableRooms->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else{
        CCLabelTTF *label1 = getLabelFromTagID(cell, tag_RoomID);
        if( label1!=NULL )
            label1->setString(soPhong->getCString());
		cell->setSelectedState(cell->getSelectedState());
    }
    return cell;
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerChonBanChoi::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
  //  CCLOG("tabletag: %d", table->getTag());
    if(table->getTag()==tagListPlay){
        return process4ListRooms(table, idx);
    }
    return process4Rooms(table, idx);
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerChonBanChoi::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    if(table->getTag()==tagListPlay){
        boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms
        = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup(CCString::createWithFormat("%d", m_gID)->getCString());
        return rooms->size();
    }
    if(table->getTag()==tagListRoom){
        return 7;
    }
    return 0;
}


void LayerChonBanChoi::OnSmartFoxInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("Invite Player");
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueInvitation = (*ptrEvetnParams)["invitation"];
	boost::shared_ptr<Invitation::Invitation> invitation = ((boost::static_pointer_cast<Invitation::Invitation>(ptrEventParamValueInvitation)));

// 	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
 	boost::shared_ptr<ISFSObject> param = invitation->Params();
	//
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	//Get PAI
	CCLOG("Invitee: %s Inviter: %s, gameID: %s, minbet: %s", invitation->Invitee()->Name()->c_str(), invitation->Inviter()->Name()->c_str(),
		 param->GetUtfString("gid")->c_str(), param->GetUtfString("mb")->c_str());
	if( myself->GetVariable("pai")->GetStringValue()->compare("0")!=0 ){
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
		mRoomID4Invite = atoi( param->GetUtfString("roomid")->c_str() );
		layer->setNotificationOptions("THƯ MỜI CHƠi", 
			CCString::createWithFormat("Người chơi %s mời bạn cùng chơi:\n%s\n Tiền cược: %s\n Bạn có muốn cùng tham gia?"
				, invitation->Inviter()->Name()->c_str(), mUtils::getGameNameByID( atoi(param->GetUtfString("gid")->c_str()) )->getCString()
				, param->GetUtfString("mb")->c_str())->getCString()
			, true , "ĐỒNG Ý", tagComfirmInvite, this );
	}
}

void LayerChonBanChoi::OnSmartFoxRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Join Room");
    SceneManager::getSingleton().gotoGameByTag(m_gID);
	//Update, khong chap nhan loi moi nua
	boost::shared_ptr<vector<boost::shared_ptr<UserVariable>>> collectionUserVariable (new vector<boost::shared_ptr<UserVariable>>());
	boost::shared_ptr<SFSUserVariable> variable (new SFSUserVariable ("pai", boost::make_shared<int>(0), VARIABLETYPE_INT));
	collectionUserVariable->push_back(variable);	//
	boost::shared_ptr<IRequest> request (new SetUserVariablesRequest(collectionUserVariable)); 
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerChonBanChoi::OnSmartFoxRoomJoinError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Join Room Error");
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
	boost::shared_ptr<string> message (new string("Join Room Failure: " +  *ptrErrorMessage));
	//
	Chat *toast = new Chat(message->c_str(), -1);
	this->addChild(toast);
}

void LayerChonBanChoi::OnSmartFoxRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Create Room Error");
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
	boost::shared_ptr<string> message (new string("Room Create Failure: " +  *ptrErrorMessage));
	//
	Chat *toast = new Chat(message->c_str(), -1);
	this->addChild(toast);
}

void LayerChonBanChoi::OnSmartFoxRoomAdd(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Room Add");
}

void LayerChonBanChoi::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("User Exit Room Ở chọn bàn chơi");
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEvetnParams)["user"];
	boost::shared_ptr<User> user = ((boost::static_pointer_cast<User>(ptrEventParamValueUser)));
	if( user->IsItMe() ){
		boost::shared_ptr<vector<boost::shared_ptr<UserVariable>>> collectionUserVariable (new vector<boost::shared_ptr<UserVariable>>());
		boost::shared_ptr<SFSUserVariable> variable (new SFSUserVariable ("pai", boost::make_shared<int>(1), VARIABLETYPE_INT));
		collectionUserVariable->push_back(variable);	//
		boost::shared_ptr<IRequest> request (new SetUserVariablesRequest(collectionUserVariable)); 
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void LayerChonBanChoi::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	//
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	//
	if(strcmp("nem_ntf", cmd->c_str())==0){//EXT_EVENT_NOT_ENOUGH_MONEY_NTF = "nem_ntf";
		//
		Chat *toast = new Chat("Bạn không đủ tiền chơi tiếp!\nHãy nạp tiền để tiếp tục chơi.", -1);
		this->addChild(toast);
	}else if(strcmp("kkntf", cmd->c_str())==0){ ////EXT_EVENT_USER_KICKED_NOTIF    = "kkntf";
		if( strcmp(myself->Name()->c_str(), param->GetUtfString("uid")->c_str() )==0 ){
			Chat *toast = new Chat("Bạn đã bị đá ra khỏi phòng!", -1);
			this->addChild(toast);
		}else{
			Chat *toast = new Chat( CCString::createWithFormat("Người chơi %s đã bị đá ra khỏi phòng!", param->GetUtfString("uid")->c_str())->getCString(), -1);
			this->addChild(toast);
		}
	}
}

void LayerChonBanChoi::notificationCallBack( bool isOK, int tag )
{
	if( !isOK )
		return;
	switch(tag){
	case tagComfirmInvite:
		//Send request
		boost::shared_ptr<IRequest> request (new JoinRoomRequest(12345,""));
		GameServer::getSingleton().getSmartFox()->Send(request);
		break;
	}
}

void LayerChonBanChoi::joinRoomByID( int rID )
{
	boost::shared_ptr<IRequest> request (new JoinRoomRequest(rID,""));
	GameServer::getSingleton().getSmartFox()->Send(request);
}
