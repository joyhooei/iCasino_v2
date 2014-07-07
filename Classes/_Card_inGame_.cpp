//
//  _Card_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/19/14.
//  Layer chứa các quân bài cũng như các thao tác với quân bài
//

#include "_Card_inGame_.h"
#include "SceneManager.h"
#include "LayerPlayGamePhom.h"

enum {
    kTagCountCard = 0
};

vector<string> LayerCardInGame::split(string &S, const char &str) {
    vector<string> arrStr;
    string::iterator t, t2;
    
    for (t = S.begin(); t < S.end(); ){
        // Lặp từ vị trí bắt đầu
        t2 = find(t, S.end(), str);
        
        //kể từ vị trí t
        if(t != t2){
            arrStr.push_back(string(t, t2));
        }
        else if (t2 != S.end())
        {
			arrStr.push_back("");
        }
        
        
		if (t2 == S.end())
		{
			break;
		}
        t = t2 + 1;
    }
    
    return arrStr;
}

LayerCardInGame::~LayerCardInGame() {
	CCLOG("~~~~LayerCardInGame");
}

void LayerCardInGame::onExit() {
	CCLOG("onExit: clean LayerCardInGame");

	CC_SAFE_DELETE_ARRAY(arrCardOnHand);
	CC_SAFE_DELETE_ARRAY(arrAllCard);

	arrIDCardOnHandLeft.clear();
	arrIDCardOnHandRight.clear();
	arrIDCardOnHandTop.clear();

	if (cardBackLeft)
	{
		cardBackLeft->release();
		cardBackLeft=NULL;
	}
	if (cardBackRight)
	{
		cardBackRight->release();
		cardBackRight=NULL;
	}
	if (cardBackTop)
	{
		cardBackTop->release();
		cardBackTop=NULL;
	}
}

// mang co dang id:xx:xx:xx:xx;id:xx:xx:xx:xx;id:xx:xx:xx:xx ta chi can tach ra va lay cac id
vector<int> LayerCardInGame::getIDFromString(string pList) {
    vector<string> arrString = split(pList, ';');
    
    vector<int> arrID;
    int length = arrString.size();
    
    for (int i = 0; i < length; i++) {
        if (arrString[i].length() > 3) {
            vector<string> arrInfo = split(arrString[i], ':');
            if (arrInfo[0].length() > 0) {
                arrID.push_back(atoi(arrInfo[0].c_str()));
            }
        }
    }
    
    return arrID;
}

vector<int> LayerCardInGame::getIDFromString_Last(string pList) {
	vector<string> arrString = split(pList, ';');

	vector<int> arrID;
	int length = arrString.size();

	for (int i = 0; i < length; i++) {
		if (arrString[i].length() > 3) {
			vector<string> arrInfo = split(arrString[i], ':');
			if (arrInfo[0].length() > 0) {
				arrID.push_back(atoi(arrInfo[arrInfo.size()-1].c_str()));
			}
		}
	}

	return arrID;
}

// "id, id, id, id"
vector<int> LayerCardInGame::getIDFromString_TienLen(string pList) {
    vector<string> arrString = split(pList, ',');
    
    vector<int> arrID;
    int length = arrString.size();
    
    for (int i = 0; i < length; i++) {
        arrID.push_back(atoi(arrString[i].c_str()));
    }
    
    return arrID;
}

int LayerCardInGame::getCountCardOnHand() {
    return arrCardOnHand->count();
}

int LayerCardInGame::getCountCardTaken() {
    return countCardMe_Take;
}

bool LayerCardInGame::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    // scaleApp
    // ---- TouchEvent Start
    this->sizeScreen = CCDirector::sharedDirector()->getVisibleSize();
    float scaleX = sizeScreen.width / WIDTH_DESIGN;
    float scaleY = sizeScreen.height / HEIGHT_DESIGN;
    float scaleMin = (scaleX < scaleY) ? scaleX : scaleY;
    scaleApp = scaleMin;
    
    startLeft = (sizeScreen.width - WIDTH_DESIGN) / 2;
    startTop = (sizeScreen.height - HEIGHT_DESIGN) / 2;
    
	cardBackLeft = NULL;
	cardBackRight = NULL;
	cardBackTop = NULL;

    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(0, 0));
    this->setTouchEnabled(true);
    
    initGame();
    
    return true;
}

// event touches
void LayerCardInGame::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
    CCSetIterator iterator = pTouches->begin();
    CCTouch *touch;
    touch = (CCTouch*)(*iterator);
    CCPoint tap;
    tap = convertPoint(touch->getLocation());
    this->pointTouchBegan = tap;
    
    // refresh status
    disTouchBegan.setSize(0, 0);
    indexCardCurrent = -1;
    indexCardTarget  = -1;
    isClickCard = true;
    
    int length = arrCardOnHand->count();
    for (int i = 0; i < length; i++) {
        Card *card = (Card*) arrCardOnHand->objectAtIndex(i);
        
        if ((i < length - 1 && isTouchedCard_notTail(card, tap)) || (i == length - 1 && isTouchedCard_Tail(card, tap))){
            countTouched++;
            
            disTouchBegan.setSize(tap.x - card->getPositionX(), tap.y - card->getPositionY());
            
            indexCardCurrent = i;
            break;
        }
    }
}

void LayerCardInGame::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCSetIterator iterator;
    CCTouch *touch;
    CCPoint tap;
    
    if (indexCardCurrent >= 0) {
        int length = arrCardOnHand->count();
        
        Card *card = (Card*) arrCardOnHand->objectAtIndex(indexCardCurrent);
        Card *cardTarget;
        
        iterator = pTouches->begin();
        touch = (CCTouch*)(*iterator);
        tap = convertPoint(touch->getLocation());
        
        if (disTouchBegan.width > 0) {
            isClickCard = false;
            
            // tim quan bai Target
            for (int iT = 0; iT < length; iT++) {
                cardTarget = (Card*) arrCardOnHand->objectAtIndex(iT);
                
                if (card != cardTarget){
                    if ((iT < length - 1 && isTouchedCard_notTail(cardTarget, tap)) || (iT == length - 1 && isTouchedCard_Tail(cardTarget, tap))){
                        indexCardTarget = iT;
                        break;
                    }
                }
            }
           
            tap.x -= disTouchBegan.width;
            tap.y -= disTouchBegan.height;
            
            card->setZOrder(length);
            card->setPosition(tap);
        }
        
    }
    
}

