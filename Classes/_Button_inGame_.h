//
//  _Button_inGame_.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/15/14.
//
//  Create buttons: Back, Seting, Chat, Coin in a Game
//  This is a CCLayer:
// anchorPoint = 0, 0
// position = 0, 0
//

#ifndef __iCasino_v2___Button_inGame___
#define __iCasino_v2___Button_inGame___

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::ui;

class LayerButtonInGame : public UILayer
{
public:
	virtual bool init();
	CREATE_FUNC(LayerButtonInGame);

	Button* createButtonWith_Style_Position(int style, CCPoint pPoint);

	void addWidgetEx(Button* node);

	// add event listener
	void eventTouchBtnBack(CCObject *pObject, TouchEventType pType);
	void eventTouchBtnSetting(CCObject *pObject, TouchEventType pType);
	void eventTouchBtnChat(CCObject *pObject, TouchEventType pType);
	void eventTouchBtnCoin(CCObject *pObject, TouchEventType pType);

};

#endif /* defined(__iCasino_v2___Button_inGame___) */
