//
//  TableViewCustomLoader.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_TableViewCustomLoader_h
#define demo_TableViewCustomLoader_h

class TableViewCustomLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TableViewCustomLoader, loader);
protected:
    virtual CCTableView * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCTableView *pRet = new CCTableView();
        pRet->initWithViewSize(CCSizeZero, NULL);
        pRet->autorelease();
        return pRet;
    }
};


#endif
