//
//  _CardBaCay_.cpp
//  iCasino_v2
//
//  Created by DauA on 6/24/14.
//
//

#include "_CardBaCay_.h"
#include "mUtils.h"
#include "SimpleAudioEngine.h"
#include "_Card_.h"
#include "GameServer.h"
#include "LayerAvatar_BaCay.h"
#include "SceneManager.h"
CardBaCay::~CardBaCay()
{
	
    
    CARD_0->release();
	CARD_1->release();
	CARD_2->release();
	CARD_3->release();
    CARD_4->release();
	CARD_5->release();
	CARD_6->release();
	
	this->removeAllChildren();
	CCLOG("Deconstructor Layer Cards Ba Cay");
}

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
	
    
    CARD_0->release();
	CARD_1->release();
	CARD_2->release();
	CARD_3->release();
    CARD_4->release();
	CARD_5->release();
	CARD_6->release();
	if(m_callback)
	{
		m_callback = NULL;
	}
	
	this->removeAllChildren();
	CCLOG("Deconstructor Layer Cards Ba Cay");
}

void CardBaCay::initGame()
{

    
    ///
    CARD_0 = CCArray::create();
	CARD_1 = CCArray::create();
	CARD_2 = CCArray::create();
	CARD_3 = CCArray::create();
    CARD_4 = CCArray::create();
	CARD_5 = CCArray::create();
	CARD_6 = CCArray::create();
    ///
    CARD_0->retain();
	CARD_1->retain();
	CARD_2->retain();
	CARD_3->retain();
    CARD_4->retain();
	CARD_5->retain();
	CARD_6->retain();
    //

	arrCardTypes.push_back("s");
	arrCardTypes.push_back("c");
	arrCardTypes.push_back("h");
	arrCardTypes.push_back("d");

	myListCards = "";
	listUser = "";
	myName = "";


    //
    xCardPos_me=370;
    yCardPos_me=175;
    xCardPos_u1=140;
    yCardPos_u1=205;
    xCardPos_u2=140;
    yCardPos_u2=302;
    xCardPos_u3=264;
    yCardPos_u3=345;
    xCardPos_u4=492;
    yCardPos_u4=345;
    xCardPos_u5=610;
    yCardPos_u5=302;
    xCardPos_u6=605;
    yCardPos_u6=205;
	
	w_card_me = 50;
	w_card_notme = 30;
	h_card_me = 50 * 1.3;
	h_card_notme = 30 * 1.3;

	count_give = 0;

	m_callback = NULL;
	m_callbackListener = NULL;
}

void CardBaCay::resetGame()
{
	count_give = 0;

    
    deleteAllCards_FromArray(CARD_0);
	deleteAllCards_FromArray(CARD_1);
	deleteAllCards_FromArray(CARD_2);
	deleteAllCards_FromArray(CARD_3);
    deleteAllCards_FromArray(CARD_4);
	deleteAllCards_FromArray(CARD_5);
	deleteAllCards_FromArray(CARD_6);

}

void CardBaCay::setListUser(string listuser)
{
	this->listUser = listuser;
}

void CardBaCay::setMyName(string name)
{
	this->myName = name;
}

void CardBaCay::playSound(string pathSound)
{
    if(mUtils::isSoundOn())
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pathSound.c_str());
}

void CardBaCay::givePocker()
{
	playSound("sounds/deal_card.mp3");
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
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
		give_next(CARD_0, w_card_me, h_card_me, xCardPos_me, yCardPos_me, count_vir);
	}
	else
	{
		switch(getPosUserByName(info[0]))
		{
		case kuser1:
			give_next(CARD_1, w_card_notme, h_card_notme, xCardPos_u1, yCardPos_u1, count_vir);
			break;
		case kuser2:
			give_next(CARD_2, w_card_notme, h_card_notme, xCardPos_u2, yCardPos_u2, count_vir);
			break;
		case kuser3:
			give_next(CARD_3, w_card_notme, h_card_notme, xCardPos_u3, yCardPos_u3, count_vir);
			break;
        case kuser4:
            give_next(CARD_4, w_card_notme, h_card_notme, xCardPos_u4, yCardPos_u4, count_vir);
            break;
        case kuser5:
            give_next(CARD_5, w_card_notme, h_card_notme, xCardPos_u5, yCardPos_u5, count_vir);
            break;
        case kuser6:
            give_next(CARD_6, w_card_notme, h_card_notme, xCardPos_u6, yCardPos_u6, count_vir);
            break;
		case kuser0:
			if(isSpect())
			give_next(CARD_0, w_card_notme, h_card_notme, xCardPos_me, yCardPos_me, count_vir);
			break;
		default:
			break;
		}
	}
}


