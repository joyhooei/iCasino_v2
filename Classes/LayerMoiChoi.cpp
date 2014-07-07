//
//  LayerMoiChoi.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/3/14.
//
//

#include "LayerMoiChoi.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"
#include "GameServer.h"

using namespace cocos2d;
//using namespace CocosDenshion;

LayerMoiChoi::LayerMoiChoi()
{
    nodeTable = NULL;
    tblTable = NULL;
	lblTitle = NULL;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerMoiChoi::~LayerMoiChoi()
{
    GameServer::getSingleton().removeListeners(this);
	//
	CC_SAFE_RELEASE(nodeTable);
	CC_SAFE_RELEASE(lblTitle);
}

void LayerMoiChoi::loadAllDatas(){
	//get game id
	int gid = atoi( GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str() );
	//
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutInt("maqp", 10);
	params->PutDouble("mimp", 1000);
	params->PutDouble("amf ", 10000);
	params->PutInt("gid", gid);
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rglip", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerMoiChoi::onButtonClose(CCObject* pSender){
    this->removeFromParentAndCleanup(true);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerMoiChoi::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerMoiChoi::onButtonClose);
    return NULL;
}

// CCBMemberVariableAssigner interface
bool LayerMoiChoi::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTable", CCNode *, nodeTable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle", CCLabelTTF *, lblTitle);
    return true;
}

void LayerMoiChoi::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    //Init for table
    tblTable = CCTableView::create(this, nodeTable->getContentSize());
    tblTable->setDirection(kCCScrollViewDirectionVertical);
    tblTable->setAnchorPoint(ccp(0, 0));
    tblTable->setPosition(ccp(0, 0));
    tblTable->setDelegate(this);
    tblTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	tblTable->setTouchPriority(-128);
    
    nodeTable->addChild(tblTable);
    
    tblTable->reloadData();
    //
    lblTitle->setString("MỜI BẠN CHƠI");
	//
	this->setTouchEnabled(true);
    return;
}

// hàm khi click vào 1 hành của table view
void LayerMoiChoi::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d", cell->getTag());
	int idx = cell->getTag();
	StructFriendInfo sms = lstFriendInfos.at(idx);
// 	if( sms==NULL )
// 		return;
	//
	if( GameServer::getSingleton().getSmartFox()->LastJoinedRoom()==NULL )
		return;
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	int groupId = atoi( GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str() );
	vector<string> lstParams = mUtils::splitString( *GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue(), '@' );
	//double mb = atof(lstParams.at(0).c_str());
	//Send request
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("gid", GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	params->PutUtfString("mb", lstParams.at(0).c_str());
	params->PutUtfString("roomid", CCString::createWithFormat("%d", GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->Id())->getCString() );
	params->PutUtfString("lu", sms.aI.c_str());
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rilu", params));
	GameServer::getSingleton().getSmartFox()->Send(request);

	//remove it from list
	lstFriendInfos.erase( lstFriendInfos.begin()+idx );
	tblTable->reloadData();
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerMoiChoi::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    return CCSizeMake(nodeTable->getContentSize().width, 40);
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerMoiChoi::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    StructFriendInfo sms = lstFriendInfos.at(idx);
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        //Time
        CCLabelTTF *labelName = CCLabelTTF::create(CCString::createWithFormat("%s - %s xu"
			, sms.aN.c_str(), mUtils::convertMoneyEx( atof(sms.amf.c_str() ) ).c_str() )->getCString()
			, "Helvetica", 16.0);
// 		CCLabelTTF *labelName = CCLabelTTF::create(sms.aN.c_str(), "Helvetica", 16.0);
        labelName->setPosition(ccp(nodeTable->getContentSize().width/2, 20));
		labelName->setAnchorPoint(ccp(0.5, 0.5));
		labelName->setTag(1);
        //        labelName->setTag(tag_NameFriend);
        cell->addChild(labelName);
		CCLOG("uid: %d", sms.uid);
		cell->setTag( idx );
        //Sprite
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(nodeTable->getContentSize().width/2,0));
        line->setScaleX(nodeTable->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else
    {
		CCLabelTTF *label1 = (CCLabelTTF *)cell->getChildByTag(1);
		if( label1!=NULL )
			label1->setString( CCString::createWithFormat("%s - %s xu", sms.aN.c_str(), mUtils::convertMoneyEx( atof(sms.amf.c_str()) ).c_str() )->getCString());
        //        CCLabelTTF *label1 = getLabelFromTagID(cell, tag_cellTime);
        //        if( label1!=NULL )
        //            label1->setString(his.lastUpdateTime.c_str());
        //        CCLabelTTF *label2= getLabelFromTagID(cell, tag_cellAmount);
        //        if( label2!=NULL )
        //            label2->setString(his.amount.c_str());
        //        CCLabelTTF *label3 = getLabelFromTagID(cell, tag_cellDetails);
        //        if( label3!=NULL )
        //            label3->setString(mUtils::getExplainOfTransType(his.transType.c_str()).c_str());
    }
    return cell;
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerMoiChoi::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return lstFriendInfos.size();
}

void LayerMoiChoi::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	CCLOG("cmd=%s", cmd->c_str());
	if( strcmp( cmd->c_str(), "lip" )==0 ){
		boost::shared_ptr<string> lipv = param->GetUtfString("lipv");
		CCLOG("lipv: %s", lipv->c_str());
		if( strlen(lipv->c_str())==0 ){
			//Nobody
		}else{
			//25,dautv12,dautv12,1315918.0,|
			CCLOG("ListFriendInvite: %s", lipv->c_str());
			vector<string> lstFriends = mUtils::splitString(*lipv, '|');
			lstFriendInfos.clear();
			for( int i = 0; i<lstFriends.size(); i++ ){
				if( strcmp( lstFriends.at(i).c_str(), "" )==0 )
					continue;
				vector<string> friendInfo = mUtils::splitString(lstFriends.at(i), ',');
				StructFriendInfo info;
				info.uid = atoi( friendInfo.at(0).c_str() );
				info.aI = friendInfo.at(1);
				info.aN = friendInfo.at(2);
				info.amf = friendInfo.at(3);

				lstFriendInfos.push_back( info );
			}  
			tblTable->reloadData();
		}
	}
}

void LayerMoiChoi::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerMoiChoi::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerMoiChoi::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerMoiChoi::onExit()
{
	CCLayer::onExit();
}
