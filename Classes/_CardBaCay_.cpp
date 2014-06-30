//
//  _CardBaCay_.cpp
//  iCasino_v2
//
//  Created by DauA on 6/24/14.
//
//

#include "_CardBaCay_.h"
#include "CardChan.h"
#include "mUtils.h"

CardBaCay::~CardBaCay()
{
	CARD_ME->release();
	CARD_RIGHT->release();
	CARD_TOP->release();
	CARD_LEFT->release();
	this->removeAllChildren();
	CCLOG("Deconstructor Layer Cards Ba Cay");
}
//Chân
bool CardBaCay::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));
	this->setTouchEnabled(true);

	initGame();

	return true;
}

void CardBaCay::onExit()
{
	CARD_ME->release();
	CARD_RIGHT->release();
	CARD_TOP->release();
	CARD_LEFT->release();
	if(m_callback)
	{
		m_callback = NULL;
	}
	
	this->removeAllChildren();
	CCLOG("Deconstructor Layer Cards Ba Cay");
}

void CardBaCay::initGame()
{
	CARD_ME = CCArray::create();
	CARD_LEFT = CCArray::create();
	CARD_RIGHT = CCArray::create();
	CARD_TOP = CCArray::create();

	CARD_ME->retain();
	CARD_LEFT->retain();
	CARD_RIGHT->retain();
	CARD_TOP->retain();

	arrCardTypes.push_back("s");
	arrCardTypes.push_back("c");
	arrCardTypes.push_back("h");
	arrCardTypes.push_back("d");

	myListCards = "";
	listUser = "";
	myName = "";

	leftMe = 319;
	leftLeft = 117;
	leftRight = 539;
	leftTop = 328;
	bottomMe = 90; 
	bottomLeft = 209;
	bottomTop = 268;
	
	w_card_me = 54;
	w_card_notme = 48;
	h_card_me = 54 * 1.3;
	h_card_notme = 48 * 1.3;

	count_give = 0;

	m_callback = NULL;
	m_callbackListener = NULL;
}

void CardBaCay::resetGame()
{
	count_give = 0;
	deleteAllCards_FromArray(CARD_ME);
	deleteAllCards_FromArray(CARD_LEFT);
	deleteAllCards_FromArray(CARD_RIGHT);
	deleteAllCards_FromArray(CARD_TOP);
}

void CardBaCay::setListUser(string listuser)
{
	this->listUser = listuser;
}

void CardBaCay::setMyName(string name)
{
	this->myName = name;
}

void CardBaCay::givePocker()
{
	string virtualList = listUser + listUser + listUser;
	CCLOG("list virtual %s",virtualList.c_str());
	vector<string> arrVirtuals = mUtils::splitString(virtualList,';');
	if (arrVirtuals.size() == 0)
	{
		return;
	}
	int count_vir = (int) arrVirtuals.size();

	string player = arrVirtuals[count_give];
	vector<string> info = mUtils::splitString(player,'|');
	
	if (strcmp(info[0].c_str(),myName.c_str()) == 0)
	{
		give_next(CARD_ME, w_card_me, h_card_me, leftMe, bottomMe, count_vir);
	}
	else
	{
		switch(getPosUserByName(info[0]))
		{
		case kUserLeft:
			give_next(CARD_LEFT, w_card_notme, h_card_notme, leftLeft, bottomLeft, count_vir);
			break;
		case kUserRight:
			give_next(CARD_RIGHT, w_card_notme, h_card_notme, leftRight, bottomLeft, count_vir);
			break;
		case kUserTop:
			give_next(CARD_TOP, w_card_notme, h_card_notme, leftTop, bottomTop, count_vir);
			break;
		default:
			break;
		}
	}
}


void CardBaCay::give_next(CCArray *P, float _width, float _height, float _left, float _bottom, int count)
{
	count_give++;
	CardChan *card = CardChan::create();
    card->loadTexture("card_back.png");
    card->setSizeCard(w_card_notme, h_card_notme);
    card->setPosition(ccp(WIDTH_DESIGN/2-card->getContentSize().width/2,HEIGHT_DESIGN/2-card->getContentSize().height/2));
    this->addChild(card);

	CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(_left + P->count() *_width, _bottom));
    CCScaleBy *scaleTo = CCScaleBy::create(0.3, _width / w_card_notme, _height / h_card_notme);
    card->runAction(newTo);
    card->runAction(scaleTo);
    P->addObject(card);

	if (count_give < count)
	{
		 this->runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(CardBaCay::givePocker)),NULL));
	}
	else
	{
		//setCallBack
		CCLOG("Call back");
		if (m_callback && m_callbackListener)
		{
			(m_callback->*m_callbackListener)(this);
		}
	}
}

