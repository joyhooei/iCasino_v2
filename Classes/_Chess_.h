//
//  _Chess_.h
//  iCasinov2
//
//  Created by Thanhhv on 6/5/14.
//
//

#ifndef __iCasinov2___Chess___
#define __iCasinov2___Chess___

#include <iostream>
#include "cocos2d.h"
#include "AllData.h"
USING_NS_CC;
using namespace std;

class Chess : public CCSprite {
private:
    int id_name;
    int id_pos;
    int id_pos_init;
	int side; // DARK or LIGHT
	int name; // PAWN, BISHOP, ...

    bool isClicked;

	enum NAME {
		DARK = 1,
		LIGHT = 2,
		PAWN = 0,
		BISHOP = 1,
		ELEPHANT = 2,
		KNIGHT = 3,
		CANNON = 4,
		ROOK = 5,
		KING = 6,
		EMPTY = 7,
	};
    
public:
    //Chess(int id_name, int id_pos);
	Chess(int side, int name, int id_pos);
    ~Chess();
    
    // setter, getter
    void setIDName(int id);
    int  getIDName();
    void setIDPos(int id);
    int  getIDPos();
    int  getIDPosInit();
	int  getName();
	int  getSide();
    
    void setClick(bool isClick);
    
	string getURL();
    string getURL(int id);
    string getURL_hover();
};

#endif /* defined(__iCasinov2___Chess___) */
