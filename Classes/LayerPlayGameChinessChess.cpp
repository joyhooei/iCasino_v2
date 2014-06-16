//
//  LayerPlayGameChinessChess.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/4/14.
//
//

#include "LayerPlayGameChinessChess.h"
#include "SceneManager.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"
#include "Requests/LeaveRoomRequest.h"
#include "_Number_.h"

using namespace cocos2d;
//using namespace CocosDenshion;

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
    
    return -1;
}
string LayerPlayGameChinessChess::convertResponseToString(int inInt) {
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
    
    return "";
}

LayerPlayGameChinessChess::LayerPlayGameChinessChess()
{
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
    GameServer::getSingleton().addListeners(this);
    
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
    
    this->schedule(schedule_selector(LayerPlayGameChinessChess::updateTimer), 1);
}

void LayerPlayGameChinessChess::updateTimer(float dt) {
    if (isStartedGame && nameCurrentTurn.length() > 0) {
        if (nameCurrentTurn == myName) {
            timeRestBlack--;
            lblTotalTimeBlack->setString(convertTimer(timeRestBlack).c_str());
        }
        else {
            timeRestRed--;
            lblTotalTimeRed->setString(convertTimer(timeRestRed).c_str());
        }
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
	if (this->nameCurrentTurn != myName) return; 

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
    Chess *xe_red_1 = new Chess(kXeDo, 0);
    Chess *ma_red_1 = new Chess(kMaDo, 1);
    Chess *tuongj_red_1 = new Chess(kTuongjDo, 2);
    Chess *si_red_1 = new Chess(kSiDo, 3);
    Chess *tuong_red = new Chess(kTuongDo, 4);
    Chess *si_red_2 = new Chess(kSiDo, 5);
    Chess *tuongj_red_2 = new Chess(kTuongjDo, 6);
    Chess *ma_red_2 = new Chess(kMaDo, 7);
    Chess *xe_red_2 = new Chess(kXeDo, 8);
    Chess *phao_red_1 = new Chess(kPhaoDo, 19);
    Chess *phao_red_2 = new Chess(kPhaoDo, 25);
    Chess *tot_red_1 = new Chess(kTotDo, 27);
    Chess *tot_red_2 = new Chess(kTotDo, 29);
    Chess *tot_red_3 = new Chess(kTotDo, 31);
    Chess *tot_red_4 = new Chess(kTotDo, 33);
    Chess *tot_red_5 = new Chess(kTotDo, 35);
    //
    
    Chess *xe_blue_1 = new Chess(kXeXanh, 81);
    Chess *ma_blue_1 = new Chess(kMaXanh, 82);
    Chess *tuongj_blue_1 = new Chess(kTuongjXanh, 83);
    Chess *si_blue_1 = new Chess(kSiXanh, 84);
    Chess *tuong_blue = new Chess(kTuongXanh, 85);
    Chess *si_blue_2 = new Chess(kSiXanh, 86);
    Chess *tuongj_blue_2 = new Chess(kTuongjXanh, 87);
    Chess *ma_blue_2 = new Chess(kMaXanh, 88);
    Chess *xe_blue_2 = new Chess(kXeXanh, 89);
    Chess *phao_blue_1 = new Chess(kPhaoXanh, 64);
    Chess *phao_blue_2 = new Chess(kPhaoXanh, 70);
    Chess *tot_blue_1 = new Chess(kTotXanh, 54);
    Chess *tot_blue_2 = new Chess(kTotXanh, 56);
    Chess *tot_blue_3 = new Chess(kTotXanh, 58);
    Chess *tot_blue_4 = new Chess(kTotXanh, 60);
    Chess *tot_blue_5 = new Chess(kTotXanh, 62);
    
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

void LayerPlayGameChinessChess::drawCanMove(vector<int> arrPos) {
    for (int i = 0; i < 90; i++) {
        setPointVisiable(i, false);
    }
    
    for (int i = 0; i < arrPos.size(); i++) {
        int pos = arrPos.at(i);
        if (pos >= 0 && pos < 90) setPointVisiable(pos, true);
    }
}

LayerPlayGameChinessChess::~LayerPlayGameChinessChess()
{
    GameServer::getSingleton().removeListeners(this);
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

void LayerPlayGameChinessChess::loadAllDatas(){
}

void LayerPlayGameChinessChess::onButtonBack(CCObject* pSender){
    // leave room
    boost::shared_ptr<IRequest> request (new LeaveRoomRequest());
    GameServer::getSingleton().getSmartFox()->Send(request);
    
    
    GameServer::getSingleton().removeListeners(this);
    this->removeAllChildrenWithCleanup(true);
//    this->removeFromParentAndCleanup(true);
//    CC_SAFE_RELEASE(this);
    
    SceneManager::getSingleton().gotoMain();
    
    //Test thu get position
//    CCPoint a = getPositionFromIndex(89);
//    CCLOG("x:%lf, y:%lf", a.x, a.y);
//    
//    for (int i = 0; i < 90; i++) {
////        CCSprite *tag1 = CCSprite::create("tag_phom_1.png");
////        tag1->setPosition(getPositionFromIndex(i));
////
////        nodeTableChess->addChild(tag1, 1000);
//        setPointVisiable(i, true);
//    }
}
void LayerPlayGameChinessChess::onButtonSetting(CCObject* pSender){
    
}
void LayerPlayGameChinessChess::onButtonMoney(CCObject* pSender){
    
}
void LayerPlayGameChinessChess::onButtonChat(CCObject* pSender){
    
}
void LayerPlayGameChinessChess::onButtonLose(CCObject* pSender){
    boost::shared_ptr<ISFSObject> parameter (new SFSObject());
    boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_IM_LOSE), parameter, lastRoom));
    GameServer::getSingleton().getSmartFox()->Send(request);
}
void LayerPlayGameChinessChess::onButtonPeace(CCObject* pSender){
    boost::shared_ptr<ISFSObject> parameter (new SFSObject());
    boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_FOR_PEACE), parameter, lastRoom));
    GameServer::getSingleton().getSmartFox()->Send(request);
}
void LayerPlayGameChinessChess::onButtonRemove(CCObject* pSender){
    
}
void LayerPlayGameChinessChess::onButtonReady(CCObject* pSender){
    CCLog("clicked ready");
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
    return true;
}

