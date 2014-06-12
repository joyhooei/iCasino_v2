//
//  LayerLichSuGiaoDich.cpp
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#include "LayerLichSuGiaoDich.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"

using namespace cocos2d;
//using namespace CocosDenshion;

LayerLichSuGiaoDich::LayerLichSuGiaoDich()
{
    nodeHistory = NULL;
    tblHistory = NULL;
    //
    GameServer::getSingleton().addListeners(this);
    
    CCLOG("current: %s", mUtils::getCurrentDateTime("%d/%m/%Y %I:%M:%S").c_str());
}

LayerLichSuGiaoDich::~LayerLichSuGiaoDich()
{
    GameServer::getSingleton().removeListeners(this);
}

void LayerLichSuGiaoDich::loadAllDatas(){
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    params->PutUtfString("startT", "24/02/2014 08:30:59");
    params->PutUtfString("endT", mUtils::getCurrentDateTime("%d/%m/%Y %I:%M:%S").c_str());
    params->PutInt("maqp", 20);
    boost::shared_ptr<IRequest> request (new ExtensionRequest("glts", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
    
}


CCNode* LayerLichSuGiaoDich::createLabel4Cell(int tag, const char* text, CCSize size, CCPoint point){
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

CCLabelTTF* LayerLichSuGiaoDich::getLabelFromTagID(CCTableViewCell *cell, int tag){
    CCNode* node = cell->getChildByTag(tag);
    if( node == NULL )
        return NULL;
    CCLabelTTF *lbl = (CCLabelTTF*)node->getChildByTag(tag);
    return lbl;
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerLichSuGiaoDich::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

// CCBMemberVariableAssigner interface
bool LayerLichSuGiaoDich::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeHistory", CCNode *, nodeHistory);
    return true;
}

void LayerLichSuGiaoDich::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    //Init for table
    tblHistory = CCTableView::create(this, nodeHistory->getContentSize());
    tblHistory->setDirection(kCCScrollViewDirectionVertical);
    tblHistory->setAnchorPoint(ccp(0, 0));
    tblHistory->setPosition(ccp(0, 0));
    tblHistory->setDelegate(this);
    tblHistory->setVerticalFillOrder(kCCTableViewFillTopDown);
    
    nodeHistory->addChild(tblHistory);
    return;
}

// hàm khi click vào 1 hành của table view
void LayerLichSuGiaoDich::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d",cell->getObjectID());
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerLichSuGiaoDich::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    return CCSizeMake(nodeHistory->getContentSize().width, 40);
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerLichSuGiaoDich::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    StructHistory his = lstHistory.at(idx);
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        //Time
        cell->addChild(createLabel4Cell(tag_cellTime, his.lastUpdateTime.c_str(), CCSizeMake(161*1.032, 40), ccp(0, 0)));
        //Amount
        cell->addChild(createLabel4Cell(tag_cellAmount, his.amount.c_str(), CCSizeMake(149*1.032, 40), ccp(162*1.032, 0)));
        //Details
        cell->addChild(createLabel4Cell(tag_cellDetails, mUtils::getExplainOfTransType(his.transType.c_str()).c_str(), CCSizeMake(430*1.032, 40), ccp(311*1.032, 0)));
        //Sprite
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(nodeHistory->getContentSize().width/2,0));
        line->setScaleX(nodeHistory->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else
    {
        CCLabelTTF *label1 = getLabelFromTagID(cell, tag_cellTime);
        if( label1!=NULL )
            label1->setString(his.lastUpdateTime.c_str());
        CCLabelTTF *label2= getLabelFromTagID(cell, tag_cellAmount);
        if( label2!=NULL )
            label2->setString(his.amount.c_str());
        CCLabelTTF *label3 = getLabelFromTagID(cell, tag_cellDetails);
        if( label3!=NULL )
            label3->setString(mUtils::getExplainOfTransType(his.transType.c_str()).c_str());
    }
    return cell;
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerLichSuGiaoDich::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return lstHistory.size();
}

void LayerLichSuGiaoDich::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("glts", cmd->c_str())==0){ //Lich su giao dich response
        CCLOG( "OnExtensionResponse cmd: %s data: %s", cmd->c_str(), param->GetUtfString("litr")->c_str() );
        vector<string> lstHis;
        lstHis = mUtils::splitString(*param->GetUtfString("litr"), '|');
        //
        lstHistory.clear();
        //
        for( int j = 0; j<lstHis.size(); j++ ){
            vector<string> his = mUtils::splitString(lstHis.at(j), ',');
            StructHistory structHis;
            structHis.transID= his.at(0);
            structHis.accId=his.at(1);
            structHis.ip=his.at(2);
            structHis.accId2=his.at(3);
            structHis.transType=his.at(4);
            structHis.amount = mUtils::convertMoneyEx(atof(his.at(5).c_str())).c_str() ;
            structHis.transErr=his.at(6);
            structHis.transErrDetail=his.at(7);
            structHis.status=his.at(8);
            structHis.cardSerial=his.at(9);
            structHis.cardPin=his.at(10);
            structHis.lastUpdateTime=his.at(11);
            lstHistory.push_back(structHis);
        }
        //OK, reload datas now
        tblHistory->reloadData();
    }
}