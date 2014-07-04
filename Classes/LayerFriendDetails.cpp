//
//  LayerFriendDetails.cpp
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#include "LayerFriendDetails.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"
#include "CustomTableViewCell.h"
#include "_Chat_.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerFriendDetails::LayerFriendDetails()
{
    lblSex=NULL;
    lblXu=NULL;
    lblOnline=NULL;
    lblName=NULL;
    
    spriteOnline=NULL;
    
    nodeTableHistory=NULL;
    tblHistory=NULL;
    nodeFriends=NULL;
    tblFriends=NULL;
    
    rowsFriendsCount = 0;
    rowsHistoryCount = 0;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerFriendDetails::~LayerFriendDetails()
{
	GameServer::getSingleton().removeListeners(this);
	CCLOG("LayerFriendDetails::~LayerFriendDetails()");

	//
	CC_SAFE_RELEASE(lblSex);
	CC_SAFE_RELEASE(lblXu);
	CC_SAFE_RELEASE(lblOnline);
	CC_SAFE_RELEASE(lblName);

	CC_SAFE_RELEASE(spriteOnline);

	CC_SAFE_RELEASE(nodeTableHistory);
	CC_SAFE_RELEASE(nodeFriends);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerFriendDetails::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSms", LayerFriendDetails::onButtonSMS);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnTransferMoney", LayerFriendDetails::onButtonTransferMoney);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUnInvite", LayerFriendDetails::onButtonUnInvite);
    return NULL;
}

void LayerFriendDetails::onButtonSMS(CCObject* pSender)
{
    CCLOG("onButtonSMS");
    
}

void LayerFriendDetails::onButtonTransferMoney(CCObject* pSender)
{
    CCLOG("onButtonTransferMoney");
    
}

void LayerFriendDetails::onButtonUnInvite(CCObject* pSender)
{
    CCLOG("onButtonUnInvite");
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aI", currFriendID.c_str());
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rarf", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBMemberVariableAssigner interface
bool LayerFriendDetails::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    if( pMemberVariableName==NULL || strcmp(pMemberVariableName, "") == 0 )
        return true;
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblName", CCLabelTTF *, lblName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblOnline", CCLabelTTF *, lblOnline);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblSex", CCLabelTTF *, lblSex);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblXu", CCLabelTTF *, lblXu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "spriteOnline", CCSprite*, spriteOnline);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTableHistory", CCNode *, nodeTableHistory);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeFriends", CCNode *, nodeFriends);
    
    return true;
}

