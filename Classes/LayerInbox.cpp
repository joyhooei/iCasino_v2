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
    tblEmail = CCTableView::create(this, nodeTableEmail->getContentSize());
    tblEmail->setDirection(kCCScrollViewDirectionVertical);
    tblEmail->setAnchorPoint(ccp(0, 0));
    tblEmail->setPosition(ccp(0, 0));
    tblEmail->setDelegate(this);
    tblEmail->setVerticalFillOrder(kCCTableViewFillTopDown);
    nodeTableEmail->addChild(tblEmail);
    tblEmail->reloadData();
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
//    if (!cell) {
//        cell = new CCTableViewCell();
//        cell->autorelease();
//        //Name game
//        CCLabelTTF *labelName = CCLabelTTF::create(mUtils::getGameNameByID(100+idx)->getCString(), "Helvetica", 17.0);
//        labelName->setPosition(ccp(0, 20));
//		labelName->setAnchorPoint(ccp(0, 0.5));
//        labelName->setTag(tag_User);
//        cell->addChild(labelName);
//        //Level
//        CCLabelTTF *labelLevel = CCLabelTTF::create(CCString::createWithFormat("Cấp độ: %d", historys[idx].numOfLevel)->getCString(), "Helvetica", 17.0);
//        labelLevel->setPosition(ccp(nodeTableEmail->getContentSize().width/2, 20));
//		labelLevel->setAnchorPoint(ccp(0.5, 0.5));
//        labelLevel->setTag(tag_Level);
//        cell->addChild(labelLevel);
//        //Win lose
//        CCLabelTTF *labelWin = CCLabelTTF::create(CCString::createWithFormat("Thắng %d/Thua %d", historys[idx].numOfWin, historys[idx].numOfLose)->getCString(), "Helvetica", 17.0);
//        labelWin->setPosition(ccp(nodeTableEmail->getContentSize().width, 20));
//		labelWin->setAnchorPoint(ccp(1, 0.5));
//        labelWin->setTag(tag_WinLose);
//        cell->addChild(labelWin);
//        //Sprite
//        CCSprite* s = CCSprite::createWithSpriteFrameName("assest/lineNgang.png");
//		s->setAnchorPoint(ccp(0.5, 0));
//        s->setPosition(ccp(nodeTableEmail->getContentSize().width/2, 0));
//        cell->addChild(s);
//    }
//    else
//    {
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
//    }
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
    params->PutUtfString("startT", "24/02/2014 08:30:59");
    params->PutUtfString("endT", mUtils::getCurrentDateTime("%d/%m/%Y %I:%M:%S").c_str());
    params->PutInt("startR", 0);
    params->PutInt("endR", 100);
    boost::shared_ptr<IRequest> request (new ExtensionRequest("rglsim", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerInbox::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("rglsim", cmd->c_str())==0){ //rglsim response
//        boost::shared_ptr<string> emails = param->GetUtfString("rglsim");
//        CCLOG("rglsim: %s", emails->c_str());
//        vector<string> lstEmail = mUtils::splitString(*emails, "$#");
    }
}