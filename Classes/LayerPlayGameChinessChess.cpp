//
//  LayerPlayGameChinessChess.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/4/14.
//
//

#include "AllData.h"
#include "LayerPlayGameChinessChess.h"
#include "SceneManager.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"
#include "Requests/LeaveRoomRequest.h"
#include "Requests/PublicMessageRequest.h"
#include "_Number_.h"
#include "LayerSettings.h"
#include "LayerChatWindow.h"
#include "LayerChargeMoney.h"

using namespace cocos2d;
//using namespace CocosDenshion;

void LayerPlayGameChinessChess::showToast(string mes) {
	Chat *noti = new Chat(mes, -1);
	this->addChild(noti);
}

void LayerPlayGameChinessChess::playSound( string soundPath )
{
	if( mUtils::isSoundOn() )
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundPath.c_str());
}

vector<string> LayerPlayGameChinessChess::split(string &S, const char &str) {
    vector<string> arrStr;
    string::iterator t, t2;
    
    for (t = S.begin(); t < S.end(); ){
        // Lặp từ vị trí bắt đầu
        t2 = find(t, S.end(), str);
        
        //kể từ vị trí t
        if(t != t2){
            arrStr.push_back(string(t, t2));
        }
        else if (t2 != S.end()) arrStr.push_back("");
        
		if (t2 == S.end())
		{
			break;
		}
		

        t = t2 + 1;
    }
    
    return arrStr;
}

int LayerPlayGameChinessChess::convertResponseToInt(string inString) {
	if (inString == "ctbl")		return EXT_EVENT_CHESS_TABLE_NTF;
    if (inString == "s")        return EXT_EVENT_START;
    if (inString == "nt")       return EXT_EVENT_NEXT_TURN;
    if (inString == "e")        return EXT_EVENT_END;
    if (inString == "rntf")     return EXT_EVENT_READY_NTF;
    if (inString == "grs")      return EXT_EVENT_GAME_RESULT;
    if (inString == "e_rntf")   return EXT_EVENT_ERROR_READY_NTF;
    if (inString == "luu")      return EXT_EVENT_LIST_USER_UPDATE;
    if (inString == "mntf")     return EXT_EVENT_MOVE_NTF;
    if (inString == "fpntf")    return EXT_EVENT_FOR_PEACE_NTF;
    //
    if (inString == "rr")       return EXT_EVENT_READY_REQ;
    if (inString == "fp")       return EXT_EVENT_FOR_PEACE;
    if (inString == "iml")      return EXT_EVENT_IM_LOSE;
    if (inString == "move")     return EXT_EVENT_MOVE;
	if (inString == "rfp")      return EXT_EVENT_REPLY_FOR_PEACE;
	if (inString == "umr")      return EXT_EVENT_UNDO_MOVE_REQ;
	if (inString == "rum")      return EXT_EVENT_REPLY_UNDO_MOVE;
	if (inString == "umntf")    return EXT_EVENT_UNDO_MOVE_NTF;
    
    return -1;
}
string LayerPlayGameChinessChess::convertResponseToString(int inInt) {
	if (inInt == EXT_EVENT_CHESS_TABLE_NTF)		return "ctbl";
    if (inInt == EXT_EVENT_START)               return "s";
    if (inInt == EXT_EVENT_NEXT_TURN)           return "nt";
    if (inInt == EXT_EVENT_END)                 return "e";
    if (inInt == EXT_EVENT_READY_NTF)           return "rntf";
    if (inInt == EXT_EVENT_GAME_RESULT)         return "grs";
    if (inInt == EXT_EVENT_ERROR_READY_NTF)     return "e_rntf";
    if (inInt == EXT_EVENT_LIST_USER_UPDATE)    return "luu";
    if (inInt == EXT_EVENT_MOVE_NTF)            return "mntf";
    if (inInt == EXT_EVENT_FOR_PEACE_NTF)       return "fpntf";
    //
    if (inInt == EXT_EVENT_READY_REQ)           return "rr";
    if (inInt == EXT_EVENT_FOR_PEACE)           return "fp";
    if (inInt == EXT_EVENT_IM_LOSE)             return "iml";
    if (inInt == EXT_EVENT_MOVE)                return "move";
	if (inInt == EXT_EVENT_REPLY_FOR_PEACE)     return "rfp";
	if (inInt == EXT_EVENT_UNDO_MOVE_REQ)		return "umr";
	if (inInt == EXT_EVENT_REPLY_UNDO_MOVE)     return "rum";
	if (inInt == EXT_EVENT_UNDO_MOVE_NTF)		return "umntf";
    
    return "";
}

LayerPlayGameChinessChess::LayerPlayGameChinessChess()
{
	imagedownloader4Red = new ImageDownloader();
	imagedownloader4Black = new ImageDownloader();

    nodeAvatarRed=NULL;
    lblNameRed=NULL;
    lblMoneyRed=NULL;
    lblWinRateRed=NULL;
    
    nodeAvatarBlack=NULL;
    lblNameBlack=NULL;
    lblMoneyBlack=NULL;
    lblWinRateBlack=NULL;
    
    box_time_focus_red=NULL;
    box_time_focus_black=NULL;
    
    readyRed=NULL;
    lblTimeRed=NULL;
    lblTotalTimeRed=NULL;
    
    readyBlack=NULL;
    lblTimeBlack=NULL;
    lblTotalTimeBlack=NULL;
    
    nodeTableChess=NULL;
    nodePoint=NULL;
    
    btnBack=NULL;
    btnSetting=NULL;
    btnMoney=NULL;
    btnChat=NULL;
    btnLose=NULL;
    btnPeace=NULL;
    btnReMove=NULL;
    
    lblXeRed_status=NULL;
    lblTotRed_status=NULL;
    lblMaRed_status=NULL;
    lblPhaoRed_status=NULL;
    lblTuongRed_status=NULL;
    lblSyRed_status=NULL;
    lblXeBlack_status=NULL;
    lblTotBlack_status=NULL;
    lblMaBlack_status=NULL;
    lblPhaoBlack_status=NULL;
    lblTuongBlack_status=NULL;
    lblSyBlack_status=NULL;
    //
    btnReady=NULL;
    btnUnReady=NULL;
    //
	// popup=NULL;
    GameServer::getSingleton().addListeners(this);
    SceneManager::getSingleton().hideLoading();

    // @thanhhv
    addButtons();
    
    // scaleApp
    // ---- TouchEvent Start
    this->sizeScreen = CCDirector::sharedDirector()->getVisibleSize();
    float scaleX = sizeScreen.width / WIDTH_DESIGN;
    float scaleY = sizeScreen.height / HEIGHT_DESIGN;
    float scaleMin = (scaleX < scaleY) ? scaleX : scaleY;
    this->scaleApp = scaleMin;
    
    this->startLeft = (sizeScreen.width - WIDTH_DESIGN) / 2;
    this->startTop = (sizeScreen.height - HEIGHT_DESIGN) / 2;
    
    tag = CCSprite::create("tag_phom_2.png");
    //this->addChild(tag, 1000);
	this->timeToReady = 20;

	this->isRegistSitdown = false;
	this->isRegistStandUp = false;
    
    this->schedule(schedule_selector(LayerPlayGameChinessChess::updateTimer), 1);
}

void LayerPlayGameChinessChess::updateTimer(float dt) {
    if ((isStartedGame || isSpector) && nameCurrentTurn.length() > 0) {
		if (timeRestBlack <= 0 || timeRestRed <= 0 || timeForTurnBlack <= 0 || timeForTurnRed <= 0)
			return;
        if (nameCurrentTurn == myName) {
            timeRestBlack--;
            lblTotalTimeBlack->setString(convertTimer(timeRestBlack).c_str());
			timeForTurnBlack--;
			lblTimeBlack->setString(convertTimer(timeForTurnBlack).c_str());
        }
        else {
            timeRestRed--;
            lblTotalTimeRed->setString(convertTimer(timeRestRed).c_str());
			timeForTurnRed--;
			lblTimeRed->setString(convertTimer(timeForTurnRed).c_str());
        }
    }
	else {
		// 
		if (timeToReady >= 0 && !isSpector) {
			Chat *noti = new Chat("Bạn có 20 giây để sẵn sàng!", -1);
			noti->setPositionY(70);
			noti->setPositionX(nodeTableChess->getContentSize().width/2 - noti->getSize().width/2);
			//nodeTableChess->addChild(noti, 100);

			CCString *stringTime = CCString::createWithFormat("%d", timeToReady);
			Number *time = new Number(stringTime->getCString());
			int count = (timeToReady >= 10) ? 2 : 1;
			time->setPosition(ccp(nodeTableChess->getContentSize().width/2-(33*count)/2,
								  100));
			nodeTableChess->addChild(time, 100 + (20-timeToReady));
			timeToReady--;

			time->runAction(CCSequence::create(
				CCFadeTo::create(1, 50),
				CCRemoveSelf::create(), 
				NULL));
		}
		timeRestBlack = 900;
		timeRestRed = 900;
		lblTotalTimeBlack->setString(convertTimer(timeRestBlack).c_str());
		lblTotalTimeRed->setString(convertTimer(timeRestRed).c_str());
	}
}

string LayerPlayGameChinessChess::convertTimer(int time) {
    int minute = time / 60;
    int second = time - minute * 60;
    
    string mString = to_string(minute);
    if (minute < 10)
        mString = "0" + mString;
    
    string sString = to_string(second);
    if (second < 10)
        sString = "0" + sString;
    
    string resutl = mString + ":" + sString;
    return (resutl);
}