void LayerPlayGameChinessChess::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    logicChess = new ChessLogic();
    logicChess->loadNewGame();
    
    this->setTouchEnabled(true);
    
    createChess();
    

	CCSize sizeTable = nodeTableChess->getContentSize();
    tag2 = CCSprite::create("tag_phom_1.png");
    //nodeTableChess->addChild(tag2);
    chieuTuongRed = CCSprite::create("chess/attack1.png");
	chieuTuongRed->setPosition(ccp(sizeTable.width / 2, sizeTable.height / 2 - 100));
	chieuTuongRed->setVisible(false);
	chieuTuongBlack = CCSprite::create("chess/attack2.png");
	chieuTuongBlack->setPosition(ccp(sizeTable.width / 2, sizeTable.height / 2 + 100));
	chieuTuongBlack->setVisible(false);
	nodeTableChess->addChild(chieuTuongRed, 100);
	nodeTableChess->addChild(chieuTuongBlack, 100);

    // Khoi tao cac doi tuong o day
    myName = SceneManager::getSingleton().getMyName();
    indexCurrent = -1;
    indexTarget = -1;
    
    isStartedGame = false;
  
    //
    lblNameRed->setString("--");
    lblMoneyRed->setString("--");
    lblWinRateRed->setString("--");
    lblTimeRed->setString("--");
    lblTotalTimeRed->setString("--");
    lblXeRed_status->setString("--");
    lblPhaoRed_status->setString("--");
    lblMaRed_status->setString("--");
    lblTotRed_status->setString("--");
    lblTuongRed_status->setString("--");
    lblSyRed_status->setString("--");
    //
    lblNameBlack->setString("--");
    lblMoneyBlack->setString("--");
    lblWinRateBlack->setString("--");
    lblTimeBlack->setString("--");
    lblTotalTimeBlack->setString("--");
    lblXeBlack_status->setString("--");
    lblPhaoBlack_status->setString("--");
    lblMaBlack_status->setString("--");
    lblTotBlack_status->setString("--");
    lblTuongBlack_status->setString("--");
    lblSyBlack_status->setString("--");

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
    
    return;
}

