//
//  LayerGameChan_KetQua.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerGameChan_KetQua.h"
#include "GameServer.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
#include "CardChan.h"

using namespace Sfs2X;
using namespace cocos2d;
//using namespace CocosDenshion;


LayerGameChan_KetQua::LayerGameChan_KetQua()
{
	lblThongBao=NULL;
	lblMoney=NULL;

	list_noc = "";

	CARD_NOC = CCArray::create();
	CARD_NOC->retain();
	CARD_WINNER = CCArray::create();
	CARD_WINNER->retain();

	EXT_EVENT_REQ_NOC_DETAIL = "rqnocdtl";
	EXT_EVENT_REQ_TRENTAY_DETAIL = "rqttdtl";
	GameServer::getSingleton().addListeners(this);
}

LayerGameChan_KetQua::~LayerGameChan_KetQua()
{
	GameServer::getSingleton().removeListeners(this);
	CARD_NOC->removeAllObjects();
	CARD_NOC->release();
	CARD_WINNER->removeAllObjects();
	CARD_WINNER->release();

	CCLOG("Jumpe to Deconstructor LayerGameChan_KetQua");
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerGameChan_KetQua::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnXemNoc", LayerGameChan_KetQua::onButtonXemNoc);
	return NULL;
}

void LayerGameChan_KetQua::onButtonXemNoc(CCObject* pSender)
{
	CCLOG("onButtonXemNoc");
	if (list_noc != "")
	{
		setCard_Noc(list_noc);
	}
}

// CCBMemberVariableAssigner interface
bool LayerGameChan_KetQua::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblThongBao", CCLabelTTF *, lblThongBao);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
	return true;
}

void LayerGameChan_KetQua::setValueNoc(string _list){
	this->list_noc = _list;
}

void LayerGameChan_KetQua::closePopUp(){
	this->removeFromParentAndCleanup(true);
}

void LayerGameChan_KetQua::setPlayer_U(string uid){
	lblThongBao->setString((uid + " đã báo Ù con bài này \n Chờ nhà này xướng !").c_str());
}

void LayerGameChan_KetQua::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("Imhere onNodeLoaded");
	lblMoney->setString("");
	this->setTouchEnabled(true);
}

void LayerGameChan_KetQua::rotateListCards(CCArray *P){
	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CCActionInterval *action = CCRotateBy::create(0.8, dem*(250/19));
		card->runAction(CCSequence::create(action,NULL));
		dem++;
	}
}

void LayerGameChan_KetQua::setCard_Noc(string listnoc){
	if (CARD_NOC->count() > 0)
	{
		while(CARD_NOC->count() > 0)
		{
			CardChan* cards = (CardChan*)CARD_NOC->lastObject();
			CARD_NOC->removeLastObject();
			cards->removeFromParentAndCleanup(true);
		}
	}

	vector<string> arrNoc = mUtils::splitString(listnoc,';');
	float startLeft = (800 - (arrNoc.size() * 30)) / 2;
	int i = 0;
	int listsize = (int)arrNoc.size();
	while(i <= listsize)
	{
		if (i < listsize)
		{
			vector<string> info = mUtils::splitString(arrNoc[i],':');
			CardChan *pCard = CardChan::create();
			pCard->loadTexture(findTypeCard(info[1],info[2]).c_str());
			pCard->setSizeCard(30,100);
			pCard->setPosition(ccp(startLeft,50));
			CARD_NOC->addObject(pCard);
			this->addChild(pCard);
			i++;
		}
		else
		{
			displayListCard_Noc(CARD_NOC);
			break;
		}
	}
}

string LayerGameChan_KetQua::findTypeCard(string number,string suite){
	string str = "";
	str += number+"_"+suite+".png";
	return str;
}

void LayerGameChan_KetQua::setListCard_WinnerUser(string listcard){
	vector<string> arrCard = mUtils::splitString(listcard,';');
	int i = 0;
	int listsize = (int)arrCard.size();
	while (i <= listsize)
	{
		if (i < listsize)
		{
			vector<string> info = mUtils::splitString(arrCard[i],':');
			CardChan *pCard = CardChan::create();
			pCard->loadTexture(findTypeCard(info[1],info[2]).c_str());
			pCard->setAnchorPoint(ccp(0.5,0));
			pCard->setSizeCard(34,125);
			pCard->setPosition(ccp(200,240));
			float start = (listsize % 2 == 0) ? (float)listsize : (float)(listsize - 1);
			pCard->setRotation(-((start) / 2 * (250/19)));
			this->addChild(pCard);
			CARD_WINNER->addObject(pCard);
			i++;
		}
		else{
			rotateListCards(CARD_WINNER);
			break;
		}
	}
}

void LayerGameChan_KetQua::displayListCard_Noc(CCArray *P){
	if (P->count() == 0)
	{
		return;
	}

	int startLeft = (800 - P->count() * 30) / 2;
	CCLOG("Start Left %d",startLeft);
	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CCActionInterval *moveTo = CCMoveTo::create(0.8,ccp(startLeft + dem * 30,50));
		card->runAction(CCSequence::create(moveTo,NULL));
		dem++;
	}
}

void LayerGameChan_KetQua::displayListCard_Winner(string listcard){

}

void LayerGameChan_KetQua::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("hbc", cmd->c_str())==0){
		return;
	}
	CCLOG("cmd = %s",cmd->c_str());
	if (strcmp("rntf",cmd->c_str()) == 0)
	{
		this->removeFromParentAndCleanup(true);
	}
	else if (strcmp("ntfnocdetl",cmd->c_str()) == 0)
	{
		boost::shared_ptr<string> nocdetl = param->GetUtfString("nocdetl");
		if (nocdetl != NULL)
		{
			list_noc = nocdetl->c_str();
		}
	}
	else if (strcmp("grs", cmd->c_str()) == 0)
	{
		boost::shared_ptr<string> rg = param->GetUtfString("rg");
		if(rg != NULL)
		{
// 			string strs = rg->c_str();
// 			CCLOG("reruilt in Layer Ket qua: %s",rg->c_str());
// 			vector<string> listResuilt = mUtils::splitString(strs,';');
// 			CCLOG("Winner: %s", listResuilt[2].c_str());
// 			CCLOG("Den lang: %s", listResuilt[3].c_str());
// 			CCLOG("Win cuoc sac: %s", listResuilt[4].c_str());
// 			CCLOG("Den lang cuoc sac: %s", listResuilt[5].c_str());
			//CCLOG("Tong diem: %s", listResuilt[6].c_str());
		}
	}
	else if (strcmp("ntfcurpu", cmd->c_str()) == 0)
	{
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
		if (strcmp(usrn->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
		{
			this->removeFromParentAndCleanup(true);
		}
	}
}

// format: gameid;gameEndReason;winnerUserName;denLangUserName;winCuocSacList;denLangCuocSacList;totalScore;danhSáchTínhTiền
// trong đó winCuocSacList hoặc denLangCuocSacList có định dạng: cuoc1:cuoc2:cuocN:...
// danhSáchTínhTiền: cộng trừ tiền cho các player, thông tin mỗi player có format username:coinReason:coinChange, thông tin mỗi player cách nhau bởi kí tự '/'
// mẫu: 1;1;phanpc;;2:6;;6;phanpc:0:27000/phanpc1:6:-30000

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

void LayerGameChan_KetQua::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerGameChan_KetQua::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
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