void LayerPlayGameChinessChess::addButtons() {
//    CCSize sizeScreen = CCDirector::sharedDirector()->getVisibleSize();
//    float startLeft = (sizeScreen.width - WIDTH_DESIGN) / 2;
//    float startTop  = (sizeScreen.height - HEIGHT_DESIGN) / 2;
//
    
//    Chess *ma = new Chess(1,1);
//    ma->setAnchorPoint(ccp(0, 0));
//    this->addChild(ma, 100);
    
}

CCPoint LayerPlayGameChinessChess::convertPoint(CCPoint pPoint) {
    float xCenter = sizeScreen.width / 2;
    float yCenter = sizeScreen.height / 2;
    
    float xTap = pPoint.x;
    float yTap = pPoint.y;
    
    float x1, x2;
    float y1, y2;
    
    float A = ((powf(xCenter - xTap, 2) + powf(yCenter - yTap, 2))) / powf(scaleApp, 2);
    float B = powf((yCenter - yTap) / (xCenter - xTap) , 2) + 1;
    
    x1 = xCenter + sqrtf(A / B);
    x2 = xCenter - sqrtf(A / B);
    
    y1 = yCenter + (yCenter - yTap) * (x1 - xCenter) / (xCenter - xTap);
    y2 = yCenter + (yCenter - yTap) * (x2 - xCenter) / (xCenter - xTap);
    
    // "điểm cần convert" = A
    // Bởi vì A và Tap nằm ở cùng 1 phía so với Center nên nếu xTap < xCenter thì xA < xCenter và ngược lại
    
    if ((xTap < xCenter && x1 < xCenter) || (xTap > xCenter && x1 > xCenter)) {
        x1 -= startLeft;
        y1 -= startTop;
        
        pPoint.x = x1;
        pPoint.y = y1;
    } else if ((xTap < xCenter && x2 < xCenter) || (xTap > xCenter && x2 > xCenter)) {
        x2 -= startLeft;
        y2 -= startTop;
        
        pPoint.x = x2;
        pPoint.y = y2;
    } else {
        CCLog("No define POINT CONVERT");
    }
    
    return pPoint;
}

CCPoint LayerPlayGameChinessChess::convertPoint_LayerToTable(CCPoint point) {
    //CCPoint posTable = nodeTableChess->getPosition();
    CCPoint posTable = ccp(310, 1);
    CCSize  sizeTable = nodeTableChess->getContentSize();
    return ccp(point.x - (posTable.x), point.y - (posTable.y));
}

CCPoint LayerPlayGameChinessChess::convertPoint_TableToLayer(CCPoint point) {
    //CCPoint posTable = nodeTableChess->getPosition();
    CCPoint posTable = ccp(310, 1);
    return ccp(point.x + posTable.x, point.y + posTable.y);
}

void LayerPlayGameChinessChess::ccTouchesEnded(CCSet *pTouches, CCEvent *event){
	if (isClickedBack) return;

	hideMenu();

	if (isSpector) {
		showChat("Bạn đang ở chế độ khách!");
		return;
	}

	if (this->nameCurrentTurn != myName){
		return; 
	}

    CCSetIterator iterator = pTouches->begin();
    CCTouch *touch;
    touch = (CCTouch*)(*iterator);
    CCPoint tap;
    tap = convertPoint(touch->getLocation());
    //tag->setPosition(tap);
    
    CCPoint pointInTable = convertPoint_LayerToTable(tap);
    //tag2->setPosition(pointInTable);
    int index = getIndexFromPosition(pointInTable);
    if (index > -1) {
        // kiểm tra xem có phải đã click vào 1 trong các quân cờ của mình hay ko
        // nếu có thì gán cho indexCurrent
        bool isClick = false;
        for (int i = 0; i < 16; i++) {
            Chess *chess= arrChess.at(i);
            if (chess->getIDPos() == index) {
                indexCurrent = index;
                chess->setClick(true);
				playSound("Click.mp3");

                if (isRedChess){
					// nếu mình là quân đỏ thì mọi thao tác sẽ phải convertID 
					vector<int> arrID = logicChess->getAllMovesFromPos(convertID(indexCurrent));
					vector<int> arrIDConvert;
					for (int i = 0; i < arrID.size(); i++) 
					{
						int id = arrID.at(i);
						if (id < 0)
						{
							break;
						}
						arrIDConvert.push_back(convertID(id));
					}
                    drawCanMove(arrIDConvert);
				}
				else {
					vector<int> arrID = logicChess->getAllMovesFromPos(indexCurrent);
					vector<int> arrIDConvert;
					for (int i = 0; i < arrID.size(); i++) 
					{
						int id = arrID.at(i);
						if (id < 0)
						{
							break;
						}
						arrIDConvert.push_back(id);
					}
					
					drawCanMove(arrIDConvert);
				}

                
                isClick = true;
            }
            else {
                chess->setClick(false);
            }
        }
        // nếu click vào thì ko có gì đáng bàn
        // ngược lại nếu ko click vào quân cờ nào của mình và trước đó đã click rồi thì
        if (!isClick && indexCurrent > -1) {
			playSound("Click.mp3");

            // gửi lên sv
            indexTarget = index;
            
            if (isRedChess) {
                indexCurrent = convertID(indexCurrent);
                indexTarget = convertID(indexTarget);
            }
            
            if (indexCurrent > -1 && indexTarget > -1){
                boost::shared_ptr<ISFSObject> params (new SFSObject());
                params->PutInt("mf", indexCurrent);
                params->PutInt("mt", indexTarget);
                boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
                boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_MOVE), params, lastRoom));
                GameServer::getSingleton().getSmartFox()->Send(request);

				CCLOG("Đã gửi indexCurrent = %d, indexTarget  = %d", indexCurrent, indexTarget);

				vector<int> ar;
				drawCanMove(ar);
            }
            CCLog("indexCurrent = %d", indexCurrent);
            CCLog("indexTarget  = %d", indexTarget);
            
            // reset
            indexCurrent = -1;
            indexTarget  = -1;
        }
    }
}

void LayerPlayGameChinessChess::createChess() {
    // quan do
    Chess *xe_red_1 = new Chess(1, ROOK, 0);
    Chess *ma_red_1 = new Chess(1, KNIGHT, 1);
    Chess *tuongj_red_1 = new Chess(1, ELEPHANT, 2);
    Chess *si_red_1 = new Chess(1, BISHOP, 3);
    Chess *tuong_red = new Chess(1, KING, 4);
    Chess *si_red_2 = new Chess(1, BISHOP, 5);
    Chess *tuongj_red_2 = new Chess(1, ELEPHANT, 6);
    Chess *ma_red_2 = new Chess(1, KNIGHT, 7);
    Chess *xe_red_2 = new Chess(1, ROOK, 8);
    Chess *phao_red_1 = new Chess(1, CANNON, 19);
    Chess *phao_red_2 = new Chess(1, CANNON, 25);
    Chess *tot_red_1 = new Chess(1, PAWN, 27);
    Chess *tot_red_2 = new Chess(1, PAWN, 29);
    Chess *tot_red_3 = new Chess(1, PAWN, 31);
    Chess *tot_red_4 = new Chess(1, PAWN, 33);
    Chess *tot_red_5 = new Chess(1, PAWN, 35);
    //
    
    Chess *xe_blue_1 = new Chess(2, ROOK, 81);
    Chess *ma_blue_1 = new Chess(2, KNIGHT, 82);
    Chess *tuongj_blue_1 = new Chess(2, ELEPHANT, 83);
    Chess *si_blue_1 = new Chess(2, BISHOP, 84);
    Chess *tuong_blue = new Chess(2, KING, 85);
    Chess *si_blue_2 = new Chess(2, BISHOP, 86);
    Chess *tuongj_blue_2 = new Chess(2, ELEPHANT, 87);
    Chess *ma_blue_2 = new Chess(2, KNIGHT, 88);
    Chess *xe_blue_2 = new Chess(2, ROOK, 89);
    Chess *phao_blue_1 = new Chess(2, CANNON, 64);
    Chess *phao_blue_2 = new Chess(2, CANNON, 70);
    Chess *tot_blue_1 = new Chess(2, PAWN, 54);
    Chess *tot_blue_2 = new Chess(2, PAWN, 56);
    Chess *tot_blue_3 = new Chess(2, PAWN, 58);
    Chess *tot_blue_4 = new Chess(2, PAWN, 60);
    Chess *tot_blue_5 = new Chess(2, PAWN, 62);
    
    //
    //
    arrChess.push_back(xe_red_1);
    arrChess.push_back(ma_red_1);
    arrChess.push_back(tuongj_red_1);
    arrChess.push_back(si_red_1);
    arrChess.push_back(tuong_red);
    arrChess.push_back(si_red_2);
    arrChess.push_back(tuongj_red_2);
    arrChess.push_back(ma_red_2);
    arrChess.push_back(xe_red_2);
    arrChess.push_back(phao_red_1);
    arrChess.push_back(phao_red_2);
    arrChess.push_back(tot_red_1);
    arrChess.push_back(tot_red_2);
    arrChess.push_back(tot_red_3);
    arrChess.push_back(tot_red_4);
    arrChess.push_back(tot_red_5);
    //
    arrChess.push_back(xe_blue_1);
    arrChess.push_back(ma_blue_1);
    arrChess.push_back(tuongj_blue_1);
    arrChess.push_back(si_blue_1);
    arrChess.push_back(tuong_blue);
    arrChess.push_back(si_blue_2);
    arrChess.push_back(tuongj_blue_2);
    arrChess.push_back(ma_blue_2);
    arrChess.push_back(xe_blue_2);
    arrChess.push_back(phao_blue_1);
    arrChess.push_back(phao_blue_2);
    arrChess.push_back(tot_blue_1);
    arrChess.push_back(tot_blue_2);
    arrChess.push_back(tot_blue_3);
    arrChess.push_back(tot_blue_4);
    arrChess.push_back(tot_blue_5);
    
    for (int i = 0; i < arrChess.size(); i++) {
        nodeTableChess->addChild(arrChess.at(i));
    }
    refreshChess();
}

