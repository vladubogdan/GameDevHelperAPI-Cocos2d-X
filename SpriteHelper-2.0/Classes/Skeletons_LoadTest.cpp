//
//  Skeletons_LoadTest.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Skeletons_LoadTest.h"
#include "HelloWorldScene.h"
#include "GameDevHelper.h"
using namespace cocos2d;

Skeletons_LoadTest::~Skeletons_LoadTest()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Skeletons_LoadTest::Skeletons_LoadTest()
{
}

CCScene* Skeletons_LoadTest::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Skeletons_LoadTest *layer = Skeletons_LoadTest::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

std::string Skeletons_LoadTest::initTest()
{
    skeleton = NULL;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLayer::draw ();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    this->executeTestCodeAtPosition(ccp(s.width/2, s.height/2));
    
    
    return "Demonstrate loading a skeleton.\nTouch and drag to move the left hand.";
}

void Skeletons_LoadTest::executeTestCodeAtPosition(CCPoint p)
{
    
    if(skeleton == NULL)
    {
        skeleton = GHSkeleton::createWithFile("skeletons/Officer_Officer.plist");
        
        skeleton->setPosition(p);
        this->addChild(skeleton);
    }
}

void Skeletons_LoadTest::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    if(skeleton){
        skeleton->setPositionForBoneNamed(location, "leftHand");
    }
}
