//
//  LayerOpenCard_Xito.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerOpenCard_Xito.h"
#include "Requests/ExtensionRequest.h"
#include "XiTo.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerOpenCard_Xito::LayerOpenCard_Xito()
{
	btnCard1 = NULL;
	btnCard2 = NULL;
	arrCardTypes[0] = "h";
	arrCardTypes[1] = "s";
	arrCardTypes[2] = "c";
	arrCardTypes[3] = "d";
}

LayerOpenCard_Xito::~LayerOpenCard_Xito()
{
	CC_SAFE_RELEASE(btnCard1);
	CC_SAFE_RELEASE(btnCard2);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerOpenCard_Xito::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCard1", LayerOpenCard_Xito::onButtonCard1);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCard2", LayerOpenCard_Xito::onButtonCard2);
	return NULL;
}

void LayerOpenCard_Xito::onButtonCard1(CCObject* pSender)
{
	CCLOG("onButtonCard1");
	CCMenuItem *b = (CCMenuItem*)pSender;
	CCLOG("Tag = %d",b->getTag());
	sendOpenCards(b->getTag());
}

void LayerOpenCard_Xito::onButtonCard2(CCObject* pSender)
{
	CCLOG("onButtonCard2");
	CCMenuItem *b = (CCMenuItem*)pSender;
	CCLOG("Tag = %d",b->getTag());
	sendOpenCards(b->getTag());
}

// CCBMemberVariableAssigner interface
bool LayerOpenCard_Xito::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	//CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnCard1", CCMenuItem *, btnCard1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnCard2", CCMenuItem *, btnCard2);
	return true;
}

void LayerOpenCard_Xito::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("Imhere onNodeLoaded");
	CCLOG("Nhay vao day dau tien");
	btnCard1->setOpacity(0);
	btnCard2->setOpacity(0);
	CCLOG("%f %f",btnCard2->getContentSize().width,btnCard2->getContentSize().height);

	this->setTouchEnabled(true);
	return;
}

void LayerOpenCard_Xito::sendOpenCards(int cardIdx){
	boost::shared_ptr<ISFSObject> param (new SFSObject());
	param->PutInt("crdvl",cardIdx);
	//EXT_EVENT_SELECT_OPEN_CARD_REQ = "slstrq";
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest("slstrq",param,lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
	//    XiTo::setChooseCard(false);
	this->removeFromParentAndCleanup(true);
}

void LayerOpenCard_Xito::setDealCards(string listDeal){
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("CardsBig.plist");

	vector<string> arrCards = Dsplit(listDeal, ',');


	CCSprite* s = CCSprite::createWithSpriteFrameName(("CardsBig/"+findtypeCard(convertCard(arrCards[0]))).c_str());
	s->setAnchorPoint(ccp(0, 0));
	s->setPosition(ccp(0, 0));
	btnCard1->setTag(atoi(arrCards[0].c_str()));
	btnCard1->addChild(s);

	CCSprite* s1 = CCSprite::createWithSpriteFrameName(("CardsBig/"+findtypeCard(convertCard(arrCards[1]))).c_str());

	s1->setAnchorPoint(ccp(0, 0));
	s1->setPosition(ccp(0, 0));
	btnCard2->setTag(atoi(arrCards[1].c_str()));
	btnCard2->addChild(s1);
}

string LayerOpenCard_Xito::convertCard(string strCard){
	vector<string> arrCards = Dsplit(strCard,',');
	string str = "";

	for(int i=0;i<arrCards.size();i++){
		if(arrCards[i]!=""){
			int a = atoi(arrCards[i].c_str());
			if(a==-1){
				str+="0_0-";
			}
			else{
				int num = a/4 + 7;
				string cardId = "";
				int type = a%4;

				if(type == 0){
					num--;
					cardId+=boost::to_string(num);
				}

				if(num == 14){
					num = 1;
					cardId = "1";
				}
				else if(num == 13){
					cardId = "k";
				}
				else if(num == 12){
					cardId = "q";
				}
				else if(num == 11){
					cardId = "j";
				}
				else{
					cardId = boost::to_string(num);
				}
				str += cardId + "_" + boost::to_string(type) + "-";
			}
		}
	}

	return str;

}
string LayerOpenCard_Xito::findtypeCard(string listCards){
	CCLOG("lc %s",listCards.c_str());
	vector<string> info = Dsplit(listCards, '_');
	CCLOG("card: %s, type %s",info[0].c_str(),info[1].c_str());
	string url = "card_"+info[0] + "_" + arrCardTypes[atoi(info[1].c_str())]+".png";
	return url;
}

vector<string> LayerOpenCard_Xito::Dsplit(string &S,const char &str){
	vector<string> arrStr;
	string::iterator t,t2;
	for(t=S.begin();t<S.end();){
		t2=find(t, S.end(),str);
		if(t!=t2)
			arrStr.push_back(string(t,t2));
		if(t2 == S.end())
			break;
		t=t2+1;
	}
	return arrStr;
}

void LayerOpenCard_Xito::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerOpenCard_Xito::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerOpenCard_Xito::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerOpenCard_Xito::onExit()
{
	CCLayer::onExit();
}