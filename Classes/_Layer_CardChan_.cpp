
#include "_Layer_CardChan_.h"
#include "mUtils.h"
#include "AllData.h"
#include "GameServer.h"
#include "_Chat_.h"
#include "Requests/ExtensionRequest.h"
#include "SimpleAudioEngine.h"

#define PI 3.141592653589
#define kTag_buttonNoc 123
#define kTag_layerGive 124

using namespace Sfs2X;

_Layer_CardChan_::_Layer_CardChan_(){

}
_Layer_CardChan_::~_Layer_CardChan_()
{
	CARD_ME->removeAllObjects();
	CARD_ME->release();

	CARD_D_ME_top->removeAllObjects();
	CARD_D_ME_top->release();

	CARD_C_ME->removeAllObjects();
	CARD_C_ME->release();

	CARD_D_LEFT_top->removeAllObjects();
	CARD_D_LEFT_top->release();

	CARD_C_LEFT->removeAllObjects();
	CARD_C_LEFT->release();

	CARD_D_RIGHT_top->removeAllObjects();
	CARD_D_RIGHT_top->release();

	CARD_C_RIGHT->removeAllObjects();
	CARD_C_RIGHT->release();

	CARD_D_TOP_top->removeAllObjects();
	CARD_D_TOP_top->release();

	CARD_C_TOP->removeAllObjects();
	CARD_C_TOP->release();

	CARD_D_ME_bottom->removeAllObjects();
	CARD_D_ME_bottom->release();

	CARD_D_LEFT_bottom->removeAllObjects();
	CARD_D_LEFT_bottom->release();

	CARD_D_RIGHT_bottom->removeAllObjects();
	CARD_D_RIGHT_bottom->release();

	CARD_D_TOP_bottom->removeAllObjects();
	CARD_D_TOP_bottom->release();

	ALL_CARDS->removeAllObjects();
	ALL_CARDS->release();

	CARD_RESUITL->removeAllObjects();
	CARD_RESUITL->release();

	CARD_NOC->removeAllObjects();
	CARD_NOC->release();
	CCLOG("Layer card Chan Deconstructor !");
}

bool _Layer_CardChan_::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));
	this->setTouchEnabled(false);

	isGuess = false;

	this->sizeScreen = CCDirector::sharedDirector()->getVisibleSize();
	float scaleX = sizeScreen.width / WIDTH_DESIGN;
	float scaleY = sizeScreen.height / HEIGHT_DESIGN;
	float scaleMin = (scaleX < scaleY) ? scaleX : scaleY;
	scaleApp = scaleMin;

	startLeft = (sizeScreen.width - WIDTH_DESIGN) / 2;
	startTop = (sizeScreen.height - HEIGHT_DESIGN) / 2;

	// Cards
	uLayer = UILayer::create();
	uLayer->setAnchorPoint(ccp(0, 0));
	uLayer->setPosition(ccp(0, 0));
	this->addChild(uLayer);

	dianoc = UIButton::create();
	dianoc->loadTextures("dia_noc.png","dia_noc.png","");
	dianoc->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2 + 32.5));
	dianoc->setEnabled(false);
	uLayer->addWidget(dianoc);

	UIImageView *img = UIImageView::create();
	img->loadTexture("back_chan1.png");
	img->setPosition(ccp(20, 10));
	dianoc->addChild(img);

	countNoc = UILabel::create();
	countNoc->setText("");
	countNoc->setFontSize(17);
	countNoc->setColor(ccYELLOW);
	countNoc->setPosition(ccp(10, 20));
	img->addChild(countNoc);

	w_cardhand = 34;
	h_cardhand = 125;
	w_card = 25;
	h_card = 98;
	goc = float(250/19);
	_coutZorder = 0;
	list_noc = "";

	// Vi tri cac la bai cua tri
	left_chi_left = (123);
	left_chi_right = (680);
	left_chi_me = (510 + w_card * 2) + w_card / 2;
	left_chi_top = (365) - w_card;

	bottom_chi_left = 206;
	bottom_chi_right = 237;
	bottom_chi_me = 95;
	bottom_chi_top = 320;

	//Vi tri cac la bai duoi tay
	left_d_me = 29;
	left_d_top = 464;
	left_d_left = 29;
	left_d_right = WIDTH_DESIGN - 29;

	bottom_d_me = 85;
	bottom_d_left = 360;
	bottom_d_right = 360;
	bottom_d_top = 382;

	//đếm số chíu của từng người chơi
	count_chiu_me = 0;
	count_chiu_left = 0;
	count_chiu_right = 0;
	count_chiu_top = 0;

	posCard_LeftX = 10 + w_card / 2;
	posCard_RightX = WIDTH_DESIGN - 10 - w_card / 2;
	posCard_TopX = WIDTH_DESIGN / 2;
	posCard_BottomX = WIDTH_DESIGN / 2;

	posCard_LeftY = HEIGHT_DESIGN / 2 - h_card / 2;
	posCard_RightY = posCard_LeftY;
	posCard_TopY = HEIGHT_DESIGN - h_card - 20;
	posCard_BottomY = 30;

	//Khoảng cách lá bài cửa trì
	kc_me = kc_left = kc_right = kc_top = w_card;

	//Drag drop cards of winner user !
	pos_Left = WIDTH_DESIGN / 2 - h_card - 20;
	pos_Right = WIDTH_DESIGN / 2 + h_card + 20;
	pos_Bottom = HEIGHT_DESIGN / 2 + 50 - h_card;
	pos_Top = HEIGHT_DESIGN / 2 + 55 + h_card;
	kc_TB = pos_Top - pos_Bottom;
	kc_RL = pos_Right - pos_Left;
	flag_DragDrop1 = false;
	flag_DragDrop1 = false;

	//All Cards
	ALL_CARDS = CCArray::create();
	ALL_CARDS->retain();
	createAllCards();

	CARD_ME = CCArray::create();
	CARD_ME->retain();

	CARD_C_ME = CCArray::create();
	CARD_C_ME->retain();

	CARD_C_LEFT = CCArray::create();
	CARD_C_LEFT->retain();

	CARD_C_RIGHT = CCArray::create();
	CARD_C_RIGHT->retain();

	CARD_C_TOP = CCArray::create();
	CARD_C_TOP->retain();

	CARD_D_ME_top = CCArray::create();
	CARD_D_ME_top->retain();

	CARD_D_LEFT_top = CCArray::create();
	CARD_D_LEFT_top->retain();

	CARD_D_RIGHT_top = CCArray::create();
	CARD_D_RIGHT_top->retain();

	CARD_D_TOP_top = CCArray::create();
	CARD_D_TOP_top->retain();

	CARD_D_ME_bottom = CCArray::create();
	CARD_D_ME_bottom->retain();

	CARD_D_LEFT_bottom = CCArray::create();
	CARD_D_LEFT_bottom->retain();

	CARD_D_RIGHT_bottom = CCArray::create();
	CARD_D_RIGHT_bottom->retain();

	CARD_D_TOP_bottom = CCArray::create();
	CARD_D_TOP_bottom->retain();

	CARD_RESUITL = CCArray::create();
	CARD_RESUITL->retain();

	CARD_NOC = CCArray::create();
	CARD_NOC->retain();

	layerCardResult = CCLayer::create();
	layerCardResult->setAnchorPoint(ccp(0,0));
	layerCardResult->setPosition(ccp(0,0));
	layerCardResult->setZOrder(0);
	this->addChild(layerCardResult);

	rLayer = UILayer::create();
	rLayer->setAnchorPoint(ccp(0,0));
	rLayer->setPosition(ccp(0,0));
	this->addChild(rLayer);

	//Button Xem noc
	UIButton *btn_XemNoc = UIButton::create();
	btn_XemNoc->setTag(kTag_buttonNoc);
	btn_XemNoc->loadTextures("dia_noc.png","dia_noc.png","");
	btn_XemNoc->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2 + 32.5));
	btn_XemNoc->setEnabled(false);
	btn_XemNoc->addTouchEventListener(this, toucheventselector(_Layer_CardChan_::btn_XemNoc_click));
	
	UIImageView *iconNoc = UIImageView::create();
	iconNoc->loadTexture("U.png");
	btn_XemNoc->addChild(iconNoc);

	UILabelBMFont *lbl = UILabelBMFont::create();
	lbl->setFntFile("tttt.fnt");
	lbl->setText("Nọc");
	lbl->setColor(ccRED);
	lbl->setScale(0.8);
	lbl->setPositionY(5);
	iconNoc->addChild(lbl);

	rLayer->addWidget(btn_XemNoc);

	CCLOG("Init success !");
	return true;
}

