//
//  LayerBuyAvatar.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/6/14.
//
//

#include "LayerBuyAvatar.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerBuyAvatar::LayerBuyAvatar()
{
    nodeListAvatar = NULL;
    //
	currChoice = -1;
    GameServer::getSingleton().addListeners(this);
}

LayerBuyAvatar::~LayerBuyAvatar()
{
	for( int i = 0; i<m_lstAvatarsImg.size(); i++ ){
		if( m_lstAvatarsImg.at(i)!=NULL )
			CC_SAFE_DELETE( m_lstAvatarsImg.at(i) );
	}
	//
    GameServer::getSingleton().removeListeners(this);
    //
    CC_SAFE_RELEASE(nodeListAvatar);
}

void LayerBuyAvatar::loadAllMyDatas(){
    tblAvatar->reloadData();
    //Send request
   boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
   //
   boost::shared_ptr<ISFSObject> params (new SFSObject());
   params->PutUtfString("aI", myself->Name());
   params->PutInt("startR", 0);
   params->PutInt("endR", 100);
   boost::shared_ptr<IRequest> request (new ExtensionRequest("aGLA", params)); //
   GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerBuyAvatar::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnBuy", LayerBuyAvatar::onButtonBuy);
    return NULL;
}

void LayerBuyAvatar::onButtonBuy(CCObject* pSender)
{
    CCLOG("onButtonBuy");
	//aBA: Buy Avatar
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutInt("aId", 1);
	boost::shared_ptr<IRequest> request (new ExtensionRequest("aBA", params)); //
	GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBMemberVariableAssigner interface
bool LayerBuyAvatar::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeListAvatar", CCNode*, nodeListAvatar);
    return true;
}

void LayerBuyAvatar::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	m_lstAvatars.clear();
    //Init for table
    tblAvatar = CCTableView::create(this, nodeListAvatar->getContentSize());
    tblAvatar->setDirection(kCCScrollViewDirectionHorizontal);
    tblAvatar->setAnchorPoint(ccp(0, 0));
    tblAvatar->setPosition(ccp(0, 0));
    tblAvatar->setDelegate(this);
    tblAvatar->setVerticalFillOrder(kCCTableViewFillTopDown);
    
    nodeListAvatar->addChild(tblAvatar);
    return;
}

// hàm khi click vào 1 hành của table view
void LayerBuyAvatar::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
//    CCLOG("Roomid: %d",cell->getObjectID());
	if( currChoice != cell->getObjectID() ){
		currChoice = cell->getObjectID();
		CCSprite* c = (CCSprite*)cell->getChildByTag( tag_Choice );
		if( c ){
			c->initWithSpriteFrameName(true?"assest/ratio_active.png":"assest/ratio_disable.png");
		}
		//Uncheck other cell
		for( int i = 0; i<7; i++ ){
			CCTableViewCell* cc = (CCTableViewCell*)table->cellAtIndex(i);
			if( cc==NULL )
				continue;
			CCSprite* c = (CCSprite*)cc->getChildByTag( tag_Choice );
			if( c ){
				c->initWithSpriteFrameName(currChoice==i?"assest/ratio_active.png":"assest/ratio_disable.png");
			}
		}
	}
}

// Hàm set giá trị width height cho 1 cell table view
CCSize LayerBuyAvatar::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    return CCSizeMake(120, 140);
}

