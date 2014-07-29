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
	lstCuoc.push_back("Có Thiên Khai");
	lstCuoc.push_back("Ăn Bòn");
	lstCuoc.push_back("Ù Bòn");
	lstCuoc.push_back("Có Chíu");
	lstCuoc.push_back("Chíu Ù");
	lstCuoc.push_back("Bạch Thủ");
	lstCuoc.push_back("Hoa rơi cửa phật");
	lstCuoc.push_back("Nhà lầu xe hơi, hoa rơi cửa phật");
	lstCuoc.push_back("Cá lội sân đình");
	lstCuoc.push_back("Cá nhảy đầu thuyền");
	lstCuoc.push_back("Chùa đổ nát hoa");
	lstCuoc.push_back("Đôi Lèo");
	lstCuoc.push_back("Đôi Tám đỏ");
	lstCuoc.push_back("Đôi Tôm");
	lstCuoc.push_back("Bạch Thủ Chi");
    //
    GameServer::getSingleton().addListeners(this);
}

LayerGameChan_XuongU2::~LayerGameChan_XuongU2()
{
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
// 	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
// 	boost::shared_ptr<ISFSObject> params (new SFSObject());
// 
// 	string str = "";
// 	if (chooseXuong->count() == 0)
// 	{
// 		str = "";
// 		CCLOG("Chua chon cuoc xuong !");
// 		return;
// 	}
// 	else
// 	{
// 		for (int i = 0; i < (int)chooseXuong->count(); i++)
// 		{
// 			CCInteger *f = (CCInteger*) chooseXuong->objectAtIndex(i);
// 			if (i < chooseXuong->count() - 1)
// 			{
// 				str+=boost::to_string(f->getValue())+":";
// 			}
// 			else
// 				str+=boost::to_string(f->getValue());
// 		}
// 	}
// 	
// 	CCLOG("str = %s",str.c_str());
// 	params->PutUtfString("ucsac",str);
// 	boost::shared_ptr<IRequest> request (new ExtensionRequest("rquanou",params,lastRoom));
// 	GameServer::getSingleton().getSmartFox()->Send(request);
// 	this->removeFromParentAndCleanup(true);
//     CCLOG("onButtonXuong ");
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
	UILayer* ui = UILayer::create();
	ui->setAnchorPoint(ccp(0, 1));
	ui->setContentSize(ccp(722, 298));
	ui->setPosition( ccp(20, 20) );
	ui->setTouchEnabled(true);
	this->addChild(ui);
	//Init all button
	for( int i = 0; i<6; i++ ){
		UIButton* btn = UIButton::create();
		btn->setTitleText( lstCuoc.at(i).c_str() );
		btn->setPosition( ccp(80, 220 + i*35) );
		btn->setPressedActionEnabled(true);
		btn->setTitleFontSize(22);
		ui->addWidget(btn);
	}
    //
    return;
}

void LayerGameChan_XuongU2::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];

	CCLOG("cmd (in xuong u) = %s",ptrNotifiedCmd->c_str());
	if (strcmp("rsuanou",ptrNotifiedCmd->c_str()) == 0)
	{
		CCLOG("nhan duoc respond");
	}
}