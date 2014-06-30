
//
//  _LayerCard_XiTo_.cpp
//  iCasinov2
//
//  Created by DauA on 6/28/14.
//
//

#include "_LayerCard_XiTo_.h"
#include "CardChan.h"
#include "mUtils.h"
#include "GameServer.h"

LayerCardXiTo::~LayerCardXiTo()
{
	arrCardTypes.clear();
	CARD_ME->release();
	CARD_LEFT_BOTTOM->release();
	CARD_LEFT_TOP->release();
	CARD_RIGHT_BOTTOM->release();
	CARD_RIGHT_TOP->release();
}

void LayerCardXiTo::onExit()
{
	arrCardTypes.clear();
	CARD_ME->release();
	CARD_LEFT_BOTTOM->release();
	CARD_LEFT_TOP->release();
	CARD_RIGHT_BOTTOM->release();
	CARD_RIGHT_TOP->release();
}

bool LayerCardXiTo::init()
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

string LayerCardXiTo::convertCard(string strCard)
{
	vector<string> arrCards = mUtils::splitString(strCard,',');
	string str = "";

	for(int i = 0; i < arrCards.size(); i++){
		if(arrCards[i] != ""){
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
					cardId += boost::to_string(num);
				}

				if(num == 14){
					num = 1;
					cardId = "a";
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

string LayerCardXiTo::findTypeCard(string listCards)
{
	vector<string> info = mUtils::splitString(listCards, '_');
	string url = "card_" + info[0] + "_" + arrCardTypes[atoi(info[1].c_str())] + ".png";
	return url;
}

void LayerCardXiTo::initGame()
{
	listUser = "";

	count_give = 0;

	bt_card_me = 87;
	bt_card_bottom = 211;
	bt_card_top = 350;

	lf_card_me = 280;
	lf_card_left_bottom = 113;
	lf_card_left_top = 178;
	lf_card_right_bottom = 507;
	lf_card_right_top = 447;

	w_card_me = 67;
	h_card_me = 87;
	w_card_notme = 48;
	h_card_notme = 62;

	arrCardTypes.push_back("h");
	arrCardTypes.push_back("s");
	arrCardTypes.push_back("c");
	arrCardTypes.push_back("d");

	CARD_ME = CCArray::create();
	CARD_LEFT_BOTTOM = CCArray::create();
	CARD_LEFT_TOP = CCArray::create();
	CARD_RIGHT_BOTTOM = CCArray::create();
	CARD_RIGHT_TOP = CCArray::create();

	CARD_ME->retain();
	CARD_LEFT_BOTTOM->retain();
	CARD_LEFT_TOP->retain();
	CARD_RIGHT_BOTTOM->retain();
	CARD_RIGHT_TOP->retain();
}

void LayerCardXiTo::resetGame()
{
	count_give = 0;
	deleteAllCard_FromArray(CARD_ME);
	deleteAllCard_FromArray(CARD_RIGHT_BOTTOM);
	deleteAllCard_FromArray(CARD_RIGHT_TOP);
	deleteAllCard_FromArray(CARD_LEFT_BOTTOM);
	deleteAllCard_FromArray(CARD_LEFT_TOP);
}

void LayerCardXiTo::givePocker()
{
	vector<string> realUser = mUtils::splitString(listUser,';');
	string listUser_vitural = listUser;
	listUser_vitural += ";" + listUser;

	vector<string> data = mUtils::splitString(listUser_vitural, ';');
	int num = (int)data.size();

	vector<string> info = mUtils::splitString(data[count_give], '_');
	if (strcmp(info[1].c_str(), myName.c_str()) == 0)
	{
		giveDeal(CARD_ME, w_card_me, h_card_me, lf_card_me, bt_card_me, num);
	}
	else
	{
		switch(getPosUserByName(info[1]))
		{
		case user_leftTop:
			giveDeal(CARD_LEFT_TOP, w_card_notme, h_card_notme, lf_card_left_top, bt_card_top, num);
			break;
		case user_leftBottom:
			giveDeal(CARD_LEFT_BOTTOM, w_card_notme, h_card_notme, lf_card_left_bottom, bt_card_bottom, num);
			break;
		case user_rightTop:
			giveDeal(CARD_RIGHT_TOP, w_card_notme, h_card_notme, lf_card_right_top, bt_card_top, num);
			break;
		case user_rightBottom:
			giveDeal(CARD_RIGHT_BOTTOM, w_card_notme, h_card_notme, lf_card_right_bottom, bt_card_bottom, num);
			break;
		default:
			break;
		}
	}
}

void LayerCardXiTo::giveDeal(CCArray *P, float _width, float _height, float _left, float _bottom, int num)
{
	count_give++;
	CardChan *pCard = CardChan::create();
	pCard->loadTexture("card_back.png");
	pCard->setSizeCard(w_card_notme, h_card_notme);
	pCard->setPosition(ccp(WIDTH_DESIGN / 2 - w_card_notme / 2, HEIGHT_DESIGN - h_card_notme));
	this->addChild(pCard);

	CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(_left+P->count()*_width,_bottom));
	CCScaleBy *scaleTo = CCScaleBy::create(0.3, _width/w_card_notme,_height/h_card_notme);
	pCard->runAction(newTo);
	pCard->runAction(scaleTo);
	P->addObject(pCard);
	CCLOG("Card me: %d",CARD_ME->count());

	if (count_give < num)
	{
		this->runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(LayerCardXiTo::givePocker)),NULL));
	}
	else
	{
		vector<string> deal = mUtils::splitString(myListCards, ',');
		string strDeal = convertCard(myListCards);
		vector<string> arr = mUtils::splitString(strDeal, '-');
		for(int i = 0; i < arr.size(); i++){
			CardChan *pXiTo = (CardChan*)CARD_ME->objectAtIndex(i);
			pXiTo->loadTexture(findTypeCard(arr[i]).c_str());
			pXiTo->setID(atoi(deal[i].c_str()));
		}

		CCLOG("Call back");
		if (m_callback && m_callbackListener)
		{
			(m_callback->*m_callbackListener)(this);
		}
	}
}

