//
//  CardChan.h
//  AppDemo
//
//  Created by DauA on 5/13/14.
//
//

#ifndef __AppDemo__CardChan__
#define __AppDemo__CardChan__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class CardChan : public ImageView{
private:
	int id_card;
	bool flag;
	//for chan
	int number;
	int suite;
public:
	CardChan();
	~CardChan();
	CREATE_FUNC(CardChan);
	bool init();
	int getID();
	bool getFlag();
	void setID(int n);
	void setFlag(bool b);
	void setSizeCard(float toWidth,float toHeight);
	//for chan
	void setNumber(int num);
	void setSuite(int sui);
	int getNumber();
	int getSuite();
};
#endif /* defined(__AppDemo__CardChan__) */
