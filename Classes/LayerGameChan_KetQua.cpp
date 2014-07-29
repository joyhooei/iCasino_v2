//
//  LayerGameChan_KetQua.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerGameChan_KetQua.h"
#include "mUtils.h"
#include "AllData.h"

LayerGameChan_KetQua::LayerGameChan_KetQua()
{

}

LayerGameChan_KetQua::~LayerGameChan_KetQua()
{
	this->removeAllChildrenWithCleanup(true);
	CCLOG("Jumpe to Deconstructor LayerGameChan_KetQua");
}

bool LayerGameChan_KetQua::init(){
	if (!CCLayer::init())
	{
		return false;
	}

	this->setAnchorPoint(ccp(0,0));
	this->setPosition(ccp(0,0));

	resuiltKQ = UILayer::create();
	resuiltKQ->setAnchorPoint(ccp(0,0));
	resuiltKQ->setPosition(ccp(0,0));
	this->addChild(resuiltKQ);

	img = UIImageView::create();
	img->loadTexture("frame-wood.png");
	img->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2));
	resuiltKQ->addWidget(img);

	btnClose = UIButton::create();
	btnClose->loadTextures("btnChanClose.png","btnChanClose_press.png","");
	btnClose->setPosition(ccp(WIDTH_DESIGN / 2, img->getPositionY() - img->getContentSize().height / 2 + 13));
	btnClose->setTitleText("Đóng");
	btnClose->setEnabled(true);
	btnClose->addTouchEventListener(this, toucheventselector(LayerGameChan_KetQua::btnClose_LayerResuilt));
	resuiltKQ->addWidget(btnClose);

	UILabel *title = UILabel::create();
	title->setText("Kết quả");
	title->setFontSize(40);
	title->setColor(ccRED);
	title->setPosition(ccp(WIDTH_DESIGN / 2,HEIGHT_DESIGN / 2 + img->getContentSize().height / 2 - 40));
	resuiltKQ->addWidget(title);

	return true;
}

void LayerGameChan_KetQua::btnClose_LayerResuilt(CCObject *sender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		this->removeFromParentAndCleanup(true);
	}
}

void LayerGameChan_KetQua::displayResuilt(string resuilt){
	vector<string> arrResuilt = splitString(resuilt,';');
	string str = "";
	if (arrResuilt.size() == 0)
	{
		str += "Hoa ca lang";
	}

	if (strcmp(arrResuilt[2].c_str(), "") != 0)
	{
		str += arrResuilt[2] + " xuong: " + getCuoc(arrResuilt[4]) + "\n";
	}

	if (strcmp(arrResuilt[3].c_str(), "") != 0){
		str += arrResuilt[4] + " den lang: " + getCuoc(arrResuilt[5]) + "\n";
	}
	

	if (strcmp(arrResuilt[7].c_str(), "") != 0)
	{
		vector<string> arrTinhtien = splitString(arrResuilt[7],'/');
		for (int i = 0; i < arrTinhtien.size(); i++)
		{
			vector<string> info = splitString(arrTinhtien[i],':');
			str += info[0] + ": " + info[2] + "\n";
		}
	}

	CCLOG(str.c_str());

	UILabel *content = UILabel::create();
	content->setText(str.c_str());
	content->setFontSize(20);
	content->setColor(ccRED);
	img->addChild(content);
}

vector<string> LayerGameChan_KetQua::splitString(string &S,const char &str){
	vector<string> arrStr;
	string::iterator t,t2;
	for(t=S.begin();t<S.end();){
		// Lặp từ vị trí bắt đầu
		t2=find(t, S.end(),str); // Tìm vị trí space ' ' đầu tiên
		//kể từ vị trí t
		if(t!=t2)
			arrStr.push_back(string(t,t2));
		else  if( t2 != S.end() )
			arrStr.push_back("");
		if( t2 == S.end() )
			break;
		t=t2+1; // chuyển sang vị trí sau
	}
	return arrStr;
}

// format: 0-gameid;1-gameEndReason;2-winnerUserName;3-denLangUserName;4-winCuocSacList;5-denLangCuocSacList;6-totalScore;7-danhSáchTínhTiền
// trong đó winCuocSacList hoặc denLangCuocSacList có định dạng: cuoc1:cuoc2:cuocN:...
// danhSáchTínhTiền: cộng trừ tiền cho các player, thông tin mỗi player có format username:coinReason:coinChange, thông tin mỗi player cách nhau bởi kí tự '/'
// mẫu: 1;1;phanpc;;2:6;;6;phanpc:0:27000/phanpc1:6:-30000

string LayerGameChan_KetQua::getCuoc(string cuoc){
	vector<string> arr = splitString(cuoc, ',');
	string str = "";
	for (int i = 0; i < arr.size(); i++)
	{
		if (i == arr.size() - 1)
		{
			str += identifyCuoc_sac(arr[i]);
		}
		else
		{
			str += identifyCuoc_sac(arr[i]) + ", ";
		}
	}
	return str;
}

string LayerGameChan_KetQua::identifyCuoc_sac(string _cuoc){
	int cuoc = atoi(_cuoc.c_str());
	switch(cuoc){
	case 0:
		return "Xuông";
	case 1:
		return "Thông";
	case 2:
		return "Chì";
	case 3:
		return "Thiên Ù";
	case 4:
		return "Địa Ù";
	case 5:
		return "Tôm";
	case 6:
		return "Lèo";
	case 7:
		return "Bạch Định";
	case 8:
		return "Tám Đỏ";
	case 9:
		return " Kính Tứ Chi";
	case 10:
		return " Thập thành";
	case 11:
		return "Có Thiên Khai";
	case 12:
		return "Ăn Bòn";
	case 13:
		return "Ù Bòn";
	case 14:
		return "Có Chíu";
	case 15:
		return "Chíu Ù";
	case 16:
		return "Bạch Thủ";
	case 17:
		return "Hoa Rơi cửa phật";
	case 18:
		return "Nhà lầu xe hơi, hoa rơi cửa phật";
	case 19:
		return "Cá lội sân đình";
	case 20:
		return "Cá nhảy đầu thuyền";
	case 21:
		return "Chùa đổ nát hoa";
	case 22:
		return "Đôi Lèo";
	case 23:
		return "Đôi tám đỏ";
	case 24:
		return "Đôi Tôm";
	case 25:
		return "Bạch thủ Chi";
	}
	return "";
}

void LayerGameChan_KetQua::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerGameChan_KetQua::onExit()
{
	CCLayer::onExit();
}