void _Layer_CardChan_::setIsGuess(bool _guess){
	this->isGuess = _guess;
}

bool _Layer_CardChan_::checkListCardsUser(int pos){
	switch(pos){
	case kUserBot:
		return checkCardInArray(CARD_C_ME, CARD_D_ME_bottom, CARD_D_ME_top);
	case kUserLeft:
		return checkCardInArray(CARD_C_LEFT, CARD_D_LEFT_bottom, CARD_D_LEFT_top);
	case kUserRight:
		return checkCardInArray(CARD_C_RIGHT, CARD_D_RIGHT_bottom, CARD_D_RIGHT_top);
	case kUserTop:
		return checkCardInArray(CARD_C_TOP, CARD_D_TOP_bottom, CARD_D_TOP_top);
	default:
		return false;
	}
	return false;
}

bool _Layer_CardChan_::checkCardInArray(CCArray *P1, CCArray *P2, CCArray *P3){
	if (P1->count() > 0 || P2->count() > 0 || P3->count() > 0)
	{
		return true;
	}
	return false;
}

void _Layer_CardChan_::createAllCards(){

	for(int i = 0; i < 130; i++)
	{
		CardChan *pCard = CardChan::create();
		pCard->setZOrder(i);
		pCard->loadTexture("3_2.png");
		pCard->setVisible(false);
		pCard->setRotation(0);
		pCard->setTouchEnabled(false);
		uLayer->addWidget(pCard);
		ALL_CARDS->addObject(pCard);
	}
}

void _Layer_CardChan_::resetAllCards(){
	this->setTouchEnabled(false);
	CCLOG("ALL_CARD %d",ALL_CARDS->count());
	for(int i = 0; i < (int)ALL_CARDS->count(); i++)
	{
		CardChan *pCard = (CardChan*)ALL_CARDS->objectAtIndex(i);
		pCard->setColor(ccc3(255,255,255));
		pCard->setVisible(false);
		pCard->setTouchEnabled(false);
		pCard->setRotation(0);
		pCard->setPos(-1);
		pCard->setZOrder(i);
	}
	_coutZorder = 0;
	count_chiu_me = count_chiu_left = count_chiu_right = count_chiu_top = 0;
	kc_top = kc_me = kc_right = kc_left = w_card;

	list_noc = "";

	removeAllCardFromArray(CARD_ME);

	removeAllCardFromArray(CARD_C_ME);
	removeAllCardFromArray(CARD_C_LEFT);
	removeAllCardFromArray(CARD_C_RIGHT);
	removeAllCardFromArray(CARD_C_TOP);

	removeAllCardFromArray(CARD_D_LEFT_bottom);
	removeAllCardFromArray(CARD_D_ME_bottom);
	removeAllCardFromArray(CARD_D_RIGHT_bottom);
	removeAllCardFromArray(CARD_D_TOP_bottom);

	removeAllCardFromArray(CARD_D_TOP_top);
	removeAllCardFromArray(CARD_D_RIGHT_top);
	removeAllCardFromArray(CARD_D_ME_top);
	removeAllCardFromArray(CARD_D_LEFT_top);

	removeAllCardFromArray(CARD_RESUITL);
	

	flag_DragDrop1 = false;
	flag_DragDrop2 = false;

	layerCardResult->removeAllChildrenWithCleanup(true);
	rLayer->getWidgetByTag(kTag_buttonNoc)->setEnabled(false);
	while(CARD_NOC->count() > 0){
		CardChan *cards = (CardChan*) CARD_NOC->lastObject();
		CARD_NOC->removeLastObject();
		rLayer->removeWidget(cards);
	}
	countNoc->setText("");
	dianoc->setEnabled(false);
}

void _Layer_CardChan_::createOrRestoreListCards(int pos, string listCards){
	if (!checkListCardsUser(pos))
	{
		switch(pos)
		{
			case kUserTop:
				createCards4Guess(CARD_C_TOP, CARD_D_TOP_top, CARD_D_TOP_bottom, listCards);
				break;
			case kUserBot:
				createCards4Guess(CARD_C_ME, CARD_D_ME_top, CARD_D_ME_bottom, listCards);
				break;
			case kUserLeft:
				createCards4Guess(CARD_C_LEFT, CARD_D_LEFT_top, CARD_D_LEFT_bottom, listCards);
				break;
			case kUserRight:
				createCards4Guess(CARD_C_RIGHT, CARD_D_RIGHT_top, CARD_D_RIGHT_bottom, listCards);
				break;
		}
	}
}

void _Layer_CardChan_::createCards4Guess(CCArray *P_Chi, CCArray *P_D_Top, CCArray *P_D_Bottom, string listCards){
	vector<string> arrList = mUtils::splitString(listCards, '/');
	for (int i = 0; i < arrList.size(); i++)
	{
	}
}

void _Layer_CardChan_::setMyListCards(string listCards){
	string card_Hand = mUtils::splitString(listCards, '/')[0];
	vector<string> list = mUtils::splitString(card_Hand, ';');

	int i = 0;
	int list_size = (int)list.size();

	float posx = ((WIDTH_DESIGN - (list_size * w_cardhand / 3)) / 2);

	while (i <= list.size()) {
		if (i < list.size()) {
			vector<string> info = mUtils::splitString(list[i], ':');
			CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
			pCard->setID(i);
			pCard->setNumber(atoi(info[1].c_str()));
			pCard->setSuite(atoi(info[2].c_str()));
			pCard->setFlag(false);
			pCard->loadTexture(findTypeCard(info[1], info[2]).c_str());
			pCard->setSizeCard(w_cardhand, h_cardhand);
			pCard->setPosition(ccp(400,120));
			float start = (list_size % 2 == 0) ? (float)list_size : (float)(list_size - 1);
			pCard->setTouchEnabled(true);
			pCard->setVisible(true);
			pCard->addTouchEventListener(this, toucheventselector(_Layer_CardChan_::CardTouch));
			CARD_ME->addObject(pCard);
			_coutZorder++;
			i++;
		}else{
			rotateListCards(CARD_ME);
			dianoc->setEnabled(true);
			break;
		}
	}//end while
}

void _Layer_CardChan_::rotateListCards(CCArray *P){
	CCObject *t;
	int dem = 0;
	float startX = (WIDTH_DESIGN - (P->count() * w_cardhand / 3)) / 2;
	float startAg =(float)(P->count() - 1);

	playSounds("Xoe.mp3");

	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);

		float xOld = card->getPositionX();
		float yOld = card->getPositionY();

		float _goc = -((startAg) / 2 * goc) + goc * dem;

		float xNew = xOld + sin(_goc * PI / 180) * h_cardhand/6;
		float yNew = yOld - (h_cardhand/6 - cos(_goc * PI / 180) * h_cardhand/6);

		CCActionInterval *moveTo = CCMoveTo::create(0.8, ccp(xNew, yNew));

		CCActionInterval *action = CCRotateBy::create(0.8, _goc);

		card->runAction(moveTo);
		card->runAction(action);
		dem++;
	}
}

