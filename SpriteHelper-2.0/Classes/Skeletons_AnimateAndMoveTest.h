//
//  Skeletons_AnimateAndMoveTest.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __SpriteHelper2_TestCases__Skeletons_AnimateAndMoveTest__
#define __SpriteHelper2_TestCases__Skeletons_AnimateAndMoveTest__


#include "cocos2d.h"
#include "TestLayer.h"
#include "GameDevHelper.h"

class Skeletons_AnimateAndMoveTest : public TestLayer, public GHSkeletonDelegate
{
public:
	Skeletons_AnimateAndMoveTest();
	virtual ~Skeletons_AnimateAndMoveTest();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Skeletons_AnimateAndMoveTest);
    
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);

    void animationFrameNotification(CCObject* object);
    
    
    virtual void didStartAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton);
    
    virtual void didStopAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton);
    
    virtual void didFinishLoopInAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton);

    
    GHSkeleton* skeleton;
    

    virtual void update(float dt);
};



#endif /* defined(__SpriteHelper2_TestCases__Skeletons_AnimateAndMoveTest__) */
