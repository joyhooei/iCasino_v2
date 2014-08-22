//
//  LayerGameChan_XuongU2.cpp
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#include "LayerGameChan_XuongU2.h"
#include "mUtils.h"
#include "CustomTableViewCell.h"
#include "Requests/ExtensionRequest.h"

#include "SceneManager.h"

using namespace cocos2d;

LayerGameChan_XuongU2::LayerGameChan_XuongU2()
{
	lblTime = NULL;
	lblTitle = NULL;
	lstCuoc.push_back("Xuông");
	lstCuoc.push_back("Thông");
	lstCuoc.push_back("Chì");
	lstCuoc.push_back("Thiên Ù");
	lstCuoc.push_back("Địa Ù");
	lstCuoc.push_back("Tôm");
	lstCuoc.push_back("Lèo");
	lstCuoc.push_back("Bạch Định");
	lstCuoc.push_back("Tám Đỏ");
	lstCuoc.push_back("Kính Tứ Chi");
	lstCuoc.push_back("Thập Thành");
	lstCuoc.push_back("Thiên Khai");
	lstCuoc.push_back("Ăn Bòn");
	lstCuoc.push_back("Ù Bòn");
	lstCuoc.push_back("Có Chíu");
	lstCuoc.push_back("Chíu Ù");
	lstCuoc.push_back("Bạch Thủ");
	lstCuoc.push_back("Hoa rơi");
	lstCuoc.push_back("NLXH, HRCP");
	lstCuoc.push_back("Cá lội SĐ");
	lstCuoc.push_back("Cá nhảy ĐT");
	lstCuoc.push_back("Chùa đổ NH");
	lstCuoc.push_back("Đôi Lèo");
	lstCuoc.push_back("2 Tám đỏ");
	lstCuoc.push_back("2 Tôm");
	lstCuoc.push_back("Bạch Thủ Chi");
    //
	ListCuoc = CCArray::create();
	ListCuoc->retain();
    GameServer::getSingleton().addListeners(this);
}

LayerGameChan_XuongU2::~LayerGameChan_XuongU2()
{
	ListCuoc->removeAllObjects();
	ListCuoc->release();
    GameServer::getSingleton().removeListeners(this);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerGameChan_XuongU2::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnXuong", LayerGameChan_XuongU2::onButtonXuong);
    return NULL;
}

void LayerGameChan_XuongU2::onButtonXuong(CCObject* pSender)
{
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
 	boost::shared_ptr<ISFSObject> params (new SFSObject());

	CCArray *arrCuoc = CCArray::create();
	string str = "";
	int _count = 0;
	for (int i = 0; i < ListCuoc->count(); i++)
	{
		ButtonXuong *btn = (ButtonXuong*)ListCuoc->objectAtIndex(i);
		if (btn->getClicked())
		{
			arrCuoc->addObject(btn);
			_count++;
		}
	}

	if (_count <= 0)
	{
		str = "";
		CCLOG("Chua chon cuoc xuong !");
		return;
	}
	else
	{
		for (int i = 0; i < (int)arrCuoc->count(); i++)
		{
			ButtonXuong *itemXuong = (ButtonXuong*)arrCuoc->objectAtIndex(i);
			if (i < arrCuoc->count() - 1)
			{
				str+=boost::to_string(itemXuong->getID())+":";
			}
			else
				str+=boost::to_string(itemXuong->getID());
		}
	}
	
	CCLOG("str = %s",str.c_str());
	params->PutUtfString("ucsac",str);
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rquanou",params,lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
	this->removeFromParentAndCleanup(true);
    CCLOG("onButtonXuong ");
}
// CCBMemberVariableAssigner interface
bool LayerGameChan_XuongU2::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCLOG("onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTime", CCLabelTTF *, lblTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle", CCLabelTTF *, lblTitle);
    return true;
}

