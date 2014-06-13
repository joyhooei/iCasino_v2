//
//  TextFieldCustomPopupLoader.h
//  iCasinov2
//
//  Created by AlexDao on 6/6/14.
//
//

#ifndef iCasinov2_TextFieldCustomPopupLoader_h
#define iCasinov2_TextFieldCustomPopupLoader_h

class TextFieldCustomPopUpLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TextFieldCustomPopUpLoader, loader);
protected:
    virtual CCEditBox * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        //Get child
		CCEditBox *pRet = CCEditBox::create(CCSizeMake(280, 48), CCScale9Sprite::create("input.png"));
		pRet->setInputMode(kEditBoxInputModeAny);
        return pRet;
    }
};

#endif
