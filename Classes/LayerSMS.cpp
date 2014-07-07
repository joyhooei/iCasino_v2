//
//  LayerSMS.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/3/14.
//
//

#include "LayerSMS.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"

using namespace cocos2d;
//using namespace CocosDenshion;

LayerSMS::LayerSMS()
{
    nodeTable = NULL;
    tblTable = NULL;
    //
    StructSMS sms1;
    sms1.content = "81xx - 3.000 VND";
    StructSMS sms2;
    sms2.content = "85xx - 5.000 VND";
    StructSMS sms3;
    sms3.content = "86xx - 10.000 VND";
    StructSMS sms4;
    sms4.content = "87xx - 15.000 VND";
    StructSMS sms5;
    sms5.content = "88xx - 20.000 VND";
    
    lstSMS.push_back(sms1);
    lstSMS.push_back(sms2);
    lstSMS.push_back(sms3);
    lstSMS.push_back(sms4);
    lstSMS.push_back(sms5);
    //
    GameServer::getSingleton().addListeners(this);
}

LayerSMS::~LayerSMS()
{
    GameServer::getSingleton().removeListeners(this);
	//
	CC_SAFE_RELEASE(nodeTable);
}

void LayerSMS::loadAllDatas(){
}

void LayerSMS::onButtonClose(CCObject* pSender){
    this->removeFromParentAndCleanup(true);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerSMS::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCLOG("sfsdfsdf");
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerSMS::onButtonClose);
    return NULL;
}

// CCBMemberVariableAssigner interface
bool LayerSMS::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCLOG("sfsdfsdf12");
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTable", CCNode *, nodeTable);
    return true;
}

void LayerSMS::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
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
	//
	this->setTouchEnabled(true);
    return;
}

// hàm khi click vào 1 hành của table view
void LayerSMS::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d", 1);
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerSMS::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    return CCSizeMake(nodeTable->getContentSize().width, 40);
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerSMS::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    StructSMS sms = lstSMS.at(idx);
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        //Time
        CCLabelTTF *labelName = CCLabelTTF::create(sms.content.c_str(), "Helvetica", 16.0);
        labelName->setPosition(ccp(nodeTable->getContentSize().width/2, 20));
		labelName->setAnchorPoint(ccp(0.5, 0.5));
//        labelName->setTag(tag_NameFriend);
        cell->addChild(labelName);
        //Sprite
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(nodeTable->getContentSize().width/2,0));
        line->setScaleX(nodeTable->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else
    {
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
unsigned int LayerSMS::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return lstSMS.size();
}

void LayerSMS::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
}

void LayerSMS::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerSMS::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerSMS::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerSMS::onExit()
{
	CCLayer::onExit();
}