void _Layer_CardChan_::refreshListCard(){
	CCLOG("refresh list cards");
	float countCard = (float)(CARD_ME->count() - 1);

	float start = (-countCard / 2) * goc;
	CCObject *t;
	int cou = 0;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard = dynamic_cast<CardChan*>(t);
		float xOld = 400;
		float yOld = 120;

		float rotate = start + cou * goc;
		float oldAngle = pCard->getRotation();

		float _newAngle = rotate;

		float xNew = xOld + sin(_newAngle * PI / 180) * h_cardhand / 6;
		float yNew = yOld - (h_cardhand / 6 - cos(_newAngle * PI / 180) * h_cardhand / 6);

		CCActionInterval *rr = CCRotateBy::create(0.4, rotate - oldAngle);
		CCActionInterval *mm = CCMoveTo::create(0.4, ccp(xNew, yNew));

		pCard->runAction(rr);
		pCard->runAction(mm);
		pCard->setFlag(false);

		cou++;
	}
}

void _Layer_CardChan_::sortMyListCards(string listCards){
	vector<string> list = mUtils::splitString(listCards, ';');
	if ((int)list.size() > (int)CARD_ME->count())
	{
		setMyListCards(listCards);
	}

	for(int i = 0; i < list.size(); i++){
		vector<string> info = mUtils::splitString(list[i], ':');
		CardChan* pCard = (CardChan*)CARD_ME->objectAtIndex(i);
		pCard->setNumber(atoi(info[1].c_str()));
		pCard->setSuite(atoi(info[2].c_str()));
		pCard->setFlag(false);
		pCard->loadTexture(findTypeCard(info[1], info[2]).c_str());
	}
}

void _Layer_CardChan_::CardTouch(CCObject *pSender,TouchEventType type){
	if (type == TOUCH_EVENT_ENDED) {
		CardChan *pChan = (CardChan*)pSender;
		CCObject *t;
		CCARRAY_FOREACH(CARD_ME, t){
			CardChan *pCard = dynamic_cast<CardChan*>(t);
			if (pCard->getNumber() == pChan->getNumber() && pCard->getSuite() == pChan->getSuite() && pCard->getID() == pChan->getID()) {

				if(!pCard->getFlag()){
					CCPoint p = pChan->getPosition();
					float rotate = pChan->getRotation();

					pCard->setPosition(ccp(p.x + 20 * sin((rotate * PI) / 180), p.y + 20 * cos((rotate * PI) / 180)));
					pCard->setFlag(true);
				}else{
					CCPoint p = pCard->getPosition();
					float rotate = pCard->getRotation();
					pCard->setPosition(ccp(p.x - 20 * sin((rotate * PI) / 180), p.y - 20 * cos((rotate * PI) / 180)));
					pCard->setFlag(false);
				}
			}
			else{
				if (pCard->getFlag())
				{
					CCPoint p = pCard->getPosition();
					float rotate = pCard->getRotation();
					pCard->setPosition(ccp(p.x - 20 * sin((rotate * PI) / 180), p.y - 20 * cos((rotate * PI) / 180)));
					pCard->setFlag(false);
				}
			}
		}
	}
}

void _Layer_CardChan_::CardResuiltMove(CCObject *pSender,TouchEventType type){
	if (type == TOUCH_EVENT_BEGAN)
	{
		CCLOG("touch start !");
	}
	else if(type == TOUCH_EVENT_MOVED)
	{
		CCLOG("touch move !");
	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		CCLOG("touch end !");
	}
}

void _Layer_CardChan_::resortCard_CuaTri_Alluser(int pos){
	switch(pos){
	case kUserMe:
		CCLOG("CARD_ME count %d", CARD_C_ME->count());
		if (CARD_C_ME->count() > 8)
		{
			kc_me = (w_card * 8) / (CARD_C_ME->count());
			animateCards(CARD_C_ME, left_chi_me, bottom_chi_me, kc_me);
		}
		break;
	case kUserLeft:
		if (CARD_C_LEFT->count() > 8)
		{
			kc_left = (w_card * 8) / (CARD_C_LEFT->count());
			animateCards(CARD_C_LEFT, left_chi_left, bottom_chi_left, kc_left);
		}
		break;
	case kUserRight:
		if (CARD_C_RIGHT->count() > 8)
		{
			kc_right = (w_card * 8) / (CARD_C_RIGHT->count());
			animateCards(CARD_C_RIGHT, left_chi_right, bottom_chi_right, -kc_right);
		}
		break;
	case kUserTop:
		if (CARD_C_TOP->count() > 8)
		{
			kc_top = (w_card * 8) / (CARD_C_TOP->count());
			animateCards(CARD_C_TOP, left_chi_top, bottom_chi_top,  -kc_top);
		}
		break;
	}
}

void _Layer_CardChan_::animateCards(CCArray *P, float _left, float _bottom, float _kc){
	if (P->count() == 0)
	{
		return;
	}

	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CCActionInterval *moveTo = CCMoveTo::create(0.5,ccp((_left + _kc * dem),_bottom));
		card->runAction(moveTo);
		dem++;
	}

	// sort zOrder
	for (int i = 0; i < P->count() - 1; i++)
	{
		for (int j = i + 1; j < P->count(); j++)
		{
			CardChan *iCard = (CardChan*)P->objectAtIndex(i);
			CardChan *jCard = (CardChan*)P->objectAtIndex(j);
			if (iCard->getZOrder() > jCard->getZOrder())
			{
				int temp = iCard->getZOrder();
				iCard->setZOrder(jCard->getZOrder());
				jCard->setZOrder(temp);
			}
		}
	}
}

string _Layer_CardChan_::findTypeCard(string number,string suite){
	string str = "";
	str += number + "_" + suite + ".png";
	return str;
}

string _Layer_CardChan_::getNameCard(int number, int suite){
	string str = "";
	//sui 2:sach 0:vạn 1 văn
	switch (number) {
	case 2:
		str += "Nhị";
		break;
	case 3:
		str += "Tam";
		break;
	case 4:
		str += "Tứ";
		break;
	case 5:
		str += "Ngũ";
		break;
	case 6:
		str += "Lục";
		break;
	case 7:
		str += "Thất";
		break;
	case 8:
		str += "Bát";
		break;
	case 9:
		str += "Cửu";
		break;
	default:

		str += "Chi";
		break;
	}

	switch (suite) {
	case 0:
		str+= " Vạn";
		break;
	case 1:
		str+= " Văn";
		break;
	case 2:
		str+= " Sách";
		break;
	default:
		str+= " Chi";
		break;
	}
	return str;
}

void _Layer_CardChan_::addCard_toCuaTri(CCNode* sender, void* data){
	int *f = (int*) data; 
	CardChan *pCard = (CardChan*) sender;

	switch(*f){
	case kUserMe:
		CARD_C_ME->addObject(pCard);
		resortCard_CuaTri_Alluser(kUserMe);
		break;
	case kUserBot:
		CARD_C_ME->addObject(pCard);
		resortCard_CuaTri_Alluser(kUserMe);
		break;
	case kUserLeft:
		CARD_C_LEFT->addObject(pCard);
		resortCard_CuaTri_Alluser(kUserLeft);
		break;
	case kUserRight:
		CARD_C_RIGHT->addObject(pCard);
		resortCard_CuaTri_Alluser(kUserRight);
		break;
	case kUserTop:
		CARD_C_TOP->addObject(pCard);
		resortCard_CuaTri_Alluser(kUserTop);
		break;
	}
}

void _Layer_CardChan_::addCard_toDuoiTay_top(CCNode *sender, void *data){
	int *f = (int*) data; 
	CardChan *fcard = (CardChan*) sender;
	switch(*f)
	{
	case kUserMe:
		fcard->setPos(CARD_D_ME_top->count());
		CARD_D_ME_top->addObject(fcard);
		swapZorder(CARD_D_ME_bottom, CARD_D_ME_top, count_chiu_me, false);
		break;
	case kUserLeft:
		fcard->setPos(CARD_D_LEFT_top->count());
		CARD_D_LEFT_top->addObject(fcard);
		swapZorder(CARD_D_LEFT_bottom, CARD_D_LEFT_top, count_chiu_left, false);
		break;
	case kUserRight:
		fcard->setPos(CARD_D_RIGHT_top->count());
		CARD_D_RIGHT_top->addObject(fcard);
		swapZorder(CARD_D_RIGHT_bottom, CARD_D_RIGHT_top, count_chiu_right, false);
		break;
	case kUserTop:
		fcard->setPos(CARD_D_TOP_top->count());
		CARD_D_TOP_top->addObject(fcard);
		swapZorder(CARD_D_TOP_bottom, CARD_D_TOP_top, count_chiu_top, false);
		break;
	default:
		break;
	}
}

