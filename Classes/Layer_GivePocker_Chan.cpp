#include "Layer_GivePocker_Chan.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
#include "LayerChanToast.h"
#include "AllData.h"

#define WIDTH_DESIGN 800
#define HEIGHT_DESIGN 480

using namespace Sfs2X;

bool Layer_GivePocker_Chan::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	uLayer = UILayer::create();
	uLayer->setAnchorPoint(ccp(0,0));
	uLayer->setPosition(ccp(0,0));
	this->addChild(uLayer);

	//Bat dau o day
	countLeft = 0;
	countRight = 0;
	index_Noc = -1;

	_startTimmer = 45;

	flagBocCai = false;
	flag_ChonNoc = false;
	isPlayerBocCai = false;

	playerBocCai = "";
	playerStart = ""; 
	listusers = "";
	arrTag.push_back(9);

	c1_leftX = 300;
	c1_leftY = 260;

	c2_leftX = 325;
	c2_leftY = 205;

	c3_leftX = 350;
	c3_leftY = 150;
	 
	c4_leftX = 225;
	c4_leftY = 195;

	c5_leftX = 250;
	c5_leftY = 140;

	c1_rightX = WIDTH_DESIGN - c1_leftX;
	c1_rightY = HEIGHT_DESIGN - c1_leftY;

	c2_rightX = WIDTH_DESIGN - c2_leftX;
	c2_rightY = HEIGHT_DESIGN - c2_leftY;

	c3_rightX = WIDTH_DESIGN - c3_leftX;
	c3_rightY = HEIGHT_DESIGN - c3_leftY;

	c4_rightX = WIDTH_DESIGN - c4_leftX;
	c4_rightY = HEIGHT_DESIGN - c4_leftY;

	c5_rightX = WIDTH_DESIGN - c5_leftX;
	c5_rightY = HEIGHT_DESIGN - c5_leftY;

	B1 = create5Cards(c1_leftX, c1_leftY, 0);
	B2 = create5Cards(c2_leftX, c2_leftY, 0);
	B3 = create5Cards(c3_leftX, c3_leftY, 0);
	B4 = create5Cards(c4_leftX, c4_leftY, 0);
	B5 = create5Cards(c5_leftX, c5_leftY, 0);

	B6 = create5Cards(c1_rightX, c1_rightY, 3);
	B7 = create5Cards(c2_rightX, c2_rightY, 5);
	B8 = create5Cards(c3_rightX, c3_rightY, 4);
	B9 = create5Cards(c4_rightX, c4_rightY, 2);
	B10 = create5Cards(c5_rightX, c5_rightY, 1);

	P_NOC = CCArray::create();
	P_NOC->retain();
	P_NOC->addObject(B10);
	P_NOC->addObject(B9);
	P_NOC->addObject(B6);
	P_NOC->addObject(B7);
	P_NOC->addObject(B8);
	//10-9-6-8-7

	uLayer->addWidget(B1);
	uLayer->addWidget(B2);
	uLayer->addWidget(B3);
	uLayer->addWidget(B4);
	uLayer->addWidget(B5);
	uLayer->addWidget(B6);
	uLayer->addWidget(B7);
	uLayer->addWidget(B8);
	uLayer->addWidget(B9);
	uLayer->addWidget(B10);

	initAllCards();

	noc = UIImageView::create();
	noc->loadTexture("card_back_chan.png");
	noc->setAnchorPoint(ccp(0.5, 0.5));
	noc->setPosition(ccp(WIDTH_DESIGN/2, HEIGHT_DESIGN/2));
	noc->setRotation(20);
	noc->setScale(0.4);
	noc->setRotation(-45);
	noc->setTouchEnabled(true);
	noc->addTouchEventListener(this, toucheventselector(Layer_GivePocker_Chan::BocNoc));
	uLayer->addWidget(noc);

	noc2 = UIImageView::create();
	noc2->loadTexture("card_back_chan.png");
	noc2->setAnchorPoint(ccp(0.5, 0.5));
	noc2->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2));
	noc2->setRotation(20);
	noc2->setScale(0.4);
	noc2->setRotation(-45);
	noc2->setTouchEnabled(true);
	noc2->addTouchEventListener(this, toucheventselector(Layer_GivePocker_Chan::BocNoc));
	uLayer->addWidget(noc2);

	timer = UILabelBMFont::create();
	timer->setFntFile("UVNVan.fnt");
	timer->setText("45");
	timer->setColor(ccGREEN);
	timer->setScale(0.7);
	timer->setVisible(false);
	uLayer->addChild(timer);

	GameServer::getSingleton().addListeners(this);
	return true;
}