void LayerFriendDetails::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    //Load all datas
    for( int i = 0 ; i<mUtils::numOfGame; i++ ){
        historys[i].ID = mUtils::numBeginGameID+i;
        historys[i].name = mUtils::getGameNameByID(mUtils::numBeginGameID+i);
        historys[i].numOfLevel = 0;
        historys[i].numOfWin = 0;
        historys[i].numOfLose = 0;
    }
    //Init for table tag_Historys
    tblHistory = CCTableView::create(this, nodeTableHistory->getContentSize());
    tblHistory->setDirection(kCCScrollViewDirectionVertical);
    tblHistory->setAnchorPoint(ccp(0, 0));
    tblHistory->setPosition(ccp(0, 0));
    tblHistory->setDelegate(this);
    tblHistory->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblHistory->setTag(tag_Historys);
    nodeTableHistory->addChild(tblHistory);
    tblHistory->reloadData();
    //Init for table tag_Friends
    tblFriends = CCTableView::create(this, nodeFriends->getContentSize());
    tblFriends->setDirection(kCCScrollViewDirectionVertical);
    tblFriends->setAnchorPoint(ccp(0, 0));
    tblFriends->setPosition(ccp(0, 0));
    tblFriends->setDelegate(this);
    tblFriends->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblFriends->setTag(tag_Friends);
    nodeFriends->addChild(tblFriends);
    //
    tblFriends->reloadData();
	//
	loadFirstCell();
}
// hàm khi click vào 1 hành của table view
void LayerFriendDetails::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d of %s", cell->getObjectID(), table->getTag()==tag_Friends?"Friends":"Historys");
	if( table->getTag()==tag_Friends ){
		CustomTableViewCell* cc = (CustomTableViewCell*)cell;
		int fid = cc->getObjectID();
		string fname = cc->getStringObject();
		//getFriend
		boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > lstBuddys = GameServer::getSingleton().getSmartFox()->BuddyManager()->BuddyList();
		boost::shared_ptr<Sfs2X::Entities::Buddy> buddy = GameServer::getSingleton().getSmartFox()->BuddyManager()->GetBuddyByName(fname);
		if( buddy==NULL )
			return;
		lblOnline->setString( buddy->IsOnline()?"Online":"Offline" );
		//Uncheck other cells
		for( int i = 0; i<lstBuddys->size(); i++ ){
			CustomTableViewCell* cc = (CustomTableViewCell*)table->cellAtIndex(i);
			if( cc==NULL )
				continue;
			cc->setSelectedState(false);
		}
		//check
		CustomTableViewCell*c = (CustomTableViewCell*)cell;
		c->setSelectedState(true);
		//Get all info
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		params->PutUtfString("aI", buddy->Name()->c_str());
		boost::shared_ptr<IRequest> request (new ExtensionRequest("rgif", params));
		GameServer::getSingleton().getSmartFox()->Send(request);
		//Get history
		boost::shared_ptr<IRequest> request1 (new ExtensionRequest("rghba", params));
		GameServer::getSingleton().getSmartFox()->Send(request1);

		currFriendID = fname;

		mCurrentRoomIndex = cell->getIdx();
	}
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerFriendDetails::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    if( table->getTag() == tag_Friends ){
        return CCSizeMake(nodeFriends->getContentSize().width-10, 60);
    }
    return CCSizeMake(nodeTableHistory->getContentSize().width-20, 40);
}

CCTableViewCell* LayerFriendDetails::createCell4History(CCTableView *table, int idx){
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        //CCLOG("createCell4History");
        cell = new CCTableViewCell();
        cell->autorelease();
        //Name game
        CCLabelTTF *labelName = CCLabelTTF::create(mUtils::getGameNameByID(100+idx)->getCString(), "Helvetica", 17.0);
        labelName->setPosition(ccp(0, 20));
		labelName->setAnchorPoint(ccp(0, 0.5));
        labelName->setTag(tag_NameGame);
        cell->addChild(labelName);
        //Level
        CCLabelTTF *labelLevel = CCLabelTTF::create(CCString::createWithFormat("Cấp độ: %d", historys[idx].numOfLevel)->getCString(), "Helvetica", 17.0);
        labelLevel->setPosition(ccp(nodeTableHistory->getContentSize().width/2, 20));
		labelLevel->setAnchorPoint(ccp(0.5, 0.5));
        labelLevel->setTag(tag_Level);
        cell->addChild(labelLevel);
        //Win lose
        CCLabelTTF *labelWin = CCLabelTTF::create(CCString::createWithFormat("Thắng %d/Thua %d", historys[idx].numOfWin, historys[idx].numOfLose)->getCString(), "Helvetica", 17.0);
        labelWin->setPosition(ccp(nodeTableHistory->getContentSize().width, 20));
		labelWin->setAnchorPoint(ccp(1, 0.5));
        labelWin->setTag(tag_WinLose);
        cell->addChild(labelWin);
        //Sprite
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/lineNgang.png");
        line->setPosition(ccp(nodeTableHistory->getContentSize().width/2,0));
        line->setScaleX(nodeTableHistory->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(tag_NameGame);
        if( label )
            label->setString(mUtils::getGameNameByID(100+idx)->getCString());
        //
        CCLabelTTF *labelLevel = (CCLabelTTF*)cell->getChildByTag(tag_Level);
        if( labelLevel )
            labelLevel->setString(CCString::createWithFormat("Level: %d", historys[idx].numOfLevel)->getCString());
        //
        CCLabelTTF *labelWin = (CCLabelTTF*)cell->getChildByTag(tag_WinLose);
        if( labelWin )
            labelWin->setString(CCString::createWithFormat("Thắng %d/Thua %d", historys[idx].numOfWin, historys[idx].numOfLose)->getCString());
    }
    return cell;
}

