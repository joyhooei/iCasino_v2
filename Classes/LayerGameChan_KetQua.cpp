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
#include "GameServer.h"

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
	img->loadTexture("frame_thongbao.png");
	img->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2));
	resuiltKQ->addWidget(img);

	btnClose = UIButton::create();
	btnClose->loadTextures("btnChanClose.png","btnChanClose_press.png","");
	btnClose->setPosition(ccp(WIDTH_DESIGN / 2, img->getPositionY() - img->getContentSize().height / 2));

	UILabelBMFont *title = UILabelBMFont::create();
	title->setFntFile("tttt.fnt");
	title->setText("Đóng");
	title->setColor(ccWHITE);
	title->setScale(0.7);
	title->setPositionY(5.0);
	btnClose->addChild(title);

	btnClose->setEnabled(true);
	btnClose->addTouchEventListener(this, toucheventselector(LayerGameChan_KetQua::btnClose_LayerResuilt));
	resuiltKQ->addWidget(btnClose);

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

	CCLog("winner user: %s", arrResuilt[2].c_str());
	CCLog("den lang user: %s", arrResuilt[3].c_str());
	CCLog("win cuoc sac: %s", arrResuilt[4].c_str());
	CCLog("den lang cuoc sac: %s", arrResuilt[5].c_str());
	CCLog("Tong diem: %s", arrResuilt[6].c_str());
	CCLog("danh sach tinh tien: %s", arrResuilt[7].c_str());
	if (arrResuilt.size() >= 9)
	{
		CCLog("Cac cuoc thieu: %s", arrResuilt[8].c_str());
	}
	if (arrResuilt.size() >= 10)
	{
		CCLog("Cac cuoc co ga: %s", arrResuilt[9].c_str());
	}
	

	if(atoi(arrResuilt[6].c_str()) == 0){
		UILabel *ttt = UILabel::create();
		ttt->setText("Hòa cả làng");
		ttt->setFontSize(20);
		ttt->setColor(ccRED);
		img->addChild(ttt);
		return;
	}

	string str = "";

	//Xác định người thắng
	if (strcmp(arrResuilt[2].c_str(), "") != 0)
	{
		str += getNamePlayer(arrResuilt[2]) + " xướng: " + getCuoc(arrResuilt[4], true) + "\n";
		if (arrResuilt.size() >= 10 && arrResuilt[9] != "")
		{
			str += "Cước có gà: "+getCuoc(arrResuilt[9], false) + "\n";
		}
	}

	//Xác định người thua
	if (strcmp(arrResuilt[3].c_str(), "") != 0){
		str += getNamePlayer(arrResuilt[3]) + " Đền làng: " + getCuoc(arrResuilt[5], true) + (getCuoc(arrResuilt[8], true) == "" ? "" : "\n");
		if (strcmp(arrResuilt[8].c_str(), "") != 0)
		{
			str += "Xướng thiếu " + getCuoc(arrResuilt[8], true) + "\n";
		}
	}
	
	str += "Tổng điểm: "+arrResuilt[6];

	//Tính tiền
	string strScore = "";
	if (strcmp(arrResuilt[7].c_str(), "") != 0)
	{
		vector<string> arrTinhtien = splitString(arrResuilt[7],'/');
		for (int i = 0; i < arrTinhtien.size(); i++)
		{
			vector<string> info = splitString(arrTinhtien[i],':');
			strScore += getNamePlayer(info[0]) + ": " + info[2] + "\n";
		}
	}

	UILabel *content1 = UILabel::create();
	content1->setText(str.c_str());
	content1->setFontSize(17);
	content1->setColor(ccRED);
	content1->setAnchorPoint(ccp(0.5, 0));
	content1->setPosition(ccp(0, 5));
	img->addChild(content1);

	UILabel *content = UILabel::create();
	content->setText(strScore.c_str());
	content->setFontSize(17);
	content->setColor(ccRED);
	content->setAnchorPoint(ccp(0.5, 1));
	img->addChild(content);

} 

string LayerGameChan_KetQua::getNamePlayer(string uid){
	boost::shared_ptr<Room> room = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	if (room == NULL)
	{
		return uid;
	}
	
	boost::shared_ptr<User> user = room->GetUserByName(uid);
	if (user == NULL)
	{
		return uid;
	}
	boost::shared_ptr<string> name = user->GetVariable("aN")->GetStringValue();
	return name->c_str();
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

// gửi bản tin thông báo kết quả ván chơi xuống các client
// format: gameid;gameEndReason;winnerUserName;denLangUserName;winCuocSacList;denLangCuocSacList;totalScore;danhSáchTínhTiền;cácCướcXướngThiếu;cácCướcGà
// trong đó winCuocSacList, denLangCuocSacList, cácCướcXướngThiếu và cácCướcGà có định dạng: cuoc1:cuoc2:cuocN:...
// danhSáchTínhTiền: cộng trừ tiền cho các player, thông tin mỗi player có format username:coinReason:coinChange, thông tin mỗi player cách nhau bởi kí tự '/'
// mẫu: 1;1;phanpc;;2:6;;6;phanpc:0:27000/phanpc1:6:-30000
//

string LayerGameChan_KetQua::getCuoc(string cuoc, bool type){
	//30 ký tự trong 1 dòng
	vector<string> arr = splitString(cuoc, ':');
	string str = "";
	for (int i = 0; i < arr.size(); i++)
	{
		if (str.length() > 13)
		{
			str += "\n";
		}
		if (i == arr.size() - 1)
		{
			if (type == true)
			{
				str += identifyCuoc_sac(arr[i]);
			}
			else
			{
				str += identifyCuoc_Ga(arr[i]);
			}
		}
		else
		{
			if (type == true)
			{
				str += identifyCuoc_sac(arr[i]) + ", ";
			}
			else
			{
				str += identifyCuoc_Ga(arr[i]) + ", ";
			}
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
		return "Kính Tứ Chi";
	case 10:
		return "Thập thành";
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

string LayerGameChan_KetQua::identifyCuoc_Ga(string _cuoc){
	int cuoc = atoi(_cuoc.c_str());
	switch(cuoc){
	case 0:
		return "Ù bòn bạch thủ";
	case 1:
		return "Ù Bòn Bạch Thủ Chi";
	case 2:
		return "Thập Thành";
	case 3:
		return "Kính Tứ Chi";
	case 4:
		return "Bạch Định";
	case 5:
		return "Tám đỏ";
	case 6:
		return "Bạch Thủ Chi";
	case 7:
		return "Hoa rơi cửa phật";
	case 8:
		return "Cá lội sân đình";
	case 9:
		return "Nhà lầu xe hơi, hoa rơi cửa phật";
	case 10:
		return "Chì Bạch thủ";
	case 11:
		return "Chì Bạch thủ Chi";
	case 12:
		return "Ngư ông bắt cá";
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