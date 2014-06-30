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
#include "Requests/ExtensionRequest.h"

#include "SceneManager.h"

using namespace cocos2d;

LayerGameChan_XuongU::LayerGameChan_XuongU()
{
	nodeTableListXuongSelected = NULL;
	nodeTableXuong = NULL;
	tblListXuongSelected = NULL;
	tblXuong = NULL;
	lblTime = NULL;
	cuoc.push_back("Xuông");
	cuoc.push_back("Thông");
	cuoc.push_back("Chì");
	cuoc.push_back("Thiên Ù");
	cuoc.push_back("Địa Ù");
	cuoc.push_back("Tôm");
	cuoc.push_back("Lèo");
	cuoc.push_back("Bạch Định");
	cuoc.push_back("Tám Đỏ");
	cuoc.push_back("Kính Tứ Chi");
	cuoc.push_back("Thập Thành");
	cuoc.push_back("Có Thiên Khai");
	cuoc.push_back("Ăn Bòn");
	cuoc.push_back("Ù Bòn");
	cuoc.push_back("Có Chíu");
	cuoc.push_back("Chíu Ù");
	cuoc.push_back("Bạch Thủ");
	cuoc.push_back("Hoa rơi cửa phật");
	cuoc.push_back("Nhà lầu xe hơi, hoa rơi cửa phật");
	cuoc.push_back("Cá lội sân đình");
	cuoc.push_back("Cá nhảy đầu thuyền");
	cuoc.push_back("Chùa đổ nát hoa");
	cuoc.push_back("Đôi Lèo");
	cuoc.push_back("Đôi Tám đỏ");
	cuoc.push_back("Đôi Tôm");
	cuoc.push_back("Bạch Thủ Chi");
    //
	chooseXuong = new CCArray();
	chooseXuong->retain();
    GameServer::getSingleton().addListeners(this);
}