// Hàm này tạo 1 tableview Row để add vào table view
CCTableViewCell* LayerBuyAvatar::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
		cell->setObjectID( idx );
        cell->autorelease();
        //Chon
        CCSprite* ready = CCSprite::createWithSpriteFrameName("assest/ratio_disable.png");
        ready->setPosition(ccp(15, 119));
        ready->setAnchorPoint(ccp(0, 0));
		ready->setTag(tag_Choice);
        cell->addChild(ready);
        //lable chon
        CCLabelTTF *labelChon = CCLabelTTF::create("Chọn", "Helvetica", 14);
        labelChon->setPosition(ccp(40, 119));
        labelChon->setAnchorPoint(ccp(0, 0));
        cell->addChild(labelChon);
        //avatar
		CCNode* nodeAvatar = CCNode::create();
		nodeAvatar->setTag( tag_NodeAvatar );
		nodeAvatar->setPosition(ccp(0, 18));
		nodeAvatar->setAnchorPoint(ccp(0, 0));
		nodeAvatar->setContentSize(ccp(93, 93));
		cell->addChild(nodeAvatar);
		//load avatar
		m_lstImageDownloaders.at(idx)->setPointerNodeImage( nodeAvatar );
		m_lstImageDownloaders.at(idx)->downLoadImage(m_lstAvatars.at(idx).url);
        //Coin
        CCLabelTTF *coin = CCLabelTTF::create( CCString::createWithFormat("%d Chips", m_lstAvatars.at(idx).money)->getCString() , "Helvetica", 14);
        coin->setPosition(ccp(95/2, 0));
        coin->setAnchorPoint(ccp(0.5, 0));
		coin->setTag(tag_Money);
        cell->addChild(coin);
    }
    else
	{
		cell->setObjectID( idx );
        CCNode* nodeAvatar = cell->getChildByTag( tag_NodeAvatar );
		if( nodeAvatar ){
			m_lstImageDownloaders.at(idx)->setPointerNodeImage( nodeAvatar );
			m_lstImageDownloaders.at(idx)->downLoadImage(m_lstAvatars.at(idx).url);
		}
		CCLabelTTF* coin = (CCLabelTTF*)cell->getChildByTag( tag_Money );
		if( coin ){
			coin->setString( CCString::createWithFormat("%d Chips", m_lstAvatars.at(idx).money)->getCString() );
		}

		CCSprite* c = (CCSprite*)cell->getChildByTag( tag_Choice );
		if( c ){
			c->initWithSpriteFrameName(currChoice==idx?"assest/ratio_active.png":"assest/ratio_disable.png");
		}
    }
    return cell;
}

// Hàm gán giá trị số hàng của table view
unsigned int LayerBuyAvatar::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return m_lstAvatars.size();
}

void LayerBuyAvatar::OnExtensionResponse(unsigned long long ptrContext,boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));



	CCLOG("LayerBuyAvatar::OnExtensionResponse() - cmd=%s", cmd->c_str());

    if(strcmp("aGLA", cmd->c_str())==0){
		CCLOG("aGLR=%s", param->GetUtfString("aGLR")->c_str());
//        //Insert datas to textfield
		vector<string> lstAvatars = mUtils::splitString( *param->GetUtfString("aGLR"), '|' );
		//SAFE RELEASE
		m_lstAvatars.clear();
		for( int i = 0; i<m_lstAvatarsImg.size(); i++ ){
			if( m_lstAvatarsImg.at(i)!=NULL )
				CC_SAFE_DELETE(m_lstAvatarsImg.at(i));
		}
		//
		for( int i = 0; i<lstAvatars.size(); i++ ){
			vector<string> infos = mUtils::splitString( lstAvatars.at(i), ',' );
			//1,http: //bestteam.publicvm.com/avatars_sell/1.png,/var/www/html/avatars_sell/1.png,1.png,100,1,2014-07-13 00:00:00.0
			if( infos.size()<7 )
				continue;
			AvatarInfo info;
			info.id = atoi( infos.at(0).c_str() );
			info.url = infos.at(1);
			info.filename = infos.at(2);
			info.filepath = infos.at(3);
			info.money = atoi( infos.at(4).c_str() );
			info.status = atoi( infos.at(5).c_str() );
			info.timeCreate = infos.at(6);
			m_lstAvatars.push_back( info );
			//
			ImageDownloader* imagedownloader = new ImageDownloader();
			m_lstImageDownloaders.push_back( imagedownloader );
		}
		tblAvatar->reloadData();
	}else if(strcmp("aBA", cmd->c_str())==0){
		
	}
}