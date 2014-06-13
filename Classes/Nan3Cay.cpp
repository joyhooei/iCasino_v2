#include "Nan3Cay.h"
#include <algorithm>

Nan3Cay::Nan3Cay():m_callback(NULL)
	,m_callbackListener(NULL)
{

}

Nan3Cay::Nan3Cay( CCObject *pSender )
{

}


Nan3Cay::~Nan3Cay(){

}

bool Nan3Cay::init(){
	if (!CCLayer::init())
	{
		return false;
	}

	CCLOG("Init layer nan ba cay");
	arrCardTypes[0] = "s";
	arrCardTypes[1] = "c";
	arrCardTypes[2] = "h";
	arrCardTypes[3] = "d";

	dx = 0;
	dy = 0;
	_index = -1;
	_where = -1;
	isTouched = false;

	deltaX = 0;
	deltaY = 0;
	sX = 0;
	sY = 0;
	xcu = 0;
	ycu = 0;

	cardIndex = 2;

	//Touch move
	cardIndex_under = 0;
	flag_move = false;
	flag_left = flag_right = -1;
	count_move = 0;

	//touch end
	vt = -1;

	this->sizeScreen = CCDirector::sharedDirector()->getVisibleSize();
	float scaleX = sizeScreen.width / WIDTH_DESIGN;
	float scaleY = sizeScreen.height / HEIGHT_DESIGN;
	float scaleMin = (scaleX < scaleY) ? scaleX : scaleY;
	scaleApp = scaleMin;

	bottomCard = 68;
	leftCard = 267;
	rightCard = 267;

	widthCard = 267;
	heightCard = 344;

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));
	this->setTouchEnabled(true);

	cardOnhand = new CCArray();
	cardOnhand->retain();

	btnBack = UIButton::create();
	btnBack->loadTextures("ready.png", "ready_selected.png", "");
	btnBack->setTitleText("Thoát");
	btnBack->setAnchorPoint(ccp(0,0));
	btnBack->setPosition(ccp(WIDTH_DESIGN-btnBack->getContentSize().width-20,10));
	btnBack->setTouchEnabled(false);
	btnBack->addTouchEventListener(this, toucheventselector(Nan3Cay::btnBack_click));
	btnBack->setTitleFontSize(20);
	btnBack->setTitleColor(ccRED);

	CCLOG("Jumphere");
	return true;
}


void Nan3Cay::initListCardHand(string lsCards){
	vector<string> arr = Dsplit(lsCards,'-');
	for (int i=0; i<arr.size(); i++)
	{
		vector<string> info = Dsplit(arr[i],'_');
		CardChan *pCard = CardChan::create();
		string t = "Nan3Cay/card_"+findTypeCard(info[0])+"_"+arrCardTypes[atoi(info[1].c_str())]+".png";
		pCard->loadTexture(t.c_str());
		pCard->setSizeCard(widthCard,heightCard);
		pCard->setPosition(ccp(leftCard,bottomCard));
		pCard->setZOrder(i+1);
		cardOnhand->addObject(pCard);
		this->addChild(pCard);
	}

	if(cardOnhand->count()==0)
		return;
	cardIndex = (int)cardOnhand->count() - 1;
}

void Nan3Cay::setCallbackFunc(CCObject* target, SEL_CallFuncN callfun){
	m_callback = target;
	m_callbackListener = callfun;
}

void Nan3Cay::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	CCSetIterator iterator = pTouches->begin();
	CCTouch *touch;
	touch = (CCTouch*)(*iterator);
	CCPoint tap;
	tap = touch->getLocation();
	this->pointTouchBegan = touch->getLocation();
	disTouchBegan.setSize(0,0);

	//Execute
	if (tap.x > leftCard && tap.x < leftCard + widthCard &&
		tap.y > bottomCard && tap.y < bottomCard + heightCard)
	{
		isTouched = true;
		dx = tap.x - leftCard;
		dy = tap.y - bottomCard;
		_index = 7;

		sX = tap.x;
		sY = tap.y;

		xcu = tap.x;
		ycu = tap.y;

		disTouchBegan.setSize(tap.x - leftCard, tap.y - bottomCard);
	}
}

