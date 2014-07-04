//
//  LayerUserInfo_Details.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerUserInfo_Details.h"
#include "mUtils.h"
#include "GameServer.h"
#include "LayerUpdateInfo.h"
#include "SceneManager.h"
#include "Requests/ExtensionRequest.h"
#include "Requests/LogoutRequest.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerUserInfo_Details::LayerUserInfo_Details()
{
    lblName = NULL;
    lblAMF = NULL;
    lblAM = NULL;
    lblID = NULL;
    lblLevel = NULL;
    
    nodeTableHistory = NULL;
    tblHistory = NULL;
    
    for( int i = 0 ; i<mUtils::numOfGame; i++ ){
        historys[i].ID = 100+i;
        historys[i].name = mUtils::getGameNameByID(100+i);
        historys[i].numOfLevel = 0;
        historys[i].numOfWin = 0;
        historys[i].numOfLose = 0;
    }
    //
    GameServer::getSingleton().addListeners(this);
}

LayerUserInfo_Details::~LayerUserInfo_Details()
{
    GameServer::getSingleton().removeListeners(this);
    //
    CCLOG("Call ~LayerUserInfo_Details()");
    CC_SAFE_RELEASE(lblName);
    CC_SAFE_RELEASE(lblAMF);
    CC_SAFE_RELEASE(lblAM);
    CC_SAFE_RELEASE(lblID);
    CC_SAFE_RELEASE(lblLevel);
    
    CC_SAFE_RELEASE(nodeTableHistory);
}

void LayerUserInfo_Details::loadAllMyDatas(){
    boost::shared_ptr<double> am, amf;
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    if( myself==NULL || myself->GetVariable("am")==NULL || myself->GetVariable("amf")==NULL ){
        CCLOG("myself %s= NULL | myself->GetVariable(am) %s= NULL | myself->GetVariable(amf)%s=NULL",
              myself==NULL?"=":"!", myself->GetVariable("am")==NULL?"=":"!", myself->GetVariable("amf")==NULL?"=":"!");
        return;
    }
    am = myself->GetVariable("am")->GetDoubleValue();
    amf = myself->GetVariable("amf")->GetDoubleValue();
    //Set Name
    lblName->setString( GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("aN")->GetStringValue()->c_str() );
    lblAMF->setString( mUtils::convertMoneyEx(*amf).c_str() );
    lblAM->setString( mUtils::convertMoneyEx(*am).c_str() );
    lblID->setString( boost::to_string(myself->Id()).c_str() );
    //Get histories
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("rghba", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerUserInfo_Details::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUpdate", LayerUserInfo_Details::onButtonUpdate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnThoat", LayerUserInfo_Details::onButtonLogout);
    return NULL;
}

void LayerUserInfo_Details::onButtonUpdate(CCObject* pSender)
{
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerUpdateInfo* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerUpdateInfo *)ccbReader->readNodeGraphFromFile( "LayerUpdateInfo.ccbi" );
        mLayer->setZOrder(1000);
        this->getParent()->getParent()->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    mLayer->loadAllMyDatas();
}

void LayerUserInfo_Details::onButtonLogout(CCObject* pSender)
{
    
    boost::shared_ptr<IRequest> request (new LogoutRequest());
    SceneManager::getSingleton().gotoLogin();
    CCLOG("Logout");
    GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBMemberVariableAssigner interface
bool LayerUserInfo_Details::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
//    if( pMemberVariableName==NULL || strcmp(pMemberVariableName, "")==0 )
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblAM", CCLabelTTF *, lblAM);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblAMF", CCLabelTTF *, lblAMF);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblID", CCLabelTTF *, lblID);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblName", CCLabelTTF *, lblName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblLevel", CCLabelTTF *, lblLevel);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTableHistory", CCNode *, nodeTableHistory);
    return true;
}

void LayerUserInfo_Details::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    //Init for table
    tblHistory = CCTableView::create(this, nodeTableHistory->getContentSize());
    tblHistory->setDirection(kCCScrollViewDirectionVertical);
    tblHistory->setAnchorPoint(ccp(0, 0));
    tblHistory->setPosition(ccp(0, 0));
    tblHistory->setDelegate(this);
    tblHistory->setVerticalFillOrder(kCCTableViewFillTopDown);
    
    nodeTableHistory->addChild(tblHistory);
    return;
}

// hàm khi click vào 1 hành của table view
void LayerUserInfo_Details::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d",cell->getObjectID());
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerUserInfo_Details::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    return CCSizeMake(nodeTableHistory->getContentSize().width, 40);
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerUserInfo_Details::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
//    CCLOG("cell: %d %s", idx, mUtils::getGameNameByID(100+idx)->getCString());
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        //Name game
        CCLabelTTF *labelName = CCLabelTTF::create(mUtils::getGameNameByID(100+idx)->getCString(), "Helvetica", 20.0);
        labelName->setPosition(ccp(0, 20));
		labelName->setAnchorPoint(ccp(0, 0.5));
        labelName->setTag(tag_NameGame);
        cell->addChild(labelName);
        //Level
        CCLabelTTF *labelLevel = CCLabelTTF::create(CCString::createWithFormat("Cấp độ: %d", historys[idx].numOfLevel)->getCString(), "Helvetica", 20.0);
        labelLevel->setPosition(ccp(nodeTableHistory->getContentSize().width/2, 20));
		labelLevel->setAnchorPoint(ccp(0.5, 0.5));
        labelLevel->setTag(tag_Level);
        cell->addChild(labelLevel);
        //Win lose
        CCLabelTTF *labelWin = CCLabelTTF::create(CCString::createWithFormat("Thắng %d/Thua %d", historys[idx].numOfWin, historys[idx].numOfLose)->getCString(), "Helvetica", 20.0);
        labelWin->setPosition(ccp(nodeTableHistory->getContentSize().width, 20));
		labelWin->setAnchorPoint(ccp(1, 0.5));
        labelWin->setTag(tag_WinLose);
        cell->addChild(labelWin);
        //Sprite
        CCSprite* s = CCSprite::createWithSpriteFrameName("assest/lineNgang.png");
		s->setAnchorPoint(ccp(0.5, 0));
        s->setPosition(ccp(nodeTableHistory->getContentSize().width/2, 0));
        cell->addChild(s);
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

// Hàm gán giá trị số hàng của table view
unsigned int LayerUserInfo_Details::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return mUtils::numOfGame;
}

void LayerUserInfo_Details::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("rghba", cmd->c_str())==0){ //History response
        CCLOG("History response: %s", param->GetUtfString("rghba")->c_str());
        vector<string> lstHis;
        lstHis = mUtils::splitString(*param->GetUtfString("rghba"), '|');
        //
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
    }
}
