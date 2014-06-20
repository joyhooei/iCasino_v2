#include "TomCuaCa.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CCScene* TomCuaCa::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TomCuaCa *layer = TomCuaCa::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TomCuaCa::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	UILayer* ul = UILayer::create();
	ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("TomCuaCa/TomCuaCa_1_1.json"));
	this->addChild(ul);
	UIScrollView* scroll1 = dynamic_cast<UIScrollView*>(ul->getWidgetByName("scrollView_kq1"));
	scroll1->scrollToPercentVertical(_kqNai,10,true);
		
	UIScrollView* scroll2 = dynamic_cast<UIScrollView*>(ul->getWidgetByName("scrollView_kq2"));
	scroll2->scrollToPercentVertical(_kqCua,15,true);

	UIScrollView* scroll3 = dynamic_cast<UIScrollView*>(ul->getWidgetByName("scrollView_kq3"));
	scroll3->scrollToPercentVertical(_kqCa,18,true);
    
	UIButton* btnThoat = dynamic_cast<UIButton*>(ul->getWidgetByName("button_back"));
	btnThoat->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::click);
    return true;
}


void TomCuaCa::click(CCObject* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	CCLog("OUt");

}
