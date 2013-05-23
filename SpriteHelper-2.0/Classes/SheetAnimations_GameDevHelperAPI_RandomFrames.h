//
//  SheetAnimations_GameDevHelperAPI_RandomFrames.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __SpriteHelper2_TestCases__SheetAnimations_GameDevHelperAPI_RandomFrames__
#define __SpriteHelper2_TestCases__SheetAnimations_GameDevHelperAPI_RandomFrames__


#include "cocos2d.h"
#include "TestLayer.h"
#include "GameDevHelper.h"
class SheetAnimations_GameDevHelperAPI_RandomFrames : public TestLayer, public GHAnimationDelegate
{
public:
	SheetAnimations_GameDevHelperAPI_RandomFrames();
	virtual ~SheetAnimations_GameDevHelperAPI_RandomFrames();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(SheetAnimations_GameDevHelperAPI_RandomFrames);
    
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);

    void animationFrameNotification(CCObject* object);
    
    //GHAnimation delegate notifications methods
    virtual void animationDidFinishPlayingOnSprite(GHAnimation* anim, GHSprite* sprite);
    virtual void animationDidChangeFrameIdxOnSprite(GHAnimation* anim, int frmIdx, GHSprite* sprite);
    virtual void animationDidFinishRepetitionOnSprite(GHAnimation* anim, int repetitionNo, GHSprite* sprite);
};



#endif /* defined(__SpriteHelper2_TestCases__SheetAnimations_GameDevHelperAPI_RandomFrames__) */
