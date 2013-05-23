//
//  Physics_CollisionFiltering.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __SpriteHelper2_TestCases__Physics_CollisionFiltering__
#define __SpriteHelper2_TestCases__Physics_CollisionFiltering__


#include "cocos2d.h"
#include "TestLayer.h"

#include "Box2D.h"

//Pixel to metres ratio. Box2D uses metres as the unit for measurement.
//This ratio defines how many pixels correspond to 1 Box2D "metre"
//Box2D is optimized for objects of 1x1 metre therefore it makes sense
//to define the ratio so that your most common object type is 1x1 metre.
#define PTM_RATIO 32

class Physics_CollisionFiltering : public TestLayer
{
public:
	Physics_CollisionFiltering();
	virtual ~Physics_CollisionFiltering();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Physics_CollisionFiltering);
    
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);

    void animationFrameNotification(CCObject* object);
    
    
    b2World* world;					// strong ref
    void initPhysics();
    
    virtual void update(float dt);
    
    
    void createMouseJointForTouchLocation(cocos2d::CCPoint point);
    void setTargetOnMouseJoint(cocos2d::CCPoint point);
    void destroyMouseJoint();
    
    b2Body* groundBody;
    b2MouseJoint* mouseJoint;
};



#endif /* defined(__SpriteHelper2_TestCases__Physics_CollisionFiltering__) */