void Nan3Cay::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	CCSetIterator iterator;
	CCTouch *touch;
	CCPoint tap;

	iterator = pTouches->begin();
	touch = (CCTouch*)(*iterator);
	tap = touch->getLocation();

	 if (isTouched)
	 {
		 deltaX = sX - tap.x;
		 deltaY = sY - tap.y;
		 sX = tap.x;
		 sY = tap.y;

		 if(deltaX > 0 && tap.x < xcu){
			 count_move++;
			 if (count_move == 1){
				 flag_left = 0;
			 }else{
				count_move++;
			 }
		 }

		 if (deltaX < 0 && tap.x > xcu)
		 {
			 count_move--;
			 if (count_move == -1)
			 {
				 flag_right = 0;
			 }
			 else
			 {
				count_move++;
			 }
		 }

		 tap.x -= disTouchBegan.width;
		 tap.y -= disTouchBegan.height;

		 if (flag_left == 0)
		 {
			 CardChan *pCard = (CardChan*)cardOnhand->objectAtIndex(cardIndex);
			 pCard->setPosition(tap);
		 }
		 
		 if (flag_right == 0)
		 {
			 CardChan *pCard = (CardChan*)cardOnhand->objectAtIndex(cardIndex_under);
			 pCard->setPosition(tap);
		 }

	 }
}

void Nan3Cay::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){

	if (flag_left == 0)
	{
		vt = cardIndex;
	}
	else if (flag_right == 0)
	{
		vt = cardIndex_under;
	}

	if (isTouched)
	{
		if (vt == -1)
		{
			return;
		}
		CardChan *pCard = (CardChan*)cardOnhand->objectAtIndex(vt);
		if (pCard->getPositionX() <= (leftCard-widthCard) || pCard->getPositionX() >= (leftCard+widthCard) ||
			pCard->getPositionY() >= (bottomCard+heightCard))
		{
			if (flag_left == 0)
			{
				movePockerFinish(pCard,vt);
				cardIndex--;
			}
			if (flag_right == 0)
			{
				movePockerFinish(pCard,vt);
				cardIndex_under++;
			}
		}
		else
		{
			pCard->setPosition(ccp(leftCard,bottomCard));
		}

		//Reset Cac tay cam la bai

	}//end if touches
	isTouched = false;
	flag_left = flag_right = -1;
	count_move = 0;
	if (cardIndex == cardIndex_under)
	{
		CardChan *pCard = (CardChan*)cardOnhand->objectAtIndex(cardIndex);
		movePockerFinish(pCard,cardIndex);
		this->runAction(CCSequence::create(CCDelayTime::create(1),CCCallFunc::create(this, callfunc_selector(Nan3Cay::closeLayerNanBai)),NULL));
	}
}

//Di chuyển lá bài về vị trí khi đã nặn xong
void Nan3Cay::movePockerFinish(CardChan *pCard,int pos){
	float toX = -1;
	float toY = -1;
	toY = bottomCard;

	switch(pos){
	case 0:
		toX = leftCard + widthCard;
		break;
	case 1:
		toX = leftCard;
		break;
	case 2:
		toX = leftCard - widthCard;
		pCard->setZOrder(0);
		break;
	default:
		break;
	}

	CCMoveTo *pMoveBy = CCMoveTo::create(0.4,ccp(toX,toY));
	pCard->runAction(pMoveBy);
}

void Nan3Cay::closeLayerNanBai(){
	//callback

	CCLOG("Call back");
	if (m_callback && m_callbackListener)
	{
		(m_callback->*m_callbackListener)(this);
	}
	this->removeFromParentAndCleanup(true);
}

string Nan3Cay::findTypeCard(string card){
	if(card == "11"){
		card = "j";
	}
	else if(card == "1"){
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

vector<string> Nan3Cay::Dsplit(string &S,const char &str){
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

bool Nan3Cay::isTouch(CardChan *card, CCPoint tap){
	if (tap.x > card->getPositionX() && tap.x < card->getPositionX() + widthCard &&
		tap.y > card->getPositionY() && tap.y < card->getPositionY() + heightCard)
	{
		return true;
	}
	return false;
}

void Nan3Cay::btnBack_click(CCObject *psender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		CCLOG("Btn Back Click");
		this->removeFromParentAndCleanup(true);
	}
}