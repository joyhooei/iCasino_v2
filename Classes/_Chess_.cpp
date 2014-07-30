//
//  _Chess_.cpp
//  iCasinov2
//
//  Created by Thanhhv on 6/5/14.
//
//

#include "_Chess_.h"

/*
Chess::Chess(int id_name, int id_pos) {
    this->id_name = id_name;
    this->id_pos = id_pos;
    this->id_pos_init = id_pos;
    
    string url = getURL(id_name);
    this->initWithFile(url.c_str());
}*/

Chess::Chess(int side, int name, int id_pos) {
	this->side = side;
	this->name = name;
	this->id_pos = id_pos;
	this->id_pos_init = id_pos;

	this->initWithFile(getURL().c_str());
}

Chess::~Chess(){}

// setter, getter
void Chess::setIDName(int id) {
    this->id_name = id;
}

int  Chess::getIDName() {
    return this->id_name;
}

void Chess::setIDPos(int id) {
    this->id_pos = id;
}

int  Chess::getIDPos() {
    return this->id_pos;
}

int  Chess::getIDPosInit() {
    return this->id_pos_init;
}

int  Chess::getName() {
	return this->name;
}

int  Chess::getSide() {
	return this->side;
}

void Chess::setClick(bool isClick) {
    if (isClick) {
        this->initWithFile(getURL_hover().c_str());
    }
    else {
        this->initWithFile(getURL().c_str());
    }
}

string Chess::getURL() {
	string sideString;
	string nameString;

	switch (this->side) {
		case DARK:
			sideString = "red";
			break;
		case LIGHT:
			sideString = "blue";
	}

	/*int PAWN = 0;   // tốt
	int BISHOP = 1;   // sỹ
	int ELEPHANT = 2; // tượng
	int KNIGHT = 3;   // mã
	int CANNON = 4;	  // pháo
	int ROOK = 5;	  // xe
	int KING = 6;	  // tướng
	int EMPTY = 7;*/  
	switch (this->name) {
		case PAWN:
			nameString = "tot";
			break;
		case BISHOP:
			nameString = "si";
			break;
		case ELEPHANT:
			nameString = "tuongj";
			break;
		case KNIGHT:
			nameString = "ma";
			break;
		case CANNON:
			nameString = "phao";
			break;
		case ROOK:
			nameString = "xe";
			break;
		case KING:
			nameString = "tuong";
			break;
	}

	return "chess/" + nameString + "_" + sideString + ".png";
}

string Chess::getURL(int id) {
    string url = "chess/";
    switch (id) {
        case kXeXanh:
            url += "xe_blue.png";
            break;
        case kMaXanh:
            url += "ma_blue.png";
            break;
        case kTuongjXanh:
            url += "tuongj_blue.png";
            break;
        case kSiXanh:
            url += "si_blue.png";
            break;
        case kTuongXanh:
            url += "tuong_blue.png";
            break;
        case kPhaoXanh:
            url += "phao_blue.png";
            break;
        case kTotXanh:
            url += "tot_blue.png";
            break;
        case kXeDo:
            url += "xe_red.png";
            break;
        case kMaDo:
            url += "ma_red.png";
            break;
        case kTuongjDo:
            url += "tuongj_red.png";
            break;
        case kSiDo:
            url += "si_red.png";
            break;
        case kTuongDo:
            url += "tuong_red.png";
            break;
        case kPhaoDo:
            url += "phao_red.png";
            break;
        case kTotDo:
            url += "tot_red.png";
            break;
    }
    
    return url;
}

string Chess::getURL_hover() {
    string sideString;
	string nameString;

	switch (this->side) {
		case DARK:
			sideString = "red";
			break;
		case LIGHT:
			sideString = "blue";
	}
 
	switch (this->name) {
		case PAWN:
			nameString = "tot";
			break;
		case BISHOP:
			nameString = "si";
			break;
		case ELEPHANT:
			nameString = "tuongj";
			break;
		case KNIGHT:
			nameString = "ma";
			break;
		case CANNON:
			nameString = "phao";
			break;
		case ROOK:
			nameString = "xe";
			break;
		case KING:
			nameString = "tuong";
			break;
	}

	return "chess/hover/" + nameString + "_" + sideString + ".png";
}