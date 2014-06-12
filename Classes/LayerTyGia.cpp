//
//  LayerTyGia.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/3/14.
//
//

#include "LayerTyGia.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"

using namespace cocos2d;
//using namespace CocosDenshion;

LayerTyGia::LayerTyGia()
{
    nodeTable = NULL;
    tblTable = NULL;
	lblTitle = NULL;
    //
    StructSMS sms1;
    sms1.content = "Nạp thẻ 10.000 được 10.000 chips";
    StructSMS sms2;
    sms2.content = "Nạp thẻ 20.000 được 20.000 chips";
    StructSMS sms3;
    sms3.content = "Nạp thẻ 50.000 được 50.000 chips";
    StructSMS sms4;
    sms4.content = "Nạp thẻ 100.000 được 100.000 chips";
    StructSMS sms5;
    sms5.content = "Nạp thẻ 200.000 được 200.000 chips";
    
    StructSMS sms8;
    sms8.content = "SMS 5.000 được 2.500 chips";
    StructSMS sms6;
    sms6.content = "SMS 10.000 được 5.000 chips";
    StructSMS sms7;
    sms7.content = "SMS 15.000 được 7.500 chips";
    
    lstSMS.push_back(sms8);
    lstSMS.push_back(sms6);
    lstSMS.push_back(sms7);
    
    lstSMS.push_back(sms1);
    lstSMS.push_back(sms2);
    lstSMS.push_back(sms3);
    lstSMS.push_back(sms4);
    lstSMS.push_back(sms5);
    //
    GameServer::getSingleton().addListeners(this);
}

LayerTyGia::~LayerTyGia()
{
    GameServer::getSingleton().removeListeners(this);
}

void LayerTyGia::loadAllDatas(){
}

void LayerTyGia::onButtonClose(CCObject* pSender){
    this->removeFromParentAndCleanup(true);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerTyGia::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCLOG("sfsdfsdf");
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerTyGia::onButtonClose);
    return NULL;
}

// CCBMemberVariableAssigner interface
bool LayerTyGia::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTable", CCNode *, nodeTable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle", CCLabelTTF *, lblTitle);
    return true;
}

void LayerTyGia::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
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
    lblTitle->setString("TỶ GIÁ");
	//
	this->setTouchEnabled(true);
    return;
}

// hàm khi click vào 1 hành của table view
void LayerTyGia::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d", 1);
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerTyGia::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    return CCSizeMake(nodeTable->getContentSize().width, 40);
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerTyGia::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
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
unsigned int LayerTyGia::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return lstSMS.size();
}

void LayerTyGia::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
}

void LayerTyGia::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerTyGia::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerTyGia::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerTyGia::onExit()
{
	CCLayer::onExit();
}