void LayerCardInGame::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (indexCardCurrent >= 0) {
        Card *card = (Card*) arrCardOnHand->objectAtIndex(indexCardCurrent);
        
        CCSetIterator iterator = pTouches->begin();
        CCTouch *touch;
        touch = (CCTouch*)(*iterator);
        CCPoint tap;
        tap = convertPoint(touch->getLocation());
        
        // clicked
        if (getDisPoint(tap, pointTouchBegan) < 10) {
            card->setZOrder(indexCardCurrent);
            setCardClick(card);
        }
        // moved
        else {
            if (indexCardCurrent < indexCardTarget) indexCardTarget++;
            
            if (indexCardTarget >= 0){
                CCArray *arrCardCopy = new CCArray();
                arrCardCopy->retain();
                
                for (int i = 0; i < indexCardTarget; i++) {
                    Card *card = (Card*) arrCardOnHand->objectAtIndex(i);
                    
                    if (i != indexCardCurrent) {
                        arrCardCopy->addObject(card);
                    }
                }
                
                Card *card = (Card*) arrCardOnHand->objectAtIndex(indexCardCurrent);
                arrCardCopy->addObject(card);
                
                for (int i = indexCardTarget; i < arrCardOnHand->count(); i++) {
                    Card *card = (Card*) arrCardOnHand->objectAtIndex(i);
                    
                    if (i != indexCardCurrent) {
                        arrCardCopy->addObject(card);
                    }
                }
                
                arrCardOnHand->removeAllObjects();
                arrCardOnHand->addObjectsFromArray(arrCardCopy);
                
                arrCardCopy->release();
            }
            
            bool isRefreshTop = true;
            refreshCardOnHand(isRefreshTop);
        }
    }
}

float   LayerCardInGame::getDisPoint(CCPoint p1, CCPoint p2) {
    float dis;
    
    dis = sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
    
    return dis;
}

