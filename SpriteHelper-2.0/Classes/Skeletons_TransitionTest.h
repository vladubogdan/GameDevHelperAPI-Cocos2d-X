//
//  Skeletons_LoadPoseTest.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __SpriteHelper2_TestCases__Skeletons_TransitionTest__
#define __SpriteHelper2_TestCases__Skeletons_TransitionTest__


#include "cocos2d.h"
#include "TestLayer.h"
#include "GameDevHelper.h"

class Skeletons_TransitionTest : public TestLayer
{
public:
	Skeletons_TransitionTest();
	virtual ~Skeletons_TransitionTest();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Skeletons_TransitionTest);
    
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);
    
    GHSkeleton* skeleton;
    
    void changeAnimation();
};



#endif /* defined(__SpriteHelper2_TestCases__Skeletons_TransitionTest__) */
