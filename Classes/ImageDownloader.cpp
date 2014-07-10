//
//  ImageDownloader.cpp
//  iCasino_v2
//
//  Created by HoangDD on 7/10/14.
//
//

#include "ImageDownloader.h"
#include "mUtils.h"
#include <fstream>

void ImageDownloader::loadDefaultImage(){
	CCSprite* pSprite = CCSprite::createWithSpriteFrameName("assest/icon_default.png");
	pSprite->setAnchorPoint(ccp(0, 0));
	pSprite->cocos2d::CCNode::setScale(_nodeImagePointer->getContentSize().width/pSprite->getContentSize().width, _nodeImagePointer->getContentSize().height/pSprite->getContentSize().height);
	//Call callback
	_nodeImagePointer->removeAllChildrenWithCleanup(true);
	//
	_nodeImagePointer->addChild(pSprite);
}

void ImageDownloader::downLoadImage(string url, string fileNameEx){
	if( _nodeImagePointer==NULL )
		return;
	//Get File name
	string fileName = fileNameEx;
	if( fileNameEx=="" ){
		fileName = mUtils::getFileName(url);
	}
	//Kiem tra 
	if( url.compare("")==0 || fileName=="" ){
		loadDefaultImage();
		return;
	}
	//
	//Check filename existed ?
	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	writablePath.append( fileName );
	ifstream f(writablePath.c_str());
	if(f){
		//existed
		CCSprite* pSprite = NULL;
		try{
			pSprite = CCSprite::create(writablePath.c_str());
		}catch(...){
			//Do nothing
			pSprite = NULL;
		}
		if( pSprite!=NULL ){
			//Nếu load ảnh có sẵn thành công
			pSprite->setAnchorPoint(ccp(0, 0));
			pSprite->cocos2d::CCNode::setScale(_nodeImagePointer->getContentSize().width/pSprite->getContentSize().width
				, _nodeImagePointer->getContentSize().height/pSprite->getContentSize().height);
			//Call callback
			_nodeImagePointer->removeAllChildrenWithCleanup(true);
			//
			_nodeImagePointer->addChild(pSprite);
			return;
		}
	}
	//
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, httpresponse_selector(ImageDownloader::onImageDownLoaded));
	request->setTag(fileName.c_str());
	CCHttpClient::getInstance()->send(request);
	request->release();
}

void ImageDownloader::onImageDownLoaded(CCHttpClient* pSender, CCHttpResponse* pResponse){
	CCHttpResponse* response = pResponse;

	if (!response)
	{
		CCLog("No Response");
		loadDefaultImage();
		return ;
	}
	int statusCode = response->getResponseCode();

	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLog("response code: %d", statusCode);

	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer: %s", response->getErrorBuffer());
		loadDefaultImage();
		return;
	}
	std::vector<char>*buffer = response->getResponseData();

	CCImage * img=new CCImage();
	img->initWithImageData(&(buffer->front()), buffer->size());

	// Save image file to device.
	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	writablePath.append(response->getHttpRequest()->getTag());
	// add this line
	img->saveToFile(writablePath.c_str());

	//Now create Sprite from downloaded image
	CCSprite* pSprite = CCSprite::create(writablePath.c_str());
	pSprite->setAnchorPoint(ccp(0, 0));
	pSprite->cocos2d::CCNode::setScale(_nodeImagePointer->getContentSize().width/pSprite->getContentSize().width
		, _nodeImagePointer->getContentSize().height/pSprite->getContentSize().height);
	//Call callback
	_nodeImagePointer->removeAllChildrenWithCleanup(true);
	//
	_nodeImagePointer->addChild(pSprite);
}

void ImageDownloader::setPointerNodeImage( CCNode* pImg )
{
	_nodeImagePointer = pImg;
}

ImageDownloader::ImageDownloader()
{
	_nodeImagePointer = NULL;
}
