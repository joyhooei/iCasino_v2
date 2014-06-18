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

#include "Requests/JoinRoomRequest.h"
#include "SceneManager.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerChatRoom::LayerChatRoom()
{
    nodeListContents = NULL;
    tblListContents = NULL;
    
    nodeListRooms = NULL;
    tblListRooms = NULL;
    
    lblTitle = NULL;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerChatRoom::~LayerChatRoom()
{
    GameServer::getSingleton().removeListeners(this);
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
	CCLOG("onButtonChat");
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
    CCLOG("Roomid: %d", cell->getObjectID());
//    if(table->getTag()==tagListPlay){
//        CCLOG("Roomid: %d",cell->getObjectID());
//        boost::shared_ptr<Room> ro = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup(CCString::createWithFormat("%d", m_gID)->getCString())->at(cell->getObjectID());
//        //GetRoomById(cell->getTag());
//        if(ro==NULL){
//            CCLOG("Roomid: %d NOT FOUND",cell->getObjectID());
//            return;
//        }
//        
//        boost::shared_ptr<IRequest> request (new JoinRoomRequest(ro,""));
//        GameServer::getSingleton().getSmartFox()->Send(request);
//    }
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerChatRoom::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    if(table->getTag()==tagListRoom)
        return CCSizeMake(nodeListRooms->getContentSize().width, 40);
    //Rooms
    //    if( idx==0 )
    //        return CCSizeMake(nodeListContents->getContentSize().width, 0);
    return CCSizeMake(nodeListContents->getContentSize().width, 40);
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
    }
    else{
        CCLabelTTF *label1 = getLabelFromTagID(cell, tag_Content);
        if( label1!=NULL )
            label1->setString(rooms->at(idx)->Name()->c_str());
    }
    return cell;
}
CCTableViewCell* LayerChatRoom::process4ListContents(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    CCLOG("cell: %lf %lf", tblListContents->getContentSize().width, tblListContents->getContentSize().height);
    CCString *soPhong = CCString::createWithFormat("Phòng %d", idx+1);
    if(!cell){
        cell = new CustomTableViewCell(CCSizeMake(nodeListContents->getContentSize().width, 40));
        cell->setObjectID(idx);
        cell->autorelease();
        cell->setTag(idx);
        
        //
        //
        CCSprite* line = CCSprite::createWithSpriteFrameName("assest/background_cell.png");
        line->setPosition(ccp(nodeListContents->getContentSize().width/2,0));
        line->setScaleX(nodeListContents->getContentSize().width/line->getContentSize().width);
        line->setAnchorPoint(ccp(0.5,0));
        cell->addChild(line);
    }
    else{
        CCLabelTTF *label1 = getLabelFromTagID(cell, tag_Content);
        if( label1!=NULL )
            label1->setString(soPhong->getCString());
    }
    return cell;
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerChatRoom::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCLOG("tabletag: %d", table->getTag());
    if(table->getTag()==tagListRoom){
        return process4ListRooms(table, idx);
    }
    return process4ListContents(table, idx);
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerChatRoom::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    CCLOG("tabletag: %d", table->getTag());
    if(table->getTag()==tagListRoom){
        boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms
        = GameServer::getSingleton().getSmartFox()->GetRoomListFromGroup("200");
        return rooms->size();
    }
    if(table->getTag()==tagListContent){
        return 0;
    }
    return 0;
}


void LayerChatRoom::OnSmartFoxInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Invite Playe");
}

void LayerChatRoom::OnSmartFoxRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Join Room");
    SceneManager::getSingleton().gotoGameByTag(m_gID);
}

void LayerChatRoom::OnSmartFoxRoomJoinError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Join Room Error");
}

void LayerChatRoom::OnSmartFoxRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Create Room Error");
}

void LayerChatRoom::OnSmartFoxRoomAdd(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("Room Add");
}

void LayerChatRoom::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("User Exit Room Ở chọn bàn chơi");
    //SceneManager::getSingleton().gotoMain();
}

void LayerChatRoom::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    
    CCLOG("cmd = %s",ptrNotifiedCmd->c_str());
}