LayerGameChan_XuongU::~LayerGameChan_XuongU()
{
    GameServer::getSingleton().removeListeners(this);
	chooseXuong->removeAllObjects();
	chooseXuong->release();
	cuoc.clear();
	CCLOG("Jump to Deconstructor LayerGameChan_XuongU");
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
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<ISFSObject> params (new SFSObject());

	string str = "";
	if (chooseXuong->count() == 0)
	{
		str = "";
	}
	else
	{
		for (int i = 0; i < (int)chooseXuong->count(); i++)
		{
			CCInteger *f = (CCInteger*) chooseXuong->objectAtIndex(i);
			if (i < chooseXuong->count() - 1)
			{
				str+=boost::to_string(f->getValue())+":";
			}
			else
				str+=boost::to_string(f->getValue());
		}
	}
	
	CCLOG("str = %s",str.c_str());
	params->PutUtfString("ucsac",str);
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rquanou",params,lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
	this->removeFromParentAndCleanup(true);
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
    //Init for table List Room
//     tblListXuongSelected = CCTableView::create(this, nodeTableListXuongSelected->getContentSize());
//     tblListXuongSelected->setDirection(kCCScrollViewDirectionVertical);
//     tblListXuongSelected->setAnchorPoint(ccp(0, 0));
//     tblListXuongSelected->setPosition(ccp(0, 0));
//     tblListXuongSelected->setDelegate(this);
//     tblListXuongSelected->setVerticalFillOrder(kCCTableViewFillTopDown);
//     tblListXuongSelected->setTag(tagListXuongSelected);
//     nodeTableListXuongSelected->addChild(tblListXuongSelected);
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
   
    if(table->getTag()==tagListXuong){
		CCLOG("cell click: %d", cell->getObjectID());
		CCLabelTTF *label1 = getLabelFromTagID(cell, tag_RoomID);
		CCLOG("%s ",label1->getString());

		if (chooseXuong->count() == 0)
		{
			CCInteger *value = CCInteger::create(cell->getObjectID());
			chooseXuong->addObject(value);
			CCSprite *icon = (CCSprite *) cell->getChildByTag(tag_Players);
			if (icon != NULL)
			{
				icon->setVisible(true);
			}
		}
		else
		{
			bool _flag = false;
			for(int i = 0; i < (int)chooseXuong->count(); i++)
			{
				CCInteger *f = (CCInteger*) chooseXuong->objectAtIndex(i);
				if (f->getValue() == cell->getObjectID()){
					_flag = true;
				}
			}

			if (_flag)
			{
				for (int i = 0; i < (int)chooseXuong->count(); i++)
				{
					CCInteger *f = (CCInteger*) chooseXuong->objectAtIndex(i);
					if (f->getValue() == cell->getObjectID())
					{
						chooseXuong->removeObjectAtIndex(i);
					}
				}
				CCSprite *icon = (CCSprite *) cell->getChildByTag(tag_Players);
				if (icon != NULL)
				{
					icon->setVisible(false);
				}
			}
			else
			{
				CCInteger *value = CCInteger::create(cell->getObjectID());
				chooseXuong->addObject(value);
				CCSprite *icon = (CCSprite*) cell->getChildByTag(tag_Players);
				if (icon != NULL)
				{
					icon->setVisible(true);
				}
			}
		}
		CCLOG("choose Xuong : %d ",chooseXuong->count());

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
		cell = new CustomTableViewCell(CCSizeMake(nodeTableXuong->getContentSize().width, 40));
		cell->autorelease();
		cell->setObjectID(idx);
		cell->setTag(idx);
		cell->addChild(createLabel4Cell(tag_RoomID, cuoc[idx].c_str(), CCSizeMake(100, 40), ccp(0, 0)));
   
		CCSprite* sLock = CCSprite::create("lock.png");
		sLock->setTag( tag_Players );
		sLock->setPosition(ccp(5, 20));
		sLock->setAnchorPoint(ccp(0, 0.5));
		sLock->setScale(0.7);
		sLock->setVisible(false);
		cell->addChild(sLock);
	}
    else{
		CCLabelTTF *label1 = getLabelFromTagID(cell, tag_RoomID);
		if( label1!=NULL )
			label1->setString(cuoc[idx].c_str());
		if (cell->getChildByTag(tag_Players) == NULL)
		{
			CCSprite* sLock = CCSprite::create("lock.png");
			sLock->setTag( tag_Players );
			sLock->setPosition(ccp(5, 20));
			sLock->setAnchorPoint(ccp(0, 0.5));
			sLock->setScale(0.7);
			sLock->setVisible(false);
			cell->addChild(sLock);
		}
    }
    return cell;
}
CCTableViewCell* LayerGameChan_XuongU::process4XuongSelected(cocos2d::extension::CCTableView *table, unsigned int idx){
    CustomTableViewCell *cell = (CustomTableViewCell *)table->dequeueCell();
   // CCLOG("cell: %lf %lf", tblRooms->getContentSize().width, tblRooms->getContentSize().height);
    //CCString *soPhong = CCString::createWithFormat("Phòng %d", idx+1);
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

CCLabelTTF* LayerGameChan_XuongU::getLabelFromTagID(CCTableViewCell *cell, int tag){
	CCNode* node = cell->getChildByTag(tag);
	if( node == NULL )
		return NULL;
	CCLabelTTF *lbl = (CCLabelTTF*)node->getChildByTag(tag);
	return lbl;
}

CCNode* LayerGameChan_XuongU::createLabel4Cell(int tag, const char* text, CCSize size, CCPoint point){
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

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerGameChan_XuongU::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
  //  CCLOG("tabletag: %d", table->getTag());
    if(table->getTag()==tagListXuong){
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
		//cuoc->length();
        return (int)cuoc.size();
    }
    return 0;
}

void LayerGameChan_XuongU::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];

    CCLOG("cmd (in xuong u) = %s",ptrNotifiedCmd->c_str());
	if (strcmp("rsuanou",ptrNotifiedCmd->c_str()) == 0)
	{
		CCLOG("nhan duoc respond");
	}
}