void LayerCardXiTo::givePocker_next()
{

}

void LayerCardXiTo::setMyName(string myname)
{
	this->myName = myname;
}

void LayerCardXiTo::setListUser(string listusers)
{
	this->listUser = listusers;
}

void LayerCardXiTo::setMyListCard(string listcards)
{
	this->myListCards = listcards;
}

int LayerCardXiTo::getPosUserByName(string uid)
{
	if (listUser == "")
	{
		return -1;
	}
	int vt = -1;
	vector<string> list = mUtils::splitString(listUser, ';');

	for(int i = 0; i < list.size(); i++){
		string _id = mUtils::splitString(list[i], '_')[1];
		if(strcmp(_id.c_str(), myName.c_str())==0){
			vt = i;
			break;
		}
	}

	for(int k = 0; k < list.size(); k++){
		if(strcmp(list[k].c_str(), "") == 0){
			continue;
		}
		string player = list[k];
		vector<string> n = mUtils::splitString(player, '_');
		if(strcmp(n[1].c_str(), uid.c_str())==0){
			if(k==vt){
				return 0;
			}
			else if(k == (vt + 1) % 5){
				return user_rightBottom;
			}
			else if(k == (vt + 2) % 5){
				return user_rightTop;
			}
			else if(k == (vt + 3) % 5){
				return user_leftTop;
			}
			else if(k == ( vt + 4) % 5){
				return user_leftBottom;
			}
		}
	}
	return -1;
}

void LayerCardXiTo::deleteAllCard_FromArray(CCArray *P)
{
	while(P->count() > 0)
	{
		CardChan *pCard = (CardChan*)P->lastObject();
		P->removeLastObject();
		pCard->removeFromParentAndCleanup(true);
	}
}

void LayerCardXiTo::setCallbackFunc(CCObject* target, SEL_CallFuncN callfun)
{
	m_callback = target;
	m_callbackListener = callfun;
}