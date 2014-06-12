//
//  Card.h
//  iCasinoCard
//
//  Created by Thanhhv on 5/8/14.
//
//

#ifndef __iCasinoCard__Card__
#define __iCasinoCard__Card__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Card : public CCSprite
{
private:
    bool isTouched;
    bool isClicked;
    bool isPhom;
    bool isEat;
    
    CCSize sizeCard;
    string url;
    int id;
    float scaleX;
    float scaleY;
    
public:
    
    Card(const char *fileName);
    void initialize();
    
    static Card* createCardWithFileName(const char *fileName);
    
    // call when reset game!
    void resetStatus();
    
    void setTouched(bool isTouched);
    bool getTouched();
    
    void setClicked(bool isClicked);
    bool getClicked();
    
    void setPhom(bool isPhom);
    bool getPhom();
    
    void setEat(bool isEat);
    bool getEat();
    //void setEatEffect();
    
    void setSize(float wid, float hei);
    CCSize getSize();
    
    void setURL(string url);
    string getURL();
    
    void setID(int id);
    int getID();
    
    void setScaleCard(float scaleX, float scaleY);
    CCSize getScaleCard();
    float getScaleCardX();
    float getScaleCardY();
    
    void setCardAte();
    void setCardCanEat();
};

#endif /* defined(__iCasinoCard__Card__) */