CCTableViewCell* LayerFriendDetails::createCell4Friends(CCTableView *table, int idx){
    CustomTableViewCell* cell = (CustomTableViewCell*)table->dequeueCell();
    boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > buddys = GameServer::getSingleton().getSmartFox()->BuddyManager()->BuddyList();
    if( buddys->at(idx) == NULL )
        return cell;
    if (!cell) {
        //CCLOG("createCell4Friends");
        cell = new CustomTableViewCell( CCSizeMake(nodeFriends->getContentSize().width, 60) );
        cell->autorelease();
        //Avatar
        cell->addChild( loadDefaultImage(CCSizeMake(48, 48), ccp(10, 60/2)) );
        //Name friend
        CCLabelTTF *labelName = CCLabelTTF::create(buddys->at(idx)->Name()->c_str(), "Helvetica", 16.0);
        labelName->setPosition(ccp(80, 36));
		labelName->setAnchorPoint(ccp(0, 0));
        labelName->setTag(tag_NameFriend);
        cell->addChild(labelName);
        //Online
        CCLabelTTF *labelOnlineState = CCLabelTTF::create(buddys->at(idx)->IsOnline()?"Online":"Offline", "Helvetica", 16.0);
		labelOnlineState->setAnchorPoint(ccp(0, 0));
        labelOnlineState->setPosition(ccp(111, 12));
        labelOnlineState->setTag(tag_OnlineState);
        cell->addChild(labelOnlineState);
        //Sprite Online
        CCSprite* sOnline = CCSprite::createWithSpriteFrameName(buddys->at(idx)->IsOnline()?"assest/ratio_active.png":"assest/ratio_disable.png");
		sOnline->setAnchorPoint(ccp(0, 0));
        sOnline->setPosition(ccp(80, 12));
		sOnline->setTag(tag_OnlineStateImage);
        cell->addChild(sOnline);
        //Sprite
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(nodeFriends->getContentSize().width/2,0));
        line->cocos2d::CCNode::setScale(nodeFriends->getContentSize().width/line->getContentSize().width, 60/line->getContentSize().height);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
		//set id
		cell->setObjectID( buddys->at(idx)->Id() );
		cell->setStringObject( *buddys->at(idx)->Name() );
		//
		cell->setSelectedState( idx == mCurrentRoomIndex );
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(tag_NameFriend);
        if( label )
            label->setString(buddys->at(idx)->Name()->c_str());
        //
        CCLabelTTF *labelLevel = (CCLabelTTF*)cell->getChildByTag(tag_OnlineState);
        if(labelLevel)
			labelLevel->setString(buddys->at(idx)->IsOnline()?"Online":"Offline");
		cell->setObjectID( buddys->at(idx)->Id() );
		//
		cell->removeChildByTag(tag_OnlineStateImage, true);
		CCSprite* sOnline = CCSprite::createWithSpriteFrameName(buddys->at(idx)->IsOnline()?"assest/ratio_active.png":"assest/ratio_disable.png");
		sOnline->setAnchorPoint(ccp(0, 0));
		sOnline->setPosition(ccp(80, 12));
		sOnline->setTag(tag_OnlineStateImage);
		cell->addChild(sOnline);
		cell->setStringObject( *buddys->at(idx)->Name() );
		
		cell->setSelectedState( idx == mCurrentRoomIndex );
        //
//        CCLabelTTF *labelWin = (CCLabelTTF*)cell->getChildByTag(tag_WinLose);
//        labelWin->setString(CCString::createWithFormat("Thắng %d/Thua %d", historys[idx].numOfWin, historys[idx].numOfLose)->getCString());
    }
    return cell;
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerFriendDetails::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
 //   CCLOG("table tag: %d", table->getTag());
    if( table->getTag() == tag_Friends ){
        return createCell4Friends(table, idx);
    }else if(table->getTag() == tag_Historys)
        return createCell4History(table, idx);
    //
    CCTableViewCell *cell = table->dequeueCell();
    return cell;
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerFriendDetails::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    if( table->getTag() == tag_Friends ){
        boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > buddys = GameServer::getSingleton().getSmartFox()->BuddyManager()->BuddyList();
        return buddys->size();
    }else if( table->getTag() == tag_Historys )
        return mUtils::numOfGame;
    return 0;
}

