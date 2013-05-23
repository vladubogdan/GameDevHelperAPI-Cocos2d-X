//
//  Physics_LoadSpritesWithPhysicalBody.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __SpriteHelper2_TestCases__Physics_LoadSpritesWithPhysicalBody__
#define __SpriteHelper2_TestCases__Physics_LoadSpritesWithPhysicalBody__


#include "cocos2d.h"
#include "TestLayer.h"

#include "Box2D.h"

//Pixel to metres ratio. Box2D uses metres as the unit for measurement.
//This ratio defines how many pixels correspond to 1 Box2D "metre"
//Box2D is optimized for objects of 1x1 metre therefore it makes sense
//to define the ratio so that your most common object type is 1x1 metre.
#define PTM_RATIO 32

class Physics_LoadSpritesWithPhysicalBody : public TestLayer
{
public:
	Physics_LoadSpritesWithPhysicalBody();
	virtual ~Physics_LoadSpritesWithPhysicalBody();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Physics_LoadSpritesWithPhysicalBody);
    
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);

    void animationFrameNotification(CCObject* object);
    
    
    b2World* world;					// strong ref
    void initPhysics();
    
    virtual void update(float dt);
};



#endif /* defined(__SpriteHelper2_TestCases__Physics_LoadSpritesWithPhysicalBody__) */