void LayerPlayGameChinessChess::refreshChess() {
    // Đặt lại vị trí của quân cờ theo đúng id_pos
    for (int i = 0; i < arrChess.size(); i++) {
        Chess *chess = arrChess.at(i);
        chess->setPosition(getPositionFromIndex(chess->getIDPosInit()));
        chess->setIDPos(chess->getIDPosInit());
        chess->setZOrder(0);
        chess->setVisible(true);
        chess->setClick(false);
    }
}

void LayerPlayGameChinessChess::drawChess() {
	Chess *chess;
	int id_pos;
	for (int i = 0; i < arrChess.size(); i++) {
		chess = arrChess.at(i);
		id_pos = chess->getIDPos();
		if (id_pos < 0 || id_pos > 89) {
			chess->setVisible(false);
		} else{
			chess->setVisible(true);
			chess->setPosition(getPositionFromIndex(id_pos));
			chess->setZOrder(0);
			chess->setClick(false);
		}
	}
}

void LayerPlayGameChinessChess::drawCanMove(vector<int> arrPos) {
    for (int i = 0; i < 90; i++) {
        setPointVisiable(i, false);
    }
    
    for (int i = 0; i < arrPos.size(); i++) {
        int pos = arrPos.at(i);
        if (pos >= 0 && pos < 90) setPointVisiable(pos, true);
    }
}

Chess* LayerPlayGameChinessChess::getChessByName_Side(int name, int side) {
	/* 
	int PAWN = 0;   // tốt
	int BISHOP = 1;   // sỹ
	int ELEPHANT = 2; // tượng
	int KNIGHT = 3;   // mã
	int CANNON = 4;	  // pháo
	int ROOK = 5;	  // xe
	int KING = 6;	  // tướng
	int EMPTY = 7;
	*/  
	
	// trả lại 1 quân cờ dựa vào name và side 
	// dk cần: id_pos < 0

	int i, leng = arrChess.size();
	Chess *chess;
	for (i = 0; i < leng; i++) 
	{
		chess = arrChess.at(i);
		if (chess->getIDPos() < 0 && chess->getName() == name && chess->getSide() == side) {
			return chess;
		}
	}

	return NULL;
}

LayerPlayGameChinessChess::~LayerPlayGameChinessChess()
{
    GameServer::getSingleton().removeListeners(this);
	//
	CC_SAFE_DELETE(imagedownloader4Red);
	CC_SAFE_DELETE(imagedownloader4Black);
}

float LayerPlayGameChinessChess::getDistant2Point(CCPoint p1, CCPoint p2) {
    return sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}

/*
 hàm này có tác dụng lấy vị trí của 1 điểm trên bàn cờ
 , để set vị trí cho 1 quân cờ tại 1 vị trí
 id = [0..89], tứ duới lên trên
 */
CCPoint LayerPlayGameChinessChess::getPositionFromIndex(int id){
    CCNode* nodeChild = nodePoint->getChildByTag(id/9);
    if( !nodeChild ){
        return CCPointZero;
    }
    CCNode* c = nodeChild->getChildByTag(id);
    if( !nodeChild ){
        return CCPointZero;
    }
    return c->getPosition();
}

int LayerPlayGameChinessChess::getIndexFromPosition(cocos2d::CCPoint pos) {
    for (int i = 0; i < 90; i++) {
        CCPoint point = getPositionFromIndex(i);
        if (getDistant2Point(pos, point) < 20){
            return i;
        }
    }
    
    return -1;
}

/*
 hàm này có tác dụng hiển thị 1 điểm, cho việc hiện các nước có thể đi đc
 id = [0..89], tứ duới lên trên
 */
void LayerPlayGameChinessChess::setPointVisiable(int id, bool isShow){
    CCNode* nodeChild = nodePoint->getChildByTag(id/9);
    if( !nodeChild ){
        return ;
    }
    CCNode* c = nodeChild->getChildByTag(id);
    if( !nodeChild ){
        return ;
    }
    c->setVisible(isShow);
}

void LayerPlayGameChinessChess::actionMenu() {
	if (menuLayer->isVisible()) hideMenu();
	else showMenu();
}

void LayerPlayGameChinessChess::hideMenu() {
	if (menuLayer == NULL || menuBgr == NULL) return;

	if (menuLayer->isVisible()) {
		menuLayer->setVisible(false);
		menuLayer->getWidgetByTag(kTagButtonBack)->setTouchEnabled(false);
		menuLayer->getWidgetByTag(kTagButtonSitting)->setTouchEnabled(false);
		menuLayer->getWidgetByTag(kTagButtonStandUp)->setTouchEnabled(false);
	}
	if (menuBgr->isVisible()) menuBgr->setVisible(false);
}

void LayerPlayGameChinessChess::showMenu() {
	if (!menuLayer->isVisible()) {
		menuLayer->setVisible(true);
		menuLayer->getWidgetByTag(kTagButtonBack)->setTouchEnabled(true);
		menuLayer->getWidgetByTag(kTagButtonSitting)->setTouchEnabled(true);
		menuLayer->getWidgetByTag(kTagButtonStandUp)->setTouchEnabled(true);
	}
	if (!menuBgr->isVisible()) menuBgr->setVisible(true);
}

void LayerPlayGameChinessChess::showChat(string mes) {
	Chat *noti = new Chat(mes, -1);
	this->addChild(noti, 100);
}

void LayerPlayGameChinessChess::loadAllDatas(){
}

void LayerPlayGameChinessChess::onButtonBack(CCObject* pSender){
    // leave room
    /*boost::shared_ptr<IRequest> request (new LeaveRoomRequest());
    GameServer::getSingleton().getSmartFox()->Send(request);
    
    GameServer::getSingleton().removeListeners(this);
    this->removeAllChildrenWithCleanup(true);
    
    SceneManager::getSingleton().gotoMain();*/
	
	actionMenu();
}
void LayerPlayGameChinessChess::onButtonSetting(CCObject* pSender){
	hideMenu();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerSettings* mLayerSettings;
	if (ccbReader)
	{
		mLayerSettings = (LayerSettings *)ccbReader->readNodeGraphFromFile( "LayerSettings.ccbi" );
		this->addChild(mLayerSettings, 1, 1);
		ccbReader->release();
	}
}
void LayerPlayGameChinessChess::onButtonMoney(CCObject* pSender){
	hideMenu(); 
	//
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerChargeMoney* mLayer;
	if (ccbReader)
	{
		mLayer = (LayerChargeMoney *)ccbReader->readNodeGraphFromFile( "LayerPopupChargeMoney.ccbi" );
		mLayer->setIsPopup(true);
		//this->getParent()->addChild(mLayer, 1, 1);
		this->addChild(mLayer, 1, 1);
		mLayer->setTouchEnabled(true);
		ccbReader->release();
	}
}
void LayerPlayGameChinessChess::onButtonChat(CCObject* pSender){
	hideMenu();

	if (isSpector) {
		showChat("Bạn đang ở chế độ khách!");
		return;
	}

	LayerChatWindow* l = SceneManager::getSingleton().getLayerChatWindow();
	l->setCallbackFunc(this,callfuncND_selector(LayerButtonInGame::callbackFromChatWindow));
	SceneManager::getSingleton().showLayerChatWindow();
}
void LayerPlayGameChinessChess::callbackFromChatWindow( CCNode*, void* data )
{
	if( strlen((char*)data)==0 )
		return;
	boost::shared_ptr<ISFSObject> parameters(new SFSObject());
	boost::shared_ptr<IRequest> request (new PublicMessageRequest((char*)data, parameters, GameServer::getSingleton().getSmartFox()->LastJoinedRoom())); 
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerPlayGameChinessChess::onButtonLose(CCObject* pSender){
	hideMenu();
    /**/
	if (isSpector){
		//showChat("Bạn đang ở chế độ khách!");
		return;
	}

	if (!isStartedGame) {
		showChat("Chưa bắt đầu game!");
		return;
	}
	
	LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
	if( !SceneManager::getSingleton().showNotification() ){
		CCLOG("NTF Dialog already open!");
		return;
	}
	layer->setNotificationOptions("XIN THUA", 
		"Bạn chắc muốn XIN THUA chứ?", true, "Ok", DONG_Y_XIN_THUA, this);
}
void LayerPlayGameChinessChess::onButtonPeace(CCObject* pSender){
	hideMenu();
	if (isSpector)
	{
		//showChat("Bạn đang ở chế độ khách!");
		return;
	}

	if (!isStartedGame) {
		showChat("Chưa bắt đầu game!");
		return;
	}

	LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
	if( !SceneManager::getSingleton().showNotification() ){
		CCLOG("NTF Dialog already open!");
		return;
	}
	layer->setNotificationOptions("XIN HÒA", 
		"Bạn chắc muốn XIN HÒA chứ?", true, "Ok", DONG_Y_XIN_HOA, this);

}

void LayerPlayGameChinessChess::notificationCallBack( bool isOK, int tag )
{
	switch (tag){
	case DONG_Y_CHO_HOA:
		if( isOK ){
			// gửi lại sv là mình đồng ý (rep=1)
			boost::shared_ptr<ISFSObject> parameter (new SFSObject());
			parameter->PutInt("rep", 1);
			boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REPLY_FOR_PEACE), parameter, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
		}
		break;
	case DONG_Y_CHO_DI_LAI:
		if( isOK ){
			// gửi lại sv là mình đồng ý (rep=1)
			boost::shared_ptr<ISFSObject> parameter (new SFSObject());
			parameter->PutInt("rep", 1);
			boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REPLY_UNDO_MOVE), parameter, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
		}
		break;
	case DONG_Y_XIN_HOA:
		if( isOK ){
			boost::shared_ptr<ISFSObject> parameter (new SFSObject());
			boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_FOR_PEACE), parameter, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
		}
		break;
	case DONG_Y_XIN_THUA:
		if( isOK ){
			boost::shared_ptr<ISFSObject> parameter (new SFSObject());
			boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_IM_LOSE), parameter, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
		}
		break;
	case DONG_Y_XIN_DI_LAI:
		if( isOK ){
			CCLOG("Dong y di lai");
			boost::shared_ptr<ISFSObject> parameter (new SFSObject());
			parameter->PutLong("amf", 1000);
			boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_UNDO_MOVE_REQ), parameter, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
		}
		break;
	}
}

