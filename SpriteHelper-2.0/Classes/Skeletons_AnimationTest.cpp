//
//  Skeletons_AnimationTest.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Skeletons_AnimationTest.h"
#include "HelloWorldScene.h"
#include "GameDevHelper.h"
using namespace cocos2d;

Skeletons_AnimationTest::~Skeletons_AnimationTest()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Skeletons_AnimationTest::Skeletons_AnimationTest()
{
}

CCScene* Skeletons_AnimationTest::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Skeletons_AnimationTest *layer = Skeletons_AnimationTest::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

std::string Skeletons_AnimationTest::initTest()
{
    skeleton = NULL;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    GHSkeletalAnimationCache* cache = GHSkeletalAnimationCache::sharedSkeletalAnimationCache();
    cache->addSkeletalAnimationWithFile("skeletons/animations/BallPlay.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Bow.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Death.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/HatWave.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/HolsterGun.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Idle.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Push.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Shoot.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/SoftWalk.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/StrongWalk.plist");
    
    
    
    this->executeTestCodeAtPosition(ccp(s.width/2, s.height/2));
    
    return "Demonstrate skeletal animations.\nTap to change animation.\nWatch console for notifications.";
}

void Skeletons_AnimationTest::executeTestCodeAtPosition(CCPoint p)
{
    
    if(skeleton == NULL)
    {
        skeleton = GHSkeleton::createWithFile("skeletons/Officer_Officer.plist");
        
        skeleton->setPosition(p);
        skeleton->setDelegate(this);
        this->addChild(skeleton);
    }
    
    this->changeAnimation();
}

void Skeletons_AnimationTest::changeAnimation(){
    
    
    std::vector<std::string> animNames;
    animNames.push_back("BallPlay");
    animNames.push_back("Bow");
    animNames.push_back("Death");
    animNames.push_back("HatWave");
    animNames.push_back("HolsterGun");
    animNames.push_back("Idle");
    animNames.push_back("Push");
    animNames.push_back("Shoot");
    animNames.push_back("SoftWalk");
    animNames.push_back("StrongWalk");
    
    int animNameIdx = arc4random() % animNames.size();
    
    std::string finalAnimName = animNames[animNameIdx];
    
    CCLog("START ANIMIMATION %s", finalAnimName.c_str());
    
    if(skeleton){
        skeleton->playAnimationWithName(finalAnimName.c_str());
    }
}


void Skeletons_AnimationTest::didStartAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){
    CCLog("DID START ANIMATION NAMED %s ON SKELETON %p", animation->getName().c_str(), skeleton);
}

void Skeletons_AnimationTest::didStopAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){
    
    CCLog("DID STOP ANIMATION NAMED %s ON SKELETON %p", animation->getName().c_str(), skeleton);
}

void Skeletons_AnimationTest::didFinishLoopInAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){
    
    CCLog("DID FINISH LOOP IN ANIMATION NAMED %s ON SKELETON %p", animation->getName().c_str(), skeleton);
}

