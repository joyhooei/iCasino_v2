//
//  LayerChatRoom.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/3/14.
//
//

#include "LayerChatRoom.h"
#include "SliderCustomLoader.h"
#include "TextFieldCustomLoader.h"
#include "LayerCreateRoom.h"
#include "mUtils.h"
#include "CustomTableViewCell.h"
#include "_Chat_.h"

#include "Requests/JoinRoomRequest.h"
#include "SceneManager.h"
#include "Requests/LeaveRoomRequest.h"
#include "Requests/PublicMessageRequest.h"

#include "LayerChatWindow.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerChatRoom::LayerChatRoom()
{
    nodeListContents = NULL;
    tblListContents = NULL;
    
    nodeListRooms = NULL;
    tblListRooms = NULL;
    
    lblTitle = NULL;

	currRoomChatIndex = -1;
	//
	for( int i = 1; i<=16; i++ ){
		lstRegex.push_back( CCString::createWithFormat("(%d)", i)->getCString() );
	}
    //
    GameServer::getSingleton().addListeners(this);
}

LayerChatRoom::~LayerChatRoom()
{
    GameServer::getSingleton().removeListeners(this);
	// leave room
	boost::shared_ptr<IRequest> request (new LeaveRoomRequest());
	GameServer::getSingleton().getSmartFox()->Send(request);
	//
	CC_SAFE_RELEASE(nodeListContents);

	CC_SAFE_RELEASE(nodeListRooms);

	CC_SAFE_RELEASE(lblTitle);
}

void LayerChatRoom::setGameID(int gID){
    m_gID = gID;
    CCLOG("setGameID: gId: %d", gID);
    lblTitle->setString( CCString::createWithFormat("CHỌN BÀN - %s", mUtils::getGameNameUpperCaseByID(gID)->getCString())->getCString() );
    tblListRooms->reloadData();
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerChatRoom::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChat", LayerChatRoom::onButtonChat);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnRefresh", LayerChatRoom::onButtonRefresh);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChoiNgay", LayerChatRoom::onButtonChoiNgay);
    return NULL;
}

void LayerChatRoom::onButtonChat(CCObject* pSender)
{
// 	string line("test\ttest2\ttest3");
// 	vector<string> strs;
// 	boost::split(strs,line,boost::is_any_of("\t")	return;
	LayerChatWindow* l = SceneManager::getSingleton().getLayerChatWindow();
	l->setCallbackFunc(this,callfuncND_selector(LayerChatRoom::callbackFromChatWindow));
	SceneManager::getSingleton().showLayerChatWindow();
}

// CCBMemberVariableAssigner interface
bool LayerChatRoom::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeListRooms", CCNode *, nodeListRooms);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle", CCLabelTTF *, lblTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeListContents", CCNode *, nodeListContents);
    return true;
}

void LayerChatRoom::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	currRoomChatIndex = 0;
	currRoomID = -1;
    //Init for table List Room
    tblListRooms = CCTableView::create(this, nodeListRooms->getContentSize());
    tblListRooms->setDirection(kCCScrollViewDirectionVertical);
    tblListRooms->setAnchorPoint(ccp(0, 0));
    tblListRooms->setPosition(ccp(0, 0));
    tblListRooms->setDelegate(this);
    tblListRooms->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblListRooms->setTag(tagListRoom);
    nodeListRooms->addChild(tblListRooms);
    tblListRooms->reloadData();
    //Init for table List Room
    tblListContents = CCTableView::create(this, nodeListContents->getContentSize());
    tblListContents->setDirection(kCCScrollViewDirectionVertical);
    tblListContents->setAnchorPoint(ccp(0, 0));
    tblListContents->setPosition(ccp(0, 0));
    tblListContents->setDelegate(this);
    tblListContents->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblListContents->setTag(tagListContent);
    nodeListContents->addChild(tblListContents);    //
	//Join first room chat
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms
		= GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup("200");
	if( rooms->size()==0 )
		return;
	boost::shared_ptr<IRequest> request (new JoinRoomRequest(rooms->at(0),""));
	GameServer::getSingleton().getSmartFox()->Send(request);
    return;
}

void LayerChatRoom::tableCellHighlight(CCTableView* table, CCTableViewCell* cell){
    //CCLOG("tableCellHighlight: %d", cell->getObjectID());
}

void LayerChatRoom::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){
    //CCLOG("tableCellUnhighlight: %d", cell->getObjectID());
}