void LayerPlayGameChinessChess::onButtonRemove(CCObject* pSender){
	hideMenu();

	if (isSpector) {
		//showChat("Bạn đang ở chế độ khách!");
		return;
	}

	if (!isStartedGame) {
		showChat("Chưa bắt đầu game!");
		return;
	}

	LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
	if( !SceneManager::getSingleton().showNotification() ){
		return;
	}
	layer->setNotificationOptions("ĐI LẠI", 
		"Bạn chắc muốn XIN ĐI LẠI chứ?", true, "Ok", DONG_Y_XIN_DI_LAI, this);
}
void LayerPlayGameChinessChess::onButtonReady(CCObject* pSender){
	hideMenu();
    btnReady->setEnabled(false);
    btnReady->setVisible(false);
//    btnUnReady->setEnabled(true);
//    btnUnReady->setVisible(true);
    btnUnReady->setEnabled(false);
    btnUnReady->setVisible(false);
    
    boost::shared_ptr<ISFSObject> parameter (new SFSObject());
    boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_READY_REQ), parameter, lastRoom));
    GameServer::getSingleton().getSmartFox()->Send(request);
}
void LayerPlayGameChinessChess::onButtonUnReady(CCObject* pSender){
    CCLog("clicked unready");
    btnReady->setEnabled(true);
    btnReady->setVisible(true);
    btnUnReady->setEnabled(false);
    btnUnReady->setVisible(false);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerPlayGameChinessChess::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnBack", LayerPlayGameChinessChess::onButtonBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSetting", LayerPlayGameChinessChess::onButtonSetting);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnMoney", LayerPlayGameChinessChess::onButtonMoney);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChat", LayerPlayGameChinessChess::onButtonChat);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnLose", LayerPlayGameChinessChess::onButtonLose);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnPeace", LayerPlayGameChinessChess::onButtonPeace);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnReMove", LayerPlayGameChinessChess::onButtonRemove);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnReady", LayerPlayGameChinessChess::onButtonReady);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnReadyHover", LayerPlayGameChinessChess::onButtonUnReady);
    return NULL;
}

// CCBMemberVariableAssigner interface
bool LayerPlayGameChinessChess::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeAvatarRed", CCNode*, nodeAvatarRed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblNameRed", CCLabelTTF*, lblNameRed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoneyRed", CCLabelTTF*, lblMoneyRed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblWinRateRed", CCLabelTTF*, lblWinRateRed);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeAvatarBlack", CCNode*, nodeAvatarBlack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblNameBlack", CCLabelTTF*, lblNameBlack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoneyBlack", CCLabelTTF*, lblMoneyBlack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblWinRateBlack", CCLabelTTF*, lblWinRateBlack);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "box_time_focus_red", CCSprite*, box_time_focus_red);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "box_time_focus_black", CCSprite*, box_time_focus_black);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "readyRed", CCSprite*, readyRed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTimeRed", CCLabelTTF*, lblTimeRed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTotalTimeRed", CCLabelTTF*, lblTotalTimeRed);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "readyBlack", CCSprite*, readyBlack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTimeBlack", CCLabelTTF*, lblTimeBlack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTotalTimeBlack", CCLabelTTF*, lblTotalTimeBlack);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTableChess", CCNode*, nodeTableChess);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodePoint", CCNode*, nodePoint);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblXeRed_status", CCLabelTTF*, lblXeRed_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTotRed_status", CCLabelTTF*, lblTotRed_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMaRed_status", CCLabelTTF*, lblMaRed_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblPhaoRed_status", CCLabelTTF*, lblPhaoRed_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTuongRed_status", CCLabelTTF*, lblTuongRed_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblSyRed_statuss", CCLabelTTF*, lblSyRed_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblXeBlack_status", CCLabelTTF*, lblXeBlack_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTotBlack_status", CCLabelTTF*, lblTotBlack_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMaBlack_status", CCLabelTTF*, lblMaBlack_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblPhaoBlack_status", CCLabelTTF*, lblPhaoBlack_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTuongBlack_status", CCLabelTTF*, lblTuongBlack_status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblSyBlack_status", CCLabelTTF*, lblSyBlack_status);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnReady", CCMenuItem*, btnReady);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnReadyHover", CCMenuItem*, btnUnReady);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnLose", CCMenuItem*, btnLose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnPeace", CCMenuItem*, btnPeace);    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnReMove", CCMenuItem*, btnReMove);

    return true;
}

void LayerPlayGameChinessChess::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{	
	myName = SceneManager::getSingleton().getMyName();
	isRegistSitdown = false;
	isClickedBack = false;
	isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName)->IsSpectator();
	if (isSpector) {
		isRedChess = false;
		btnReady->setEnabled(false);
		btnReady->setVisible(false);

		showChat("Bạn đang ở chế độ khách!");
	}

	lblYouIsGuess = CCLabelTTF::create("Bạn đang là khách!", "", 24);
	lblYouIsGuess->setColor(ccWHITE);
	lblYouIsGuess->setPosition(btnPeace->getPosition());
	//this->addChild(lblYouIsGuess);

	boost::shared_ptr<Room> room = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<RoomVariable> rv = room->GetVariable("params");
	string s = *rv->GetStringValue();

// 	vector<string> lstBet = mUtils::splitString( s, '@' );
// 	lstBet.at(1).compare("1")==0 ? (isStartedGame = true) : (isStartedGame = false);
// 	if (isStartedGame) {
// 		CCLog("Ban dang choi!");
// 	} else CCLog("Ban chua choi!");

	

    logicChess = new ChessLogic();
    logicChess->loadNewGame();
    
    this->setTouchEnabled(true);
    
    createChess();

	CCSize sizeTable = nodeTableChess->getContentSize();
    chieuTuongRed = CCSprite::create("chess/attack1.png");
	chieuTuongRed->setPosition(ccp(sizeTable.width / 2, sizeTable.height / 2 - 100));
	chieuTuongRed->setVisible(false);
	chieuTuongBlack = CCSprite::create("chess/attack2.png");
	chieuTuongBlack->setPosition(ccp(sizeTable.width / 2, sizeTable.height / 2 + 100));
	chieuTuongBlack->setVisible(false);
	nodeTableChess->addChild(chieuTuongRed, 100);
	nodeTableChess->addChild(chieuTuongBlack, 100);

    // Khoi tao cac doi tuong o day
	//
	indexCurrent = -1;
    indexTarget = -1;
  
    //
    lblNameRed->setString("--");
    lblMoneyRed->setString("--");
    lblWinRateRed->setString("--");
    lblTimeRed->setString("--");
    lblTotalTimeRed->setString("--");
    lblXeRed_status->setString("x2");
    lblPhaoRed_status->setString("x2");
    lblMaRed_status->setString("x2");
    lblTotRed_status->setString("x5");
    lblTuongRed_status->setString("x2");
    lblSyRed_status->setString("x2");
    //
    lblNameBlack->setString("--");
    lblMoneyBlack->setString("--");
    lblWinRateBlack->setString("--");
    lblTimeBlack->setString("--");
    lblTotalTimeBlack->setString("--");
    lblXeBlack_status->setString("x2");
    lblPhaoBlack_status->setString("x2");
    lblMaBlack_status->setString("x2");
    lblTotBlack_status->setString("x5");
    lblTuongBlack_status->setString("x2");
    lblSyBlack_status->setString("x2");

	// thông tin bàn chơi và mức cược
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = split(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	//string name = mu.getGameNameByID(id);
	string name = " ";
	string moneyConvert = mu.convertMoneyEx(atoi(money.c_str()));

	string result = "";
	if (name.length() > 0 && moneyConvert.length() > 0)
	{
		result = "Cược:" + moneyConvert;
	}
	CCLabelTTF *nameGame= CCLabelTTF::create(result.c_str(), "", 16);
	nameGame->setPosition(ccp(nodeTableChess->getContentSize().width / 2, nodeTableChess->getContentSize().height / 2));
	nameGame->setColor(ccBLACK);
	nameGame->setOpacity(100);
	nodeTableChess->addChild(nameGame, 0);


	// popup - back, sitting, stand up, ...
	// popup = PopupLayer::create("HelloWorld.png");
	//this->addChild(popup, 100);

	

	

	menuBgr = CCSprite::create("menu_bgr.png");
	menuBgr->setAnchorPoint(ccp(1, 1));
	menuBgr->setPosition(ccp(800 - 54, 480));
	this->addChild(menuBgr);

	menuLayer = UILayer::create();
	this->addChild(menuLayer);

	CCSize sizeMenu = menuBgr->boundingBox().size;
	float x = menuBgr->getPositionX();
	float y = menuBgr->getPositionY();
	Button *btn = createButtonWithTitle_Position("Trở lại", ccp(x - sizeMenu.width/2, y - sizeMenu.height/10 - 3));
	btn->addTouchEventListener(this, toucheventselector(LayerPlayGameChinessChess::actionBack));
	btn->setTag(kTagButtonBack);
	menuLayer->addWidget(btn);
	btn = createButtonWithTitle_Position("Ngồi xuống", ccp(x - sizeMenu.width/2, y - sizeMenu.height/10*3));
	btn->addTouchEventListener(this, toucheventselector(LayerPlayGameChinessChess::actionSit));
	btn->setTag(kTagButtonSitting);
	menuLayer->addWidget(btn);
	btn = createButtonWithTitle_Position("Đứng lên", ccp(x - sizeMenu.width/2, y - sizeMenu.height/10*5 + 3));
	btn->setTag(kTagButtonStandUp);
	btn->addTouchEventListener(this, toucheventselector(LayerPlayGameChinessChess::actionStand));
	menuLayer->addWidget(btn);

	hideMenu();
    
    return;
}