void _Layer_CardChan_::swapZorder(CCArray* P1, CCArray* P2, int _count, bool _state){
	//D_Bottom vs D_top
	if (!_state)
	{
		if (P1->count() >= P2->count())
		{
			CardChan *pCard = (CardChan*)P2->objectAtIndex(P2->count() - 1);
			CardChan *qCard = (CardChan*)P1->objectAtIndex(P2->count() - 1);
			if (pCard->getZOrder() > qCard->getZOrder())
			{
				int _zorder = -1;
				_zorder = pCard->getZOrder();
				pCard->setZOrder(qCard->getZOrder());
				qCard->setZOrder(_zorder);
			}
		}
	}
	//D_Top vs D_Bottom
	else
	{
		if ((P1->count() - _count) <= P2->count())
		{
			CardChan *pCard = (CardChan*)P1->lastObject();
			CardChan *qCard = (CardChan*)P2->objectAtIndex(P1->count() - 1 - _count);
			if (pCard->getZOrder() < qCard->getZOrder())
			{
				int _zorder = -1;
				_zorder = pCard->getZOrder();
				pCard->setZOrder(qCard->getZOrder());
				qCard->setZOrder(_zorder);
			}
		}
	}
}

void _Layer_CardChan_::removeAllCardFromArray(CCArray *P){
	while(P->count() > 0){
		CardChan *pCard = (CardChan*)P->lastObject();
		P->removeLastObject();
	}
}

void _Layer_CardChan_::takeCards(int f_user, int t_user, string cardnu, string cardsu, int crdorg){
	switch(crdorg){
	case CARD_ORIGINATION_CHIA_BAI:
		break;
	case CARD_ORIGINATION_BOC_NOC:
		CCLOG("Bốc nọc");
		if (t_user == kUserMe)
		{
			refreshListCard();
		}
		action_BocNoc(t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_AN_CUA_TREN:
		CCLOG("Ăn cửa trên");
		playSounds("An.mp3");
		action_AnCuaTren(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_AN_CUA_TRI:
		playSounds("An.mp3");
		CCLOG("Ăn cửa trì");
		action_AnCuaTri(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_CHIU:
		CCLOG("Chíu");
		action_ChiuBai(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_TRA_CUA:
		CCLOG("Trả cửa");
		action_TraCua(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_BY_DISCARD:
		CCLOG("Đánh bài");
		playSounds("Danh.mp3");
		action_DanhBai(f_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_BY_DUOI:
		//playSounds("duoi.mp3");
		if(t_user == kUserMe){
			refreshListCard();
		}
		CCLOG("Dưới");
		break;
	case CARD_ORIGINATION_BY_TRANSFER_TREN_2_DUOI:
		CCLOG("Chuyển bài");
		action_ChuyenBai(f_user, t_user, cardnu, cardsu);
		break;
	case 10:
		action_An_U(f_user, t_user, cardnu, cardsu);
		break;
	default:
		break;
	}
}

void _Layer_CardChan_::action_BocNoc(int t_pos,string cardnu, string cardsu){
	CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setNumber(atoi(cardnu.c_str()));
	pCard->setSuite(atoi(cardsu.c_str()));
	pCard->setSizeCard(w_card, h_card);
	pCard->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2));
	pCard->setOpacity(200);
	pCard->setColor(ccc3(200,255,255));
	pCard->setVisible(true);

	float toX = -1;
	float toY = -1;
	int f = -1;
	int pos = t_pos;


	switch (pos) {
	case kUserMe:
		toX = left_chi_me + (float)CARD_C_ME->count() * kc_me;
		toY = bottom_chi_me;
		f = kUserMe;
		break;
	case kUserBot:
		toX = left_chi_me + (float)CARD_C_ME->count() * kc_me;
		toY = bottom_chi_me;
		f = kUserBot;
		break;
	case kUserLeft:
		toX = left_chi_left + (float)CARD_C_LEFT->count() * kc_left;
		toY = bottom_chi_left;
		f = kUserLeft;
		break;
	case kUserRight:
		toX = left_chi_right - (float)CARD_C_RIGHT->count() * kc_right;
		toY = bottom_chi_right;
		f = kUserRight;
		break;
	case kUserTop:
		toX = left_chi_top - (float)CARD_C_TOP->count() * kc_top;
		toY = bottom_chi_top;
		f = kUserTop;
		break;
	default:
		break;
	}

	playSounds("Boc.mp3");
	//Animation
	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(_Layer_CardChan_::addCard_toCuaTri),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	pCard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
}

void _Layer_CardChan_::action_AnCuaTren(int f_user, int t_user, string cardnu, string cardsu){
	CCLOG("Ăn cửa trên");
	float toX = -1;
	float toY = -1;
	int f = -1;

	CardChan* fcard = getCardFromPos_take(f_user);
	if (fcard == NULL) {
		return;
	}

	switch (t_user) {
	case kUserMe:
		toX = (float)CARD_D_ME_top->count() * w_card + left_d_me;
		toY = bottom_d_me;
		f = kUserMe;
		break;
	case kUserBot:
		toX = (float)CARD_D_ME_top->count() * w_card + left_d_me;
		toY = bottom_d_me;
		f = kUserMe;
		break;
	case kUserLeft:
		toX = (float)CARD_D_LEFT_top->count() * w_card + left_d_left;
		toY = bottom_d_left;
		f = kUserLeft;
		break;
	case kUserRight:
		toX = left_d_right - (float)CARD_D_RIGHT_top->count() * w_card;
		toY = bottom_d_right;
		f = kUserRight;
		break;
	case kUserTop:
		toX = (float)CARD_D_TOP_top->count() * w_card + left_d_top;
		toY = bottom_d_top;
		f = kUserTop;
		break;
	default:
		break;
	}

	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(_Layer_CardChan_::addCard_toDuoiTay_top),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	fcard->runAction(CCSequence::create(delay, moveTo, callfun, NULL));
}

void _Layer_CardChan_::action_AnCuaTri(int f_user, int t_user, string cardnu, string cardsu){
	CCLOG("Ăn cửa trì");
	action_AnCuaTren(f_user, f_user, cardnu, cardsu);
}

void _Layer_CardChan_::action_ChiuBai(int f_user, int t_user, string cardnu, string cardsu){
	int fpos = -1;
	int tpos = -1;
	fpos = f_user;
	tpos = t_user;
	CardChan *fcard = NULL;
	fcard = getCardFromPos_take(fpos);
	if (fcard == NULL)
	{
		return;
	}

	float toX = -1;
	float toY = -1;
	int f = -1;

	switch(tpos)
	{
	case kUserMe:
		toX = (float)CARD_D_ME_top->count() * w_card + left_d_me;
		toY = bottom_d_me;
		f = kUserMe;
		break;
	case kUserBot:
		toX = (float)CARD_D_ME_top->count() * w_card + left_d_me;
		toY = bottom_d_me;
		f = kUserMe;
		break;
	case kUserLeft:
		toX = (float)CARD_D_LEFT_top->count() * w_card + left_d_left;
		toY = bottom_d_left;
		f = kUserLeft;
		break;
	case kUserRight:
		toX = left_d_right - (float)CARD_D_RIGHT_top->count() * w_card;
		toY = bottom_d_right;
		f = kUserRight;
		break;
	case kUserTop:
		toX = (float)CARD_D_TOP_top->count() * w_card + left_d_top;
		toY = bottom_d_top;
		f = kUserTop;
		break;
	default:
		break;
	}

	//animation
	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(_Layer_CardChan_::addCard_toDuoiTay_top),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	fcard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
}

void _Layer_CardChan_::action_TraCua(int f_user, int t_user, string cardnu, string cardsu){
	CCLOG("Trả cửa");
	int fpos = -1;
	int tpos = -1;
	fpos = f_user;
	tpos = t_user;

	CCLOG("fpos = %d, tpos = %d", fpos, tpos);
	if(t_user == -1)
	{
		CCLOG("Mot nguoi boc, chiu xong danh vao cua tri cua minh");
		action_DanhBai(f_user, cardnu, cardsu);
	}

	else
	{
		if (f_user == kUserMe)
		{
			action_TraCua_ME(tpos, cardnu, cardsu);
		}
		else
		{
			action_TraCua_NOTME(fpos, tpos, cardnu, cardsu);
		}
	}
}

void _Layer_CardChan_::action_TraCua_ME(int tpos, string cardnu, string cardsu){
	CCLOG("Minh chiu xong va tra cua");
	CCObject *t;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard =  dynamic_cast<CardChan*>(t);
		if (pCard->getFlag() && pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())) {
			float rotate = -(pCard->getRotation());
			CCActionInterval *rotateTo = CCRotateBy::create(0.4, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.4, w_card / w_cardhand, h_card / h_cardhand);

			float toX = 0;
			float toY = 0;
			int f = -1;
			switch(tpos){
			case kUserMe:
				toX = (float)CARD_C_ME->count() * kc_me + left_chi_me;
				toY = bottom_chi_me;
				f = kUserMe;
				break;
			case kUserLeft:
				toX = (float)CARD_C_LEFT->count() * kc_left + left_chi_left;
				toY = bottom_chi_left;
				f = kUserLeft;
				break;
			case kUserRight:
				toX = left_chi_right - (float)CARD_C_RIGHT->count() * kc_right ;
				toY = bottom_chi_right;
				f = kUserRight;
				break;
			case kUserTop:
				toX = left_chi_top - (float)CARD_C_TOP->count() * kc_top;
				toY = bottom_chi_top;
				f = kUserTop;
				break;
			default:
				break;
			}
			CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));

			pCard->runAction(moveTo);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);
			CARD_ME->removeObject(pCard);

			switch(f){
			case kUserMe:
				CARD_C_ME->addObject(pCard);
				break;
			case kUserLeft:
				CARD_C_LEFT->addObject(pCard);
				break;
			case kUserRight:
				CARD_C_RIGHT->addObject(pCard);
				break;
			case kUserTop:
				CARD_C_TOP->addObject(pCard);
				break;
			}
			this->refreshListCard();
		}
	}
}

