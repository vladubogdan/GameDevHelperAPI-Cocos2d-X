//
//  Sprites_LoadSpriteFromPNGTest.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __SpriteHelper2_TestCases__Sprites_LoadSpriteFromPNGTest__
#define __SpriteHelper2_TestCases__Sprites_LoadSpriteFromPNGTest__


#include "cocos2d.h"

class Sprites_LoadSpritesFromPNGTest : public cocos2d::CCLayerColor
{
public:
	Sprites_LoadSpritesFromPNGTest();
	~Sprites_LoadSpritesFromPNGTest();
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool,
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Sprites_LoadSpritesFromPNGTest);
    
    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    void menuCallback(CCObject* sender);
protected:
    
    
};



#endif /* defined(__SpriteHelper2_TestCases__Sprites_LoadSpriteFromPNGTest__) */
