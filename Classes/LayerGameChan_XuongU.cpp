//
//  LayerGameChan_XuongU.cpp
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#include "LayerGameChan_XuongU.h"
#include "mUtils.h"
#include "CustomTableViewCell.h"

#include "SceneManager.h"

using namespace cocos2d;

LayerGameChan_XuongU::LayerGameChan_XuongU()
{
	nodeTableListXuongSelected = NULL;
	nodeTableXuong = NULL;
	tblListXuongSelected = NULL;
	tblXuong = NULL;
	lblTime = NULL;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerGameChan_XuongU::~LayerGameChan_XuongU()
{
    GameServer::getSingleton().removeListeners(this);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerGameChan_XuongU::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{

	CCLOG("onResolveCCBCCMenuItemSelector: %s", pSelectorName);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnXuongU", LayerGameChan_XuongU::onButtonXuong);
    return NULL;
}

void LayerGameChan_XuongU::onButtonXuong(CCObject* pSender)
{
    CCLOG("onButtonXuong ");
}
// CCBMemberVariableAssigner interface
bool LayerGameChan_XuongU::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCLOG("onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeListXuong", CCNode *, nodeTableXuong);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeXuongSelected", CCNode *, nodeTableListXuongSelected);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTime", CCLabelTTF *, lblTime);
    return true;
}

void LayerGameChan_XuongU::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	return;
    //Init for table List Room
    tblListXuongSelected = CCTableView::create(this, nodeTableListXuongSelected->getContentSize());
    tblListXuongSelected->setDirection(kCCScrollViewDirectionVertical);
    tblListXuongSelected->setAnchorPoint(ccp(0, 0));
    tblListXuongSelected->setPosition(ccp(0, 0));
    tblListXuongSelected->setDelegate(this);
    tblListXuongSelected->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblListXuongSelected->setTag(tagListXuongSelected);
    nodeTableListXuongSelected->addChild(tblListXuongSelected);
    //Init for table List Room
    tblXuong = CCTableView::create(this, nodeTableXuong->getContentSize());
    tblXuong->setDirection(kCCScrollViewDirectionVertical);
    tblXuong->setAnchorPoint(ccp(0, 0));
    tblXuong->setPosition(ccp(0, 0));
    tblXuong->setDelegate(this);
    tblXuong->setVerticalFillOrder(kCCTableViewFillTopDown);
    tblXuong->setTag(tagListXuong);
    nodeTableXuong->addChild(tblXuong);
    tblXuong->reloadData();
    //
    return;
}

// hàm khi click vào 1 hành của table view
void LayerGameChan_XuongU::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    CCLOG("Roomid: %d", cell->getObjectID());
    if(table->getTag()==tagListXuongSelected){
        
    }else{
		
	}
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerGameChan_XuongU::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    if(table->getTag()==tagListXuongSelected)
        return CCSizeMake(nodeTableListXuongSelected->getContentSize().width, 20);
    return CCSizeMake(nodeTableXuong->getContentSize().width, 40);
}

CCTableViewCell* LayerGameChan_XuongU::process4ListXuong(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    if(!cell){
//         cell = new CustomTableViewCell(CCSizeMake(nodeTableListXuongSelected->getContentSize().width, 40));
//         cell->autorelease();
//         cell->setObjectID(rooms->at(idx)->Id());
//         cell->setTag(rooms->at(idx)->Id());
//         // Mã phòng
//         cell->addChild(createLabel4Cell(tag_RoomID, boost::to_string(rooms->at(idx)->Id()).c_str(), CCSizeMake(100, 40), ccp(0, 0)));
//         
//         //người chơi
//         CCString *songuoi = CCString::createWithFormat("%s/%s",boost::to_string(rooms->at(idx)->UserCount()).c_str(),boost::to_string(rooms->at(idx)->MaxUsers()).c_str());
//         
//         cell->addChild(createLabel4Cell(tag_Players, songuoi->getCString(), CCSizeMake(100, 40), ccp(101, 0)));
//         
//         cell->addChild(createLabel4Cell(tag_Bet, rv->GetStringValue()->c_str(), CCSizeMake(100, 40), ccp(202, 0)));
//         
//         cell->addChild(createLabel4Cell(-1, "Nhà chẳng có gì, có mỗi điều kiện", CCSizeMake(271, 40), ccp(302, 0)));
//         
//         CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
//         line->setPosition(ccp(tblListXuongSelected->getContentSize().width/2,0));
//         line->setScaleX(tblListXuongSelected->getContentSize().width/line->getContentSize().width);
//         line->setAnchorPoint(ccp(0.5,0));
//         cell->addChild(line);
    }
    else{
//         CCLabelTTF *label1 = getLabelFromTagID(cell, tag_RoomID);
//         if( label1!=NULL )
//             label1->setString(boost::to_string(rooms->at(idx)->Id()).c_str());
//         
//         CCLabelTTF *label2 = getLabelFromTagID(cell, tag_Players);
//         if( label2!=NULL ){
//             CCString *songuoi = CCString::createWithFormat("%s/%s",boost::to_string(rooms->at(idx)->UserCount()).c_str(),boost::to_string(rooms->at(idx)->MaxUsers()).c_str());
//             label2->setString(songuoi->getCString());
//         }
//         
//         CCLabelTTF *label3 = getLabelFromTagID(cell, tag_Bet);
//         if( label3!=NULL )
//             label3->setString(rv->GetStringValue()->c_str());
    }
    return cell;
}
CCTableViewCell* LayerGameChan_XuongU::process4XuongSelected(cocos2d::extension::CCTableView *table, unsigned int idx){
    CustomTableViewCell *cell = (CustomTableViewCell *)table->dequeueCell();
   // CCLOG("cell: %lf %lf", tblRooms->getContentSize().width, tblRooms->getContentSize().height);
    CCString *soPhong = CCString::createWithFormat("Phòng %d", idx+1);
    if(!cell){
//         cell = new CustomTableViewCell(CCSizeMake(nodeTableXuong->getContentSize().width, 40));
//         cell->setObjectID(idx);
//         cell->autorelease();
//         cell->setTag(idx);
//         cell->setSelectedState( idx==0 );
//         //
//         cell->addChild(createLabel4Cell(tag_RoomID, soPhong->getCString(), CCSizeMake(nodeTableXuong->getContentSize().width, 40), ccp(0, 0)));
//         //
//         CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
//         line->setPosition(ccp(nodeTableXuong->getContentSize().width/2,0));
//         line->setScaleX(nodeTableXuong->getContentSize().width/line->getContentSize().width);
//         line->setAnchorPoint(ccp(0.5,0));
//         cell->addChild(line);
    }
    else{
//         CCLabelTTF *label1 = getLabelFromTagID(cell, tag_RoomID);
//         if( label1!=NULL )
//             label1->setString(soPhong->getCString());
// 		cell->setSelectedState(cell->getSelectedState());
    }
    return cell;
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerGameChan_XuongU::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
  //  CCLOG("tabletag: %d", table->getTag());
    if(table->getTag()==tagListXuongSelected){
        return process4ListXuong(table, idx);
    }
    return process4XuongSelected(table, idx);
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerGameChan_XuongU::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    if(table->getTag()==tagListXuongSelected){
       return 0;
    }
    if(table->getTag()==tagListXuong){
        return 0;
    }
    return 0;
}

void LayerGameChan_XuongU::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];

    CCLOG("cmd = %s",ptrNotifiedCmd->c_str());
}