void LayerGameChan_XuongU2::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	lblTitle->setString("");

	UILayer* ui = UILayer::create();
	ui->setAnchorPoint(ccp(0, 0));
	ui->setPosition( ccp(0, 0) );
	ui->setTouchEnabled(true);
	this->addChild(ui);
	//Init all button
	int c = 0;
	int d = 0;
	float yPos = HEIGHT_DESIGN/2 - 60 + 37 * 5;
	while(c < 26){
		

		if (d < 3)
		{
			for( int i = 0; i < 6; i++ ){

				ButtonXuong* btn = ButtonXuong::create();
				btn->setID(c);
				btn->loadTextures("itemXuong.png","","");
				btn->setTitleText( lstCuoc.at(c).c_str() );
				btn->setTitleColor(ccBLACK);
				btn->setAnchorPoint(ccp(0 , 0));

				btn->setPosition( ccp(135 * d + 60, yPos - i % 6 * 37) );
				btn->setEnabled(true);
				btn->addTouchEventListener(this, toucheventselector(LayerGameChan_XuongU2::ItemXuong_Click));
				btn->setTitleFontSize(22);
				ListCuoc->addObject(btn);
				ui->addWidget(btn);
				c++;
				if(c >= lstCuoc.size()){
					c = 26;
					break;
				}
			}
		}
		else{
			for( int i = 0; i < 5; i++ ){

				ButtonXuong* btn = ButtonXuong::create();
				btn->setID(c);
				btn->loadTextures("itemXuong.png","","");
				btn->setTitleText( lstCuoc.at(c).c_str() );
				btn->setTitleColor(ccBLACK);
				btn->setAnchorPoint(ccp(0 , 0));

				btn->setPosition( ccp(135 * d + 60, yPos - i % 5 * 37) );
				btn->setEnabled(true);
				btn->addTouchEventListener(this, toucheventselector(LayerGameChan_XuongU2::ItemXuong_Click));
				btn->setTitleFontSize(20);
				ListCuoc->addObject(btn);
				ui->addWidget(btn);
				c++;
				if(c >= lstCuoc.size()){
					c = 26;
					break;
				}
			}
		}
		
		d++;
	}
    return;
}

void LayerGameChan_XuongU2::ItemXuong_Click(CCObject *sender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		ButtonXuong *btn = (ButtonXuong*)sender;
		CCLOG("Ban vua click: %d", btn->getID());
		if (!btn->getClicked())
		{
			btn->loadTextures("itemXuong_press.png","","");
			btn->setClicked(true);
		}
		else{
			btn->loadTextures("itemXuong.png","","");
			btn->setClicked(false);
		}

		string ttt = "";

		for (int i = 0; i < ListCuoc->count(); i++)
		{
			ButtonXuong *itemXuong = (ButtonXuong*)ListCuoc->objectAtIndex(i);

			if (itemXuong->getClicked())
			{
				if(i == ListCuoc->count() - 1){
					ttt += getValuesCuoc(itemXuong->getID());
				}
				else
				{
					ttt += getValuesCuoc(itemXuong->getID()) +" ";
				}
			}
		}
		lblTitle->setString(ttt.c_str());
	}
}

string LayerGameChan_XuongU2::getValuesCuoc(int idx){
	return lstCuoc.at(idx);
}

void LayerGameChan_XuongU2::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));

	CCLOG("cmd (in xuong u) = %s", ptrNotifiedCmd->c_str());
	if (strcmp("rsuanou", ptrNotifiedCmd->c_str()) == 0)
	{
		CCLOG("nhan duoc respond");
	}
	else if (strcmp("ntfanbao", ptrNotifiedCmd->c_str()) == 0)
	{
		boost::shared_ptr<long> anbaores = param->GetInt("anbaores");
		if (anbaores != NULL)
		{
			if (*anbaores == 23)
			{
				this->removeFromParentAndCleanup(true);
			}
		}
	}
	else if (strcmp("e", ptrNotifiedCmd->c_str()) == 0)
	{
		this->removeFromParentAndCleanup(true);
	}
}

bool ButtonXuong::init(){
	if (!UIButton::init())
	{
		return false;
	}
	isClicked = false;
	return true;
}

void ButtonXuong::setID(int idx){
	this->idx = idx;
}

int ButtonXuong::getID(){
	return this->idx;
}

void ButtonXuong::setClicked(bool isClicked){
	this->isClicked = isClicked;
}

bool ButtonXuong::getClicked(){
	return this->isClicked;
}