void LayerPlayGameChinessChess::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	int    money = (int) (*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	string name = boost::to_string(*ptrNotifiedUser->Name());

	CCLOG("Update User Variables");
	CCLOG("name=%s, money=%d", name.c_str(), money);

	mUtils mu;
	if (name==myName) {
		lblMoneyBlack->setString(mu.convertMoneyEx(money).c_str());
	}
	else lblMoneyRed->setString(mu.convertMoneyEx(money).c_str());
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
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_START(){
    CCLog("event_EXT_EVENT_START:: start game!");
    
    isStartedGame = true;
    nameCurrentTurn = "";
    timeRestBlack = 900;
    timeRestRed   = 900;
    
    btnReady->setEnabled(false);
    btnReady->setVisible(false);
    btnUnReady->setEnabled(false);
    btnUnReady->setVisible(false);
    
    readyRed->setVisible(false);
    readyBlack->setVisible(false);

	//lblNameRed->setString("--");
	//lblMoneyRed->setString("--");
	//lblWinRateRed->setString("--");
	//lblTimeRed->setString("--");
	//lblTotalTimeRed->setString("--");
	lblXeRed_status->setString("--");
	lblPhaoRed_status->setString("--");
	lblMaRed_status->setString("--");
	lblTotRed_status->setString("--");
	lblTuongRed_status->setString("--");
	lblSyRed_status->setString("--");
	//
	//lblNameBlack->setString("--");
	//lblMoneyBlack->setString("--");
	//lblWinRateBlack->setString("--");
	//lblTimeBlack->setString("--");
	//lblTotalTimeBlack->setString("--");
	lblXeBlack_status->setString("--");
	lblPhaoBlack_status->setString("--");
	lblMaBlack_status->setString("--");
	lblTotBlack_status->setString("--");
	lblTuongBlack_status->setString("--");
	lblSyBlack_status->setString("--");
    
    refreshChess();
}

void LayerPlayGameChinessChess::event_EXT_EVENT_NEXT_TURN(){
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    boost::shared_ptr<string> list_time = param->GetUtfString("crt");
    
    if (name != NULL && list_time != NULL) {
        CCLog("event_EXT_EVENT_NEXT_TURN:: name=%s, list_time=%s", name->c_str(), list_time->c_str());
        
		// nếu là ban đầu thì kiểm tra xem người đi đầu là mình hay đối thủ
		if (nameCurrentTurn.length() == 0)
		{
			isIamTheFirst = (myName == name->c_str());
			if (isIamTheFirst)
			{
				CCLog("Minh di dau");
			}
			else {
				CCLog("Minh di sau");
			}
		}
		

        nameCurrentTurn = name->c_str();
        
        if (nameCurrentTurn == myName){
            box_time_focus_black->setVisible(true);
            box_time_focus_red->setVisible(false);
        }
        else {
            box_time_focus_red->setVisible(true);
            box_time_focus_black->setVisible(false);
        }
        
        // ptich chuoi thanhhv|900;thanhhv2|900;
        string lsTime =  list_time->c_str();
        vector<string> arrLsTime = split(lsTime, ';');
        
        // Player 1
        vector<string> arrInfo_1 = split(arrLsTime[0], '|');
        string name =arrInfo_1[0];
        string money = arrInfo_1[1];
        if (name == myName) {
            timeRestBlack = atoi(money.c_str());
        } else timeRestRed = atoi(money.c_str());
        
        // Player 2
        vector<string> arrInfo_2 = split(arrLsTime[1], '|');
        name =arrInfo_2[0];
        money = arrInfo_2[1];
        if (name == myName) {
            timeRestBlack = atoi(money.c_str());
        } else timeRestRed = atoi(money.c_str());
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_END(){
    CCLog("event_EXT_EVENT_END:: end game!");
    
    logicChess->loadNewGame();
    nameCurrentTurn = "";
	isIamTheFirst  = false;
	isStartedGame = false;
    
    btnReady->setEnabled(true);
    btnReady->setVisible(true);
    
    // reset
    indexCurrent = -1;
    indexTarget  = -1;
}

void LayerPlayGameChinessChess::event_EXT_EVENT_READY_NTF(){
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    
    if (name != NULL ) {
        CCLog("event_EXT_EVENT_READY_NTF:: name=%s", name->c_str());
        
        if (name->c_str() == myName) readyBlack->setVisible(true);
        else readyRed->setVisible(true);
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_GAME_RESULT(){
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    boost::shared_ptr<string> result = param->GetUtfString("rg");
    
    if (name != NULL && result != NULL) {
        //name=thanhhv2, result=-0|0
        CCLog("event_EXT_EVENT_GAME_RESULT:: name=%s, result=%s", name->c_str(), result->c_str());
        
        string lsmoney = result->c_str();
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
        
        // thanhhv2|r;thanhhv1|b;
        // Dựa vào ds này xác định xem mình là chủ phòng hay ko
        string ls = listUser->c_str();
        vector<string> arrInfo = split(ls, ';');
        
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
            }
            
        }
        
        if (isMaster) {
            // thong tin đối thủ ở i = 1 (nếu có)
            if (sizeInfo >= 2) {
                vector<string> arr = split(arrInfo[1], '|');
                lblNameRed->setString(arr[0].c_str());
            }
        }
        else {
            vector<string> arr = split(arrInfo[0], '|');
            lblNameRed->setString(arr[0].c_str());
        }
        
        // name của mình luôn đặt ở dưới, của đối thủ đặt ở trên
        lblNameBlack->setString(myName.c_str());
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
        // nếu mình đi sau thì ko cần convert gì
        if (isRedChess) {
            moveChess(convertID(moveFrom), convertID(moveTo));
        }
        else {
            moveChess(moveFrom, moveTo);
        }
    }
}

void LayerPlayGameChinessChess::event_EXT_EVENT_FOR_PEACE_NTF(){
    CCLog("event_EXT_EVENT_FOR_PEACE_NTF");
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

void LayerPlayGameChinessChess::moveChess(int fromID, int toID) {
    CCLog("action moveChess fromID=%d, toID=%d", fromID, toID);
    if (isRedChess) {
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
            chess->runAction(CCMoveTo::create(0.5, getPositionFromIndex(toID)));
            chess->setClick(true);
        }
        else if (id_pos == toID){
            chess->setIDPos(-1);
            chess->setVisible(false);
        }
    }
    
	// thong tin so quan co con lai tren ban cua moi user
	// xe_phao_ma_tuongj_si_tot (vd: 1_0_1_0_0_3)
	int RED = 1;
	int BLACK = 2;
	string listChessRed, listChessBlack;
	if (isRedChess) {
		listChessRed = logicChess->getArrayLostPieces(RED);
		listChessBlack = logicChess->getArrayLostPieces(BLACK);

		if (!logicChess->IsKingSafe(BLACK)) {
			CCLog("ben kia dang chieu tuong");
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

		if (!logicChess->IsKingSafe(RED)) {
			CCLog("Minh la quan den: ben kia dang chieu tuong");
			CCActionInterval *blink = CCBlink::create(2, 3);
			chieuTuongRed->runAction(blink);
		}
		if (!logicChess->IsKingSafe(BLACK)) {
			CCLog("Minh la quan den: Dang chieu tuong ben kia");
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


