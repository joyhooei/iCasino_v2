//
//  _Chess_.cpp
//  iCasinov2
//
//  Created by Thanhhv on 6/5/14.
//
//

#include "_Chess_.h"

Chess::Chess(int id_name, int id_pos) {
    this->id_name = id_name;
    this->id_pos = id_pos;
    this->id_pos_init = id_pos;
    
    string url = getURL(id_name);
    this->initWithFile(url.c_str());
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

void Chess::setClick(bool isClick) {
    if (isClick) {
        this->initWithFile(getURL_hover(this->id_name).c_str());
    }
    else {
        this->initWithFile(getURL(this->id_name).c_str());
    }
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

string Chess::getURL_hover(int id) {
    string url = "chess/hover/";
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