Layer_GivePocker_Chan::~Layer_GivePocker_Chan(){
	CCLog("Jumpe deconstructor Layer GivePocker for Chan Game !!!!!");
	GameServer::getSingleton().removeListeners(this);
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);
}

void Layer_GivePocker_Chan::onExit()
{
	CCLog("Jumpe onExit Layer GivePocker for Chan Game !!!!!");
	GameServer::getSingleton().removeListeners(this);
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);
}

void Layer_GivePocker_Chan::setListusers(string listusers){
	this->listusers = listusers;
}

void Layer_GivePocker_Chan::setIsPlayerBocCai(bool isFlag){
	this->isPlayerBocCai = isFlag;
}

void Layer_GivePocker_Chan::setPlayerBocCai(string player){
	this->playerBocCai = player;
}

UIImageView* Layer_GivePocker_Chan::create5Cards(float posX, float posY, int mTag){
	UIImageView *img = UIImageView::create();
	img->loadTexture("image_transparent.png");
	img->setAnchorPoint(ccp(0.5, 0.5));
	img->setPosition(ccp(posX, posY));
	img->setScale(0.4);
	img->setTag(mTag);
	img->setTouchEnabled(true);
	img->addTouchEventListener(this, toucheventselector(Layer_GivePocker_Chan::NocTouch));
	img->setRotation(16.0);
	return img;
}

void Layer_GivePocker_Chan::NocTouch(CCObject *pSender,TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		if(isPlayerBocCai == false)
			return;
		if (flagBocCai == true)
		{
			UIImageView *img = (UIImageView*)pSender;
			if (img != NULL)
			{
				B1->setEnabled(false);
				B2->setEnabled(false);
				B3->setEnabled(false);
				B4->setEnabled(false);
				B5->setEnabled(false);
				CCLog("Tag = %d", img->getTag());
				noc2->setEnabled(false);
				
				if (flag_ChonNoc == false)
				{
					index_Noc = img->getTag();
					img->runAction(CCMoveTo::create(0.3, ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2)));
					flag_ChonNoc = true;
				}
				
				else{
					flagBocCai = false;
					CCCallFunc *callfun = CCCallFunc::create(this, callfunc_selector(Layer_GivePocker_Chan::sendRequsetBocNoc));
					CCActionInterval *moveTo = CCMoveTo::create(0.5,img->getPosition());
					index_Choose = img->getTag();
					noc->runAction(CCSequence::create(moveTo, callfun, NULL));
				}
			}
		}
	}
}

void Layer_GivePocker_Chan::sendRequsetBocNoc(){
	//Gửi bản tin bốc nọc đi
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	boost::shared_ptr<Room> lstRooms = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rqbocc",params,lstRooms));
	GameServer::getSingleton().getSmartFox()->Send(request);
	CCLOG("Send Request Bốc Cái !");
}

void Layer_GivePocker_Chan::BocNoc(CCObject *pSender,TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		if (flagBocCai == true)
		{
			CCLog("Boc noc !");
			noc2->setEnabled(false);
		}
	}
}

void Layer_GivePocker_Chan::initAllCards(){
	addVirtualCard(B1);
	addVirtualCard(B2);
	addVirtualCard(B3);
	addVirtualCard(B4);
	addVirtualCard(B5);
	addVirtualCard(B6);
	addVirtualCard(B7);
	addVirtualCard(B8);
	addVirtualCard(B9);
	addVirtualCard(B10);
}

