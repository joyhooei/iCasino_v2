//
//  LayerLoading.cpp
//  TestCpp
//
//  Created by leafsoar on 7/29/13.
//
//

#include "LayerLoading.h"

LayerLoading::LayerLoading():
m__pMenu(NULL)
	, m_contentPadding(0)
	, m_contentPaddingTop(0)
	, m_callbackListener(NULL)
	, m_callback(NULL)
	, m__sfBackGround(NULL)
	, m__s9BackGround(NULL)
	, m__ltContentText(NULL)
	, m__ltTitle(NULL)
{

}

LayerLoading::~LayerLoading(){
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
	CCLog("~LayerLoading");
}

bool LayerLoading::init(){
	bool bRef = false;
	do{
		CC_BREAK_IF(!CCLayer::init());

		setTouchEnabled(true);

		bRef = true;
	}while(0);
	return bRef;
}

void LayerLoading::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerLoading::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	return true;
}

/*
LayerLoading* LayerLoading::create(const char *backgroundImage){
	LayerLoading* ml = LayerLoading::create();
	return ml;
}*/

void LayerLoading::setTitle(const char *title, int fontsize){
	CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "", fontsize);
	setLabelTitle(ltfTitle);
}

void LayerLoading::setContentText(const char *text, int fontsize, int padding, int paddingTop){
	CCLabelTTF* ltf = CCLabelTTF::create(text, "", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void LayerLoading::setCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncN callfun){
	m_callbackListener = target;
	m_callback = callfun;    
}


bool LayerLoading::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);

	CCMenuItemImage* menuImage = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(LayerLoading::buttonCallback));
	menuImage->setTag(tag);
	menuImage->setPosition(pCenter);

	CCSize imenu = menuImage->getContentSize();
	CCLabelTTF* ttf = CCLabelTTF::create(title, "", 20);
	ttf->setColor(ccc3(0, 0, 0));
	ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
	menuImage->addChild(ttf);

	getMenuButton()->addChild(menuImage);
	return true;
}

void LayerLoading::buttonCallback(cocos2d::CCObject *pSender){
	CCNode* node = dynamic_cast<CCNode*>(pSender);
	if (m_callback && m_callbackListener){
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParentAndCleanup(true);
}

void LayerLoading::onEnter(){
	CCLayer::onEnter();
	CCSize sizeScreen = CCDirector::sharedDirector()->getWinSize();
	this->setPosition(ccp(-sizeScreen.width/2, -sizeScreen.height/2));

	CCAction* LayerLoading = CCSequence::create(CCScaleTo::create(0.0, 0.0),
		CCScaleTo::create(0.06, 1.05),
		CCScaleTo::create(0.08, 0.95),
		CCScaleTo::create(0.08, 1.0), NULL);
	this->runAction(LayerLoading);

	CCLayerColor *backgroundColor = CCLayerColor::create();
	backgroundColor->setAnchorPoint(ccp(0.5, 0.5));
	backgroundColor->setPosition(ccp(0, 0));
	backgroundColor->initWithColor(ccc4(0, 0, 0, 100));
	this->addChild(backgroundColor);

	CCSprite *card = CCSprite::create("card_back.png");
	card->setAnchorPoint(ccp(0.5, 0.5));
	card->setPosition(ccp(sizeScreen.width/2, sizeScreen.height/2));
	//this->addChild(card);

	// add Loading
	CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("loading.plist");

	CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::create("loading.png");
	this->addChild(spritesheet);

	CCArray *loadingFrames = new CCArray;
	for (int i = 1; i <= 7; i++)
	{
		CCString *fileName = CCString::createWithFormat("loading%d.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName->getCString());
		loadingFrames->addObject(frame);
	}

	CCAnimation *runAnim = CCAnimation::createWithSpriteFrames(loadingFrames, 0.1);
	CCSprite *loading = CCSprite::createWithSpriteFrameName("loading1.png");

	CCSize sizeWin = CCDirector::sharedDirector()->getWinSize();
	loading->setPosition(ccp(sizeWin.width/2, sizeWin.height/2));

	CCAction *action = CCRepeatForever::create(CCAnimate::create(runAnim));
	loading->runAction(action);

	spritesheet->addChild(loading);
}

void LayerLoading::onExit(){
	CCLog("popup on exit.");
	CCLayer::onExit();
}