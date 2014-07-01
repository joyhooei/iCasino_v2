#include "LayerChatWindow.h"
#include "SceneManager.h"
#include "mUtils.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

CCScene* LayerChatWindow::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LayerChatWindow *layer = LayerChatWindow::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LayerChatWindow::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	//return true;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	_count = 100;
	UILayer* ul = UILayer::create();
	ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("LayerChatWindow_1.ExportJson"));
	this->addChild(ul);
	ul->setTouchPriority(-128);
	this->setTouchEnabled(true);

	//Get all chat button
	for( int i = 1; i <= 8; i++ ){
		UIButton* btnChat = dynamic_cast<UIButton*>(ul->getWidgetByName( CCString::createWithFormat("btnChat%d", i)->getCString() ));
		btnChat->addTouchEventListener(this,(SEL_TouchEvent)&LayerChatWindow::onButtonChats);
	}
	UIButton* btnClose = dynamic_cast<UIButton*>(ul->getWidgetByName("btnClose"));
	btnClose->addTouchEventListener(this,(SEL_TouchEvent)&LayerChatWindow::onButtonClose);
	//
	UIButton* btnSend = dynamic_cast<UIButton*>(ul->getWidgetByName("btnSend"));
	btnSend->addTouchEventListener(this,(SEL_TouchEvent)&LayerChatWindow::onButtonSend);

	txtChat = dynamic_cast<UITextField*>(ul->getWidgetByName("txtChat"));
	txtChat->setText("");
	txtChat->setPlaceHolder("Noi dung");
	txtChat->addEventListenerTextField(this, textfieldeventselector(LayerChatWindow::textFieldEvent));

	UIPanel* pEmo = dynamic_cast<UIPanel*>(ul->getWidgetByName("pEmo"));
	UIImageView* pImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_25_0"));
	//Add all emo to this
	int i = 1;
// 	CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(CCString::createWithFormat("onion%d.ExportJson", 1)->getCString());
// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(CCString::createWithFormat("onion%d.ExportJson", 1)->getCString());
	int row=-1, col = 1;
	int widthOfPage = 580;
	int numOfCols = 9;
	int space = 10;
	int widthOfImage = 50;
	int startPosX = widthOfPage/2 - (widthOfImage+space)*numOfCols/2;
	int startPosY = space;
	CCLOG("numOfCols = %d", numOfCols);
	for( int i = 1; i<=16; i++ ){
		CCArmature *armature = CCArmature::create(CCString::createWithFormat("onion%d", 1)->getCString());
		armature->getAnimation()->playByIndex(i-1);
		RichElementCustomNode* recustom = RichElementCustomNode::create(1, ccWHITE, 255, armature);
		RichText* _richText = RichText::create();

		_richText->setContentSize( armature->getContentSize() );
		_richText->pushBackElement(recustom);
		if( col> numOfCols ){
			row++;
			col = 1;
		}
		_richText->setAnchorPoint(ccp(0, 1));
		_richText->setPosition(ccp( startPosX + 60*(col-1)
			, -1*row*50 - startPosY - (row+1)*space ));
		_richText->addTouchEventListener(this,(SEL_TouchEvent)&LayerChatWindow::OnEmoClick);

		UIButton* b = UIButton::create();
		b->setPosition(ccp( startPosX + 60*(col-1)
			, -1*row*50 - startPosY - (row+1)*space ));
		b->setAnchorPoint(ccp(0, 1));
		b->setContentSize( armature->getContentSize() );
		b->addTouchEventListener(this,(SEL_TouchEvent)&LayerChatWindow::OnEmoClick);
		b->loadTextures("emo_blank.png", "", "");
		b->setTag(i);

		pImg->addChild( _richText );
		pImg->addChild( b );
		CCLOG("button w: %lf h: %lf", b->getContentSize().width, b->getContentSize().height);
		col++;
	}
	return true;
}

void LayerChatWindow::onButtonClose( CCObject* pSender, TouchEventType type )
{
	if(type == TOUCH_EVENT_ENDED){
// 		if (m_callback && m_callbackListener)
// 		{
// 			(m_callback->*m_callbackListener)(this, "");
// 		}
		SceneManager::getSingleton().hideLayerChatWindow();
		txtChat->setText("");
		txtChat->setDetachWithIME(false);
	}
}

void LayerChatWindow::onButtonSend( CCObject* pSender, TouchEventType type )
{
	if(type == TOUCH_EVENT_ENDED){
		if (m_callback && m_callbackListener)
		{
			(m_callback->*m_callbackListener)(this, (void*)txtChat->getStringValue());
		}
		SceneManager::getSingleton().hideLayerChatWindow();
		txtChat->setText("");
		txtChat->setDetachWithIME(false);
	}
}

void LayerChatWindow::onButtonChats( CCObject* pSender, TouchEventType type )
{
	UIButton* btnChat = dynamic_cast<UIButton*>(pSender);
	if(type == TOUCH_EVENT_ENDED){
		CCLog("onButtonChats %s", btnChat->getTitleText());
		txtChat->setText( btnChat->getTitleText() );
	}
}


void LayerChatWindow::registerWithTouchDispatcher( void )
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerChatWindow::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerChatWindow::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerChatWindow::onExit()
{
	CCLayer::onExit();
}

void LayerChatWindow::OnEmoClick( CCObject* pSender, TouchEventType type )
{
	UIButton* btn = dynamic_cast<UIButton*>(pSender);
	if( type == TOUCH_EVENT_ENDED ){
		CCLOG("OnEmoClick button tag: %d", btn->getTag());
		txtChat->setText( CCString::createWithFormat("%s(%d)", txtChat->getStringValue(), btn->getTag())->getCString() );
	}
}

void LayerChatWindow::setCallbackFunc( CCObject* target, SEL_CallFuncND callfun )
{
	m_callback = target;
	m_callbackListener = callfun;
}

LayerChatWindow::~LayerChatWindow()
{
	CCLOG("~LayerChatWindow()");
}

void LayerChatWindow::textFieldEvent( CCObject *pSender, TextFiledEventType type )
{
	switch (type)
	{
	case TEXTFIELD_EVENT_ATTACH_WITH_IME:
		{
			CCLOG("TEXTFIELD_EVENT_ATTACH_WITH_IME");
		}
		break;

	case TEXTFIELD_EVENT_DETACH_WITH_IME:
		{
			CCLOG("TEXTFIELD_EVENT_DETACH_WITH_IME");
		}
		break;

	case TEXTFIELD_EVENT_INSERT_TEXT:
		CCLOG("TEXTFIELD_EVENT_INSERT_TEXT");
		break;
	case TEXTFIELD_EVENT_DELETE_BACKWARD:
		CCLOG("TEXTFIELD_EVENT_DELETE_BACKWARD");
		break;
	default:
		break;
	}
}
