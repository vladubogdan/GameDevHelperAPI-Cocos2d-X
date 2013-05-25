//
//  Skeletons_AnimateAndMoveTest.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Skeletons_AnimateAndMoveTest.h"
#include "HelloWorldScene.h"
#include "GameDevHelper.h"
using namespace cocos2d;

Skeletons_AnimateAndMoveTest::~Skeletons_AnimateAndMoveTest()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Skeletons_AnimateAndMoveTest::Skeletons_AnimateAndMoveTest()
{
}

CCScene* Skeletons_AnimateAndMoveTest::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Skeletons_AnimateAndMoveTest *layer = Skeletons_AnimateAndMoveTest::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

std::string Skeletons_AnimateAndMoveTest::initTest()
{
    skeleton = NULL;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    GHSkeletalAnimationCache* cache = GHSkeletalAnimationCache::sharedSkeletalAnimationCache();
//    cache->addSkeletalAnimationWithFile("skeletons/animations/BallPlay.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/Bow.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/Death.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/HatWave.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/HolsterGun.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/Idle.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/Push.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/Shoot.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/SoftWalk.plist");
//    cache->addSkeletalAnimationWithFile("skeletons/animations/StrongWalk.plist");
    
    
    
    this->executeTestCodeAtPosition(ccp(s.width/2, s.height/2));
    
    this->scheduleUpdate();
    
    return "Demonstrate how to move a skeleton.\nTap to change direction...";
}

void Skeletons_AnimateAndMoveTest::executeTestCodeAtPosition(CCPoint p)
{
    
    if(skeleton == NULL)
    {
        skeleton = GHSkeleton::createWithFile("skeletons/Officer_Officer.plist");
        
        skeleton->setPosition(p);
        skeleton->setDelegate(this);
        this->addChild(skeleton);
        skeleton->playAnimationWithName("SoftWalk");
    }
}

void Skeletons_AnimateAndMoveTest::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(skeleton){
        skeleton->setScaleX(-1*skeleton->getScaleX());
    }
}

void Skeletons_AnimateAndMoveTest::update(float dt)
{
    if(skeleton == NULL)return;
    
    CCPoint curPosition = skeleton->getPosition();
    if(skeleton->getScaleX() > 0)
    {
        skeleton->setPosition(ccp(curPosition.x + 1.4, curPosition.y));
    }
    else{
        skeleton->setPosition(ccp(curPosition.x - 1.4, curPosition.y));
    }
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    if(curPosition.x > s.width-30){
        
        skeleton->setScaleX(-1);
    }
    else if(curPosition.x < 30)
    {
        skeleton->setScaleX(1);
    }
}


void Skeletons_AnimateAndMoveTest::didStartAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){
    CCLog("DID START ANIMATION NAMED %s ON SKELETON %p", animation->getName().c_str(), skeleton);
}

void Skeletons_AnimateAndMoveTest::didStopAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){
    
    CCLog("DID STOP ANIMATION NAMED %s ON SKELETON %p", animation->getName().c_str(), skeleton);
}

void Skeletons_AnimateAndMoveTest::didFinishLoopInAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){
    
    CCLog("DID FINISH LOOP IN ANIMATION NAMED %s ON SKELETON %p", animation->getName().c_str(), skeleton);
}