//create list card
void CardBaCay::turnUpAllCards(string lc, int pos)
{
	CCLOG("Jumpe to turn upp");
	switch(pos)
	{
	case kUserMe:
		turnUpAllCards_Pos(lc, CARD_ME, w_card_me, h_card_me, leftMe, bottomMe);
		break;
	case kUserLeft:
		turnUpAllCards_Pos(lc, CARD_LEFT, w_card_notme, h_card_notme, leftLeft, bottomLeft);
		break;
	case kUserRight:
		turnUpAllCards_Pos(lc, CARD_RIGHT, w_card_notme, h_card_notme, leftRight, bottomLeft);
		break;
	case kUserTop:
		turnUpAllCards_Pos(lc, CARD_TOP, w_card_notme, h_card_notme, leftTop, bottomTop);
		break;
	default:
		break;
	}
}

void CardBaCay::turnUpAllCards_Pos(string lc, CCArray *P, float _width, float _height, float _left, float _bottom){

	if (P->count() != 3)
	{
		deleteAllCards_FromArray(P);
		createListCard_Back(P, _width, _height, _left, _bottom);
	}
	
	vector<string> arrCards = mUtils::splitString(lc,'-');
	if (arrCards.size() == 0)
	{
		return;
	}

	for (int i = 0; i < arrCards.size(); i++)
	{
		CardChan *pCard = (CardChan*)P->objectAtIndex(i);
		if (strcmp(arrCards[i].c_str(),"0_0") == 0)
		{
			pCard->loadTexture("card_back.png");
		}
		else
		{
			vector<string> info = mUtils::splitString(arrCards[i],'_');
			string str = "card_"+findTypeCardByID(info[0])+"_"+arrCardTypes[atoi(info[1].c_str())]+".png";
			pCard->loadTexture(str.c_str());
		}
	}
}

string CardBaCay::findTypeCardByID(string card)
{
	if(card == "11"){
		card = "j";
	}
	else if(card=="1"){
		card = "a";
	}
	else if (card == "12"){
		card = "q";
	}
	else if (card ==  "13"){
		card = "k";
	}
	return card;
}

void CardBaCay::createCardBack(int pos)
{
	switch(pos)
	{
	case kUserMe:
		createListCard_Back(CARD_ME, w_card_me, h_card_me, leftMe, bottomMe);
		break;
	case kUserLeft:
		createListCard_Back(CARD_LEFT, w_card_notme, h_card_notme, leftLeft, bottomLeft);
		break;
	case kUserRight:
		createListCard_Back(CARD_RIGHT, w_card_notme, h_card_notme, leftRight, bottomLeft);
		break;
	case kUserTop:
		createListCard_Back(CARD_TOP, w_card_notme, h_card_notme, leftTop, bottomTop);
		break;
	}
}

void CardBaCay::createListCard_Back(CCArray *P, float _width, float _height, float _left, float _bottom)
{
	for (int i = 0; i < 3; i++)
	{
		CardChan *pCard = CardChan::create();
		pCard->loadTexture("card_back.png");
		pCard->setPosition(ccp(_left + i * _width, _bottom));
		pCard->setSizeCard(_width, _height);
		P->addObject(pCard);
		this->addChild(pCard);
	}
}

void CardBaCay::deleteAllCards_FromArray(CCArray *P)
{
	while(P->count() > 0)
	{
		CardChan *pCard = (CardChan*)P->lastObject();
		P->removeLastObject();
		pCard->removeFromParentAndCleanup(true);
	}
}


int CardBaCay::getPosUserByName(string pName)
{
	if (listUser == "")
	{
		return -1;
	}

	int vt = -1;
	vector<string> list = mUtils::splitString(listUser,';');
	for (int i = 0; i < list.size(); i++)
	{
		vector<string> info = mUtils::splitString(list[i],'|');
		if (strcmp(myName.c_str(), info[0].c_str()) == 0)
		{
			vt = i;
			break;
		}
	}

	int countuser = (int)list.size();

	CCLOG("count user = %d",countuser);
	CCLOG("vt = %d",vt);

	if (vt != -1)
	{
		for (int k = 0; k < countuser; k++)
		{
			if(strcmp(list[k].c_str(), "") == 0)
				continue;
			string player = list[k];
			vector<string> n = mUtils::splitString(player, '|');

			if(strcmp(n[0].c_str(), pName.c_str()) == 0){

				if(k == vt){
					return kUserMe;
				}
				else if(k == (vt + 1) % 4){
					return kUserRight;
				}
				else if(k == (vt + 2) % 4){
					return kUserTop;
				}
				else if(k == (vt + 3) % 4){
					return kUserLeft;
				}
				break;
			}
		}
	}
	else
		return -1;
}

void CardBaCay::setCallbackFunc(CCObject* target, SEL_CallFuncN callfun)
{
	m_callback = target;
	m_callbackListener = callfun;
}

CCArray* CardBaCay::getListCards_Me()
{
	return CARD_ME;
}

CCArray* CardBaCay::getListCards_Left()
{
	return CARD_LEFT;
}

CCArray* CardBaCay::getListCards_Right()
{
	return CARD_RIGHT;
}

CCArray* CardBaCay::getListCards_Top()
{
	return CARD_TOP;
}