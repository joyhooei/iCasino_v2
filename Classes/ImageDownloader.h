//
//  ImageDownloader.h
//  iCasino_v2
//
//  Created by HoangDD on 7/10/14.
//
//

#ifndef __iCasino_v2__ImageDownloader__
#define __iCasino_v2__ImageDownloader__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;
/*
 *Lớp này có tác dụng download 1 image from http url về máy, và hiển thị lên 1 CCNode
 */

class ImageDownloader : public CCObject{
private:
	CCNode* _nodeImagePointer;
public:
	ImageDownloader();
	void setPointerNodeImage(CCNode* pImg);
	void downLoadImage(string url, string fileNameEx="");
	void onImageDownLoaded(CCHttpClient* pSender, CCHttpResponse* pResponse);
	void loadDefaultImage();
};

#endif /* defined(__iCasino_v2__ImageDownloader__) */