void Layer_GivePocker_Chan::addVirtualCard(UIImageView *img){
	for (int i = 0; i < 5; i++)
	{
		UIImageView *a = UIImageView::create();
		a->setAnchorPoint(ccp(0.5, 0.5));
		a->loadTexture("card_back_chan.png");
		int _rote = rand()%(15) - 10;
		a->setRotation((float)_rote);
		a->setTag(i);
		a->setVisible(false);
		img->addChild(a);
	}
}

void Layer_GivePocker_Chan::startGivePocker(){
	noc->setRotation(20);
	givePocker(0);
	this->runAction(CCSequence::create(CCDelayTime::create(0.4),CCCallFunc::create(this, callfunc_selector(Layer_GivePocker_Chan::delayTimeturn2)),NULL));
}

void Layer_GivePocker_Chan::delayTimeturn2(){
	noc2->setRotation(20);
	givePocker(1);
}

void Layer_GivePocker_Chan::givePocker(int Pos){
	//ben trai
	if (Pos == 0)
	{
		int z = countLeft / 5;
		if (z <= 4)
		{
			int t = countLeft % 5;
			switch(t){
			case 0:
				giveToPosition(c1_leftX, c1_leftY, 0);
				break;
			case 1:
				giveToPosition(c2_leftX, c2_leftY, 0);
				break;
			case 2: 
				giveToPosition(c3_leftX, c3_leftY, 0);
				break;
			case 3: 
				giveToPosition(c4_leftX, c4_leftY, 0);
				break;
			case 4: 
				giveToPosition(c5_leftX, c5_leftY, 0);
				break;
			default: 
				break;
			}
		}
		return;
	}

	//ben phai
	if (Pos == 1)
	{
		int z = countRight / 5;
		if (z <= 4)
		{
			int t = countRight % 5;
			switch(t){
			case 0:
				giveToPosition(c1_rightX, c1_rightY, 1);
				break;
			case 1:
				giveToPosition(c2_rightX, c2_rightY, 1);
				break;
			case 2: 
				giveToPosition(c3_rightX, c3_rightY, 1);
				break;
			case 3: 
				giveToPosition(c4_rightX, c4_rightY, 1);
				break;
			case 4: 
				giveToPosition(c5_rightX, c5_rightY, 1);
				break;
			default: 
				break;
			}
		}
		return;
	}
}

void Layer_GivePocker_Chan::giveToPosition(float toX, float toY, int pos){
	int *value = new int(pos);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(Layer_GivePocker_Chan::test),(void*)value);
	CCActionInterval *moveTo = CCMoveTo::create(0.2,ccp(toX, toY));
	if (pos == 0)
	{
		countLeft++;
		if (countLeft < 25)
		{
			noc->runAction(CCSequence::create(CCDelayTime::create(0.1), moveTo, callfun, NULL));
		}
		else
		{
			CCMoveTo *moveTo = CCMoveTo::create(0.3,ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2));
			noc->runAction(moveTo);
		}
	}else{
		countRight++;
		if (countRight < 25)
		{
			noc2->runAction(CCSequence::create(CCDelayTime::create(0.1), moveTo, callfun,NULL));
		}
		else
		{
			CCMoveTo *moveTo = CCMoveTo::create(0.3,ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2));
			noc2->runAction(moveTo);

			B10->runAction(CCMoveTo::create(0.5, B1->getPosition()));
			B9->runAction(CCMoveTo::create(0.5, B2->getPosition()));

			CCCallFunc *callfunc = CCCallFunc::create(this, callfunc_selector(Layer_GivePocker_Chan::delayTimeEnd));
			this->runAction(CCSequence::create(CCDelayTime::create(0.5), callfunc, NULL));
		}
	}
}

void Layer_GivePocker_Chan::delayTimeEnd(){
	//Chuyen 4 -> 8, 5 - 7, 3 - 6
	B4->runAction(CCMoveTo::create(0.5, B8->getPosition()));
	B5->runAction(CCMoveTo::create(0.5, B7->getPosition()));
	B3->runAction(CCMoveTo::create(0.5, B6->getPosition()));
	flagBocCai = true;

	string str = "";
	if (isPlayerBocCai)
	{
		str = "Bạn hãy chọn 1 bộ bài làm nọc";
	}
	else
	{
		str = "Chờ " + getNamePlayer(playerBocCai) + " chọn nọc ";
	}
	LayerChanToast::showToast(this, str, 4);
	//Add interval đếm ngược ở đây
	setIntervalBocNoc();
}

