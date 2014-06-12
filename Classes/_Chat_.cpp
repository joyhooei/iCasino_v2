//
//  _Chat_.cpp
//  testcpp2605
//
//  Created by Thanhhv on 5/27/14.
//
//

#include "_Chat_.h"

enum{
    kTagLabel,
    kOrderLabel
};

Chat::Chat(string pMes, int posUser) {
    this->mes = pMes;
    this->posUser = posUser;
    init();
}

bool Chat::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    this->setAnchorPoint(ccp(0, 0));
    //
    
    formatMes();
    
    // text
    CCLabelTTF *label = CCLabelTTF::create(this->mes.c_str(), "Arial", 16);
    label->setAnchorPoint(ccp(0, 0));
    label->setPosition(ccp(0, 6));
    
    
    // background_a
    CCSize sizeDesign = CCSize(169, 30);
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("chats/framechat_a.png");
    CCScale9Sprite *blocks = CCScale9Sprite::create();
    blocks ->updateWithBatchNode(batchNode , CCRect(0, 0, sizeDesign.width, sizeDesign.height), false, CCRect(10, 10, sizeDesign.width - 20, sizeDesign.height - 20));
    
    CCSize size = CCSizeMake(label->getContentSize().width + 10, label->getContentSize().height + 5);
    blocks ->setContentSize(size);
//    blocks ->setAnchorPoint(label->getAnchorPoint());
//    blocks ->setPosition(label->getPosition());
    blocks->setAnchorPoint(ccp(0.5, 0.5));
    blocks->setPosition(ccp(label->getPositionX() + label->getContentSize().width / 2, label->getPositionY() + label->getContentSize().height / 2));
    
    // background_b
    CCSprite *bgB = CCSprite::create("chats/framechat_b.png");
    bgB->setAnchorPoint(label->getAnchorPoint());
    bgB->setPositionY(0);
    
    switch (this->posUser) {
        case kUserMe: case kUserTop: case kUserBot: // me, bottom, top
            bgB->setPositionX(size.width / 2 - 7);
            CCLog("Center");
            break;
        case kUserLeft: // left
            bgB->setPositionX(size.width / 4);
            CCLog("Left");
            break;
        case kUserRight:
            bgB->setPositionX(size.width / 4 * 3 - 10);
            CCLog("Right");
            break;
            
        default:
            // this is Toast
            bgB->setVisible(false);
            blocks->setColor(ccc3(84, 81, 69));
            blocks->setOpacity(200);
            
            this->setPosition(ccp((WIDTH_DESIGN - size.width) / 2, 100));
            
            CCLog("NO DIRECTION");
            break;
    }
    
    // add
    this->addChild(blocks);
    this->addChild(label, kOrderLabel, kTagLabel);
    this->addChild(bgB);
    
    this->sizeThis = size;
    
    this->runAction(CCSequence::create(CCDelayTime::create(3),
                                       CCCallFunc::create(this, callfunc_selector(Chat::releaseSafe)),
                                       NULL));
    
    return true;
}

void Chat::setStatusByServer(bool isServer) {
    CCLabelTTF *label = (CCLabelTTF*) this->getChildByTag(kTagLabel);
    
    if (label == NULL)
        return;
    
    if (isServer) {
        label->setColor(ccWHITE);
    }
    else {
        label->setColor(ccWHITE);
    }
}


CCSize Chat::getSize() {
    return this->sizeThis;
}

void Chat::formatMes() {
    int MAX_LENGTH_LINE = 20;
    int length = this->mes.length();
    
    int row = length / MAX_LENGTH_LINE;
    
    if (row > 1) {
        string newMes = "";
        int startSub, endSub;
        
        for (int i = 0; i <= row; i++) {
            startSub = i * MAX_LENGTH_LINE;
            endSub = (i+1) * MAX_LENGTH_LINE;
            
            if (endSub > length) {
                endSub = length;
            }
            
            newMes += " " + this->mes.substr(startSub, endSub - startSub) + " ";
            if (i < row) newMes += "\n";
        }
        
        this->mes = newMes;
    } else {
        this->mes = "  " + this->mes + "  ";
        //this->mes += "\n";
    }
    
}

void Chat::releaseSafe() {
    this->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE(this);
}