// hàm khi click vào 1 hành của table view
void LayerChatRoom::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d", cell->getTag());
   if(table->getTag()==tagListRoom){
       CCLOG("Roomid: %d",cell->getTag());
	   if( currRoomID == cell->getTag() )
		   return;
//        if(ro==NULL){
//            CCLOG("Roomid: %d NOT FOUND",cell->getTag());
//            return;
//        }
       boost::shared_ptr<IRequest> request (new JoinRoomRequest(cell->getTag(), ""));
       GameServer::getSingleton().getSmartFox()->Send(request);
   }
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerChatRoom::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    if(table->getTag()==tagListRoom)
        return CCSizeMake(nodeListRooms->getContentSize().width, 40);
    //Rooms
    //    if( idx==0 )
    //        return CCSizeMake(nodeListContents->getContentSize().width, 0);
    return CCSizeMake(nodeListContents->getContentSize().width, 50);
}

CCNode* LayerChatRoom::createLabel4Cell(int tag, const char* text, CCSize size, CCPoint point){
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

CCLabelTTF* LayerChatRoom::getLabelFromTagID(CCTableViewCell *cell, int tag){
    CCNode* node = cell->getChildByTag(tag);
    if( node == NULL )
        return NULL;
    CCLabelTTF *lbl = (CCLabelTTF*)node->getChildByTag(tag);
    return lbl;
}

RichText* LayerChatRoom::getRichTextFromTagID( CCTableViewCell *cell, int tag )
{
	CCNode* node = cell->getChildByTag(tag);
	if( node == NULL )
		return NULL;
	RichText *rt = (RichText*)node->getChildByTag(tag);
	return rt;
}

CCTableViewCell* LayerChatRoom::process4ListRooms(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    CCLOG("cell: %d", idx);
    boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms
    = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup("200");
    
    boost::shared_ptr<RoomVariable> rv = rooms->at(idx)->GetVariable("params");
    
    if(!cell){
        cell = new CustomTableViewCell(CCSizeMake(nodeListRooms->getContentSize().width, 40));
        cell->autorelease();
        cell->setObjectID(rooms->at(idx)->Id());
        cell->setTag(rooms->at(idx)->Id());
        // Mã phòng
        cell->addChild(createLabel4Cell(tag_Content, rooms->at(idx)->Name()->c_str(), CCSizeMake(nodeListRooms->getContentSize().width, 40), ccp(0, 0)));
        
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(tblListRooms->getContentSize().width/2,0));
        line->setScaleX(tblListRooms->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
		//
		if( idx == currRoomChatIndex ){
			((CustomTableViewCell*)cell)->setSelectedState(true);
		}
    }
    else{
        CCLabelTTF *label1 = getLabelFromTagID(cell, tag_Content);
        if( label1!=NULL )
            label1->setString(rooms->at(idx)->Name()->c_str());
		((CustomTableViewCell*)cell)->setSelectedState(idx == currRoomChatIndex);
    }
    return cell;
}
CCTableViewCell* LayerChatRoom::process4ListContents(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    CCLOG("cell: %lf %lf", tblListContents->getContentSize().width, tblListContents->getContentSize().height);
    CCString *soPhong = CCString::createWithFormat("Phòng %d", idx+1);
	MessageInfo info = lstChatMessage.at(idx);
    if(!cell){
        cell = new CustomTableViewCell(CCSizeMake(nodeListContents->getContentSize().width, 50));
        cell->setObjectID(idx);
        cell->autorelease();
		cell->setTag(idx);
		//
		cell->addChild(createLabel4CellContent(tag_Content, info.content.c_str(), info.user.c_str(), CCSizeMake(nodeListContents->getContentSize().width, 50), ccp(0, 0)));
        //
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(nodeListContents->getContentSize().width/2,0));
        line->setScaleX(nodeListContents->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else{
		RichText *rtContent = getRichTextFromTagID(cell, tag_Content);
        if( rtContent!=NULL )
			setContent2Richtext( rtContent, info.content.c_str() );
		//
		CCLabelTTF *labelUser = getLabelFromTagID(cell, tag_User);
		if( labelUser!=NULL )
			labelUser->setString(info.user.c_str());
    }
    return cell;
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerChatRoom::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
   // CCLOG("tabletag: %d", table->getTag());
    if(table->getTag()==tagListRoom){
        return process4ListRooms(table, idx);
    }
    return process4ListContents(table, idx);
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerChatRoom::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    //CCLOG("tabletag: %d", table->getTag());
    if(table->getTag()==tagListRoom){
        boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms
        = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup("200");
        return rooms->size();
    }
    if(table->getTag()==tagListContent){
        return lstChatMessage.size();
    }
    return 0;
}

void LayerChatRoom::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    
    CCLOG("cmd = %s",ptrNotifiedCmd->c_str());
}

void LayerChatRoom::callbackFromChatWindow( CCNode* n, void* data)
{
	if( strlen( (char*)data )==0 )
		return;
	//Get room
	boost::shared_ptr<Room>  room
		= GameServer::getSingleton().getSmartFox()->GetRoomById(currRoomID);
	if(room==NULL)
		return;
	//
	CCLOG("callbackFromChatWindow %s", (char*)data);
	boost::shared_ptr<ISFSObject> parameters(new SFSObject());
	boost::shared_ptr<IRequest> request (new PublicMessageRequest((char*)data, parameters, room)); 
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerChatRoom::OnSmartFoxPublicMessage( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
	//
	CCLOG("ptrNotifiedMessage: %s", ptrNotifiedMessage->c_str());
	MessageInfo info;
	info.content = *ptrNotifiedMessage;
	info.user = *ptrNotifiedUser->Name();
	lstChatMessage.push_back(info);
	if( lstChatMessage.size()>4 ){
		lstChatMessage.erase( lstChatMessage.begin() );
	}
	tblListContents->reloadData();
}

void LayerChatRoom::OnSmartFoxRoomJoin( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	CCLOG("LayerChatRoom - Join Room");
	// Room joined
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
	//
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms
		= GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup("200");
	currRoomID = ptrNotifiedRoom->Id();
	lstChatMessage.clear();
	for( int i = 0; i<rooms->size(); i++ ){
		if( rooms->at(i)->Id() == ptrNotifiedRoom->Id() ){
			lblTitle->setString( CCString::createWithFormat("PHÒNG TÁN GẪU - %s", rooms->at(i)->Name()->c_str())->getCString()  );
			currRoomChatIndex = i;
			tblListRooms->reloadData();
			lstChatMessage.clear();
			tblListContents->reloadData();
			break;
		}
	}
}

void LayerChatRoom::OnSmartFoxRoomJoinError( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
	boost::shared_ptr<string> message (new string("Join Room Failure: " +  *ptrErrorMessage));
	Chat *toast = new Chat(CCString::createWithFormat("Vào phòng thất bại!\n%s", message->c_str())->getCString(), -1);
	this->addChild(toast);
}

CCNode* LayerChatRoom::createLabel4CellContent( int tag, const char* text, const char* user, CCSize size, CCPoint point )
{
	CCNode* node = CCNode::create();
	node->setContentSize(size);
	node->setAnchorPoint(CCPointZero);
	node->setPosition(point);
	node->setTag(tag);

	UILayer* layer = UILayer::create();
	layer->setContentSize(size);
	node->addChild(layer);

	RichText* _richText = RichText::create();
	layer->addWidget(_richText);
	_richText->setSize( size );
	_richText->setPosition(ccp(0, 0));
	_richText->setAnchorPoint(ccp(0, 0));

	setContent2Richtext(_richText, text);
	_richText->setTag(tag);

// 	CCLabelTTF *label = CCLabelTTF::create(text, "Helvetica", 14);
// 	label->setAnchorPoint(ccp(0.5,0.5));
// 	label->setPosition(ccp( size.width/2, size.height/2 ));
// 	label->setTag(tag);

	CCLabelTTF *labelUser = CCLabelTTF::create(user, "Helvetica", 14);
	labelUser->setAnchorPoint(ccp(0, 1));
	labelUser->setPosition(ccp( 2, size.height-5 ));
	labelUser->setColor(ccc3(231, 252, 0));
	labelUser->setTag(tag_User);

	node->addChild(labelUser);

	return node;
}

void LayerChatRoom::setContent2Richtext( RichText* rt, const char* text )
{
	if( rt==NULL )
		return;
	rt->removeAllChildrenWithCleanup(true);
// 	CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(CCString::createWithFormat("onion%d.ExportJson", 1)->getCString());
// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(CCString::createWithFormat("onion%d.ExportJson", 1)->getCString());
	//split content
	vector<string> lstContents = mUtils::splitStringByListRegex(text, lstRegex, true);
	for( int i=0; i<lstContents.size(); i++ ){
		bool check = false;
		int j=0;
		for( j=0; j<lstRegex.size(); j++ )
			if( lstRegex.at(j) == lstContents.at(i) ){
				check = true;
				break;
			}
		if( check ){
			CCArmature *armature = CCArmature::create(CCString::createWithFormat("onion%d", 1)->getCString());
			armature->getAnimation()->playByIndex(j);
			RichElementCustomNode* recustom = RichElementCustomNode::create(1, ccWHITE, 255, armature);
			rt->pushBackElement(recustom);
		}else{
			RichElementText* re1 = RichElementText::create(1, ccWHITE, 255, lstContents.at(i).c_str(), "Helvetica", 12);
			rt->pushBackElement(re1);
		}
	}
}
