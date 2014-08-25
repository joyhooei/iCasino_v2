//
//  LayerGameChan_KetQua.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerGameChan_KetQua_h
#define demo_LayerGameChan_KetQua_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;
class LayerGameChan_KetQua : public CCLayer
{
private:
	UILayer *resuiltKQ;
	UIImageView *img;
	UIButton *btnClose;
public:
	LayerGameChan_KetQua();
	virtual ~LayerGameChan_KetQua();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(LayerGameChan_KetQua);
	string identifyCuoc_sac(string _cuoc);
	string identifyCuoc_Ga(string _cuoc);

	string getNamePlayer(string uid);

	vector<string> splitString(string &S,const char &str);
	string getCuoc(string cuoc, bool type);

	void displayResuilt(string resuilt);

	void btnClose_LayerResuilt(CCObject *sender, TouchEventType type);
};

#endif