void _Layer_CardChan_::action_TraCua_NOTME(int fpos, int tpos, string cardnu, string cardsu){
	CCLOG("Nguoi khac tra cua: from %d, to %d",fpos,tpos);
	CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);
	pCard->setTouchEnabled(false);

	//Xác định vị trí lá bài được đánh ra
	switch (fpos) {
	case kUserBot:
		pCard->setPosition(ccp(posCard_BottomX, posCard_BottomY));
		break;
	case kUserLeft:
		pCard->setPosition(ccp(posCard_LeftX, posCard_LeftY));
		break;
	case kUserRight:
		pCard->setPosition(ccp(posCard_RightX, posCard_RightY));
		break;
	case kUserTop:
		pCard->setPosition(ccp(posCard_TopX, posCard_TopY));
		break;
	default:
		break;
	}

	pCard->setVisible(true);

	//di chuyen den:
	float toX = -1;
	float toY = -1;
	int f = -1;

	switch(tpos){
	case kUserMe:
		toX = (float)CARD_C_ME->count() * kc_me + left_chi_me;
		toY = bottom_chi_me;
		f = kUserMe;
		break;
	case kUserBot:
		toX = (float)CARD_C_ME->count() * kc_me + left_chi_me;
		toY = bottom_chi_me;
		f = kUserMe;
		break;
	case kUserLeft:
		toX = (float)CARD_C_LEFT->count() * kc_left + left_chi_left;
		toY = bottom_chi_left;
		f = kUserLeft;
		break;
	case kUserRight:
		toX = left_chi_right - (float)CARD_C_RIGHT->count() * kc_right ;
		toY = bottom_chi_right;
		f = kUserRight;
		break;
	case kUserTop:
		toX = left_chi_top - (float)CARD_C_TOP->count() * kc_top;
		toY = bottom_chi_top;
		f = kUserTop;
		break;
	default:
		break;
	}

	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(_Layer_CardChan_::addCard_toCuaTri),(void*)value);
	CCMoveTo *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	pCard->runAction(moveTo);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	pCard->runAction(CCSequence::create(delay, moveTo, callfun, NULL));
}

void _Layer_CardChan_::action_DanhBai(int f_user, string cardnu, string cardsu){
	CCLOG("Đánh bài");
	if (f_user == kUserMe) {
		action_DanhBai_ME(cardnu, cardsu);
	}
	else{
		action_DanhBai_NOTME(f_user, cardnu, cardsu);
	}
}

void _Layer_CardChan_::action_DanhBai_ME(string cardnu,string cardsu){
	CCLOG("Tôi đánh");
	int idCard = -1;
	bool _flag = false;
	for (int i = 0; i < CARD_ME->count(); i++)
	{
		CardChan *pCard = (CardChan *) CARD_ME->objectAtIndex(i);
		if (pCard->getFlag()){
			_flag = true;
			break;
		}
	}

	if (_flag == true)
	{
		for(int i = 0; i < CARD_ME->count(); i++){
			CardChan *pCard = (CardChan *) CARD_ME->objectAtIndex(i);
			if (pCard->getFlag() && pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str()))
			{
				idCard = pCard->getID();
				break;
			}
		}
	}
	else
	{
		for(int i = 0; i < CARD_ME->count(); i++){
			CardChan *pCard = (CardChan *) CARD_ME->objectAtIndex(i);
			if(pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())){
				idCard = pCard->getID();
				break;
			}
		}
	}

	CCLOG("idCards = %d", idCard);

	CCObject *t;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard =  dynamic_cast<CardChan*>(t);
		if (pCard->getID() == idCard) {
			float rotate = -(pCard->getRotation());
			CCActionInterval *rotateTo = CCRotateBy::create(0.3, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.3, w_card / w_cardhand, h_card / h_cardhand);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);
			CARD_ME->removeObject(pCard);
			//Animation
			CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp((float)CARD_C_ME->count() * kc_me + left_chi_me, bottom_chi_me));
			int *value = new int(kUserMe);
			CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(_Layer_CardChan_::addCard_toCuaTri),(void*)value);
			CCDelayTime *delay = CCDelayTime::create(0.3);
			pCard->runAction(CCSequence::create(delay, moveTo, callfun, NULL));
			this->refreshListCard();
		}
	}
}

void _Layer_CardChan_::action_DanhBai_NOTME(int pos,string cardnu,string cardsu){
	CCLOG("Người khác đánh bài");
	CardChan *pCard = (CardChan*)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);

	float toX = -1;
	float toY = -1;
	int f = -1;
	switch (pos) {
	case kUserBot:
		pCard->setPosition(ccp(posCard_BottomX, posCard_BottomY));
		toX = (float)CARD_C_ME->count() * kc_me + left_chi_me;
		toY = bottom_chi_me;
		f = kUserMe;
		break;
	case kUserLeft:
		pCard->setPosition(ccp(posCard_LeftX, posCard_LeftY));
		toX = (float)CARD_C_LEFT->count() * kc_left + left_chi_left;
		toY = bottom_chi_left;
		f = kUserLeft;
		break;
	case kUserRight:
		pCard->setPosition(ccp(posCard_RightX, posCard_RightY));
		toX = left_chi_right - (float)CARD_C_RIGHT->count() * kc_right;
		toY = bottom_chi_right;
		f = kUserRight;
		break;
	case kUserTop:
		pCard->setPosition(ccp(posCard_TopX, posCard_TopY));
		toX = left_chi_top - (float)CARD_C_TOP->count() * kc_top;
		toY = bottom_chi_top;
		f = kUserTop;
		break;
	default:
		break;
	}

	pCard->setVisible(true);
	//////////////////////////////////////////////////////////////////////////
	//Animation
	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(_Layer_CardChan_::addCard_toCuaTri),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	pCard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
}