Button* LayerPlayGameChinessChess::createButtonWithTitle_Position(const char *title, CCPoint pPoint) {
	// Create the button
	Button* button = Button::create();
	button->setTouchEnabled(true);
	button->setScale9Enabled(false);
	button->loadTextures("action_bgr.png", "action_bgr_hover.png", "");
	button->setTitleText(title);
	button->setTitleColor(ccWHITE);
	button->setTitleFontSize(65/3);
	button->setAnchorPoint(ccp(0.5, 0.5));
	button->setPosition(pPoint);
	button->setScale(0.8);
	return button;
}

void LayerPlayGameChinessChess::actionBack(CCObject *pSender, TouchEventType pType) {
	if (pType == TOUCH_EVENT_BEGAN) {
		CCLog("actionBack");
		isClickedBack = true;

		GameServer::getSingleton().removeListeners(this);
		this->removeAllChildrenWithCleanup(true);

		if( GameServer::getSingleton().getSmartFox()->LastJoinedRoom()==NULL ){
			SceneManager::getSingleton().gotoMain();
			return;
		} 
		boost::shared_ptr<string> gameID = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId();
		if (gameID == NULL) {
			return;
		}

		SceneManager::getSingleton().gotoMain();
		LayerMain::getSingleton().gotoChonBanChoi( atol(gameID->c_str()) );

		// leave room
		boost::shared_ptr<IRequest> request (new LeaveRoomRequest());
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void LayerPlayGameChinessChess::actionSit(CCObject *pSender, TouchEventType pType) {
	if (pType == TOUCH_EVENT_BEGAN) {
		if (isSpector) {
			if (isStartedGame) {
				if (!isRegistSitdown){
					showChat("Bạn vừa đăng ký tham gia chơi, vui lòng chờ!");
					isRegistSitdown = true;
					CCLog("Bạn vừa đăng ký tham gia chơi, vui lòng chờ!");
				}
			} else {
				// join game
				boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest());
				GameServer::getSingleton().getSmartFox()->Send(request);
				isRegistSitdown = false;
				CCLog("Join Game to SV");
			}
		}

		hideMenu();
	}
}

void LayerPlayGameChinessChess::actionStand(CCObject *pSender, TouchEventType pType) {
	if (pType == TOUCH_EVENT_BEGAN) {
		hideMenu();

		if (!isSpector) {
			if (countUser < 2) {
				showChat("Không thể đứng lên khi phòng chỉ có mỗi bạn!");
				return;
			}

			if (isStartedGame) {
				if (!isRegistStandUp){
					showChat("Bạn vừa đăng ký đứng xem ở ván kế tiếp");
					isRegistStandUp = true;
					CCLog("Bạn vừa đăng ký đứng xem ở ván kế tiếp");
				}

			} else {
				boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest());
				GameServer::getSingleton().getSmartFox()->Send(request);
				isRegistStandUp = false;
				CCLog("out game!");
			}
		}

	}
}

void LayerPlayGameChinessChess::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	int    money = (int) (*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	string name = boost::to_string(*ptrNotifiedUser->Name());

	CCLOG("Update User Variables name=%s, money=%d", name.c_str(), money);

}

void LayerPlayGameChinessChess::OnSmartFoxPublicMessage( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
	//
	CCLOG("ptrNotifiedMessage: %s", ptrNotifiedMessage->c_str());
	//
	Chat *newMes = new Chat(ptrNotifiedMessage->c_str(), kUserMe);
	newMes->setStatusByServer(false);

	CCPoint point;
	string name = ptrNotifiedUser->Name()->c_str();

	// neu la minh thi ko dc chat
	if (name == myName && isSpector) return;

	if (name == myName || name == player2) {
		point.setPoint(20, 176);
	}
	else {
		point.setPoint(20, 363);
	}

	newMes->setPosition(point);
	this->addChild(newMes);
}

void LayerPlayGameChinessChess::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//
	if( ptrNotifiedUser->IsItMe() ){
		//close window - tricks by HoangDD
		this->onButtonBack(NULL);
	}
}

void LayerPlayGameChinessChess::OnSmartFoxRoomVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEvetnParams)["room"];
	boost::shared_ptr<Room> room = ((boost::static_pointer_cast<Room>(ptrEventParamValueRoom)));
	//
	return;
	boost::shared_ptr<RoomVariable> rv = room->GetVariable("params");
	string s = *rv->GetStringValue();
	CCLOG("Room %s update RoomVariables: %s", room->Name()->c_str(), s.c_str());

	vector<string> lstBet = mUtils::splitString( s, '@' );
	lstBet.at(1).compare("1")==0 ? (isStartedGame = true) : (isStartedGame = false);

	isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName)->IsSpectator();
	if (isSpector) {
		CCLog("Ban la khach");
		btnReady->setEnabled(false);
		btnReady->setVisible(false);
		btnUnReady->setEnabled(false);
		btnUnReady->setVisible(false);

		showChat("Bạn đang ở chế độ khách!");
	}


	if (isStartedGame) {
		CCLOG("Game dang choi");
	}
	else {
		CCLOG("Game chua bat dau");
		// Game đang ko diễn ra, có thể gửi đi thông báo đứng xem
		if (!isSpector && isRegistStandUp) {
			boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest());
			GameServer::getSingleton().getSmartFox()->Send(request);
			isRegistStandUp = false;
			CCLog("Gui di thong bao muon dung len!");
		}

		// có thể gửi đi thông báo muốn ngồi vào bàn chơi
		if (isSpector && isRegistSitdown) {
			boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest());
			GameServer::getSingleton().getSmartFox()->Send(request);
			isRegistSitdown = false;
			CCLog("Gui di thong bao muon ngoi xuong!");
		}
	}
}

