//
//  _Chat_.cpp
//  testcpp2605
//
//  Created by Thanhhv on 5/27/14.
//
//

#include "_Chat_.h"
#include "mUtils.h"
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
	vector<string> lstRegex;
	for( int i = 1; i<=16; i++ ){
		lstRegex.push_back( CCString::createWithFormat("(%d)", i)->getCString() );
	}
    
    this->setAnchorPoint(ccp(0, 0));
    formatMes();
    
	// text
	cocos2d::ui::RichText* label = cocos2d::ui::RichText::create();
    label->setAnchorPoint(ccp(0, 0));
    label->setPosition(ccp(0, 6));
	vector<string> lstContents = mUtils::splitStringByListRegex(this->mes.c_str(), lstRegex);
	int wLabel = 0, hLabel = 0;
	for( int i=0; i<lstContents.size(); i++ ){
		bool check = false;
		int j=0;
		for( j=0; j<lstRegex.size(); j++ )
			if( lstRegex.at(j) == lstContents.at(i) ){
				check = true;
				break;
			}
			if( check ){
				CCArmature *armature = CCArmature::create(CCString::createWithFormat("onion%d", 1)->getCString());
				armature->getAnimation()->playByIndex(j);
				cocos2d::ui::RichElementCustomNode* recustom = cocos2d::ui::RichElementCustomNode::create(1, ccWHITE, 255, armature);
				label->pushBackElement(recustom);
				wLabel+=50;
				hLabel = 55;
			}else{
				CCLabelTTF *l = CCLabelTTF::create(lstContents.at(i).c_str(), "Arial", 16);
				l->setColor(ccc3(204, 16, 85));
				cocos2d::ui::RichElementText* re1 = cocos2d::ui::RichElementText::create(1, ccWHITE, 255, lstContents.at(i).c_str(), "Arial", 16);
				label->pushBackElement(re1);
				wLabel+=l->getContentSize().width;
				//CCLOG("labelw: %lf, rte: %lf", l->getContentSize().width, 1);
				hLabel = hLabel>50?55:l->getContentSize().height;
			}
	}
	this->addChild(label, kOrderLabel, kTagLabel);
//     CCLabelTTF *label = CCLabelTTF::create(this->mes.c_str(), "Arial", 16);
//     label->setAnchorPoint(ccp(0, 0));
//     label->setPosition(ccp(0, 6));
    
    
    // background_a
    CCSize sizeDesign = CCSize(169, 30);
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("chats/framechat_a.png");
    CCScale9Sprite *blocks = CCScale9Sprite::create();
    blocks ->updateWithBatchNode(batchNode , CCRect(0, 0, sizeDesign.width, sizeDesign.height), false, CCRect(10, 10, sizeDesign.width - 20, sizeDesign.height - 20));
    
    CCSize size = CCSizeMake(wLabel + 10, hLabel + 5);
    blocks ->setContentSize(size);
    blocks->setAnchorPoint(ccp(0.5, 0.5));
    blocks->setPosition(ccp(label->getPositionX() + wLabel / 2, label->getPositionY() + hLabel / 2));
    
    // background_b
    CCSprite *bgB = CCSprite::create("chats/framechat_b.png");
    bgB->setAnchorPoint(label->getAnchorPoint());
    bgB->setPositionY(0);
    
    switch (this->posUser) {
        case kUserMe: case kUserTop: case kUserBot: // me, bottom, top
            bgB->setPositionX(size.width / 2 - 7);
            break;
        case kUserLeft: // left
            bgB->setPositionX(size.width / 4);
            break;
        case kUserRight:
            bgB->setPositionX(size.width / 4 * 3 - 10);
            break;
            
        default:
            // this is Toast
            bgB->setVisible(false);
            blocks->setColor(ccc3(84, 81, 69));
            blocks->setOpacity(200);
            this->setPosition(ccp((WIDTH_DESIGN - size.width) / 2, 100));
            break;
    }
    
    // add
    this->addChild(blocks);
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
    
//     if (isServer) {
//         label->setColor(ccWHITE);
//     }
//     else {
//         label->setColor(ccWHITE);
//     }
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
    }
    
}

void Chat::releaseSafe() {
    this->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE(this);
}