void Layer_GivePocker_Chan::setIntervalBocNoc(){
	//wid_Avata = 90, hei_Avata = 125
	CCPoint pPoint;
	int posBocCai = getPosUserByName(playerBocCai, listusers);

	if (mUtils::splitString(listusers, ';').size() == 2)
	{
		if (posBocCai == kUserMe)
		{
			pPoint = CCPoint(ccp(WIDTH_DESIGN / 2, 90));
		}
		else
		{
			pPoint = CCPoint(ccp(WIDTH_DESIGN / 2 + 65, HEIGHT_DESIGN - 115));
		}
	}
	else
	{
		switch(posBocCai){
		case kUserMe:
			pPoint = CCPoint(ccp(WIDTH_DESIGN / 2, 90));
			break;
		case kUserLeft:
			pPoint = CCPoint(ccp(105, HEIGHT_DESIGN / 2));
			break;
		case kUserRight:
			pPoint = CCPoint(ccp(WIDTH_DESIGN - 105, HEIGHT_DESIGN / 2));
			break;
		case kUserTop:
			pPoint = CCPoint(ccp(WIDTH_DESIGN / 2 + 65, HEIGHT_DESIGN - 115));
			break;
		}
	}
	
	timer->setPosition(pPoint);
	timer->setVisible(true);
	schedule(schedule_selector(Layer_GivePocker_Chan::updateTimer), 1);
}

void Layer_GivePocker_Chan::updateTimer(float dt){
	_startTimmer -= dt;
	int k = ((int)_startTimmer);
	if (k < 0)
	{
		return;
	}
	
	char time[10] = {0};
	sprintf(time, "%d", k);
	timer->setText(time);
}

void Layer_GivePocker_Chan::test(CCNode* sender, void* data){
	int *pos = (int*) data; 
	if (*pos == 0)
	{
		int t = (countLeft - 1) % 5;
		int z = (countLeft - 1) / 5;
		UIImageView *img;
		switch(t){
		case 0:
			img = (UIImageView *)B1->getChildByTag(z);
			img->setVisible(true);
			break;
		case 1:
			img = (UIImageView*)B2->getChildByTag(z);
			img->setVisible(true);
			break;
		case 2: 
			img = (UIImageView*)B3->getChildByTag(z);
			img->setVisible(true);
			break;
		case 3: 
			img = (UIImageView*)B4->getChildByTag(z);
			img->setVisible(true);
			break;
		case 4: 
			img = (UIImageView*)B5->getChildByTag(z);
			img->setVisible(true);
			break;
		default: 
			break;
		}
	}
	else
	{
		int t = (countRight - 1) % 5;
		int z = (countRight - 1) / 5;
		UIImageView *img;
		switch(t){
		case 0:
			img = (UIImageView*)B6->getChildByTag(z);
			img->setVisible(true);
			break;
		case 1:
			img = (UIImageView*)B7->getChildByTag(z);
			img->setVisible(true);
			break;
		case 2: 
			img = (UIImageView*)B8->getChildByTag(z);
			img->setVisible(true);
			break;
		case 3: 
			img = (UIImageView*)B9->getChildByTag(z);
			img->setVisible(true);
			break;
		case 4: 
			img = (UIImageView*)B10->getChildByTag(z);
			img->setVisible(true);
			break;
		default: 
			break;
		}
	}

	givePocker(*pos);
}

