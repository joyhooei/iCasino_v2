//
//  _Background_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/16/14.
//
//

#include "_Background_inGame_.h"
#include "AllData.h"

bool BackgroundInGame::init() {
    if (!UILayer::init()) return false;
    
    this->setAnchorPoint(ccp(0, 0));
    
    ImageView *bg = ImageView::create();
    bg->loadTexture("table.png");
    
    bg->setAnchorPoint(ccp(0, 0));
    
    this->addWidget(bg);
    
    return true;
}