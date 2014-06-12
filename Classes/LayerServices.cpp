//
//  LayerServices.cpp
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#include "LayerServices.h"
#include "LayerMain.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerServices::LayerServices()
{
}

LayerServices::~LayerServices()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerServices::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
 //   CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnGame", LayerServices::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnShop", LayerServices::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnRank", LayerServices::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnGuide", LayerServices::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChat", LayerServices::onButtonClick);
    return NULL;
}

void LayerServices::onButtonClick(CCObject* pSender)
{
    CCMenuItem* mnu = (CCMenuItem*)pSender;
    int tag = mnu->getTag();
    CCLOG("onButtonClick tag: %d", tag);
    //
    switch (tag) {
        case tag_Games:
            LayerMain::getSingleton().gotoChooseGame();
            break;
        case tag_Chat:
            LayerMain::getSingleton().gotoChat();
            break;
        case tag_Shop:
            LayerMain::getSingleton().gotoShop();
            break;
        case tag_Guide:
            LayerMain::getSingleton().gotoGuide();
            break;
        case tag_Rank:
            LayerMain::getSingleton().gotoRank();
            break;
    }
}

// CCBMemberVariableAssigner interface
bool LayerServices::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    return true;
}

void LayerServices::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    return;
}