void _Layer_CardChan_::action_ChuyenBai(int f_user, int t_user, string cardnu, string cardsu){
	CCLOG("Chuyển bài từ trên xuống dưới tay");
	CCLOG("from %d to %d",f_user, t_user);
	int pos = t_user;
	if( f_user != -1 && t_user != -1)
	{
		if (t_user == kUserMe) {
			action_ChuyenBai_ME(pos, cardnu, cardsu);
		}else{
			action_ChuyenBai_NOTME(pos, cardnu, cardsu);
		}
	}
	if (f_user == -1)
	{
		CCLOG("Chuyen bai khi chiu");
		action_ChuyenBai_Chiu(pos, cardnu, cardsu);
	}
}

void _Layer_CardChan_::action_ChuyenBai_ME(int pos, string cardnu, string cardsu){
	CCLOG("Chuyen bai tu bo bai xoe quat me");
	CCObject *t;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard =  dynamic_cast<CardChan*>(t);
		if (pCard->getFlag() && pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())) {

			float rotate = -(pCard->getRotation());
			int tmp = 0;
			tmp = count_chiu_me > 0 ? count_chiu_me - 1 : 0;
			pCard->setPos(CARD_D_ME_bottom->count() - tmp);
			CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp((CARD_D_ME_bottom->count() - tmp) * w_card + left_d_me, bottom_d_me - 25));
			CCActionInterval *rotateTo = CCRotateBy::create(0.4, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.4, w_card / w_cardhand,h_card / h_cardhand);

			CCLOG("zOrder card hand: %d",pCard->getZOrder());
			pCard->runAction(moveTo);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);
			pCard->setTouchEnabled(false);
			pCard->setZOrder(_coutZorder + 1);

			CARD_ME->removeObject(pCard);
			CARD_D_ME_bottom->addObject(pCard);
			this->refreshListCard();
		}
	}

}

void _Layer_CardChan_::action_ChuyenBai_NOTME(int pos, string cardnu, string cardsu){
	CCLOG("Chuyen bai tu tren tay xuong duoi tay binh thuong");
	CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);

	float toX = -1;
	float toY = -1;
	int f = -1;
	int tmp = 0;

	switch (pos) {
	case kUserBot:
		pCard->setPosition(ccp(posCard_BottomX, posCard_BottomY));
		tmp = count_chiu_me > 0 ? count_chiu_me - 1 : 0;
		pCard->setPos(CARD_D_ME_bottom->count() - tmp);
		toX = (CARD_D_ME_bottom->count() - tmp) * w_card + left_d_me;
		CCLog("D_ME_Bottom count = %d", CARD_D_ME_bottom->count());
		CCLog("Jumpe here bottom toX = %f", toX);
		toY = bottom_d_me - 25;
		f = kUserMe;
		break;
	case kUserLeft:
		pCard->setPosition(ccp(posCard_LeftX, posCard_LeftY));
		tmp = count_chiu_left > 0 ? count_chiu_left - 1 : 0;
		pCard->setPos(CARD_D_LEFT_bottom->count() - tmp);
		toX = (float)(CARD_D_LEFT_bottom->count() - tmp) * w_card + left_d_left;
		toY = bottom_d_left - 25;
		f = kUserLeft;
		break;
	case kUserRight:
		pCard->setPosition(ccp(posCard_RightX, posCard_RightY));
		tmp = count_chiu_right > 0 ? count_chiu_right - 1 : 0;
		pCard->setPos(CARD_D_RIGHT_bottom->count() - tmp);
		toX = left_d_right - (float)(CARD_D_RIGHT_bottom->count() - tmp) * w_card;
		toY = bottom_d_right - 25;
		f = kUserRight;
		break;
	case kUserTop:
		pCard->setPosition(ccp(posCard_TopX, posCard_TopY));
		tmp = count_chiu_top > 0 ? count_chiu_top - 1 : 0;
		pCard->setPos(CARD_D_TOP_bottom->count() - tmp);
		toX = (float)(CARD_D_TOP_bottom->count() - tmp) * w_card + left_d_top;
		toY = bottom_d_top - 25;
		f = kUserTop;
		break;
	default:
		break;
	}

	pCard->setVisible(true);

	CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	pCard->runAction(moveTo);
	switch (f) {
	case kUserMe:
		CARD_D_ME_bottom->addObject(pCard);
		break;
	case kUserLeft:
		CARD_D_LEFT_bottom->addObject(pCard);
		break;
	case kUserRight:
		CARD_D_RIGHT_bottom->addObject(pCard);
		break;
	case kUserTop:
		CARD_D_TOP_bottom->addObject(pCard);
		break;
	default:
		break;
	}
}

void _Layer_CardChan_::action_ChuyenBai_Chiu(int pos, string cardnu, string cardsu){
	CCLOG("Chuyen bai thu tren tay xuong duoi tay khi chiu");
	CardChan *pCard = NULL;

	float toX = -1;
	float toY = -1;
	int f = -1;
	{
		CCLOG("Chuyen bai khi nguoi khac chiu");
		pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
		_coutZorder++;
		pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
		pCard->setSizeCard(w_card, h_card);
		int tmp;
		int cmp;
		switch(pos){
		case kUserMe:
			for(int i = 0; i < CARD_ME->count(); i++)
			{
				CardChan *cards = (CardChan *)CARD_ME->objectAtIndex(i);
				if (cards->getNumber() == atoi(cardnu.c_str()) && cards->getSuite() == atoi(cardsu.c_str()))
				{
					cards->setTouchEnabled(false);
					cards->setVisible(false);
					CARD_ME->removeObjectAtIndex(i);
					break;
				}
			}
			tmp = count_chiu_me / 3;
			cmp = count_chiu_me % 3;
			pCard->setPosition(ccp(400, 120));
			toX = (float)(CARD_D_ME_bottom->count() - tmp * 3 - cmp + tmp) * w_card + left_d_me;
			toY = (bottom_d_me) - (25 / 2) * (cmp + 1);
			count_chiu_me++;
			f = kUserMe;
			break;

		case kUserBot:
			tmp = count_chiu_me / 3;
			cmp = count_chiu_me % 3;
			pCard->setPosition(ccp(posCard_BottomX, posCard_BottomY));
			toX = (float)(CARD_D_ME_bottom->count() - tmp * 3 - cmp + tmp) * w_card + left_d_me;
			toY = (bottom_d_me) - (25 / 2) * (cmp + 1);
			count_chiu_me++;
			f = kUserMe;
			break;
		case kUserLeft:
			tmp = count_chiu_left / 3;
			cmp = count_chiu_left % 3;
			pCard->setPosition(ccp(posCard_LeftX, posCard_LeftY));
			toX = (float)(CARD_D_LEFT_bottom->count() - tmp * 3 - cmp + tmp) * w_card + left_d_left;
			toY = (bottom_d_left) - (25 /2) * (cmp + 1);
			count_chiu_left++;
			f = kUserLeft;
			break;
		case kUserRight:
			tmp = count_chiu_right / 3;
			cmp = count_chiu_right % 3;
			pCard->setPosition(ccp(posCard_RightX, posCard_RightY));
			toX = left_d_right - (float)(CARD_D_RIGHT_bottom->count() - tmp * 3 - cmp + tmp) * w_card;
			toY = bottom_d_right - (25 / 2) * (cmp + 1);
			count_chiu_right++;
			f = kUserRight;
			break;
		case kUserTop:
			tmp = count_chiu_top / 3;
			cmp = count_chiu_top % 3;
			pCard->setPosition(ccp(posCard_TopX, posCard_TopY));
			toX = (float)(CARD_D_TOP_bottom->count() - tmp * 3 - cmp + tmp) * w_card + left_d_top;
			toY = bottom_d_top - (25 / 2) * (cmp + 1);
			count_chiu_top++;
			f = kUserTop;
			break;
		default:
			break;
		}
		CCLOG("tmp = %d", tmp);
	}
	
	pCard->setVisible(true);
	pCard->setZOrder(_coutZorder + 4);
	float _rotate = -(pCard->getRotation());
	CCLOG("rotate: %f",pCard->getRotation());

	CCActionInterval *moveto = CCMoveTo::create(0.3, ccp(toX, toY));
	CCActionInterval *rotateBy = CCRotateTo::create(0.3, _rotate);
	pCard->runAction(moveto);
	pCard->runAction(rotateBy);

	switch(f)
	{
	case kUserMe:
		CARD_D_ME_bottom->addObject(pCard);
		this->runAction(CCSequence::create(CCDelayTime::create(1.0),CCCallFunc::create(this, callfunc_selector(_Layer_CardChan_::refreshListCard)),NULL));
		break;
	case kUserLeft:
		CARD_D_LEFT_bottom->addObject(pCard);
		break;
	case kUserRight:
		CARD_D_RIGHT_bottom->addObject(pCard);
		break;
	case kUserTop:
		CARD_D_TOP_bottom->addObject(pCard);
		break;
	default:
		break;
	}
}