CCPoint LayerCardInGame::convertPoint(CCPoint pPoint) {
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

bool LayerCardInGame::isTouchedCard_Tail(Card *card, CCPoint tap) {
    
    if (tap.x > card->getPositionX() && tap.x < card->getPositionX() + card->getSize().width &&
        tap.y > card->getPositionY() && tap.y < card->getPositionY() + card->getSize().height) return true;
    
    return false;
}

bool LayerCardInGame::isTouchedCard_notTail(Card *card, CCPoint tap) {
    
    if (tap.x > card->getPositionX() && tap.x < card->getPositionX() + disCards &&
        tap.y > card->getPositionY() && tap.y < card->getPositionY() + card->getSize().height) return true;
    
    return false;
}

void LayerCardInGame::refreshCardOnHand() {
    float leftTheFirst = (WIDTH_DESIGN - (arrCardOnHand->count() - 1) * disCards - sizeCard.width) / 2;
    float top = topCard;
    
    for (int i = 0; i < arrCardOnHand->count(); i++) {
        Card *card = (Card*) arrCardOnHand->objectAtIndex(i);
        card->setZOrder(i);
        card->stopAllActions();
        card->setClicked(false);

        CCMoveTo *actionMove = CCMoveTo::create(0.5, ccp(leftTheFirst + i * disCards, top));
        if (i == arrCardOnHand->count() - 1) {
            // nếu cần gợi ý hạ phỏm
            card->runAction(CCSequence::create(actionMove,
                                               CCCallFuncN::create(this, callfuncN_selector(LayerCardInGame::actionRecommendCard)),
                                               NULL));
        }
        else
            card->runAction(actionMove);
    }
}

void LayerCardInGame::refreshCardOnHand(bool isRefreshTop) {
    float leftTheFirst = (WIDTH_DESIGN - (arrCardOnHand->count() - 1) * disCards - sizeCard.width) / 2;
    float top;
    
    for (int i = 0; i < arrCardOnHand->count(); i++) {
        Card *card = (Card*) arrCardOnHand->objectAtIndex(i);
        
        if (isRefreshTop){
            top = topCard;
            card->setClicked(false);
        }
        else{
			// nếu quân bài đang được click thì top giữ nguyên
			// ngược lại top cần được đặt lại vị trí khởi tạo topCard
			if (card->getClicked()) top = card->getPositionY();
			else top = topCard;
		}
        
        card->setZOrder(i);
        card->stopAllActions();
        card->runAction(CCMoveTo::create(0.5, ccp(leftTheFirst + i * disCards, top)));
    }
}

void LayerCardInGame::refreshCardOnHand(float delay) {
	// only Deal card
    float leftTheFirst = (WIDTH_DESIGN - (arrCardOnHand->count() - 1) * disCards - sizeCard.width) / 2;
    float top = topCard;
    
	playSound("sound_deal_10.mp3");
    for (int i = 0; i < arrCardOnHand->count(); i++) {
        Card *card = (Card*) arrCardOnHand->objectAtIndex(i);
        
        card->setClicked(false);
        card->setZOrder(i);
        card->stopAllActions();
        card->runAction(CCSequence::create(CCDelayTime::create(delay * i),
										   //CCCallFunc::create(this, callfunc_selector(LayerCardInGame::callbackRefreshCardOnHand)),
										   CCMoveTo::create(0.5, ccp(leftTheFirst + i * disCards, top)), 
										   NULL));
    }
}

void LayerCardInGame::callbackRefreshCardOnHand() {
	playSound("card_move.mp3");
}

void LayerCardInGame::setCardClick(Card* card) {
    bool isClick = card->getClicked();
    
    float top;
    if (isClick) top = topCard;
    else top = topCard + card->getSize().height / 4;
    
    card->stopAllActions();
    card->runAction(CCMoveTo::create(0.2, ccp(card->getPositionX(), top)));
    
    card->setClicked(!isClick);
}

string LayerCardInGame::getURL_byID(int pID) {
    ostringstream oss;
    
    int num = (pID % 13) + 1;
    int type = (pID / 13) + 1;
    
    string url = "card_";
    
    switch (num) {
        case 11:
            url += "j";
            break;
        case 12:
            url += "q";
            break;
        case 13:
            url += "k";
            break;
        case 1:
            url += "a";
            break;
        default:
            oss << num;
            url += oss.str();
            break;
    }
    
    url+= "_";
    
    switch (type) {
        case 1:
            url += "h.png";
            break;
        case 2:
            url += "d.png";
            break;
        case 3:
            url += "s.png";
            break;
        case 4:
            url += "c.png";
            break;
            
        default:
            break;
    }
    
    return url;
}

string LayerCardInGame::getURL_byID_TienLen(int pID) {
    ostringstream oss;
    
    int num = (pID / 4);
    int type = (pID % 4);
    
    if (type == 0) {
		num--;
		type = 3;
	} else
		type--;
	if (pID == 0) {
		num = 0;
		type = 0;
	}
    
    string url = "card_";
    
    switch (num) {
		case 11:
			url += "j";
			break;
		case 12:
			url += "q";
			break;
		case 13:
			url += "k";
			break;
		case 14:
			url += "a";
			break;
		case 15:
			url += "2";
			break;
		default:
			oss << num;
            url += oss.str();
			break;
	}
    
    url += "_";
    
	// [0, 1, 2, 3] = ['s', 'c', 'd', 'h']
	switch (type) {
		case 0:
			url += "s.png";
			break;
		case 1:
			url += "c.png";
			break;
		case 2:
			url += "d.png";
			break;
		case 3:
			url += "h.png";
			break;
	}
    
    return url;
}

vector<int> LayerCardInGame::getIdCardByClicked() {
    vector<int> arrID;
    
    for (int i = 0; i < arrCardOnHand->count(); i++) {
        Card* card = (Card*) arrCardOnHand->objectAtIndex(i);
        if (card->getClicked()) {
            arrID.push_back(card->getID());
        }
    }
    
    return arrID;
}

vector<string> LayerCardInGame::getID_HaPhom() {
    vector<string> arrListID;
    
    vector<int> arrCardClicked = getIdCardByClicked();
    
    for (int tag = 0; tag < 3; tag++) {
        string list = "";
        
        for (int i = 0; i < arrCardClicked.size(); i++) {
            int id = arrCardClicked[i];
            
            Card *card = getCardByID(id);
            
            if (card->getTag() == tag) {
                if (list.length() != 0) {
                    list += ":";
                }
                
                ostringstream oss;
                oss<<id;
                list += oss.str();
            }
        }
        
        if (list.length() > 0) {
            arrListID.push_back(list);
        }
    }
    
    for (int i = 0; i < arrListID.size(); i++) {
        CCLog("getID_HaPhom= %s", arrListID[i].c_str());
    }
    
    return arrListID;
}

void LayerCardInGame::setIdCardCanEat(int id) {
    this->idCardCanEat = id;
}

int LayerCardInGame::getIdCardCanEat() {
    return this->idCardCanEat;
}

void LayerCardInGame::setGameStarted(bool isStarted){
    this->gameStarted = isStarted;
}

bool LayerCardInGame::getGameStarted() {
    return this->gameStarted;
}

bool LayerCardInGame::getAllowSortCard() {
    return this->allowSortCard;
}

void LayerCardInGame::setAllowSortCard(bool isAllow) {
    this->allowSortCard = isAllow;
}

void LayerCardInGame::initGame() {
    //if (arrAllCard == NULL) {
        //
        ZORDER_PHOM = 0;
        ZORDER_TAKE = 10;
        ZORDER_HAND = 20;
        
        topCard = 72;
        disCards = 55;
        
        isClickCard = true;
        gameStarted = false;
        allowSortCard = true;
        requestRecommendHaPhom = false;
        
        this->lcRecommendHaPhom = "";

		// count
		countCardMe_Take = 0;
		countCardLeft_Take = 0;
		countCardRight_Take = 0;
		countCardTop_Take = 0;
		countCardBot_Take = 0;
		//
		countCardMe_Eat = 0;
		countCardLeft_Eat = 0;
		countCardRight_Eat = 0;
		countCardTop_Eat = 0;
		countCardBot_Eat = 0;
		//
		countCardMe_Phom = 0;
		countCardLeft_Phom = 0;
		countCardRight_Phom = 0;
		countCardTop_Phom = 0;
		countCardBot_Phom = 0;
		//
		countMe_Phom = 0;
        
        //
        arrAllCard = new CCArray();
        arrAllCard->retain();
        
        arrCardOnHand = new CCArray();
        arrCardOnHand->retain();
        
        
        // all cards
        // card_back
        Card *card_back = new Card("card_back.png");
        sizeCard = card_back->getSize();
        card_back->setAnchorPoint(ccp(0, 0));
        card_back->setPosition(getPointCardInCenter());
        card_back->setID(-1);
        card_back->setZOrder(52);
        arrAllCard->addObject(card_back);
        
        this->addChild(card_back);
    //}
}

void LayerCardInGame::resetGame() {
    // card
    arrCardOnHand->removeAllObjects();
	arrIDCardOnHandLeft.clear();
	arrIDCardOnHandRight.clear();
	arrIDCardOnHandTop.clear();
    
    int length = arrAllCard->count();
    
    for (int i = 0; i < length; i++) {
        Card *card = (Card*) arrAllCard->objectAtIndex(i);
        card->resetStatus();
        card->setPosition(getPointCardInCenter());
    }
    
    gameStarted = false;
    requestRecommendHaPhom = false;
	lcRecommendHaPhom = "";
    
    // count
    countCardMe_Take = 0;
    countCardLeft_Take = 0;
    countCardRight_Take = 0;
    countCardTop_Take = 0;
    countCardBot_Take = 0;
    //
    countCardMe_Eat = 0;
    countCardLeft_Eat = 0;
    countCardRight_Eat = 0;
    countCardTop_Eat = 0;
    countCardBot_Eat = 0;
    //
    countCardMe_Phom = 0;
    countCardLeft_Phom = 0;
    countCardRight_Phom = 0;
    countCardTop_Phom = 0;
    countCardBot_Phom = 0;
    //
    countMe_Phom = 0;
    
    if (cardBackLeft != NULL) {
        cardBackLeft->setVisible(false);
        cardBackRight->setVisible(false);
        cardBackTop->setVisible(false);
    }
}

void LayerCardInGame::playSound( string soundPath )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundPath.c_str());
}

//
void LayerCardInGame::initCardByPhom() {
    // init card
    for (int i = 0; i < 52; i++) {
        Card *card = new Card(getURL_byID(i).c_str());
        card->setID(i);
        card->setAnchorPoint(ccp(0, 0));
        card->setPosition(getPointCardInCenter());
        
        this->addChild(card);
        arrAllCard->addObject(card);
    }
}