CCSprite* LayerFriendDetails::loadDefaultImage(CCSize s, CCPoint p){
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("assest/icon_default.png");
    pSprite->setAnchorPoint(ccp(0, 0.5));
    pSprite->cocos2d::CCNode::setScale(s.width/pSprite->getContentSize().width, s.height/pSprite->getContentSize().height);
    pSprite->setPosition(p);
    return pSprite;
}

void LayerFriendDetails::OnExtensionResponse( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if( strcmp( cmd->c_str(), "rgif" )==0 ){ //Friend info
		lblName->setString( param->GetUtfString("aN")->c_str() );
		lblSex->setString( CCString::createWithFormat("Giới tính: %s", param->GetInt("aS")==0?"Nữ": "Nam")->getCString() );
		lblXu->setString( CCString::createWithFormat("Xu: %s", mUtils::convertMoneyEx( *param->GetDouble("amf") ).c_str() )->getCString() );
	}else if( strcmp( cmd->c_str(), "rghba" )==0 ){ //History
		vector<string> lstHis;
		lstHis = mUtils::splitString(*param->GetUtfString("rghba"), '|');
		for( int i = 0; i<mUtils::numOfGame; i++ ){
			bool check = false;
			for( int j = 0; j<lstHis.size(); j++ ){
				vector<string> his = mUtils::splitString(lstHis.at(j), ',');
				if( atoi(his.at(0).c_str())==(i+100) ){
					//                    CCLOG("Imhere: gid: %s", his.at(0).c_str());
					historys[i].numOfLevel = atoi(his.at(1).c_str());
					historys[i].numOfWin = atoi(his.at(2).c_str());
					historys[i].numOfLose = atoi(his.at(3).c_str());
					check = true; break;
				}
			}
			if( !check ){
				historys[i].numOfLevel = 0;
				historys[i].numOfWin = 0;
				historys[i].numOfLose = 0;
			}
		}
		//OK, reload datas now
		tblHistory->reloadData();
	}else if(strcmp( cmd->c_str(), "arfc" )==0){ //Ti.App.REMOVE_FRIEND_CMD = "arfc";
		Chat *toast = new Chat("Đã hủy kết bạn!", -1);
		this->addChild(toast);
		//
		tblFriends->reloadData();
		loadFirstCell();
	}
}

void LayerFriendDetails::loadFirstCell()
{
	boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > lstBuddys = GameServer::getSingleton().getSmartFox()->BuddyManager()->BuddyList();
	if( lstBuddys == NULL || lstBuddys->size()==0 ){
		lblName->setString("-");
		lblOnline->setString("-");
		lblSex->setString("-");
		lblXu->setString("-");
		//
		for( int i = 0 ; i<mUtils::numOfGame; i++ ){
			historys[i].ID = mUtils::numBeginGameID+i;
			//historys[i].name = mUtils::getGameNameByID(mUtils::numBeginGameID+i);
			historys[i].numOfLevel = 0;
			historys[i].numOfWin = 0;
			historys[i].numOfLose = 0;
		}
		return;
	}
	boost::shared_ptr<Sfs2X::Entities::Buddy> buddy = lstBuddys->at(0);
	if( buddy==NULL )
		return;
	lblOnline->setString( buddy->IsOnline()?"Online":"Offline" );
	//Uncheck other cells
	for( int i = 0; i<lstBuddys->size(); i++ ){
		CustomTableViewCell* cc = (CustomTableViewCell*)tblFriends->cellAtIndex(i);
		if( cc==NULL )
			continue;
		cc->setSelectedState(false);
	}
	//check
	CustomTableViewCell*c = (CustomTableViewCell*)tblFriends->cellAtIndex(0);
	mCurrentRoomIndex = 0;
	c->setSelectedState(true);
	//Get all info
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aI", buddy->Name()->c_str());
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rgif", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
	//Get history
	boost::shared_ptr<IRequest> request1 (new ExtensionRequest("rghba", params));
	GameServer::getSingleton().getSmartFox()->Send(request1);

	currFriendID = *buddy->Name();
}
