//
//  CustomTableViewCell.h
//  AppDemo
//
//  Created by DauA on 5/5/14.
//
//

#ifndef __AppDemo__CustomTableViewCell__
#define __AppDemo__CustomTableViewCell__

#include "cocos-ext.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
using namespace std;

class CustomTableViewCell : public cocos2d::extension::CCTableViewCell{
private:
    long roomID;
	string sValue;
	enum{
		tag_NodeColor = 11212
	};
	CCSize m_currSize;
	bool isSelected;
public:
	CustomTableViewCell(CCSize s);
    virtual void draw();
    void setRoomId(long idx);
    long getRoomId();

	void setStringObject(string val);
	string getStringObject();

	void setSelectedState(bool isSelected);
	bool getSelectedState();
};

#endif /* defined(__AppDemo__CustomTableViewCell__) */