void _Layer_CardChan_::action_ChuyenBai_ChiuME(string cardnu, string cardsu){

// 	CCObject *t;
// 	CCARRAY_FOREACH(CARD_ME, t){
// 		CardChan *pCard =  dynamic_cast<CardChan*>(t);
// 		if (pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())) {
// 
// 			float rotate = -(pCard->getRotation());
// 			
// 			float toX = (float)(CARD_D_ME_bottom->count() - count_chiu_me) * w_card + left_d_me;
// 			float toY = (bottom_d_me) - (25 /2) * count_chiu_me;
// 
// 			CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp((toX, toY));
// 			CCActionInterval *rotateTo = CCRotateBy::create(0.4, rotate);
// 			CCActionInterval *scaleBy = CCScaleBy::create(0.4, w_card / w_cardhand,h_card / h_cardhand);
// 
// 			pCard->runAction(moveTo);
// 			pCard->runAction(rotateTo);
// 			pCard->runAction(scaleBy);
// 			pCard->setTouchEnabled(false);
// 
// 			CARD_ME->removeObject(pCard);
// 			CARD_D_ME_bottom->addObject(pCard);
// 			count_chiu_me++;
// 
// 			this->refreshListCard();
// 		}
// 	}
}

void _Layer_CardChan_::action_ChuyenBai_ChiuNotMe(int pos, string cardnu, string cardsu){
	//Chuyen bai nhung nguoi khac
}

void _Layer_CardChan_::action_An_U(int f_user, int t_user, string cardnu, string cardsu){
	action_AnCuaTren(f_user, t_user, cardnu, cardsu);
}

CardChan* _Layer_CardChan_::getCardFromPos_take(int pos){
	if (isGuess == true)
	{
	}
	CardChan* fcard = NULL;
	switch (pos) {
	case kUserMe:
		if(CARD_C_ME->count() == 0)
			return NULL;
		fcard = (CardChan*)CARD_C_ME->lastObject();
		CARD_C_ME->removeLastObject();
		break;
	case kUserBot:
		if (CARD_C_ME->count() == 0)
			return NULL;
		fcard = (CardChan*)CARD_C_ME->lastObject();
		CARD_C_ME->removeLastObject();
		break;
	case kUserLeft:
		if (CARD_C_LEFT)
			return NULL;		
		fcard = (CardChan*)CARD_C_LEFT->lastObject();
		CARD_C_LEFT->removeLastObject();
		break;
	case kUserRight:
		if (CARD_C_RIGHT->count() == 0)
			return NULL;
		fcard = (CardChan*)CARD_C_RIGHT->lastObject();
		CARD_C_RIGHT->removeLastObject();
		break;
	case kUserTop:
		if (CARD_C_TOP->count() == 0)
			return NULL;
		fcard = (CardChan*)CARD_C_TOP->lastObject();
		CARD_C_TOP->removeLastObject();
		break;
	default:
		return NULL;
	}
	return fcard;
}

void _Layer_CardChan_::scaleCardsHand_whenU(){
	float countCard = (float)(CARD_ME->count() - 1);

	float start = (-countCard / 2) * goc;
	CCObject *t;
	int cou = 0;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard = dynamic_cast<CardChan*>(t);
		float xOld = 400;
		float yOld = 90;

		float rotate = start + cou * goc;
		float oldAngle = pCard->getRotation();

		float _newAngle = rotate;

		float xNew = xOld + sin(_newAngle * PI / 180) * h_cardhand / 6;
		float yNew = yOld - (h_cardhand / 6 - cos(_newAngle * PI / 180) * h_cardhand / 6);

		pCard->setSizeCard(w_card + 5, h_card + 5);
		CCActionInterval *mm = CCMoveTo::create(0.3, ccp(xNew, yNew));
		pCard->runAction(mm);

		cou++;
	}
}

void _Layer_CardChan_::setCardsResuilt(string listCards){
	this->setTouchEnabled(true);
	dianoc->setEnabled(false);

	vector<string> list = mUtils::splitString(listCards, ';');

	int i = 0;
	int list_size = (int)list.size();

	float posx = ((WIDTH_DESIGN - (list_size * (w_card + 5) / 3)) / 2);
	flag_DragDrop1 = true;
	while (i <= list.size()) {
		if (i < list.size()) {
			vector<string> info = mUtils::splitString(list[i], ':');
			CardChan *pCard = CardChan::create();
			pCard->loadTexture(findTypeCard(info[1], info[2]).c_str());
			pCard->setSizeCard(w_card + 5, h_card + 5);
			pCard->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2 + 50));
			float start = (list_size % 2 == 0) ? (float)list_size : (float)(list_size - 1);
			pCard->setTouchEnabled(true);
			pCard->setVisible(true);
			pCard->addTouchEventListener(this, toucheventselector(_Layer_CardChan_::CardResuiltMove));
			CARD_RESUITL->addObject(pCard);
			layerCardResult->addChild(pCard);
			i++;
		}else{
			rotateListCards(CARD_RESUITL);
			rLayer->getWidgetByTag(kTag_buttonNoc)->setEnabled(true);
			break;
		}
	}//end while
}

void _Layer_CardChan_::moveCardChi_whenU(){
	CCObject *t;
	int cou = 0;
	CCARRAY_FOREACH(CARD_C_ME, t){
		CardChan *pCard = dynamic_cast<CardChan*>(t);
		float oldx = pCard->getPositionX();
		CCMoveTo *moveTo = CCMoveTo::create(0.3,ccp(oldx, bottom_d_me - 25));
		pCard->runAction(moveTo);
	}
}

void _Layer_CardChan_::setCountNoc(int count){
	string _dem = boost::to_string(count);
	this->countNoc->setText(_dem);
}

void _Layer_CardChan_::setListNoc(string _list){
	this->list_noc = _list;
}