void CardBaCay::give_next(CCArray *P, float _width, float _height, float _left, float _bottom, int count)
{
	count_give++;

	Card *card = new Card("card_back.png");
    
	card->setPosition(ccp(WIDTH_DESIGN / 2 - w_card_notme / 2, HEIGHT_DESIGN / 2 - h_card_notme / 2));
	card->setScaleCard(w_card_notme / card->getContentSize().width, h_card_notme / card->getContentSize().height);
	card->setVisible(true);
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
	switch(pos)
	{
	case kuser0:
		turnUpAllCards_Pos(lc, CARD_0, w_card_me, h_card_me, xCardPos_me, yCardPos_me);
		break;
    case kuser1:
        turnUpAllCards_Pos(lc, CARD_1, w_card_notme, h_card_notme, xCardPos_u1, yCardPos_u1);
        break;
    case kuser2:
        turnUpAllCards_Pos(lc, CARD_2, w_card_notme, h_card_notme, xCardPos_u2, yCardPos_u2);
        break;
    case kuser3:
        turnUpAllCards_Pos(lc, CARD_3, w_card_notme, h_card_notme, xCardPos_u3, yCardPos_u3);
        break;
    case kuser4:
        turnUpAllCards_Pos(lc, CARD_4, w_card_notme, h_card_notme, xCardPos_u4, yCardPos_u4);
        break;
    case kuser5:
        turnUpAllCards_Pos(lc, CARD_5, w_card_notme, h_card_notme, xCardPos_u5, yCardPos_u5);
        break;
    case kuser6:
        turnUpAllCards_Pos(lc, CARD_6, w_card_notme, h_card_notme, xCardPos_u6, yCardPos_u6);
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
		Card *pCard = (Card*)P->objectAtIndex(i);

		if (strcmp(arrCards[i].c_str(),"0_0") == 0)
		{
			pCard->initWithFile("card_back.png");
		}
		else
		{
			vector<string> info = mUtils::splitString(arrCards[i],'_');
			string str = "card_" + findTypeCardByID(info[0]) + "_" + arrCardTypes[atoi(info[1].c_str())] + ".png";
			pCard->initWithFile(str.c_str());
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
	case kuser0:
		createListCard_Back(CARD_0, w_card_me, h_card_me, xCardPos_me, yCardPos_me);
		break;
	case kuser1:
		createListCard_Back(CARD_1, w_card_notme, h_card_notme, xCardPos_u1, yCardPos_u1);
		break;
    case kuser2:
        createListCard_Back(CARD_1, w_card_notme, h_card_notme, xCardPos_u2, yCardPos_u2);
        break;
    case kuser3:
        createListCard_Back(CARD_1, w_card_notme, h_card_notme, xCardPos_u3, yCardPos_u3);
        break;
    case kuser4:
        createListCard_Back(CARD_1, w_card_notme, h_card_notme, xCardPos_u4, yCardPos_u4);
        break;
    case kuser5:
        createListCard_Back(CARD_1, w_card_notme, h_card_notme, xCardPos_u5, yCardPos_u5);
        break;
    case kuser6:
        createListCard_Back(CARD_1, w_card_notme, h_card_notme, xCardPos_u6, yCardPos_u6);
        break;
   
	}
}

void CardBaCay::createListCard_Back(CCArray *P, float _width, float _height, float _left, float _bottom)
{
	for (int i = 0; i < 3; i++)
	{
		Card *pCard = new Card("card_back.png");
		pCard->setScaleCard(_width / pCard->getContentSize().width, _height / pCard->getContentSize().height);
		pCard->setPosition(ccp(_left + i * _width, _bottom));
		pCard->setVisible(true);

		P->addObject(pCard);
		this->addChild(pCard);
	}
}

void CardBaCay::deleteAllCards_FromArray(CCArray *P)
{
	while(P->count() > 0)
	{
		Card *pCard = (Card *)P->lastObject();
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
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	vector<string> list = mUtils::splitString(listUser,';');
	for (int i = 0; i < list.size(); i++)
	{
		vector<string> info = mUtils::splitString(list[i],'|');
		if (strcmp(myName.c_str(), info[0].c_str()) == 0 || isSpect())
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
					return kuser0;
				}
				else if(k == (vt + 1) % 7){
					return kuser1;
				}
				else if(k == (vt + 2) % 7){
					return kuser2;
				}
				else if(k == (vt + 3) % 7){
					return kuser3;
				}
                else if(k == (vt + 4) % 7){
					return kuser4;
				}
                else if(k == (vt + 5) % 7){
					return kuser5;
				}
                else if(k == (vt + 6) % 7){
					return kuser6;
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

CCArray* CardBaCay::getListCards_0()
{
	return CARD_0;
}
CCArray* CardBaCay::getListCards_1()
{
	return CARD_1;
}
CCArray* CardBaCay::getListCards_2()
{
	return CARD_2;
}
CCArray* CardBaCay::getListCards_3()
{
	return CARD_3;
}
CCArray* CardBaCay::getListCards_4()
{
	return CARD_4;
}
CCArray* CardBaCay::getListCards_5()
{
	return CARD_5;
}
CCArray* CardBaCay::getListCards_6()
{
	return CARD_6;
}
bool CardBaCay::isSpect() {
	vector<string> arr = mUtils::splitString(this->listUser, ';');
	int size = arr.size();
	for (int i = 0; i < size; i++){
		vector<string> arrInfo = mUtils::splitString(arr.at(i), '|');
		if (arrInfo.size() < 2) continue;
		string ai = arrInfo.at(0);
		if (ai == SceneManager::getSingleton().getMyName())
             return false;
	}
	return true;
}
