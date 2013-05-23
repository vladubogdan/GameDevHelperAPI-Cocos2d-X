//
//  Sprites_LoadSpriteFromPNGTest.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __SpriteHelper2_TestCases__SheetAnimations_LoadAnimationTest__
#define __SpriteHelper2_TestCases__SheetAnimations_LoadAnimationTest__


#include "cocos2d.h"
#include "TestLayer.h"

class SheetAnimations_LoadAnimationTest : public TestLayer
{
public:
	SheetAnimations_LoadAnimationTest();
	virtual ~SheetAnimations_LoadAnimationTest();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(SheetAnimations_LoadAnimationTest);
    
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);

    void animationFrameNotification(CCObject* object);
};



#endif /* defined(__SpriteHelper2_TestCases__SheetAnimations_LoadAnimationTest__) */
