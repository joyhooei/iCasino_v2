//
//  TextFieldCustomLoader.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_TextFieldCustomLoader_h
#define demo_TextFieldCustomLoader_h

class TextFieldCustomLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TextFieldCustomLoader, loader);
protected:
    virtual CCEditBox * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        //Get child
        CCEditBox *pRet = CCEditBox::create(CCSizeMake(306, 50), CCScale9Sprite::create("input.png"));
        return pRet;
    }
};

#endif