void Layer_GivePocker_Chan::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if (strcmp("e", cmd->c_str()) == 0)
	{
		this->removeFromParentAndCleanup(true);
	}
	if(strcmp("rsbocc", cmd->c_str()) != 0){
		return;
	}
	if (strcmp("rsbocc", cmd->c_str()) == 0)
	{
		boost::shared_ptr<string> nocdetl = param->GetUtfString("nocdetl");
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");

		if (nocdetl != NULL && usrn != NULL)
		{
			//"nocdetl":"dautv3;92:9:2:1"
			vector<string> _nocdetl = mUtils::splitString(*nocdetl, ';');
			playerStart = _nocdetl.at(0);
			CCLOG("player start %s", playerStart.c_str());
			if (isPlayerBocCai == false)
			{
				moveRandomIsNotPlayerBocCai(_nocdetl.at(1));
			}
			else
			{
				moveCard4User(_nocdetl.at(1), _nocdetl.at(0));
			}
			CCCallFunc *callfun = CCCallFunc::create(this, callfunc_selector(Layer_GivePocker_Chan::moveCardsToPosition));	
			this->runAction(CCSequence::create(CCDelayTime::create(0.3), callfun, NULL));
		}
	}
}

void Layer_GivePocker_Chan::moveCardsToPosition(){

	CCLOG("arrTag va chooseIndex");
	CCLOG("player start %s", playerStart.c_str());
	CCLOG("chooseIndex = %d", index_Choose);
	for (int i = 0; i < arrTag.size(); i++)
	{
		CCLOG("arrTag[%d] = %d",i,arrTag[i]);
	}

	int posuser = getPosUserByName(playerStart, listusers);
	vector<string> arrUser = mUtils::splitString(listusers,';');
	vector<int> pos;
	for (int i = 0; i < arrUser.size(); i++)
	{
		vector<string> info = mUtils::splitString(arrUser[i], ':');
		int a = getPosUserByName(info[1], listusers);
		pos.push_back(a);
	}
	
	// Sắp xếp lại vị trí các nọc
	int vt = -1;
	for (int i = 0; i < arrTag.size(); i++)
	{
		if (arrTag.at(i) == index_Choose)
		{
			vt = i;
			break;
		}
	}
	if (vt == -1)
	{
		return;
	}
		
	vector<int> newTag = sortArrayTag(arrTag, vt);
	vector<int> newPos = sortArrayTag(pos, posuser);

	chiaBai(newPos, newTag);
}

void Layer_GivePocker_Chan::chiaBai(vector<int> toPos, vector<int> allTag){
	for(int i = 0; i < toPos.size(); i++)
	{
		for (int j = 0; j < P_NOC->count(); j++)
		{
			UIImageView *img = (UIImageView*)P_NOC->objectAtIndex(j);
			if (img->getTag() == allTag.at(i))
			{
				finishGive(img, toPos.at(i));
				break;
			}
		}
	}
}

void Layer_GivePocker_Chan::finishGive(UIImageView *img, int tpos){
	bool _flag = false;
	if (tpos == getPosUserByName(playerStart, listusers))
	{
		_flag = true;		
	}
	
	CCPoint pPoint_Me = CCPoint(ccp(WIDTH_DESIGN / 2, 50));
	CCPoint pPoint_Left = CCPoint(ccp(50, HEIGHT_DESIGN / 2));
	CCPoint pPoint_Right = CCPoint(ccp(WIDTH_DESIGN - 50, HEIGHT_DESIGN / 2));
	CCPoint pPoint_Top = CCPoint(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN - 50));

	CCPoint pPoint;

	if (mUtils::splitString(listusers,';').size() == 2)
	{
		if (tpos == kUserMe)
		{
			pPoint = pPoint_Me;
		}
		else
		{
			pPoint = pPoint_Top;
		}
	}
	else
	{
		switch(tpos){
		case kUserMe:
			pPoint = pPoint_Me;
			break;
		case kUserLeft:
			pPoint = pPoint_Left;
			break;
		case kUserTop:
			pPoint = pPoint_Top;
			break;
		case kUserRight:
			pPoint = pPoint_Right;
			break;
		default:
			break;
		}
	}

	img->runAction(CCMoveTo::create(0.4, pPoint));
	CCLOG("_flag = %s",_flag ? "true" : "false");
	if (_flag == true)
	{
		noc->runAction(CCMoveTo::create(0.4, pPoint));
	}
}

vector<int> Layer_GivePocker_Chan::sortArrayTag(vector<int> _arr, int position){
	vector<int> newTag;
	for (int i = 0; i < _arr.size(); i++)
	{
		int pos = (i + position) % _arr.size();
		newTag.push_back(_arr[pos]);
	}
	return newTag;
}