void LayerCardInGame::initCardByTienLen() {
    for (int id = 13; id < 52 + 13; id++) {
        Card *card = new Card(getURL_byID_TienLen(id).c_str());
        card->setID(id);
		card->setURL(getURL_byID_TienLen(id));
        card->setAnchorPoint(ccp(0, 0));
        card->setPosition(getPointCardInCenter());
        
        this->addChild(card);
        arrAllCard->addObject(card);
    }
    
    // các quân bài tượng trưng
    cardBackLeft = CCSprite::create("card_back.png");
    cardBackRight = CCSprite::create("card_back.png");
    cardBackTop = CCSprite::create("card_back.png");
    
    cardBackLeft->setVisible(false);
    cardBackRight->setVisible(false);
    cardBackTop->setVisible(false);
    
    cardBackLeft->setAnchorPoint(ccp(0, 0));
    cardBackLeft->setPosition(getStartPositionCardUserLeft_Hit_TienLen());
    cardBackLeft->setScale(0.5);
    cardBackLeft->setZOrder(100);
    
    cardBackRight->setAnchorPoint(ccp(0, 0));
    cardBackRight->setPosition(getStartPositionCardUserRight_Hit_TienLen());
    cardBackRight->setScale(0.5);
    cardBackRight->setZOrder(100);
    
    cardBackTop->setAnchorPoint(ccp(0, 0));
    cardBackTop->setPosition(getStartPositionCardUserTop_Hit_TienLen());
    cardBackTop->setScale(0.5);
    cardBackTop->setZOrder(100);
    //
    this->addChild(cardBackLeft);
    this->addChild(cardBackRight);
    this->addChild(cardBackTop);
    
    //
    // hien thi so quan bai dang co tren tay
    CCLabelTTF *countCardLeft = CCLabelTTF::create("0", "Arial", 45);
    CCLabelTTF *countCardRight = CCLabelTTF::create("0", "Arial", 45);
    CCLabelTTF *countCardTop = CCLabelTTF::create("0", "Arial", 45);
    
    countCardLeft->setAnchorPoint(ccp(0, 0));
    countCardRight->setAnchorPoint(ccp(0, 0));
    countCardTop->setAnchorPoint(ccp(0, 0));
    
    countCardLeft->setColor(ccYELLOW);
    countCardRight->setColor(ccYELLOW);
    countCardTop->setColor(ccYELLOW);
    
    float widCard = cardBackLeft->getContentSize().width;
    float heiCard = cardBackLeft->getContentSize().height;
    float widLabel = countCardLeft->getContentSize().width;
    float heiLabel = countCardLeft->getContentSize().height;
    CCPoint pointCenter = ccp((widCard - widLabel) / 2, (heiCard - heiLabel) / 2);
    
    countCardLeft->setPosition(pointCenter);
    countCardRight->setPosition(pointCenter);
    countCardTop->setPosition(pointCenter);
    
    countCardLeft->setTag(kTagCountCard);
    countCardRight->setTag(kTagCountCard);
    countCardTop->setTag(kTagCountCard);
    
    cardBackLeft->addChild(countCardLeft);
    cardBackRight->addChild(countCardRight);
    cardBackTop->addChild(countCardTop);
}

void LayerCardInGame::actionDealCard(vector<int> arrCardID) {
    arrCardOnHand->removeAllObjects();
    
    for (int i = 0; i < arrCardID.size(); i++) {
        int id = (int) arrCardID[i];
        Card *card = getCardByID(id);
        card->setVisible(true);
        arrCardOnHand->addObject(card);
    }
    
    float delay = 0.1;
    refreshCardOnHand(delay);
}

void LayerCardInGame::actionSortCard(vector<int> arrCardID) {
    // tạm thôi!
    
    if (!allowSortCard){
        CCLog("Khong dc xep bai do allowSortCard=false !");
        return;
    }
    
    // mỗi lần xếp đều "nghỉ" 3s
    this->allowSortCard = false;
    // this->scheduleOnce(schedule_selector(LayerCardInGame::delayAllowSortCard), 3);
    
    int length = arrCardID.size();
    
    arrCardOnHand->removeAllObjects();
    
    for (int i = 0; i < length; i++) {
        int id = (int) arrCardID[i];
        Card *card = getCardByID(id);
        card->setVisible(true);
        arrCardOnHand->addObject(card);
    }
    
	bool isRefreshTop = false;
    refreshCardOnHand(isRefreshTop);
}

void LayerCardInGame::actionSortCardByTienLen() {
    
    int length = arrCardOnHand->count();
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            Card *cardi = (Card*) arrCardOnHand->objectAtIndex(i);
            Card *cardj = (Card*) arrCardOnHand->objectAtIndex(j);
            
            if (cardi->getID() > cardj->getID()) {
                arrCardOnHand->removeObjectAtIndex(i);
                arrCardOnHand->insertObject(cardj, i);
                
                arrCardOnHand->removeObjectAtIndex(j);
                arrCardOnHand->insertObject(cardi, j);
            }
        }
    }
    
    refreshCardOnHand();
}

void LayerCardInGame::delayAllowSortCard() {
    this->allowSortCard = true;
}

