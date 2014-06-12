//
//  LayerPlayGame.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/14/14.
//
//

#include "LayerPlayGame.h"
#include "SceneManager.h"

LayerPlayGame::LayerPlayGame() {
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(-WIDTH_DESIGN / 2, -HEIGHT_DESIGN / 2));
    this->setTouchEnabled(true);
    
    // Title
    titleGame = CCLabelTTF::create("Layer Game", "Arial", 30);
    titleGame->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2));
    this->addChild(titleGame);
    
    // Button control
    Button *button = Button::create();
    button->setTitleColor(ccWHITE);
    button->setTitleText("Back");
    button->setTitleFontSize(30);
    button->loadTextures("ready.png", "ready_selected.png", "");
    button->addTouchEventListener(this, toucheventselector(LayerPlayGame::onTouchButton));
    button->setPosition(ccp(WIDTH_DESIGN / 2, 170));
    button->setTouchEnabled(true);
    
    
    UILayer *layerWidget = UILayer::create();
    layerWidget->setAnchorPoint(ccp(0, 0));
    layerWidget->setPosition(ccp(0, 0));
    layerWidget->addWidget(button);
    
    this->addChild(layerWidget);
}

LayerPlayGame::~LayerPlayGame() {
    
}

void LayerPlayGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
    CCLog("Touched layer gaming");
}

void LayerPlayGame::onTouchButton(CCObject *pSender, TouchEventType pEventType) {
    SceneManager::getSingleton().gotoMain();
}