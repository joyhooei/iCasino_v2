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
    string name;

    bool isClicked;
    
public:
    Chess(int id_name, int id_pos);
    ~Chess();
    
    // setter, getter
    void setIDName(int id);
    int  getIDName();
    void setIDPos(int id);
    int  getIDPos();
    int  getIDPosInit();
    
    void setClick(bool isClick);
    
    string getURL(int id);
    string getURL_hover(int id);
};

#endif /* defined(__iCasinov2___Chess___) */
