//
//  LayerInbox.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/3/14.
//
//

#include "LayerInbox.h"

#include "Requests/ExtensionRequest.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerInbox::LayerInbox()
{
    nodeTableEmail=NULL;
    tblEmail=NULL;
    
    countOfEmail = 0;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerInbox::~LayerInbox()
{
    GameServer::getSingleton().removeListeners(this);
	//
	CC_SAFE_RELEASE(nodeTableEmail);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerInbox::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnNewMail", LayerInbox::onButtonCreate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnRefresh", LayerInbox::onButtonRefresh);
    return NULL;
}

void LayerInbox::onButtonCreate(CCObject* pSender)
{
    CCLOG("onButtonCreate");
}

void LayerInbox::onButtonRefresh(CCObject* pSender)
{
    CCLOG("onButtonRefresh");
    
}

// CCBMemberVariableAssigner interface
bool LayerInbox::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    if( pMemberVariableName==NULL || strcmp(pMemberVariableName, "") == 0 )
        return true;
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTable", CCNode *, nodeTableEmail);
    
    return true;
}

void LayerInbox::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	lstEmails.clear();
    tblEmail = CCTableView::create(this, nodeTableEmail->getContentSize());
    tblEmail->setDirection(kCCScrollViewDirectionVertical);
    tblEmail->setAnchorPoint(ccp(0, 0));
    tblEmail->setPosition(ccp(0, 0));
    tblEmail->setDelegate(this);
    tblEmail->setVerticalFillOrder(kCCTableViewFillTopDown);
    nodeTableEmail->addChild(tblEmail);
}
// hàm khi click vào 1 hành của table view
void LayerInbox::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
//    CCLOG("Roomid: %d of %s", cell->getObjectID(), table->getTag()==tag_Friends?"Friends":"Historys");
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerInbox::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    return CCSizeMake(nodeTableEmail->getContentSize().width-20, 40);
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerInbox::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
   if (!cell) {
       cell = new CCTableViewCell();
       cell->autorelease();
       //to user
	   cell->addChild(createLabel4Cell(tag_User, lstEmails.at(idx).toUser.c_str(), CCSizeMake(160, 40), ccp(0, 0)));
	   //datetime
	   cell->addChild(createLabel4Cell(tag_Date, lstEmails.at(idx).datetime.c_str(), CCSizeMake(160, 40), ccp(164, 0)));
	   //contents
	   cell->addChild(createLabel4Cell(tag_Content, lstEmails.at(idx).content.c_str(), CCSizeMake(328, 40), ccp(164*2, 0)));

	   CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
	   line->setPosition(ccp(tblEmail->getContentSize().width/2,0));
	   line->setScaleX(tblEmail->getContentSize().width/line->getContentSize().width);
	   line->setAnchorPoint(ccp(0.5,0));
	   cell->addChild(line);
   }
   else
   {
//        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(tag_NameGame);
//        if( label )
//            label->setString(mUtils::getGameNameByID(100+idx)->getCString());
//        //
//        CCLabelTTF *labelLevel = (CCLabelTTF*)cell->getChildByTag(tag_Level);
//        if( labelLevel )
//            labelLevel->setString(CCString::createWithFormat("Level: %d", historys[idx].numOfLevel)->getCString());
//        //
//        CCLabelTTF *labelWin = (CCLabelTTF*)cell->getChildByTag(tag_WinLose);
//        if( labelWin )
//            labelWin->setString(CCString::createWithFormat("Thắng %d/Thua %d", historys[idx].numOfWin, historys[idx].numOfLose)->getCString());
   }
    return cell;
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerInbox::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return lstEmails.size();
}

void LayerInbox::loadAllMyDatas(){
    lstEmails.clear();
    //Send get list
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    params->PutUtfString("startT", "24/02/2013 08:30:59");
    params->PutUtfString("endT", mUtils::getCurrentDateTime("%d/%m/%Y 23:59:59").c_str());
    params->PutInt("startR", 0);
    params->PutInt("endR", 100);
    boost::shared_ptr<IRequest> request (new ExtensionRequest("glmi", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerInbox::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	CCLOG("cmd=%s", cmd->c_str());
    if(strcmp("glmi", cmd->c_str())==0){ //rglsim response
       boost::shared_ptr<string> glmi = param->GetUtfString("glmi");
       CCLOG("glmi: %s", glmi->c_str());
	   processGLMIMessage( *glmi );
//        vector<string> lstEmail = mUtils::splitString(*emails, "$#");
	}else if(strcmp("rglsim", cmd->c_str())==0){
		boost::shared_ptr<string> rglsim = param->GetUtfString("rglsim");
		CCLOG("rglsim: %s", rglsim->c_str());
		//processRGLSIMMessage( *glmi );
	}else if(strcmp("rglmibai", cmd->c_str())==0){
		boost::shared_ptr<string> rglmibai = param->GetUtfString("rglmibai");
		CCLOG("rglmibai: %s", rglmibai->c_str());
		//processRGLSIMMessage( *glmi );
	}
}

void LayerInbox::processGLMIMessage( string msg )
{
	//98$%hoangdd$%dautv4$%(3)(3)(2)(2)(2)(2)(2)(2)$%23//03/2014 12:46:26$%1$#...
	vector<string> lstRegex;
	lstRegex.push_back("$#");
	vector<string> lstAccounts = mUtils::splitStringByListRegex(msg, lstRegex);
	//
	lstRegex.clear();
	lstRegex.push_back("$%");
	//
	lstEmails.clear();
	for( int i = 0; i<lstAccounts.size(); i++ ){
		if( lstAccounts.at(i).compare("")==0 || lstAccounts.at(i).size()<5 )
			continue;
		vector<string> lstInfos = mUtils::splitStringByListRegex(lstAccounts.at(i), lstRegex);
		StructEmail infos;
		infos.id = atoi( lstInfos.at(0).c_str() );
		infos.fromUser = lstInfos.at(1);
		infos.toUser = lstInfos.at(2);
		infos.content = lstInfos.at(3);
		infos.datetime = lstInfos.at(4);
		lstEmails.push_back(infos);
	}
	tblEmail->reloadData();
}

void LayerInbox::processRGLSIMMessage( string msg )
{
// 	vector<string> lstRegex;
// 	lstRegex.push_back("$#");
// 	vector<string> lstAccounts = mUtils::splitStringByListRegex(msg, lstRegex);
// 	//
// 	lstRegex.clear();
// 	lstRegex.push_back("$%");
// 	//
// 	lstEmails.clear();
// 	for( int i = 0; i<lstAccounts.size(); i++ ){
// 		if( lstAccounts.at(i).compare("")==0 )
// 			continue;
// 		vector<string> lstInfos = mUtils::splitStringByListRegex(lstAccounts.at(i), lstRegex);
// 		StructEmail infos;
// 		infos.id = atoi( lstInfos.at(0).c_str() );
// 		infos. = lstInfos.at(1);
// 		infos.content = lstInfos.at(2);
// 		infos.datetime = lstInfos.at(3);
// 		lstEmails.push_back(infos);
// 	}
// 	tblEmail->reloadData();
}

CCNode* LayerInbox::createLabel4Cell( int tag, const char* text, CCSize size, CCPoint point )
{
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
