//
//  LayerGameChan_KetQua.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerGameChan_KetQua.h"
#include "GameServer.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
#include "CardChan.h"

using namespace Sfs2X;
using namespace cocos2d;
//using namespace CocosDenshion;


LayerGameChan_KetQua::LayerGameChan_KetQua()
{
	lblThongBao=NULL;
	lblMoney=NULL;

	CARD_NOC = CCArray::create();
	CARD_NOC->retain();
	CARD_WINNER = CCArray::create();
	CARD_WINNER->retain();

	EXT_EVENT_REQ_NOC_DETAIL = "rqnocdtl";
	EXT_EVENT_REQ_TRENTAY_DETAIL = "rqttdtl";
	GameServer::getSingleton().addListeners(this);
}

LayerGameChan_KetQua::~LayerGameChan_KetQua()
{
	GameServer::getSingleton().removeListeners(this);
	CARD_NOC->removeAllObjects();
	CARD_NOC->release();
	CARD_WINNER->removeAllObjects();
	CARD_WINNER->release();

	CCLOG("Jumpe to Deconstructor LayerGameChan_KetQua");
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerGameChan_KetQua::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnXemNoc", LayerGameChan_KetQua::onButtonXemNoc);
	return NULL;
}

void LayerGameChan_KetQua::onButtonXemNoc(CCObject* pSender)
{
	CCLOG("onButtonXemNoc");
	//this->removeFromParentAndCleanup(true);
	setCard_Noc("95:9:2:0:0;94:9:2:1:0;70:7:2:0:0;71:7:2:0:0;94:9:2:1:0;70:7:2:0:0;71:7:2:0:0;71:7:2:0:0;54:6:1:0:0;53:6:1:0:0;70:7:2:0:0;71:7:2:0:0;54:6:1:0:0;53:6:1:0:0;70:7:2:0:0;71:7:2:0:0;54:6:1:0:0;53:6:1:0:0");

}

// CCBMemberVariableAssigner interface
bool LayerGameChan_KetQua::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblThongBao", CCLabelTTF *, lblThongBao);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
	return true;
}

void LayerGameChan_KetQua::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("Imhere onNodeLoaded");
	lblThongBao->setString("dautv da bao u con bai nay \n cho nha nay xuong");
	lblMoney->setString("");
	setListCard_WinnerUser("95:9:2:0:0;94:9:2:1:0;70:7:2:0:0;71:7:2:0:0;94:9:2:1:0;70:7:2:0:0;71:7:2:0:0;71:7:2:0:0;54:6:1:0:0;53:6:1:0:0;70:7:2:0:0;71:7:2:0:0;54:6:1:0:0;53:6:1:0:0;70:7:2:0:0;71:7:2:0:0;54:6:1:0:0;53:6:1:0:0");
	this->setTouchEnabled(true);
}

void LayerGameChan_KetQua::rotateListCards(CCArray *P){
	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CCActionInterval *action = CCRotateBy::create(0.8, dem*(250/19));
		card->runAction(CCSequence::create(action,NULL));
		dem++;
	}
}

void LayerGameChan_KetQua::setCard_Noc(string listnoc){
	if (CARD_NOC->count() > 0)
	{
		while(CARD_NOC->count() > 0)
		{
			CardChan* cards = (CardChan*)CARD_NOC->lastObject();
			CARD_NOC->removeLastObject();
			cards->removeFromParentAndCleanup(true);
		}
	}

	vector<string> arrNoc = mUtils::splitString(listnoc,';');
	float startLeft = (800 - (arrNoc.size() * 30)) / 2;
	int i = 0;
	int listsize = (int)arrNoc.size();
	while(i <= listsize)
	{
		if (i < listsize)
		{
			vector<string> info = mUtils::splitString(arrNoc[i],':');
			CardChan *pCard = CardChan::create();
			pCard->loadTexture(findTypeCard(info[1],info[2]).c_str());
			pCard->setSizeCard(30,100);
			pCard->setPosition(ccp(startLeft,50));
			CARD_NOC->addObject(pCard);
			this->addChild(pCard);
			i++;
		}
		else
		{
			displayListCard_Noc(CARD_NOC);
			break;
		}
	}
}

string LayerGameChan_KetQua::findTypeCard(string number,string suite){
	string str = "";
	str += number+"_"+suite+".png";
	return str;
}

void LayerGameChan_KetQua::setListCard_WinnerUser(string listcard){
	vector<string> arrCard = mUtils::splitString(listcard,';');
	int i = 0;
	int listsize = (int)arrCard.size();
	while (i <= listsize)
	{
		if (i < listsize)
		{
			vector<string> info = mUtils::splitString(arrCard[i],':');
			CardChan *pCard = CardChan::create();
			pCard->loadTexture(findTypeCard(info[1],info[2]).c_str());
			pCard->setAnchorPoint(ccp(0.5,0));
			pCard->setSizeCard(34,125);
			pCard->setPosition(ccp(200,240));
			float start = (listsize % 2 == 0) ? (float)listsize : (float)(listsize - 1);
			pCard->setRotation(-((start) / 2 * (250/19)));
			this->addChild(pCard);
			CARD_WINNER->addObject(pCard);
			i++;
		}
		else{
			rotateListCards(CARD_WINNER);
			break;
		}
	}
}

void LayerGameChan_KetQua::displayListCard_Noc(CCArray *P){
	if (P->count() == 0)
	{
		return;
	}

	int startLeft = (800 - P->count() * 30) / 2;
	CCLOG("Start Left %d",startLeft);
	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CCActionInterval *moveTo = CCMoveTo::create(0.8,ccp(startLeft + dem * 30,50));
		card->runAction(CCSequence::create(moveTo,NULL));
		dem++;
	}
}

void LayerGameChan_KetQua::displayListCard_Winner(string listcard){

}

void LayerGameChan_KetQua::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("hbc", cmd->c_str())==0){
		return;
	}
	CCLOG("cmd = %s",cmd->c_str());
}

void LayerGameChan_KetQua::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerGameChan_KetQua::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerGameChan_KetQua::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerGameChan_KetQua::onExit()
{
	CCLayer::onExit();
}