void LayerCardInGame::actionHitCard(int kUser, int id) {
    int length = arrAllCard->count();
    
    if (id >= length) {
        id = length - 1;
    }

	bool isPlaySound = true;
    if (length > 0){
        Card *card = getCardByID(id);
        
        switch (kUser) {
            case kUserMe:
                arrCardOnHand->removeObject(card);
                refreshCardOnHand();
                
                if (!card->isVisible()) {
                    card->setVisible(true);
                }
                
                card->setZOrder(0);
                card->runAction(CCMoveTo::create(0.3, ccp(350 + disCards / 2 * countCardMe_Take, topCard + sizeCard.height)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardMe_Take++;
                
                break;
            case kUserLeft:
                
                if (!card->isVisible()){
                    card->setVisible(true);
                    card->setPosition(getStartPositionCardUserLeft_Hit());
                }
                
                card->setZOrder(ZORDER_TAKE + countCardLeft_Take);
                card->runAction(CCMoveTo::create(0.3, ccp(125 + disCards / 2 * countCardLeft_Take, 214)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardLeft_Take++;
                
                break;
            case kUserRight:
                
                if (!card->isVisible()) {
                    card->setVisible(true);
                    card->setPosition(getStartPositionCardUserRight_Hit());
                }
                
                card->setZOrder(ZORDER_TAKE + countCardRight_Take);
                card->runAction(CCMoveTo::create(0.3, ccp(687 - (3 * disCards / 2 + card->getContentSize().width / 2) + disCards / 2 * countCardRight_Take, 214)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardRight_Take++;
                
                break;
            case kUserTop:
                
                if (!card->isVisible()) {
                    card->setVisible(true);
                    card->setPosition(getStartPositionCardUserTop_Hit());
                }
                
                card->setZOrder(ZORDER_TAKE + countCardTop_Take);
                card->runAction(CCMoveTo::create(0.3, ccp(350 + disCards / 2 * countCardTop_Take, HEIGHT_DESIGN - 114 - sizeCard.height)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardTop_Take++;
                
                break;
            case kUserBot:
                
                if (!card->isVisible()) {
                    card->setVisible(true);
                    card->setPosition(getStartPositionCardUserRight_Hit());
                }
                
                card->setZOrder(ZORDER_TAKE + countCardBot_Take);
                card->runAction(CCMoveTo::create(0.3, ccp(350 + disCards / 2 * countCardBot_Take, 162)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardBot_Take++;
                
                break;
            default:
				isPlaySound=false;
                break;
        }
        
		if (isPlaySound) playSound("danh_bai.mp3");
    }
}

void LayerCardInGame::actionHitCardByTienLen(int posUser, vector<int> arrID) {
    int length = arrID.size();
    float toLeft = WIDTH_DESIGN / 2 - (sizeCard.width / 2 * length) / 2;
    float toTop = getPointCardInCenter().y;
    
    bool isMe = false;
    for (int i = 0; i < length; i++) {
        int id = (int) arrID[i];
        Card *card = getCardByID(id);
        
        if (posUser == kUserMe) {
            removeCardOnHandByID(id);
            isMe = true;
        }
        
        if (!card->isVisible()) {
            card->setPosition(getStartPositionCardByPos_TienLen(posUser));
            card->setVisible(true);
        }
        
        int rdAngle = rand() % 20 - 10;
        
        card->setZOrder(52);
        card->runAction(CCRotateTo::create(0.3, rdAngle));
        card->runAction(CCMoveTo::create(0.3, ccp(toLeft + i * disCards / 2, toTop)));
        card->runAction(CCScaleTo::create(0.3, 0.5));
    }
    if (isMe) {
        refreshCardOnHand();
    }
}

void LayerCardInGame::actionGiveCard(int kUser, int id) {
    int length = arrAllCard->count();
    if (id >= length) id = -1;
    
    Card *card = getCardByID(id);
    
    card->resetStatus();
    card->setPosition(getPointCardInCenter());
    card->setVisible(true);
    
	bool isPlaySound = true;
    switch (kUser) {
        case kUserMe:
            
            arrCardOnHand->addObject(card);
            refreshCardOnHand();
            
            break;
        case kUserLeft:
            
            card->runAction(CCSequence::create(CCMoveTo::create(0.3, getStartPositionCardUserLeft_Hit()), CCDelayTime::create(0.5), CCCallFuncN::create(this, callfuncN_selector(LayerCardInGame::callbackGiveCard)), NULL));
            card->runAction(CCScaleTo::create(0.3, 0.5));
            
            break;
        case kUserRight:
            
            card->runAction(CCSequence::create(CCMoveTo::create(0.3, getStartPositionCardUserRight_Hit()), CCDelayTime::create(0.5), CCCallFuncN::create(this, callfuncN_selector(LayerCardInGame::callbackGiveCard)), NULL));
            card->runAction(CCScaleTo::create(0.3, 0.5));
            
            break;
        case kUserTop:
            
            card->runAction(CCSequence::create(CCMoveTo::create(0.3, getStartPositionCardUserTop_Hit()), CCDelayTime::create(0.5), CCCallFuncN::create(this, callfuncN_selector(LayerCardInGame::callbackGiveCard)), NULL));
            card->runAction(CCScaleTo::create(0.3, 0.5));
            
            break;
        case kUserBot:
            
            card->runAction(CCSequence::create(CCMoveTo::create(0.3, getStartPositionCardUserBot_Hit()), CCDelayTime::create(0.5), CCCallFuncN::create(this, callfuncN_selector(LayerCardInGame::callbackGiveCard)), NULL));
            card->runAction(CCScaleTo::create(0.3, 0.5));
            
            break;
            
        default:
			isPlaySound=false;
            break;
    }

	if (isPlaySound) playSound("rut_bai.mp3");
}

void LayerCardInGame::callbackGiveCard(CCNode *pSender) {
    Card *card = getCardByID(-1);
    card->setVisible(false);
}

void LayerCardInGame::actionEatCard(int fromPosUser, int toPosUser, int pId) {
    int length = arrAllCard->count();
    if (pId >= 100) pId = length - 1;
    
    Card *card = getCardByID(pId);
    card->setCardAte();
	//CCLog("Quan bai can tren tay can di chuyen la: id=%d, name=%s", card->getID(), card->getURL().c_str());
    
	bool isPlaySound = true;
    switch (fromPosUser) {
        case kUserMe: case kUserBot:
            countCardMe_Take--;
            countCardBot_Take--;
            break;
        case kUserLeft:
            countCardLeft_Take--;
            break;
        case kUserRight:
            countCardRight_Take--;
            break;
        case kUserTop:
            countCardTop_Take--;
            break;
        default:
			isPlaySound=false;
            break;
    }
	if (isPlaySound) playSound("an_bai.mp3");
    
	
    switch (toPosUser) {
        case kUserMe:
            
            card->setScaleCard(card->getScaleCardX(), card->getScaleCardY());
            arrCardOnHand->addObject(card);
            refreshCardOnHand();
            
            countCardMe_Eat++;
            
            break;
            
        case kUserLeft:
            
            if (!card->isVisible()) {
                card->setVisible(true);
                card->setPosition(getStartPositionCardUserLeft_Hit());
            }
            
            card->setScale(0.5);
            card->runAction(CCMoveTo::create(0.3, ccp(10 + disCards / 2 * countCardLeft_Eat, 310)));
            card->setZOrder(countCardLeft_Eat);
            
            countCardLeft_Eat++;
            
            break;
            
        case kUserRight:
            
            if (!card->isVisible()) {
                card->setVisible(true);
                card->setPosition(getStartPositionCardUserRight_Hit());
            }
            
            card->setScale(0.5);
            card->runAction(CCMoveTo::create(0.3, ccp(790 - sizeCard.width / 2 - disCards / 2 * countCardRight_Eat, 310)));
            card->setZOrder(10 - countCardRight_Eat);
            
            countCardRight_Eat++;
            
            break;
            
        case kUserTop:
            
            if (!card->isVisible()) {
                card->setVisible(true);
                card->setPosition(getStartPositionCardUserTop_Hit());
            }
            
            card->setScale(0.5);
            card->runAction(CCMoveTo::create(0.3, ccp(457 + disCards / 2 * countCardTop_Eat, 403)));
            card->setZOrder(countCardTop_Eat);
            
            countCardTop_Eat++;
            
            break;
            
        case kUserBot:
            
            if (!card->isVisible()) {
                card->setVisible(true);
                card->setPosition(getStartPositionCardUserBot_Hit());
            }
            
            card->setScale(0.5);
            card->runAction(CCMoveTo::create(0.3, ccp(457 + disCards / 2 * countCardBot_Eat + disCards / 2 * countCardLeft_Eat, 10)));
            card->setZOrder(countCardBot_Eat);
            
            countCardBot_Eat++;
            
            break;
            
        default:
            break;
    }
	

}

void LayerCardInGame::actionTransferedCard(int fromPosUser, int toPosUser, int pId) {
    int length = arrAllCard->count();
    if (pId >= length) pId = length - 1;
    
    Card *card = getCardByID(pId);
    
    switch (fromPosUser) {
        case kUserMe: case kUserBot:
            countCardMe_Take--;
            countCardBot_Take--;
            break;
            
        case kUserLeft:
            countCardLeft_Take--;
            break;
            
        case kUserRight:
            countCardRight_Take--;
            break;
            
        case kUserTop:
            countCardTop_Take--;
            break;
            
        default:
            break;
    }
    
    switch (toPosUser) {
        case kUserMe:
            
            card->setZOrder(0);
            card->runAction(CCMoveTo::create(0.3, ccp(350 + disCards / 2 * countCardMe_Take, topCard + sizeCard.height)));
            
            countCardMe_Take++;
            
            break;
            
        case kUserLeft: case kUserRight: case kUserTop: case kUserBot:
            
            actionHitCard(toPosUser, pId);
            
            break;
            
        default:
            break;
    }
}

void LayerCardInGame::actionPushCard(int fromPosUser, int toPosUser, int pId) {
    int length = arrAllCard->count();
    if (pId >= length) pId = length - 1;
    
    Card *card = getCardByID(pId);
    
    switch (fromPosUser) {
        case kUserMe: case kUserBot:
            removeCardOnHandByID(pId);
            refreshCardOnHand();
            break;
            
        case kUserLeft:
            if (!card->isVisible()) {
                card->setVisible(true);
                card->setPosition(getStartPositionCardUserLeft_Hit());
            }
            break;
            
        case kUserRight:
            if (!card->isVisible()) {
                card->setVisible(true);
                card->setPosition(getStartPositionCardUserRight_Hit());
            }
            break;
            
        case kUserTop:
            if (!card->isVisible()) {
                card->setVisible(true);
                card->setPosition(getStartPositionCardUserTop_Hit());
            }
            break;
            
        default:
            break;
    }
    
    actionHaPhomByPos(toPosUser, pId);
}

void LayerCardInGame::actionRecommendCard(CCNode *pSender) {
    if (lcRecommendHaPhom.length() <= 2) {
        return;
    }
    
    vector<string> listID; // moi ptu co dang id:id:id
    listID = split(lcRecommendHaPhom, ';');
    
    for (int i = 0 ; i < listID.size(); i++) {
        string list = listID[i];
        
        if (list.length() > 1) {
            vector<string> arrID = split(list, ':');
            
            for (int j = 0; j < arrID.size(); j++) {
                int id = (atoi)(arrID[j].c_str());
                
                Card *card = (Card*) getCardByID(id);
                setCardClick(card);
                
                // đánh dấu bộ phỏm (tối đa là 3 bộ)
                card->setTag(i);
            }
        }
    }
    
    // hiển thị các Button
    LayerPlayGamePhom *layerGame = SceneManager::getSingleton().getLayerGamePhom();
    
    Button *btnSort = (Button*)    layerGame->getButtonByTag(kTagButtonSort);
    Button *btnHit  = (Button*)    layerGame->getButtonByTag(kTagButtonHit);
    Button *btnHaPhom = (Button*)  layerGame->getButtonByTag(kTagButtonHaPhom);
    Button *btnPush = (Button*)    layerGame->getButtonByTag(kTagButtonPush);
    
    btnSort->setEnabled(true);
    btnHit->setEnabled(true);
    btnHaPhom->setEnabled(true);
    btnPush->setEnabled(true);
    
    this->requestRecommendHaPhom = false;
    this->lcRecommendHaPhom = "";
}

void LayerCardInGame::actionHaPhom(vector<int> arrID, vector<int> arrIDPhom) {
    if (arrID.size() != arrIDPhom.size()) return;

    int dem = 0;
	int currentPhom = 0;
    for (int i = 0; i < arrID.size(); i++) {
        int id = arrID.at(i);
		int orderPhom = arrIDPhom.at(i);
		CCLog("actionHaPhom id=%d, orderPhom=%d", id, orderPhom);
        if (currentPhom != orderPhom){
			currentPhom = orderPhom;
			dem=0;
		}

        Card *card = getCardByID(id);
        
        //if (!card->getPhom()) {
            removeCardOnHandByID(id);
            
            card->setVisible(true);
            card->setPhom(true);
            
            card->setZOrder(ZORDER_PHOM + countCardMe_Phom);
            int left = 10 + dem * disCards / 2;
            int top = topCard + (sizeCard.height - card->getContentSize().height / 2);
            top -= (orderPhom-1) * sizeCard.height / 3;
            
            card->runAction(CCMoveTo::create(0.3, ccp(left, top)));
            card->runAction(CCScaleTo::create(0.3, 0.5));
            
            countCardMe_Phom++;
            dem++;
        //}
        
    }
}

void LayerCardInGame::actionHaPhomFromListID(string listID) {
	// index:number:suit:turnedUp:origination:phomID
	/*	 8:9:1:1:4:1;
		21:9:2:1:4:1;
		34:9:3:1:2:1;
		18:6:2:1:4:2;
		19:7:2:1:4:2;
		20:8:2:1:4:2;
	*/


}

void LayerCardInGame::actionHaPhomByPos(int pos, int pID) {
    if (pID >= arrAllCard->count()) pID = arrAllCard->count() - 1;
    Card *card = getCardByID(pID);
    
    switch (pos) {
        case kUserLeft:
            if (!card->getPhom()) {
                if (!card->isVisible()) {
                    card->setPosition(getStartPositionCardUserLeft_Hit());
                    card->setVisible(true);
                }
                
                card->setPhom(true);
                
                card->setZOrder(ZORDER_PHOM + countCardLeft_Phom);
                card->runAction(CCMoveTo::create(0.3, ccp(115 + countCardLeft_Phom * disCards / 2, 243)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardLeft_Phom++;
                //this->countCardLeft_Eat = 0;
            }
            break;
            
        case kUserRight:
            if (!card->getPhom()){
                if (!card->isVisible()) {
                    card->setPosition(getStartPositionCardUserRight_Hit());
                    card->setVisible(true);
                }
                
                card->setPhom(true);
                
                card->setZOrder(10-countCardRight_Phom);
                card->runAction(CCMoveTo::create(0.3, ccp(687 - ((countCardRight_Phom + 1) * disCards / 2), 243)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardRight_Phom++;
                //this->countCardRight_Eat = 0;
            }
            break;
            
        case kUserTop:
            if (!card->getPhom()) {
                if (!card->isVisible()) {
                    card->setPosition(getStartPositionCardUserTop_Hit());
                    card->setVisible(true);
                }
                
                card->setPhom(true);
                
                card->setZOrder(ZORDER_PHOM + countCardTop_Phom);
                card->runAction(CCMoveTo::create(0.3, ccp(457 + countCardTop_Phom * disCards / 2, 403 - sizeCard.height / 2)));
                card->runAction(CCScaleTo::create(0.3, 0.5));
                
                countCardTop_Phom++;
                
                //this->countCardTop_Eat = 0;
            }
            break;
		default: break;
    }
}

void LayerCardInGame::removeCardOnHandByID(int pID) {
    Card *card = getCardByID(pID);
    if (card != NULL) {
        arrCardOnHand->removeObject(card);
    }
}

Card* LayerCardInGame::getCardByID(int pID) {
    int length = arrAllCard->count();
    int indexCard = -1;
    for (int i = 0; i < length; i++) {
        Card *card = (Card*) arrAllCard->objectAtIndex(i);
        if (card->getID() == pID) {
            indexCard = i;
            break;
        }
    }
    
	if (indexCard < 0) return NULL;
    return (Card*)arrAllCard->objectAtIndex(indexCard);
}

void LayerCardInGame::eventListcardNTF(int posUser, string lc) {
    // lc = numberCardOnHand/id:xx:xx:xx:xx;id:xx:xx:xx:xx;...../
    
    // ở đây chỉ thực hiện 2 nhiệm vụ nếu posUser=kUserMe
    // 1. Chia bài (gameStarted = false)
    // 2. Xếp bài (gameStarted = true)
    vector<string> arrString = split(lc, '/');
    int length = arrString.size();
    
    vector<int> arrID_OnHand;
    vector<int> arrID_OnTable;
    vector<int> arrID_Phom;
	vector<int> arrID_PhomID;
    
    if (length >= 2) {
        arrID_OnHand = getIDFromString(arrString[1]);
    }
    
    if (length >= 3) {
        arrID_OnTable = getIDFromString(arrString[2]);
    }
    
    if (length >= 4) {
        arrID_Phom =   getIDFromString(arrString[3]);
		arrID_PhomID = getIDFromString_Last(arrString[3]);
    }
    
    
	bool isPlaySound = false;
	int lengArrPhom = arrID_Phom.size();

    switch (posUser) {
        case kUserMe:
            if (!this->gameStarted) {
                // nhảy vào đây để chia bài (chỉ 1 lần)
                CCLog("LISTCARD  - Chia bai!!!");
                actionDealCard(arrID_OnHand);
        
                this->gameStarted = true;
            }
            else {
                if (this->allowSortCard) {
                    CCLog("LISTCARD  - xep bai");
                    
                    actionSortCard(arrID_OnHand);
                    this->allowSortCard = false;
                }
            }
            
            // phỏm
			if (lengArrPhom > countCardMe_Phom){
				actionHaPhom(arrID_Phom, arrID_PhomID);
				isPlaySound=true;
			}
            
            // chỉ dành cho 1 lần khi người dùng vào lại bàn đang chơi
            if (this->countCardMe_Take == 0) {
                // bài đã đánh
                for (int i = 0; i < arrID_OnTable.size(); i++) {
                    int id = arrID_OnTable[i];
                    actionHitCard(kUserMe, id);
                }
                
                // ẩn nút sẵn sàng và hiện nút sắp xếp
                LayerPlayGamePhom *layerGamePhom = SceneManager::getSingleton().getLayerGamePhom();
                
                Button *btnReady = (Button*) layerGamePhom->getButtonByTag(kTagButtonReady);
                btnReady->setEnabled(false);
                
                Button *btnSort = (Button*) layerGamePhom->getButtonByTag(kTagButtonSort);
                btnSort->setEnabled(true);
            }
            
            
            break;
            
        case kUserLeft:
            
            // phỏm
			if (lengArrPhom > countCardLeft_Phom){
				for (int i = 0; i < arrID_Phom.size(); i++) {
					int id = arrID_Phom[i];
					actionHaPhomByPos(kUserLeft, id);
				}
				isPlaySound=true;
			}
            
            // bài đã đánh
            if (this->countCardLeft_Take == 0) {
                for (int i = 0; i < arrID_OnTable.size(); i++) {
                    int id = arrID_OnTable[i];
                    actionHitCard(kUserLeft, id);
                }
            }
            
            // bài trên tay (khi hết ván hoặc các quân bài đã ăn được)
//             if (this->countCardLeft_Eat == 0)
//                 for (int i = 0; i < arrID_OnHand.size(); i++) {
//                     actionEatCard(-1, kUserLeft, arrID_OnHand[i]);
//                 }
            
			arrIDCardOnHandLeft.clear();
			arrIDCardOnHandLeft = arrID_OnHand;
            
            break;
            
        case kUserRight:
            
            // ha phom
			if (lengArrPhom > countCardRight_Phom){
				for (int i = 0; i < arrID_Phom.size(); i++) {
					int id = arrID_Phom[i];
					actionHaPhomByPos(kUserRight, id);
				}
				isPlaySound=true;
			}

            // bài đã đánh
            if (this->countCardRight_Take == 0) {
                for (int i = 0; i < arrID_OnTable.size(); i++) {
                    int id = arrID_OnTable[i];
                    actionHitCard(kUserRight, id);
                }
            }
            
            // bài trên tay (các quân bài đã ăn được)
//             if (this->countCardRight_Eat == 0)
//                 for (int i = 0; i < arrID_OnHand.size(); i++) {
//                     actionEatCard(-1, kUserRight, arrID_OnHand[i]);
//                 }
            
				arrIDCardOnHandRight.clear();
				arrIDCardOnHandRight = arrID_OnHand;

            break;
            
        case kUserTop:
            
            // ha phom
			if (lengArrPhom > countCardTop_Phom){
				for (int i = 0; i < arrID_Phom.size(); i++) {
					int id = arrID_Phom[i];
					actionHaPhomByPos(kUserTop, id);
				}
				isPlaySound=true;
			}
            
            // bài đã đánh
            if (this->countCardTop_Take == 0) {
                for (int i = 0; i < arrID_OnTable.size(); i++) {
                    int id = arrID_OnTable[i];
                    actionHitCard(kUserTop, id);
                }
            }
            
            // bài trên tay (các quân bài đã ăn được)
//             if (this->countCardTop_Eat == 0)
//                 for (int i = 0; i < arrID_OnHand.size(); i++) {
// 					actionEatCard(-1, kUserTop, arrID_OnHand[i]);
// 				}
            
				arrIDCardOnHandTop.clear();
				arrIDCardOnHandTop = arrID_OnHand;
            
            break;
            
        default:
            break;
    }

	if (isPlaySound) playSound("ha_phom.mp3");
}

void LayerCardInGame::event_EXT_SRVNTF_RECOMMENDED_CARDSETS(string lc) {
    // lưu trữ để chờ đợi hàm refresfCardOnHand() thực hiện runAction xong,
    // khi đó ở đó sẽ làm tiếp cv :).
    lcRecommendHaPhom = lc;
    requestRecommendHaPhom = true;
}

CCPoint LayerCardInGame::getPointCardInCenter() {
    return CCPoint(WIDTH_DESIGN / 2 - sizeCard.width / 2, HEIGHT_DESIGN / 2 - sizeCard.height / 2);
}

CCPoint LayerCardInGame::getStartPositionCardUserLeft_Hit(){
    return CCPoint(10, HEIGHT_DESIGN / 2 - sizeCard.height / 2);
}

CCPoint LayerCardInGame::getStartPositionCardUserRight_Hit() {
    return CCPoint(WIDTH_DESIGN - 10 - sizeCard.width, HEIGHT_DESIGN / 2 - sizeCard.height / 2);
}

CCPoint LayerCardInGame::getStartPositionCardUserTop_Hit() {
    return CCPoint(WIDTH_DESIGN / 2 - sizeCard.width / 2, HEIGHT_DESIGN - 10 - sizeCard.height);
}

CCPoint LayerCardInGame::getStartPositionCardUserBot_Hit() {
    return CCPoint(WIDTH_DESIGN / 2 - sizeCard.width / 2, 10);
}

CCPoint LayerCardInGame::getStartPositionCardByPos(int pos) {
    switch (pos) {
        case kUserLeft:
            return getStartPositionCardUserLeft_Hit();
            break;
            
        case kUserRight:
            return getStartPositionCardUserRight_Hit();
            break;
            
        case kUserTop:
            return getStartPositionCardUserTop_Hit();
            break;
            
        case kUserBot:
            return getStartPositionCardUserBot_Hit();
            break;
            
        default: return getPointCardInCenter(); break;
    }
}

CCPoint LayerCardInGame::getStartPositionCardUserLeft_Hit_TienLen() {
    return ccp(110, 216);
}

CCPoint LayerCardInGame::getStartPositionCardUserRight_Hit_TienLen() {
    return ccp(647, 216);
}

CCPoint LayerCardInGame::getStartPositionCardUserTop_Hit_TienLen() {
    return ccp(454, 343);
}

CCPoint LayerCardInGame::getStartPositionCardUserBot_Hit_TienLen() {return ccp(0, 0);}

CCPoint LayerCardInGame::getStartPositionCardByPos_TienLen(int pos) {
    switch (pos) {
        case kUserLeft:
            return getStartPositionCardUserLeft_Hit_TienLen();
            break;
            
        case kUserRight:
            return getStartPositionCardUserRight_Hit_TienLen();
            break;
            
        case kUserTop:
            return getStartPositionCardUserTop_Hit_TienLen();
            break;
            
        case kUserBot:
            return getStartPositionCardUserBot_Hit_TienLen();
            break;
            
        default: return getPointCardInCenter(); break;
    }
}


void LayerCardInGame::setCountCardByPos(int pos, int count) {
    string countString = to_string(count);
    CCLabelTTF *label;
    
    switch (pos) {
        case kUserLeft:
            cardBackLeft->setVisible(count>0);
            label = (CCLabelTTF*) cardBackLeft->getChildByTag(kTagCountCard);
            break;
            
        case kUserRight:
            cardBackRight->setVisible(count>0);
            label = (CCLabelTTF*) cardBackRight->getChildByTag(kTagCountCard);
            break;
            
        case kUserTop:
            cardBackTop->setVisible(count>0);
            label = (CCLabelTTF*) cardBackTop->getChildByTag(kTagCountCard);
            break;
            
        default: label=NULL; break;
    }
    
    if (label != NULL) {
        label->setString(countString.c_str());
        CCSize sizeLabel = label->getContentSize();
        CCSize sizeCard = cardBackLeft->getContentSize();
        CCPoint pointCenter = ccp((sizeCard.width - sizeLabel.width) / 2, (sizeCard.height - sizeLabel.height) / 2);
        label->setPosition(pointCenter);
    }
}

void LayerCardInGame::showCardOnHandAll() {
	showCardOnHandByPos_Arr(kUserLeft, arrIDCardOnHandLeft);
	showCardOnHandByPos_Arr(kUserRight, arrIDCardOnHandRight);
	showCardOnHandByPos_Arr(kUserTop, arrIDCardOnHandTop);
}

void LayerCardInGame::showCardOnHandByPos_Arr(int kUser, vector<int> arrID) {
	for (int i = 0; i < arrID.size(); i++)
	{
		actionEatCard(-1, kUser, arrID.at(i));
	}
}

void LayerCardInGame::showCardOnHandByPos_List(int kUser, string lc) {

	vector<string> arrIDString = split(lc, ',');
	vector<int>	   arrID;

	for (int i = 0; i < arrIDString.size(); i++)
	{
		int id = atoi(arrIDString.at(i).c_str());
		if (id > 0) arrID.push_back(id);
	}

	showCardOnHandByPos_Arr(kUser, arrID);
}