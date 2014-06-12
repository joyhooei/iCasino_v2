//
//  _Chat_inGame_.cpp
//  iCasinov2
//
//  Created by Thanhhv on 5/27/14.
//
//

#include "_Chat_inGame_.h"

bool LayerChatInGame::init() {
    if (!CCLayer::init()) return false;
    
    this->setAnchorPoint(ccp(0, 0));
    
    return true;
}

void LayerChatInGame::showChatByPos(int pos, string mes) {
    Chat *newMes = new Chat(mes, pos);
    newMes->setStatusByServer(false);
    
    CCPoint point;
    
    switch (pos) {
        case kUserLeft:
            point.setPoint(10, 175 + 137);
            break;
            
        case kUserRight:
            point.setPoint(WIDTH_DESIGN - newMes->getSize().width - 10, 175 + 137);
            break;
            
        case kUserTop:
            point.setPoint((WIDTH_DESIGN - newMes->getSize().width) / 2, 343);
            break;
            
        case kUserBot: case kUserMe:
            point.setPoint((WIDTH_DESIGN - newMes->getSize().width) / 2, 70);
            break;
        
        default:
            point.setPoint((WIDTH_DESIGN - newMes->getSize().width) / 2, (HEIGHT_DESIGN - newMes->getSize().height) / 2);
            newMes->setStatusByServer(true);
            break;
    }
    
    newMes->setPosition(point);
    this->addChild(newMes);
}