//
//  LayerChooseGame.cpp
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#include "LayerChooseGame.h"
#include "LayerMain.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "platform/android/jni/Android.h"
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "IOS.h"
#endif
LayerChooseGame::LayerChooseGame()
{
}

LayerChooseGame::~LayerChooseGame()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerChooseGame::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
   // CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnBaCayChuong", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnBaCayThuong", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnPhom", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnXito", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnTLMB", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnTLMN", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnLieng", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCoTuong", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnTomCuaCa", LayerChooseGame::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChan", LayerChooseGame::onButtonClick);

    return NULL;
}

void LayerChooseGame::onButtonClick(CCObject* pSender)
{
    CCMenuItem* mnu = (CCMenuItem*)pSender;
    int tag = mnu->getTag();
    CCLOG("tag: %d", tag);
    //Do anything
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    turnOffAd();
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    IOS::turnOffAD();
#endif
    LayerMain::getSingleton().gotoChonBanChoi(tag);
}

// CCBMemberVariableAssigner interface
bool LayerChooseGame::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    return true;
}

void LayerChooseGame::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    return;
}