void Layer_GivePocker_Chan::moveCard4User(string cards, string user){
	if (index_Noc == -1)
	{
		index_Noc = rand()%(4);
	}
	
	CCLOG("index noc: %d",index_Noc);

	//1-2-3-5-4
	int a[5] = {1,2,3,5,4};
	int n = 5;
	arrTag.clear();
	for(int i = 0; i < n; i++){
		if (a[i] != index_Noc)
		{
			arrTag.push_back(a[i]);
		}
	}//-> có a[]. index_Choose

	vector<string> detail = mUtils::splitString(cards,':');
	noc->loadTexture(findTypeCard(detail[1], detail[2]).c_str());

	// cần mảng a, và 1 phần tử xác định
}

void Layer_GivePocker_Chan::moveRandomIsNotPlayerBocCai(string cards){
		if (isPlayerBocCai == false)
		{
			B1->setEnabled(false);
			B2->setEnabled(false);
			B3->setEnabled(false);
			B4->setEnabled(false);
			B5->setEnabled(false);
			noc2->setEnabled(false);

			int n = 5;
			int a[5] = {1,2,3,5,4};

			//x=rand()%(b-a+1)+a
			int x = rand()%(n - 1);
			CCLog("random Tag: %d", x);
			index_Noc = a[x];
			UIImageView *img;
			for (int i = 0; i < 5; i ++)
			{
				UIImageView *imgs = (UIImageView*)P_NOC->objectAtIndex(i);
				if (imgs->getTag() == a[x])
				{
					img = imgs;
					break;
				}
			}
			img->runAction(CCMoveTo::create(0.3, noc2->getPosition()));

			// Để lấy mảng các UI hiệu ứng
			CCLog("Jumpe to here error !");
			arrTag.clear();
			for(int i = 0; i < n; i++){
				if (a[i] != index_Noc)
				{
					arrTag.push_back(a[i]);
				}
			}

			CCLog("Here 2 error");
			UIImageView *img2;
			int y = rand()%(arrTag.size() - 2);
			index_Choose = arrTag.at(y);
			for (int i = 0; i < arrTag.size(); i++)
			{
				UIImageView *imgs = (UIImageView*)P_NOC->objectAtIndex(i);
				if (imgs->getTag() == index_Choose)
				{
					img2 = imgs;
					break;
				}
			}

			CCLog("here 3 error ");
			noc->runAction(CCMoveTo::create(0.3, img2->getPosition()));
			vector<string> detail = mUtils::splitString(cards,':');
			noc->loadTexture(findTypeCard(detail[1], detail[2]).c_str());
			//Có được a[] và y.
			CCLog("Chay het ham roi loi");
		}
}

string Layer_GivePocker_Chan::findTypeCard(string number,string suite){
	string str = "";
	str += number + "_" + suite + ".png";
	return str;
}

int Layer_GivePocker_Chan::getPosUserByName(string uid,string _list_user){
	int vt = -1;
	vector<string> list;
	if(_list_user.c_str() != NULL && _list_user != ""){
		list = mUtils::splitString(_list_user, ';');
	}

	for(int i = 0; i < list.size(); i++){
		string _id = mUtils::splitString(list[i], ':')[1];

		if(strcmp(_id.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
			vt = i;
			break;
		}
	}

	for(int k = 0; k < list.size(); k++){
		if(strcmp(list[k].c_str(), "")==0)
			continue;
		string player = list[k];
		vector<string> n = mUtils::splitString(player, ':');
		if(strcmp(n[1].c_str(), uid.c_str()) == 0){
			if(k == vt){
				return kUserMe;
			}
			else if(k == (vt + 1) % 4){
				return kUserRight;
			}
			else if(k == (vt + 2) % 4){
				return kUserTop;
			}
			else if(k == (vt + 3) % 4){
				return kUserLeft;
			}
			break;
		}
	}
	return -1;
}

string Layer_GivePocker_Chan::getNamePlayer(string uid){
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

void Layer_GivePocker_Chan::killLayer(){
	this->removeFromParentAndCleanup(true);
}