void _Layer_CardChan_::doDisCards(){
	CCLOG("Btn Take Click");
	//EXT_EVENT_REQ_DISCARD = "rqhofc";
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	int count = 0;
	for (int i = 0; i < CARD_ME->count(); i++) {
		CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
		if (pCard->getFlag()) {
			count++;
			boost::shared_ptr<ISFSObject> params (new SFSObject());
			params->PutByte("cardnu", pCard->getNumber());
			params->PutByte("cardsu", pCard->getSuite());
			boost::shared_ptr<IRequest> request (new ExtensionRequest("rqhofc",params,lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
			break;
		}
	}
	if (count == 0) {
		CCLOG("Chọn 1 lá bài để đánh");
		Chat *toast = new Chat("Chọn 1 lá bài để đánh",-1);
		toast->setPositionY(HEIGHT_DESIGN / 2 - 60);
		this->addChild(toast);
	}
	else{
		count = 0;
	}
}

void _Layer_CardChan_::doChiuCard(){
	//EXT_EVENT_REQ_CHIU_CARD = "rqchiuc";
	boost::shared_ptr<Room> lstRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	int count = 0;
	for(int i = 0; i < CARD_ME->count(); i++)
	{
		CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
		if (pCard->getFlag())
		{
			count ++;
			boost::shared_ptr<ISFSObject> params (new SFSObject());
			params->PutByte("cardnu", pCard->getNumber());
			params->PutByte("cardsu", pCard->getSuite());
			boost::shared_ptr<IRequest> request (new ExtensionRequest("rqchiuc", params, lstRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
			break;
		}
	}
	if (count == 0)
	{
		Chat *toast = new Chat("Chọn 1 lá bài để chíu", -1);
		toast->setPositionY(HEIGHT_DESIGN / 2 - 60);
		this->addChild(toast);
	}
	else
	{
		count == 0;
	}
}

void _Layer_CardChan_::doEateCard(){
	//EXT_EVENT_REQ_TAKE_CARD = "rqtkc";
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	int count = 0;
	for (int i = 0; i < CARD_ME->count(); i++) {
		CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
		if (pCard->getFlag()) {
			count++;
			boost::shared_ptr<ISFSObject> params (new SFSObject());
			params->PutByte("cardnu", pCard->getNumber());
			params->PutByte("cardsu", pCard->getSuite());
			boost::shared_ptr<IRequest> request (new ExtensionRequest("rqtkc",params,lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
			break;
		}
	}
	if (count == 0) {
		Chat *toast = new Chat("Chọn 1 lá bài để ăn", -1);
		toast->setPositionY(HEIGHT_DESIGN / 2 - 60);
		this->addChild(toast);
	}
	else{
		count = 0;
	}
}

void _Layer_CardChan_::doDuoiCard(){
	//EXT_EVENT_REQ_DUOI_CARD = "EXT_EVENT_REQ_DUOI_CARD = "rqduoic";";
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	boost::shared_ptr<Room> lstRooms = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rqduoic",params,lstRooms));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void _Layer_CardChan_::doViewNoc(string listnoc){
	CCLOG("Do View Noc ! %s",list_noc.c_str());
	
	if(CARD_NOC->count() > 0){
		while(CARD_NOC->count() > 0){
			CardChan *pCard = (CardChan*) CARD_NOC->lastObject();
			CARD_NOC->removeLastObject();
			pCard->removeFromParentAndCleanup(true);
		}
	}
	
	if(strcmp(list_noc.c_str(),"") != 0){
		vector<string> arrNoc = mUtils::splitString(list_noc,';');
		float startLeft = (800 - (arrNoc.size() * (w_card / 3 * 2))) / 2;
		int i = 0;
		int listsize = (int)arrNoc.size();
		while(i <= listsize)
		{
			if (i < listsize)
			{
				vector<string> info = mUtils::splitString(arrNoc[i], ':');
				CardChan *pCard = CardChan::create();
				pCard->loadTexture(findTypeCard(info[1], info[2]).c_str());
				pCard->setSizeCard(w_card, h_card);
				pCard->setPosition(ccp(startLeft, HEIGHT_DESIGN / 2 - h_card / 2));
				pCard->setVisible(true);
				pCard->setTouchEnabled(true);
				pCard->addTouchEventListener(this, toucheventselector(_Layer_CardChan_::CardNoc_Touch));
				CARD_NOC->addObject(pCard);
				rLayer->addWidget(pCard);
				i++;
			}
			else
			{
				displayListCard_Noc(CARD_NOC);
				break;
			}
		}
	}
}

void _Layer_CardChan_::displayListCard_Noc(CCArray *P){
	if (P->count() == 0)
	{
		return;
	}

	int startLeft = (800 - P->count() * (w_card / 3 * 2)) / 2;
	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CCActionInterval *moveTo = CCMoveTo::create(0.8, ccp(startLeft + dem * (w_card / 3 * 2), HEIGHT_DESIGN / 2 - h_card / 2));
		card->runAction(CCSequence::create(moveTo, NULL));
		dem++;
	}
}

void _Layer_CardChan_::CardNoc_Touch(CCObject *pSender,TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
	{
		if (CARD_NOC->count() > 0)
		{
			while(CARD_NOC->count() > 0)
			{
				CardChan *pCard = (CardChan*) CARD_NOC->lastObject();
				CARD_NOC->removeLastObject();
				pCard->removeFromParentAndCleanup(true);
			}
		}
	}
  }
}

void _Layer_CardChan_::playSounds(string url){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(("sounds/Chan/"+url).c_str());
}

void _Layer_CardChan_::setCallbackFunc(CCObject* target, SEL_CallFuncN callfun){
	m_callback = target;
	m_callbackListener = callfun;
}

CCPoint _Layer_CardChan_::convertPoint(CCPoint pPoint) {

	float xCenter = this->sizeScreen.width / 2;
	float yCenter = this->sizeScreen.height / 2;

	float xTap = pPoint.x;
	float yTap = pPoint.y;

	float x1, x2;
	float y1, y2;

	float A = ((powf(xCenter - xTap, 2) + powf(yCenter - yTap, 2))) / powf(scaleApp, 2);
	float B = powf((yCenter - yTap) / (xCenter - xTap) , 2) + 1;

	x1 = xCenter + sqrtf(A / B);
	x2 = xCenter - sqrtf(A / B);

	y1 = yCenter + (yCenter - yTap) * (x1 - xCenter) / (xCenter - xTap);
	y2 = yCenter + (yCenter - yTap) * (x2 - xCenter) / (xCenter - xTap);

	// "điểm cần convert" = A
	// Bởi vì A và Tap nằm ở cùng 1 phía so với Center nên nếu xTap < xCenter thì xA < xCenter và ngược lại
	if ((xTap < xCenter && x1 < xCenter) || (xTap > xCenter && x1 > xCenter)) {
		x1 -= startLeft;
		y1 -= startTop;

		pPoint.x = x1;
		pPoint.y = y1;
	} else if ((xTap < xCenter && x2 < xCenter) || (xTap > xCenter && x2 > xCenter)) {
		x2 -= startLeft;
		y2 -= startTop;

		pPoint.x = x2;
		pPoint.y = y2;
	} else {
		CCLog("No define POINT CONVERT");
	}

	return pPoint;
}

float   _Layer_CardChan_::getDisPoint(CCPoint p1, CCPoint p2) {
	float dis;

	dis = sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));

	return dis;
}

void _Layer_CardChan_::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	CCSetIterator iterator = pTouches->begin();
	CCTouch *touch;
	touch = (CCTouch*)(*iterator);
	CCPoint tap;
	tap = convertPoint(touch->getLocation());
	disTouchBegan.setSize(0,0);

	if (tap.x > pos_Left && tap.x < pos_Right && tap.y > pos_Bottom && tap.y < pos_Top)
	{
		flag_DragDrop2 = true;
		disTouchBegan.setSize(tap.x - pos_Left, tap.y - pos_Bottom);
	}
}

void _Layer_CardChan_::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	CCSetIterator iterator;
	CCTouch *touch;
	CCPoint tap;

	iterator = pTouches->begin();
	touch = (CCTouch*)(*iterator);
	tap = convertPoint(touch->getLocation());
	if (flag_DragDrop2 == true)
	{
		layerCardResult->setPosition(ccp(tap.x - pos_Left - disTouchBegan.width, tap.y - pos_Bottom - disTouchBegan.height));
	}
}

void _Layer_CardChan_::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (flag_DragDrop2 == true)
	{
		pos_Left = WIDTH_DESIGN / 2 - h_card - 20 + layerCardResult->getPositionX();
		pos_Right = WIDTH_DESIGN / 2 + h_card + 20 + layerCardResult->getPositionX();
		pos_Bottom = HEIGHT_DESIGN / 2 + 50 - h_card + layerCardResult->getPositionY();
		pos_Top = HEIGHT_DESIGN / 2 + 55 + h_card + layerCardResult->getPositionY(); 

		flag_DragDrop2 = false;
	}
}

void _Layer_CardChan_::btn_XemNoc_click(CCObject *sender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		doViewNoc("");
	}
}