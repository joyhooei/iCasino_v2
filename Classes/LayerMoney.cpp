//
//  LayerMoney.cpp
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#include "LayerMoney.h"

#include "LayerChargeMoney.h"
#include "LayerLichSuGiaoDich.h"
#include "LayerTransferMoney.h"
#include "LayerCurrencyExchange.h"
#include "LayerBorrowMoney.h"
#include "mUtils.h"

#include "SceneManager.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerMoney::LayerMoney()
{
    currTag = tag_ChargeDisable;

    lblChargeDisable= NULL;
    lblHistoryDisable= NULL;
    lblTransferDisable= NULL;
    lblLoanDisable= NULL;
    lblExchangeDisable= NULL;
    
    lblChargeEnable= NULL;
    lblHistoryEnable= NULL;
    lblTransferEnable= NULL;
    lblLoanEnable= NULL;
    lblExchangeEnable= NULL;
    
    btnCharge_enable= NULL;
    btnHistory_enable= NULL;
    btnTransfer_enable= NULL;
    btnLoan_enable= NULL;
    btnExchange_enable= NULL;
    
    btnCharge_disable= NULL;
    btnHistory_disable= NULL;
    btnTransfer_disable= NULL;
    btnLoan_disable= NULL;
    btnExchange_disable= NULL;
    
    nodeChild = NULL;
    currNodeView = NULL;

}

LayerMoney::~LayerMoney()
{
	currNodeView->removeFromParentAndCleanup(true);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerMoney::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
   // CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCharge_disable", LayerMoney::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnHistory_disable", LayerMoney::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnTransfer_disable", LayerMoney::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnLoan_disable", LayerMoney::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnExchange_disable", LayerMoney::onButtonClick);
    return NULL;
}

void LayerMoney::disableTabs(tag_SpriteClick newTag){
    lblChargeEnable->setVisible( newTag == tag_ChargeEnable );
    btnCharge_enable->setVisible( newTag == tag_ChargeEnable );
    lblChargeDisable->setVisible( newTag != tag_ChargeEnable );
    btnCharge_disable->setVisible( newTag != tag_ChargeEnable );
    
    lblHistoryEnable->setVisible( newTag == tag_HistoryEnable );
    btnHistory_enable->setVisible( newTag == tag_HistoryEnable );
    lblHistoryDisable->setVisible( newTag != tag_HistoryEnable );
    btnHistory_disable->setVisible( newTag != tag_HistoryEnable );
    
    lblTransferEnable->setVisible( newTag == tag_TransferEnable );
    btnTransfer_enable->setVisible( newTag == tag_TransferEnable );
    lblTransferDisable->setVisible( newTag != tag_TransferEnable );
    btnTransfer_disable->setVisible( newTag != tag_TransferEnable );
    
    lblLoanEnable->setVisible( newTag == tag_LoanEnable );
    btnLoan_enable->setVisible( newTag == tag_LoanEnable );
    lblLoanDisable->setVisible( newTag != tag_LoanEnable );
    btnLoan_disable->setVisible( newTag != tag_LoanEnable );
    
    lblExchangeEnable->setVisible( newTag == tag_ExchangeEnable );
    btnExchange_enable->setVisible( newTag == tag_ExchangeEnable );
    lblExchangeDisable->setVisible( newTag != tag_ExchangeEnable );
    btnExchange_disable->setVisible( newTag != tag_ExchangeEnable );
}

void LayerMoney::onButtonClick(CCObject* pSender)
{
    CCMenuItem* mnu = (CCMenuItem*)pSender;
    int tag = mnu->getTag();
    if( currTag == tag )
        return;
    //
    switch (tag) {
        case tag_ChargeDisable:
            currTag = tag_ChargeEnable;
            gotoChargeMoney();
            break;
        case tag_HistoryDisable:
            currTag = tag_HistoryEnable;
            gotoHistory();
            break;
        case tag_TransferDisable:
            currTag = tag_TransferEnable;
            gotoTransfer();
            break;
        case tag_LoanDisable:
            currTag = tag_LoanEnable;
            gotoBorrow();
            break;
        case tag_ExchangeDisable:
            currTag = tag_ExchangeEnable;
            gotoExchange();
            break;
    }
    disableTabs(currTag);
    CCLOG("onButtonClick with tag: %d", tag);}

// CCBMemberVariableAssigner interface
bool LayerMoney::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblChargeDisable", CCLabelTTF *, lblChargeDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblHistoryDisable", CCLabelTTF *, lblHistoryDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTransferDisable", CCLabelTTF *, lblTransferDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblLoanDisable", CCLabelTTF *, lblLoanDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblExchangeDisable", CCLabelTTF *, lblExchangeDisable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblChargeEnable", CCLabelTTF *, lblChargeEnable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblHistoryEnable", CCLabelTTF *, lblHistoryEnable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTransferEnable", CCLabelTTF *, lblTransferEnable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblLoanEnable", CCLabelTTF *, lblLoanEnable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblExchangeEnable", CCLabelTTF *, lblExchangeEnable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnCharge_disable", CCMenuItem *, btnCharge_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnHistory_disable", CCMenuItem *, btnHistory_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnTransfer_disable", CCMenuItem *, btnTransfer_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnLoan_disable", CCMenuItem *, btnLoan_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnExchange_disable", CCMenuItem *, btnExchange_disable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnCharge_enable", CCMenuItem *, btnCharge_enable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnHistory_enable", CCMenuItem *, btnHistory_enable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnTransfer_enable", CCMenuItem *, btnTransfer_enable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnLoan_enable", CCMenuItem *, btnLoan_enable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnExchange_enable", CCMenuItem *, btnExchange_enable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeChild", CCNode *, nodeChild);
    
    return true;
}

void LayerMoney::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    gotoChargeMoney();
    return;
}

void LayerMoney::gotoChargeMoney(){
	removeOldView();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerChargeMoney* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerChargeMoney *)ccbReader->readNodeGraphFromFile( "LayerChargeMoney.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
}
void LayerMoney::gotoHistory(){
	removeOldView();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerLichSuGiaoDich* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerLichSuGiaoDich *)ccbReader->readNodeGraphFromFile( "LayerLichSuGiaoDich.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    mLayer->loadAllDatas();
    currNodeView = mLayer;
}
void LayerMoney::gotoTransfer(){
	removeOldView();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerTransferMoney* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerTransferMoney *)ccbReader->readNodeGraphFromFile( "LayerTransferMoney.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
}
void LayerMoney::gotoBorrow(){
	removeOldView();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerBorrowMoney* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerBorrowMoney *)ccbReader->readNodeGraphFromFile( "LayerBorrowMoney.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    mLayer->loadAllMyDatas();
    currNodeView = mLayer;
}
void LayerMoney::gotoExchange(){
	removeOldView();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerCurrencyExchange* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerCurrencyExchange *)ccbReader->readNodeGraphFromFile( "LayerCurrencyExchange.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    mLayer->loadAllMyDatas();
    currNodeView = mLayer;
}
void LayerMoney::removeOldView(){
    if( currNodeView==NULL )
        return;
//    nodeChild->removeChild(currNodeView);
    currNodeView->removeFromParentAndCleanup(true);
//    CC_SAFE_RELEASE(currNodeView);
    //    try{
    //        currNodeView->release()();
    //    }catch(...){
    //
    //    }
    currNodeView = NULL;
}