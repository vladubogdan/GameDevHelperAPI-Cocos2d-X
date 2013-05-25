//
//  TestLayer.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#ifndef __TestLayer__
#define __TestLayer__


#include "cocos2d.h"

class TestLayer : public cocos2d::CCLayer
{
public:
	TestLayer();
	virtual ~TestLayer();
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool,
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(TestLayer);
    
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    void menuCallback(CCObject* sender);
    
    virtual std::string initTest();
    virtual void executeTestCodeAtPosition(cocos2d::CCPoint p);
    
    cocos2d::CCSpriteBatchNode *batchNodeParent;
protected:
    
};



#endif /* defined(__SpriteHelper2_TestCases__Sprites_LoadSpriteFromPNGTest__) */
