//
//  Sprites_LoadSpriteFromPVRCCZTest.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __Sprites_LoadSpriteFromPVRCCZTest__
#define __Sprites_LoadSpriteFromPVRCCZTest__


#include "cocos2d.h"
#include "TestLayer.h"

class Sprites_LoadSpriteFromPVRCCZTest : public TestLayer
{
public:
	Sprites_LoadSpriteFromPVRCCZTest();
	virtual ~Sprites_LoadSpriteFromPVRCCZTest();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Sprites_LoadSpriteFromPVRCCZTest);
    
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);

};



#endif /* defined(Sprites_LoadSpriteFromPVRCCZTest) */