void LayerPlayGameChinessChess::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    this->param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    //
    if(strcmp("hbc", cmd->c_str())==0){
        return;
    }
    
    switch(convertResponseToInt(cmd->c_str())) {
		case EXT_EVENT_CHESS_TABLE_NTF:
			event_EXT_EVENT_CHESS_TABLE_NTF();
			break;

        case EXT_EVENT_START:
            event_EXT_EVENT_START();
            break;
            
        case EXT_EVENT_NEXT_TURN:        
            event_EXT_EVENT_NEXT_TURN();
            break;
            
        case EXT_EVENT_END:
            event_EXT_EVENT_END();
            break;
            
        case EXT_EVENT_READY_NTF:
            event_EXT_EVENT_READY_NTF();
            break;
            
        case EXT_EVENT_GAME_RESULT:
            event_EXT_EVENT_GAME_RESULT();
            break;
            
        case EXT_EVENT_ERROR_READY_NTF:
            event_EXT_EVENT_ERROR_READY_NTF();
            break;
            
        case EXT_EVENT_LIST_USER_UPDATE:
            event_EXT_EVENT_LIST_USER_UPDATE();
            break;
            
        case EXT_EVENT_MOVE_NTF:
            event_EXT_EVENT_MOVE_NTF();
            break;
            
        case EXT_EVENT_FOR_PEACE_NTF:
            event_EXT_EVENT_FOR_PEACE_NTF();
            break;

		case EXT_EVENT_UNDO_MOVE_REQ:
			event_EXT_EVENT_UNDO_MOVE_REQ();
			break;

		case EXT_EVENT_UNDO_MOVE_NTF:
			event_EXT_EVENT_UNDO_MOVE_NTF();
			break;
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_START(){
    CCLog("event_EXT_EVENT_START:: start game!");
	playSound("StartGame.mp3");
    
    isStartedGame = true;
    timeRestBlack = 900;
    timeRestRed   = 900;
	timeToReady	  = 20;
    
    btnReady->setEnabled(false);
    btnReady->setVisible(false);
    btnUnReady->setEnabled(false);
    btnUnReady->setVisible(false);
    
    readyRed->setVisible(false);
    readyBlack->setVisible(false);


	lblXeRed_status->setString("x2");
	lblPhaoRed_status->setString("x2");
	lblMaRed_status->setString("x2");
	lblTotRed_status->setString("x5");
	lblTuongRed_status->setString("x2");
	lblSyRed_status->setString("x2");
	//
	lblXeBlack_status->setString("x2");
	lblPhaoBlack_status->setString("x2");
	lblMaBlack_status->setString("x2");
	lblTotBlack_status->setString("x5");
	lblTuongBlack_status->setString("x2");
	lblSyBlack_status->setString("x2");

	chieuTuongBlack->setVisible(false);
	chieuTuongRed->setVisible(false);
    
    refreshChess();
}

void LayerPlayGameChinessChess::event_EXT_EVENT_NEXT_TURN(){
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    boost::shared_ptr<string> list_time = param->GetUtfString("crt");
	boost::shared_ptr<long> tft = param->GetInt("tft");
    
    if (name != NULL && list_time != NULL && tft != NULL) {
        CCLog("event_EXT_EVENT_NEXT_TURN:: name=%s, list_time=%s, turn_time=%d", name->c_str(), list_time->c_str(), *tft);
        
		// nếu là ban đầu thì kiểm tra xem người đi đầu là mình hay đối thủ
		if (nameCurrentTurn.length() < 2)
		{
			isIamTheFirst = (myName == name->c_str());
		}
		

        nameCurrentTurn = name->c_str();
        
        if (nameCurrentTurn == myName){
            box_time_focus_black->setVisible(true);
            box_time_focus_red->setVisible(false);
			Chat *noti = new Chat("Tới lượt bạn!", -1);
			noti->setPositionY(70);
			noti->setPositionX(nodeTableChess->getContentSize().width/2 - noti->getSize().width/2);
			nodeTableChess->addChild(noti, 100);

			timeForTurnBlack = *tft;
        }
        else {
            box_time_focus_red->setVisible(true);
            box_time_focus_black->setVisible(false);

			timeForTurnRed = *tft;
        }
        
        // ptich chuoi thanhhv|900;thanhhv2|900;
        string lsTime =  list_time->c_str();
		if (lsTime.length() < 2) return;
        vector<string> arrLsTime = split(lsTime, ';');
        
        // Player 1
        vector<string> arrInfo_1 = split(arrLsTime[0], '|');
        string name =arrInfo_1[0];
        string money = arrInfo_1[1];
        if (name == myName || name == player1) {
            timeRestBlack = atoi(money.c_str());
        } else timeRestRed = atoi(money.c_str());
        
        // Player 2
        vector<string> arrInfo_2 = split(arrLsTime[1], '|');
        name =arrInfo_2[0];
        money = arrInfo_2[1];
        if (name == myName || name == player2) {
            timeRestBlack = atoi(money.c_str());
        } else timeRestRed = atoi(money.c_str());
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_END(){
    CCLog("event_EXT_EVENT_END:: end game!");
    
    logicChess->loadNewGame();
    nameCurrentTurn = "";
	player1 = "";
	player2 = "";
	isIamTheFirst  = false;
	isStartedGame = false;
    
	if (!isSpector) {
		btnReady->setEnabled(true);
		btnReady->setVisible(true);
	}
    
    // reset
    indexCurrent = -1;
    indexTarget  = -1;

	chieuTuongBlack->setVisible(false);
	chieuTuongRed->setVisible(false);

	isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName)->IsSpectator();
	if (isSpector) {
		btnReady->setEnabled(false);
		btnReady->setVisible(false);
		btnUnReady->setEnabled(false);
		btnUnReady->setVisible(false);
	}

	if (!isSpector && isRegistStandUp) {
		boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest());
		GameServer::getSingleton().getSmartFox()->Send(request);
		isRegistStandUp = false;
	}

	if (isSpector && isRegistSitdown) {
		boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest());
		GameServer::getSingleton().getSmartFox()->Send(request);
		isRegistSitdown = false;
	}
}

