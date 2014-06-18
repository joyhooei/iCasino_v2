//
//  _Card_inGame_.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/19/14.
//
//

#ifndef __iCasino_v2___Card_inGame___
#define __iCasino_v2___Card_inGame___

#include <iostream>
#include "cocos2d.h"
#include "AllData.h"

#include "_Card_.h"

USING_NS_CC;
using namespace std;

class LayerCardInGame : public CCLayer
{
public:
	~LayerCardInGame();
	void onExit();
    bool init();
    CREATE_FUNC(LayerCardInGame);
    
    // touches event
    CCPoint convertPoint(CCPoint point);
    float   getDisPoint(CCPoint p1, CCPoint p2);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    void initGame();
    void resetGame();
    
    //
    void initCardByPhom();
    void initCardByTienLen();
    
    // actions card
    // chia bai
    void actionDealCard(vector<int> arrCardID);
    
    // xep bai
    void actionSortCard(vector<int> arrCardID);
    void actionSortCardByTienLen(); // tam thoi
    void delayAllowSortCard();
    
    // danh bai
    void actionHitCard(int posUser, int pId);
    void actionHitCardByTienLen(int posUser, vector<int> arrID);
    
    // boc bai
    void actionGiveCard(int posUser, int pId);
    void callbackGiveCard(CCNode *pSender);
    
    // an bai
    void actionEatCard(int fromPosUser, int toPosUser, int pId);
    
    // chuyen bai
    void actionTransferedCard(int fromPosUser, int toPosUser, int pId);
    
    // gui bai
    void actionPushCard(int fromPosUser, int toPosUser, int pId);
    
    // gợi ý hạ phỏm
    void actionRecommendCard(CCNode *pSender);
    
    // hạ phỏm
    void actionHaPhom(vector<int> arrID);
    void actionHaPhomByPos(int pos, int pID);
    
    // ----
    
    // phom
    vector<string> split(string &S, const char &str);
    vector<int> getIDFromString(string pListCard);
    vector<int> getIDFromString_TienLen(string pList);
    int getCountCardOnHand();
    int getCountCardTaken();
    
    // event-server
    void eventListcardNTF(int posUser, string lc); // nhận ds các ID, nhiệm vụ: chia bài, xếp bài,
    
    void event_EXT_SRVNTF_RECOMMENDED_CARDSETS(string lc);
    
    void refreshCardOnHand();
    void refreshCardOnHand(bool isRefreshTop);
    void refreshCardOnHand(float delayPerAction);
    void setCardClick(Card* card);
    bool isTouchedCard_Tail(Card *card, CCPoint tap);
    bool isTouchedCard_notTail(Card *card, CCPoint tap);
    string getURL_byID(int pID);
    string getURL_byID_TienLen(int pID);
    
    vector<int> getIdCardByClicked();
    
    // hạ phỏm
    // trả về 1 mảng chứa các listID: [0]:="id:id:id"; [1]:="id:id:id"
    vector<string> getID_HaPhom();
    
    Card* getCardByID(int pID);
    
    void removeCardOnHandByID(int pID);
    
    void setIdCardCanEat(int id);
    int getIdCardCanEat();
    
    void setGameStarted(bool isStarted);
    bool getGameStarted();
    
    void setAllowSortCard(bool isAllow);
    bool getAllowSortCard();
    
    // Phom
    CCPoint getPointCardInCenter();
    CCPoint getStartPositionCardUserLeft_Hit();
    CCPoint getStartPositionCardUserRight_Hit();
    CCPoint getStartPositionCardUserTop_Hit();
    CCPoint getStartPositionCardUserBot_Hit();
    CCPoint getStartPositionCardByPos(int pos);
    // TienLen
    CCPoint getStartPositionCardUserLeft_Hit_TienLen();
    CCPoint getStartPositionCardUserRight_Hit_TienLen();
    CCPoint getStartPositionCardUserTop_Hit_TienLen();
    CCPoint getStartPositionCardUserBot_Hit_TienLen();
    CCPoint getStartPositionCardByPos_TienLen(int pos);
    
    void setCountCardByPos(int pos, int count);

	void showCardOnHandAll();
	void showCardOnHandByPos_Arr(int kUser, vector<int> arrID);
	void showCardOnHandByPos_List(int kUser, string lc);

private:
	// lưu các ID-Card để cuối ván hiển thị
	vector<int> arrIDCardOnHandLeft;
	vector<int> arrIDCardOnHandRight;
	vector<int> arrIDCardOnHandTop;

    float startLeft;
    float startTop;
    float scaleApp;
    float disCards;
    float topCard;
    
    CCSize sizeScreen;
    CCSize disTouchBegan;
    CCSize sizeCard;
    CCPoint pointTouchBegan;
    
    // [Can changes]
    // count
    int countCardMe_Take;
    int countCardLeft_Take;
    int countCardRight_Take;
    int countCardTop_Take;
    int countCardBot_Take;
    //
    int countCardMe_Eat;
    int countCardLeft_Eat;
    int countCardRight_Eat;
    int countCardTop_Eat;
    int countCardBot_Eat;
    
    int countCardMe_Phom;
    int countCardLeft_Phom;
    int countCardRight_Phom;
    int countCardTop_Phom;
    int countCardBot_Phom;
    
    int countMe_Phom;
    
    // [Const]
    int ZORDER_PHOM;
    int ZORDER_TAKE;
    int ZORDER_HAND;
    
    CCArray *arrAllCard;
    CCArray *arrCardOnHand;
    
    int idCardCanEat;
    int countTouched;
    int indexCardCurrent;
    int indexCardTarget;
    
    bool isClickCard;    // click or move card - default: click card
    bool gameStarted;
    bool allowSortCard;  // kiểm soát khi người dùng ấn "xếp bài"
    bool requestRecommendHaPhom;  // =true thì sẽ gợi ý hạ phỏm
    
    string lcRecommendHaPhom;
    
    // số bài trên tay
    CCSprite *cardBackLeft, *cardBackRight, *cardBackTop;
};

#endif /* defined(__iCasino_v2___Card_inGame___) */
