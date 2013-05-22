//
//  Sprites_LoadSpriteFromPVRTest.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __Sprites_LoadSpriteFromPVRTest__
#define __Sprites_LoadSpriteFromPVRTest__


#include "cocos2d.h"
#include "TestLayer.h"

class Sprites_LoadSpriteFromPVRTest : public TestLayer
{
public:
	Sprites_LoadSpriteFromPVRTest();
	virtual ~Sprites_LoadSpriteFromPVRTest();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Sprites_LoadSpriteFromPVRTest);
    
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);

};



#endif /* defined(__Sprites_LoadSpriteFromPVRTest__) */