void LayerPlayGameChinessChess::event_EXT_EVENT_READY_NTF(){
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    
	if (isSpector) {
		if (name->c_str() == player1) {
			readyRed->setVisible(true);
		}
		else {
			readyBlack->setVisible(true);
		}

		return;
	}

    if (name != NULL ) {
        CCLog("event_EXT_EVENT_READY_NTF:: name=%s", name->c_str());
        
        if (name->c_str() == myName){
			readyBlack->setVisible(true);
			timeToReady = -1;
		}
        else readyRed->setVisible(true);
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_GAME_RESULT(){
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    boost::shared_ptr<string> result = param->GetUtfString("rg");
	boost::shared_ptr<long> wt = param->GetInt("wt");

    if (name != NULL && result != NULL && wt != NULL) {
        //name=thanhhv2, result=-0|0
        CCLog("event_EXT_EVENT_GAME_RESULT:: name=%s, result=%s, wt=%d", name->c_str(), result->c_str(), *wt);
        showChat("Kết thúc ván");

        string lsmoney = result->c_str();
		if (lsmoney.length() < 2) return;
        vector<string> arrMoney = split(lsmoney, '|');
        if (name->c_str() == myName) {
            Number *numMoney0 = new Number(arrMoney[0]);
            numMoney0->setZOrder(10);
            numMoney0->setPositionStart(ccp(10, 120));
            this->addChild(numMoney0);
            
            Number *numMoney1 = new Number(arrMoney[1]);
            numMoney1->setZOrder(10);
            numMoney1->setPositionStart(ccp(10, 312));
            this->addChild(numMoney1);

			if (isSpector) {
				playSound("Win.mp3");
				return;
			}
			playSound("Lose.mp3");
			CCSprite *iconLose = CCSprite::create("chess/iconlose.png");
			iconLose->setPosition(ccp(nodeTableChess->getContentSize().width/2, nodeTableChess->getContentSize().height/2));
			iconLose->setZOrder(100);
			nodeTableChess->addChild(iconLose);

			iconLose->runAction(CCSequence::create(//CCDelayTime::create(0.7), 
				CCDelayTime::create(5), 
				CCRemoveSelf::create(), 
				NULL));
        }
        else {
            Number *numMoney0 = new Number(arrMoney[1]);
            numMoney0->setZOrder(10);
            numMoney0->setPositionStart(ccp(10, 120));
            this->addChild(numMoney0);
            
            Number *numMoney1 = new Number(arrMoney[0]);
            numMoney1->setZOrder(10);
            numMoney1->setPositionStart(ccp(10, 312));
            this->addChild(numMoney1);

			if (isSpector) {
				playSound("Win.mp3");
				return;
			}
			playSound("Win.mp3");
			CCSprite *iconWin = CCSprite::create("chess/iconwin.png");
			iconWin->setPosition(ccp(nodeTableChess->getContentSize().width/2, nodeTableChess->getContentSize().height/2));
			iconWin->setZOrder(100);
			nodeTableChess->addChild(iconWin);

			iconWin->runAction(CCSequence::create(//CCDelayTime::create(0.7), 
				CCDelayTime::create(5), 
				CCRemoveSelf::create(), 
				NULL));
        }

		// reason for result
		switch(*wt) {
			case 1:
				// hòa
				break;
			case 0:
				// thắng bình thường
				break;
			case 2:
				// thắng do người kia thoát game
				break;
			case 3:
				// thắng vì 1 người kia hết time
				break;
			case 4:
				// thắng vì người kia xin thua
				break;
			}
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_ERROR_READY_NTF(){
    CCLog("event_EXT_EVENT_ERROR_READY_NTF");
}

void LayerPlayGameChinessChess::event_EXT_EVENT_LIST_USER_UPDATE(){
    boost::shared_ptr<string> listUser = param->GetUtfString("lu");
    
    if (listUser != NULL) {
        CCLog("event_EXT_EVENT_LIST_USER_UPDATE:: listUser=%s", listUser->c_str());
		isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName)->IsSpectator();        

        // thanhhv2|r|30.00|isFirstPlay;thanhhv1|b|32.02|isFirstPlay;
        // Dựa vào ds này xác định xem mình là chủ phòng hay ko
        string ls = listUser->c_str();
        vector<string> arrInfo = split(ls, ';');
		
		countUser = arrInfo.size();
		
		lblNameRed->setString("--");
		lblMoneyRed->setString("--");
		lblWinRateRed->setString("--");
		imagedownloader4Red->setPointerNodeImage(nodeAvatarRed);
		imagedownloader4Red->downLoadImage("");
		lblTimeRed->setString("--");
		lblTotalTimeRed->setString("--");
		//
		lblNameBlack->setString("--");
		lblMoneyBlack->setString("--");
		lblWinRateBlack->setString("--");
		imagedownloader4Black->setPointerNodeImage(nodeAvatarBlack);
		imagedownloader4Black->downLoadImage("");
		lblTimeBlack->setString("--");
		lblTotalTimeBlack->setString("--");
		

		// nếu mình là khách (isSpector=true)
		// Begin
		if (isSpector) {

			btnReMove->setVisible(false);
			btnPeace->setVisible(false);
			btnLose->setVisible(false);
			//lblYouIsGuess->setVisible(true);

			CCLog("Khach!");
			int sizeInfo = arrInfo.size();
			if (sizeInfo < 1) return;

			vector<string> arr = split(arrInfo[0], '|');
			int size = arr.size();
			if(size < 3) return;
			string name = arr.at(0);
			string rateWin = arr.at(2);
			string tile = "Tỉ lệ thắng: " + rateWin + "%";
			if (arr.at(1) == "r") {
				player1 = name;
				lblNameRed->setString(player1.c_str());
				lblWinRateRed->setString(tile.c_str());
				boost::shared_ptr<User> userInfo = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(name);
				boost::shared_ptr<double> amf = userInfo->GetVariable("amf")->GetDoubleValue();
				int money = (int)(*amf);
				// money
				lblMoneyRed->setString(mUtils::convertMoneyEx(money).c_str());
				// avatar
				boost::shared_ptr<string> url = userInfo->GetVariable("aal")->GetStringValue();
				//4 black
				imagedownloader4Red->setPointerNodeImage( nodeAvatarRed );
				imagedownloader4Red->downLoadImage( *url );

				CCLog("name= %s", player1.c_str());
			}
			else {
				player2 = name;
				lblNameBlack->setString(player2.c_str());
				lblWinRateBlack->setString(tile.c_str());
				boost::shared_ptr<User> userInfo = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(name);
				boost::shared_ptr<double> amf = userInfo->GetVariable("amf")->GetDoubleValue();
				int money = (int)(*amf);
				// money
				lblMoneyBlack->setString(mUtils::convertMoneyEx(money).c_str());
				// avatar
				boost::shared_ptr<string> url = userInfo->GetVariable("aal")->GetStringValue();
				//4 black
				imagedownloader4Black->setPointerNodeImage( nodeAvatarBlack );
				imagedownloader4Black->downLoadImage( *url );
			}
		
			if (sizeInfo < 2) {
				/*lblNameRed->setString("--");
				lblMoneyRed->setString("--");
				lblWinRateRed->setString("--");
				imagedownloader4Red->setPointerNodeImage(nodeAvatarRed);
				imagedownloader4Red->downLoadImage("");*/
				return;
			}
			arr = split(arrInfo[1], '|');
			size = arr.size();
			if(size < 3) return;
			name = arr.at(0);
			if (arr.at(1) == "r") player1 = name;
			else player2 = name;
			rateWin = arr.at(2);
			tile = "Tỉ lệ thắng: " + rateWin + "%";
			if (arr.at(1) == "r") {
				player1 = name;
				lblNameRed->setString(player1.c_str());
				lblWinRateRed->setString(tile.c_str());
				boost::shared_ptr<User> userInfo = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(name);
				boost::shared_ptr<double> amf = userInfo->GetVariable("amf")->GetDoubleValue();
				int money = (int)(*amf);
				// money
				lblMoneyRed->setString(mUtils::convertMoneyEx(money).c_str());
				// avatar
				boost::shared_ptr<string> url = userInfo->GetVariable("aal")->GetStringValue();
				//4 black
				imagedownloader4Red->setPointerNodeImage( nodeAvatarRed );
				imagedownloader4Red->downLoadImage( *url );
			}
			else {
				player2 = name;
				lblNameBlack->setString(player2.c_str());
				lblWinRateBlack->setString(tile.c_str());
				boost::shared_ptr<User> userInfo = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(name);
				boost::shared_ptr<double> amf = userInfo->GetVariable("amf")->GetDoubleValue();
				int money = (int)(*amf);
				// money
				lblMoneyBlack->setString(mUtils::convertMoneyEx(money).c_str());
				// avatar
				boost::shared_ptr<string> url = userInfo->GetVariable("aal")->GetStringValue();
				//4 black
				imagedownloader4Black->setPointerNodeImage( nodeAvatarBlack );
				imagedownloader4Black->downLoadImage( *url );
			}
			

			return;
		}
		// End
 
		else {
			btnReady->setEnabled(true);
			btnReady->setVisible(true);

			btnReMove->setVisible(true);
			btnPeace->setVisible(true);
			btnLose->setVisible(true);

			//lblYouIsGuess->setVisible(false);
		}

        int sizeInfo = arrInfo.size();
        for (int i = 0; i < sizeInfo; i++) {
            vector<string> arr = split(arrInfo[i], '|');
            int size = arr.size();
            if(size < 2) return;
            
            if (myName == arr[0]) {
				this->isRedChess = (arr[1] == "r");
                if (i == 0){
                    isMaster = true;
                }
                else {
                    isMaster = false;
                }

				string tile = "Tỉ lệ thắng: " + arr.at(2) + "%";
				lblWinRateBlack->setString(tile.c_str());
            }
        }
        
		string nameEnemy = "";
        if (isMaster) {
            // thong tin đối thủ ở i = 1 (nếu có)
            if (sizeInfo >= 2) {
                vector<string> arr = split(arrInfo[1], '|');
				nameEnemy = arr.at(0);
				string tile = "Tỉ lệ thắng: " + arr.at(2) + "%";
				lblWinRateRed->setString(tile.c_str());
            }
        }
        else {
            vector<string> arr = split(arrInfo[0], '|');
			nameEnemy = arr.at(0);
			string tile = "Tỉ lệ thắng: " + arr.at(2) + "%";
			lblWinRateRed->setString(tile.c_str());
        }
        
        // myself
		// name
        lblNameBlack->setString(myName.c_str());
		boost::shared_ptr<User> userInfo = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName);
		boost::shared_ptr<double> amf = userInfo->GetVariable("amf")->GetDoubleValue();
		int money = (int)(*amf);
		// money
		lblMoneyBlack->setString(mUtils::convertMoneyEx(money).c_str());
		// avatar
		boost::shared_ptr<string> url = userInfo->GetVariable("aal")->GetStringValue();
		//4 black
		imagedownloader4Black->setPointerNodeImage( nodeAvatarBlack );
		imagedownloader4Black->downLoadImage( *url );

		// enemy
		if (nameEnemy.length() < 2){
			lblNameRed->setString("--");
			lblMoneyRed->setString("--");
			lblWinRateRed->setString("--");
			imagedownloader4Red->setPointerNodeImage(nodeAvatarRed);
			imagedownloader4Red->downLoadImage("");
			return;
		}
		lblNameRed->setString(nameEnemy.c_str());
		boost::shared_ptr<User> userInfoEnemy = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(nameEnemy);
		boost::shared_ptr<double> amfEnemy = userInfoEnemy->GetVariable("amf")->GetDoubleValue();
		int moneyEnemy = (int)(*amfEnemy);
		lblMoneyRed->setString(mUtils::convertMoneyEx(moneyEnemy).c_str());
		// avatar
		boost::shared_ptr<string> urlEnemy = userInfoEnemy->GetVariable("aal")->GetStringValue();
		//4 black
		imagedownloader4Red->setPointerNodeImage( nodeAvatarRed );
		imagedownloader4Red->downLoadImage( *urlEnemy );
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_MOVE_NTF(){
    boost::shared_ptr<long> mf = param->GetInt("mf");
    boost::shared_ptr<long> mt = param->GetInt("mt");
    
    if (mf != NULL && mt != NULL) {
        CCLog("event_EXT_EVENT_MOVE_NTF:: moveFrom=%ld, moveTo=%ld", *mf, *mt);
        
        int moveFrom = *mf;
        int moveTo   = *mt;
        
        // nếu mình được đi trước thì phải nhận id ngược (vì các id hiện đang bị ngược so với sv)
        // nếu mình đi sau thì ko cần convert
		bool isPlayer1 = (player1.length() > 0 && player1==nameCurrentTurn);
        if (isRedChess /*|| isPlayer1*/) {
            moveChess(convertID(moveFrom), convertID(moveTo), true);
        }
        else {
            moveChess(moveFrom, moveTo, true);
        }
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_FOR_PEACE_NTF(){
    CCLog("event_EXT_EVENT_FOR_PEACE_NTF");
	LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
	if( !SceneManager::getSingleton().showNotification() ){
		CCLOG("NTF Dialog already open!");
		return;
	}
	layer->setNotificationOptions("Đối phương muốn CẦU HÒA!", 
		"Bạn đồng ý chứ?", true, "Ok", DONG_Y_CHO_HOA, this);
}

void LayerPlayGameChinessChess::event_EXT_EVENT_UNDO_MOVE_REQ() {
	// accept for replay
	// EXT_FIELD_USERID
	// EXT_FIELD_MONEY= "amf"
	CCLog("event_EXT_EVENT_UNDO_MOVE_REQ");
	boost::shared_ptr<long> amf = param->GetInt("amf");
	if (amf==NULL) return;
	int money = *amf;
	CCLog("money=%d", money);

	LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
	if( !SceneManager::getSingleton().showNotification() ){
		return;
	}
	layer->setNotificationOptions("Đối phương muốn XIN ĐI LẠI!", 
		"Bạn đồng ý chứ?", true, "Ok", DONG_Y_CHO_DI_LAI, this);
}
void LayerPlayGameChinessChess::event_EXT_EVENT_UNDO_MOVE_NTF() {
	// move chess for replay
	// EXT_FIELD_LIST_MOVE= "lm"
	//
	//idside,from,to,fromIdChess,toIdChess;... ( từ lần di chuyển gần nhất tới lâu nhất )
	// thanhhv3,67,31,4,0;thanhhv1,2,22,2,7;
	// 
	CCLog("event_EXT_EVENT_UNDO_MOVE_NTF");
	boost::shared_ptr<string> lm = param->GetUtfString("lm");
	if (lm==NULL) return;
	CCLog("lm=%s", lm->c_str());

	// 
	string lmstring = lm->c_str();
	vector<string> arr = split(lmstring, ';');
	if (arr.size() < 2) return;
	for (int i = 0; i < 2; i++)
	{
		vector<string> arrInfo = split(arr.at(i), ',');
		if (arrInfo.size() < 5) return;
		string name = arrInfo.at(0);
		int fromID = atoi(arrInfo.at(1).c_str());
		int toID = atoi(arrInfo.at(2).c_str());
		int IDChessUndo1 = atoi(arrInfo.at(3).c_str());
		int IDChessUndo2 = atoi(arrInfo.at(4).c_str());

		// di chuyển quân
		int moveFrom = toID;
		int moveTo   = fromID;
		if (isRedChess) {
			moveChess(convertID(moveFrom), convertID(moveTo), false);
		}
		else {
			moveChess(moveFrom, moveTo, false);
		}

		// kiểm tra xem IDChessUndo2 có phải 1 quân cờ hay ko, nếu phải thì hiện hình :D
		int chessName = IDChessUndo2;
		int chessSide = -1;
		if (name != myName || (isSpector && name != player2)) {
			chessSide = 1;
		}
		else {
			chessSide = 2;
		}

		isRedChess?(toID=convertID(toID)):toID;
		Chess *chess;
		// tim kiem quan co tuong ung va dat lai vi tri toID
		for (int i = 0; i < arrChess.size(); i++) 
		{
			chess = arrChess.at(i);
			if (chess->getName() == chessName && chess->getSide() == chessSide && !chess->isVisible()) {

				chess->setVisible(true);
				chess->setIDPos(toID);
				chess->setPosition(getPositionFromIndex(toID));
				chess->setClick(false);

				logicChess->setChessIDBySide(IDChessUndo2, chessSide, toID);
				break;
			}
		}

	}

}

void LayerPlayGameChinessChess::event_EXT_EVENT_CHESS_TABLE_NTF() {
	CCLog("event_EXT_EVENT_CHESS_TABLE_NTF");
	CCLog("Player1= %s, Player2= %s", player1.c_str(), player2.c_str());
	boost::shared_ptr<string> tblc = param->GetUtfString("tblc");
	CCLog("||%s||", tblc->c_str());
	// 5_1;3_1;2_1;1_1;6_1;1_1;2_1;3_1;
	string tb = tblc->c_str();
	vector<string> arr = split(tb, ';');
	int i;

	for (i = 0; i < arrChess.size(); i++) {
		arrChess.at(i)->setIDPos(-1);
	}

	vector<string> arr_info;
	int leng;
	int name;
	int side;
	Chess *chess;
	for (i = 0; i < arr.size(); i++) {
		arr_info = split(arr.at(i), '_');
		leng = arr_info.size();
		if (leng < 2) return;
		name = atoi(arr_info.at(0).c_str());
		side = atoi(arr_info.at(1).c_str());
		chess = getChessByName_Side(name, side);
		if (chess!=NULL) {
			chess->setIDPos(i);
		}

		logicChess->setChessIDBySide(name, side, i);
	}

	drawChess();
}

int LayerPlayGameChinessChess::convertID(int id) {
    // xac dinh hang va cot cua id tu duoi len
    int row = id / 9;
    int col = id - row * 9;
    
    int rowC;
    int colC = col;
    
    if (row <= 4) {
        rowC = 5 + (4 - row);
    }
    else {rowC = 4 - (row - 5);}
    
    return (rowC * 9 + colC);
}

void LayerPlayGameChinessChess::moveChess(int fromID, int toID, bool isCheckChieuTuong) {
	bool isPlayer1 = (player1.length() > 0 && nameCurrentTurn==player1);

    if (isRedChess /*|| isPlayer1*/) {
        logicChess->Move(convertID(fromID), convertID(toID));
    }
    else {
        logicChess->Move(fromID, toID);
    }
    vector<int> arrID;
    drawCanMove(arrID);
    
	
    for (int i = 0; i < arrChess.size(); i++) {
        Chess *chess = arrChess.at(i);
        chess->setClick(false);
        
        int id_pos = chess->getIDPos();
        if (id_pos == fromID){
            chess->setIDPos(toID);
            chess->setZOrder(1);
            chess->runAction(CCMoveTo::create(0.25, getPositionFromIndex(toID)));
            chess->setClick(true);

			playSound("ChessMove.mp3");
        }
        else if (id_pos == toID){
            chess->setIDPos(-1);
            chess->setVisible(false);

			playSound("an_bai.mp3");
        }
    }
    
	// thong tin so quan co con lai tren ban cua moi user
	// xe_phao_ma_tuongj_si_tot (vd: 1_0_1_0_0_3)
	int RED = 1;
	int BLACK = 2;
	string listChessRed, listChessBlack;
	if (isRedChess /*|| isPlayer1*/) {
		listChessRed = logicChess->getArrayLostPieces(RED);
		listChessBlack = logicChess->getArrayLostPieces(BLACK);

		if (isCheckChieuTuong)
			if (!logicChess->IsKingSafe(BLACK)) {
				CCActionInterval *blink = CCBlink::create(2, 3);
				chieuTuongRed->runAction(blink);
			}
			if (!logicChess->IsKingSafe(RED)) {
				CCActionInterval *blink = CCBlink::create(2, 3);
				chieuTuongBlack->runAction(blink);
			}
	}
	else {
		listChessRed = logicChess->getArrayLostPieces(BLACK);
		listChessBlack = logicChess->getArrayLostPieces(RED);

		if (isCheckChieuTuong)
			if (!logicChess->IsKingSafe(RED)) {
				CCActionInterval *blink = CCBlink::create(2, 3);
				chieuTuongRed->runAction(blink);
			}
			if (!logicChess->IsKingSafe(BLACK)) {
				CCActionInterval *blink = CCBlink::create(2, 3);
				chieuTuongBlack->runAction(blink);
			}
	}
	vector<string> arrChessRed = split(listChessRed, '_');
	vector<string> arrChessBlack = split(listChessBlack, '_');
	if (arrChessRed.size() < 6 || arrChessBlack.size() < 6) return;
	
	lblXeRed_status->setString(arrChessRed.at(0).c_str());
	lblPhaoRed_status->setString(arrChessRed.at(1).c_str());
	lblMaRed_status->setString(arrChessRed.at(2).c_str());
	lblTotRed_status->setString(arrChessRed.at(5).c_str());
	lblTuongRed_status->setString(arrChessRed.at(3).c_str());
	lblSyRed_status->setString(arrChessBlack.at(4).c_str());
	//
	lblXeBlack_status->setString(arrChessBlack.at(0).c_str());
	lblPhaoBlack_status->setString(arrChessBlack.at(1).c_str());
	lblMaBlack_status->setString(arrChessBlack.at(2).c_str());
	lblTotBlack_status->setString(arrChessBlack.at(5).c_str());
	lblTuongBlack_status->setString(arrChessBlack.at(3).c_str());
	lblSyBlack_status->setString(arrChessBlack.at(4).c_str());
	
}


// hoangdd
void LayerPlayGameChinessChess::loadDefaultImage(CCNode *nodeContainer){
	if (nodeContainer == NULL) {
		return;
	}

	CCSprite* pSprite = CCSprite::createWithSpriteFrameName("assest/icon_default.png");
	//pSprite->setTag(tagIcon);
	pSprite->setAnchorPoint(ccp(0, 0));
	CCSize sizeSprite = pSprite->getContentSize();
	// 75x70
	CCSize sizeExactly = nodeContainer->getContentSize();
	pSprite->cocos2d::CCNode::setScale(sizeExactly.width / sizeSprite.width, sizeExactly.height / sizeSprite.height);

	nodeContainer->removeAllChildrenWithCleanup(true);
	nodeContainer->addChild(pSprite);
}

void LayerPlayGameChinessChess::downLoadImage(string url, string fileName){
	if( url.compare("")==0 ){
		
		// load default icon
		string where = "black";
		vector<string> arr = split(fileName, '_');
		if (arr.size() > 0) where = arr.at(0);
		arr.clear();
		if (where == "black") loadDefaultImage(nodeAvatarBlack);
		else loadDefaultImage(nodeAvatarRed);
		
		return;
	}
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, httpresponse_selector(LayerPlayGameChinessChess::onImageDownLoaded));
	request->setTag(fileName.c_str());
	CCHttpClient::getInstance()->send(request);
	request->release();
}

void LayerPlayGameChinessChess::setAvatarByPath(CCNode *nodeContainer, string path) {
	CCSprite *img = CCSprite::create(path.c_str());
	setAvatarBySprite(nodeContainer, img);
}

void LayerPlayGameChinessChess::setAvatarBySprite(CCNode *nodeContainer, CCSprite* img) {
	CCSize sizeOfContainer = nodeContainer->getContentSize();
	img->setAnchorPoint(CCPointZero);
	img->setScaleX(sizeOfContainer.width/img->getContentSize().width);
	img->setScaleY(sizeOfContainer.height/img->getContentSize().height);

	nodeContainer->removeAllChildrenWithCleanup(true);
	nodeContainer->addChild(img);
}

void LayerPlayGameChinessChess::onImageDownLoaded(CCHttpClient* pSender, CCHttpResponse* pResponse){
	CCHttpResponse* response = pResponse;

	if (!response)
	{
		CCLog("No Response");
		//loadDefaultImage();
		return ;
	}
	int statusCode = response->getResponseCode();

	char statusString[64] = {};
	CCLog("HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLog("response code: %d", statusCode);

	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer: %s", response->getErrorBuffer());
		//loadDefaultImage();
		return;
	}
	std::vector<char>*buffer = response->getResponseData();


	CCImage * img=new CCImage();
	img->initWithImageData(&(buffer->front()), buffer->size());

	// Save image file to device.
	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	writablePath.append(response->getHttpRequest()->getTag());
	// add this line
	img->saveToFile(writablePath.c_str());

	// xác định nơi đặt avatar (black or red)
	string where = "black";
	string iconname = response->getHttpRequest()->getTag();
	vector<string> arr = split(iconname, '_');
	if (arr.size() > 0) where = arr.at(0);
	arr.clear();
	CCNode *nodeContainer;
	if (where == "black") nodeContainer = nodeAvatarBlack;
	else nodeContainer = nodeAvatarRed;

	setAvatarByPath(nodeContainer, writablePath.c_str());
}

void LayerPlayGameChinessChess::menuSittingDownCallback(CCObject *pSender) {
	CCLog(":)");
}

