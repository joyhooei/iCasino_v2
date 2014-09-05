#include "LayerChanToast.h"
#include "mUtils.h"
#include "AllData.h"

int LayerChanToast::count = 0;
CCArray LayerChanToast::arrObject = NULL;
string LayerChanToast::curentString = "";

LayerChanToast::~LayerChanToast()
{
	Queue->removeAllObjects();
	Queue->release();
}

LayerChanToast::LayerChanToast(string message){
	vector<string> lstRegex;
	for( int i = 1; i <= 16; i++ ){
		lstRegex.push_back( CCString::createWithFormat("(%d)", i)->getCString() );
	}

	this->setAnchorPoint(ccp(0, 0));
	// text
	cocos2d::ui::RichText* label = cocos2d::ui::RichText::create();
	label->setAnchorPoint(ccp(0, 0));
	label->setPosition(ccp(0, HEIGHT_DESIGN / 3.5));

	vector<string> lstContents = mUtils::splitStringByListRegex(message, lstRegex);
	int wLabel = 0, hLabel = 0;
	for( int i = 0; i < lstContents.size(); i++ ){
		bool check = false;
		int j = 0;
		for( j = 0; j < lstRegex.size(); j++ )
			if( lstRegex.at(j) == lstContents.at(i) ){
				check = true;
				break;
			}
			if( check ){
				CCArmature *armature = CCArmature::create(CCString::createWithFormat("onion%d", 1)->getCString());
				armature->getAnimation()->playByIndex(j);
				cocos2d::ui::RichElementCustomNode* recustom = cocos2d::ui::RichElementCustomNode::create(1, ccWHITE, 255, armature);
				label->pushBackElement(recustom);
				wLabel += 50;
				hLabel = 55;
			}else{
				CCLabelTTF *l = CCLabelTTF::create(lstContents.at(i).c_str(), "Arial", 16);
				l->setColor(ccc3(204, 16, 85));
				cocos2d::ui::RichElementText* re1 = cocos2d::ui::RichElementText::create(1, ccWHITE, 255, lstContents.at(i).c_str(), "Arial", 16);
				label->pushBackElement(re1);
				wLabel += l->getContentSize().width;
				hLabel = hLabel > 50 ? 55 : l->getContentSize().height;
			}
	}
	this->addChild(label, 1, 0);

	CCSize sizeDesign = CCSize(169, 30);
	CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("chats/framechat_a.png");
	CCScale9Sprite *blocks = CCScale9Sprite::create();
	blocks ->updateWithBatchNode(batchNode , CCRect(0, 0, sizeDesign.width, sizeDesign.height), false, CCRect(10, 10, sizeDesign.width - 20, sizeDesign.height - 20));

	CCSize size = CCSizeMake(wLabel + 10, hLabel + 5);
	blocks ->setContentSize(size);
	blocks->setAnchorPoint(ccp(0.5, 0.5));
	blocks->setPosition(ccp(label->getPositionX() + wLabel / 2, label->getPositionY() + hLabel / 2));

	blocks->setColor(ccc3(84, 81, 69));
	blocks->setOpacity(200);
	this->setPosition(ccp((WIDTH_DESIGN - size.width) / 2, 100));
	// add
	this->addChild(blocks);
}

void LayerChanToast::dissmiss(CCObject *sender){
	LayerChanToast *pToast = (LayerChanToast*)sender;
	int index = pToast->getTag();
	arrObject.removeObjectAtIndex(index);
	pToast->removeFromParentAndCleanup(true);

	for (int i = 0; i < arrObject.count(); i++)
	{
		LayerChanToast* toast = (LayerChanToast*)arrObject.objectAtIndex(i);
		toast->setPositionY(HEIGHT_DESIGN / 3.5 - 26 * i);
		toast->setTag(i);
	}
	if (count == 0)
	{
		curentString = "";
	}
	count--;
	CCLog("count = %d",count);
}

void LayerChanToast::showMessage(CCNode *target){
	this->setPositionY(HEIGHT_DESIGN / 3.5 - 20 * count);
	count ++;
	target->addChild(this);

}

void LayerChanToast::showToast(CCNode *target, string message, float duration){
	if (strcmp(curentString.c_str(), message.c_str()) == 0 || count == 4)
	{
		return;
	}
	curentString = message;
	LayerChanToast *myToast = new LayerChanToast(message);
	myToast->setPositionY(HEIGHT_DESIGN / 3.5 - 26 * count);
	target->addChild(myToast);
	CCFadeOut *faceout = CCFadeOut::create(3);
	CCDelayTime *delay = CCDelayTime::create(3);
	CCCallFunc *callfun = CCCallFuncO::create(target, callfuncO_selector(LayerChanToast::dissmiss),myToast);
	myToast->runAction(CCSequence::create(delay, faceout, callfun, NULL));
	arrObject.addObject(myToast);
	myToast->setTag(count);

	count++;
	CCLOG("CCArray count: %d", arrObject.count());
}

void LayerChanToast::resetStaticVariables(){
	curentString = "";
	count = 0;
	arrObject.removeAllObjects();
}